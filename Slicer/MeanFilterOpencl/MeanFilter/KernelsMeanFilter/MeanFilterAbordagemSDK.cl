bool checkDimensions(int x , int y, int z){
  bool isValid = true;

  if(x >= width) isValid = false;
  if(y >= height) isValid = false;
  if(z >= depth) isValid = false;

  return isValid;	
}

//print variable
//print variable

void printArrayInt(int *array, int length){

	for(int i=0;i<length;i++){
		printf("Array[%d]: %d \n", i,array[i]); 	
	}

}

void printArrayFloat(float *array, int length){

	for(int i=0;i<length;i++){
		printf("Array[%d]: %f \n", i,array[i]); 	
	}

}
float getMaximum(const __global float *in){

 float max = 0.0;
  
 for(int x=0; x<width;x++){
  for(int y=0; y<height;y++){
   for(int z=0; z<depth;z++){

    if(checkDimensions(x,y,z))
    {
     int index = width*(z*height + y) + x;
     if(in[index]>max) max= in[index];
    }	

 }}}
  
 return max;
}

float getMinimum(const __global float *in){

 float min = 0.0;
  
 for(int x=0; x<width;x++){
  for(int y=0; y<height;y++){
   for(int z=0; z<depth;z++){

    if(checkDimensions(x,y,z))
    {
     int index = width*(z*height + y) + x;
     if(in[index]<min) min= in[index];
    }	

 }}}
  
 return min;
}


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



void DoMeanFilter(const __global float* in,__global float* out,int radiusx, int radiusy, int radiusz){

  int index = getCurrentIndex();
  float sum = 0;
  unsigned int num = 0;


  int gix = (int)get_global_id(0);
  int giy = (int)get_global_id(1);
  int giz = (int)get_global_id(2);

  if( checkDimensions(gix,giy,giz) )
  {
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

    out[index] = (float)(sum/(float)num);
  }

}

__kernel void MeanFilter(const __global float* in,__global float* out,int radiusx, int radiusy, int radiusz)
{

  DoMeanFilter(in,out,radiusx,radiusy,radiusz);
  

}
