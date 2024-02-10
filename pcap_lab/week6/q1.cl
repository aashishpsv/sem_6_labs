__kernel void str_repeat(__global char *inputStr, __global char *outputStr, int len) {
    int i = get_global_id(0);
    
    for (int j = 0; j < len; j++) {
        outputStr[i*len + j] = inputStr[j];
    }
}
