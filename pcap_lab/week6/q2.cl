// Kernels.cl

__kernel void swap(__global int *arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

__kernel void parallelSelectionSort(__global int *arr, const int n) {
    for(int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for(int j = i+1; j < n; j++) {
            if(arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if(minIndex != i) {
            swap(arr, i, minIndex);
        }
    }
}
