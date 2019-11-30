using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AP2M3.Model
{/// <summary>
/// used as the client to connect the server.
/// meaning it will be used to send the sed message (or any other kind of message) to the simulator
/// </summary>
    class Command
    {
        TcpClient client;
        NetworkStream clientStream;

        public Command()
        {
            client = new TcpClient();
        }

        public bool isCommandsConnect
        {
            get { return client.Connected; }
        }

        public void commandsConnect(string ip, int port)
        {
            try
            {
                client.Connect(IPAddress.Parse(ip), port);

            }
            catch (Exception e)
            {
                Console.WriteLine("exception in conncting : {0}", e.ToString());
            }

        }

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

        ~Command()
        {
            closeCommands();
        }
    }
}
