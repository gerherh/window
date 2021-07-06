
namespace WindowPart
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.left_button = new System.Windows.Forms.Button();
            this.right_button = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.us_cm_label = new System.Windows.Forms.Label();
            this.auto_button = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.port_combo = new System.Windows.Forms.ComboBox();
            this.comport_label = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.baud_rate_combo = new System.Windows.Forms.ComboBox();
            this.connect_button = new System.Windows.Forms.Button();
            this.disconnect_button = new System.Windows.Forms.Button();
            this.auto_stop_button = new System.Windows.Forms.Button();
            this.serviceController1 = new System.ServiceProcess.ServiceController();
            this.SuspendLayout();
            // 
            // left_button
            // 
            this.left_button.Location = new System.Drawing.Point(12, 367);
            this.left_button.Name = "left_button";
            this.left_button.Size = new System.Drawing.Size(117, 71);
            this.left_button.TabIndex = 0;
            this.left_button.Text = "왼쪽";
            this.left_button.UseVisualStyleBackColor = true;
            this.left_button.Click += new System.EventHandler(this.left_button_Click);
            // 
            // right_button
            // 
            this.right_button.Location = new System.Drawing.Point(135, 367);
            this.right_button.Name = "right_button";
            this.right_button.Size = new System.Drawing.Size(109, 71);
            this.right_button.TabIndex = 1;
            this.right_button.Text = "오른쪽";
            this.right_button.UseVisualStyleBackColor = true;
            this.right_button.Click += new System.EventHandler(this.right_button_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("굴림", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label1.Location = new System.Drawing.Point(665, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(64, 32);
            this.label1.TabIndex = 2;
            this.label1.Text = "CM";
            // 
            // us_cm_label
            // 
            this.us_cm_label.AutoSize = true;
            this.us_cm_label.Font = new System.Drawing.Font("굴림", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.us_cm_label.Location = new System.Drawing.Point(584, 29);
            this.us_cm_label.Name = "us_cm_label";
            this.us_cm_label.Size = new System.Drawing.Size(33, 32);
            this.us_cm_label.TabIndex = 3;
            this.us_cm_label.Text = "0";
            // 
            // auto_button
            // 
            this.auto_button.Location = new System.Drawing.Point(250, 367);
            this.auto_button.Name = "auto_button";
            this.auto_button.Size = new System.Drawing.Size(109, 71);
            this.auto_button.TabIndex = 4;
            this.auto_button.Text = "자동";
            this.auto_button.UseVisualStyleBackColor = true;
            this.auto_button.Click += new System.EventHandler(this.auto_button_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // port_combo
            // 
            this.port_combo.FormattingEnabled = true;
            this.port_combo.Items.AddRange(new object[] {
            "COM1",
            "COM2",
            "COM3",
            "COM4"});
            this.port_combo.Location = new System.Drawing.Point(90, 12);
            this.port_combo.Name = "port_combo";
            this.port_combo.Size = new System.Drawing.Size(121, 20);
            this.port_combo.TabIndex = 5;
            // 
            // comport_label
            // 
            this.comport_label.AutoSize = true;
            this.comport_label.Font = new System.Drawing.Font("굴림", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.comport_label.Location = new System.Drawing.Point(5, 16);
            this.comport_label.Name = "comport_label";
            this.comport_label.Size = new System.Drawing.Size(79, 16);
            this.comport_label.TabIndex = 6;
            this.comport_label.Text = "COM Port";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("굴림", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label2.Location = new System.Drawing.Point(5, 45);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 16);
            this.label2.TabIndex = 7;
            this.label2.Text = "Baud Rate";
            // 
            // baud_rate_combo
            // 
            this.baud_rate_combo.FormattingEnabled = true;
            this.baud_rate_combo.Items.AddRange(new object[] {
            "9600",
            "115200"});
            this.baud_rate_combo.Location = new System.Drawing.Point(90, 43);
            this.baud_rate_combo.Name = "baud_rate_combo";
            this.baud_rate_combo.Size = new System.Drawing.Size(121, 20);
            this.baud_rate_combo.TabIndex = 8;
            // 
            // connect_button
            // 
            this.connect_button.Location = new System.Drawing.Point(8, 85);
            this.connect_button.Name = "connect_button";
            this.connect_button.Size = new System.Drawing.Size(75, 23);
            this.connect_button.TabIndex = 9;
            this.connect_button.Text = "연결";
            this.connect_button.UseVisualStyleBackColor = true;
            this.connect_button.Click += new System.EventHandler(this.connect_button_click);
            // 
            // disconnect_button
            // 
            this.disconnect_button.Location = new System.Drawing.Point(90, 85);
            this.disconnect_button.Name = "disconnect_button";
            this.disconnect_button.Size = new System.Drawing.Size(75, 23);
            this.disconnect_button.TabIndex = 10;
            this.disconnect_button.Text = "끊기";
            this.disconnect_button.UseVisualStyleBackColor = true;
            this.disconnect_button.Click += new System.EventHandler(this.disconnect_button_click);
            // 
            // auto_stop_button
            // 
            this.auto_stop_button.Location = new System.Drawing.Point(365, 367);
            this.auto_stop_button.Name = "auto_stop_button";
            this.auto_stop_button.Size = new System.Drawing.Size(109, 71);
            this.auto_stop_button.TabIndex = 11;
            this.auto_stop_button.Text = "자동 중지";
            this.auto_stop_button.UseVisualStyleBackColor = true;
            this.auto_stop_button.Click += new System.EventHandler(this.auto_stop_button_click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.auto_stop_button);
            this.Controls.Add(this.disconnect_button);
            this.Controls.Add(this.connect_button);
            this.Controls.Add(this.baud_rate_combo);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.comport_label);
            this.Controls.Add(this.port_combo);
            this.Controls.Add(this.auto_button);
            this.Controls.Add(this.us_cm_label);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.right_button);
            this.Controls.Add(this.left_button);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button left_button;
        private System.Windows.Forms.Button right_button;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label us_cm_label;
        private System.Windows.Forms.Button auto_button;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.ComboBox port_combo;
        private System.Windows.Forms.Label comport_label;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox baud_rate_combo;
        private System.Windows.Forms.Button connect_button;
        private System.Windows.Forms.Button disconnect_button;
        private System.Windows.Forms.Button auto_stop_button;
        private System.ServiceProcess.ServiceController serviceController1;
    }
}

