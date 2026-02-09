using VoidEngine.Math;

namespace VoidEngine.IO.GFX
{
    public abstract class ATextureProvider
	{
		public abstract byte[] GetData();
		public abstract Vec2i GetSize();
	}
}

