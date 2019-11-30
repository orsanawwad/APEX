using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace AP2M3.Model
{
    /// <summary>
    /// used as the server. this is how the simuator will connect to the server and use it to get updates from the simulator
    /// </summary>
    class Info
    {
        public delegate void gotData(string data);
        public event gotData gotDataEvent;
        TcpListener listener;
        Task serverTask;
        volatile bool isInfoOpen;
        serverThreadArgs args;
        bool isWatingToClient;

        public Info()
        {
            isInfoOpen = false;
            isWatingToClient = false;
        }

        public void StartInfo(string ip, int port, double hrz)
        {
            if (isInfoOpen)
            {
                closeInfo();
            }
            listener = new TcpListener(IPAddress.Parse(ip), port);

            args = new serverThreadArgs(listener, hrz);
            Action<object> act = (args) =>
            {
                TcpListener server = (args as serverThreadArgs).info;
                double hr = (args as serverThreadArgs).hrz;
                server.Start();
                // Buffer for reading data
                Byte[] bytes = new Byte[256];
                String data = null;
                TcpClient client;
                try
                {
                    isWatingToClient = true;
                    client = server.AcceptTcpClient();
                } catch (SocketException e)
                {
                    if (e.SocketErrorCode == SocketError.Interrupted)
                    {
                        return;
                    }
                    isWatingToClient = false;
                    throw e;
                }
                isWatingToClient = false;
                isInfoOpen = true;

                int dataSize;
                NetworkStream stream = client.GetStream();
                StreamReader reader = new StreamReader(stream);
                while (isInfoOpen)
                {
                    data = reader.ReadLine();
                    if (data == null)
                    {
                        closeInfo();
                        return;
                    }
                    gotDataEvent?.Invoke(data);
                    //Thread.Sleep(Convert.ToInt32(hr));
                }
                stream.Close();
                client.Close();
            };

            serverTask = new Task(act, args);
            serverTask.Start();
        }

        public void closeInfo()
        {
            isInfoOpen = false;
            if (isWatingToClient)
            {
                listener?.Stop();
                serverTask?.Wait();
            }
            else
            {
                serverTask?.Wait();
                listener?.Stop();
            }
        }

        public bool isOpen()
        {
            return isInfoOpen;
        }

        ~Info()
        {
            closeInfo();
        }

    }

    public class serverThreadArgs
    {
        public TcpListener info;
        public double hrz;

        public serverThreadArgs(TcpListener _info, double _hrz)
        {
            this.info = _info;
            this.hrz = _hrz;
        }

    }



}

    

