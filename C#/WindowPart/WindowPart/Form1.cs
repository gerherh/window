using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowPart
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        private void connect_button_click(object sender, EventArgs e)
        {
            serialPort1.PortName = port_combo.SelectedItem.ToString();
            serialPort1.BaudRate = Convert.ToInt32(baud_rate_combo.SelectedItem);
            serialPort1.Open();
            connect_button.Enabled = false;
        }

        private void disconnect_button_click(object sender, EventArgs e)
        {
            serialPort1.Close();
            connect_button.Enabled = true;
        }

        private void left_button_Click(object sender, EventArgs e)
        {
            if(serialPort1.IsOpen)
            {
                serialPort1.Write("LEFT\n");
            }
        }

        private void right_button_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Write("RIGHT\n");
            }
        }

        private void auto_button_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Write("AUTO\n");
            }
        }

        private void auto_stop_button_click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Write("AUTO_STOP\n");
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            us_cm_label.Text = serialPort1.ReadLine();
        }
    }
}
