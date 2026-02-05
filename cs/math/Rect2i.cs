using System.Runtime.CompilerServices;

namespace VoidEngine.Math
{
    public struct Rect2i
	{
		public Vec2i Position { get; set; }
		public Vec2i Size { get; set; }

		public Rect2i(Vec2i position, Vec2i size) {
			this.Position = position;
			this.Size = size;
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

		public override string ToString() => $"( Position: {Position}, Size: {Size} )";
	}
}

