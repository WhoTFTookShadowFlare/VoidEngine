using System;
using System.Runtime.CompilerServices;

namespace VoidEngine.IO.GFX
{
    public sealed class Shader
	{
#pragma warning disable CS0649
		internal IntPtr cxxObject;
#pragma warning restore CS0649

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Shader(ShaderType type, AShaderSourceProvider sourceCode);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern ~Shader();
	}
}

