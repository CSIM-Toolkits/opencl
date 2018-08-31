int getCurrentIndex(){


  int x = (int)get_global_id(0);
  int y = (int)get_global_id(1);
  int z = (int)get_global_id(2);

  int index = width*(z*height + y) + x;

  return index;
}



void DoSobelFilter(const __global float* in,__global float* out){

  int index = getCurrentIndex();
  int arg[9];
  float neighborhood[9];
  float Gx=0.0, Gy=0.0, G=0.0; 

  int step = 1;	
  int count = 0;


	 //get neigborhood
	 for(int j=-step;j<step+1;j++){
             for(int i=-step;i<step+1;i++){		
		arg[count] = 0.0;
                arg[count]=getCurrentIndex() + (width*j) + i;
		count++;
	     }
	 }

       //sum
       for(int i=0;i<9;i++){
             if(!isnan((float)arg[i])) neighborhood[i]=in[arg[i]];

       }


                                               
	Gx = -neighborhood[0] -(int)2*neighborhood[3] - neighborhood[6] + neighborhood[2] + (int)2*neighborhood[5] + neighborhood[8];
	Gy = -neighborhood[6] -(int)2*neighborhood[7] - neighborhood[8] + neighborhood[0] + (int)2*neighborhood[1] + neighborhood[2];
	G = native_divide(native_sqrt(Gx * Gx + Gy * Gy), (float)(2));

                                               
       out[index] = G;
  
  

}

__kernel void SobelFilter(const __global float* in,__global float* out)
{

  DoSobelFilter(in,out);
  

}
