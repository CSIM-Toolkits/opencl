__kernel void blank(__global int4 *x) {

   for(int i=0; i<25; i++) {
      x[i] *= 2;
   }

   printf("global id = %d, local id = %d, global size = %lu, local size = %lu\n", get_global_id(0), get_local_id(0), get_global_size(0), get_local_size(0));

}
