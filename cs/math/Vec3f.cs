using System.Runtime.CompilerServices;

namespace VoidEngine.Math
{
    public struct Vec3f
	{
		public float X { get; set; }
		public float Y { get; set; }
		public float Z { get; set; }

		public Vec3f(float x, float y, float z)
		{
			this.X = x;
			this.Y = y;
			this.Z = z;
		}

		public Vec3f(double x, double y, double z)
		{
			this.X = (float) x;
			this.Y = (float) y;
			this.Z = (float) z;
		}

		public override string ToString() => $"({X}, {Y}, {Z})";
	}
}

