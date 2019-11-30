using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using AP2M4.Models;

namespace AP2M4.Model
{
    /// <summary>
    /// Model for sending and receiving requests and responses to FlightGear sim.
    /// </summary>
    class CommandModel
    {
        TcpClient client;
        NetworkStream clientStream;
        Mutex mutex;

        public CommandModel()
        {
            client = new TcpClient();
            mutex = new Mutex();
        }
        
        /// <summary>
        /// Connect to FlightGear
        /// </summary>
        /// <param name="ip">IP to connect</param>
        /// <param name="port">FlightGear port</param>
        public void commandsConnect(string ip, int port)
        {
            client.Connect(IPAddress.Parse(ip), port);
        }

        /// <summary>
        /// Extract current point.
        /// </summary>
        /// <returns>CheckPoint data.</returns>
        public CheckPoint getCurrentPosition()
        {
            mutex.WaitOne();
            this.send("get /position/longitude-deg\r\n");
            double lon = this.extractValue(this.read());
            this.send("get /position/latitude-deg\r\n");
            double lat = this.extractValue(this.read());
            this.send("get /controls/engines/current-engine/throttle\r\n");
            double throttle = this.extractValue(this.read());
            this.send("get /controls/flight/rudder\r\n");
            double rudder = this.extractValue(this.read());
            mutex.ReleaseMutex();
            return new CheckPoint(lon,lat,throttle,rudder);
        }

        /// <summary>
        /// Regex for extracting data from response.
        /// </summary>
        /// <param name="data">Garbled data, the value is inside single quotes.</param>
        /// <returns>Extracted value</returns>
        private double extractValue(String data)
        {
            double extractedData = -1;
            Regex rx = new Regex(@"\'(.*?)\'", RegexOptions.Compiled);
            MatchCollection matches = rx.Matches(data);
            foreach (Match match in matches)
            {
                GroupCollection groups = match.Groups;
                extractedData = double.Parse(groups[1].Value);
            }

            return extractedData;
        }

        /// <summary>
        /// Read response.
        /// </summary>
        /// <returns>Response value</returns>
        public string read()
        {
            while (!client.Connected)
            {
                Task.Delay(50);
            }

            String responseData = String.Empty;

            try
            {
                Byte[] data = new Byte[1024];

                // String to store the response ASCII representation.

                // Read the first batch of the TcpServer response bytes.
                responseData = new StreamReader(client.GetStream()).ReadLine();
            }
            catch (Exception e)
            {
                Console.WriteLine("exception in reading message : {0}", e.ToString());
                return null;
            }

            return responseData;
        }

        /// <summary>
        /// Send request.
        /// </summary>
        /// <param name="message">Request string.</param>
        public void send(string message)
        { 
            while (!client.Connected)
            {
                Task.Delay(50);
            }
            try
            {
                Byte[] data = System.Text.Encoding.ASCII.GetBytes(message);
                if (clientStream == null)
                {
                    clientStream = client.GetStream();
                }
                clientStream.Write(data, 0, data.Length);
            }
            catch (Exception e)
            {
                Console.WriteLine("exception in sending the message : {0}", e.ToString());
                throw new Exception("error while trying to send via the client a message");
            }

        }
        
        /// <summary>
        /// Close connection.
        /// </summary>
        public void closeCommands()
        {
            if (clientStream != null)
            {
                clientStream.Close();
                clientStream = null;
            }
            if (client.Connected)
            {
                client.Close();
            }
        }

        ~CommandModel()
        {
            closeCommands();
        }
    }
}
