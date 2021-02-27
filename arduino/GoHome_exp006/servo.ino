void servo_init(void) {
  pwm_D2D3_init();
  servo_D2D3(0 , 0);
}

void pwm_D2D3_init() {
  pwm_D2D3 = TCFactory::alloc(TCOUNTER_ID_TCC1 , TCOUNTER_MODE16, TCOUNTER_WAVEGEN_MPWM);
  pwm_D2D3->frequency(50);
  pwm_D2D3->dutyCycle(TCOUNTER_MC0, TCOUNTER_DUTY_PER(50));
  pwm_D2D3->dutyCycle(TCOUNTER_MC1, TCOUNTER_DUTY_PER(50));
  pwm_D2D3->output(TCOUNTER_MC0, TCOUNTER_TCC1_WO0_PIN_D2, true);
  pwm_D2D3->output(TCOUNTER_MC1 , TCOUNTER_TCC1_WO0_PIN_D3, true);
  pwm_D2D3->start();
}

void servo_D2D3(float angleD2 , float angleD3) {//R:正で頭上げ側舵角　L:正で頭下げ側舵角
  angleD2 = angleD2 - 0.0;
  angleD3 = angleD3 - 13.0;
  if (angleD2 > s_degulim) {
    angleD2 = s_degulim;
  }
  if (angleD2 < s_degllim) {
    angleD2 = s_degllim;
  }
  float ajust_angle2D = angleD2 - s_degllim;
  float duty_angle2D = (ajust_angle2D / (s_degulim - s_degllim) * (pulse_max - pulse_min) + pulse_min) / 20000.0 * 100.0;
  pwm_D2D3->dutyCycle(TCOUNTER_MC0, TCOUNTER_DUTY_PER(duty_angle2D));

  if (angleD3 > s_degulim) {
    angleD3 = s_degulim;
  }
  if (angleD3 < s_degllim) {
    angleD3 = s_degllim;
  }
  float ajust_angleD3 = angleD3 - s_degllim;
  float duty_angleD3 = (ajust_angleD3 / (s_degulim - s_degllim) * (pulse_max - pulse_min) + pulse_min) / 20000.0 * 100.0;
  pwm_D2D3->dutyCycle(TCOUNTER_MC1, TCOUNTER_DUTY_PER(duty_angleD3));
}
