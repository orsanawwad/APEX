using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Web;
using AP2M4.Model;

namespace AP2M4.Models
{
    public class SaveModel
    {
        private int MaxRuns = 0;
        private int CurrentRuns = 0;
        private string ip = "";
        private int port = 0;
        private CommandModel commandModel = new CommandModel();

        private List<CheckPoint> _arr = new List<CheckPoint>();

        public List<CheckPoint> arr => this._arr;

        public SaveModel(int MaxRuns, string ip, int port)
        {
            this.MaxRuns = MaxRuns;
            this.CurrentRuns = 0;
            this.ip = ip;
            this.port = port;
            this.commandModel.commandsConnect(ip, port);
        }



        public void FetchPoint(Object stateInfo)
        {
            this.arr.Add(this.commandModel.getCurrentPosition());
            this.CurrentRuns++;
            if (this.CurrentRuns == this.MaxRuns)
            {
                AutoResetEvent autoEvent = (AutoResetEvent)stateInfo;
                this.CurrentRuns = 0;
                autoEvent.Set();
            }
        }
    }
}