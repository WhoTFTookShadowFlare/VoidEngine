using System.Runtime.CompilerServices;

namespace VoidEngine.Math
{
    public class Rect2f
	{
		private Vec2f position = new Vec2f(0.0f, 0.0f), size = new Vec2f(1.0f, 1.0f);

		public Vec2f Position {
			get { return position; }
			set {
				if(value == null) return;
				position = value;
			}
		}

		public Vec2f Size {
			get { return size; }
			set {
				if(value == null) return;
				size = value;
			}
		}

		public Rect2f() {}

		public Rect2f(Vec2f position, Vec2f size) {
			if(position != null) this.position = position;
			if(size != null) this.size = size;
		}

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Vec2f GetEndPosition();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern bool CollidesWith(Rect2f other);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern bool ContainsPoint(Vec2f point);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Vec2f GetCenter();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern float GetVerticalCenter();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern float GetHorizontalCenter();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Vec2f[] GetRectVertices();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Rect2f[] SplitHorizontally(float point);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Rect2f[] SplitVertically(float point);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Rect2f Round();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Rect2f Floor();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern Rect2f Ceil();
	}
}

