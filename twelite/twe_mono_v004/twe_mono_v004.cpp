// use twelite mwx c++ template library
#include <TWELITE>
#include <NWK_SIMPLE>

#define M_PI 3.1415927
/*** Config part */
// application ID
const uint32_t APP_ID = 0x000103E9;
// channel
const uint8_t CHANNEL = 13;
/*** function prototype */
void send_data_mono2pc();
void send_data_mono2twe(uint32_t addr);

/*** application defs */
// packet message
const int READ_LEN = 51;
const int READ_LEN_PC = 49;

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
	nwk	<< NWK_SIMPLE::logical_id(0x03); // set Logical ID. (0xFE means a child device with no ID)

	/*** BEGIN section */
	SerialParser.begin(PARSER::BINARY , 255); // Initialize the serial parser
	the_twelite.begin(); // start twelite!
	Timer0.begin(10); // 10Hz Timer

	/*** INIT message */
	// Serial << "start mono" << mwx::crlf;
}
/*** loop procedure (called every event) */
void loop() {
	send_data_mono2pc();
	send_data_mono2twe(0x04);
	if (Timer0.available()) {
		// send_data_mono2twe(0x04);
		// Serial << format(" acc_dummydata=%fs>", acc_dummydata[0]) << mwx::crlf;
		// Serial << format(" statuspc=%i>", statuspc) << mwx::crlf;
	}
}

void send_data_mono2pc(){
	// packet
	while (the_twelite.receiver.available()) {
		uint8_t r_uchMsg[READ_LEN];//tweから受け取ったバイナリデータ
		uint8_t pc_data[READ_LEN+4];
		auto&& rx = the_twelite.receiver.read();
		expand_bytes(rx.get_payload().begin(), rx.get_payload().end(), r_uchMsg);
		pc_data[0] = 0xa5;
		pc_data[1] = 0x5a;
		int i=0;
		for(i=0;i<READ_LEN;i++){
			pc_data[i+2] = r_uchMsg[i];
		}
		pc_data[READ_LEN+2] = 0x0d;
		pc_data[READ_LEN+3] = 0x0a;
		Serial << pc_data;
	}
}

void send_data_mono2twe(uint32_t addr) {
	while(Serial.available()){
		if ( SerialParser.parse(Serial.read())) {
			auto&& SerialParserbuf = SerialParser.get_buf();
			//Serial << format(" read len=%i>", sizeof(SerialParserbuf)) << mwx::crlf;
			uint8_t serial_data_frompc[READ_LEN_PC];
			for(int i = 0;i<READ_LEN_PC;i++)serial_data_frompc[i] = SerialParserbuf[i];
			if (auto&& pkt = the_twelite.network.use<NWK_SIMPLE>().prepare_tx_packet()) {
				pkt << tx_addr(addr)  // 0..0xFF (LID 0:parent, FE:child w/ no id, FF:LID broad cast), 0x8XXXXXXX (long address)
					<< tx_retry(0x0) // set retry (0x3 send four times in total)
					<< tx_process_immediate();//即時送信
				pack_bytes(pkt.get_payload() // set payload data objects.
					, make_pair(serial_data_frompc, READ_LEN_PC) // string should be paired with length explicitly.
				);
				pkt.transmit();
			}
		}
	}
}
