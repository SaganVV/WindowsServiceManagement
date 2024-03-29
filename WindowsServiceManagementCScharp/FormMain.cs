﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using COMWindowsServicesLib;

namespace WindowsServiceManagementCScharp
{


    public partial class FormMainMenu : Form
    {
        private const int ServiceNameColumnIndex = 0;
        private const int ServiceStateColumnIndex = 1;

        private Button[] serviceControlButtons;

        private string selectedServiceName;
        private Service[] services = null;

        public FormMainMenu()
        {
            InitializeComponent();

            init();

        }
        private void init() 
        {
            services = Service.GetWindowsServices();
            serviceControlButtons = new Button[4] { btnStart, btnStop, btnContinue, btnPause };
            DeactivateServiceControlButtons();     
            UpdateServicesGrid("");

        }

        private void UpdateServicesGrid(string startWith)
        {
            dgvServices.Rows.Clear();

            var filteredServices = DataGridViewHandler.ServicesToDataGridRowFormat(DataGridViewHandler.SelecteService(services, startWith)) ;

            foreach (var serviceData in filteredServices)
            {
                dgvServices.Rows.Add(serviceData);
            }
            dgvServices.ClearSelection();
        }
        private void DeactivateServiceControlButtons()
        {
            foreach (var btn in serviceControlButtons)
            {
                btn.Enabled = false;
            }
        }
        private void ActivateServiceControlButtons()
        {
            var service = new Service(selectedServiceName);

            if (service != null)
            {
                var controlsAccepted = service.controlsAccepted;
                var serviceState = service.stateCode;

                switch (serviceState)
                {
                    case ServiceStates.SERVICE_STOPPED:
                        serviceControlButtons[0].Enabled = true; // Enable "Start" button
                        break;

                    case ServiceStates.SERVICE_RUNNING:
                        if (Service.ActionAppliable(ServiceControlAccepted.SERVICE_ACCEPT_PAUSE, controlsAccepted))
                        {
                            serviceControlButtons[3].Enabled = true; // Enable "Pause" button
                        }
                        if (Service.ActionAppliable(ServiceControlAccepted.SERVICE_ACCEPT_STOP, controlsAccepted))
                        {
                            serviceControlButtons[1].Enabled = true; // Enable "Stop" button
                        }
                        break;

                    case ServiceStates.SERVICE_PAUSED:
                        if (Service.ActionAppliable(ServiceControlAccepted.SERVICE_ACCEPT_CONTINUE, controlsAccepted))
                        {
                            serviceControlButtons[2].Enabled = true; // Enable "Continue" button
                        }
                        if (Service.ActionAppliable(ServiceControlAccepted.SERVICE_ACCEPT_STOP, controlsAccepted))
                        {
                            serviceControlButtons[1].Enabled = true; // Enable "Stop" button
                        }
                        break;
                }
            }
        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            services = Service.GetWindowsServices();
            UpdateServicesGrid("");
            
            DeactivateServiceControlButtons();
        }

        private void btnFindService_Click(object sender, EventArgs e)
        {
            string beginText = txtbServiceName.Text;
            UpdateServicesGrid(beginText);
        }

        private void dgvServices_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            DeactivateServiceControlButtons();
            if (e.RowIndex >= 0)
            {
                DataGridViewRow row = dgvServices.Rows[e.RowIndex];
                if (row != null)
                {
                    selectedServiceName = (string)row.Cells[0].Value;
                    ActivateServiceControlButtons();
                }
            }
        }

        private void FormMainMenu_Load(object sender, EventArgs e)
        {
            dgvServices.ClearSelection();
           // dgvServices.Rows.Add()
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            ButtonHandler.StartServiceButtonHandler(selectedServiceName);
        }

        private void btnContinue_Click(object sender, EventArgs e)
        {
            ButtonHandler.ContinueServiceButtonHandler(selectedServiceName);
        }

        private void btnPause_Click(object sender, EventArgs e)
        {
            ButtonHandler.PauseServiceButtonHandler(selectedServiceName);
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            ButtonHandler.StopServiceButtonHandler(selectedServiceName);
        }

        private void dgvServices_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            
        }
        private void dgvServices_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0)
            {
                DataGridViewRow row = dgvServices.Rows[e.RowIndex];
                if (row != null)
                {
                    selectedServiceName = (string)row.Cells[0].Value;
                    ActivateServiceControlButtons();
                }
            }
            FormService form2 = new FormService();
            form2.setTextTo_txtBServiceName(selectedServiceName);
            form2.ShowDialog();
        }
    }
}
