using System;
using System.Runtime.CompilerServices;

using VoidEngine.Math;

namespace VoidEngine.IO.GFX
{
    public sealed class GraphicsProgram
	{
#pragma warning disable CS0649
		internal IntPtr cxxObject;
#pragma warning restore CS0649

		public extern Uniform[] Uniforms {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern GraphicsProgram(Shader vertex, Shader fragment);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern ~GraphicsProgram();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void Draw(Mesh mesh);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void SetUniform(Uniform target, float[] value);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void SetUniform(Uniform target, int[] value);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void SetUniform(Uniform target, Vec2f[] value);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void SetUniform(Uniform target, Vec3f[] value);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void SetUniform(Uniform target, Vec4f[] value);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void SetUniform(Uniform target, Vec2i[] value);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void SetUniform(Uniform target, Vec3i[] value);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void SetUniform(Uniform target, Vec4i[] value);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void SetUniform(Uniform target, Mat4x4f[] value);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void SetUniform(Uniform target, Texture[] value);
	}
}

