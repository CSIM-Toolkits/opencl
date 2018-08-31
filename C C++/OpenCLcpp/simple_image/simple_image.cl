__constant sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | 
      CLK_ADDRESS_CLAMP | CLK_FILTER_NEAREST; 

__kernel void simple_image(read_only image2d_t src_image,
                        write_only image2d_t dst_image) {

   /* Compute value to be subtracted from each pixel */
   uint offset = get_global_id(1) * 0x4000 + get_global_id(0) * 0x1000;

   /* Read pixel value */
   int2 coord = (int2)(get_global_id(0), get_global_id(1));
   uint4 pixel = read_imageui(src_image, sampler, coord);

   /* Subtract offset from pixel */
   pixel.x -= offset;

   /* Write new pixel value to output */
   write_imageui(dst_image, coord, pixel.x);

   printf("global id = %d, local id = %d, global size na dim 0 = %lu, local size na dim 0 = %lu\n", get_global_id(0), get_local_id(0), get_global_size(0), get_local_size(0));
   printf("global id = %d, local id = %d, global size na dim 1 = %lu, local size na dim 1 = %lu\n  -----\n", get_global_id(1), get_local_id(1), get_global_size(1), get_local_size(1));


}
