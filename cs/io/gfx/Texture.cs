using System;
using System.Runtime.CompilerServices;

namespace VoidEngine.IO.GFX
{
    public sealed class Texture
	{
#pragma warning disable CS0649
		internal IntPtr cxxObject;
#pragma warning restore CS0649
		
		public bool Filtered {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			set;
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}

		public sbyte TextureSlot {
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Texture(sbyte slot);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern ~Texture();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void Bind();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void SetTextureProvider(ATextureProvider provider);
	}
}

