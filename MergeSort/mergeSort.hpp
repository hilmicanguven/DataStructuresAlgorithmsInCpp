/*

Merge Sort

İki tane sort edilmiş array'in bir araya gelerek oluşturduğu array'i [1,3,7,8 , 2,4,5,6] 
tek bir sort edili array haline getirmek için kullanılır.

Merge Sort, listeyi sürekli 2'ye bölerek sub-array'ler oluşturur. sub-array'deki eleman sayısı 1 olana kadar bunu yapar.
sonrasında bu sub-array'leri bir araya getirerek sorted array yapar.
sub-array'e ayırma işlemi yapıldığında 
    1 - 3 - 7 - 8 - 2 - 4 - 5 - 6 
elimizde kalır. sonrasında merged ederek tekrar yukarı doğru array'i oluşturdğumuzda
1.iterasyon sonucu
    1,3  7,8  2,4   5,6
şeklinde sub-array elde ederiz. 2.iterasyon sonucunda
    1,3,7,8    2,4,5,6
elde ederiz. 3.iterasyon sonucunda
    1,2,3,4,5,6,7,8
elder ederiz.

Merge Sort yaparken, recursive bir şekilde benzer işlemleri tekrarlayacağız.
1- breaks array in half
2- base case: when sub-array size is 1 (where recursion ends)
3- call helper function ( @ref merge) to bring togerther sub-arrays into one result array

Complexity

Space Complexity: O(n)              // mevcut array'i alt sub-array'leri böldüğümüz için

Time Complexity : O(n * log(n) + n) // 8 elemanlı bir array'i 3 kere bölüp 3 adım da da tekrar bir araya getirdiğimiz için bu işlemler log(n) kadar tutar.
*/                                  // 8 elemena dokunduğumuz için O(n) kısmı da buradan gelir.

#include <iostream>

using namespace std;

/** @brief helper function to merge two sorted array */
void merge(int array[], int leftIndex, int midIndex, int rightIndex) {
    int leftArraySize = midIndex - leftIndex + 1;
    int rightArraySize = rightIndex - midIndex;

    int leftArray[leftArraySize];
    int rightArray[rightArraySize];

    for (int i = 0; i < leftArraySize; i++)
        leftArray[i] = array[leftIndex + i];
    for (int j = 0; j < rightArraySize; j++)
        rightArray[j] = array[midIndex + 1 + j];

    // ana array içerisindeki sort edili halde olan 2 array'i ayrı ayrı container'da tutarız.,

    int index = leftIndex;
    int i = 0;  // left array içerisindeki cursor'ı tutar
    int j = 0;  // right array içerisindeki cursor'ı tutar
    
    while (i < leftArraySize && j < rightArraySize) {
        if (leftArray[i] <= rightArray[j]) {
            array[index] = leftArray[i];
            index++;
            i++;
        }
        else {
            array[index] = rightArray[j];
            index++;
            j++;
        }
    }

    // right array'de eleman biterse left array'de kalan sayılar ana array'e taşınır
    while (i < leftArraySize) {
        array[index] = leftArray[i];
        index++;
        i++;
    }

    // left array'de eleman biterse right array'de kalan sayılar ana array'e taşınır
    while (j < rightArraySize) {
        array[index] = rightArray[j];
        index++;
        j++;
    }

}

void mergeSort(int array[], int leftIndex, int rightIndex)
{
    if (leftIndex >= rightIndex) return;
    
    int midIndex = leftIndex + (rightIndex - leftIndex) / 2;
    mergeSort(array, leftIndex, midIndex);
    mergeSort(array, midIndex+1, rightIndex);

    merge(array, leftIndex, midIndex, rightIndex);
}

int ms_sort_main()
{
    
    int myArray[] = {3,1,4,2};

    int size = sizeof(myArray) / sizeof(myArray[0]);
    int leftIndex = 0;
    int rightIndex = size - 1;


    mergeSort(myArray, leftIndex, rightIndex);


    for (auto value : myArray) {  
        cout << value << " ";
    }

    /*
        EXPECTED OUTPUT:
        ----------------
        1 2 3 4 
        
     */
    
    return 0;
}