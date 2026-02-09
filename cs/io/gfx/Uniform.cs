using System;
using System.Runtime.CompilerServices;

namespace VoidEngine.IO.GFX
{
    public sealed class Uniform
	{
#pragma warning disable CS0649
		internal IntPtr cxxObject;
#pragma warning restore CS0649

		private Uniform() {}

		public extern string Name {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}

		public extern uint Location {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}
		
		public extern UniformType Type {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}
	}
}

