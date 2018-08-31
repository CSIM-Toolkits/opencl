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


    out[gidx] = in[gidx];
  }

}
