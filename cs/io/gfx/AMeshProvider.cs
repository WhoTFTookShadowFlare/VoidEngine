namespace VoidEngine.IO.GFX
{
    public abstract class AMeshProvider
	{
		public abstract Vertex[] GetVertices();
		public abstract uint[] GetIndices();
	}
}
