__constant sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP |
                         CLK_FILTER_NEAREST;
#pragma OPENCL_EXTENSION cl_amd_fp64 : enable

__kernel void simple_image(read_only image2d_t src_image,
                        write_only image2d_t dst_image) {

   /* Compute value to be subtracted from each pixel */
   uint offset = get_global_id(1) * 0x4000 + get_global_id(0) * 0x1000;

   /* Read pixel value */
   int2 coord = (int2)(get_global_id(0), get_global_id(1));
   uint4 pixel = read_imageui(src_image, sampler, coord);

   /* Subtract offset from pixel */
if(get_global_id(0)==0 && get_global_id(1)==0){
   //printf("PAssou aqui %d %d \n",get_global_id(0),get_global_id(1));
   pixel.x =0;
}else if (get_global_id(0)==0 && get_global_id(1)==1){

   pixel.x = 1060000000;
   pixel.y = 1065353216;
   pixel.z = 1065353216;
   pixel.w = 1065353216;
}else{
   pixel.x -=offset;
}
   printf("dim_1= %d - dim_2= %d \n ",get_global_id(0),get_global_id(1));
   printf("offest= %d ", offset);
   printf("pixel.x= %d ", pixel.x);
   printf("pixel.y= %d ", pixel.y);
   printf("pixel.z= %d ", pixel.z);
   printf("pixel.w= %d \n", pixel.w);


   /* Write new pixel value to output */
   write_imageui(dst_image, coord, pixel);


}
