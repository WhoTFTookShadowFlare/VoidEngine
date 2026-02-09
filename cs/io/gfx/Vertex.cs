using VoidEngine.Math;

namespace VoidEngine.IO.GFX
{
	public struct Vertex
	{
		Vec3f Position { get; set; }
		Vec4f Color { get; set; }
		Vec2f UV { get; set; }

		public Vertex(Vec3f position, Vec4f color, Vec2f uv)
		{
			this.Position = position;
			this.Color = color;
			this.UV = uv;
		}
	}
}

