void my_setup(void) {
  pinMode(LED_pin, OUTPUT);
  pinMode(IR_p, INPUT);
  pinMode(SD_cd, OUTPUT);

  Serial.begin(115200);
  Serial1.begin(115200);
  SD.begin(SD_cd);
  //  sd.begin(SD_cd, SPISettings(20000000U, MSBFIRST, SPI_MODE0));

  servo_init();
  delay(1000);
  sensor_init();
  data_init();
  IntervalSet(dt);
}

void data_init(void) {
  for (int i = 0; i < Si1buf_size; i++)Serial1_buffer[i] = 0x00;
  Serial1_buffer_len = 0;
}

void IntervalSet(float interupt_time) {
  timer1 = TCFactory::alloc(TCOUNTER_MODE16, TCOUNTER_WAVEGEN_MFRQ );
  timer1->frequency(int(1.0 / interupt_time));
  timer1->setCallback(timer_1);
  timer1->interrupt(TCOUNTER_INT_MC0 , true);
  timer1->start();
}
