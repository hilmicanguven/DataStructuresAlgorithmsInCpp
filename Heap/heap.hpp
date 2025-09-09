/*

Heap

Bu heap, işletim sistemlerinde bildiğimiz heap'ten farklıdır :)
Heap görsel açıdan Binary Search Tree ye benzer.
Ancak içindeki dataların yerleştimi farklıdır.
Her node kendi altındaki child-node lardan daha büyük değere sahiptir.
Root node maksimum değere sahiptir.
Heap, "complete" olmalıdır. sol node'un olduğu her yerde sağ node olmalıdır.
BST den farklı olarak duplicate node2lar olabilir.
Max yerine Min değerin Root da ve altınadkilerden küçük olduğu heap'e "Minumum Heap" denir.
farklı seviyelerdeki node'ların değerleri arasında bir ilişki bulunmaz. rasttgele dağılabilir.

Heap'i depolamak için
    - Vector kullanılabilir. Vector'in 0th elemanı boş bırakarak root,left,right şeklidne Vector'e doldurursak
        left_child_index = 2 * parent_index + 1;
        right_child_index = 2 * parent_index + 2;

        parent = int (child_position / 2)

    (aıfırıncı elemanın boş bırakılması yukarıdaki matematiği kolaylaştırmak için)
        
Heap'e eleman eklemek için
    bir üstteki elemanlar ile kıyaslayarak (bir while içinde) nereye koyulacğaına kararlaştırırız.
    while'ın bitme koşulu root node'a erişmemizdir.
    eğer node'un eklendiği konumda (vector'deki bir index'e tekabül eder), parent'ten büyük ise değerlerin swap edilmesi gerekir
    swap etmek için gerekli aritmetik yukarıda açıklandığı gibidir.

Heap'ten eleman silmek için
    yalnızca root node silinebilir.
    silindikten sonra kalan node'lar tekrar sıralanması gerekir, değerlerine göre
    root node silindikten sonra "complete tree oluşturmak için" en sondaki node root node'a atanır
    bu durumda yeni root'u child'ları ile kıyaslarız ve swap işlemi yaparız.
    bu işlemi en sona gidene kadar yapmalıyız.

Priority Queue

    Genellikle priority queue implemente ederken "heap" kullanılır.
    bunun nedeni Big O() ya dayanır.
    eğer Linked List ile implemente edersek
        tüm listeyi taramamız gerekirdi
    eğer Vector olsa
        yine tüm liste taranması gerekir, rastgele datalardan oluşacaktır
    eğer unordered_map olsa, (diyelim 90 en yüksek değer)
        bu key'e erişmek O(1) olur ancak 90'ın en büyük değer olduğunu bilmiyor olabiliriz
    Binary Search Tree kullanabiliriz
        ancak Balanced ise (O(log(n))) mantıklı olur. her zaman balanced olmaz
        sürekli sağ node'a veri eklenmişse LinkedList ten farklı olmaz
    Binary Heap implemente ederiz   
        bu durumda root'u sildikten sonra ağacın tekrar arrange edilmesi gerekir
        bu da ağacın height'i ile orantılıdır
        O(log(n)) olur bu durumda. +++ efficient

    
*/

#include <iostream>
#include <vector>
 
using namespace std;

class Heap
{
    private:
        vector<int> heap;
        /** @brief the function returns left child of node at index "index" */
        int leftChild(int index) { return 2*index + 1 ;}
        int rightChild(int index) { return 2*index + 2 ;}
        int parent(int index) { return (index - 1)/2 ;}
        void swap(int index1, int index2) 
        {
            auto temp = heap[index2];
            heap[index2] = heap[index1];
            heap[index1] = temp;
        }

    public:
        void insert(int value)
        {
            heap.push_back(value);

            int current = heap.size() - 1;

            while(current > 0 && heap[current] > heap[parent(current)])
            {
                swap(current, parent(current));
                current = parent(current);
                
            }
        }

        void printHeap()
        {
            cout << "\n[";
            for (size_t i = 0; i < heap.size(); i++)
            {
                cout << heap[i];
                if(i < heap.size() - 1)
                {
                    cout << ", ";
                }
            }
            cout << "]\n";
            
        }

        void sinkDown(int index)
        {
            int max_index = index;

            while(true)
            {
                int left_child_index = leftChild(index);
                int right_child_index = rightChild(index);

                if( left_child_index < heap.size() &&
                    heap[left_child_index] > heap[max_index])
                {
                    max_index = left_child_index;
                }
                
                if( right_child_index < heap.size() && 
                    heap[right_child_index] > heap[max_index])
                {
                    max_index = right_child_index;
                }

                if(max_index != index)
                {
                    swap(index, max_index);
                    index = max_index;
                }
                else
                {
                    return;
                }
            }
        }

        int remove()
        {
            if(heap.empty())
            {
                return INT_MIN;
            }

            int maxValue = heap.front();

            if(heap.size() == 1)
            {
                heap.pop_back();
            }
            else
            {
                // en sondaki eleman root'a atanır
                heap[0] = heap.back(); 
                // en sondaki eleman silinir
                heap.pop_back();
                // yeni root büyüklüğüne göre ağaçtaki uygun yere taşınır, aşağı level'e doğru dalar.
                sinkDown(0);

            }

            return maxValue;

        }


};


int heap_main()
{

    Heap* myHeap = new Heap();

    myHeap->insert(95);
    myHeap->insert(75);
    myHeap->insert(80);
    myHeap->insert(55);
    myHeap->insert(60);
    myHeap->insert(50);
    myHeap->insert(65);

    myHeap->printHeap();
    
    myHeap->remove();
    myHeap->printHeap();
    
    myHeap->remove();
    myHeap->printHeap();

    return 0;
}