using System.Runtime.CompilerServices;

namespace VoidEngine.Math
{
    public struct Vec2f
    {
		public float X { get; set; }
		public float Y { get; set; }

		public Vec2f(float x, float y)
		{
			this.X = x;
			this.Y = y;
		}

		public Vec2f(double x, double y)
		{
			this.X = (float) x;
			this.Y = (float) y;
		}

		public override string ToString() => $"({X}, {Y})";
	}
}

