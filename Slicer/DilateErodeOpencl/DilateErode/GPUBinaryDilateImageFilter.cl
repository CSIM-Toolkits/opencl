/*=========================================================================
 *IN DILATE FILTER  FOREGROUND VALUE IS EQUAL BACKGROUND VALUE (DUE BACKGROUND VALUE IS NOT NECESSARY)
 *BORDER FOREGROUND VALUE IS JUST TO PAINT THE BORDER
 *SESUM IS NOT NECESSARY FOR DILATE FILTER
 *ONLY 3D IMAGES
 *
 *
 *=========================================================================*/

__kernel void BinaryDilateFilter(const __global float* in,__global float* out,__constant float* op,const int radius, int sesum,const int fgValue,
const int bgValue,const int borderFg)
{

  int gix = get_global_id(0);
  int giy = get_global_id(1);
  int giz = get_global_id(2);

  unsigned int gidx = width*(giz*height + giy) + gix;
  unsigned int opIdx = (2*radius + 1)*(2*radius + 1)*(2*radius + 1) - 1;

  bool isValid = true;
  if(gix < 0 || gix >= width) isValid = false;
  if(giy < 0 || giy >= height) isValid = false;
  if(giz < 0 || giz >= deep) isValid = false;

  float result = in[gidx];
  bool finished = false;

/*
if(gix==0 && giy==0 && giz==0){


      printf("ingidx: %d \n", gidx); 
      printf("opIdx: %d \n", opIdx); 
      printf("result: %f \n", result);

      printf("Radius: %d \n", radius); 
      printf("Sesum: %d \n", sesum); 
      printf("fgValue: %d \n", fgValue); 
      printf("bgValue: %d \n", bgValue); 
      printf("borderFg: %d \n", borderFg); 


	for(int i=0;i<26;i++){
		printf("Array[%d]: %f \n", i,op[i]); 	
	}

}
*/


  if( isValid )
  {
      for(int z = -radius; z <= radius; z++)
      {
	  for(int y = -radius; y <= radius; y++)
	  {
	    for(int x = -radius; x <= radius; x++)
	    {
		if(op[opIdx] == 1){
		    int tx = gix-x;
                    if(tx < 0 || tx >= width){
                        if(borderFg){ result = fgValue; finished = true; break; }
                        --opIdx; continue; }

		    int ty = giy-y;
                    if(ty < 0 || ty >= height){
                        if(borderFg){ result = fgValue; finished = true; break; }
                        --opIdx; continue; }

		    int tz = giz-z;
                    if(tz < 0 || tz >= deep){
                        if(borderFg){ result = fgValue; finished = true; break; }
                        --opIdx; continue; }

                    unsigned int tidx = width*height*tz + width*ty + tx;
		    if(in[tidx] == fgValue){
			result = fgValue;
			finished = true;
			break;
		    }
		}
		--opIdx;
	    }
	    if(finished) break;
	  }
	  if(finished) break;
     }

    out[gidx] = result;

/*
if(gix==255 && giy==255 && giz==50){

  printf("Count = %d \n", sesum); 
}*/

  }





}



