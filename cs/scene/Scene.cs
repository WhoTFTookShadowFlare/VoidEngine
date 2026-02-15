using System;
using System.Runtime.CompilerServices;

namespace VoidEngine.Scene
{
	public sealed class Scene
	{
#pragma warning disable CS0649
		internal IntPtr cxxObject;
#pragma warning restore CS0649

		public extern GameObject this[string name]
		{
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			set;
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Scene();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern ~Scene();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void draw(double delta);
	}
}

