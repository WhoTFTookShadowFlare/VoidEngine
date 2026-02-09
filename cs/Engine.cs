using System.Runtime.CompilerServices;
using System.Collections.Generic;
using VoidEngine.Math;
using VoidEngine.IO;

namespace VoidEngine
{
    public class Engine {
		private Engine() {}

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern double GetDelta();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern string GetExecutablePath();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern string GetDataDirectory();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern Window GetMainWindow();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern Rect2i[] GetMonitorAreas();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern Vec2i GetWorkspaceArea();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern Rect2i[] GetWorkspaceChunked();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern Rect2i[] GetWorkspaceDeadzones();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern Rect2i[] GetWorkspaceCaves();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public static extern Rect2i[] GetWorkspacePlateaus();
	}
}

