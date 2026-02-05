using System.Runtime.CompilerServices;

namespace VoidEngine.Math
{
    public struct Vec4i
	{
		public int X { get; set; }
		public int Y { get; set; }
		public int Z { get; set; }
		public int W { get; set; }

		public Vec4i(int x, int y, int z, int w)
		{
			this.X = x;
			this.Y = y;
			this.Z = z;
			this.W = w;
		}

		public override string ToString() => $"({X}, {Y}, {Z}, {W})";
	}
}

