﻿namespace iNEMO_Application.Properties
{
    using System;
    using System.CodeDom.Compiler;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Drawing;
    using System.Globalization;
    using System.Resources;
    using System.Runtime.CompilerServices;

    [DebuggerNonUserCode, GeneratedCode("System.Resources.Tools.StronglyTypedResourceBuilder", "2.0.0.0"), CompilerGenerated]
    public class Resources
    {
        private static CultureInfo resourceCulture;
        private static System.Resources.ResourceManager resourceMan;

        internal Resources()
        {
        }

        public static Bitmap Book_angleHS
        {
            get
            {
                return (Bitmap) ResourceManager.GetObject("Book_angleHS", resourceCulture);
            }
        }

        internal static Bitmap connected2
        {
            get
            {
                return (Bitmap) ResourceManager.GetObject("connected2", resourceCulture);
            }
        }

        [EditorBrowsable(EditorBrowsableState.Advanced)]
        internal static CultureInfo Culture
        {
            get
            {
                return resourceCulture;
            }
            set
            {
                resourceCulture = value;
            }
        }

		public static Bitmap documentSave
        {
            get
            {
                return (Bitmap) ResourceManager.GetObject("documentSave", resourceCulture);
            }
        }

		public static Bitmap documentSaveAs
        {
            get
            {
                return (Bitmap) ResourceManager.GetObject("documentSaveAs", resourceCulture);
            }
        }

		public static Bitmap Help
        {
            get
            {
                return (Bitmap) ResourceManager.GetObject("Help", resourceCulture);
            }
        }

        internal static Icon Logo
        {
            get
            {
                return (Icon) ResourceManager.GetObject("Logo", resourceCulture);
            }
        }

        public static Bitmap NewDocumentHS
        {
            get
            {
                return (Bitmap) ResourceManager.GetObject("NewDocumentHS", resourceCulture);
            }
        }

        public static Bitmap openHS
        {
            get
            {
                return (Bitmap) ResourceManager.GetObject("openHS", resourceCulture);
            }
        }

        [EditorBrowsable(EditorBrowsableState.Advanced)]
        internal static System.Resources.ResourceManager ResourceManager
        {
            get
            {
                if (object.ReferenceEquals(resourceMan, null))
                {
                    System.Resources.ResourceManager manager = new System.Resources.ResourceManager("iNEMO_Application.Properties.Resources", typeof(Resources).Assembly);
                    resourceMan = manager;
                }
                return resourceMan;
            }
        }

        internal static Bitmap splash
        {
            get
            {
                return (Bitmap) ResourceManager.GetObject("splash", resourceCulture);
            }
        }

        internal static Bitmap stop2
        {
            get
            {
                return (Bitmap) ResourceManager.GetObject("stop2", resourceCulture);
            }
        }

        internal static Bitmap wait2
        {
            get
            {
                return (Bitmap) ResourceManager.GetObject("wait2", resourceCulture);
            }
        }
    }
}

