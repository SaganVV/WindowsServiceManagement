using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
namespace WindowsServiceManagementCScharp
{
    internal class DataGridViewHandler
    {
        public static IEnumerable<string[]> ServicesToDataGridRowFormat(Service[] services)
        {
            var filteredServices = services
                .Select(service => new[] { service.Name, service.GetState().ToString() });

            return filteredServices;
        }
        public static Service[] SelecteService(Service[] services, string startWith) 
        {
            var filteredServices = services
    .Where(service => service.Name.ToLower().StartsWith(startWith.ToLower()));
            return filteredServices.ToArray();
        }
        public static void AddDataToGrid(DataGridView dgv, IEnumerable<string[]> services)
        {
            foreach (var serviceData in services)
            {
                dgv.Rows.Add(serviceData);
            }
        }
    }
}
