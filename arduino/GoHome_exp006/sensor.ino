void sensor_init(void) {

  Wire.begin();
  Wire.setClock(3400000); //at least faster than 1000000
  bno.begin();

  delay(500);

  ADC_init();
  APS_init();
  BNO055_init();
  f_sensok = 1;
}

void BNO055_init(void) {
  int i = 0;
  //  get_calib();
  while (1) {
    get_calib();
    if (statuscalib != 0 ) {
      break;
    } else {
      i = i + 1;
      delay(100);
      if (i > 1000) {
        f_fsa = 1;
        break;
      }
    }
  }

}

void APS_init(void) {
  pressureSensor.begin(); // Begin links an I2C port and I2C address to the sensor, sets an I2C speed, begins I2C on the main board, and then sets default settings
  int i = 0;
  int ita_num = 1000;
  altitude_offset_data = 0.0;
  for (i = 0; i < ita_num; i++) {
    get_apres();
    get_temp();
    altitude_offset_data = altitude_offset_data + (pow((M_P0 * 100.0 / apres_data), (1.0 / 5.257)) - 1.0) * (temp_data + M_T) / 0.0065;
  }
  altitude_offset_data = altitude_offset_data / (float)ita_num;
}

void ADC_init(void) {
  Wire.beginTransmission(MCP3425_address);
  Wire.write(MCP3425_confReg);
  Wire.endTransmission();
  delayMicroseconds(50);
  Wire.requestFrom(MCP3425_address, 2);
  adc_data = (float)((Wire.read() << 8 ) + Wire.read());
  int i = 0;
  int ita_num = 1000;
  dpres_offset_data = 0.0;
  for (i = 0; i < ita_num; i++) {
    float buf = (float)get_ADC() / 4096.0 * 3.3 / 8.0;
    if (buf > dpres_offset_data) {
      dpres_offset_data = buf;
    }
    //dpres_offset_data = dpres_offset_data + (float)get_ADC() / 4096.0 * 3.3 / 8.0;
  }
  //dpres_offset_data = dpres_offset_data / (float)ita_num;
}

void get_ir(void) {
  ph_data = (float)analogRead(IR_p) / 4096.0;
  //  Serial.println(ph_data);
}

void get_dpres(void) {
  float adc_data = (float)get_ADC();
  float tmp = (adc_data / 4096.0 * 3.3 / 8.0 - dpres_offset_data) / DPRESS_COEF * 103421.0;
  //  float ave_databuff[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  //  float sum_data = 0.0;
  //  for (int i = 0; i < 9; i++) {
  //    ave_databuff[i] = ave_data[i];
  //  }
  //  for (int i = 0; i < 9; i++) {
  //    ave_data[i + 1] = ave_databuff[i];
  //  }
  //  ave_data[0] = tmp;
  //  for (int i = 0; i < 10; i++) {
  //    sum_data = sum_data + ave_data[i];
  //  }
  //  dpres_data = sum_data / 10.0;
  dpres_data = (cnt4_time * tmp + lpf_cdp * dpres_data) / (cnt4_time + lpf_cdp);
  //  Serial.print(tmp);
  //  Serial.print(',');
  //  Serial.println(dpres_data);
  //  Serial.println(adc_data);
  if (dpres_data < 0) {
    dpres_data = 0.0;
  }

}

float get_ADC() {
  Wire.requestFrom(MCP3425_address, 2);

  if (Wire.available() < 2) {
  } else {
    adc_data = (float)((Wire.read() << 8 ) + Wire.read());
  }

  //  Serial.println(adc_data);
  return adc_data;
}

void get_apres(void) {
  apres_data = (float)pressureSensor.getPressure_hPa() * 100.0;
}

void get_altitude(void) {
  altitude_data = (pow((M_P0 * 100.0 / apres_data), (1.0 / 5.257)) - 1.0) * (temp_data + M_T) / 0.0065 - altitude_offset_data;

}

void get_temp(void) {
  temp_data = pressureSensor.getTemperature_degC();
}

void get_airvel(void) {
  float rho = apres_data * M_R / ( temp_data + M_T );
  //  airvel_data = sqrt(2*dpres_data/rho);
  //  airvel_data = lpf_cdp * lpf_data_f[6] + (1.0 - lpf_cdp) * sqrt(2*dpres_data/rho);
  //float cnt4_time_dt = (float)(time_u - pretime_u) / 1000.0 / 1000.0;
  //airvel_data = (cnt4_time_dt * sqrt(2 * dpres_data / rho) + lpf_cdp * airvel_data) / (cnt4_time_dt + lpf_cdp);
  airvel_data = sqrt(2 * dpres_data / rho);
  //  Serial.println(airvel_data);
}



void get_attitude(void) {
  sensors_event_t angVelocityData , accelerometerData;
  bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
  gyro_data[0] = (float)angVelocityData.gyro.x / 180.0 * M_PI;
  gyro_data[1] = -(float)angVelocityData.gyro.y / 180.0 * M_PI;
  gyro_data[2] = -(float)angVelocityData.gyro.z / 180.0 * M_PI;

  //bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_LINEARACCEL);
  bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
  acc_data[0] = (float)accelerometerData.acceleration.x;
  acc_data[1] = -(float)accelerometerData.acceleration.y;
  acc_data[2] = -(float)accelerometerData.acceleration.z;

  imu::Quaternion quat = bno.getQuat();
  quat_data[0] = (float)quat.w();
  quat_data[1] = -(float)quat.x();
  quat_data[2] = (float)quat.y();
  quat_data[3] = -(float)quat.z();

  calc_dgyro();
  calc_attitude();
}

void get_calib(void) {
  /* Display calibration status for each sensor. */
  uint8_t gyro, accel, mag = 0;
  bno.getCalibration(&statuscalib, &gyro, &accel, &mag);
}
