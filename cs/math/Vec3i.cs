using System.Runtime.CompilerServices;

namespace VoidEngine.Math
{
    public struct Vec3i
	{
		public int X { get; set; }
		public int Y { get; set; }
		public int Z { get; set; }

		public Vec3i(int x, int y, int z)
		{
			this.X = x;
			this.Y = y;
			this.Z = z;
		}

		public override string ToString() => $"({X}, {Y}, {Z})";
	}
}

