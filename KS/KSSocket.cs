﻿namespace KS
{
    using System;
    using System.Runtime.CompilerServices;
    using System.Runtime.Serialization;

    [Serializable]
    public class KSSocket : ISerializable
    {
		public string Param { get; set; }
		public string Protocol { get; set; }
		public KSSocketType Type { get; set; }

        public KSSocket()
        {
            Type = KSSocketType.None;
            Param = "";
            Protocol = "";
        }

        public KSSocket(KSSocket obj) : this()
        {
            if (obj != null)
            {
                Type = obj.Type;
                Param = obj.Param;
                Protocol = obj.Protocol;
            }
        }

        public KSSocket(SerializationInfo info, StreamingContext ctxt) : this()
        {
            Type = (KSSocketType) info.GetValue("Type", typeof(KSSocketType));
            Param = (string) info.GetValue("Param", typeof(string));
            Protocol = (string) info.GetValue("Protocol", typeof(string));
        }

        public override bool Equals(object obj)
        {
            return (Type.ToString() == obj.ToString());
        }

        public override int GetHashCode()
        {
            return (Type.GetHashCode() ^ Param.GetHashCode());
        }

        public void GetObjectData(SerializationInfo info, StreamingContext ctxt)
        {
            info.AddValue("Type", Type);
            info.AddValue("Param", Param);
            info.AddValue("Protocol", Protocol);
        }

        public override string ToString()
        {
            return Type.ToString();
        }
    }
}

