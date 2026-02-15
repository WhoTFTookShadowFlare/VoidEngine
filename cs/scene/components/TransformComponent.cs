using System;
using System.Runtime.CompilerServices;
using VoidEngine.Math;

namespace VoidEngine.Scene.Components
{
    public class TransformComponent : AObjectComponent
	{
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern TransformComponent();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern ~TransformComponent();

		public override void Update(double delta) {}
		public override void Draw(double delta) {}

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Mat4x4f GetMatrix();
	}
}

