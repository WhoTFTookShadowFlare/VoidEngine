using System.Runtime.CompilerServices;

namespace VoidEngine.Math
{
    public class Rect2f
	{
		public Vec2f Position { get; set; }
		public Vec2f Size { get; set; }
		
		public Rect2f(Vec2f position, Vec2f size) {
			this.Position = position;
			this.Size = size;
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

		public override string ToString() => $"( Position: {Position}, Size: {Size} )";
	}
}

