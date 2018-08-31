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



void DoMeanFilter(const __global float* in,__global float* out){

  int index = getCurrentIndex();
  float sum = 0;
  unsigned int num = 9;
  int neighborhood[9];


       
       neighborhood[0]=(index - width)-1;
       neighborhood[1]=index - width;
       neighborhood[2]=(index - width)+1;

       neighborhood[3]=index-1;
       neighborhood[4]=index;
       neighborhood[5]=index+1;

       neighborhood[6]=(index + width) -1;
       neighborhood[7]=index + width;
       neighborhood[8]=(index+ width)+1;


       if(!isnan((float)neighborhood[0])) sum=sum+in[neighborhood[0]];
       if(!isnan((float)neighborhood[1])) sum=sum+in[neighborhood[1]];
       if(!isnan((float)neighborhood[2])) sum=sum+in[neighborhood[2]];
       if(!isnan((float)neighborhood[3])) sum=sum+in[neighborhood[3]];
       if(!isnan((float)neighborhood[4])) sum=sum+in[neighborhood[4]];
       if(!isnan((float)neighborhood[5])) sum=sum+in[neighborhood[5]];
       if(!isnan((float)neighborhood[6])) sum=sum+in[neighborhood[6]];
       if(!isnan((float)neighborhood[7])) sum=sum+in[neighborhood[7]];
       if(!isnan((float)neighborhood[8])) sum=sum+in[neighborhood[8]];

                                               
       out[index] = (float)(sum/(float)num);
  

}

__kernel void MeanFilter(const __global float* in,__global float* out)
{

  DoMeanFilter(in,out);
  

}
