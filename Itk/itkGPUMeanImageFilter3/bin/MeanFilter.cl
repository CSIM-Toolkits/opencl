__kernel void MeanFilter(const __global short* in,
                         __global short* out,
                         int radiusx, int radiusy, int radiusz,
                         int width, int height, int depth)
{

  int gix = (int)get_global_id(0);
  int giy = (int)get_global_id(1);
  int giz = (int)get_global_id(2);

  unsigned int gidx = width*(giz*height + giy) + gix;

  short sum = 0;
  unsigned int num = 0;

  bool isValid = true;
  if(gix >= width) isValid = false;
  if(giy >= height) isValid = false;
  if(giz >= depth) isValid = false;

  if( isValid )
  {


    // Clamping boundary condition
    for(int z = max(0, (int)(giz-radiusz)); z <= min((int)(depth-1), (int)(giz+radiusz)); z++)
    {
      for(int y = max((int)0, (int)(giy-radiusy)); y <= min((int)(height-1), (int)(giy+radiusy)); y++)
      {
        for(int x = max((int)0, (int)(gix-radiusx)); x <= min((int)(width-1), (int)(gix+radiusx)); x++)
        {
          unsigned int cidx = width*(z*height + y) + x;

          sum += (short)in[cidx];
          num++;
        }
      }
    }


    out[gidx] = (short)(sum/(short)num);
  }

}
