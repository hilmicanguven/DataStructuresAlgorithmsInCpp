/*

Stack - Yığın

Üst üste eklenen item'ler eklendiklerinin tersi sırasıyla erişilebilen (LIFO) veri yapısı türüdür.

Stack'e Ekleme(Push) ve Çıkarma(Pop) aynı pointer ile yapılır.

Push veya Pop, O(1) karmaşıklığa sahiptir. Index bilgisi olmadığından tüm stack'in traverse edilmesi gibi bir şey söz konusu değildir.
Stack'i LinkedList ya da Vector gibi veri yapıları kullanarak oluşturabiliriz.
Vector kullanıldığı durumda karmaşıklık O(n) olacaktır. Re-Indexing yapacağımız için
LinkedList, head pointer'ı tuttuğu ve biz de yalnızca head pointer'ı kullanarak pop/push yapacağımız için Linked List kullanacağız.


Queue - Kuyruk

Stack'in tersine, FIFO şeklinde depolanan verilerden oluşur.
Kuyrukta bekleyen insanlar analojisi sıkça kullanılır.
Queue'ya eleman eklenmesi -> Enqueue
Queue'dan eleman çıkarılması -> Deqeueu
olarak adlandırılır.

Queue implemente etmek için de farklı data structure kullanabiliriz.
    - eğer Vector ile implemente edersek, sona ekleme O(1), başa ekleme/çıkarma O(n) olacaktır re-indexing sebebiyşe
    - eğer LinkedList ile implemente edersek 
        head'e ekleme/çıkarma O(1)
        tail'e ekleme O(n) çıkarma O(1) ile yapabiliriz.
        bu durumda head'e ekleme=enqueue ve tail'den çıkarma=dequeue yaparsak
        her ikiside O(1) olur ve Vector'e kıyasla daha efficient olur.


*/


#include <iostream>

// Node sınıfı hem stack hem de queue için ortak, birebir aynı şekilde kullanılabilir.
// Node class can be used for both Stack and Queue in an exactly same way.
class Node
{
    public:
        int value;
        Node* next;

        Node(int val)
        {
            value = val;
            next=nullptr;
        }
};

class Stack
{
    private:
        Node* top;
        /** @brief  */
        int height;

    public:
        Stack(int value)
        {
            Node* new_node = new Node(value);
            top = new_node;
            height = 1;
        }

        void print_stack()
        {
            Node* temp = top;

            while(temp != nullptr)
            {
                std::cout << temp->value << std::endl;
                temp = temp->next;
            }
        }

        void push(int value)
        {
            Node* new_node = new Node(value);

            new_node->next = top;
            top = new_node;
            
            height++;
        }

        /**
         * @brief 
         * @note if stack is empty, the function returns 0xdeadbeaf magic number as an invalid value
         */
        int pop()
        {
            // if(!top) return INT_MIN;
            if(nullptr == top) return 0xDEADBEAF;

            Node* temp = top;
            int popped_value = top->value;
            top = top->next;
            delete temp;
            height--;
            if(height == 0 ) top = nullptr;

            return popped_value;
        }

        void get_top() { std::cout << "Top of the Stack: " << top->value << "\n";}
        void get_height() { std::cout << "Height of the Stack: " << height << "\n";}
};

class Queue
{
    private:
        Node* first;
        Node* last;
        int length;

    public:
        Queue(int val)
        {
            Node* new_node = new Node(val);
            first = new_node;
            last = new_node;
            length = 1;
        }

        void print_queue()
        {
            Node* temp = first;

            while(temp)
            {
                std::cout << temp->value << "\t";
                temp = temp->next;
            }
            std::cout << "\n";
        }

        void enqueue(int val)
        {
            Node* new_node = new Node(val);

            if(length == 0)
            {
                first = new_node;
                last = new_node;
            }
            else
            {
                last->next = new_node;
                last = new_node;
            }

            length++;
        }

        int dequeue()
        {
            if(first == nullptr) return 0xdeadbeaf;
            
            Node* temp = first;
            int dequeued_value = first->value;
            if(length == 1)
            {
                first = nullptr;
                last = nullptr;
            }
            else{

                first = first->next;
                
            }
            
            delete temp;
            length--;

            return dequeued_value;
        }

        void get_first() { std::cout << "First: " << first->value << "\n";}
        void get_last() { std::cout << "Last: " << last->value << "\n";}
        void get_length() { std::cout << "Length: " << length << "\n";}
};

#include <vector>

using namespace std;

/** @brief Stack i */
class VectorStack {
    private:
        vector<int> stackVector;
    
    public:
        vector<int>& getStackVector() {
            return stackVector;
        }
    
        void printStack() {
            for (int i = stackVector.size() - 1; i >= 0; i--) {
                cout << stackVector[i] << endl;
            }
        }
    
        bool isEmpty() {
            return stackVector.size() == 0;
        }
    
        int peek() {
            if (isEmpty()) {
                return int();
            } else {
                return stackVector[stackVector.size() - 1];
            }
        }
    
        int size() {
            return stackVector.size();
        }

        void push(int val)
        {
            stackVector.push_back(val);
        }
    
        void pop()
        {
            if(isEmpty())
            {
                return;
            }
            
            stackVector.pop_back();
        }    
};

Stack* my_stack = new Stack(16);

#include "exercises.hpp"


int stack_queue_main()
{

    // my_stack->get_top();
    // my_stack->push(41);
    // my_stack->pop();
    // my_stack->pop();
    // std::cout << "invalid value: " << my_stack->pop() << "\n";
    // my_stack->print_stack();

    // Queue* queue = new Queue(100);
    // queue->enqueue(101);
    // queue->enqueue(102);
    // queue->enqueue(103);
    // queue->print_queue();
    // queue->dequeue();
    // queue->print_queue();

    // std::string word = "hilmi-guven";
    
    // auto res = reverse_string(word);
    // std::cout << "Original: " << word << "\n";
    // std::cout << "Reversed: " << res << "\n";

    // std::string paranthesis = "((()))))";
    // std::cout << "is balanced: " << is_balanced_parentheses(paranthesis) << boolalpha << "\n";

    stack<int> int_stack;
    int_stack.push(2);
    int_stack.push(3);
    int_stack.push(1);
    int_stack.push(4);

    sortStack(int_stack);
    
    printStack(int_stack);

    
    return 0;
}