float getCurrentPixel(const __global float* in){


  int x = (int)get_global_id(0);
  int y = (int)get_global_id(1);
  int z = (int)get_global_id(2);

  int index = width*(z*height + y) + x;

  return in[index];
}

int getCurrentIndex(){


  int x = (int)get_global_id(0);
  int y = (int)get_global_id(1);
  int z = (int)get_global_id(2);

  int index = width*(z*height + y) + x;

  return index;
}

bool checkDimensions(int x , int y, int z){
  bool isValid = true;

  if(x >= width) isValid = false;
  if(y >= height) isValid = false;
  if(z >= depth) isValid = false;

  return isValid;	
}


void getNeighborhood(__local int *arg){

}

__kernel void SobelFilter(__global const float *in,__global float *out,int radiusx, int radiusy)
{
  int gix = get_global_id(0);
  int giy = get_global_id(1);
  unsigned int gidx = width*giy + gix;
  float sum = 0;
  unsigned int num = 0;
  int size = width*height;

  __local int neighborhood[8];
  
  //printf("pixel: %d \n", gidx);
  //printf("Tamanho total: %d \n", size);

  if(gix < width && giy < height)
  {


      for(int y = max((int)0, (int)(giy-radiusy)); y <= min((int)(height-1), (int)(giy+radiusy)); y++)
      {
        for(int x = max((int)0, (int)(gix-radiusx)); x <= min((int)(width-1), (int)(gix+radiusx)); x++)
        {
          unsigned int cidx = width*y + (unsigned int)(min(max(0, x),width-1));

          sum += (float)in[cidx];
          num++;
        }
      }
    

    out[gidx] = (float)(sum/(float)num);
  }
			
}

	

	 
