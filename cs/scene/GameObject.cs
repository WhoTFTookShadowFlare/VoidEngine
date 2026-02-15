using System;
using System.Runtime.CompilerServices;

namespace VoidEngine.Scene
{
    public sealed class GameObject
	{
#pragma warning disable CS0649
		internal IntPtr cxxObject;
#pragma warning restore CS0649

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern GameObject();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern ~GameObject();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void AddComponent(AObjectComponent component);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern AObjectComponent[] GetComponents();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void RemoveComponent(AObjectComponent component);
	}
}

