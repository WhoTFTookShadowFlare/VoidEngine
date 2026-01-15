using System.Runtime.CompilerServices;

namespace VoidEngine.Math
{
    public class Rect2i
	{
		private Vec2i position = new Vec2i(0, 0), size = new Vec2i(1, 1);

		public Vec2i Position {
			get { return position; }
			set {
				if(value == null) return;
				position = value;
			}
		}

		public Vec2i Size {
			get { return size; }
			set {
				if(value == null) return;
				size = value;
			}
		}

		public Rect2i() {}

		public Rect2i(Vec2i position, Vec2i size) {
			if(position != null) this.position = position;
			if(size != null) this.size = size;
		}

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Vec2i GetEndPosition();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern bool CollidesWith(Rect2i other);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern bool ContainsPoint(Vec2i point);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Vec2i GetCenter();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern int GetVerticalCenter();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern int GetHorizontalCenter();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Vec2i[] GetRectVertices();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Rect2i[] SplitHorizontally(int point);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Rect2i[] SplitVertically(int point);
	}
}

