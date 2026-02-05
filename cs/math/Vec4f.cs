using System.Runtime.CompilerServices;

namespace VoidEngine.Math
{
    public struct Vec4f
	{
		public float X { get; set; }
		public float Y { get; set; }
		public float Z { get; set; }
		public float W { get; set; }

		public Vec4f(float x, float y, float z, float w)
		{
			this.X = x;
			this.Y = y;
			this.Z = z;
			this.W = w;
		}

		public Vec4f(double x, double y, double z, double w)
		{
			this.X = (float) x;
			this.Y = (float) y;
			this.Z = (float) z;
			this.W = (float) w;
		}

		public override string ToString() => $"({X}, {Y}, {Z}, {W})";
	}
}

