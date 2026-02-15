using System.Runtime.CompilerServices;
using System;

namespace VoidEngine.Scene
{
    public sealed class ComponentUpdater
	{
#pragma warning disable CS0649
		internal IntPtr cxxObject;
#pragma warning restore CS0649

		private ComponentUpdater() {}
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern ~ComponentUpdater();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern ComponentUpdater GetInstance(uint index);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern uint GetInstanceCount();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern bool IsComponentUpdating(AObjectComponent component);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void AddComponent(AObjectComponent component);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void RemoveComponent(AObjectComponent component);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern bool HandlesComponent(AObjectComponent component);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern void UpdateComponents(double delta);
	}
}

