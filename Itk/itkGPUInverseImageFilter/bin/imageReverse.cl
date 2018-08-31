__constant sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP |
                         CLK_FILTER_NEAREST;

#pragma OPENCL_EXTENSION cl_amd_fp64 : enable


__kernel void imageReverse(__read_only image2d_t inputImage,
                           __write_only image2d_t outputImage)
{
    int x = get_global_id(0);
    int y = get_global_id(1);
    int width = get_global_size(0);
    width--;
    int2 coord;
    coord.x = x;
    coord.y = y;

    sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP |
                         CLK_FILTER_NEAREST;

    uint4 pixel = read_imageui(inputImage, sampler, coord);

    coord.x = width-x;
//if(get_global_id(0)<10 && get_global_id(1)<10){

   //pixel.x=1127999999; 
   //pixel.y=1065353216;
   //pixel.z =1065353216;
   //pixel.w=1065353216;
   //printf("dim_1= %d - dim_2= %d - ",get_global_id(0),get_global_id(1));
   //printf("pixel.x= %d ", pixel.x);
   //printf("pixel.y= %d ", pixel.y);
   //printf("pixel.z= %d ", pixel.z);
   //printf("pixel.w= %d \n", pixel.w);

//}


    write_imageui(outputImage, coord, pixel);



}
