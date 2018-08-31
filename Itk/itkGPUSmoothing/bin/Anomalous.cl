

void add( __global float* array, float c) {
	for (int i=0; i<width*height; i++){
		array[i] = array[i] + c;
	}
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

bool checkDimensions(int x , int y, int z){
	bool isValid = true;

	if(x >= width){ isValid = false;}
	if(y >= height){isValid = false;}
	if(z >= depth) {isValid = false;}

	return isValid;	
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

void getNeighborhood2D(int *arg,const __global float* in){  
  
	int index[8];

	arg[0]= 0;  arg[1]= 0;  arg[2]= 0;  arg[3]= 0;  arg[4]= 0;  arg[5]= 0;  arg[6]= 0;  arg[7]= 0;  arg[8]= 0;

	int x = (int)get_global_id(0);
	int y = (int)get_global_id(1);
	int z = (int)get_global_id(2);

	if(checkDimensions(x,y,z))
	{

		  index[0]=(getCurrentIndex() + width)-1;
		  index[1]=(getCurrentIndex() + width);
		  index[2]=(getCurrentIndex() + width)+1;
		  index[3]=getCurrentIndex()-1;
		  index[4]=getCurrentIndex();
		  index[5]=getCurrentIndex()+1;
		  index[6]=(getCurrentIndex() - width)-1;
		  index[7]=(getCurrentIndex() - width);
		  index[8]=(getCurrentIndex() - width)+1;


		  if(arg[0]>=0 || arg[0]<=width*height) arg[0]=in[index[0]];
		  if(arg[1]>=0 || arg[1]<=width*height) arg[1]=in[index[1]];
		  if(arg[2]>=0 || arg[2]<=width*height) arg[2]=in[index[2]];
		  if(arg[3]>=0 || arg[3]<=width*height) arg[3]=in[index[3]];
		  if(arg[4]>=0 || arg[4]<=width*height) arg[4]=in[index[4]];
		  if(arg[5]>=0 || arg[5]<=width*height) arg[5]=in[index[5]];
		  if(arg[6]>=0 || arg[6]<=width*height) arg[6]=in[index[6]];
		  if(arg[7]>=0 || arg[7]<=width*height) arg[7]=in[index[7]];
		  if(arg[8]>=0 || arg[8]<=width*height) arg[8]=in[index[8]];


		/*
		 if(get_global_id(0)==1 && (int)get_global_id(1)==1){

		      printf("Vizinhança[0]: %d \n", index[0]);     
		      printf("Vizinhança[1]: %d \n", index[1]);     
		      printf("Vizinhança[2]: %d \n", index[2]);     
		      printf("Vizinhança[3]: %d \n", index[3]);     
		      printf("Vizinhança[4]: %d \n", index[4]);     
		      printf("Vizinhança[5]: %d \n", index[5]);     
		      printf("Vizinhança[6]: %d \n", index[6]);     
		      printf("Vizinhança[7]: %d \n", index[7]);     
		      printf("Vizinhança[8]: %d \n", index[8]); 
		 }
		*/

	}
}

void DoAnomalous(const __global float* in,__global float* output,__global float* qOutput, float minImg){


	int NumInteration = (int)1;
	int nx = (int)width;
	int ny = (int)height;
        float dd = native_sqrt((float)2.0);
	//float *qOutput[width*height];

  
       if(get_global_id(0)==0 && (int)get_global_id(1)==0){
        printf("nx: %d \n", nx);
        printf("ny: %d \n", ny);
        printf("minImg: %f \n", minImg);
        printf("dd: %f \n", dd);        
       }
 


 
}



__kernel void Anomalous(__global const float *in,__global float *out,__global float *qOutput, float minImg)
{

	DoAnomalous(in,out,qOutput,minImg);
			
}

	

	 
