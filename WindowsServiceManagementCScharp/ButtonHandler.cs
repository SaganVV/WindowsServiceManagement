using COMWindowsServicesLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsServiceManagementCScharp
{
    internal class ButtonHandler
    {
        public static void StartServiceButtonHandler(string serviceName)
        {
            try
            {
                new ServiceHandler().ServiceStart(serviceName);
                MessageBox.Show("Service successfully started");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        public static void StopServiceButtonHandler(string serviceName)
        {
            try
            {
                new ServiceHandler().ServiceStop(serviceName);
                MessageBox.Show("Service successfully stopped");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        public static void PauseServiceButtonHandler(string serviceName)
        {
            try
            {
                new ServiceHandler().ServicePause(serviceName);
                MessageBox.Show("Service successfully paused");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        public static void ContinueServiceButtonHandler(string serviceName)
        {
            try
            {
                new ServiceHandler().ServiceResume(serviceName);
                MessageBox.Show("Service successfully paused");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

    }
}
