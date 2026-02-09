using System;
using System.Runtime.CompilerServices;
using VoidEngine.IO;
using VoidEngine.Math;

namespace VoidEngine.IO.GFX
{
    public sealed class Renderer
	{
		private Renderer() {}

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern void Clear(Vec4f clearColor);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern void BindRenderTarget(Window target);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern void SwapBuffers(Window win);
	}
}

