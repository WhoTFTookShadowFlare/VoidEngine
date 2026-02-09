using System;
using System.Runtime.CompilerServices;
using VoidEngine.Math;

namespace VoidEngine.IO.GFX
{
    public sealed class FileTextureProvider : ATextureProvider
	{
#pragma warning disable CS0649
		internal IntPtr cxxObject;
#pragma warning restore CS0649

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern FileTextureProvider(string filePath);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern ~FileTextureProvider();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public override extern byte[] GetData();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public override extern Vec2i GetSize();
	}
}

