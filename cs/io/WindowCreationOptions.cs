using System;
using System.Runtime.CompilerServices;
using VoidEngine.Math;

namespace VoidEngine.IO
{
    public sealed class WindowCreationOptions
	{
#pragma warning disable CS0649
		internal IntPtr cxxObject;
#pragma warning restore CS0649
		
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern WindowCreationOptions();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern ~WindowCreationOptions();

		public extern Vec2i Size {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			set;
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}

		public extern string Title {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			set;
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}

		public extern bool Resizable {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			set;
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}

		public extern bool Borderless {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			set;
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}

		public extern bool AlwaysOnTop {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			set;
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}

		public extern bool Utility {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			set;
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}
	}
}

