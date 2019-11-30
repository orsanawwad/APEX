using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Policy;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace AP2M4
{
    public class RouteConfig
    {
        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            routes.MapRoute(
                name: "Index",
                url: "",
                defaults: new { controller = "Home", action = "Index" }
            );

            routes.MapRoute(
                name: "Display",
                url: "display/{param1}/{param2}/{param3}",
                defaults: new { controller = "Display", action = "Index", param3 = UrlParameter.Optional }
            );

            routes.MapRoute(
                name: "GetPoint",
                url: "getPoint/{ip}/{port}/",
                defaults: new { controller = "Display", action = "GetPoint" },
                constraints: new { httpMethod = new HttpMethodConstraint("POST")}
            );

            routes.MapRoute(
                name: "Save",
                url: "save/{ip}/{port}/{refresh}/{duration}/{saveFile}",
                defaults: new { controller = "Save", action = "Index" }
            );
        }
    }
}
