using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class RS232 : Form
    {
        public RS232()
        {
            InitializeComponent();
            if (!Myport.IsOpen)
            {
                Myport.Open();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Myport.Write(txtBox.Text);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (Myport.IsOpen)
            {
                Myport.Close();
            }
        }
    }
}
