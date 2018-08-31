__kernel void threeLoops(__global float* result) {
   
   int i = get_global_id(0);

   result[i] = i;


}

