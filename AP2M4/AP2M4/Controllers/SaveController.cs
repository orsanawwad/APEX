using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Threading;
using System.Web;
using System.Web.Mvc;
using AP2M4.Models;
using System.Web.Script.Serialization;

namespace AP2M4.Controllers
{
    public class SaveController : Controller
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="ip">IP to connect</param>
        /// <param name="port">Port for FlightGear</param>
        /// <param name="refresh">Refresh rate for new points</param>
        /// <param name="duration">How long to save</param>
        /// <param name="saveFile">File name to save</param>
        /// <returns></returns>
        public ActionResult Index(string ip, int port, int refresh, int duration, string saveFile)
        {
            String path = Server.MapPath("~/App_Data/" + saveFile + ".json");

            //Check if file exists, if so return error.
            if (System.IO.File.Exists(path))
            {
                Response.StatusCode = 403;
                ViewBag.Message = "File Already Exists!";
                return View();
            }

            var autoEvent = new AutoResetEvent(false);
            //Run timer and save points
            var saveInstancePoints = new SaveModel(refresh*duration, ip, port);
            var stateTimer = new Timer(saveInstancePoints.FetchPoint,
                autoEvent, 0, 1000/refresh);
            autoEvent.WaitOne();
            stateTimer.Dispose();



            

            //Save to file
            var jsonSerialiser = new JavaScriptSerializer();
            var json = jsonSerialiser.Serialize(
                new
                {
                    fileName = saveFile,
                    points = saveInstancePoints.arr
                });
            json = JsonHelper.FormatJson(json);
            System.IO.File.WriteAllText(path, json);
            //Redirect to /display with current inputs
            return Redirect("/display/" + saveFile + "/" + refresh);
        }
    }
}