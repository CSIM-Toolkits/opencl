


__kernel void hello_kernel(__global char16 *msg) {



    float teste[9]= (0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01);



   *msg = (char16)('H', 'e', 'l', 'l', 'o', ' ',
      'k', 'e', 'r', 'n', 'e', 'l', '!', '!', '!', '\0');
}
