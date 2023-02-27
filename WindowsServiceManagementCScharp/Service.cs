using COMWindowsServicesLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsServiceManagementCScharp
{
    public static class ServiceStates
    {
        public const int SERVICE_STOPPED = 1;
        public const int SERVICE_START_PENDING = 2;
        public const int SERVICE_STOP_PENDING = 3;
        public const int SERVICE_RUNNING = 4;
        public const int SERVICE_CONTINUE_PENDING = 5;
        public const int SERVICE_PAUSE_PENDING = 6;
        public const int SERVICE_PAUSED = 7;
    }
    public static class ServiceControlAccepted
    {
        public const int SERVICE_ACCEPT_STOP = 1;
        public const int SERVICE_ACCEPT_PAUSE = 2;
        public const int SERVICE_ACCEPT_CONTINUE = 2;
    }
    internal class Service
    {
        public string Name { get; set; }

        private static readonly Dictionary<uint, string> serviceStateMap = new Dictionary<uint, string>()
        {
            { ServiceStates.SERVICE_STOPPED, "not running." },
            { ServiceStates.SERVICE_START_PENDING, "starting." },
            { ServiceStates.SERVICE_STOP_PENDING, "stopping." },
            { ServiceStates.SERVICE_RUNNING, "running." },
            { ServiceStates.SERVICE_CONTINUE_PENDING, "continue is pending." },
            { ServiceStates.SERVICE_PAUSE_PENDING, "pause is pending." },
            { ServiceStates.SERVICE_PAUSED, "paused." }
        };

        public uint stateCode
        {
            get
            {
               
                uint _code = 0;
                new ServiceHandler().ServiceCurrentState(Name, out _code);
                return _code;
            }
        }
        public uint controlsAccepted
        {
            get
            {
                
                uint controlsAccepted = 0;
                new ServiceHandler().ServiceControlsAccepted(Name, out controlsAccepted);
                return controlsAccepted;
            }
        }
        public Service(string name)
        {
            this.Name = name;
        }

        public string GetState()
        {
            return serviceStateMap.TryGetValue(stateCode, out string state) ? state : "unknown";
        }

        public static bool ActionAppliable(uint acceptCode, uint controlCode) 
        {
            return (acceptCode & controlCode) == acceptCode;
        }
        public static Service[] GetWindowsServices()
        {
           
            uint serviceCount = 0;
            Array serviceNames;
            new ServiceHandler().GetServices(out serviceNames, out serviceCount);

            Service[] services = new Service[serviceNames.Length];
            for (int i = 0; i < serviceNames.Length; i++)
            {
                services[i] = new Service((string)serviceNames.GetValue(i));
            }

            return services;
        }
        public static Service[] GetDependentServicesNames(string serviceName)
        {
            Array serviceNames;
            uint countServicesReturned;
            try
            {
                new ServiceHandler().GetDependentServices(serviceName, out serviceNames, out countServicesReturned);
                /*                Service[] services = new Service[serviceNames.Length];
                                for (int i = 0; i < serviceNames.Length; i++)
                                {
                                    services[i] = new Service((string)serviceNames.GetValue(i));
                                }
                                return services;*/
                return null;

            }
            catch(Exception ex) { MessageBox.Show(ex.Message); return null; }
            
        }
        public Service[] GetDependentServicesNames()
        {
            return GetDependentServicesNames(Name);
        }
    }
}



