#include "init.h"

void setup() {
  my_setup();
}

void loop() {
  M_L();
  C_L();
  S_L();
  R_L();
}

void timer_1(TCounter* tcounter, TCOUNTER_INT flag) {//
  t = t + dt;
  cnt0 = cnt0 + 1;
  cnt1 = cnt1 + 1;
  cnt2 = cnt2 + 1;
  cnt3 = cnt3 + 1;
  cnt4 = cnt4 + 1;
  // Serial.println(t);
  if (cnt1 > (int)(cnt1_time / dt) - 1) { //led function
    cnt1_flag = !cnt1_flag;
    digitalWrite(LED_pin, cnt1_flag);
    cnt1 = 0;
  }
  if (cnt2 > (int)(cnt2_time / dt) - 1) { //送信する関数
    cnt2_flag = HIGH;
    cnt2 = 0;
  }
  if (cnt3 > (int)(cnt3_time / dt) - 1) { //制御する関数
    cnt3_flag = HIGH;
    cnt3 = 0;
  }
  if (cnt4 > (int)(cnt4_time / dt) - 1) { //計測する関数
    cnt4_flag = HIGH;
    cnt4 = 0;
  }
}

void S_L() { //送信する関数
  if (cnt2_flag) {
    int i = 0;
    byte s_uchMsg[52];
    word ushTmp;
    //start byte
    s_uchMsg[0] = 0xa5;
    s_uchMsg[1] = 0x5a;

    //data length
    s_uchMsg[2] = 0x80;
    s_uchMsg[3] = 0x2f;

    //statusmpu
    ushTmp = (byte)(statusmpu);
    s_uchMsg[4] = ushTmp;

    //mpu_t
    ushTmp = (word)(t / 600.0 * 65535.0);
    s_uchMsg[5] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[6] = (byte)(ushTmp & 0x00ff);

    //acc_data
    ushTmp = (word)((reg_data[0] + 16.0) / (32.0) * 65535.0);
    s_uchMsg[7] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[8] = (byte)(ushTmp & 0x00ff);

    ushTmp = (word)((reg_data[1] + 16.0) / (32.0) * 65535.0);
    s_uchMsg[9] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[10] = (byte)(ushTmp & 0x00ff);

    ushTmp = (word)((reg_data[2] + 16.0) / (32.0) * 65535.0);
    s_uchMsg[11] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[12] = (byte)(ushTmp & 0x00ff);

    //v_data
    ushTmp = (word)((reg_data[3] + 50.0) / (100.0) * 65535.0);
    s_uchMsg[13] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[14] = (byte)(ushTmp & 0x00ff);

    ushTmp = (word)((reg_data[4] + 50.0) / (100.0) * 65535.0);
    s_uchMsg[15] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[16] = (byte)(ushTmp & 0x00ff);

    ushTmp = (word)((reg_data[5] + 50.0) / (100.0) * 65535.0);
    s_uchMsg[17] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[18] = (byte)(ushTmp & 0x00ff);

    //xi eta hight_data
    ushTmp = (word)((reg_data[6] + 15.0) / (30.0) * 65535.0);
    s_uchMsg[19] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[20] = (byte)(ushTmp & 0x00ff);

    ushTmp = (word)((reg_data[7] + 15.0) / (30.0) * 65535.0);
    s_uchMsg[21] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[22] = (byte)(ushTmp & 0x00ff);

    ushTmp = (word)((reg_data[8] + 0.0) / (30.0) * 65535.0);
    s_uchMsg[23] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[24] = (byte)(ushTmp & 0x00ff);

    //gyro_data
    ushTmp = (word)((reg_data[9] + 3 * M_PI) / (6 * M_PI) * 65535.0);
    s_uchMsg[25] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[26] = (byte)(ushTmp & 0x00ff);

    ushTmp = (word)((reg_data[10] + 3 * M_PI) / (6 * M_PI) * 65535.0);
    s_uchMsg[27] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[28] = (byte)(ushTmp & 0x00ff);

    ushTmp = (word)((reg_data[11] + 3 *  M_PI) /  (6 * M_PI) * 65535.0);
    s_uchMsg[29] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[30] = (byte)(ushTmp & 0x00ff);

    //euler_data
    ushTmp = (word)((reg_data[12] + M_PI) /  (2 * M_PI) * 65535.0);
    s_uchMsg[31] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[32] = (byte)(ushTmp & 0x00ff);

    ushTmp = (word)((reg_data[13] + M_PI) /  (2 * M_PI) * 65535.0);
    s_uchMsg[33] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[34] = (byte)(ushTmp & 0x00ff);

    ushTmp = (word)((reg_data[14] + M_PI) /  (2 * M_PI) * 65535.0);
    s_uchMsg[35] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[36] = (byte)(ushTmp & 0x00ff);

    //air_vel_data
    ushTmp = (word)((reg_data[15] + 0.0) /  (255.0) * 65535.0);
    s_uchMsg[37] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[38] = (byte)(ushTmp & 0x00ff);

    //quat_data
    ushTmp = (word)((reg_data[16] + 1.0) /  (2.0) * 65535.0);
    s_uchMsg[39] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[40] = (byte)(ushTmp & 0x00ff);

    ushTmp = (word)((reg_data[17] + 1.0) /  (2.0) * 65535.0);
    s_uchMsg[41] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[42] = (byte)(ushTmp & 0x00ff);

    ushTmp = (word)((reg_data[18] + 1.0) /  (2.0) * 65535.0);
    s_uchMsg[43] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[44] = (byte)(ushTmp & 0x00ff);

    ushTmp = (word)((reg_data[19] + 1.0) /  (2.0) * 65535.0);
    s_uchMsg[45] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[46] = (byte)(ushTmp & 0x00ff);

    //elevonR
    ushTmp = (word)((reg_data[20] + 120.0) /  (240.0) * 65535.0);
    s_uchMsg[47] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[48] = (byte)(ushTmp & 0x00ff);

    //elevonL
    ushTmp = (word)((reg_data[21] + 120.0) /  (240.0) * 65535.0);
    s_uchMsg[49] = (byte)(ushTmp >> 8 & 0x00ff);
    s_uchMsg[50] = (byte)(ushTmp & 0x00ff);

    s_uchMsg[51] = 0x00;
    for (i = 4; i < (DataLength + 4); i++) {
      s_uchMsg[51] = s_uchMsg[51] ^ s_uchMsg[i];
    }

    Serial1.write(s_uchMsg, sizeof(s_uchMsg));

    String dataString = "";
    dataString += String(t);
    dataString += ",";
    dataString += String(statusmpu);
    dataString += ",";
    dataString += String(acc_data[0]);
    dataString += ",";
    dataString += String(acc_data[1]);
    dataString += ",";
    dataString += String(acc_data[2]);
    dataString += ",";
    dataString += String(gyro_data[0]);
    dataString += ",";
    dataString += String(gyro_data[1]);
    dataString += ",";
    dataString += String(gyro_data[2]);
    dataString += ",";
    dataString += String(euler_data[0]);
    dataString += ",";
    dataString += String(euler_data[1]);
    dataString += ",";
    dataString += String(euler_data[2]);
    dataString += ",";
    dataString += String(airvel_data);
    dataString += ",";
    dataString += String(adc_data);
    dataString += ",";
    dataString += String(apres_data);
    dataString += ",";
    dataString += String(temp_data);
    dataString += ",";
    dataString += String(elevonR_com);
    dataString += ",";
    dataString += String(elevonL_com);
    //dataString += ",";

    if (statusmpu == 5 || statusmpu == 6 || statusmpu == 7 || statusmpu == 8 || statusmpu == 9 || statusmpu == 10 || statusmpu == 14) {
      if (sd_cnt > SD_SAVECYCLE || f_sdact == 0) {
        if (f_sdact == 1) {
          dataFile.close();
          dataFile.println(dataString);
        }
        dataFile = SD.open("datalog.txt", FILE_WRITE);
        if (dataFile) {
          f_sdact = 1;
        } else {
          f_sdact = 0;
        }
        sd_cnt = 0;
      } else {
        dataFile.println(dataString);
        sd_cnt = sd_cnt + 1;
      }

    } else {
      if (f_sdact == 1) {
        dataFile.close();
        sd_cnt = 0;
        f_sdact = 0;
      }
    }

    cnt2_flag = LOW;
  }
}

void C_L() { //制御関数
  if (cnt3_flag) {
    fail_diagnosis();
    control_state();

    //    elevonL_rotation(elevonL_dummycom);
    //    elevonR_rotation(elevonR_dummycom);
    cnt3_flag = LOW;
  }
}

void M_L() { //計測する関数

  if (cnt4_flag) {
    pretime_u = time_u;
    time_u = micros();
    get_ir();
    get_altitude();
    get_dpres();
    get_apres();
    get_temp();
    get_airvel();
    get_calib();
    get_attitude();

    //    Serial.println(ph_data);

    reg_data[0] = acc_data[0];
    reg_data[1] = acc_data[1];
    reg_data[2] = acc_data[2];

    reg_data[3] = v_data[0];
    reg_data[4] = v_data[1];
    reg_data[5] = v_data[2];

    reg_data[6] = xeh_data[0];
    reg_data[7] = xeh_data[1];
    reg_data[8] = xeh_data[2];

    reg_data[9] = gyro_data[0];
    reg_data[10] = gyro_data[1];
    reg_data[11] = gyro_data[2];

    reg_data[12] = euler_data[0];
    reg_data[13] = euler_data[1];
    reg_data[14] = euler_data[2];

    reg_data[15] = airvel_data;

    reg_data[16] = quat_data[0];
    reg_data[17] = quat_data[1];
    reg_data[18] = quat_data[2];
    reg_data[19] = quat_data[3];

    reg_data[20] = elevonR_com;
    reg_data[21] = elevonL_com;

    cnt4_flag = LOW;
  }
}

void R_L() { //受信する関数
  //noInterrupts();
  float get_data[22];

  //シリアル情報取得
  byte Serial1_buffer_tmp[Si1buf_size];
  int tmp_len = 0;
  while ( Serial1.available()) {
    if (tmp_len >= Si1buf_size)break;
    Serial1_buffer_tmp[tmp_len] = Serial1.read();
    tmp_len = tmp_len + 1;
  }

  //バッファに貯める
  if (tmp_len > (Si1buf_size - Serial1_buffer_len)) {
    //バッファサイズからはみ出るとき、はみ出た分削除の後、取得分追加
    //Serial.println("バッファサイズからはみ出るとき、はみ出た分削除の後、取得分追加");
    int over_len = tmp_len - (Si1buf_size - Serial1_buffer_len);
    byte swp_sil1_buf[Si1buf_size];
    for (int i = 0; i < Si1buf_size; i++)swp_sil1_buf[i] = Serial1_buffer[i];
    for (int i = 0; i < Si1buf_size - over_len; i++)Serial1_buffer[i] = swp_sil1_buf[i + over_len];
    Serial1_buffer_len = Serial1_buffer_len - over_len;
    for (int i = 0; i < tmp_len; i++)Serial1_buffer[Serial1_buffer_len + i] = Serial1_buffer_tmp[i];
    Serial1_buffer_len = Serial1_buffer_len + tmp_len;
  } else {
    //バッファサイズからはみ出ないとき、取得分追加
    //Serial.println("バッファサイズからはみ出ないとき、取得分追加");
    for (int i = 0; i < tmp_len; i++)Serial1_buffer[Serial1_buffer_len + i] = Serial1_buffer_tmp[i];
    Serial1_buffer_len = Serial1_buffer_len + tmp_len;
  }
  //データ読み出し
  for (int i = 0; i < Serial1_buffer_len - Si1readbyte_len; i++) {
    int buf_len = 0;

    if ( Serial1_buffer[i + buf_len] == 0xa5 ) {
      buf_len = buf_len + 1;
      if ( Serial1_buffer[i + buf_len] == 0x5a ) {
        buf_len = buf_len + 1;
        int n = 0;
        word ushTmp;
        byte low;
        byte high;
        //statustwe
        statustwe = (int)Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;

        //twe_t
        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        twe_t = ((double)ushTmp / 65535.0 * 600.0);

        //acc_data
        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[0] = ((double)ushTmp / 65535.0 * 32.0 - 16.0);

        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[1] = ((double)ushTmp / 65535.0 * 32.0 - 16.0);

        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[2] = ((double)ushTmp / 65535.0 * 32.0 - 16.0);

        //v_data
        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[3] = ((double)ushTmp / 65535.0 * 100.0 - 50.0);

        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[4] = ((double)ushTmp / 65535.0 * 100.0 - 50.0);

        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[5] = ((double)ushTmp / 65535.0 * 100.0 - 50.0);

        //xi eta hight_data
        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[6] = ((double)ushTmp / 65535.0 * 30.0 - 15.0);

        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[7] = ((double)ushTmp / 65535.0 * 30.0 - 15.0);

        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[8] = ((double)ushTmp / 65535.0 * 30.0 - 15.0);

        //gyro_data
        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[9] = ((double)ushTmp / 65535.0 * 6.0 * M_PI - 3.0 * M_PI);

        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[10] = ((double)ushTmp / 65535.0 * 6.0 * M_PI - 3.0 * M_PI);

        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[11] = ((double)ushTmp / 65535.0 * 6.0 * M_PI - 3.0 * M_PI);

        //euler_data
        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[12] = ((double)ushTmp / 65535.0 * 2.0 * M_PI - M_PI);

        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[13] = ((double)ushTmp / 65535.0 * 2.0 * M_PI - M_PI);

        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[14] = ((double)ushTmp / 65535.0 * 2.0 * M_PI - M_PI);

        //air_vel_data
        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[15] = ((double)ushTmp / 65535.0 * 255.0 - 0.0);

        //quat_data
        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[16] = ((double)ushTmp / 65535.0 * 2.0 - 1.0);

        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[17] = ((double)ushTmp / 65535.0 * 2.0 - 1.0);

        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[18] = ((double)ushTmp / 65535.0 * 2.0 - 1.0);

        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[19] = ((double)ushTmp / 65535.0 * 2.0 - 1.0);

        //elevonR
        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[20] = ((double)ushTmp / 65535.0 * 120.0 - 60.0);

        //elevonL
        low = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        high = Serial1_buffer[i + buf_len];
        buf_len = buf_len + 1;
        ushTmp = (word)(((low << 8) & 0xff00) | (high & 0x00ff));
        get_data[21] = ((double)ushTmp / 65535.0 * 120.0 - 60.0);

        if ( Serial1_buffer[i + buf_len] == 0x0d ) {
          buf_len = buf_len + 1;
          if ( Serial1_buffer[i + buf_len] == 0x0a ) {
            buf_len = buf_len + 1;
            //パケット取得成功のため、取得分より前データ削除
            int over_len = i + buf_len;
            byte swp_sil1_buf[Si1buf_size];
            for (int i = 0; i < Si1buf_size; i++)swp_sil1_buf[i] = Serial1_buffer[i];
            for (int i = 0; i < Si1buf_size - over_len; i++)Serial1_buffer[i] = swp_sil1_buf[i + over_len];
            Serial1_buffer_len = Serial1_buffer_len - over_len;

            acc_dummydata[0] = get_data[0];
            acc_dummydata[1] = get_data[1];
            acc_dummydata[2] = get_data[2];

            v_dummydata[0] = get_data[3];
            v_dummydata[1] = get_data[4];
            v_dummydata[2] = get_data[5];

            xeh_dummydata[0] = get_data[6];
            xeh_dummydata[1] = get_data[7];
            xeh_dummydata[2] = get_data[8];

            gyro_dummydata[0] = get_data[9];
            gyro_dummydata[1] = get_data[10];
            gyro_dummydata[2] = get_data[11];

            euler_dummydata[0] = get_data[12];
            euler_dummydata[1] = get_data[13];
            euler_dummydata[2] = get_data[14];

            airvel_dummydata = get_data[15];

            quat_dummydata[0] = get_data[16];
            quat_dummydata[1] = get_data[17];
            quat_dummydata[2] = get_data[18];
            quat_dummydata[3] = get_data[19];

            elevonR_dummycom = get_data[20];
            elevonL_dummycom = get_data[21];

          }
        }
      }
    }
  }
  emc_cnt = 0;
  // ヘッダの確認

}
