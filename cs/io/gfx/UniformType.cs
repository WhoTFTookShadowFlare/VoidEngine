namespace VoidEngine.IO.GFX
{
    public enum UniformType : uint
	{
		INVALID = 0,

		// Basic types
		FLOAT,
		INT,

		// Structure types
		VECTOR_2F,
		VECTOR_3F,
		VECTOR_4F,
		VECTOR_2I,
		VECTOR_3I,
		VECTOR_4I,

		MATRIX_4X4F,

		// Object types
		SAMPLER_2D,
	}
}

