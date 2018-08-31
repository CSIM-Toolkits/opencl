/*=========================================================================
 *
 *
 *
 *
 *
 *
 *=========================================================================*/

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




__kernel void AnisotropicClassic2(const __global float* in,__global float* out, const float kappa, const float even,const float odd)
{
        float diffImg[8];
        float fPerona[8];
	float gradN,gradS,gradL,gradO,gradNL,gradNO,gradSL,gradSO;
        int index = getCurrentIndex();
        
       //do gradient north
	if((index-width)<0){
		gradN = 0;
	}else{
                
		gradN =  in[index - width] - getCurrentPixel(in);
             }

       //do gradient south
	if((index+width)> (width*height)){
		gradS = 0;
	}else{
                
		gradS =  in[index + width] - getCurrentPixel(in);
             }

        //do gradiente east and west
	gradL =  in[index + 1] - getCurrentPixel(in);
	gradO =  in[index - 1] - getCurrentPixel(in);

        //do gradient northeast
	if((index - width + 1)<0){
		gradNL= 0;
	}else{
                
        	gradNL =  in[index - width + 1] - getCurrentPixel(in);
             }

        //do gradient northwest
	if((index - width - 1)<0){
		gradNO = 0;
	}else{
                
	        gradNO =  in[index - width - 1] - getCurrentPixel(in);
             }


        //do gradient southeast
	if((index + width + 1)> (width*height)){
		gradSL = 0;
	}else{
                
	        gradSL =  in[index + width + 1] - getCurrentPixel(in);
             }

        //do gradient south-west
	if((index + width - 1)> (width*height)){
		gradSO = 0;
	}else{
                
	        gradSO =  in[index + width - 1] - getCurrentPixel(in);
             }



	fPerona[0] = exp(-pow((float)(gradN/kappa),2));
	fPerona[1] = exp(-pow((float)(gradNL/kappa),2));
	fPerona[2] = exp(-pow((float)(gradL/kappa),2));
	fPerona[3] = exp(-pow((float)(gradSL/kappa),2));
	fPerona[4] = exp(-pow((float)(gradS/kappa),2));
	fPerona[5] = exp(-pow((float)(gradSO/kappa),2));
	fPerona[6] = exp(-pow((float)(gradO/kappa),2));
	fPerona[7] = exp(-pow((float)(gradNO/kappa),2));


/*

	fPerona[0] = (1.0 / (1.0 + pow((float)(gradN/kappa),2)));
	fPerona[1] = (1.0 / (1.0 + pow((float)(gradNL/kappa),2)));
	fPerona[2] = (1.0 / (1.0 + pow((float)(gradL/kappa),2)));
	fPerona[3] = (1.0 / (1.0 + pow((float)(gradSL/kappa),2)));
	fPerona[4] = (1.0 / (1.0 + pow((float)(gradS/kappa),2)));
	fPerona[5] = (1.0 / (1.0 + pow((float)(gradSO/kappa),2)));
	fPerona[6] = (1.0 / (1.0 + pow((float)(gradO/kappa),2)));
	fPerona[7] = (1.0 / (1.0 + pow((float)(gradNO/kappa),2)));

*/

	diffImg[0] = even*fPerona[0]*gradN;
	diffImg[1] = odd*fPerona[1]*gradNL;
	diffImg[2] = even*fPerona[2]*gradL;
	diffImg[3] = odd*fPerona[3]*gradSL;
	diffImg[4] = even*fPerona[4]*gradS;
	diffImg[5] = odd*fPerona[5]*gradSO;
	diffImg[6] = even*fPerona[6]*gradO;
	diffImg[7] = odd*fPerona[7]*gradNO;

        float sum=0.0;

	for (int k = 0; k < 8; k++) {
		sum += diffImg[k];
	}


	out[index] = (float)(in[index] + sum);
        //printf("Value = %f \n",diffImg[0]);


}






