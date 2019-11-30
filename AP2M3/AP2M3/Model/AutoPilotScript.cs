using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace AP2M3.Model
{
    class AutoPilotScript
    {
        public delegate void allSend();
        public event allSend allSendEvent; //the event for when all the script was send
        Task task;
        Action<object> sending; //the action to send the messages
        Mutex mutex;
        bool isSendWhileSending; //for when new script is coming while the old one is still waiting.
        volatile Queue<string> script; //the script as lines
        public string Script //used to set the script
        {
            set
            {
                clearBuffer();
                //parse the script
                string[] lines = ModelSystem.instance.parser.parseOutoPilotScript(value);
                foreach(string line in lines)
                {
                    script.Enqueue(line);
                }
                sendScripts();
            }
        }
        //check if there is a message to send
        bool isMessageSend()
        {
            return script.Count == 0;
        }
        //def constructor
        public AutoPilotScript()
        {
            isSendWhileSending = false;
            script = new Queue<string>();
            mutex = new Mutex();
            sending = (x) =>
            {
                while (script.Count != 0)
                {
                    mutex.WaitOne();
                    ModelSystem.instance.netManager.send(script.Dequeue());
                    mutex.ReleaseMutex();
                    //wait 2 sec
                    Thread.Sleep(2 * 1000);
                    if (!isSendWhileSending)
                    {
                        allSendEvent?.Invoke();
                    }
                }
            };
        }

        //send the messages acording to the action
        void sendScripts()
        {
            task?.Wait();
            isSendWhileSending = false;
            task = new Task(sending, null);
            task.Start();
        }

        //clear the buffer in a save way and stop sending the messages
        void clearBuffer()
        {
            mutex.WaitOne();
            if (script.Count != 0)
            {
                isSendWhileSending = true;
                script.Clear();
            }
            else
            {
                isSendWhileSending = false;
            }
            mutex.ReleaseMutex();
        }

        //stop sending messages
        ~AutoPilotScript()
        {
            clearBuffer();
            task?.Wait();
        }
    }
}
