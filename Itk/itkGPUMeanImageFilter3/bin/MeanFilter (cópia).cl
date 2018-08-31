__kernel void MeanFilter(const __global float* in,
                         __global float* out,
                         int radiusx, int radiusy, int radiusz,
                         int width, int height, int depth)
{

  int gix = (int)get_global_id(0);
  int giy = (int)get_global_id(1);
  int giz = (int)get_global_id(2);

  unsigned int gidx = width*(giz*height + giy) + gix;

  float sum = 0;
  unsigned int num = 0;

  /* NOTE: More than three-level nested conditional statements (e.g.,
     if A && B && C..) invalidates command queue during kernel
     execution on Apple OpenCL 1.0 (such Macbook Pro with NVIDIA 9600M
     GT). Therefore, we flattened conditional statements. */
  bool isValid = true;
  if(gix >= width) isValid = false;
  if(giy >= height) isValid = false;
  if(giz >= depth) isValid = false;

  if( isValid )
  {

/*
    // Clamping boundary condition
    for(int z = max(0, (int)(giz-radiusz)); z <= min((int)(depth-1), (int)(giz+radiusz)); z++)
    {
      for(int y = max((int)0, (int)(giy-radiusy)); y <= min((int)(height-1), (int)(giy+radiusy)); y++)
      {
        for(int x = max((int)0, (int)(gix-radiusx)); x <= min((int)(width-1), (int)(gix+radiusx)); x++)
        {
          unsigned int cidx = width*(z*height + y) + x;

          sum += (float)in[cidx];
          num++;
        }
      }
    }
*/

    // Zero-flux boundary condition
    num = (2*radiusx + 1)*(2*radiusy + 1)*(2*radiusz + 1);
    for(int z = giz-radiusz; z <= giz+radiusz; z++)
    {
      unsigned int zid = (unsigned int)(min(max(0, z),depth-1));
      for(int y = giy-radiusy; y <= giy+radiusy; y++)
      {
        unsigned int yid = (unsigned int)(min(max(0, y),height-1));
        for(int x = gix-radiusx; x <= gix+radiusx; x++)
        {
          unsigned int cidx = width*(zid*height + yid) + (unsigned int)(min(max(0, x),width-1));

          sum += (float)in[cidx];
        }
      }
    }

    out[gidx] = (float)(sum/(float)num);
  }

}
