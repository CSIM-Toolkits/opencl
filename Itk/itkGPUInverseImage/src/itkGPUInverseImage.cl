
__kernel void imageInverse2D(__global const PIXELTYPE* a, __global PIXELTYPE* c, unsigned int nElem)
{
	unsigned int width = get_global_size(0);
	unsigned int gix = get_global_id(0);
	unsigned int giy = get_global_id(1);
	unsigned int gidx = giy*width + gix;


    if (gidx < nElem)
    {
      unsigned int aux = (nElem-1) - gidx;
      c[aux] = a[gidx]; 
    }
}

