// use twelite mwx c++ template library
#include <TWELITE>
#include <NWK_SIMPLE>

#define M_PI 3.1415927

#define STS_INT 0
#define STS_LAU 1
#define STS_DEV 2
#define STS_FSA 3
/*** Config part */
// application ID
const uint32_t APP_ID = 0x000103E9;
// channel
const uint8_t CHANNEL = 13;
/*** function prototype */
void timer_1();
void send_data_twe2mono(uint32_t addr);
void read_data_frommono();

void send_data_twe2mpu();
void read_data_frommpu();

void state_controll();
void init_mode();
void launch_mode();
void develop_mode();
void fsa_mode();
void fail_diagnosis();

void cam_start();
void cam_finish();
void para_deploy();
void para_shut();
/*** application defs */
// packet message
const int SEND_LEN = 51;

//global value
uint16_t cnt1 = 0;//LEDカウンタ
uint16_t cnt2 = 0;//データ送信カウンタ
float dt = 0.001;//s
bool cnt1_flag[5] = {0,0,0,0,0};
bool cnt2_flag[5] = {0,0,0,0,0};
float cnt1_time = 0.2;//割り込み周期[sec]データ送信用
float cnt2_time = 0.02;//割り込み周期[sec]//制御用

bool diagnosis_act = 0;

uint8_t statuspc = 0;
uint8_t statustwe = 0;
uint8_t statusmpu = 0;
bool f_waitok = 0;
bool f_camact = 0;
bool f_fsa = 0;
bool f_fsaend = 0;

float wait_timer = 0.0f;
bool wait_flg = 0;

uint8_t camseq = 0;

float twe_t = 0.0f;
float mpu_t = 0.0f;
float pc_t = 0.0f;

float acc_data[3] = {0, 0, 0}; //[m/s^2]
float v_data[3] = {0, 0, 0}; //[m/s]
float xeh_data[3] = {0, 0, 0}; //[m]
float gyro_data[3] = {0, 0, 0}; //[rad/s]
float euler_data[3] = {0, 0, 0}; //[rad]
float airvel_data = 0.0; //[m/s]
float quat_data[4] = {0, 0, 0, 0}; //[-]

float elevonL_com = 0.0; //[deg]
float elevonR_com = 0.0; //[deg]
float parachute_com = 0.0; //[-]

float acc_dummydata[3] = {0, 0, 0}; //[m/s^2]
float v_dummydata[3] = {0, 0, 0}; //[m/s]
float xeh_dummydata[3] = {0, 0, 0}; //[m]
float gyro_dummydata[3] = {0, 0, 0}; //[rad/s]
float euler_dummydata[3] = {0, 0, 0}; //[rad]
float airvel_dummydata = 0.0; //[m/s]
float quat_dummydata[4] = {0, 0, 0, 0}; //[-]

float elevonL_dummycom = 0.0; //[deg]
float elevonR_dummycom = 0.0; //[deg]
float parachute_dummycom = 0.0; //[-]

/*** setup procedure (run once at cold boot) */
void setup() {
	/*** SETUP section */
	// the twelite main class
	the_twelite
		<< TWENET::appid(APP_ID)    // set application ID (identify network group)
		<< TWENET::channel(CHANNEL) // set channel (pysical channel)
		<< TWENET::rx_when_idle(0x01);  // open receive circuit (if not set, it can't listen packts from others)

	// Register Network
	auto&& nwk = the_twelite.network.use<NWK_SIMPLE>();
	nwk	<< NWK_SIMPLE::logical_id(0x04); // set Logical ID. (0xFE means a child device with no ID)

	// initialize the object. (allocate Tx/Rx buffer, and etc..)
	Serial1.setup(64, 192);

	/*** BEGIN section */
	SerialParser.begin(PARSER::BINARY , 255); // Initialize the serial parser
	the_twelite.begin(); // start twelite!

	Timer0.begin(uint16_t(1.0/dt)); // 5Hz Timer

	Timer4.begin(50,true,true); // 50Hz ,ソフトウェア割り込み有効、PWM出力有効 Timer4
	Timer4.change_duty(40,1024);

	Serial1.begin(115200);// start the peripheral with 115200bps.
	pinMode(19, OUTPUT);
	digitalWrite(19, LOW);

	/*** INIT message */
	//Serial << "twe start" << mwx::crlf;
}
/*** loop procedure (called every event) */
void loop() {
	timer_1();
	//検知系の関数
	read_data_frommpu();
	read_data_frommono();
	fail_diagnosis();//故障検知

	state_controll();//状態遷移

	send_data_twe2mpu();//0.02s周期でmpuに送信
	send_data_twe2mono(0x03);//0.2s周期でPCに送信
}

void timer_1() {//
	if (Timer0.available()) {
	  cnt1 = cnt1 + 1;
	  cnt2 = cnt2 + 1;
	  // Serial.println(t);
	  if (cnt1 > (uint16_t)(cnt1_time / dt) - 1) { //PCとのデータ通信用
			for(int i = 0;i<sizeof(cnt1_flag);i++) cnt1_flag[i] = 1;
	    cnt1 = 0;
			Serial << format(" statuspc=%i>", statuspc) << mwx::crlf;
	  }
	  if (cnt2 > (uint16_t)(cnt2_time / dt) - 1) { //制御用
			for(int i = 0;i<sizeof(cnt2_flag);i++) cnt2_flag[i] = 1;
	    cnt2 = 0;
	  }
	}
}

void state_controll(){
	int counterid = 1;
	if(cnt2_flag[counterid] == 1){
		if(statustwe >= 0 && statustwe <= 3){/* 初期状態　処理 */
			init_mode();
		}else if(statustwe >= 4 && statustwe <= 10){/* Launch mode　処理 */
			launch_mode();
		}else if(statustwe >= 11 && statustwe <= 15){/* Develop mode　処理 */
			develop_mode();
		}else{/* FSA mode　処理 */
			fsa_mode();//FSA実施
		}
		cnt2_flag[counterid] = 0;
	}
}

void init_mode(){
	switch (statustwe) {
	case 0:
		/* 初期状態 */
		if(statustwe == 0){
			statustwe = 1;
		}
		break;
	case 1:
		/* 通信確立待機時間 */
		delay(10000);
		f_waitok = 1;
		if(f_waitok == 1){
			statustwe = 2;
		}
		break;
	case 2:
		/* mpu初期化処理 */
		if(statusmpu == 3){
			para_shut();
			statustwe = 3;
			diagnosis_act = 1;//故障検知開始
		}
		break;
	case 3:
		/* 準備完了待機 */
		if(statuspc == 1){//Launch modeへの遷移指示
			statustwe = 4;
		}
		else if(statuspc == 2){//サーボ・センサーの作動をチェックするモード
			statustwe = 11;
		}
		else if(statuspc == 3){//カメラの動作をチェックするモード(カメラON)
			statustwe = 12;
		}
		else if(statuspc == 4){//カメラの動作をチェックするモード(カメラOFF)
			statustwe = 13;
		}
		else if(statuspc == 5){//制御動作確認モード
			statustwe = 14;
		}
		else if(statuspc == 6){//ダミーセンサ情報に基づいた制御動作確認モード
			statustwe = 15;
		}else{
			//待機
		}
		break;
	default:
		/* なにもしない */
		break;
	}

}

void develop_mode(){
	/* 状態遷移判断 */
	switch (statustwe) {
	case 11:
		/* サーボ・センサー確認モード */
		if(parachute_dummycom > 0.5){
			para_deploy();
		}else{
			para_shut();
		}
		if(statuspc == 1){//Launch modeへの遷移指示
			statustwe = 4;
		}
		else if(statuspc == 2){//サーボ・センサーの作動をチェックするモード
			statustwe = 11;
		}
		else if(statuspc == 3){//カメラの動作をチェックするモード(カメラON)
			statustwe = 12;
		}
		else if(statuspc == 4){//カメラの動作をチェックするモード(カメラOFF)
			statustwe = 13;
		}
		else if(statuspc == 5){//制御動作確認モード
			statustwe = 14;
		}
		else if(statuspc == 6){//ダミーセンサ情報に基づいた制御動作確認モード
			statustwe = 15;
		}else{
			//待機
		}
		break;
	case 12:
		/* カメラ動作確認モード ON */
		cam_start();
		if( f_camact == 1){
			if(statuspc == 1){//Launch modeへの遷移指示
				statustwe = 4;
			}
			else if(statuspc == 2){//サーボ・センサーの作動をチェックするモード
				statustwe = 11;
			}
			else if(statuspc == 3){//カメラの動作をチェックするモード(カメラON)
				statustwe = 12;
			}
			else if(statuspc == 4){//カメラの動作をチェックするモード(カメラOFF)
				statustwe = 13;
			}
			else if(statuspc == 5){//制御動作確認モード
				statustwe = 14;
			}
			else if(statuspc == 6){//ダミーセンサ情報に基づいた制御動作確認モード
				statustwe = 15;
			}else{
				//待機
			}
		}
		break;
	case 13:
		/* カメラ動作確認モード OFF */
		cam_finish();
		if( f_camact == 0){
			if(statuspc == 1){//Launch modeへの遷移指示
				statustwe = 4;
			}
			else if(statuspc == 2){//サーボ・センサーの作動をチェックするモード
				statustwe = 11;
			}
			else if(statuspc == 3){//カメラの動作をチェックするモード(カメラON)
				statustwe = 12;
			}
			else if(statuspc == 4){//カメラの動作をチェックするモード(カメラOFF)
				statustwe = 13;
			}
			else if(statuspc == 5){//制御動作確認モード
				statustwe = 14;
			}
			else if(statuspc == 6){//ダミーセンサ情報に基づいた制御動作確認モード
				statustwe = 15;
			}else{
				//待機
			}
		}
		break;
	case 14:
		/* 制御の動作確認モード */
		if(statuspc == 1){//Launch modeへの遷移指示
			statustwe = 4;
		}
		else if(statuspc == 2){//サーボ・センサーの作動をチェックするモード
			statustwe = 11;
		}
		else if(statuspc == 3){//カメラの動作をチェックするモード(カメラON)
			statustwe = 12;
		}
		else if(statuspc == 4){//カメラの動作をチェックするモード(カメラOFF)
			statustwe = 13;
		}
		else if(statuspc == 5){//制御動作確認モード
			statustwe = 14;
		}
		else if(statuspc == 6){//ダミーセンサ情報に基づいた制御動作確認モード
			statustwe = 15;
		}else{
			//待機
		}
		break;
	case 15:
		/* ダミー情報に基づいた制御の動作確認モード */
		if(statuspc == 1){//Launch modeへの遷移指示
			statustwe = 4;
		}
		else if(statuspc == 2){//サーボ・センサーの作動をチェックするモード
			statustwe = 11;
		}
		else if(statuspc == 3){//カメラの動作をチェックするモード(カメラON)
			statustwe = 12;
		}
		else if(statuspc == 4){//カメラの動作をチェックするモード(カメラOFF)
			statustwe = 13;
		}
		else if(statuspc == 5){//制御動作確認モード
			statustwe = 14;
		}
		else if(statuspc == 6){//ダミーセンサ情報に基づいた制御動作確認モード
			statustwe = 15;
		}else{
			//待機
		}
		break;
	default:

		break;
	}
}

void launch_mode(){
	switch (statustwe) {
	case 4:
		/* カメラスタート */
		cam_start();
		if( f_camact == 1){
			statustwe = 5;
		}
		break;
	case 5:
		/* チェック */
		if(statusmpu == 6 || statusmpu == 7 || statusmpu == 8 || statusmpu == 9 || statusmpu == 10){
			statustwe = 6;
		}
		break;
	case 6:
		/* 発射待機 */
		if(statusmpu == 7 || statusmpu == 8 || statusmpu == 9 || statusmpu == 10){
			statustwe = 7;
		}
		break;
	case 7:
		/* 制御中 */
		if(statusmpu == 8 || statusmpu == 9 || statusmpu == 10){
			statustwe = 8;
		}
		break;
	case 8:
		/* パラシュート展開 */
		para_deploy();
		if(statusmpu == 9 || statusmpu == 10){
			statustwe = 9;
		}
		break;
	case 9:
		/* カメラ終了指示 */
		cam_finish();
		if( f_camact == 0){
			statustwe = 10;
		}
		break;
		case 10:
			/* 発射終了待機 */
			if(statuspc == 2){//サーボ・センサーの作動をチェックするモード
				statustwe = 11;
			}
			else if(statuspc == 3){//カメラの動作をチェックするモード(カメラON)
				statustwe = 12;
			}
			else if(statuspc == 4){//カメラの動作をチェックするモード(カメラOFF)
				statustwe = 13;
			}
			else if(statuspc == 5){//制御動作確認モード
				statustwe = 14;
			}
			else if(statuspc == 6){//ダミーセンサ情報に基づいた制御動作確認モード
				statustwe = 15;
			}else{
				//待機
			}
			break;
	default:
		/* なにもしない */
		break;
	}
}

void cam_start(){
	if(f_camact == 0){
		if(wait_flg == 0 && camseq != 4){
			wait_timer = millis()/1000.0;
			camseq = 0;
			wait_flg = 1;
		}
		if(millis()/1000.0 - wait_timer > 5.0 && camseq == 0){
			camseq = 1;
		}
		if(millis()/1000.0 - wait_timer > 8.0 && camseq == 1){
			camseq = 2;
		}
		if(millis()/1000.0 - wait_timer > 9.0 && camseq == 2){
			camseq = 3;
		}
		if(millis()/1000.0 - wait_timer > 10.0 && camseq == 3){
			camseq = 4;
		}
		switch (camseq) {
		case 0:
			/* 電源ON start */
			digitalWrite(19, HIGH);
			break;
		case 1:
			/* 電源ON end */
			digitalWrite(19, LOW);
			break;
		case 2:
			/* 撮影開始 start */
			digitalWrite(19, HIGH);
			break;
		case 3:
			/* 撮影開始 end */
			digitalWrite(19, LOW);
			break;
		case 4:
			/* カメラスタート */
			wait_flg = 0;
			f_camact = 1;
			break;
		default:
			break;
		}
	}
}

void cam_finish(){
	if(f_camact == 1){
		if(wait_flg == 0 && camseq != 2){
			wait_timer = millis()/1000.0;
			camseq = 0;
			wait_flg = 1;
		}

		if(millis()/1000.0 - wait_timer > 5.0 && camseq == 0){
			camseq = 1;
		}
		if(millis()/1000.0 - wait_timer > 10.0 && camseq == 1){
			camseq = 2;
		}

		switch (camseq) {
		case 0:
			/* 電源OFF start */
			digitalWrite(19, HIGH);
			break;
		case 1:
			/* 電源OFF end */
			digitalWrite(19, LOW);
			break;
		case 2:
			/* カメラ終了 */
			wait_flg = 0;
			f_camact = 0;
			break;
		default:
			break;
		}
	}
}

void para_deploy(){
	Timer4.change_duty(60,1024);
}

void para_shut(){
	Timer4.change_duty(110,1024);
}

void fail_diagnosis(){
	if(diagnosis_act == 1){//故障検知フラグ
		if(statustwe != 200 && f_fsa == 1){
			statustwe = 200;
		}
	}
	if(statuspc > 9){
		f_fsa = 1;
	}
}

void fsa_mode(){
	switch (statustwe) {
	case 200:
		/* FSA実施中 */
		para_deploy();
		statustwe = 201;
		break;
	case 201:
		/* FSA完了後待機 */
		break;
	default:
		/* なにもしない */
		break;
	}
}

void read_data_frommono(){
	// packet
	uint8_t r_uchMsg[49];//monoから受け取ったバイナリデータ
	while (the_twelite.receiver.available()) {
			auto&& rx = the_twelite.receiver.read();
			expand_bytes(rx.get_payload().begin(), rx.get_payload().end(), r_uchMsg);
					uint16_t ushTmp;
					byte low;
					byte high;

					//statuspc
					statuspc = r_uchMsg[0];

					//pc_t
					low = r_uchMsg[1];
					high = r_uchMsg[2];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					pc_t = ((float)ushTmp / 65535.0 * 600.0);

					//acc_data
					low = r_uchMsg[3];
					high = r_uchMsg[4];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					acc_dummydata[0] = ((float)ushTmp / 65535.0 * 32.0 - 16.0);

					low = r_uchMsg[5];
					high = r_uchMsg[6];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					acc_dummydata[1] = ((float)ushTmp / 65535.0 * 32.0 - 16.0);

					low = r_uchMsg[7];
					high = r_uchMsg[8];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					acc_dummydata[2] = ((float)ushTmp / 65535.0 * 32.0 - 16.0);

					//v_data
					low = r_uchMsg[9];
					high = r_uchMsg[10];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					v_dummydata[0] = ((float)ushTmp / 65535.0 * 100.0 - 50.0);

					low = r_uchMsg[11];
					high = r_uchMsg[12];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					v_dummydata[1] = ((float)ushTmp / 65535.0 * 100.0 - 50.0);

					low = r_uchMsg[13];
					high = r_uchMsg[14];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					v_dummydata[2] = ((float)ushTmp / 65535.0 * 100.0 - 50.0);

					//xi eta hight_data
					low = r_uchMsg[15];
					high = r_uchMsg[16];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					xeh_dummydata[0] = ((float)ushTmp / 65535.0 * 30.0 - 15.0);

					low = r_uchMsg[17];
					high = r_uchMsg[18];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					xeh_dummydata[1] = ((float)ushTmp / 65535.0 * 30.0 - 15.0);

					low = r_uchMsg[19];
					high = r_uchMsg[20];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					xeh_dummydata[2] = ((float)ushTmp / 65535.0  * 30.0 - 0.0);

					//gyro_data
					low = r_uchMsg[21];
					high = r_uchMsg[22];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					gyro_dummydata[0] = ((float)ushTmp / 65535.0 * (6.0 * M_PI) - 3.0 * M_PI);

					low = r_uchMsg[23];
					high = r_uchMsg[24];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					gyro_dummydata[1] = ((float)ushTmp / 65535.0 * (6.0 * M_PI) - 3.0 * M_PI);

					low = r_uchMsg[25];
					high = r_uchMsg[26];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					gyro_dummydata[2] = ((float)ushTmp / 65535.0 * (6.0 * M_PI) - 3.0 * M_PI);

					//euler_data
					low = r_uchMsg[27];
					high = r_uchMsg[28];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					euler_dummydata[0] = ((float)ushTmp / 65535.0 * (2.0 * M_PI) - M_PI);

					low = r_uchMsg[29];
					high = r_uchMsg[30];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					euler_dummydata[1] = ((float)ushTmp / 65535.0 * (2.0 * M_PI) - M_PI);

					low = r_uchMsg[31];
					high = r_uchMsg[32];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					euler_dummydata[2] = ((float)ushTmp / 65535.0 * (2.0 * M_PI) - M_PI);

					//airvel_data
					low = r_uchMsg[33];
					high = r_uchMsg[34];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					airvel_dummydata = ((float)ushTmp / 65535.0 * (255.0) - 0.0);

					//quat_data
					low = r_uchMsg[35];
					high = r_uchMsg[36];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					quat_dummydata[0] = ((float)ushTmp / 65535.0 * (2.0) - 1.0);

					low = r_uchMsg[37];
					high = r_uchMsg[38];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					quat_dummydata[1] = ((float)ushTmp / 65535.0 * (2.0) - 1.0);

					low = r_uchMsg[39];
					high = r_uchMsg[40];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					quat_dummydata[2] = ((float)ushTmp / 65535.0 * (2.0) - 1.0);

					low = r_uchMsg[41];
					high = r_uchMsg[42];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					quat_dummydata[3] = ((float)ushTmp / 65535.0 * (2.0) - 1.0);

					//elevonR_data
					low = r_uchMsg[43];
					high = r_uchMsg[44];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					elevonR_dummycom = ((float)ushTmp / 65535.0 * (240.0) - 120.0);

					//elevonL_data
					low = r_uchMsg[45];
					high = r_uchMsg[46];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					elevonL_dummycom = ((float)ushTmp / 65535.0 * (240.0) - 120.0);

					//parachute_data
					low = r_uchMsg[47];
					high = r_uchMsg[48];
					ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
					parachute_dummycom = ((float)ushTmp / 65535.0 * (1.0) - 0.0);
		}
}

void read_data_frommpu(){
	while(Serial1.available()){
		//Serial << "avail" << mwx::crlf;
	  if ( SerialParser.parse(Serial1.read())) {
			//Serial << "SerialParser" << mwx::crlf;
			auto&& serial_data = SerialParser.get_buf();
      int n = 0;
      uint16_t ushTmp;
      byte low;
      byte high;
			//mpuステータス
      statusmpu = (uint8_t)serial_data[0];
			//mpu時間
      low = serial_data[1];
      high = serial_data[2];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      mpu_t = ((float)ushTmp / 65535.0 * 600.0);
			//加速度データ
			low = serial_data[3];
			high = serial_data[4];
			ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
			acc_data[0] = ((float)ushTmp / 65535.0 * 32.0 - 16.0);

      low = serial_data[5];
      high = serial_data[6];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      acc_data[1] = ((float)ushTmp / 65535.0 * 32.0 - 16.0);

      low = serial_data[7];
      high = serial_data[8];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      acc_data[2] = ((float)ushTmp / 65535.0 * 32.0 - 16.0);
			//速度データ
      low = serial_data[9];
      high = serial_data[10];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      v_data[0] = ((float)ushTmp / 65535.0 * 100.0 - 50.0);

      low = serial_data[11];
      high = serial_data[12];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      v_data[1] = ((float)ushTmp / 65535.0 * 100.0 - 50.0);

      low = serial_data[13];
      high = serial_data[14];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      v_data[2] = ((float)ushTmp / 65535.0 * 100.0 - 50.0);
			//位置データ
      low = serial_data[15];
      high = serial_data[16];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      xeh_data[0] = ((float)ushTmp / 65535.0 * 30.0 - 15.0);

      low = serial_data[17];
      high = serial_data[18];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      xeh_data[1] = ((float)ushTmp / 65535.0 * 30.0 - 15.0);

      low = serial_data[19];
      high = serial_data[20];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      xeh_data[2] = ((float)ushTmp / 65535.0  * 30.0 - 0.0);

			//角速度データ
      low = serial_data[21];
      high = serial_data[22];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      gyro_data[0] = ((float)ushTmp / 65535.0 * (6.0 * M_PI) - 3.0 * M_PI);

      low = serial_data[23];
      high = serial_data[24];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      gyro_data[1] = ((float)ushTmp / 65535.0 * (6.0 * M_PI) - 3.0 * M_PI);

      low = serial_data[25];
      high = serial_data[26];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      gyro_data[2] = ((float)ushTmp / 65535.0 * (6.0 * M_PI) - 3.0 * M_PI);

			//Euler角データ
			low = serial_data[27];
      high = serial_data[28];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      euler_data[0] = ((float)ushTmp / 65535.0 * (2.0 * M_PI) - 1.0 * M_PI);

      low = serial_data[29];
      high = serial_data[30];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      euler_data[1] = ((float)ushTmp / 65535.0 * (2.0 * M_PI) - 1.0 * M_PI);

      low = serial_data[31];
      high = serial_data[32];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      euler_data[2] = ((float)ushTmp / 65535.0 * (2.0 * M_PI) - 1.0 * M_PI);
			//機体速度データ
			low = serial_data[33];
      high = serial_data[34];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      airvel_data = ((float)ushTmp / 65535.0 * (255.0) - 0.0);
			//クォータニオンデータ
      low = serial_data[35];
      high = serial_data[36];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      quat_data[0] = ((float)ushTmp / 65535.0 * (2.0) - 1.0);

      low = serial_data[37];
      high = serial_data[38];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      quat_data[1] = ((float)ushTmp / 65535.0 * (2.0) - 1.0);

			low = serial_data[39];
      high = serial_data[40];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      quat_data[2] = ((float)ushTmp / 65535.0 * (2.0) - 1.0);

			low = serial_data[41];
      high = serial_data[42];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      quat_data[3] = ((float)ushTmp / 65535.0 * (2.0) - 1.0);
			//elevonRデータ
			low = serial_data[43];
      high = serial_data[44];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      elevonR_com = ((float)ushTmp / 65535.0 * (240.0) - 120.0);
			//elevonLデータ
			low = serial_data[45];
      high = serial_data[46];
      ushTmp = (uint16_t)(((low << 8) & 0xff00) | (high & 0x00ff));
      elevonL_com = ((float)ushTmp / 65535.0 * (240.0) - 120.0);
	  }
	}
}

void send_data_twe2mono(uint32_t addr) {
	int counterid = 0;
	if(cnt1_flag[counterid] == 1){
		twe_t = millis()/1000.0;
		uint8_t s_uchMsg[SEND_LEN];
		uint16_t ushTmp;

		//statustwe
		ushTmp = (uint8_t)(statustwe);
		s_uchMsg[0] = ushTmp;

		//statusmpu
		ushTmp = (uint8_t)(statusmpu);
		s_uchMsg[1] = ushTmp;

		//twe_t
		ushTmp = (uint16_t)(twe_t / 600.0 * 65535.0);
		s_uchMsg[2] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[3] = (uint8_t)(ushTmp & 0x00ff);

		//mpu_t
		ushTmp = (uint16_t)(mpu_t / 600.0 * 65535.0);
		s_uchMsg[4] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[5] = (uint8_t)(ushTmp & 0x00ff);

		//acc_data
		ushTmp = (uint16_t)((acc_data[0] + 16.0) / (32.0) * 65535.0);
		s_uchMsg[6] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[7] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((acc_data[1] + 16.0) / (32.0) * 65535.0);
		s_uchMsg[8] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[9] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((acc_data[2] + 16.0) / (32.0) * 65535.0);
		s_uchMsg[10] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[11] = (uint8_t)(ushTmp & 0x00ff);

		//v_data
		ushTmp = (uint16_t)((v_data[0] + 50.0) / (100.0) * 65535.0);
		s_uchMsg[12] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[13] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((v_data[1] + 50.0) / (100.0) * 65535.0);
		s_uchMsg[14] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[15] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((v_data[2] + 50.0) / (100.0) * 65535.0);
		s_uchMsg[16] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[17] = (uint8_t)(ushTmp & 0x00ff);

		//xi eta hight_data
		ushTmp = (uint16_t)((xeh_data[0] + 15.0) / (30.0) * 65535.0);
		s_uchMsg[18] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[19] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((xeh_data[1] + 15.0) / (30.0) * 65535.0);
		s_uchMsg[20] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[21] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((xeh_data[2] + 0.0) / (30.0) * 65535.0);
		s_uchMsg[22] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[23] = (uint8_t)(ushTmp & 0x00ff);

		//gyro_data
		ushTmp = (uint16_t)((gyro_data[0] + 3 * M_PI) / (6 * M_PI) * 65535.0);
		s_uchMsg[24] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[25] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((gyro_data[1] + 3 * M_PI) / (6 * M_PI) * 65535.0);
		s_uchMsg[26] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[27] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((gyro_data[2] + 3 *  M_PI) /  (6 * M_PI) * 65535.0);
		s_uchMsg[28] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[29] = (uint8_t)(ushTmp & 0x00ff);

		//euler_data
		ushTmp = (uint16_t)((euler_data[0] + M_PI) /  (2 * M_PI) * 65535.0);
		s_uchMsg[30] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[31] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((euler_data[1] + M_PI) /  (2 * M_PI) * 65535.0);
		s_uchMsg[32] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[33] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((euler_data[2] + M_PI) /  (2 * M_PI) * 65535.0);
		s_uchMsg[34] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[35] = (uint8_t)(ushTmp & 0x00ff);

		//air_vel_data
		ushTmp = (uint16_t)((airvel_data + 0.0) /  (255.0) * 65535.0);
		s_uchMsg[36] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[37] = (uint8_t)(ushTmp & 0x00ff);

		//quat_data
		ushTmp = (uint16_t)((quat_data[0] + 1.0) /  (2.0) * 65535.0);
		s_uchMsg[38] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[39] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((quat_data[1] + 1.0) /  (2.0) * 65535.0);
		s_uchMsg[40] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[41] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((quat_data[2] + 1.0) /  (2.0) * 65535.0);
		s_uchMsg[42] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[43] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((quat_data[3] + 1.0) /  (2.0) * 65535.0);
		s_uchMsg[44] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[45] = (uint8_t)(ushTmp & 0x00ff);

		//elevonR
		ushTmp = (uint16_t)((elevonR_com + 120.0) /  (240.0) * 65535.0);
		s_uchMsg[46] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[47] = (uint8_t)(ushTmp & 0x00ff);

		//elevonL
		ushTmp = (uint16_t)((elevonL_com + 120.0) /  (240.0) * 65535.0);
		s_uchMsg[48] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		s_uchMsg[49] = (uint8_t)(ushTmp & 0x00ff);

		//parachute
		s_uchMsg[50] = (uint8_t)(parachute_com);

		if (auto&& pkt = the_twelite.network.use<NWK_SIMPLE>().prepare_tx_packet()) {
			// set tx packet behavior
			pkt << tx_addr(addr)  // 0..0xFF (LID 0:parent, FE:child w/ no id, FF:LID broad cast), 0x8XXXXXXX (long address)
				<< tx_retry(0x0) // set retry (0x3 send four times in total)
				// << tx_packet_delay(100,200,20); // send packet w/ delay (send first packet with randomized delay from 100 to 200ms, repeat every 20ms)
				<< tx_process_immediate();//即時送信
			// prepare packet payload
			pack_bytes(pkt.get_payload() // set payload data objects.
				, make_pair(s_uchMsg, SEND_LEN) // string should be paired with length explicitly.
			);
			// do transmit
			pkt.transmit();
		}
		cnt1_flag[counterid] = 0;
	}
}

void send_data_twe2mpu() {
	int counterid = 0;
	if(cnt2_flag[counterid] == 1){
		twe_t = millis()/1000.0;
		uint8_t twe_data[51];
		uint16_t ushTmp;

		twe_data[0] = 0xa5;
		twe_data[1] = 0x5a;

		//statustwe
		ushTmp = (uint8_t)(statustwe);
		twe_data[2] = ushTmp;

		//twe_t
		ushTmp = (uint16_t)(twe_t / 600.0 * 65535.0);
		twe_data[3] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[4] = (uint8_t)(ushTmp & 0x00ff);

		//acc_data
		ushTmp = (uint16_t)((acc_dummydata[0] + 16.0) / (32.0) * 65535.0);
		twe_data[5] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[6] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((acc_dummydata[1] + 16.0) / (32.0) * 65535.0);
		twe_data[7] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[8] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((acc_dummydata[2] + 16.0) / (32.0) * 65535.0);
		twe_data[9] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[10] = (uint8_t)(ushTmp & 0x00ff);

		//v_data
		ushTmp = (uint16_t)((v_dummydata[0] + 50.0) / (100.0) * 65535.0);
		twe_data[11] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[12] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((v_dummydata[1] + 50.0) / (100.0) * 65535.0);
		twe_data[13] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[14] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((v_dummydata[2] + 50.0) / (100.0) * 65535.0);
		twe_data[15] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[16] = (uint8_t)(ushTmp & 0x00ff);

		//xi eta hight_data
		ushTmp = (uint16_t)((xeh_dummydata[0] + 15.0) / (30.0) * 65535.0);
		twe_data[17] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[18] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((xeh_dummydata[1] + 15.0) / (30.0) * 65535.0);
		twe_data[19] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[20] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((xeh_dummydata[2] + 0.0) / (30.0) * 65535.0);
		twe_data[21] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[22] = (uint8_t)(ushTmp & 0x00ff);

		//gyro_data
		ushTmp = (uint16_t)((gyro_dummydata[0] + 3 * M_PI) / (6 * M_PI) * 65535.0);
		twe_data[23] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[24] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((gyro_dummydata[1] + 3 * M_PI) / (6 * M_PI) * 65535.0);
		twe_data[25] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[26] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((gyro_dummydata[2] + 3 *  M_PI) /  (6 * M_PI) * 65535.0);
		twe_data[27] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[28] = (uint8_t)(ushTmp & 0x00ff);

		//euler_data
		ushTmp = (uint16_t)((euler_dummydata[0] + M_PI) /  (2 * M_PI) * 65535.0);
		twe_data[29] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[30] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((euler_dummydata[1] + M_PI) /  (2 * M_PI) * 65535.0);
		twe_data[31] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[32] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((euler_dummydata[2] + M_PI) /  (2 * M_PI) * 65535.0);
		twe_data[33] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[34] = (uint8_t)(ushTmp & 0x00ff);

		//air_vel_data
		ushTmp = (uint16_t)((airvel_dummydata + 0.0) /  (255.0) * 65535.0);
		twe_data[35] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[36] = (uint8_t)(ushTmp & 0x00ff);

		//quat_data
		ushTmp = (uint16_t)((quat_dummydata[0] + 1.0) /  (2.0) * 65535.0);
		twe_data[37] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[38] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((quat_dummydata[1] + 1.0) /  (2.0) * 65535.0);
		twe_data[39] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[40] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((quat_dummydata[2] + 1.0) /  (2.0) * 65535.0);
		twe_data[41] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[42] = (uint8_t)(ushTmp & 0x00ff);

		ushTmp = (uint16_t)((quat_dummydata[3] + 1.0) /  (2.0) * 65535.0);
		twe_data[43] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[44] = (uint8_t)(ushTmp & 0x00ff);

		//elevonR
		ushTmp = (uint16_t)((elevonR_dummycom + 120.0) /  (240.0) * 65535.0);
		twe_data[45] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[46] = (uint8_t)(ushTmp & 0x00ff);

		//elevonL
		ushTmp = (uint16_t)((elevonL_dummycom + 120.0) /  (240.0) * 65535.0);
		twe_data[47] = (uint8_t)(ushTmp >> 8 & 0x00ff);
		twe_data[48] = (uint8_t)(ushTmp & 0x00ff);

		twe_data[49] = 0x0d;
		twe_data[50] = 0x0a;
		Serial1 << twe_data;

		cnt2_flag[counterid] = 0;
	}
}
