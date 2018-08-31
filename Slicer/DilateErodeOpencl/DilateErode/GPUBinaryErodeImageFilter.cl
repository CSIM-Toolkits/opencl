/*=========================================================================
 *IN ERODE FILTER THE BACKGROUND VALUE WILL SUBSTITUTE DE FOREGROUND VALUE
 *BORDER FOREGROUND VALUE IS JUST TO PAINT THE BORDER
 *ONLY 3D IMAGES
 *
 *
 *
 *=========================================================================*/


__kernel void BinaryErodeFilter(const __global float* in,__global float* out,__constant float* op,const int radius,const int sesum,const int fgValue,
const int bgValue,const int borderFg)
{
  int gix = get_global_id(0);
  int giy = get_global_id(1);
  int giz = get_global_id(2);

  unsigned int gidx = width*(giz*height + giy) + gix;
  unsigned int sum = 0;
  unsigned int opIdx = 0;


  bool isValid = true;
  if(gix < 0 || gix >= width) isValid = false;
  if(giy < 0 || giy >= height) isValid = false;
  if(giz < 0 || giz >= deep) isValid = false;

    float result = in[gidx];
    bool finished = false;

  if( isValid )
  {

    for(int z = -radius; z <= radius; ++z)
    {
      for(int y = -radius; y <= radius; ++y)
      {
        for(int x = -radius; x <= radius; ++x)
        {
          if(op[opIdx] == 1)
          {
              int tx = gix-x;
              if(tx < 0 || tx >= width){
                    if(!borderFg){ finished = true; break; }
                    ++opIdx; ++sum; continue;
              }

              int ty = giy-y;
              if(ty < 0 || ty >= height){
                  if(!borderFg){ finished = true; break; }
                  ++opIdx; ++sum; continue;
              }

              int tz = giz-z;
              if(tz < 0 || tz >= deep){
                  if(!borderFg){ finished = true; break; }
                  ++opIdx; ++sum; continue;
              }

              unsigned int tidx = width*height*tz + width*ty + tx;

              if(in[tidx] == fgValue){
                ++sum;
              } 
          }

          opIdx++;
        }

        if(finished) break;
      }
      if(finished) break;
    }

    if(in[gidx] == fgValue && sum < sesum)
        result = bgValue;

    out[gidx] = result;
  }
}

