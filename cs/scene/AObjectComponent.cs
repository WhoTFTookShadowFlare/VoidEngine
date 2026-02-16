using System.Runtime.CompilerServices;
using System;

namespace VoidEngine.Scene
{
    public abstract class AObjectComponent
	{
#pragma warning disable CS0649
		internal IntPtr cxxObject;
#pragma warning restore CS0649

		public extern GameObject[] TiedTo
		{
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}

		public abstract void Update(double delta);
		public abstract void Draw(double delta);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern AObjectComponent();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern ~AObjectComponent();
	}
}

