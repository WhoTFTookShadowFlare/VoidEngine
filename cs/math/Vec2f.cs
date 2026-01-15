using System.Runtime.CompilerServices;

namespace VoidEngine.Math
{
    public class Vec2f
    {
		public float x = 0.0f, y = 0.0f;

		public Vec2f() {}

		public Vec2f(float x, float y)
		{
			this.x = x;
			this.y = y;
		}

		public Vec2f(double x, double y)
		{
			this.x = (float) x;
			this.y = (float) y;
		}
	}
}

