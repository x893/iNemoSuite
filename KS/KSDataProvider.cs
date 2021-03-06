﻿namespace KS
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Runtime.Serialization.Formatters.Binary;

    public class KSDataProvider
    {
		public enum CursorStep
		{
			CursorFirst,
			CursorPrev,
			CursorNext,
			CursorLast
		}
		
		private int cursor;
        private bool isModified;
        private List<KSKit> kits = new List<KSKit>();

        public KSDataProvider()
        {
            Clear();
        }

        public bool Add(KSKit kit)
        {
            bool flag = false;
            try
            {
                if (kit.IsValid() && (Find(kit.Code) == null))
                {
                    kits.Add(kit);
                    MoveTo(CursorStep.CursorLast);
                    isModified = true;
                    flag = true;
                }
            }
            catch (Exception)
            {
            }
            return flag;
        }

        public void Clear()
        {
            kits.Clear();
            cursor = -1;
            isModified = false;
        }

        public KSKit Find(string kitCode)
        {
            foreach (KSKit kit in kits)
                if (kit.Code == kitCode)
                    return kit;
            return null;
        }

        public bool Load(string dbkFile)
        {
            bool flag = true;
            try
            {
                Clear();
                Stream serializationStream = File.Open(dbkFile, FileMode.Open);
                BinaryFormatter formatter = new BinaryFormatter();
                kits = (List<KSKit>) formatter.Deserialize(serializationStream);
                serializationStream.Close();
                MoveTo(CursorStep.CursorFirst);
            }
            catch (Exception)
            {
                flag = false;
            }
            return flag;
        }

        public KSKit MoveTo(CursorStep cursorStep)
        {
            KSKit kit = null;
            if (kits.Count > 0)
            {
                switch (cursorStep)
                {
                    case CursorStep.CursorFirst:
                        cursor = 0;
                        return kits[cursor];

                    case CursorStep.CursorPrev:
                        if (cursor > 0)
                        {
                            cursor--;
                            kit = kits[cursor];
                        }
                        return kit;

                    case CursorStep.CursorNext:
                        if (cursor < (kits.Count - 1))
                        {
                            cursor++;
                            kit = kits[cursor];
                        }
                        return kit;

                    case CursorStep.CursorLast:
                        cursor = kits.Count - 1;
                        return kits[cursor];
                }
            }
            return kit;
        }

		public bool Remove(string kitCode)
		{
			for (int i = 0; i < kits.Count; i++)
				if (kits[i].Code == kitCode)
				{
					kits.RemoveAt(i);
					MoveTo(CursorStep.CursorFirst);
					isModified = true;
					return true;
				}
			return false;
		}

        public bool saveDb(string dbkFile)
        {
            bool flag = true;
            try
            {
                Stream serializationStream = File.Open(dbkFile, FileMode.Create);
                new BinaryFormatter().Serialize(serializationStream, kits);
                serializationStream.Close();
                isModified = false;
            }
            catch (Exception)
            {
                flag = false;
            }
            return flag;
        }

        public bool Update(KSKit kit)
        {
			try
			{
				for (int i = 0; i < kits.Count; i++)
					if (kits[i].Code == kit.Code)
					{
						kits[i] = kit;
						isModified = true;
						return true;
					}
			}
			catch (Exception)
			{
			}
            return false;
        }

        public KSKit CurrentKit
        {
            get
            {
                KSKit kit = null;
                if (cursor != -1)
                    kit = kits[cursor];
                return kit;
            }
			set
			{
				if (value != null)
					for (int i = 0; i < kits.Count; i++)
						if (kits[i].Code == value.Code)
						{
							cursor = i;
							return;
						}
			}
        }

		public bool IsEmpty
		{
			get { return (kits.Count == 0); }
		}

		public bool IsFirstKit
		{
			get { return (!IsEmpty && (cursor == 0)); }
		}

		public bool IsLastKit
		{
			get { return (!IsEmpty && (cursor == (kits.Count - 1))); }
		}

		public bool IsModified
		{
			get { return isModified; }
		}
    }
}

