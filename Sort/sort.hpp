/*

Bubble Sort : Bubbled maximum value into the end by switching next to it

ilk aıradaki elemanı bir sonraki eleman ile kıyaslayıp yer değiştiririz.
ilk iterasyon tamamlandığında en büyük sayının en sona geldiğini görürüz (bubbled into the end)
ikinci iterasyonda tekrar ilk elemandan başlar ve compare ederek son item - 1 kadar ilerleriz

*/

#include <iostream>
using namespace std;

void bubbleSort(int array[], int size)
{
    for(int i = size-1; i > 0 ; i-- )
    {
        for(int j = 0; j < i ; j++ )
        {
            if(array[j] > array[j+1])
            {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

/*

Selection Sort : Select minumum at index and switch iteration

ilk item'den başlarız, minumum index'i tutarız. diğer item'lere doğru ilerleriz.
ilk iterasyonu tamamladığımızda minumum index'i buluruz ve 1.sıradaki eleman ile yer değiştiririz.
ilk iterasyon tamamlandığında en düşük item'i bulmuş ve 0.index'e yerleştirmiş oluruz

*/

void selectionSort(int array[], int size)
{
    int min_index ;
    for(int i = 0; i < size ; i++ )
    {
        min_index = i;

        for(int j = i+1; j < size ; j++ )
        {
            if(array[j] < array[min_index])
            {
                min_index = j;
            }

        }
        
        int temp = array[i];
        array[i] = array[min_index];
        array[min_index] = temp;
    }
}

/*

Insertion Sort

Index 1 den başlayarak kendisinden önceki ile kıyaslarız. 
sonrasında 2.index'e ilerler eğer kendinden önce daha küçük bir değer görene başa alırız.
bu şekilde son index'e kadar gideriz.

*/

void insertionSort(int array[], int size)
{
    for(int i = 1; i < size ; i++ )
    {
        int temp = array[i];
        int j = i-1;

        while(j > -1 && temp < array[j] )
        {
            array[j+1] = array[j];
            array[j] = temp;
            j--;
        }
    }
}

/*

Complexity

Her üç sort algoritması için O(n^2) diyebiliriz.
her biri iç içe döngüden oluşur.
ANCAK, Insertion Sort eğer sorted veya neredeyse sorted bir array'den oluşuyorsa O(n) olarak değerlendirilebilir.

Space complexity, her biri için O(1) diyebiliriz.
hepsi array size ile işlem yapar, herhangi bir ek array oluşturma vb yapmaz.
*/

int sort_main()
{

    int my_array[] = {1,3,5,7,2,4,55,6,7,8};
    int size = sizeof(my_array) / sizeof(my_array[0]);

    // bubbleSort(my_array, size);
    // selectionSort(my_array, size);
    insertionSort(my_array, size);
    

    for(auto val: my_array)
    {
        cout << val << " ";
    }
    return 0;
}

