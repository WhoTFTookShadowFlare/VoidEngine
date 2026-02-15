using System;
using System.Runtime.CompilerServices;
using VoidEngine.IO.GFX;

namespace VoidEngine.Scene.Components
{
    public class MeshComponent : AObjectComponent
	{
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern MeshComponent();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern ~MeshComponent();

		public override void Update(double delta) {}
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public override extern void Draw(double delta);

		public extern TransformComponent Transform
		{
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			set;
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}

		public extern Mesh ToDraw
		{
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			set;
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}

		public extern GraphicsProgram Program
		{
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			set;
			[MethodImplAttribute(MethodImplOptions.InternalCall)]
			get;
		}
	}
}

