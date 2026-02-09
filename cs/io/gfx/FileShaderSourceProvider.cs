using System;
using System.Runtime.CompilerServices;

namespace VoidEngine.IO.GFX
{
    public sealed class FileShaderSourceProvider : AShaderSourceProvider
	{
#pragma warning disable CS0649
		internal IntPtr cxxObject;
#pragma warning restore CS0649

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern FileShaderSourceProvider(string filePath);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern ~FileShaderSourceProvider();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public override extern string GetShaderSource();
	}
}

