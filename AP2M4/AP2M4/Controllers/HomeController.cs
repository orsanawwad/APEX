using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace AP2M4.Controllers
{
    public class HomeController : Controller
    {
        /// <summary>
        /// Home Page
        /// </summary>
        /// <returns>Home Page view.</returns>
        public ActionResult Index()
        {
            return View();
        }
    }
}