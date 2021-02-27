using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;
using System.IO.Ports;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Kitware.VTK;



namespace control_center
{
    public partial class Form1 : Form
    {
        delegate void timer1Delegate();

        

        
        //Serial
        /****************************************************************************/
        /*!
		 *	@brief	ボーレート格納用のクラス定義.
		 */
        private class BuadRateItem : Object
        {
            private string m_name = "";
            private int m_value = 0;

            // 表示名称
            public string NAME
            {
                set { m_name = value; }
                get { return m_name; }
            }

            // ボーレート設定値.
            public int BAUDRATE
            {
                set { m_value = value; }
                get { return m_value; }
            }

            // コンボボックス表示用の文字列取得関数.
            public override string ToString()
            {
                return m_name;
            }
        }

        /****************************************************************************/
        /*!
		 *	@brief	制御プロトコル格納用のクラス定義.
		 */
        private class HandShakeItem : Object
        {
            private string m_name = "";
            private Handshake m_value = Handshake.None;

            // 表示名称
            public string NAME
            {
                set { m_name = value; }
                get { return m_name; }
            }

            // 制御プロトコル設定値.
            public Handshake HANDSHAKE
            {
                set { m_value = value; }
                get { return m_value; }
            }

            // コンボボックス表示用の文字列取得関数.
            public override string ToString()
            {
                return m_name;
            }
        }

        private delegate void Delegate_RcvDataToTextBox(string data);

        public Form1()
        {
            InitializeComponent();

            START_BUTTON.Enabled = false; //無効にする
            STOP_BUTTON.Enabled = false; //無効にする
            //! 利用可能なシリアルポート名の配列を取得する.
            string[] PortList = SerialPort.GetPortNames();

            COMPORT_BOX.Items.Clear();

            //! シリアルポート名をコンボボックスにセットする.
            foreach (string PortName in PortList)
            {
                COMPORT_BOX.Items.Add(PortName);
            }
            if (COMPORT_BOX.Items.Count > 0)
            {
                COMPORT_BOX.SelectedIndex = 0;
            }

            BAUDRATE_BOX.Items.Clear();

            // ボーレート選択コンボボックスに選択項目をセットする.
            BuadRateItem baud;
            baud = new BuadRateItem();
            baud.NAME = "4800bps";
            baud.BAUDRATE = 4800;
            BAUDRATE_BOX.Items.Add(baud);

            baud = new BuadRateItem();
            baud.NAME = "9600bps";
            baud.BAUDRATE = 9600;
            BAUDRATE_BOX.Items.Add(baud);

            baud = new BuadRateItem();
            baud.NAME = "19200bps";
            baud.BAUDRATE = 19200;
            BAUDRATE_BOX.Items.Add(baud);

            baud = new BuadRateItem();
            baud.NAME = "115200bps";
            baud.BAUDRATE = 115200;
            BAUDRATE_BOX.Items.Add(baud);
            BAUDRATE_BOX.SelectedIndex = 1;

            CON_BOX.Items.Clear();

            // フロー制御選択コンボボックスに選択項目をセットする.
            HandShakeItem ctrl;
            ctrl = new HandShakeItem();
            ctrl.NAME = "なし";
            ctrl.HANDSHAKE = Handshake.None;
            CON_BOX.Items.Add(ctrl);

            ctrl = new HandShakeItem();
            ctrl.NAME = "XON/XOFF制御";
            ctrl.HANDSHAKE = Handshake.XOnXOff;
            CON_BOX.Items.Add(ctrl);

            ctrl = new HandShakeItem();
            ctrl.NAME = "RTS/CTS制御";
            ctrl.HANDSHAKE = Handshake.RequestToSend;
            CON_BOX.Items.Add(ctrl);

            ctrl = new HandShakeItem();
            ctrl.NAME = "XON/XOFF + RTS/CTS制御";
            ctrl.HANDSHAKE = Handshake.RequestToSendXOnXOff;
            CON_BOX.Items.Add(ctrl);
            CON_BOX.SelectedIndex = 0;

            // 送受信用のテキストボックスをクリアする.
            SEND_DATA_TEXTBOX.Clear();
            RECEVED_DATA_TEXTBOX.Clear();


        }

        private void Form1_Load(object sender, EventArgs e)
        {

            

        }

        /****************************************************************************/
        /*!
		 *	@brief	ダイアログの終了処理.
		 *
		 *	@param	[in]	sender	イベントの送信元のオブジェクト.
		 *	@param	[in]	e		イベント情報.
		 *
		 *	@retval	なし.
		 */
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {

            timer4.Enabled = false;
            //! シリアルポートをオープンしている場合、クローズする.
            if (GETDATA1_SERIALPORT.IsOpen)
            {
                GETDATA1_SERIALPORT.Close();
            }
        }

        /****************************************************************************/
        /*!
		 *	@brief	[接続]/[切断]ボタンを押したときにシリアルポートのオープン/クローズを行う.
		 *
		 *	@param	[in]	sender	イベントの送信元のオブジェクト.
		 *	@param	[in]	e		イベント情報.
		 *
		 *	@retval	なし.
		 */
        private void COMPORT_SET_BUTTON_Click(object sender, EventArgs e)
        {

            if (GETDATA1_SERIALPORT.IsOpen == true)
            {
                //! シリアルポートをクローズする.
                GETDATA1_SERIALPORT.Close();

                //! ボタンの表示を[切断]から[接続]に変える.
                COMPORT_SET_BUTTON.Text = "CONNECT";
                START_BUTTON.Enabled = true; //有効にする
            }
            else
            {
                //! オープンするシリアルポートをコンボボックスから取り出す.
                GETDATA1_SERIALPORT.PortName = COMPORT_BOX.SelectedItem.ToString();

                //! ボーレートをコンボボックスから取り出す.
                BuadRateItem baud = (BuadRateItem)BAUDRATE_BOX.SelectedItem;
                GETDATA1_SERIALPORT.BaudRate = baud.BAUDRATE;

                //! データビットをセットする. (データビット = 8ビット)
                GETDATA1_SERIALPORT.DataBits = 8;

                //! パリティビットをセットする. (パリティビット = なし)
                GETDATA1_SERIALPORT.Parity = Parity.None;

                //! ストップビットをセットする. (ストップビット = 1ビット)
                GETDATA1_SERIALPORT.StopBits = StopBits.One;

                //! フロー制御をコンボボックスから取り出す.
                HandShakeItem ctrl = (HandShakeItem)CON_BOX.SelectedItem;
                GETDATA1_SERIALPORT.Handshake = ctrl.HANDSHAKE;

                //! 文字コードをセットする.
                GETDATA1_SERIALPORT.Encoding = Encoding.ASCII;

                GETDATA1_SERIALPORT.DtrEnable = true;
                GETDATA1_SERIALPORT.RtsEnable = true;

                try
                {
                    //! シリアルポートをオープンする.
                    GETDATA1_SERIALPORT.Open();

                    //! ボタンの表示を[接続]から[切断]に変える.
                    COMPORT_SET_BUTTON.Text = "DISCONNECT";
                    START_BUTTON.Enabled = true; //有効にする
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }
        /****************************************************************************/
        /*!
		 *	@brief	データ受信が発生したときのイベント処理.
		 *
		 *	@param	[in]	sender	イベントの送信元のオブジェクト.
		 *	@param	[in]	e		イベント情報.
		 *
		 *	@retval	なし.
		 */
        const int read_data_size = 51;
        const int get_data_size_init = 23;
        float[] get_data = new float[get_data_size_init];
        double teensy_t = 0.0;
        double twe_t = 0.0;
        int statustwe = 0;
        int statusteensy = 0;
        int cnt_r = 0;
        byte[] buffer_data = new byte[4096];
        int buffer_data_size = 0;

        private void GETDATA1_SERIALPORT_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            //! シリアルポートをオープンしていない場合、処理を行わない.
            if (GETDATA1_SERIALPORT.IsOpen == false)
            {

                return;
            }

            try
            {

                int get_data_size = GETDATA1_SERIALPORT.BytesToRead;
                byte[] rdat = new byte[get_data_size];
                GETDATA1_SERIALPORT.Read(rdat, 0, rdat.Length);

                byte[] mergedArray = new byte[rdat.Length + buffer_data_size];

                Array.Copy(buffer_data, mergedArray, buffer_data_size);

                Array.Copy(rdat, 0, mergedArray, buffer_data_size, rdat.Length);

                buffer_data_size = mergedArray.Length;

                Array.Copy(mergedArray, buffer_data, buffer_data_size);

                if (buffer_data_size >= get_data_size_init + 4)
                {                //! 受信データを読み込む.
                    int flag0 = 999;
                    int flag1 = 999;
                    int flag2 = 999;
                    int flag3 = 999;
                    byte[] idata = new byte[4096];
                    byte[] idata2 = new byte[4096];
                    Array.Copy(buffer_data, idata, buffer_data_size);
                    Array.Clear(buffer_data, 0, buffer_data_size);
                    //buffer_data_size = 0;
                    int i = 0;
                    for (i = 0; i < 4096 ; i++) {
                        if (idata[i] == 0xa5 && flag0 == 999)
                        {
                            flag0 = i;
                        }
                        if (idata[i] == 0x5a && flag0 + 1 == i)
                        {
                            flag1 = i;
                        }
                        if (idata[i] == 0x0d && flag1 + 1 + read_data_size == i)
                        {
                            flag2 = i;
                        }
                        if (idata[i] == 0x0a && flag2 + 1 == i)
                        {
                            flag3 = i;
                            buffer_data_size = buffer_data_size - (flag3 + 1);
                            Array.Copy(idata, flag3 + 1, buffer_data, 0, buffer_data_size);

                            break;
                        }
                    }
                    if (flag1 == 999 || flag3 == 999)
                    {
                        //skip_this_data
                    }
                    else
                    {
                        Array.Copy(idata, flag1 + 1, idata2, 0, flag2 - 1);
                        ushort ushTmp;
                        string data = "";

                        //statustwe
                        statustwe = (int)idata2[0];

                        //statusteensy
                        statusteensy = (int)idata2[1];

                        //twe_t
                        ushTmp = (ushort)(((idata2[2] << 8) & 0xff00) | (ushort)(idata2[3] & 0x00ff));
                        twe_t = (double)(ushTmp / 65535.0 * 600.0);

                        //teensy_t
                        ushTmp = (ushort)(((idata2[4] << 8) & 0xff00) | (ushort)(idata2[5] & 0x00ff));
                        teensy_t = (double)(ushTmp / 65535.0 * 600.0);

                        //acc_data
                        ushTmp = (ushort)(((idata2[6] << 8) & 0xff00) | (idata2[7] & 0x00ff));
                        get_data[0] = ((float)ushTmp / 65535.0F * 32F - 16F);
                        ushTmp = (ushort)(((idata2[8] << 8) & 0xff00) | (idata2[9] & 0x00ff));
                        get_data[1] = ((float)ushTmp / 65535.0F * 32F - 16F);
                        ushTmp = (ushort)(((idata2[10] << 8) & 0xff00) | (idata2[11] & 0x00ff));
                        get_data[2] = ((float)ushTmp / 65535.0F * 32F - 16F);

                        //v_data
                        ushTmp = (ushort)(((idata2[12] << 8) & 0xff00) | (idata2[13] & 0x00ff));
                        get_data[3] = ((float)ushTmp / 65535.0F * 100 - 50);
                        ushTmp = (ushort)(((idata2[14] << 8) & 0xff00) | (idata2[15] & 0x00ff));
                        get_data[4] = ((float)ushTmp / 65535.0F * 100 - 50);
                        ushTmp = (ushort)(((idata2[16] << 8) & 0xff00) | (idata2[17] & 0x00ff));
                        get_data[5] = ((float)ushTmp / 65535.0F * 100 - 50);

                        //xi eta hight_data
                        ushTmp = (ushort)(((idata2[18] << 8) & 0xff00) | (idata2[19] & 0x00ff));
                        get_data[6] = ((float)ushTmp / 65535.0F * 30 - 15);
                        ushTmp = (ushort)(((idata2[20] << 8) & 0xff00) | (idata2[21] & 0x00ff));
                        get_data[7] = ((float)ushTmp / 65535.0F * 30 - 15);
                        ushTmp = (ushort)(((idata2[22] << 8) & 0xff00) | (idata2[23] & 0x00ff));
                        get_data[8] = ((float)ushTmp / 65535.0F * 30 - 0);

                        //gyro_data
                        ushTmp = (ushort)(((idata2[24] << 8) & 0xff00) | (idata2[25] & 0x00ff));
                        get_data[9] = ((float)ushTmp / 65535.0F * 6 * (float)Math.PI - 3 * (float)Math.PI);
                        ushTmp = (ushort)(((idata2[26] << 8) & 0xff00) | (idata2[27] & 0x00ff));
                        get_data[10] = ((float)ushTmp / 65535.0F * 6 * (float)Math.PI - 3 * (float)Math.PI);
                        ushTmp = (ushort)(((idata2[28] << 8) & 0xff00) | (idata2[29] & 0x00ff));
                        get_data[11] = ((float)ushTmp / 65535.0F * 6 * (float)Math.PI - 3 * (float)Math.PI);

                        //euler_data
                        ushTmp = (ushort)(((idata2[30] << 8) & 0xff00) | (idata2[31] & 0x00ff));
                        get_data[12] = ((float)ushTmp / 65535.0F * 2 * (float)Math.PI - (float)Math.PI);
                        ushTmp = (ushort)(((idata2[32] << 8) & 0xff00) | (idata2[33] & 0x00ff));
                        get_data[13] = ((float)ushTmp / 65535.0F * 2 * (float)Math.PI - (float)Math.PI);
                        ushTmp = (ushort)(((idata2[34] << 8) & 0xff00) | (idata2[35] & 0x00ff));
                        get_data[14] = ((float)ushTmp / 65535.0F * 2 * (float)Math.PI - (float)Math.PI);

                        //air_vel_data
                        ushTmp = (ushort)(((idata2[36] << 8) & 0xff00) | (idata2[37] & 0x00ff));
                        get_data[15] = ((float)ushTmp / 65535.0F * 255 - 0);

                        //quat_data
                        ushTmp = (ushort)(((idata2[38] << 8) & 0xff00) | (idata2[39] & 0x00ff));
                        get_data[16] = ((float)ushTmp / 65535.0F * 2 - 1);
                        ushTmp = (ushort)(((idata2[40] << 8) & 0xff00) | (idata2[41] & 0x00ff));
                        get_data[17] = ((float)ushTmp / 65535.0F * 2 - 1);
                        ushTmp = (ushort)(((idata2[42] << 8) & 0xff00) | (idata2[43] & 0x00ff));
                        get_data[18] = ((float)ushTmp / 65535.0F * 2 - 1);
                        ushTmp = (ushort)(((idata2[44] << 8) & 0xff00) | (idata2[45] & 0x00ff));
                        get_data[19] = ((float)ushTmp / 65535.0F * 2 - 1);

                        //elevonR
                        ushTmp = (ushort)(((idata2[46] << 8) & 0xff00) | (idata2[47] & 0x00ff));
                        get_data[20] = ((float)ushTmp / 65535.0F * 255 - 0);

                        //elevonL
                        ushTmp = (ushort)(((idata2[48] << 8) & 0xff00) | (idata2[49] & 0x00ff));
                        get_data[21] = ((float)ushTmp / 65535.0F * 255 - 0);

                        //parachute
                        get_data[22] = ((float)idata2[50]);

                        data = teensy_t.ToString() + "\r\n";
                        State[0] = statustwe;
                        State[1] = statusteensy;
                        State[2] = twe_t;
                        State[3] = teensy_t;
                        for (i = 4; i < get_data_size_init+4; i++) State[i] = get_data[i - 4];
                        //! 受信したデータをテキストボックスに書き込む.
                        Invoke(new Delegate_RcvDataToTextBox(RcvDataToTextBox), new Object[] { data });
                        //data_save();

                        //send_outputdata();
                    }
                }

                
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        /****************************************************************************/
        /*!
		 *	@brief	受信データをテキストボックスに書き込む.
		 *
		 *	@param	[in]	data	受信した文字列.
		 *
		 *	@retval	なし.
		 */
        private void RcvDataToTextBox(string data)
        {
            //! 受信データをテキストボックスの最後に追記する.
            if (data != null)
            {
                RECEVED_DATA_TEXTBOX.AppendText(data);
            }
        }
        /****************************************************************************/
        /*!
		 *	@brief	[送信]ボタンを押して、データ送信を行う.
		 *
		 *	@param	[in]	sender	イベントの送信元のオブジェクト.
		 *	@param	[in]	e		イベント情報.
		 *
		 *	@retval	なし.
		 */
        private void SEND_DATA_LABEL_Click(object sender, EventArgs e)
        {
            //! シリアルポートをオープンしていない場合、処理を行わない.
            if (GETDATA1_SERIALPORT.IsOpen == false)
            {
                return;
            }
            //! テキストボックスから、送信するテキストを取り出す.
            String data = SEND_DATA_TEXTBOX.Text;

            //! 送信するテキストがない場合、データ送信は行わない.
            if (string.IsNullOrEmpty(data) == true)
            {
                return;
            }

            try
            {
                //! シリアルポートからテキストを送信する.
                GETDATA1_SERIALPORT.Write(data);

                //! 送信データを入力するテキストボックスをクリアする.
                SEND_DATA_TEXTBOX.Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        //Sim//***************************************************************************************

        public int timer_cnt1 = 0;//制御測更新周期カウンタ
        public int timer_cnt2 = 0;//データ保存更新周期カウンタ
        public int timer_cnt3 = 0;//データ表示更新周期カウンタ
        public int timer_cnt4 = 0;//データ送信周期カウンタ
        public double dt = 0.001;//計算刻み幅
        public double time = 0;//計算時間
        public double[] State = new double[get_data_size_init+4];//二種マイコンステータス・時間計４データ追加
        public float[,] rot_data = new float[3, 3];
        public vtkArrowSource arrowSource01 = vtkArrowSource.New();
        public vtkArrowSource arrowSource02 = vtkArrowSource.New();

        // Visualize
        public vtkPolyDataMapper mapper01 = vtkPolyDataMapper.New();
        public vtkPolyDataMapper mapper02 = vtkPolyDataMapper.New();
        public vtkRenderWindow renderWindow = null;
        public vtkRenderer renderer = null;
        public vtkCamera camera = vtkCamera.New();


        public vtkActor actor01 = vtkActor.New();
        public vtkActor actor02 = vtkActor.New();

        /*

            State[0] = statustwe;
            State[1] = statustwe;
            State[2] = twe_t;
            State[3] = teensy_t;
            State[4] = acc_data[0];
            State[5] = acc_data[1];
            State[6] = acc_data[2];
            State[7] = v_data[0];
            State[8] = v_data[1];
            State[9] = v_data[2];
            State[10] = xeh_data[0];
            State[11] = xeh_data[1];
            State[12] = xeh_data[2];
            State[13] = gyro_data[0];
            State[14] = gyro_data[1];
            State[15] = gyro_data[2];
            State[16] = euler_data[0];
            State[17] = euler_data[1];
            State[18] = euler_data[2];
            State[19] = airvel_data;
            State[20] = ir_data[0];
            State[21] = ir_data[1];
            State[22] = ir_data[2];
            State[23] = ir_data[3];
            State[24] = elevonR_com;
            State[25] = elevonL_com;
            State[26] = parachute_com;

        */

        double RTD = 57.295779513082320876798154814105;
        double DTR = 0.01745329251994329576923690768489;

        string[] save_data = new string[10];

        System.Text.StringBuilder save_data_sb = new System.Text.StringBuilder();//一度に追加
  
        
        private void Sim_Initialize()
        {
            Initialize_text();
            Initialize_phase();
            Initialize_state();
            Initialize_graph();
            send_outputdata();
        }

        private void Initialize_text()
        {
            for (int i = 0; i < 9; i++) save_data[i] = "";

            save_data[0] = "PCTime,statustwe,statusmpu,time_twe,time_mpu,acc x,acc y,acc z,v x,v y,v z,pos x,pos y,pos z,gyro x,gyro y,gyro z,euler x,euler y,euler z,airvel,quat_w,quat_x,quat_y,quat_z,elevonR,elevonL,parachute\r\n";
            for (int i = 0; i < 100; i++) textbox_val[i] = 0.0f;

            
        }

        private void Initialize_phase()
        {
            time = 0.0;
            timer_cnt1 = 0;
            timer_cnt2 = 0;
            timer_cnt3 = 0;
            timer_cnt4 = 0;
        }

        private void Initialize_state()
        {
            for (int i = 0; i < State.Length; i++) State[i] = 0;
            dt = 0.001;
        }



        private void Initialize_graph()
        {
 
        }


        private void control_law()//制御則
        {
            timer_cnt1 = 0;
        }

        private void calculation()//
        {
            //
        }
 



        //運動方程式演算部終了//**************************************************************************************

        private void data_save()//データの保存
        {

            int j;
            if (time < 5) j = 0;
            else if (time < 10) j = 1;
            else if (time < 15) j = 2;
            else if (time < 20) j = 3;
            else if (time < 25) j = 4;
            else if (time < 30) j = 5;
            else if (time < 35) j = 6;
            else if (time < 40) j = 7;
            else if (time < 45) j = 8;
            else j = 9;


            save_data_sb.Clear();//添付用変数のクリア

            //Time
            save_data_sb.Append(time.ToString());
            save_data_sb.Append(",");
            //data
            for (int i = 0; i < State.Length; i++) save_data_sb.Append(State[i].ToString() + ",");      //data

            save_data_sb.Append("\r\n");

            //添付用変数から正規に代入
            save_data[j] += save_data_sb.ToString();
            save_data_sb.Clear();//添付用変数クリア
            timer_cnt2 = 0;
        }

        private void display()//表示
        {

            /*

     State[0] = statustwe;
     State[1] = statusteensy;
     State[2] = twe_t;
     State[3] = teensy_t;
     State[4] = acc_data[0];
     State[5] = acc_data[1];
     State[6] = acc_data[2];
     State[7] = v_data[0];
     State[8] = v_data[1];
     State[9] = v_data[2];
     State[10] = xeh_data[0];
     State[11] = xeh_data[1];
     State[12] = xeh_data[2];
     State[13] = gyro_data[0];
     State[14] = gyro_data[1];
     State[15] = gyro_data[2];
     State[16] = euler_data[0];
     State[17] = euler_data[1];
     State[18] = euler_data[2];
     State[19] = airvel_data;
     State[20] = quat_data[0];
     State[21] = quat_data[1];
     State[22] = quat_data[2];
     State[23] = quat_data[3];
     State[24] = elevonR_com;
     State[25] = elevonL_com;
     State[26] = parachute_com;

 */

            //TIME_LABEL.Text = string.Format("TIME:{0:0.0}sec",time);

            TIME_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                TIME_LABEL.Text = string.Format("TIME:{0:0.0}sec", time);
            });

            //twe ステータス
            TWESTATUS_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                TWESTATUS_LABEL.Text = string.Format("Twe Status:{0:0}", State[0]);
            });
            //twe 時間
            TWETIME_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                TWETIME_LABEL.Text = string.Format("Twe Time:{0:0.00}sec", State[2]);
            });
            //teensy ステータス
            TEENSYSTATUS_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                TEENSYSTATUS_LABEL.Text = string.Format("Teensy Status:{0:0}", State[1]);
            });
            //teensy 時間
            TEENSYTIME_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                TEENSYTIME_LABEL.Text = string.Format("Teensy Time:{0:0.00}sec", State[3]);
            });

            //elevon R
            ELEVONR_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                ELEVONR_LABEL.Text = string.Format("elevon R:{0:0.00}", State[24]);
            });
            //elevon L
            ELEVONL_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                ELEVONL_LABEL.Text = string.Format("elevon L:{0:0.00}", State[25]);
            });
            //parachute
            PARACHUTE_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                PARACHUTE_LABEL.Text = string.Format("parachute:{0:0.00}", State[26]);
            });

            //accx
            ACCX_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                ACCX_LABEL.Text = string.Format("acc x:{0:0.00}", State[4]);
            });
            //accy
            ACCY_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                ACCY_LABEL.Text = string.Format("acc y:{0:0.00}", State[5]);
            });
            //accz
            ACCZ_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                ACCZ_LABEL.Text = string.Format("acc z:{0:0.00}", State[6]);
            });

            //vx
            VX_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                VX_LABEL.Text = string.Format("v x:{0:0.00}", State[7]);
            });
            //vy
            VY_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                VY_LABEL.Text = string.Format("v y:{0:0.00}", State[8]);
            });
            //vz
            VZ_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                VZ_LABEL.Text = string.Format("v z:{0:0.00}", State[9]);
            });

            //POSx
            POSX_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                POSX_LABEL.Text = string.Format("pos x:{0:0.00}", State[10]);
            });
            //POSy
            POSY_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                POSY_LABEL.Text = string.Format("pos y:{0:0.00}", State[11]);
            });
            //POSz
            POSZ_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                POSZ_LABEL.Text = string.Format("pos z:{0:0.00}", State[12]);
            });

            //quat a
            IRA_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                IRA_LABEL.Text = string.Format("quat a:{0:0.00}", State[20]);
            });
            //quat b
            IRB_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                IRB_LABEL.Text = string.Format("quat b:{0:0.00}", State[21]);
            });
            //quat c
            IRC_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
               IRC_LABEL.Text = string.Format("quat c:{0:0.00}", State[22]);
            });
            //quat d
            IRD_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
               IRD_LABEL.Text = string.Format("quat d:{0:0.00}", State[23]);
            });

            //gyrox
            GYROX_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                GYROX_LABEL.Text = string.Format("gyro x:{0:0.00}", State[13]);
            });
            //gyroy
            GYROY_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                GYROY_LABEL.Text = string.Format("gyro y:{0:0.00}", State[14]);
            });
            //gyroz
            GYROZ_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                GYROZ_LABEL.Text = string.Format("gyro z:{0:0.00}", State[15]);
            });

            //eulerx
            EULERX_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                EULERX_LABEL.Text = string.Format("euler x:{0:0.00}", State[16] * 180.0 / Math.PI);
            });
            //eulery
            EULERY_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                EULERY_LABEL.Text = string.Format("euler y:{0:0.00}", State[17] * 180.0 / Math.PI);
            });
            //eulerz
            EULERZ_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                EULERZ_LABEL.Text = string.Format("euler z:{0:0.00}", State[18] * 180.0 / Math.PI);
            });

            //Air Velocity
            AIRVEL_LABEL.BeginInvoke((MethodInvoker)delegate ()
            {
                AIRVEL_LABEL.Text = string.Format("Air Velocity:{0:0.00}", State[19]);
            });



            plot_data.BeginInvoke((MethodInvoker)delegate ()
            {
                // 軸の最大値・最小値、主目盛の間隔を設定します。
                plot_data.ChartAreas[0].AxisY.Maximum = 180;
                plot_data.ChartAreas[0].AxisY.Minimum = -180;

                if (plot_data.Series[0].Points.Count <= 500)
                {
                    plot_data.Series[0].Points.AddXY(time, State[16] * 180.0 / Math.PI);
                    plot_data.Series[1].Points.AddXY(time, State[17] * 180.0 / Math.PI);
                    plot_data.Series[2].Points.AddXY(time, State[18] * 180.0 / Math.PI);
                }
                else
                {
                    for (int i = 1; i <= 500; i++)
                    {
                        plot_data.Series[0].Points[i - 1].YValues = plot_data.Series[0].Points[i].YValues;
                        plot_data.Series[1].Points[i - 1].YValues = plot_data.Series[1].Points[i].YValues;
                        plot_data.Series[2].Points[i - 1].YValues = plot_data.Series[2].Points[i].YValues;
                    }
                    plot_data.Series[0].Points.RemoveAt(500);
                    plot_data.Series[1].Points.RemoveAt(500);
                    plot_data.Series[2].Points.RemoveAt(500);
                    plot_data.Series[0].Points.AddXY(time, State[16] * 180.0 / Math.PI);
                    plot_data.Series[1].Points.AddXY(time, State[17] * 180.0 / Math.PI);
                    plot_data.Series[2].Points.AddXY(time, State[18] * 180.0 / Math.PI);
                }
                
                plot_data.Invalidate();
            });

            plot_data2.BeginInvoke((MethodInvoker)delegate ()
            {
                // 軸の最大値・最小値、主目盛の間隔を設定します。
                plot_data2.ChartAreas[0].AxisY.Maximum = 30.0;
                plot_data2.ChartAreas[0].AxisY.Minimum = 0.0;

                if (plot_data2.Series[0].Points.Count <= 500)
                {
                    plot_data2.Series[0].Points.AddXY(time, State[19]);
                }
                else
                {
                    for (int i = 1; i <= 500; i++)
                    {
                        plot_data2.Series[0].Points[i - 1].YValues = plot_data2.Series[0].Points[i].YValues;
  
                    }
                    plot_data2.Series[0].Points.RemoveAt(500);
                    plot_data2.Series[0].Points.AddXY(time, State[19]);

                }

                plot_data.Invalidate();
            });
            timer_cnt3 = 0;
        }

        private void calc_correct_rot(double x, double y, double z)
        {
            /* 行列の積（掛け算） */
            int i, j, k;
            float[,] a = new float[3, 3];
            float[,] b = new float[3, 3];
            float[,] c = new float[3, 3];
            float term;
            float S_x = (float)Math.Sin(x);
            float C_x = (float)Math.Cos(x);
            float S_y = (float)Math.Sin(y);
            float C_y = (float)Math.Cos(y);
            float S_z = (float)Math.Sin(z);
            float C_z = (float)Math.Cos(z);
/*
            a[0,0] = C_y* C_z;
            a[0,1] = C_y * S_z;
            a[0,2] = -S_y;

            a[1,0] = C_z * S_x * S_y - C_x * S_z;
            a[1,1] = C_x* C_z + S_x* S_y * S_z;
            a[1,2] = C_y * S_x;

            a[2,0] = S_x * S_z + C_x * C_z * S_y;
            a[2,1] = C_x * S_y * S_z - C_z * S_x;
            a[2,2] = C_x * C_y;
*/
            
            a[0, 0] = C_y * C_z;
            a[0, 1] = C_z * S_x * S_y - C_x * S_z;
            a[0, 2] = S_x * S_z + C_x * C_z * S_y;

            a[1, 0] = C_y * S_z;
            a[1, 1] = C_x * C_z + S_x * S_y * S_z;
            a[1, 2] = C_x * S_y * S_z - C_z * S_x;

            a[2, 0] = -S_y;
            a[2, 1] = C_y * S_x;
            a[2, 2] = C_x * C_y;
            

            b[0,0] = rot_data[0,0];
            b[0,1] = rot_data[0,1];
            b[0,2] = rot_data[0,2];

            b[1,0] = rot_data[1,0];
            b[1,1] = rot_data[1,1];
            b[1,2] = rot_data[1,2];

            b[2,0] = rot_data[2,0];
            b[2,1] = rot_data[2,1];
            b[2,2] = rot_data[2,2];

          for (i = 0; i< 3; ++i) {
            for (j = 0; j< 3; ++j) {
              c[i,j] = a[i,j] * b[i,j];

              // 行列の項を計算
              for (i = 0; i< 3; i++) {
                for (j = 0; j< 3; j++) {
                  term = 0;
                  for (k = 0; k< 3; k++)
                    term = term + a[i,k] * b[k,j];
                  c[i,j] = term;
                }
        }
            }
          }

          rot_data[0,0] = c[0,0];
          rot_data[0,1] = c[0,1];
          rot_data[0,2] = c[0,2];

          rot_data[1,0] = c[1,0];
          rot_data[1,1] = c[1,1];
          rot_data[1,2] = c[1,2];

          rot_data[2,0] = c[2,0];
          rot_data[2,1] = c[2,1];
          rot_data[2,2] = c[2,2];
        }

        private void calc_quat2rot()
        {
            float[] quat_data = new float[4];
            quat_data[0] = (float)State[20];
            quat_data[1] = (float)State[21];
            quat_data[2] = (float)State[22];
            quat_data[3] = (float)State[23];
            //1行目
            //quat(1)^2-quat(2)^2-quat(3)^2+quat(4)^2
            rot_data[0,0] = quat_data[1] * quat_data[1] - quat_data[2] * quat_data[2] - quat_data[3] * quat_data[3] + quat_data[0] * quat_data[0];
            rot_data[0,1] = 2.0f * (quat_data[1] * quat_data[2] + quat_data[3] * quat_data[0]);
            rot_data[0,2] = 2.0f * (quat_data[1] * quat_data[3] - quat_data[2] * quat_data[0]);

            //2行目
            rot_data[1,0] = 2.0f * (quat_data[1] * quat_data[2] - quat_data[3] * quat_data[0]);
            rot_data[1,1] = -quat_data[1] * quat_data[1] + quat_data[2] * quat_data[2] - quat_data[3] * quat_data[3] + quat_data[0] * quat_data[0];
            rot_data[1,2] = 2.0f * (quat_data[2] * quat_data[3] + quat_data[1] * quat_data[0]);

            //3行目
            rot_data[2,0] = 2.0f * (quat_data[1] * quat_data[3] + quat_data[2] * quat_data[0]);
            rot_data[2,1] = 2.0f * (quat_data[2] * quat_data[3] - quat_data[1] * quat_data[0]);
            rot_data[2,2] = -quat_data[1] * quat_data[1] - quat_data[2] * quat_data[2] + quat_data[3] * quat_data[3] + quat_data[0] * quat_data[0];
        }

        public float[] model_ori_data = new float[3];
        private void calc_quat2euler()
        {
            double threshold = 0.00001;
            if (Math.Abs(rot_data[0,2] - 1.0f) < threshold)
            { // R(2,1) = sin(x) = 1の時

                model_ori_data[0] = (float)Math.Atan2(-rot_data[1, 2], rot_data[2, 2]);
                model_ori_data[1] = (float)(Math.PI/2.0);
                model_ori_data[2] = (float)0.0;
            }
            else if (Math.Abs(rot_data[0, 2] + 1.0) < threshold)
            { // R(2,1) = sin(x) = -1の時
                model_ori_data[0] = (float)Math.Atan2(-rot_data[1, 2], rot_data[2, 2]);
                model_ori_data[1] = (float)(-Math.PI / 2.0);
                model_ori_data[2] = (float)0.0;
            }
            else
            {
                model_ori_data[0] = (float)Math.Atan2(-rot_data[1, 2], rot_data[2, 2]);
                model_ori_data[1] = (float)Math.Asin(rot_data[0, 2]);
                model_ori_data[2] = (float)Math.Atan2(-rot_data[0, 1], rot_data[0, 0]);
                if (model_ori_data[1] > Math.PI / 2.0) {
                    model_ori_data[0] = model_ori_data[0] + (float)Math.PI;
                    model_ori_data[1] = model_ori_data[1] - (float)Math.PI;
                    model_ori_data[2] = model_ori_data[2] + (float)Math.PI;
                    if (model_ori_data[0] > Math.PI) model_ori_data[0] = model_ori_data[0] - (float)Math.PI * 2.0f;
                    if (model_ori_data[0] < -Math.PI) model_ori_data[0] = model_ori_data[0] + (float)Math.PI * 2.0f;
                    if (model_ori_data[2] > Math.PI) model_ori_data[2] = model_ori_data[2] - (float)Math.PI * 2.0f;
                    if (model_ori_data[2] < -Math.PI) model_ori_data[2] = model_ori_data[2] + (float)Math.PI * 2.0f;
                } else if (model_ori_data[1] < -Math.PI / 2.0) {
                    model_ori_data[0] = model_ori_data[0] + (float)Math.PI;
                    model_ori_data[1] = model_ori_data[1] + (float)Math.PI;
                    model_ori_data[2] = model_ori_data[2] + (float)Math.PI;
                    if (model_ori_data[0] > Math.PI) model_ori_data[0] = model_ori_data[0] - (float)Math.PI * 2.0f;
                    if (model_ori_data[0] < -Math.PI) model_ori_data[0] = model_ori_data[0] + (float)Math.PI * 2.0f;
                    if (model_ori_data[2] > Math.PI) model_ori_data[2] = model_ori_data[2] - (float)Math.PI * 2.0f;
                    if (model_ori_data[2] < -Math.PI) model_ori_data[2] = model_ori_data[2] + (float)Math.PI * 2.0f;
                }
            }

        }

        private void calc_quat2zyx()
        {
            model_ori_data[0] = (float)Math.Atan2(rot_data[2, 1], rot_data[2, 2]);
            model_ori_data[1] = (float)Math.Asin(-rot_data[2, 0]);
            model_ori_data[2] = (float)Math.Atan2(-rot_data[1, 0], rot_data[0, 0]);
        }

        private void calc_quat2zxy()
        {
            model_ori_data[0] = (float)Math.Asin(-rot_data[2, 1]);
            model_ori_data[1] = (float)Math.Atan2(rot_data[2, 0], rot_data[2, 2]);
            model_ori_data[2] = (float)Math.Atan2(rot_data[0, 1], rot_data[1, 1]);
        }

        private void SAVE_BUTTON_Click(object sender, EventArgs e)
        {
            string textdata = "";
            for (int i = 0; i < 10; i++) textdata += save_data[i];       //stateデータの保存
            textdata += "\r\n";
            data_save(textdata, "log_data");
        }
        private void data_save(string data, string title)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.FileName = title + ".csv";
            //はじめに表示されるフォルダを指定する
            sfd.InitialDirectory = @"C:\Users\H_M\Desktop";
            sfd.Filter =
                "csvファイル(*.csv)|*.csv|textファイル(*.text)|*.text|nmeaファイル(*.nmea)|*.nmea|すべてのファイル(*.*)|*.*";
            sfd.FilterIndex = 1;
            sfd.Title = "保存先のファイルを選択してください";
            sfd.RestoreDirectory = true;
            sfd.OverwritePrompt = true;
            sfd.CheckPathExists = true;
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                System.IO.StreamWriter sw = new System.IO.StreamWriter(
                    sfd.FileName,
                    false,
                    System.Text.Encoding.GetEncoding("shift_jis"));
                sw.Write(data);
                sw.Close();
            }
        }

        public int statuspc = 0;
        float[] textbox_val = new float[100];

        private void send_outputdata()
        {
            const int DataLength = 49;
            ushort ushTmp;
            byte[] s_uchMsg = new byte[54];
            string text_tmp = "";
            float j = 0.0f;
            ushort k = 0;
            float val_tmp = 0.0f;
            s_uchMsg[0] = 0xa5;
            s_uchMsg[1] = 0x5a;

            s_uchMsg[2] = 0x80;
            s_uchMsg[3] = 0x31;

            //ステータス
            text_tmp = PCSTATUS_TEXTBOX.Text;
            if (ushort.TryParse(text_tmp, out k)) textbox_val[0] = ushort.Parse(text_tmp);
            statuspc = (int)textbox_val[0];
            s_uchMsg[4] = (byte)(statuspc);

            //時間
            ushTmp = (ushort)(time / 600.0 * 65535.0);
            s_uchMsg[5] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[6] = (byte)(ushTmp & 0x00ff);

            //加速度xダミーデータ
            text_tmp = ACCX_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[1] = float.Parse(text_tmp);
            ushTmp = (ushort)( (double)(10.0 + 16.0) / 32.0 * 65535.0);
            s_uchMsg[7] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[8] = (byte)(ushTmp & 0x00ff);

            //加速度yダミーデータ
            text_tmp = ACCY_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[2] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[9] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[10] = (byte)(ushTmp & 0x00ff);

            //加速度zダミーデータ
            text_tmp = ACCZ_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[3] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[11] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[12] = (byte)(ushTmp & 0x00ff);

            //速度xダミーデータ
            text_tmp = VX_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[4] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[13] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[14] = (byte)(ushTmp & 0x00ff);

            //速度yダミーデータ
            text_tmp = VY_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[5] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[15] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[16] = (byte)(ushTmp & 0x00ff);

            //速度zダミーデータ
            text_tmp = VZ_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[6] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[17] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[18] = (byte)(ushTmp & 0x00ff);

            //位置xダミーデータ
            text_tmp = POSX_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[7] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[19] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[20] = (byte)(ushTmp & 0x00ff);

            //位置yダミーデータ
            text_tmp = POSY_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[8] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[21] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[22] = (byte)(ushTmp & 0x00ff);

            //位置zダミーデータ
            text_tmp = POSZ_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[9] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[23] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[24] = (byte)(ushTmp & 0x00ff);

            //角速度xダミーデータ
            text_tmp = GYROX_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[10] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[25] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[26] = (byte)(ushTmp & 0x00ff);

            //角速度yダミーデータ
            text_tmp = GYROY_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[11] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[27] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[28] = (byte)(ushTmp & 0x00ff);

            //角速度zダミーデータ
            text_tmp = GYROZ_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[12] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[29] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[30] = (byte)(ushTmp & 0x00ff);

            //角度xダミーデータ
            text_tmp = EULERX_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[13] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[31] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[32] = (byte)(ushTmp & 0x00ff);

            //角度yダミーデータ
            text_tmp = EULERY_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[14] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[33] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[34] = (byte)(ushTmp & 0x00ff);

            //角度zダミーデータ
            text_tmp = EULERZ_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[15] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[35] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[36] = (byte)(ushTmp & 0x00ff);

            //対気速度ダミーデータ
            text_tmp = AIRVEL_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[16] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[37] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[38] = (byte)(ushTmp & 0x00ff);

            //quat_aダミーデータ
            text_tmp = IRA_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[17] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[39] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[40] = (byte)(ushTmp & 0x00ff);

            //quat_bダミーデータ
            text_tmp = IRB_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[18] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[41] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[42] = (byte)(ushTmp & 0x00ff);

            //quat_cダミーデータ
            text_tmp = IRC_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[19] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[43] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[44] = (byte)(ushTmp & 0x00ff);

            //quat_dダミーデータ
            text_tmp = IRD_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[20] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(0.0) / 100.0 * 65535.0);
            s_uchMsg[45] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[46] = (byte)(ushTmp & 0x00ff);



            //elevonn_Rダミーデータ
            text_tmp = ELEVONR_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[21] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(textbox_val[21] + 60.0) / 120.0 * 65535.0);
            s_uchMsg[47] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[48] = (byte)(ushTmp & 0x00ff);


            //elevonn_Lダミーデータ
            text_tmp = ELEVONL_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[22] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(textbox_val[22] + 60.0) / 120.0 * 65535.0);
            s_uchMsg[49] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[50] = (byte)(ushTmp & 0x00ff);

            //parachuteダミーデータ
            text_tmp = PARACHUTE_TEXTBOX.Text;
            if (float.TryParse(text_tmp, out j)) textbox_val[23] = float.Parse(text_tmp);
            ushTmp = (ushort)((double)(textbox_val[23] + 0.0) / 1.0 * 65535.0);
            s_uchMsg[51] = (byte)(ushTmp >> 8 & 0x00ff);
            s_uchMsg[52] = (byte)(ushTmp & 0x00ff);

            
            int tmp_checksum = 0;
            int i = 0;
            for (i = 4; i < (DataLength + 4); i++)
            {
                tmp_checksum = tmp_checksum ^ (int)s_uchMsg[i];
            }
            s_uchMsg[53] = (byte)tmp_checksum;



            //! シリアルポートからテキストを送信する.
            GETDATA1_SERIALPORT.Write(s_uchMsg,0,54);

            timer_cnt4 = 0;
        }

        private void soft_sim()//シミュレーションの制御ルーチン
        {
            calculation();
            if (timer_cnt1 == (int)(0.02 / dt)) control_law();
            if (timer_cnt2 == (int)(0.02 / dt)) data_save();
            if (timer_cnt3 == (int)(0.02  / dt)) display();
            if (timer_cnt4 == (int)(0.2 / dt)) send_outputdata();
        }

        private void timer_cnt()
        {
            timer_cnt1++;
            timer_cnt2++;
            timer_cnt3++;
            timer_cnt4++;
            time = time + dt;
        }

        private void timer1()
        {
            timer_cnt();
            soft_sim();              
        }

        private void START_BUTTON_Click(object sender, EventArgs e)
        {
            STATUS_LABEL.Text = string.Format("Plot Now");
            Sim_Initialize();
            timer4.Enabled = true;
            START_BUTTON.Enabled = false; //無効にする
            STOP_BUTTON.Enabled = true; //有効にする
            COMPORT_SET_BUTTON.Enabled = false; //無効にする
        }

        private void timer4_OnTimer(object sender)
        {
            //timer1();
            this.Invoke(new timer1Delegate(timer1), null);
        }

        private void STOP_BUTTON_Click(object sender, EventArgs e)
        {
            STATUS_LABEL.Text = string.Format("Plot Stoped");
            timer4.Enabled = false;
            START_BUTTON.Enabled = true; //有効にする
            STOP_BUTTON.Enabled = false; //無効にする
            COMPORT_SET_BUTTON.Enabled = true; //有効にする
        }

    }
}
