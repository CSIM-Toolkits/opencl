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



void getNeighborhood3D(float *arg,const __global float* in){  
  
	int index[27];	

	int x = (int)get_global_id(0);
	int y = (int)get_global_id(1);
	int z = (int)get_global_id(2);

	if(checkDimensions(x,y,z))
	{


		 for(int i=0;i<27;i++){
			arg[i]=0;
		     }


		  //Afterward Frame
		  index[0]=(getCurrentIndex() + width)-1;
		  index[1]=(getCurrentIndex() + width);
		  index[2]=(getCurrentIndex() + width)+1;
		  index[3]=getCurrentIndex()-1;
		  index[4]=getCurrentIndex();
		  index[5]=getCurrentIndex()+1;
		  index[6]=(getCurrentIndex() - width)-1;
		  index[7]=(getCurrentIndex() - width);
		  index[8]=(getCurrentIndex() - width)+1;

		  //Middle Frame
		  index[9]=index[0]+width*height;
		  index[10]=index[1]+width*height;
		  index[11]=index[2]+width*height;
		  index[12]=index[3]+width*height;
		  index[13]=index[4]+width*height;
		  index[14]=index[5]+width*height;
		  index[15]=index[6]+width*height;
		  index[16]=index[7]+width*height;
		  index[17]=index[8]+width*height;

		  //Previous Frame
		  index[18]=index[9]+width*height;
		  index[19]=index[10]+width*height;
		  index[20]=index[11]+width*height;
		  index[21]=index[12]+width*height;
		  index[22]=index[13]+width*height;
		  index[23]=index[14]+width*height;
		  index[24]=index[15]+width*height;
		  index[25]=index[16]+width*height;
		  index[26]=index[17]+width*height;


		  if(index[0]>=0 || index[0]<=width*height*depth) arg[0]=in[index[0]];
		  if(index[1]>=0 || index[1]<=width*height*depth) arg[1]=in[index[1]];
		  if(index[2]>=0 || index[2]<=width*height*depth) arg[2]=in[index[2]];
		  if(index[3]>=0 || index[3]<=width*height*depth) arg[3]=in[index[3]];
		  if(index[4]>=0 || index[4]<=width*height*depth) arg[4]=in[index[4]];
		  if(index[5]>=0 || index[5]<=width*height*depth) arg[5]=in[index[5]];
		  if(index[6]>=0 || index[6]<=width*height*depth) arg[6]=in[index[6]];
		  if(index[7]>=0 || index[7]<=width*height*depth) arg[7]=in[index[7]];
		  if(index[8]>=0 || index[8]<=width*height*depth) arg[8]=in[index[8]];

		  if(index[9]>=0 || index[9]<=width*height*depth) arg[9]=in[index[9]];
		  if(index[10]>=0 || index[10]<=width*height*depth) arg[10]=in[index[10]];
		  if(index[11]>=0 || index[11]<=width*height*depth) arg[11]=in[index[11]];
		  if(index[12]>=0 || index[12]<=width*height*depth) arg[12]=in[index[12]];
		  if(index[13]>=0 || index[13]<=width*height*depth) arg[13]=in[index[13]];
		  if(index[14]>=0 || index[14]<=width*height*depth) arg[14]=in[index[14]];
		  if(index[15]>=0 || index[15]<=width*height*depth) arg[15]=in[index[15]];
		  if(index[16]>=0 || index[16]<=width*height*depth) arg[16]=in[index[16]];
		  if(index[17]>=0 || index[17]<=width*height*depth) arg[17]=in[index[17]];

		  if(index[18]>=0 || index[18]<=width*height*depth) arg[18]=in[index[18]];
		  if(index[19]>=0 || index[19]<=width*height*depth) arg[19]=in[index[19]];
		  if(index[20]>=0 || index[20]<=width*height*depth) arg[20]=in[index[20]];
		  if(index[21]>=0 || index[21]<=width*height*depth) arg[21]=in[index[21]];
		  if(index[22]>=0 || index[22]<=width*height*depth) arg[22]=in[index[22]];
		  if(index[23]>=0 || index[23]<=width*height*depth) arg[23]=in[index[23]];
		  if(index[24]>=0 || index[24]<=width*height*depth) arg[24]=in[index[24]];
		  if(index[25]>=0 || index[25]<=width*height*depth) arg[25]=in[index[25]];
		  if(index[26]>=0 || index[26]<=width*height*depth) arg[26]=in[index[26]];


		  //if(get_global_id(0)==0 && (int)get_global_id(1)==0 && (int)get_global_id(2)==0){
		  //	printArrayInt(index,27);
		  //}


	}
}


void DoSobelFilter(const __global float* in,__global float* out){


	float neighborhood[27];
	float Gx=0,Gy=0,Gz=0,G=0; 


	getNeighborhood3D(neighborhood,in);

	Gx = neighborhood[0] +(int)2*neighborhood[1] + neighborhood[2] + (int)2*neighborhood[3] + (int)4*neighborhood[4] + (int)2*neighborhood[5]+neighborhood[6]+
             (int)2*neighborhood[7] + neighborhood[8] + neighborhood[18] +(int)2*neighborhood[19] + neighborhood[20] + (int)2*neighborhood[21] +
             (int)4*neighborhood[22] + (int)2*neighborhood[23]+neighborhood[24] +(int)2*neighborhood[25] + neighborhood[26];
	
	Gy = neighborhood[0] +(int)2*neighborhood[1] + neighborhood[2] - neighborhood[5] -(int)2*neighborhood[7] - neighborhood[8] 
             + (int)2*neighborhood[9] +(int)4*neighborhood[10] + (int)2*neighborhood[11] - (int)2*neighborhood[15] -(int)4*neighborhood[16]-(int)2*neighborhood[17] 
             + neighborhood[18] +(int)2*neighborhood[19] + neighborhood[20] - neighborhood[24] -(int)2*neighborhood[25] - neighborhood[26];

	Gz = -neighborhood[0] + neighborhood[2] -(int)2*neighborhood[3] + (int)2*neighborhood[5] -neighborhood[6] + neighborhood[8]- (int)2*neighborhood[9]+
             (int)2*neighborhood[11] - (int)4*neighborhood[12] +(int)4*neighborhood[14] -(int)2*neighborhood[15] +(int)2*neighborhood[17]-        
              neighborhood[18] + neighborhood[20] - (int)2*neighborhood[21] +(int)2*neighborhood[23] -neighborhood[24] + neighborhood[26];


        //G = native_divide(native_sqrt(Gx * Gx* Gx + Gy * Gy * Gy + Gz * Gz * Gz), (float)(2));

        G = native_sqrt(Gx * Gx* Gx + Gy * Gy * Gy + Gz * Gz * Gz);

        //G = native_divide(cbrt(Gx * Gx + Gy * Gy + Gz * Gz), (float)(2));


	out[getCurrentIndex()] = G;

 
}

__kernel void SobelFilter(const __global float* in,__global float* out)
{

 	DoSobelFilter(in,out);

}
