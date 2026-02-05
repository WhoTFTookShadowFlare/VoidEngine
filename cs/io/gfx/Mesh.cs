using System;
using System.Runtime.CompilerServices;

namespace VoidEngine.IO.GFX
{
    public class Mesh
	{
#pragma warning disable CS0649
		internal IntPtr cxxObject;
#pragma warning restore CS0649

		public extern Vertex[] Vertices {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			set;
		}

		public extern uint[] Indices {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			set;
		}
		
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Mesh();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern ~Mesh();
	}
}

