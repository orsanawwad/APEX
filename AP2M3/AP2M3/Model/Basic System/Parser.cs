using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AP2M3.Model
{
    class Parser
    {
        /// <summary>
        /// used to connect the NetWorkManger and the DataBase
        /// </summary>
        string serverExtraData;
        Dictionary<int, string> indexToNames;

        public Parser(Dictionary<int, string> indexToNames)
        {

            this.indexToNames = indexToNames;
            indexToNames[0] = "Lon";
            indexToNames[1] = "Lat";
            serverExtraData = "";
        }

        public Dictionary<string, double> ParseFromServer(string msg)
        {
            Dictionary<string, double> updates = new Dictionary<string, double>();
            //if there is no new line, then not all the data was send. so wait for the next data recivment.
            //meaning, return as there were no updates
            string line = msg;
            string[] parts = line.Split(',');
            for (int i = 0; i < parts.Length; ++i)
            {
                if (!indexToNames.ContainsKey(i) || parts[i] == "") { continue; }
                string name = indexToNames[i];
                double value = Convert.ToDouble(parts[i]);
                updates[name] = value;
            }
            serverExtraData = "";
            for (int i = 1; i < parts.Length; ++i)
            {
                serverExtraData += "," + parts[i];
            }
            return updates;   
        }

        public string parseToServer(string name, double value)
        {
            return "set " + name + " " + value + "\r\n";
        }

        public string[] parseOutoPilotScript(string script)
        {
            string[] answer = script.Split('\n');
            for (int i = 0; i < answer.Length; ++i)
            {
                answer[i] += "\r\n";
            }

            return answer;
        }


        bool isParseFromServerWell(string[] parts)
        {
            foreach(string part in parts)
            {
                if(part.Split('.').Length > 2 ){
                    return false;
                }
            }
            return true;
        }
    }
}
