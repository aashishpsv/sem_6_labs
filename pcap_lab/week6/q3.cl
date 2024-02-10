#define N 10

__kernel void odd_sort(__global int *arr)
{
    int i = get_global_id(0);

    if(i % 2 == 0)
    {
        if(arr[i] > arr[i+1])
        {
            int temp = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = temp;
        }
    }
}

__kernel void even_sort(__global int *arr)
{
    int i = get_global_id(0);

    if(i % 2 == 1)
    {
        if(arr[i] > arr[i+1])
        {
            int temp = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = temp;
        }
    }
}
