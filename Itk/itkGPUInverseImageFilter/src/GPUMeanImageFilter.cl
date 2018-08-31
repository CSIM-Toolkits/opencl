
__kernel void MeanFilter2D(__global const PIXELTYPE* in,__global PIXELTYPE* out,int radiusx, int radiusy, int width, int height)
{
  int gix = get_global_id(0);
  int giy = get_global_id(1);
  unsigned int gidx = width*giy + gix;
  float sum = 0;
  unsigned int   num = 0;
  int size = width*height;
  
  //printf("Tamanho total: %d \n", size);

  if(gix < width && giy < height)
  {

    // Zero-flux boundary condition
    num = (2*radiusx + 1)*(2*radiusy + 1);
    for(int y = giy-radiusy; y <= giy+radiusy; y++)
    {
      unsigned int yid = (unsigned int)(min(max(0, y),height-1));
      for(int x = gix-radiusx; x <= gix+radiusx; x++)
      {
        unsigned int cidx = width*yid + (unsigned int)(min(max(0, x),width-1));

        sum += (float)in[cidx];
      }
    }

    out[gidx] = (PIXELTYPE)(sum/(float)num);
  }
}



