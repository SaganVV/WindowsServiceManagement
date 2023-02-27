using COMWindowsServicesLib;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsServiceManagementCScharp
{
    public partial class FormService : Form
    {
        private string serviceName;
        private Service[] services = null;
        public FormService()
        {
            InitializeComponent();
            
        }

        public void setTextTo_txtBServiceName(string text)
        {
            txtBServiceName.Text = text;
            serviceName = txtBServiceName.Text;

        }
        private void btnRefresh_Click(object sender, EventArgs e)
        {
            services = Service.GetDependentServicesNames(serviceName);
           
            dgvServices.Rows.Clear();
            DataGridViewHandler.AddDataToGrid(dgvServices, DataGridViewHandler.ServicesToDataGridRowFormat(services));
            dgvServices.ClearSelection();
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            ButtonHandler.StartServiceButtonHandler(serviceName);
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            ButtonHandler.StopServiceButtonHandler(serviceName);
        }

        private void btnContinue_Click(object sender, EventArgs e)
        {
            ButtonHandler.ContinueServiceButtonHandler(serviceName);
        }

        private void btnPause_Click(object sender, EventArgs e)
        {
            ButtonHandler.PauseServiceButtonHandler(serviceName);
        }

        private void btnStopDependent_Click(object sender, EventArgs e)
        {
            try
            {
                new ServiceHandler().StopDependentServices(serviceName);
            }
            catch (Exception ex)
            {
                MessageBox.Show(serviceName);
                //MessageBox.Show(ex.Message);
            }
        }
    }
}
