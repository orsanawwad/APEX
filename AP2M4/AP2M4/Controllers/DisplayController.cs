using AP2M4.Model;
using AP2M4.Models;
using System;
using System.Linq;
using System.Web.Mvc;
using System.Web.Script.Serialization;

namespace AP2M4.Controllers
{
    /// <summary>
    /// /display/...
    /// </summary>
    public class DisplayController : Controller
    {

        /// <summary>
        /// Check if given string is IPv4 or not
        /// </summary>
        /// <param name="ipString">String to check</param>
        /// <returns>valid or not</returns>
        private bool ValidateIPv4(string ipString)
        {
            if (String.IsNullOrWhiteSpace(ipString))
            {
                return false;
            }

            string[] splitValues = ipString.Split('.');
            if (splitValues.Length != 4)
            {
                return false;
            }

            byte tempForParsing;

            return splitValues.All(r => byte.TryParse(r, out tempForParsing));
        }

        /// <summary>
        /// /display/:ip/:port
        /// /display/:ip/:port/:rate
        /// /display/:file/:rate
        /// </summary>
        /// <param name="param1">IP or File</param>
        /// <param name="param2">Port or Refresh Rate</param>
        /// <param name="param3">Refresh Rate, Optional</param>
        /// <returns>Rendered View with response baked in.</returns>
        public ViewResult Index(String param1, String param2, String param3 = null)
        {
            int port = 0;
            double refreshRate = 0;
            //Check if it's an ip
            bool isIp = this.ValidateIPv4(param1);

            //Call the correct function if its an IP or a File
            if (isIp)
            {
                //If it's an ip, parse the port and refresh rate if it exists.
                port = int.Parse(param2);
                ViewBag.IP = param1;
                ViewBag.PORT = port;
                if (param3 != null)
                {
                    //If refresh rate received, call the compatible function.
                    refreshRate = double.Parse(param3);
                    return this.isIpWithRefresh(param1, port, refreshRate);
                }
                else
                {   
                    return this.isIp(param1, port);
                }
            }
            else
            {
                refreshRate = int.Parse(param2);
                return isFile(param1, refreshRate);
            }
        }

        /// <summary>
        /// /display/:ip/:port
        /// </summary>
        /// <param name="ip">IP to connect</param>
        /// <param name="port">Port for FlightGear</param>
        /// <returns>Rendered View</returns>
        private ViewResult isIp(string ip, int port)
        {
            ViewBag.Response = GetPoint(ip, port);
            if (ViewBag.Response == null)
            {
                return ErrorResponse("Could not connect to FlightSim.");
            }
            return View();
        }

        /// <summary>
        /// /display/:ip/:port/:refresh
        /// </summary>
        /// <param name="ip">IP to connect</param>
        /// <param name="port">Port for FlightGear</param>
        /// <param name="refresh">Refresh rate for new points</param>
        /// <returns>Rendered View with refresh rate setup</returns>
        private ViewResult isIpWithRefresh(string ip, int port, double refresh)
        {
            ViewBag.Response = GetPoint(ip, port);
            if (ViewBag.Response == null)
            {
                return ErrorResponse("Could not connect to FlightSim.");
            }
            ViewBag.RefreshRate = refresh;
            return View();
        }

        private ViewResult ErrorResponse(string message)
        {
            Response.StatusCode = 403;
            ViewBag.Message = message;
            return View("~/Views/Save/Index.cshtml");
        }

        /// <summary>
        /// /display/:file/:refresh
        /// </summary>
        /// <param name="fileName">File name to read from</param>
        /// <param name="refresh">Refresh rate for new points</param>
        /// <returns>Rendered View with array of points baked in</returns>
        private ViewResult isFile(string fileName, double refresh)
        {
            String path = Server.MapPath("~/App_Data/" + fileName + ".json");
            if (!System.IO.File.Exists(path))
            {
                return ErrorResponse("File not found!");
            }
            string contents = System.IO.File.ReadAllText(path);
            ViewBag.RefreshRate = refresh;
            contents = contents.Replace(System.Environment.NewLine, "");
            ViewBag.Response = contents.Replace(" ","");
            return View();
        }

        /// <summary>
        /// POST request for receiving the next point
        /// </summary>
        /// <param name="ip">IP to connect</param>
        /// <param name="port">Port for FlightGear</param>
        /// <returns>JSON with points</returns>
        [HttpPost]
        public string GetPoint(String ip, int port)
        {
            CommandModel commandModel = new CommandModel();
            try
            {
                commandModel.commandsConnect(ip, port);
            }
            catch (Exception e)
            {
                return null;
            }
            CheckPoint p = commandModel.getCurrentPosition();
            commandModel.closeCommands();
            return new JavaScriptSerializer().Serialize(p);
        }
    }
}