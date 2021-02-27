#include "tcounter.h"
#include <Wire.h>
#include <SD.h>
//#include <SdFat.h>  // https://github.com/greiman/SdFat
#include <SPI.h>
#include <SparkFun_LPS25HB_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_LPS25HB
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define M_PI 3.1415927
#define M_GR 9.80665
#define M_R 0.0034837
#define M_T 273.15
#define M_P0 1013.25

#define DataLength 47

#define LED_pin 13
#define IR_p 0     //フォトリフレクタ
#define SD_cd 1     //SD

#define SV_INITANG 5.0
#define STEP_INPUT 6.0

//900→2100μsec
#define s_degulim 60.0
#define s_degllim -60.0

#define pulse_max 2100
#define pulse_min 900

#define MCP3425_address 0x68
#define MCP3425_confReg 0b10010011 //12bit 240sps PGA x8

#define if_th 0.1
#define paratime 1.12
#define landtime 5.0

#define Si1buf_size 4095
#define Si1readbyte_len 51

#define INIT_MODE 0
#define LAUN_MODE 1
#define DEVE_MODE 2
#define FAIL_MODE 3

#define SD_SAVECYCLE 100

#define DPRESS_COEF 2.382

TCounter *pwm_D2D3;
TCounter *timer1;

LPS25HB pressureSensor; // Create an object of the LPS25HB class
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
File dataFile;
int factor = 1;
byte Serial1_buffer[Si1buf_size];
int Serial1_buffer_len = 0;

bool f_sdact = 0;
int sd_cnt = 0;

unsigned long cnt0 = 0;//時間カウンタ
int cnt1 = 0;//LEDカウンタ
int cnt2 = 0;//データ送信カウンタ
int cnt3 = 0;//制御カウンタ
int cnt4 = 0;//計測カウンタ
int control_state1 = 0;
int control_state2 = 0;
float t = 0.0;
float controll_t = 0.0;
float controll_t_offset = 0.0;
unsigned long time_u =0; 
unsigned long pretime_u =0; 
float dt = 0.001;//s
boolean cnt1_flag = HIGH;
boolean cnt2_flag = LOW;
boolean cnt3_flag = LOW;
boolean cnt4_flag = LOW;
float delay_tau = 0.0;//計測制定待ち時間[ms]
float cnt1_time = 1.0;//割り込み周期[sec]//LEDカウンタ
float cnt2_time = 0.02;//割り込み周期[sec]//データ送信カウンタ
float cnt3_time = 0.02;//割り込み周期[sec]//制御カウンタ
float cnt4_time = 0.001;//割り込み周期[sec]//計測カウンタ
double con_time = 0.0;
int emc_cnt = 0;
float reg_data[22];
//float norm_acc = 0.0;

char buffer_data[256];
char buffer_data2[512];
int buffer_length = 0;

int statusmpu = 0;
int statustwe = 0;
int statusmain = 0;//mpu内部の判断ステータス

bool f_waitok = 0;//通信確立時間待機完了判定
bool f_sensok = 0;//センサキャリブレーション完了判定
bool f_checkok = 0;//発射前チェック完了判定
bool f_launch = 0;//発射判定
bool f_parareq = 0;//パラシュート展開要求
bool f_land = 0;//着地判定
bool f_fsa = 0;//故障判定
bool f_fsaend = 0;//fsa完了判定

uint8_t statuscalib = 0;//imuのキャリブレーション状態
bool calib_act = 0;

bool diagnosis_act = 0;

float wait_timer = 0.0;
bool wait_flg = 0;

uint8_t check_mode = 0;

float twe_t = 0.0;
float elevonR_com = 0.0;//[deg]
float elevonL_com = 0.0;

float elevonR_dummycom = 0.0;//[deg]
float elevonL_dummycom = 0.0;

float acc_data[3] = {0, 0, 0}; //[m/s^2]
float pacc_data[3] = {0, 0, 0}; //[m/s^2]
float ptd_v[3] = {0.0, 0.0, 0.0};
float v_data[3] = {0, 0, 0}; //[m/s]
float pv_data[3] = {0, 0, 0}; //[m/s]
float xeh_data[3] = {0, 0, 0}; //[m]
float gyro_data[3] = {0, 0, 0}; //[rad/s]
float pgyro_data[3] = {0, 0, 0}; //[rad/s]
float dgyro_data[3] = {0, 0, 0}; //[rad/s]
float euler_data[3] = {0, 0, 0}; //[rad]
float airvel_data = 0.0; //[m/s]
float ir_data[4] = {0, 0, 0, 0}; //[-]
float quat_data[4] = {0, 0, 0, 0}; //[-]

float zxy_data[3] = {0, 0, 0}; //[rad]

float init_euler_data[3] = {0, 0, 0}; //[rad]

float rot_data[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

float arr_data[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
float arr_data2[3] = {0,0,0};

float rpy_data[3] = {0, 0, 0}; //[rad]

float sens_offset_pos[3] = {0, 0, 0}; //[m]

float acc_dummydata[3] = {0, 0, 0}; //[m/s^2]
float v_dummydata[3] = {0, 0, 0}; //[m/s]
float xeh_dummydata[3] = {0, 0, 0}; //[m]
float gyro_dummydata[3] = {0, 0, 0}; //[rad/s]
float euler_dummydata[3] = {0, 0, 0}; //[rad]
float airvel_dummydata = 0.0; //[m/s]
float quat_dummydata[4] = {0, 0, 0, 0}; //[-]

float init_data[3] = {0, 0, 0}; //[rad]

float ph_data = 0.0; //[-]
float temp_data = 0.0;
float dpres_data = 0.0;
float apres_data = 0.0;
float altitude_data = 0.0;
float lpf_cdp = 1.0/(2*M_PI*(1.0/cnt4_time));

float ave_data[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
int ave_num = 10;
float adc_data = 0.0;

float angvel_data[3] = {0, 0, 0};
float angvel_data_f[3] = {0, 0, 0};
float gyro_offset_data[3] = {0, 0, 0};
float acc_offset_data[3] = {1.0, 1.0, 1.0};
float dpres_offset_data = 0.0; //[-]
float altitude_offset_data = 0.0;


void my_setup(void);
void pin_init(void);
void IntervalSet(float interupt_time);
void calc_attitude(void);
void get_attitude(void);
void sensor_init(void);

//void get_calib(void);

void control_state(void);
void control_init(void);
void control_launch(void);
void control_develop(void);
void fail_diagnosis(void);
void control_fail(void);

void control_law(void);


typedef union accel_t_gyro_union {
  struct {
    uint8_t x_accel_h;
    uint8_t x_accel_l;
    uint8_t y_accel_h;
    uint8_t y_accel_l;
    uint8_t z_accel_h;
    uint8_t z_accel_l;
    uint8_t t_h;
    uint8_t t_l;
    uint8_t x_gyro_h;
    uint8_t x_gyro_l;
    uint8_t y_gyro_h;
    uint8_t y_gyro_l;
    uint8_t z_gyro_h;
    uint8_t z_gyro_l;
  } reg;
  struct {
    int16_t x_accel;
    int16_t y_accel;
    int16_t z_accel;
    int16_t temperature;
    int16_t x_gyro;
    int16_t y_gyro;
    int16_t z_gyro;
  } value;
};
