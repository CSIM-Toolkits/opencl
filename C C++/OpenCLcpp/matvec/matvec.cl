__kernel void matvec_mult(__global float4* matrix,
                          __global float4* vector,
                          __global float* result) {
   
   int i = get_global_id(0);
   result[i] = dot(matrix[i], vector[0]);

   printf("global id = %d, local id = %d, global size = %lu, local size = %lu\n", get_global_id(0), get_local_id(0), get_global_size(0), get_local_size(0));

}

