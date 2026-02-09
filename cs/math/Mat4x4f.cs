#pragma warning disable CS0414
namespace VoidEngine.Math
{
    public struct Mat4x4f {
#pragma warning disable CS0169
		private float
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33;
#pragma warning restore CS0169

		public static Mat4x4f Identity()
		{
			Mat4x4f matrix = default;
			matrix.m00 = 1.0f;
			matrix.m11 = 1.0f;
			matrix.m22 = 1.0f;
			matrix.m33 = 1.0f;
			return matrix;
		}
	}
}
#pragma warning restore CS0414

