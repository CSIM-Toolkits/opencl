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



__kernel void DoGradient(const __global float* in,const __global float* out,__global float* n,__global float* nl,__global float* l,__global float* sl,
__global float* s,__global float* so,__global float* o,__global float* no, __global float* fPerona0,__global float* fPerona1,__global float* fPerona2,
__global float* fPerona3,__global float* fPerona4,__global float* fPerona5,__global float* fPerona6,__global float* fPerona7, const float kappa, const float even,const float odd)
{
        int index = getCurrentIndex();
        
       //do gradient north
	if((index-width)<0){
		n[index] = 0;
	}else{
                
		n[index] =  in[index - width] - getCurrentPixel(in);
             }

       //do gradient south
	if((index+width)> (width*height)){
		s[index] = 0;
	}else{
                
		s[index] =  in[index + width] - getCurrentPixel(in);
             }

        //do gradiente east and west
	l[index] =  in[index + 1] - getCurrentPixel(in);
	o[index] =  in[index - 1] - getCurrentPixel(in);

        //do gradient northeast
	if((index - width + 1)<0){
		nl[index] = 0;
	}else{
                
        	nl[index] =  in[index - width + 1] - getCurrentPixel(in);
             }

        //do gradient northwest
	if((index - width - 1)<0){
		no[index] = 0;
	}else{
                
	        no[index] =  in[index - width - 1] - getCurrentPixel(in);
             }


        //do gradient southeast
	if((index + width + 1)> (width*height)){
		sl[index] = 0;
	}else{
                
	        sl[index] =  in[index + width + 1] - getCurrentPixel(in);
             }

        //do gradient south-west
	if((index + width - 1)> (width*height)){
		so[index] = 0;
	}else{
                
	        so[index] =  in[index + width - 1] - getCurrentPixel(in);
             }


        //Math.exp(-Math.pow(Grad[k].getPixel(i, j) / getK(), 2))   
        //fD[0] = GradN;fD[1] = GradNL;fD[2] = GradL;fD[3] = GradSL;fD[4] = GradS;fD[5] = GradSO;fD[6] = GradO;fD[7] = GradNO;

	fPerona0[index] = exp(-pow((float)(n[index]/kappa),2));
	fPerona1[index] = exp(-pow((float)(nl[index]/kappa),2));
	fPerona2[index] = exp(-pow((float)(l[index]/kappa),2));
	fPerona3[index] = exp(-pow((float)(sl[index]/kappa),2));
	fPerona4[index] = exp(-pow((float)(s[index]/kappa),2));
	fPerona5[index] = exp(-pow((float)(so[index]/kappa),2));
	fPerona6[index] = exp(-pow((float)(o[index]/kappa),2));
	fPerona7[index] = exp(-pow((float)(no[index]/kappa),2));


        //printf("Value = %f \n",in[gidx])
        //printf("Value = %f \n",kappa);
        //printf("Value = %f \n",even);
        //printf("Value = %f \n",odd);

}


__kernel void AnisotropicClassic(const __global float* in,__global float* out,__global float* n,__global float* nl,__global float* l,__global float* sl,
__global float* s,__global float* so,__global float* o,__global float* no, __global float* fPerona0,__global float* fPerona1,__global float* fPerona2,
__global float* fPerona3,__global float* fPerona4,__global float* fPerona5,__global float* fPerona6,__global float* fPerona7, const float kappa, const float even,const float odd)
{
        float diffImg[8];
        int index = getCurrentIndex();

	diffImg[0] = even*fPerona0[index]*n[index];
	diffImg[1] = odd*fPerona1[index]*nl[index];
	diffImg[2] = even*fPerona2[index]*l[index];
	diffImg[3] = odd*fPerona3[index]*sl[index];
	diffImg[4] = even*fPerona4[index]*s[index];
	diffImg[5] = odd*fPerona5[index]*so[index];
	diffImg[6] = even*fPerona6[index]*o[index];
	diffImg[7] = odd*fPerona7[index]*no[index];

        float sum=0.0;

	for (int k = 0; k < 8; k++) {
		sum += diffImg[k];
	}


	out[index] = (float)(in[index] + sum);
        //printf("Value = %f \n",diffImg[0]);


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






