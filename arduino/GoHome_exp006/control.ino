void control_state(void) {
  if (statusmpu >= 0 && statusmpu <= 3) { /* 初期状態　処理 */
    control_init();
  } else if (statusmpu >= 4 && statusmpu <= 10) { /* Launch mode　処理 */
    control_launch();
  } else if (statusmpu >= 11 && statusmpu <= 15) { /* Develop mode　処理 */
    control_develop();
  } else { /* FSA mode　処理 */
    control_fail();//FSA実施
  }
  control_law();
}

void control_init(void) {
  switch (statusmpu) {
    case 0:
      /* 初期状態 */
      if (statusmpu == 0) {
        statusmpu = 1;
      }
      break;
    case 1:
      /* 通信確立待機時間 */
      f_waitok = 1;
      if (f_waitok == 1) {
        statusmpu = 2;
      }
      break;
    case 2:
      /* mpu初期化処理 */
      if (f_sensok == 1) {
        statusmpu = 3;
        diagnosis_act = 1;//故障検知開始
      }
      break;
    case 3:
      /* 準備完了待機 */
      if (statustwe == 4) { //Launch modeへの遷移指示
        statusmpu = 4;
      }
      else if (statustwe == 11) { //サーボ・センサーの作動をチェックするモード
        statusmpu = 11;
      }
      else if (statustwe == 12) { //カメラの動作をチェックするモード(カメラON)
        statusmpu = 12;
      }
      else if (statustwe == 13) { //カメラの動作をチェックするモード(カメラOFF)
        statusmpu = 13;
      }
      else if (statustwe == 14) { //制御動作確認モード
        statusmpu = 14;
      }
      else if (statustwe == 15) { //ダミーセンサ情報に基づいた制御動作確認モード
        statusmpu = 15;
      } else {
        //待機
      }
      break;
    default:
      /* なにもしない */
      break;
  }
}

void control_launch(void) {
  switch (statusmpu) {
    case 4:
      /* カメラスタート&変数初期化 */
      f_checkok = 0;//発射前チェック完了判定
      f_launch = 0;//発射判定
      f_parareq = 0;//パラシュート展開要求
      f_land = 0;//着地判定
      controll_t = 0.0;//制御時間初期化
      controll_t_offset = 0.0;//制御時間初期化
      if ( statustwe == 5) {
        statusmpu = 5;
      }
      break;
    case 5:
      /* チェック */
      check_seq();
      if (f_checkok == 1) {
        statusmpu = 6;
      }
      break;
    case 6:
      /* 発射待機 */
      jud_launch();
      if (f_launch == 1) {
        statusmpu = 7;
        controll_t_offset = millis() / 1000.0;
      }
      break;
    case 7:
      /* 制御中 */
      controll_t = millis() / 1000.0 - controll_t_offset;
      jud_parareq();
      if (f_parareq == 1) {
        statusmpu = 8;
      }
      break;
    case 8:
      /* パラシュート展開 */
      jud_land();
      if (f_land == 1) {
        statusmpu = 9;
      }
      break;
    case 9:
      /* カメラ終了指示 */
      if ( statustwe != 9) {
        statusmpu = 10;
      }
      break;
    case 10:
      /* 発射終了待機 */
      if (statustwe == 11) { //サーボ・センサーの作動をチェックするモード
        statusmpu = 11;
      }
      else if (statustwe == 12) { //カメラの動作をチェックするモード(カメラON)
        statusmpu = 12;
      }
      else if (statustwe == 13) { //カメラの動作をチェックするモード(カメラOFF)
        statusmpu = 13;
      }
      else if (statustwe == 14) { //制御動作確認モード
        statusmpu = 14;
      }
      else if (statustwe == 15) { //ダミーセンサ情報に基づいた制御動作確認モード
        statusmpu = 15;
      } else {
        //待機
      }
      break;
    default:
      /* なにもしない */
      break;
  }
}

void control_develop(void) {
  /* 状態遷移判断 */
  switch (statusmpu) {
    case 11:
      /* サーボ・センサー確認モード */
      if (statustwe == 4) { //Launch modeへの遷移指示
        statusmpu = 4;
      }
      else if (statustwe == 11) { //サーボ・センサーの作動をチェックするモード
        statusmpu = 11;
      }
      else if (statustwe == 12) { //カメラの動作をチェックするモード(カメラON)
        statusmpu = 12;
      }
      else if (statustwe == 13) { //カメラの動作をチェックするモード(カメラOFF)
        statusmpu = 13;
      }
      else if (statustwe == 14) { //制御動作確認モード
        statusmpu = 14;
      }
      else if (statustwe == 15) { //ダミーセンサ情報に基づいた制御動作確認モード
        statusmpu = 15;
      } else {
        //待機
      }
      break;
    case 12:
      /* カメラ動作確認モード ON */
      if (statustwe == 4) { //Launch modeへの遷移指示
        statusmpu = 4;
      }
      else if (statustwe == 11) { //サーボ・センサーの作動をチェックするモード
        statusmpu = 11;
      }
      else if (statustwe == 12) { //カメラの動作をチェックするモード(カメラON)
        statusmpu = 12;
      }
      else if (statustwe == 13) { //カメラの動作をチェックするモード(カメラOFF)
        statusmpu = 13;
      }
      else if (statustwe == 14) { //制御動作確認モード
        statusmpu = 14;
      }
      else if (statustwe == 15) { //ダミーセンサ情報に基づいた制御動作確認モード
        statusmpu = 15;
      } else {
        //待機
      }
      break;
    case 13:
      /* カメラ動作確認モード OFF */
      if (statustwe == 4) { //Launch modeへの遷移指示
        statusmpu = 4;
      }
      else if (statustwe == 11) { //サーボ・センサーの作動をチェックするモード
        statusmpu = 11;
      }
      else if (statustwe == 12) { //カメラの動作をチェックするモード(カメラON)
        statusmpu = 12;
      }
      else if (statustwe == 13) { //カメラの動作をチェックするモード(カメラOFF)
        statusmpu = 13;
      }
      else if (statustwe == 14) { //制御動作確認モード
        statusmpu = 14;
      }
      else if (statustwe == 15) { //ダミーセンサ情報に基づいた制御動作確認モード
        statusmpu = 15;
      } else {
        //待機
      }
      break;
    case 14:
      /* 制御の動作確認モード */
      if (statustwe == 4) { //Launch modeへの遷移指示
        statusmpu = 4;
      }
      else if (statustwe == 11) { //サーボ・センサーの作動をチェックするモード
        statusmpu = 11;
      }
      else if (statustwe == 12) { //カメラの動作をチェックするモード(カメラON)
        statusmpu = 12;
      }
      else if (statustwe == 13) { //カメラの動作をチェックするモード(カメラOFF)
        statusmpu = 13;
      }
      else if (statustwe == 14) { //制御動作確認モード
        statusmpu = 14;
      }
      else if (statustwe == 15) { //ダミーセンサ情報に基づいた制御動作確認モード
        statusmpu = 15;
      } else {
        //待機
      }
      break;
    case 15:
      if (statustwe == 4) { //Launch modeへの遷移指示
        statusmpu = 4;
      }
      else if (statustwe == 11) { //サーボ・センサーの作動をチェックするモード
        statusmpu = 11;
      }
      else if (statustwe == 12) { //カメラの動作をチェックするモード(カメラON)
        statusmpu = 12;
      }
      else if (statustwe == 13) { //カメラの動作をチェックするモード(カメラOFF)
        statusmpu = 13;
      }
      else if (statustwe == 14) { //制御動作確認モード
        statusmpu = 14;
      }
      else if (statustwe == 15) { //ダミーセンサ情報に基づいた制御動作確認モード
        statusmpu = 15;
      } else {
        //待機
      }
      break;
    default:

      break;
  }
}

void fail_diagnosis(void) {
  if (diagnosis_act == 1) {
    if (statusmpu != 200 && f_fsa == 1) {
      statusmpu = 200;
    }
  }
  if (statusmpu > 15) {
    f_fsa = 1;
  }
}

void control_fail(void) {
  switch (statusmpu) {
    case 200:
      /* FSA実施中 */
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

void control_com(void) {
  float Grp = 30.0;
  float Grd = 3.0;
  float roll_ref = 00.0 * M_PI / 180.0;
  float groll_ref = 0.0;
  float roll_err = rpy_data[0] - roll_ref;
  float groll_err = gyro_data[0] - groll_ref;

  float Gpp = 0.0;
  float Gpd = 0.0;
  float pitch_ref = 0.0;
  float gpitch_ref = 0.0;
  float pitch_err = rpy_data[1] - pitch_ref;
  float gpitch_err = gyro_data[1] - gpitch_ref;

  float air_coeff = 1.0 / (dpres_data + 1.0);

  //R:正で頭上げ側舵角　L:正で頭下げ側舵角
  elevonR_com = air_coeff * ( Grp * roll_err + Grd * groll_err + Gpp * pitch_err + Gpd * gpitch_err) * 180.0 / M_PI;
  elevonL_com = air_coeff * ( Grp * roll_err + Grd * groll_err - Gpp * pitch_err - Gpd * gpitch_err) * 180.0 / M_PI;
}

void jud_launch(void) {
  if (ph_data < if_th) {//電圧が低いと遮蔽
    f_launch = 0;
  } else {//電圧が高いと開放
    f_launch = 1;
  }
}

void jud_parareq(void) {
  if (f_parareq == 0) {
    if (wait_flg == 0) {
      wait_timer = millis() / 1000.0;
      wait_flg = 1;
    }
    if (millis() / 1000.0 - wait_timer > paratime && wait_flg == 1) {
      wait_flg = 0;
      f_parareq = 1;
    }
  }
}

void jud_land(void) {
  if (f_land == 0) {
    if (wait_flg == 0) {
      wait_timer = millis() / 1000.0;
      wait_flg = 1;
    }
    if (millis() / 1000.0 - wait_timer > landtime && wait_flg == 1) {
      wait_flg = 0;
      f_land = 1;
    }
  }
}

void check_seq(void) {
  if (wait_flg == 0 && check_mode != 6) {
    wait_timer = millis() / 1000.0;
    check_mode = 0;
    wait_flg = 1;
  }

  if (millis() / 1000.0 - wait_timer > 1.0 && check_mode == 0) {
    check_mode = 1;
  }
  if (millis() / 1000.0 - wait_timer > 2.0 && check_mode == 1) {
    check_mode = 2;
  }
  if (millis() / 1000.0 - wait_timer > 3.0 && check_mode == 2) {
    check_mode = 3;
  }
  if (millis() / 1000.0 - wait_timer > 4.0 && check_mode == 3) {
    check_mode = 4;
  }
  if (millis() / 1000.0 - wait_timer > 5.0 && check_mode == 4) {
    check_mode = 5;
  }
  if (millis() / 1000.0 - wait_timer > 6.0 && check_mode == 5) {
    check_mode = 6;
  }
  switch (check_mode) {
    case 0:
      //elevonR_com=0,elevonL_com=0 1000sec
      elevonR_com = 0.0;
      elevonL_com = 0.0;
      break;
    case 1:
      //elevonR_com=60,elevonL_com=-60 1000sec
      elevonR_com =  SV_INITANG;
      elevonL_com =  SV_INITANG;
      break;
    case 2:
      //elevonR_com=-60,elevonL_com=60 1000sec
      elevonR_com = -SV_INITANG;
      elevonL_com = -SV_INITANG;
      break;
    case 3:
      //elevonR_com=60,elevonL_com=60 1000sec
      elevonR_com = -SV_INITANG;
      elevonL_com = SV_INITANG;
      break;
    case 4:
      //elevonR_com=-60,elevonL_com=-60 1000sec
      elevonR_com =  SV_INITANG * 2.0;
      elevonL_com = -SV_INITANG * 2.0;
      break;
    case 5:
      //elevonR_com=0,elevonL_com=0 1000sec
      elevonR_com = 0.0;
      elevonL_com = 0.0;
      break;
    case 6:
      attitude_init();
      f_checkok = 1;
      wait_flg = 0;
      check_mode = 0;
      break;
    default:
      break;
  }
}


void control_law(void) {

  if (statusmpu == 4) {
    elevonR_com = 0.0;
    elevonL_com = 0.0;
    servo_D2D3(elevonR_com , elevonL_com);
  } else if (statusmpu == 5) {
    servo_D2D3(elevonR_com , elevonL_com);
  } else if (statusmpu == 6) {
    elevonR_com = 0.0;
    elevonL_com = 0.0;
    servo_D2D3(elevonR_com , elevonL_com);
  } else if (statusmpu == 7) {
    if (controll_t < 0.3) {
      elevonR_com = 0.0;
      elevonL_com = 0.0;
    } else if (controll_t > 0.3 && controll_t < 1.0) {
      control_com();
    } else {
      elevonR_com = 0.0;
      elevonL_com = 0.0;
    }
    //control_com();
    servo_D2D3(elevonR_com , elevonL_com);
  } else if (statusmpu == 8) {
    //    elevonR_com = 0.0;
    //    elevonL_com = 0.0;
    //control_com();
    //    servo_D2D3(elevonR_com , elevonL_com);
  } else if (statusmpu == 11) {
    attitude_init();
    servo_D2D3(elevonR_dummycom , elevonL_dummycom);
  } else if (statusmpu == 14) {
    control_com();
    servo_D2D3(elevonR_com , elevonL_com);
  } else if (statusmpu == 15) {
    control_com();
    servo_D2D3(elevonR_dummycom , elevonL_dummycom);
  }
}
