﻿namespace TCPService
{
    using System;
    using System.Net.Sockets;
    using System.Threading;

    public class TCPSocketListener
    {
        private Thread m_clientListenerThread;
        private Socket m_clientSocket;
        private DateTime m_currentReceiveDateTime;
        private DateTime m_lastReceiveDateTime;
        private bool m_markedForDeletion;
        private bool m_stopClient;

        public TCPSocketListener(Socket clientSocket)
        {
            this.m_clientSocket = clientSocket;
        }

        private void CheckClientCommInterval(object o)
        {
            if (this.m_lastReceiveDateTime.Equals(this.m_currentReceiveDateTime))
            {
                this.StopSocketListener();
            }
            else
            {
                this.m_lastReceiveDateTime = this.m_currentReceiveDateTime;
            }
        }

        ~TCPSocketListener()
        {
            this.StopSocketListener();
        }

        public bool IsMarkedForDeletion()
        {
            return this.m_markedForDeletion;
        }

        public void SendData(byte[] data)
        {
            if (!this.m_stopClient)
            {
                try
                {
                    if (this.m_clientSocket.Send(data) == 0)
                    {
                        this.m_stopClient = true;
                        this.m_markedForDeletion = true;
                    }
                }
                catch (SocketException)
                {
                    this.m_stopClient = true;
                    this.m_markedForDeletion = true;
                }
            }
        }

        private void SocketListenerThreadStart()
        {
            int num = 0;
            byte[] buffer = new byte[0x400];
            this.m_lastReceiveDateTime = DateTime.Now;
            this.m_currentReceiveDateTime = DateTime.Now;
            Timer timer = new Timer(new TimerCallback(this.CheckClientCommInterval), null, 0x3a98, 0x3a98);
            while (!this.m_stopClient)
            {
                try
                {
                    num = this.m_clientSocket.Receive(buffer);
                    this.m_currentReceiveDateTime = DateTime.Now;
                    if (num == 0)
                    {
                        this.m_stopClient = true;
                        this.m_markedForDeletion = true;
                    }
                    continue;
                }
                catch (SocketException)
                {
                    this.m_stopClient = true;
                    this.m_markedForDeletion = true;
                    continue;
                }
            }
            timer.Change(-1, -1);
            timer = null;
        }

        public void StartSocketListener()
        {
            if (this.m_clientSocket != null)
            {
                this.m_clientListenerThread = new Thread(new ThreadStart(this.SocketListenerThreadStart));
                this.m_clientListenerThread.Start();
            }
        }

        public void StopSocketListener()
        {
            if (this.m_clientSocket != null)
            {
                this.m_stopClient = true;
                try
                {
                    this.m_clientSocket.Close();
                }
                catch (SocketException)
                {
                }
                this.m_clientListenerThread.Join(0x3e8);
                if (this.m_clientListenerThread.IsAlive)
                {
                    this.m_clientListenerThread.Abort();
                }
                this.m_clientListenerThread = null;
                this.m_clientSocket = null;
                this.m_markedForDeletion = true;
            }
        }

        public string ClientInfo
        {
            get
            {
                string str = "Client not available";
                try
                {
                    if (this.m_clientSocket != null)
                    {
                        str = this.m_clientSocket.RemoteEndPoint.ToString();
                    }
                }
                catch
                {
                }
                return str;
            }
        }
    }
}

