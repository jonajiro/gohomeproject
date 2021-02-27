void attitude_init(void) {
  init_data[0] = init_euler_data[0];
  init_data[1] = init_euler_data[1];
  init_data[2] = init_euler_data[2];
}

void calc_attitude(void) {
  float cnt4_time_dt = (float)(time_u - pretime_u) / 1000.0 / 1000.0;

  //eulerオフセット分 座標変換
  calc_quat2rot();

  gen_rot(0.0, 0.13, 0.0);
  calc_transpose(arr_data);
  calc_mult(arr_data, rot_data);
  insert_rot(arr_data);

  gen_rot(-M_PI, 0.0, 0.0);
  calc_transpose(arr_data);
  calc_mult(arr_data, rot_data);
  insert_rot(arr_data);

  calc_quat2initeuler();

  gen_rot(0.0, 0.0, init_data[2]);
  //calc_transpose(arr_data);
  calc_mult(rot_data, arr_data);
  insert_rot(arr_data);

  //accオフセット分 座標変換
  gen_rot(0.0, 0.13, 0.0);
  calc_mult2(arr_data, acc_data);

  gen_rot(-M_PI, 0.0, 0.0);
  calc_mult2(arr_data, arr_data2);
  insert_acc(arr_data2);

  //gyroオフセット分 座標変換
  gen_rot(0.0, 0.13, 0.0);
  calc_mult2(arr_data, gyro_data);

  gen_rot(-M_PI, 0.0, 0.0);
  calc_mult2(arr_data, arr_data2);
  insert_gyro(arr_data2);

  //姿勢角算出
  calc_quat2euler();
  calc_quat2zxy();
  calc_rpy();

  //位置算出
  calc_pos();

  //  Serial.print(v_data[0]);
  //  Serial.print(',');
  //  Serial.print(xeh_data[0]);
  //  Serial.print(',');
  //  Serial.println(v_data[0] * 1000.0);
}

void calc_dgyro(void) {
  dgyro_data[0] = (gyro_data[0] - pgyro_data[0]) / cnt4_time;
  dgyro_data[1] = (gyro_data[1] - pgyro_data[1]) / cnt4_time;
  dgyro_data[2] = (gyro_data[2] - pgyro_data[2]) / cnt4_time;
  pgyro_data[0] = gyro_data[0];
  pgyro_data[1] = gyro_data[1];
  pgyro_data[2] = gyro_data[2];
}

void calc_pos(void) {
  calc_dgyro();

  float ptd_s[3] = {0.0, 0.0, 0.0};
  float rot_hosei[3] = {0.0, 0.0, 0.0};
  calc_mult2(rot_data, acc_data);
  ptd_s[0] = arr_data2[0];
  ptd_s[1] = arr_data2[1];
  ptd_s[2] = arr_data2[2];

  calc_mult2(rot_data, sens_offset_pos);
  calc_cross2(dgyro_data, arr_data2);
  rot_hosei[0] = arr_data2[0];
  rot_hosei[1] = arr_data2[1];
  rot_hosei[2] = arr_data2[2];

  ptd_v[0] = ptd_s[0] - rot_hosei[0];
  ptd_v[1] = ptd_s[1] - rot_hosei[1];
  ptd_v[2] = ptd_s[2] - rot_hosei[2];

  //  v_data[0] = pv_data[0] + cnt4_time * ptd_v[0];
  v_data[0] = pv_data[0] + cnt4_time * (ptd_v[0] + pacc_data[0]) / 2.0;
  v_data[1] = pv_data[1] + cnt4_time * (ptd_v[1] + pacc_data[1]) / 2.0;
  v_data[2] = pv_data[2] + cnt4_time * (ptd_v[2] + pacc_data[2]) / 2.0;

  //  if (v_data[0] > 0.001) {
  //    v_data[0] = v_data[0] - 0.001;
  //  } else if (v_data[0] < -0.001) {
  //    v_data[0] = v_data[0] + 0.001;
  //  }

  xeh_data[0] = xeh_data[0] + cnt4_time * (v_data[0] + pv_data[0]) / 2.0;
  xeh_data[1] = xeh_data[1] + cnt4_time * (v_data[1] + pv_data[1]) / 2.0;
  xeh_data[2] = xeh_data[2] + cnt4_time * (v_data[2] + pv_data[2]) / 2.0;

  pv_data[0] = v_data[0];
  pv_data[1] = v_data[1];
  pv_data[2] = v_data[2];

  pacc_data[0] = ptd_v[0];
  pacc_data[1] = ptd_v[1];
  pacc_data[2] = ptd_v[2];
}

void insert_rot(float a[3][3]) {//3x3 代入
  rot_data[0][0] = a[0][0];
  rot_data[0][1] = a[0][1];
  rot_data[0][2] = a[0][2];

  rot_data[1][0] = a[1][0];
  rot_data[1][1] = a[1][1];
  rot_data[1][2] = a[1][2];

  rot_data[2][0] = a[2][0];
  rot_data[2][1] = a[2][1];
  rot_data[2][2] = a[2][2];
}

void insert_gyro(float a[3]) {//3x1 代入
  gyro_data[0] = a[0];
  gyro_data[1] = a[1];
  gyro_data[2] = a[2];
}

void insert_acc(float a[3]) {//3x1 代入
  acc_data[0] = a[0];
  acc_data[1] = a[1];
  acc_data[2] = a[2];
}

void calc_transpose(float a[3][3]) {//3x3 転置
  arr_data[0][0] = a[0][0];
  arr_data[0][1] = a[1][0];
  arr_data[0][2] = a[2][0];

  arr_data[1][0] = a[0][1];
  arr_data[1][1] = a[1][1];
  arr_data[1][2] = a[2][1];

  arr_data[2][0] = a[0][2];
  arr_data[2][1] = a[1][2];
  arr_data[2][2] = a[2][2];
}

void calc_cross2(float a[3], float b[3]) {//1x3 外積 1x3
  arr_data2[0] = a[1] * b[2] - a[2] * b[1];
  arr_data2[1] = a[2] * b[0] - a[0] * b[2];
  arr_data2[2] = a[0] * b[1] - a[1] * b[0];
}

void calc_sub(float a[3][3], float b[3][3]) {//3x3 引く 3x3
  int i, j;
  float c[3][3];
  for (i = 0; i < 3; ++i) {
    for (j = 0; j < 3; ++j) {
      c[i][j] = a[i][j] - b[i][j];
    }
  }
  arr_data[0][0] = c[0][0];
  arr_data[0][1] = c[0][1];
  arr_data[0][2] = c[0][2];

  arr_data[1][0] = c[1][0];
  arr_data[1][1] = c[1][1];
  arr_data[1][2] = c[1][2];

  arr_data[2][0] = c[2][0];
  arr_data[2][1] = c[2][1];
  arr_data[2][2] = c[2][2];
}

void calc_add(float a[3][3], float b[3][3]) {//3x3 足す 3x3
  int i, j;
  float c[3][3];
  for (i = 0; i < 3; ++i) {
    for (j = 0; j < 3; ++j) {
      c[i][j] = a[i][j] + b[i][j];
    }
  }
  arr_data[0][0] = c[0][0];
  arr_data[0][1] = c[0][1];
  arr_data[0][2] = c[0][2];

  arr_data[1][0] = c[1][0];
  arr_data[1][1] = c[1][1];
  arr_data[1][2] = c[1][2];

  arr_data[2][0] = c[2][0];
  arr_data[2][1] = c[2][1];
  arr_data[2][2] = c[2][2];
}

void calc_mult2(float a[3][3], float b[3]) {//3x3 掛ける 1x3
  arr_data2[0] = a[0][0] * b[0] + a[0][1] * b[1] + a[0][2] * b[2];
  arr_data2[1] = a[1][0] * b[0] + a[1][1] * b[1] + a[1][2] * b[2];
  arr_data2[2] = a[2][0] * b[0] + a[2][1] * b[1] + a[2][2] * b[2];
}

void calc_mult(float a[3][3], float b[3][3]) {//3x3 掛ける 3x3
  int i, j, k;
  float c[3][3], term;
  for (i = 0; i < 3; ++i) {
    for (j = 0; j < 3; ++j) {
      c[i][j] = a[i][j] * b[i][j];

      // 行列の項を計算
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
          term = 0;
          for (k = 0; k < 3; k++)
            term = term + a[i][k] * b[k][j];
          c[i][j] = term;
        }
      }
    }
  }

  arr_data[0][0] = c[0][0];
  arr_data[0][1] = c[0][1];
  arr_data[0][2] = c[0][2];

  arr_data[1][0] = c[1][0];
  arr_data[1][1] = c[1][1];
  arr_data[1][2] = c[1][2];

  arr_data[2][0] = c[2][0];
  arr_data[2][1] = c[2][1];
  arr_data[2][2] = c[2][2];
}

void gen_rot(float x, float y, float z) {
  float S_x = sin(x);
  float C_x = cos(x);
  float S_y = sin(y);
  float C_y = cos(y);
  float S_z = sin(z);
  float C_z = cos(z);

  arr_data[0][0] = C_y * C_z;
  arr_data[0][1] = C_z * S_x * S_y - C_x * S_z;
  arr_data[0][2] = S_x * S_z + C_x * C_z * S_y;

  arr_data[1][0] = C_y * S_z;
  arr_data[1][1] = C_x * C_z + S_x * S_y * S_z;
  arr_data[1][2] = C_x * S_y * S_z - C_z * S_x;

  arr_data[2][0] = -S_y;
  arr_data[2][1] = C_y * S_x;
  arr_data[2][2] = C_x * C_y;
}

void calc_correct_rot(float x, float y, float z) {
  /* 行列の積（掛け算） */
  int i, j, k;
  float a[3][3], b[3][3], c[3][3], term;

  float S_x = sin(x);
  float C_x = cos(x);
  float S_y = sin(y);
  float C_y = cos(y);
  float S_z = sin(z);
  float C_z = cos(z);

  a[0][0] = C_y * C_z;
  a[0][1] = C_z * S_x * S_y - C_x * S_z;
  a[0][2] = S_x * S_z + C_x * C_z * S_y;

  a[1][0] = C_y * S_z;
  a[1][1] = C_x * C_z + S_x * S_y * S_z;
  a[1][2] = C_x * S_y * S_z - C_z * S_x;

  a[2][0] = -S_y;
  a[2][1] = C_y * S_x;
  a[2][2] = C_x * C_y;

  b[0][0] = rot_data[0][0];
  b[0][1] = rot_data[0][1];
  b[0][2] = rot_data[0][2];

  b[1][0] = rot_data[1][0];
  b[1][1] = rot_data[1][1];
  b[1][2] = rot_data[1][2];

  b[2][0] = rot_data[2][0];
  b[2][1] = rot_data[2][1];
  b[2][2] = rot_data[2][2];

  for (i = 0; i < 3; ++i) {
    for (j = 0; j < 3; ++j) {
      c[i][j] = a[i][j] * b[i][j];

      // 行列の項を計算
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
          term = 0;
          for (k = 0; k < 3; k++)
            term = term + a[i][k] * b[k][j];
          c[i][j] = term;
        }
      }
    }
  }

  rot_data[0][0] = c[0][0];
  rot_data[0][1] = c[0][1];
  rot_data[0][2] = c[0][2];

  rot_data[1][0] = c[1][0];
  rot_data[1][1] = c[1][1];
  rot_data[1][2] = c[1][2];

  rot_data[2][0] = c[2][0];
  rot_data[2][1] = c[2][1];
  rot_data[2][2] = c[2][2];
}

void calc_quat2rot(void) {
  //1行目
  //quat(1)^2-quat(2)^2-quat(3)^2+quat(4)^2
  rot_data[0][0] = quat_data[1] * quat_data[1] - quat_data[2] * quat_data[2] - quat_data[3] * quat_data[3] + quat_data[0] * quat_data[0];
  rot_data[0][1] = 2.0 * (quat_data[1] * quat_data[2] + quat_data[3] * quat_data[0]);
  rot_data[0][2] = 2.0 * (quat_data[1] * quat_data[3] - quat_data[2] * quat_data[0]);

  //2行目
  rot_data[1][0] = 2.0 * (quat_data[1] * quat_data[2] - quat_data[3] * quat_data[0]);
  rot_data[1][1] = -quat_data[1] * quat_data[1] + quat_data[2] * quat_data[2] - quat_data[3] * quat_data[3] + quat_data[0] * quat_data[0];
  rot_data[1][2] = 2.0 * (quat_data[2] * quat_data[3] + quat_data[1] * quat_data[0]);

  //3行目
  rot_data[2][0] = 2.0 * (quat_data[1] * quat_data[3] + quat_data[2] * quat_data[0]);
  rot_data[2][1] = 2.0 * (quat_data[2] * quat_data[3] - quat_data[1] * quat_data[0]);
  rot_data[2][2] = -quat_data[1] * quat_data[1] - quat_data[2] * quat_data[2] + quat_data[3] * quat_data[3] + quat_data[0] * quat_data[0];
}

void calc_quat2initeuler(void) {
  init_euler_data[0] = atan2(-rot_data[1][2], rot_data[2][2]);
  init_euler_data[1] = asin(rot_data[0][2]);
  init_euler_data[2] = -atan2(-rot_data[0][1], rot_data[0][0]);
}

void calc_quat2euler(void) {
  euler_data[0] = atan2(-rot_data[1][2], rot_data[2][2]);
  euler_data[1] = asin(rot_data[0][2]);
  euler_data[2] = -atan2(-rot_data[0][1], rot_data[0][0]);
}

void calc_quat2zxy(void) {
  zxy_data[0] = asin(rot_data[2][1]);
  zxy_data[1] = atan2(-rot_data[2][0], rot_data[2][2]);
  zxy_data[2] = -atan2(-rot_data[0][1], rot_data[1][1]);
}

void calc_rpy(void) {
  float trs = 5.0 * M_PI / 180.0;
  float th = 45.0 * M_PI / 180.0;
  float euler_local_data[3] = {0, 0, 0}; //[rad]
  float zxy_local_data[3] = {0, 0, 0}; //[rad]
  euler_local_data[0] = atan2(-rot_data[1][2], rot_data[2][2]);
  euler_local_data[1] = asin(rot_data[0][2]);
  euler_local_data[2] = -atan2(-rot_data[0][1], rot_data[0][0]);
  zxy_local_data[0] = asin(rot_data[2][1]);
  zxy_local_data[1] = atan2(-rot_data[2][0], rot_data[2][2]);
  zxy_local_data[2] = -atan2(-rot_data[0][1], rot_data[1][1]);
  //  Serial.print(statuscalib);
  //  Serial.print(',');
  //  Serial.print(euler_local_data[0]);
  //  Serial.print(',');
  //  Serial.print(euler_local_data[1]);
  //  Serial.print(',');
  //  Serial.println(euler_local_data[2]);
  if (euler_local_data[1] > (th - trs) && euler_local_data[1] < (th + trs)) {//xyzEuler角でピッチ角が45度以上の時、zxy角に徐々に切り替える
    float coef = ((th + trs) - euler_local_data[1]) / (trs * 2.0);

    if (abs(euler_local_data[2]) > (M_PI / 2.0)) {
      if (euler_local_data[1] < 0.0) {

        float tmp = euler_local_data[0] - M_PI;
        if (tmp > M_PI) {
          tmp = tmp - 2.0 * M_PI;
        } else if (tmp < -M_PI) {
          tmp = tmp + 2.0 * M_PI;
        }
        rpy_data[0] = tmp * coef + zxy_local_data[0] * (1.0 - coef);
        rpy_data[1] = (-M_PI - euler_local_data[1]) * coef + zxy_local_data[1] * (1.0 - coef);
        rpy_data[2] = (euler_local_data[2] - M_PI) * coef + zxy_local_data[2] * (1.0 - coef);
      } else {
        float tmp = euler_local_data[0] - M_PI;
        if (tmp > M_PI) {
          tmp = tmp - 2.0 * M_PI;
        } else if (tmp < -M_PI) {
          tmp = tmp + 2.0 * M_PI;
        }
        rpy_data[0] = tmp * coef + zxy_local_data[0] * (1.0 - coef);
        rpy_data[1] = (M_PI - euler_local_data[1]) * coef + zxy_local_data[1] * (1.0 - coef);
        rpy_data[2] = (euler_local_data[2] - M_PI) * coef + zxy_local_data[2] * (1.0 - coef);
      }

    }
    else {
      rpy_data[0] = euler_local_data[0] * coef + zxy_local_data[0] * (1.0 - coef);
      rpy_data[1] = euler_local_data[1] * coef + zxy_local_data[1] * (1.0 - coef);
      rpy_data[2] = euler_local_data[2] * coef + zxy_local_data[2] * (1.0 - coef);
    }


  } else if (euler_local_data[1] < (- th + trs) && euler_local_data[1] > (-th - trs)) {//xyzEuler角でピッチ角が-45度以下の時、zxy角に徐々に切り替える
    float coef = ((th + trs) + euler_local_data[1]) / (trs * 2.0);
    if (abs(euler_local_data[2]) > (M_PI / 2.0)) {
      if (euler_local_data[1] < 0.0) {
        float tmp = euler_local_data[0] - M_PI;
        if (tmp > M_PI) {
          tmp = tmp - 2.0 * M_PI;
        } else if (tmp < -M_PI) {
          tmp = tmp + 2.0 * M_PI;
        }
        rpy_data[0] = tmp * coef + zxy_local_data[0] * (1.0 - coef);
        rpy_data[1] = (-M_PI - euler_local_data[1]) * coef + zxy_local_data[1] * (1.0 - coef);
        rpy_data[2] = (euler_local_data[2] - M_PI) * coef + zxy_local_data[2] * (1.0 - coef);
      } else {
        float tmp = euler_local_data[0] - M_PI;
        if (tmp > M_PI) {
          tmp = tmp - 2.0 * M_PI;
        } else if (tmp < -M_PI) {
          tmp = tmp + 2.0 * M_PI;
        }
        rpy_data[0] = tmp * coef + zxy_local_data[0] * (1.0 - coef);
        rpy_data[1] = (M_PI - euler_local_data[1]) * coef + zxy_local_data[1] * (1.0 - coef);
        rpy_data[2] = (euler_local_data[2] - M_PI) * coef + zxy_local_data[2] * (1.0 - coef);
      }
    }
    else {
      rpy_data[0] = euler_local_data[0] * coef + zxy_local_data[0] * (1.0 - coef);
      rpy_data[1] = euler_local_data[1] * coef + zxy_local_data[1] * (1.0 - coef);
      rpy_data[2] = euler_local_data[2] * coef + zxy_local_data[2] * (1.0 - coef);
    }

  } else if (abs(euler_local_data[1]) > (th + trs)) {//xyzEuler角でピッチ角が45度以上,-45度以下の時、zxy角に切り替える
    rpy_data[0] = zxy_local_data[0];
    rpy_data[1] = zxy_local_data[1];
    rpy_data[2] = zxy_local_data[2];
  } else {
    if (abs(euler_local_data[2]) > (M_PI / 2.0)) {
      if (euler_local_data[1] < 0.0) {
        rpy_data[0] = euler_local_data[0] - M_PI;
        rpy_data[1] = -M_PI - euler_local_data[1];
        rpy_data[2] = euler_local_data[2];
      } else {
        rpy_data[0] = euler_local_data[0] - M_PI;
        rpy_data[1] = M_PI - euler_local_data[1];
        rpy_data[2] = euler_local_data[2];
      }

    } else {
      rpy_data[0] = euler_local_data[0];
      rpy_data[1] = euler_local_data[1];
      rpy_data[2] = euler_local_data[2];
    }

  }
  if (rpy_data[0] > M_PI) {
    rpy_data[0] = rpy_data[0] - 2.0 * M_PI;
  } else if (rpy_data[0] < -M_PI) {
    rpy_data[0] = rpy_data[0] + 2.0 * M_PI;
  }
  if (rpy_data[1] > M_PI) {
    rpy_data[1] = rpy_data[1] - 2.0 * M_PI;
  } else if (rpy_data[1] < -M_PI) {
    rpy_data[1] = rpy_data[1] + 2.0 * M_PI;
  }
  if (rpy_data[2] > M_PI) {
    rpy_data[2] = rpy_data[2] - 2.0 * M_PI;
  } else if (rpy_data[2] < -M_PI) {
    rpy_data[2] = rpy_data[2] + 2.0 * M_PI;
  }
}
