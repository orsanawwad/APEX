using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace AP2M3.Model
{
    /// <summary>
    /// unify both the networking and the database of model under one singelton, the union of the both create the basic system the makes the model.
    /// the DataBase is the part of data changing
    /// the NetWorkManger the part of the communication of the model 
    /// 
    /// the system also use a parser to mange to connect the two parts (the DataBase and the NetWorkMmanger). 
    /// </summary>
    class ModelSystem 
    {
        public NetWorkManager netManager;
        public DataBase dataHolder;
        public Parser parser;
        static ModelSystem instanceValue;
        public static ModelSystem instance
        {
            get
            {
                if (instanceValue == null)
                {
                    instanceValue = new ModelSystem();
                }
                return instanceValue;
            }
        }



        private ModelSystem()
        {
            Dictionary<int, string> indexToNames = new Dictionary<int, string>();
            indexToNames.Add(0, "/instrumentation/airspeed-indicator/indicated-speed-kt");
            indexToNames.Add(1, "/instrumentation/altimeter/indicated-altitude-ft");
            indexToNames.Add(2, "/instrumentation/altimeter/pressure-alt-ft");
            indexToNames.Add(3, "/instrumentation/attitude-indicator/indicated-pitch-deg");
            indexToNames.Add(4, "/instrumentation/attitude-indicator/indicated-roll-deg");
            indexToNames.Add(5, "/instrumentation/attitude-indicator/internal-pitch-deg");
            indexToNames.Add(6, "/instrumentation/attitude-indicator/internal-roll-deg");
            indexToNames.Add(7, "/instrumentation/encoder/indicated-altitude-ft");
            indexToNames.Add(8, "/instrumentation/encoder/pressure-alt-ft");
            indexToNames.Add(9, "/instrumentation/gps/indicated-altitude-ft");
            indexToNames.Add(10, "/instrumentation/gps/indicated-ground-speed-kt");
            indexToNames.Add(11, "/instrumentation/gps/indicated-vertical-speed");
            indexToNames.Add(12, "/instrumentation/heading-indicator/indicated-heading-deg");
            indexToNames.Add(13, "/instrumentation/magnetic-compass/indicated-heading-deg");
            indexToNames.Add(14, "/instrumentation/slip-skid-ball/indicated-slip-skid");
            indexToNames.Add(15, "/instrumentation/turn-indicator/indicated-turn-rate");
            indexToNames.Add(16, "/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
            indexToNames.Add(17, "/controls/flight/aileron");
            indexToNames.Add(18, "/controls/flight/elevator");
            indexToNames.Add(19, "/controls/flight/rudder");
            indexToNames.Add(20, "/controls/flight/flaps");
            indexToNames.Add(21, "/controls/engines/engine/throttle");
            indexToNames.Add(22, "/engines/engine/rpm");
            netManager = new NetWorkManager();
            dataHolder = new DataBase();
            parser = new Parser(indexToNames);
            netManager.addToGotDataEvent(updateDataBase);
            dataHolder.dataUpdateEvent += sendSet;

        }
        private ModelSystem(Dictionary<int, string> indexToNames)
        {
            netManager = new NetWorkManager();
            dataHolder = new DataBase();
            parser = new Parser(indexToNames);
            netManager.addToGotDataEvent(updateDataBase);
            dataHolder.dataUpdateEvent += sendSet;
            openInfo();

        }


        private ModelSystem(string ipAddres, int clientPort, int serverPort)
        {
            Dictionary<int, string> indexToNames = new Dictionary<int, string>();
            indexToNames.Add(0, "/instrumentation/airspeed-indicator/indicated-speed-kt");
            indexToNames.Add(1, "/instrumentation/altimeter/indicated-altitude-ft");
            indexToNames.Add(2, "/instrumentation/altimeter/pressure-alt-ft");
            indexToNames.Add(3, "/instrumentation/attitude-indicator/indicated-pitch-deg");
            indexToNames.Add(4, "/instrumentation/attitude-indicator/indicated-roll-deg");
            indexToNames.Add(5, "/instrumentation/attitude-indicator/internal-pitch-deg");
            indexToNames.Add(6, "/instrumentation/attitude-indicator/internal-roll-deg");
            indexToNames.Add(7, "/instrumentation/encoder/indicated-altitude-ft");
            indexToNames.Add(8, "/instrumentation/encoder/pressure-alt-ft");
            indexToNames.Add(9, "/instrumentation/gps/indicated-altitude-ft");
            indexToNames.Add(10, "/instrumentation/gps/indicated-ground-speed-kt");
            indexToNames.Add(11, "/instrumentation/gps/indicated-vertical-speed");
            indexToNames.Add(12, "/instrumentation/heading-indicator/indicated-heading-deg");
            indexToNames.Add(13, "/instrumentation/magnetic-compass/indicated-heading-deg");
            indexToNames.Add(14, "/instrumentation/slip-skid-ball/indicated-slip-skid");
            indexToNames.Add(15, "/instrumentation/turn-indicator/indicated-turn-rate");
            indexToNames.Add(16, "/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
            indexToNames.Add(17, "/controls/flight/aileron");
            indexToNames.Add(18, "/controls/flight/elevator");
            indexToNames.Add(19, "/controls/flight/rudder");
            indexToNames.Add(20, "/controls/flight/flaps");
            indexToNames.Add(21, "/controls/engines/engine/throttle");
            indexToNames.Add(22, "/engines/engine/rpm");
            netManager = new NetWorkManager();
            dataHolder = new DataBase();
            parser = new Parser(indexToNames);
            netManager.addToGotDataEvent(updateDataBase);
            dataHolder.dataUpdateEvent += sendSet;
            openInfo();
            netManager.commandsConnect(ipAddres, clientPort);
            

        }

        private void openInfo()
        {
            netManager.StartInfo("127.0.0.1",ApplicationSettingsModel.Instance.FlightInfoPort, 60);
        }

        private void sendSet(string name, double value)
        {
            netManager.sendInThread(parser.parseToServer(name, value));
        }

        private void updateDataBase(string msg)
        {
            dataHolder.updateFromServer(parser.ParseFromServer(msg));
        }

        
    }
}
