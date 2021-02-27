namespace control_center
{
    partial class Form1
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series4 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.GETDATA1_SERIALPORT = new System.IO.Ports.SerialPort(this.components);
            this.COMPORT_BOX = new System.Windows.Forms.ComboBox();
            this.COMPORT_SET_BUTTON = new System.Windows.Forms.Button();
            this.TIME_LABEL = new System.Windows.Forms.Label();
            this.START_BUTTON = new System.Windows.Forms.Button();
            this.BAUDRATE_BOX = new System.Windows.Forms.ComboBox();
            this.CON_BOX = new System.Windows.Forms.ComboBox();
            this.SEND_DATA_TEXTBOX = new System.Windows.Forms.TextBox();
            this.RECEVED_DATA_TEXTBOX = new System.Windows.Forms.TextBox();
            this.SEND_DATA_LABEL = new System.Windows.Forms.Label();
            this.RECEVED_DATA_LABEL = new System.Windows.Forms.Label();
            this.STOP_BUTTON = new System.Windows.Forms.Button();
            this.SAVE_BUTTON = new System.Windows.Forms.Button();
            this.STATUS_LABEL = new System.Windows.Forms.Label();
            this.plot_data = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.TWESTATUS_LABEL = new System.Windows.Forms.Label();
            this.TEENSYSTATUS_LABEL = new System.Windows.Forms.Label();
            this.ACCY_LABEL = new System.Windows.Forms.Label();
            this.ACCX_LABEL = new System.Windows.Forms.Label();
            this.ACCZ_LABEL = new System.Windows.Forms.Label();
            this.VZ_LABEL = new System.Windows.Forms.Label();
            this.VY_LABEL = new System.Windows.Forms.Label();
            this.VX_LABEL = new System.Windows.Forms.Label();
            this.POSZ_LABEL = new System.Windows.Forms.Label();
            this.POSY_LABEL = new System.Windows.Forms.Label();
            this.POSX_LABEL = new System.Windows.Forms.Label();
            this.AIRVEL_LABEL = new System.Windows.Forms.Label();
            this.EULERZ_LABEL = new System.Windows.Forms.Label();
            this.EULERY_LABEL = new System.Windows.Forms.Label();
            this.EULERX_LABEL = new System.Windows.Forms.Label();
            this.GYROZ_LABEL = new System.Windows.Forms.Label();
            this.GYROY_LABEL = new System.Windows.Forms.Label();
            this.GYROX_LABEL = new System.Windows.Forms.Label();
            this.IRC_LABEL = new System.Windows.Forms.Label();
            this.IRB_LABEL = new System.Windows.Forms.Label();
            this.IRA_LABEL = new System.Windows.Forms.Label();
            this.IRD_LABEL = new System.Windows.Forms.Label();
            this.TWETIME_LABEL = new System.Windows.Forms.Label();
            this.TEENSYTIME_LABEL = new System.Windows.Forms.Label();
            this.ACCX_TEXTBOX = new System.Windows.Forms.TextBox();
            this.ACCY_TEXTBOX = new System.Windows.Forms.TextBox();
            this.ACCZ_TEXTBOX = new System.Windows.Forms.TextBox();
            this.VZ_TEXTBOX = new System.Windows.Forms.TextBox();
            this.VY_TEXTBOX = new System.Windows.Forms.TextBox();
            this.VX_TEXTBOX = new System.Windows.Forms.TextBox();
            this.POSZ_TEXTBOX = new System.Windows.Forms.TextBox();
            this.POSY_TEXTBOX = new System.Windows.Forms.TextBox();
            this.POSX_TEXTBOX = new System.Windows.Forms.TextBox();
            this.IRD_TEXTBOX = new System.Windows.Forms.TextBox();
            this.IRC_TEXTBOX = new System.Windows.Forms.TextBox();
            this.IRB_TEXTBOX = new System.Windows.Forms.TextBox();
            this.IRA_TEXTBOX = new System.Windows.Forms.TextBox();
            this.GYROZ_TEXTBOX = new System.Windows.Forms.TextBox();
            this.GYROY_TEXTBOX = new System.Windows.Forms.TextBox();
            this.GYROX_TEXTBOX = new System.Windows.Forms.TextBox();
            this.EULERZ_TEXTBOX = new System.Windows.Forms.TextBox();
            this.EULERY_TEXTBOX = new System.Windows.Forms.TextBox();
            this.EULERX_TEXTBOX = new System.Windows.Forms.TextBox();
            this.AIRVEL_TEXTBOX = new System.Windows.Forms.TextBox();
            this.PARACHUTE_TEXTBOX = new System.Windows.Forms.TextBox();
            this.ELEVONL_TEXTBOX = new System.Windows.Forms.TextBox();
            this.ELEVONR_TEXTBOX = new System.Windows.Forms.TextBox();
            this.PARACHUTE_LABEL = new System.Windows.Forms.Label();
            this.ELEVONL_LABEL = new System.Windows.Forms.Label();
            this.ELEVONR_LABEL = new System.Windows.Forms.Label();
            this.PCSTATUS_TEXTBOX = new System.Windows.Forms.TextBox();
            this.PCSTATUS_LABEL = new System.Windows.Forms.Label();
            this.plot_data2 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.timer4 = new control_center.MultiMediaTimerComponent(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.plot_data)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.plot_data2)).BeginInit();
            this.SuspendLayout();
            // 
            // GETDATA1_SERIALPORT
            // 
            this.GETDATA1_SERIALPORT.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.GETDATA1_SERIALPORT_DataReceived);
            // 
            // COMPORT_BOX
            // 
            this.COMPORT_BOX.FormattingEnabled = true;
            this.COMPORT_BOX.Location = new System.Drawing.Point(7, 11);
            this.COMPORT_BOX.Name = "COMPORT_BOX";
            this.COMPORT_BOX.Size = new System.Drawing.Size(70, 20);
            this.COMPORT_BOX.TabIndex = 1;
            // 
            // COMPORT_SET_BUTTON
            // 
            this.COMPORT_SET_BUTTON.Location = new System.Drawing.Point(160, 37);
            this.COMPORT_SET_BUTTON.Name = "COMPORT_SET_BUTTON";
            this.COMPORT_SET_BUTTON.Size = new System.Drawing.Size(98, 23);
            this.COMPORT_SET_BUTTON.TabIndex = 2;
            this.COMPORT_SET_BUTTON.Text = "CONNECT";
            this.COMPORT_SET_BUTTON.UseVisualStyleBackColor = true;
            this.COMPORT_SET_BUTTON.Click += new System.EventHandler(this.COMPORT_SET_BUTTON_Click);
            // 
            // TIME_LABEL
            // 
            this.TIME_LABEL.AutoSize = true;
            this.TIME_LABEL.Location = new System.Drawing.Point(12, 63);
            this.TIME_LABEL.Name = "TIME_LABEL";
            this.TIME_LABEL.Size = new System.Drawing.Size(33, 12);
            this.TIME_LABEL.TabIndex = 4;
            this.TIME_LABEL.Text = "TIME:";
            // 
            // START_BUTTON
            // 
            this.START_BUTTON.Location = new System.Drawing.Point(7, 37);
            this.START_BUTTON.Name = "START_BUTTON";
            this.START_BUTTON.Size = new System.Drawing.Size(75, 23);
            this.START_BUTTON.TabIndex = 5;
            this.START_BUTTON.Text = "START";
            this.START_BUTTON.UseVisualStyleBackColor = true;
            this.START_BUTTON.Click += new System.EventHandler(this.START_BUTTON_Click);
            // 
            // BAUDRATE_BOX
            // 
            this.BAUDRATE_BOX.FormattingEnabled = true;
            this.BAUDRATE_BOX.Location = new System.Drawing.Point(83, 11);
            this.BAUDRATE_BOX.Name = "BAUDRATE_BOX";
            this.BAUDRATE_BOX.Size = new System.Drawing.Size(97, 20);
            this.BAUDRATE_BOX.TabIndex = 6;
            // 
            // CON_BOX
            // 
            this.CON_BOX.FormattingEnabled = true;
            this.CON_BOX.Location = new System.Drawing.Point(191, 11);
            this.CON_BOX.Name = "CON_BOX";
            this.CON_BOX.Size = new System.Drawing.Size(122, 20);
            this.CON_BOX.TabIndex = 7;
            // 
            // SEND_DATA_TEXTBOX
            // 
            this.SEND_DATA_TEXTBOX.Location = new System.Drawing.Point(12, 165);
            this.SEND_DATA_TEXTBOX.Multiline = true;
            this.SEND_DATA_TEXTBOX.Name = "SEND_DATA_TEXTBOX";
            this.SEND_DATA_TEXTBOX.Size = new System.Drawing.Size(160, 160);
            this.SEND_DATA_TEXTBOX.TabIndex = 8;
            // 
            // RECEVED_DATA_TEXTBOX
            // 
            this.RECEVED_DATA_TEXTBOX.Location = new System.Drawing.Point(181, 165);
            this.RECEVED_DATA_TEXTBOX.Multiline = true;
            this.RECEVED_DATA_TEXTBOX.Name = "RECEVED_DATA_TEXTBOX";
            this.RECEVED_DATA_TEXTBOX.Size = new System.Drawing.Size(160, 160);
            this.RECEVED_DATA_TEXTBOX.TabIndex = 9;
            // 
            // SEND_DATA_LABEL
            // 
            this.SEND_DATA_LABEL.AutoSize = true;
            this.SEND_DATA_LABEL.Location = new System.Drawing.Point(12, 150);
            this.SEND_DATA_LABEL.Name = "SEND_DATA_LABEL";
            this.SEND_DATA_LABEL.Size = new System.Drawing.Size(70, 12);
            this.SEND_DATA_LABEL.TabIndex = 10;
            this.SEND_DATA_LABEL.Text = "SEND DATA";
            this.SEND_DATA_LABEL.Click += new System.EventHandler(this.SEND_DATA_LABEL_Click);
            // 
            // RECEVED_DATA_LABEL
            // 
            this.RECEVED_DATA_LABEL.AutoSize = true;
            this.RECEVED_DATA_LABEL.Location = new System.Drawing.Point(179, 150);
            this.RECEVED_DATA_LABEL.Name = "RECEVED_DATA_LABEL";
            this.RECEVED_DATA_LABEL.Size = new System.Drawing.Size(93, 12);
            this.RECEVED_DATA_LABEL.TabIndex = 11;
            this.RECEVED_DATA_LABEL.Text = "RECEVED DATA";
            // 
            // STOP_BUTTON
            // 
            this.STOP_BUTTON.Location = new System.Drawing.Point(83, 37);
            this.STOP_BUTTON.Name = "STOP_BUTTON";
            this.STOP_BUTTON.Size = new System.Drawing.Size(75, 23);
            this.STOP_BUTTON.TabIndex = 12;
            this.STOP_BUTTON.Text = "STOP";
            this.STOP_BUTTON.UseVisualStyleBackColor = true;
            this.STOP_BUTTON.Click += new System.EventHandler(this.STOP_BUTTON_Click);
            // 
            // SAVE_BUTTON
            // 
            this.SAVE_BUTTON.Location = new System.Drawing.Point(260, 37);
            this.SAVE_BUTTON.Name = "SAVE_BUTTON";
            this.SAVE_BUTTON.Size = new System.Drawing.Size(81, 23);
            this.SAVE_BUTTON.TabIndex = 13;
            this.SAVE_BUTTON.Text = "SAVE";
            this.SAVE_BUTTON.UseVisualStyleBackColor = true;
            this.SAVE_BUTTON.Click += new System.EventHandler(this.SAVE_BUTTON_Click);
            // 
            // STATUS_LABEL
            // 
            this.STATUS_LABEL.AutoSize = true;
            this.STATUS_LABEL.Location = new System.Drawing.Point(14, 79);
            this.STATUS_LABEL.Name = "STATUS_LABEL";
            this.STATUS_LABEL.Size = new System.Drawing.Size(49, 12);
            this.STATUS_LABEL.TabIndex = 14;
            this.STATUS_LABEL.Text = "STATUS";
            // 
            // plot_data
            // 
            chartArea1.AxisY.LabelStyle.Format = "{0:F0}";
            chartArea1.Name = "ChartArea1";
            this.plot_data.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.plot_data.Legends.Add(legend1);
            this.plot_data.Location = new System.Drawing.Point(347, 5);
            this.plot_data.Name = "plot_data";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastPoint;
            series1.Legend = "Legend1";
            series1.Name = "data1";
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastPoint;
            series2.Legend = "Legend1";
            series2.Name = "data2";
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastPoint;
            series3.Legend = "Legend1";
            series3.Name = "data3";
            this.plot_data.Series.Add(series1);
            this.plot_data.Series.Add(series2);
            this.plot_data.Series.Add(series3);
            this.plot_data.Size = new System.Drawing.Size(458, 168);
            this.plot_data.TabIndex = 38;
            this.plot_data.Text = "XI ETA";
            // 
            // TWESTATUS_LABEL
            // 
            this.TWESTATUS_LABEL.AutoSize = true;
            this.TWESTATUS_LABEL.Location = new System.Drawing.Point(14, 338);
            this.TWESTATUS_LABEL.Name = "TWESTATUS_LABEL";
            this.TWESTATUS_LABEL.Size = new System.Drawing.Size(63, 12);
            this.TWESTATUS_LABEL.TabIndex = 45;
            this.TWESTATUS_LABEL.Text = "Twe Status";
            // 
            // TEENSYSTATUS_LABEL
            // 
            this.TEENSYSTATUS_LABEL.AutoSize = true;
            this.TEENSYSTATUS_LABEL.Location = new System.Drawing.Point(12, 374);
            this.TEENSYSTATUS_LABEL.Name = "TEENSYSTATUS_LABEL";
            this.TEENSYSTATUS_LABEL.Size = new System.Drawing.Size(79, 12);
            this.TEENSYSTATUS_LABEL.TabIndex = 46;
            this.TEENSYSTATUS_LABEL.Text = "Teensy Status";
            // 
            // ACCY_LABEL
            // 
            this.ACCY_LABEL.AutoSize = true;
            this.ACCY_LABEL.Location = new System.Drawing.Point(190, 360);
            this.ACCY_LABEL.Name = "ACCY_LABEL";
            this.ACCY_LABEL.Size = new System.Drawing.Size(33, 12);
            this.ACCY_LABEL.TabIndex = 48;
            this.ACCY_LABEL.Text = "acc y";
            // 
            // ACCX_LABEL
            // 
            this.ACCX_LABEL.AutoSize = true;
            this.ACCX_LABEL.Location = new System.Drawing.Point(190, 338);
            this.ACCX_LABEL.Name = "ACCX_LABEL";
            this.ACCX_LABEL.Size = new System.Drawing.Size(33, 12);
            this.ACCX_LABEL.TabIndex = 47;
            this.ACCX_LABEL.Text = "acc x";
            // 
            // ACCZ_LABEL
            // 
            this.ACCZ_LABEL.AutoSize = true;
            this.ACCZ_LABEL.Location = new System.Drawing.Point(191, 383);
            this.ACCZ_LABEL.Name = "ACCZ_LABEL";
            this.ACCZ_LABEL.Size = new System.Drawing.Size(32, 12);
            this.ACCZ_LABEL.TabIndex = 49;
            this.ACCZ_LABEL.Text = "acc z";
            // 
            // VZ_LABEL
            // 
            this.VZ_LABEL.AutoSize = true;
            this.VZ_LABEL.Location = new System.Drawing.Point(361, 383);
            this.VZ_LABEL.Name = "VZ_LABEL";
            this.VZ_LABEL.Size = new System.Drawing.Size(20, 12);
            this.VZ_LABEL.TabIndex = 52;
            this.VZ_LABEL.Text = "v z";
            // 
            // VY_LABEL
            // 
            this.VY_LABEL.AutoSize = true;
            this.VY_LABEL.Location = new System.Drawing.Point(360, 360);
            this.VY_LABEL.Name = "VY_LABEL";
            this.VY_LABEL.Size = new System.Drawing.Size(21, 12);
            this.VY_LABEL.TabIndex = 51;
            this.VY_LABEL.Text = "v y";
            // 
            // VX_LABEL
            // 
            this.VX_LABEL.AutoSize = true;
            this.VX_LABEL.Location = new System.Drawing.Point(360, 338);
            this.VX_LABEL.Name = "VX_LABEL";
            this.VX_LABEL.Size = new System.Drawing.Size(21, 12);
            this.VX_LABEL.TabIndex = 50;
            this.VX_LABEL.Text = "v x";
            // 
            // POSZ_LABEL
            // 
            this.POSZ_LABEL.AutoSize = true;
            this.POSZ_LABEL.Location = new System.Drawing.Point(502, 386);
            this.POSZ_LABEL.Name = "POSZ_LABEL";
            this.POSZ_LABEL.Size = new System.Drawing.Size(32, 12);
            this.POSZ_LABEL.TabIndex = 55;
            this.POSZ_LABEL.Text = "pos z";
            // 
            // POSY_LABEL
            // 
            this.POSY_LABEL.AutoSize = true;
            this.POSY_LABEL.Location = new System.Drawing.Point(502, 363);
            this.POSY_LABEL.Name = "POSY_LABEL";
            this.POSY_LABEL.Size = new System.Drawing.Size(33, 12);
            this.POSY_LABEL.TabIndex = 54;
            this.POSY_LABEL.Text = "pos y";
            // 
            // POSX_LABEL
            // 
            this.POSX_LABEL.AutoSize = true;
            this.POSX_LABEL.Location = new System.Drawing.Point(502, 338);
            this.POSX_LABEL.Name = "POSX_LABEL";
            this.POSX_LABEL.Size = new System.Drawing.Size(33, 12);
            this.POSX_LABEL.TabIndex = 53;
            this.POSX_LABEL.Text = "pos x";
            // 
            // AIRVEL_LABEL
            // 
            this.AIRVEL_LABEL.AutoSize = true;
            this.AIRVEL_LABEL.Location = new System.Drawing.Point(502, 466);
            this.AIRVEL_LABEL.Name = "AIRVEL_LABEL";
            this.AIRVEL_LABEL.Size = new System.Drawing.Size(66, 12);
            this.AIRVEL_LABEL.TabIndex = 62;
            this.AIRVEL_LABEL.Text = "Air Velocity";
            // 
            // EULERZ_LABEL
            // 
            this.EULERZ_LABEL.AutoSize = true;
            this.EULERZ_LABEL.Location = new System.Drawing.Point(342, 489);
            this.EULERZ_LABEL.Name = "EULERZ_LABEL";
            this.EULERZ_LABEL.Size = new System.Drawing.Size(39, 12);
            this.EULERZ_LABEL.TabIndex = 61;
            this.EULERZ_LABEL.Text = "euler z";
            // 
            // EULERY_LABEL
            // 
            this.EULERY_LABEL.AutoSize = true;
            this.EULERY_LABEL.Location = new System.Drawing.Point(342, 466);
            this.EULERY_LABEL.Name = "EULERY_LABEL";
            this.EULERY_LABEL.Size = new System.Drawing.Size(40, 12);
            this.EULERY_LABEL.TabIndex = 60;
            this.EULERY_LABEL.Text = "euler y";
            // 
            // EULERX_LABEL
            // 
            this.EULERX_LABEL.AutoSize = true;
            this.EULERX_LABEL.Location = new System.Drawing.Point(342, 444);
            this.EULERX_LABEL.Name = "EULERX_LABEL";
            this.EULERX_LABEL.Size = new System.Drawing.Size(40, 12);
            this.EULERX_LABEL.TabIndex = 59;
            this.EULERX_LABEL.Text = "euler x";
            // 
            // GYROZ_LABEL
            // 
            this.GYROZ_LABEL.AutoSize = true;
            this.GYROZ_LABEL.Location = new System.Drawing.Point(186, 489);
            this.GYROZ_LABEL.Name = "GYROZ_LABEL";
            this.GYROZ_LABEL.Size = new System.Drawing.Size(36, 12);
            this.GYROZ_LABEL.TabIndex = 58;
            this.GYROZ_LABEL.Text = "gyro z";
            // 
            // GYROY_LABEL
            // 
            this.GYROY_LABEL.AutoSize = true;
            this.GYROY_LABEL.Location = new System.Drawing.Point(186, 466);
            this.GYROY_LABEL.Name = "GYROY_LABEL";
            this.GYROY_LABEL.Size = new System.Drawing.Size(37, 12);
            this.GYROY_LABEL.TabIndex = 57;
            this.GYROY_LABEL.Text = "gyro y";
            // 
            // GYROX_LABEL
            // 
            this.GYROX_LABEL.AutoSize = true;
            this.GYROX_LABEL.Location = new System.Drawing.Point(186, 444);
            this.GYROX_LABEL.Name = "GYROX_LABEL";
            this.GYROX_LABEL.Size = new System.Drawing.Size(37, 12);
            this.GYROX_LABEL.TabIndex = 56;
            this.GYROX_LABEL.Text = "gyro x";
            // 
            // IRC_LABEL
            // 
            this.IRC_LABEL.AutoSize = true;
            this.IRC_LABEL.Location = new System.Drawing.Point(655, 383);
            this.IRC_LABEL.Name = "IRC_LABEL";
            this.IRC_LABEL.Size = new System.Drawing.Size(37, 12);
            this.IRC_LABEL.TabIndex = 65;
            this.IRC_LABEL.Text = "quat c";
            // 
            // IRB_LABEL
            // 
            this.IRB_LABEL.AutoSize = true;
            this.IRB_LABEL.Location = new System.Drawing.Point(655, 360);
            this.IRB_LABEL.Name = "IRB_LABEL";
            this.IRB_LABEL.Size = new System.Drawing.Size(37, 12);
            this.IRB_LABEL.TabIndex = 64;
            this.IRB_LABEL.Text = "quat b";
            // 
            // IRA_LABEL
            // 
            this.IRA_LABEL.AutoSize = true;
            this.IRA_LABEL.Location = new System.Drawing.Point(655, 338);
            this.IRA_LABEL.Name = "IRA_LABEL";
            this.IRA_LABEL.Size = new System.Drawing.Size(37, 12);
            this.IRA_LABEL.TabIndex = 63;
            this.IRA_LABEL.Text = "quat a";
            // 
            // IRD_LABEL
            // 
            this.IRD_LABEL.AutoSize = true;
            this.IRD_LABEL.Location = new System.Drawing.Point(655, 406);
            this.IRD_LABEL.Name = "IRD_LABEL";
            this.IRD_LABEL.Size = new System.Drawing.Size(37, 12);
            this.IRD_LABEL.TabIndex = 66;
            this.IRD_LABEL.Text = "quat d";
            // 
            // TWETIME_LABEL
            // 
            this.TWETIME_LABEL.AutoSize = true;
            this.TWETIME_LABEL.Location = new System.Drawing.Point(14, 350);
            this.TWETIME_LABEL.Name = "TWETIME_LABEL";
            this.TWETIME_LABEL.Size = new System.Drawing.Size(55, 12);
            this.TWETIME_LABEL.TabIndex = 67;
            this.TWETIME_LABEL.Text = "Twe Time";
            // 
            // TEENSYTIME_LABEL
            // 
            this.TEENSYTIME_LABEL.AutoSize = true;
            this.TEENSYTIME_LABEL.Location = new System.Drawing.Point(12, 386);
            this.TEENSYTIME_LABEL.Name = "TEENSYTIME_LABEL";
            this.TEENSYTIME_LABEL.Size = new System.Drawing.Size(71, 12);
            this.TEENSYTIME_LABEL.TabIndex = 68;
            this.TEENSYTIME_LABEL.Text = "Teensy Time";
            // 
            // ACCX_TEXTBOX
            // 
            this.ACCX_TEXTBOX.Location = new System.Drawing.Point(276, 335);
            this.ACCX_TEXTBOX.Name = "ACCX_TEXTBOX";
            this.ACCX_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.ACCX_TEXTBOX.TabIndex = 69;
            // 
            // ACCY_TEXTBOX
            // 
            this.ACCY_TEXTBOX.Location = new System.Drawing.Point(276, 357);
            this.ACCY_TEXTBOX.Name = "ACCY_TEXTBOX";
            this.ACCY_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.ACCY_TEXTBOX.TabIndex = 70;
            // 
            // ACCZ_TEXTBOX
            // 
            this.ACCZ_TEXTBOX.Location = new System.Drawing.Point(276, 380);
            this.ACCZ_TEXTBOX.Name = "ACCZ_TEXTBOX";
            this.ACCZ_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.ACCZ_TEXTBOX.TabIndex = 71;
            // 
            // VZ_TEXTBOX
            // 
            this.VZ_TEXTBOX.Location = new System.Drawing.Point(422, 380);
            this.VZ_TEXTBOX.Name = "VZ_TEXTBOX";
            this.VZ_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.VZ_TEXTBOX.TabIndex = 74;
            // 
            // VY_TEXTBOX
            // 
            this.VY_TEXTBOX.Location = new System.Drawing.Point(422, 357);
            this.VY_TEXTBOX.Name = "VY_TEXTBOX";
            this.VY_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.VY_TEXTBOX.TabIndex = 73;
            // 
            // VX_TEXTBOX
            // 
            this.VX_TEXTBOX.Location = new System.Drawing.Point(422, 335);
            this.VX_TEXTBOX.Name = "VX_TEXTBOX";
            this.VX_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.VX_TEXTBOX.TabIndex = 72;
            // 
            // POSZ_TEXTBOX
            // 
            this.POSZ_TEXTBOX.Location = new System.Drawing.Point(580, 380);
            this.POSZ_TEXTBOX.Name = "POSZ_TEXTBOX";
            this.POSZ_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.POSZ_TEXTBOX.TabIndex = 77;
            // 
            // POSY_TEXTBOX
            // 
            this.POSY_TEXTBOX.Location = new System.Drawing.Point(580, 357);
            this.POSY_TEXTBOX.Name = "POSY_TEXTBOX";
            this.POSY_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.POSY_TEXTBOX.TabIndex = 76;
            // 
            // POSX_TEXTBOX
            // 
            this.POSX_TEXTBOX.Location = new System.Drawing.Point(580, 335);
            this.POSX_TEXTBOX.Name = "POSX_TEXTBOX";
            this.POSX_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.POSX_TEXTBOX.TabIndex = 75;
            // 
            // IRD_TEXTBOX
            // 
            this.IRD_TEXTBOX.Location = new System.Drawing.Point(721, 403);
            this.IRD_TEXTBOX.Name = "IRD_TEXTBOX";
            this.IRD_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.IRD_TEXTBOX.TabIndex = 82;
            // 
            // IRC_TEXTBOX
            // 
            this.IRC_TEXTBOX.Location = new System.Drawing.Point(721, 380);
            this.IRC_TEXTBOX.Name = "IRC_TEXTBOX";
            this.IRC_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.IRC_TEXTBOX.TabIndex = 81;
            // 
            // IRB_TEXTBOX
            // 
            this.IRB_TEXTBOX.Location = new System.Drawing.Point(721, 357);
            this.IRB_TEXTBOX.Name = "IRB_TEXTBOX";
            this.IRB_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.IRB_TEXTBOX.TabIndex = 80;
            // 
            // IRA_TEXTBOX
            // 
            this.IRA_TEXTBOX.Location = new System.Drawing.Point(721, 335);
            this.IRA_TEXTBOX.Name = "IRA_TEXTBOX";
            this.IRA_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.IRA_TEXTBOX.TabIndex = 79;
            // 
            // GYROZ_TEXTBOX
            // 
            this.GYROZ_TEXTBOX.Location = new System.Drawing.Point(276, 486);
            this.GYROZ_TEXTBOX.Name = "GYROZ_TEXTBOX";
            this.GYROZ_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.GYROZ_TEXTBOX.TabIndex = 85;
            // 
            // GYROY_TEXTBOX
            // 
            this.GYROY_TEXTBOX.Location = new System.Drawing.Point(276, 463);
            this.GYROY_TEXTBOX.Name = "GYROY_TEXTBOX";
            this.GYROY_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.GYROY_TEXTBOX.TabIndex = 84;
            // 
            // GYROX_TEXTBOX
            // 
            this.GYROX_TEXTBOX.Location = new System.Drawing.Point(276, 441);
            this.GYROX_TEXTBOX.Name = "GYROX_TEXTBOX";
            this.GYROX_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.GYROX_TEXTBOX.TabIndex = 83;
            // 
            // EULERZ_TEXTBOX
            // 
            this.EULERZ_TEXTBOX.Location = new System.Drawing.Point(422, 486);
            this.EULERZ_TEXTBOX.Name = "EULERZ_TEXTBOX";
            this.EULERZ_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.EULERZ_TEXTBOX.TabIndex = 88;
            // 
            // EULERY_TEXTBOX
            // 
            this.EULERY_TEXTBOX.Location = new System.Drawing.Point(422, 463);
            this.EULERY_TEXTBOX.Name = "EULERY_TEXTBOX";
            this.EULERY_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.EULERY_TEXTBOX.TabIndex = 87;
            // 
            // EULERX_TEXTBOX
            // 
            this.EULERX_TEXTBOX.Location = new System.Drawing.Point(422, 441);
            this.EULERX_TEXTBOX.Name = "EULERX_TEXTBOX";
            this.EULERX_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.EULERX_TEXTBOX.TabIndex = 86;
            // 
            // AIRVEL_TEXTBOX
            // 
            this.AIRVEL_TEXTBOX.Location = new System.Drawing.Point(613, 463);
            this.AIRVEL_TEXTBOX.Name = "AIRVEL_TEXTBOX";
            this.AIRVEL_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.AIRVEL_TEXTBOX.TabIndex = 89;
            // 
            // PARACHUTE_TEXTBOX
            // 
            this.PARACHUTE_TEXTBOX.Location = new System.Drawing.Point(108, 486);
            this.PARACHUTE_TEXTBOX.Name = "PARACHUTE_TEXTBOX";
            this.PARACHUTE_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.PARACHUTE_TEXTBOX.TabIndex = 95;
            // 
            // ELEVONL_TEXTBOX
            // 
            this.ELEVONL_TEXTBOX.Location = new System.Drawing.Point(108, 463);
            this.ELEVONL_TEXTBOX.Name = "ELEVONL_TEXTBOX";
            this.ELEVONL_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.ELEVONL_TEXTBOX.TabIndex = 94;
            // 
            // ELEVONR_TEXTBOX
            // 
            this.ELEVONR_TEXTBOX.Location = new System.Drawing.Point(108, 441);
            this.ELEVONR_TEXTBOX.Name = "ELEVONR_TEXTBOX";
            this.ELEVONR_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.ELEVONR_TEXTBOX.TabIndex = 93;
            // 
            // PARACHUTE_LABEL
            // 
            this.PARACHUTE_LABEL.AutoSize = true;
            this.PARACHUTE_LABEL.Location = new System.Drawing.Point(18, 489);
            this.PARACHUTE_LABEL.Name = "PARACHUTE_LABEL";
            this.PARACHUTE_LABEL.Size = new System.Drawing.Size(55, 12);
            this.PARACHUTE_LABEL.TabIndex = 92;
            this.PARACHUTE_LABEL.Text = "parachute";
            // 
            // ELEVONL_LABEL
            // 
            this.ELEVONL_LABEL.AutoSize = true;
            this.ELEVONL_LABEL.Location = new System.Drawing.Point(18, 466);
            this.ELEVONL_LABEL.Name = "ELEVONL_LABEL";
            this.ELEVONL_LABEL.Size = new System.Drawing.Size(48, 12);
            this.ELEVONL_LABEL.TabIndex = 91;
            this.ELEVONL_LABEL.Text = "elevon L";
            // 
            // ELEVONR_LABEL
            // 
            this.ELEVONR_LABEL.AutoSize = true;
            this.ELEVONR_LABEL.Location = new System.Drawing.Point(18, 444);
            this.ELEVONR_LABEL.Name = "ELEVONR_LABEL";
            this.ELEVONR_LABEL.Size = new System.Drawing.Size(50, 12);
            this.ELEVONR_LABEL.TabIndex = 90;
            this.ELEVONR_LABEL.Text = "elevon R";
            // 
            // PCSTATUS_TEXTBOX
            // 
            this.PCSTATUS_TEXTBOX.Location = new System.Drawing.Point(108, 416);
            this.PCSTATUS_TEXTBOX.Name = "PCSTATUS_TEXTBOX";
            this.PCSTATUS_TEXTBOX.Size = new System.Drawing.Size(50, 19);
            this.PCSTATUS_TEXTBOX.TabIndex = 97;
            // 
            // PCSTATUS_LABEL
            // 
            this.PCSTATUS_LABEL.AutoSize = true;
            this.PCSTATUS_LABEL.Location = new System.Drawing.Point(18, 419);
            this.PCSTATUS_LABEL.Name = "PCSTATUS_LABEL";
            this.PCSTATUS_LABEL.Size = new System.Drawing.Size(55, 12);
            this.PCSTATUS_LABEL.TabIndex = 96;
            this.PCSTATUS_LABEL.Text = "Pc Status";
            // 
            // plot_data2
            // 
            chartArea2.AxisY.LabelStyle.Format = "{0:F0}";
            chartArea2.Name = "ChartArea1";
            this.plot_data2.ChartAreas.Add(chartArea2);
            legend2.Name = "Legend1";
            this.plot_data2.Legends.Add(legend2);
            this.plot_data2.Location = new System.Drawing.Point(347, 179);
            this.plot_data2.Name = "plot_data2";
            series4.ChartArea = "ChartArea1";
            series4.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastPoint;
            series4.Legend = "Legend1";
            series4.Name = "data1";
            this.plot_data2.Series.Add(series4);
            this.plot_data2.Size = new System.Drawing.Size(458, 146);
            this.plot_data2.TabIndex = 99;
            this.plot_data2.Text = "XI ETA";
            // 
            // timer4
            // 
            this.timer4.Enabled = false;
            this.timer4.Interval = ((uint)(1u));
            this.timer4.Resolution = ((uint)(1u));
            this.timer4.OnTimer += new control_center.MultiMediaTimerComponent.TimerDelegate(this.timer4_OnTimer);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(822, 513);
            this.Controls.Add(this.plot_data2);
            this.Controls.Add(this.PCSTATUS_TEXTBOX);
            this.Controls.Add(this.PCSTATUS_LABEL);
            this.Controls.Add(this.PARACHUTE_TEXTBOX);
            this.Controls.Add(this.ELEVONL_TEXTBOX);
            this.Controls.Add(this.ELEVONR_TEXTBOX);
            this.Controls.Add(this.PARACHUTE_LABEL);
            this.Controls.Add(this.ELEVONL_LABEL);
            this.Controls.Add(this.ELEVONR_LABEL);
            this.Controls.Add(this.AIRVEL_TEXTBOX);
            this.Controls.Add(this.EULERZ_TEXTBOX);
            this.Controls.Add(this.EULERY_TEXTBOX);
            this.Controls.Add(this.EULERX_TEXTBOX);
            this.Controls.Add(this.GYROZ_TEXTBOX);
            this.Controls.Add(this.GYROY_TEXTBOX);
            this.Controls.Add(this.GYROX_TEXTBOX);
            this.Controls.Add(this.IRD_TEXTBOX);
            this.Controls.Add(this.IRC_TEXTBOX);
            this.Controls.Add(this.IRB_TEXTBOX);
            this.Controls.Add(this.IRA_TEXTBOX);
            this.Controls.Add(this.POSZ_TEXTBOX);
            this.Controls.Add(this.POSY_TEXTBOX);
            this.Controls.Add(this.POSX_TEXTBOX);
            this.Controls.Add(this.VZ_TEXTBOX);
            this.Controls.Add(this.VY_TEXTBOX);
            this.Controls.Add(this.VX_TEXTBOX);
            this.Controls.Add(this.ACCZ_TEXTBOX);
            this.Controls.Add(this.ACCY_TEXTBOX);
            this.Controls.Add(this.ACCX_TEXTBOX);
            this.Controls.Add(this.TEENSYTIME_LABEL);
            this.Controls.Add(this.TWETIME_LABEL);
            this.Controls.Add(this.IRD_LABEL);
            this.Controls.Add(this.IRC_LABEL);
            this.Controls.Add(this.IRB_LABEL);
            this.Controls.Add(this.IRA_LABEL);
            this.Controls.Add(this.AIRVEL_LABEL);
            this.Controls.Add(this.EULERZ_LABEL);
            this.Controls.Add(this.EULERY_LABEL);
            this.Controls.Add(this.EULERX_LABEL);
            this.Controls.Add(this.GYROZ_LABEL);
            this.Controls.Add(this.GYROY_LABEL);
            this.Controls.Add(this.GYROX_LABEL);
            this.Controls.Add(this.POSZ_LABEL);
            this.Controls.Add(this.POSY_LABEL);
            this.Controls.Add(this.POSX_LABEL);
            this.Controls.Add(this.VZ_LABEL);
            this.Controls.Add(this.VY_LABEL);
            this.Controls.Add(this.VX_LABEL);
            this.Controls.Add(this.ACCZ_LABEL);
            this.Controls.Add(this.ACCY_LABEL);
            this.Controls.Add(this.ACCX_LABEL);
            this.Controls.Add(this.TEENSYSTATUS_LABEL);
            this.Controls.Add(this.TWESTATUS_LABEL);
            this.Controls.Add(this.plot_data);
            this.Controls.Add(this.STATUS_LABEL);
            this.Controls.Add(this.SAVE_BUTTON);
            this.Controls.Add(this.STOP_BUTTON);
            this.Controls.Add(this.RECEVED_DATA_LABEL);
            this.Controls.Add(this.SEND_DATA_LABEL);
            this.Controls.Add(this.RECEVED_DATA_TEXTBOX);
            this.Controls.Add(this.SEND_DATA_TEXTBOX);
            this.Controls.Add(this.CON_BOX);
            this.Controls.Add(this.BAUDRATE_BOX);
            this.Controls.Add(this.START_BUTTON);
            this.Controls.Add(this.TIME_LABEL);
            this.Controls.Add(this.COMPORT_SET_BUTTON);
            this.Controls.Add(this.COMPORT_BOX);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.plot_data)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.plot_data2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.IO.Ports.SerialPort GETDATA1_SERIALPORT;
        private System.Windows.Forms.ComboBox COMPORT_BOX;
        private System.Windows.Forms.Button COMPORT_SET_BUTTON;
        private System.Windows.Forms.Label TIME_LABEL;
        private System.Windows.Forms.Button START_BUTTON;
        private System.Windows.Forms.ComboBox BAUDRATE_BOX;
        private System.Windows.Forms.ComboBox CON_BOX;
        private System.Windows.Forms.TextBox SEND_DATA_TEXTBOX;
        private System.Windows.Forms.TextBox RECEVED_DATA_TEXTBOX;
        private System.Windows.Forms.Label SEND_DATA_LABEL;
        private System.Windows.Forms.Label RECEVED_DATA_LABEL;
        private control_center.MultiMediaTimerComponent timer4;
        private System.Windows.Forms.Button STOP_BUTTON;
        private System.Windows.Forms.Button SAVE_BUTTON;
        private System.Windows.Forms.Label STATUS_LABEL;
        private System.Windows.Forms.DataVisualization.Charting.Chart plot_data;
        private System.Windows.Forms.Label TWESTATUS_LABEL;
        private System.Windows.Forms.Label TEENSYSTATUS_LABEL;
        private System.Windows.Forms.Label ACCY_LABEL;
        private System.Windows.Forms.Label ACCX_LABEL;
        private System.Windows.Forms.Label ACCZ_LABEL;
        private System.Windows.Forms.Label VZ_LABEL;
        private System.Windows.Forms.Label VY_LABEL;
        private System.Windows.Forms.Label VX_LABEL;
        private System.Windows.Forms.Label POSZ_LABEL;
        private System.Windows.Forms.Label POSY_LABEL;
        private System.Windows.Forms.Label POSX_LABEL;
        private System.Windows.Forms.Label AIRVEL_LABEL;
        private System.Windows.Forms.Label EULERZ_LABEL;
        private System.Windows.Forms.Label EULERY_LABEL;
        private System.Windows.Forms.Label EULERX_LABEL;
        private System.Windows.Forms.Label GYROZ_LABEL;
        private System.Windows.Forms.Label GYROY_LABEL;
        private System.Windows.Forms.Label GYROX_LABEL;
        private System.Windows.Forms.Label IRC_LABEL;
        private System.Windows.Forms.Label IRB_LABEL;
        private System.Windows.Forms.Label IRA_LABEL;
        private System.Windows.Forms.Label IRD_LABEL;
        private System.Windows.Forms.Label TWETIME_LABEL;
        private System.Windows.Forms.Label TEENSYTIME_LABEL;
        private System.Windows.Forms.TextBox ACCX_TEXTBOX;
        private System.Windows.Forms.TextBox ACCY_TEXTBOX;
        private System.Windows.Forms.TextBox ACCZ_TEXTBOX;
        private System.Windows.Forms.TextBox VZ_TEXTBOX;
        private System.Windows.Forms.TextBox VY_TEXTBOX;
        private System.Windows.Forms.TextBox VX_TEXTBOX;
        private System.Windows.Forms.TextBox POSZ_TEXTBOX;
        private System.Windows.Forms.TextBox POSY_TEXTBOX;
        private System.Windows.Forms.TextBox POSX_TEXTBOX;
        private System.Windows.Forms.TextBox IRD_TEXTBOX;
        private System.Windows.Forms.TextBox IRC_TEXTBOX;
        private System.Windows.Forms.TextBox IRB_TEXTBOX;
        private System.Windows.Forms.TextBox IRA_TEXTBOX;
        private System.Windows.Forms.TextBox GYROZ_TEXTBOX;
        private System.Windows.Forms.TextBox GYROY_TEXTBOX;
        private System.Windows.Forms.TextBox GYROX_TEXTBOX;
        private System.Windows.Forms.TextBox EULERZ_TEXTBOX;
        private System.Windows.Forms.TextBox EULERY_TEXTBOX;
        private System.Windows.Forms.TextBox EULERX_TEXTBOX;
        private System.Windows.Forms.TextBox AIRVEL_TEXTBOX;
        private System.Windows.Forms.TextBox PARACHUTE_TEXTBOX;
        private System.Windows.Forms.TextBox ELEVONL_TEXTBOX;
        private System.Windows.Forms.TextBox ELEVONR_TEXTBOX;
        private System.Windows.Forms.Label PARACHUTE_LABEL;
        private System.Windows.Forms.Label ELEVONL_LABEL;
        private System.Windows.Forms.Label ELEVONR_LABEL;
        private System.Windows.Forms.TextBox PCSTATUS_TEXTBOX;
        private System.Windows.Forms.Label PCSTATUS_LABEL;
        private System.Windows.Forms.DataVisualization.Charting.Chart plot_data2;
    }
}

