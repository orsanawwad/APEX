using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AP2M3.Model
{
    /// <summary>
    /// used to mange both the server (info) and client (commands) to be sued in the program.
    /// </summary>
    class NetWorkManager
    {
        public delegate void allMessagesSend();
        public event allMessagesSend messagesSendEvent;
        Command client;
        Info info;
        volatile bool isCommandConnected;
        Mutex mutex;
        Task task;


        public NetWorkManager()
        {
            client = new Command();
            info = new Info();
            mutex = new Mutex();
            isCommandConnected = false;

        }

        //commands part

        public bool isCommandsConnect
        {
            get { return client.isCommandsConnect; }
        }

        public void commandsConnect(string ip, int port)
        {
            Action<object> act = (x) =>
            {
                while (!isInfoServerOpen)
                {
                    Thread.Sleep(30);
                }
                client.commandsConnect(ip, port);
            };
            task = new Task(act,null);
            task.Start();
            isCommandConnected = true;
        }


        public void sendInThread(string msg)
        {
            Action<object> act = (x) =>
            {
                send(msg);
            };
            task?.Wait();
            task = new Task(act, null);
            task.Start();
        }

        public void send(string msg)
        {
            mutex.WaitOne();
            client.send(msg);
            mutex.ReleaseMutex();
        }

        public void closeCommands()
        {
            isCommandConnected = false;
            task.Wait();
            client.closeCommands();
            
        }

        //info part


        public bool isInfoServerOpen
        {
            get { return info.isOpen(); }
        }

        public void StartInfo(string ip, int port, int hrz)
        {
            info.StartInfo(ip, port, hrz);
        }

        public void addToGotDataEvent(Info.gotData func)
        {
            info.gotDataEvent += func;
        }

        public void closeInfo()
        {
            info.closeInfo();
        }

        

    }

   

   /* public class clientThreadArgs
    {
        Queue<int> messagesIndex;
        Dictionary<int, string> messages;

        public clientThreadArgs(Queue<int> messagesIndex, Dictionary<int, string> messages)
        {
            this.messages = messages;
            this.messagesIndex = messagesIndex;
        }
    }*/


}

