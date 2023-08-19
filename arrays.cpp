#include <iostream>

void printarr(int arr[], std::size_t size)
{
    for(std::size_t i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

int main()
{
    int arr[] { 1, 2, 3, 4, 5, 6 , 7};
    std::size_t size_arr = sizeof(arr) / sizeof(arr[0]);

    for(const int &e : arr)
    {
        std::cout << e << " ";
    }
    std::cout << "\n";

    printarr(arr, size_arr);
}
