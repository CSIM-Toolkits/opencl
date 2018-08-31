bool checkDimensions(int x , int y, int z){
  bool isValid = true;

  if(x >= width) isValid = false;
  if(y >= height) isValid = false;
  if(z >= deep) isValid = false;

  return isValid;	
}


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
   for(int z=0; z<deep;z++){

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
   for(int z=0; z<deep;z++){

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

  int currentIndex = width*(z*height + y) + x;

  return currentIndex;
}



void DoMeanFilter(const __global float* in,__global float* out){

  int index = getCurrentIndex();
  float sum = 0.0;
  unsigned int num = radius*radius;
  int neighborhood[radius*radius];
  int step = (int)(radius/2);	
  int count = 0;


	 //get neigborhood
	 for(int j=-step;j<step+1;j++){
             for(int i=-step;i<step+1;i++){		
		neighborhood[count] = 0.0;
                neighborhood[count]=getCurrentIndex() + (width*j) + i;
		count++;
	     }
	 }

       //sum
       for(int i=0;i<radius*radius;i++){
             if(!isnan((float)neighborhood[i])) sum=sum+in[neighborhood[i]];

       }

                                               
       out[index] = (float)(sum/(float)num);

       //printf("Array[%d]: %f \n", index,out[index]); 	


 

}

__kernel void MeanFilter(const __global float* in,__global float* out)
{

  DoMeanFilter(in,out);
  

}
