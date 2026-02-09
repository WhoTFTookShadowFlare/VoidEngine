using System;
using System.Runtime.CompilerServices;
using VoidEngine.Math;

namespace VoidEngine.IO
{
    public sealed class Window
	{
#pragma warning disable CS0649
		internal IntPtr cxxObject;
#pragma warning restore CS0649

		public extern Vec2i Position {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			set;
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}

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

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Window(WindowCreationOptions options);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern ~Window();
	}
}

