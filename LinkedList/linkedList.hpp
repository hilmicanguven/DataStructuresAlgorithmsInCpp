/*

Linked List

Linked List, içerisinde "Node" adı verilen item'lerin birbirlerine hayali bağlar ile bağlanmasıdır.
Node'lar memory'de contiguous bir alanda olma zorunluluğu yoktur.
Her Node bir sonraki Node'u gösteren bir pointer'a sahiptir.
Listedeki ilk (head) ve son (tail) elemanı gösteren pointer'lar bulunur.

Linked List ile yapılan işlemlerin Big(O) Complexity'leri 
    - Son'a eleman ekleme -> O(1)   // yeni node oluştur
                                        tail pointer'ı yeni node'u göster
                                        //birönceki last node'un next pointer'ını yeni oluşturduğun node'u göster

    - Son'dan eleman silme -> O(n)  // son eleman silindikten sonra kalan son elemanı bulmak için tüm liste baştan sonra iterate edilir

    - Başa eleman ekleme  -> O(1)
    - Baştan eleman silme -> O(1)   // head pointer doğrudan next'i gösterir, iterate etmeye gerek kalmaz

    - Ortadan eleman ekleme veya silme  -> O(n)

    - Belirli bir index'teki elemana erişmek -> O(n)    // vector gibi bir index mekanizması olmadığı için iterate edilir istediğimiz node'u bulana kadar.

    Vector ile kıyaslama yapıldığında, 
        ilk elemana ekleme/çıkarılma yapılması çok sık oluyorsa LL daha mantıklıdır.
        ancak index bazlı erişim yapılacaksa Vector daha mantıklıdır.
        "LL_vs_Vector_BigO.pdf" dökümanına göz atın...

*/

#include <iostream>

class Node
{
    public:
    int m_value;
    Node* next;

    Node(int v) : m_value(v) 
    {
        next = nullptr;
    };
    
};

class LinkedList
{
    public:
        LinkedList(int v) 
        {
            Node* new_node = new Node(v);
            
            head = new_node;
            tail = new_node;
            length = 1;
        };

        ~LinkedList()
        {
            std::cout << "Destructor Called: " << std::endl;
            // we need destructor to delete Node instances in memory
            Node* temp = head;

            while(nullptr != head)
            {
                head = head->next;
                std::cout << temp->m_value << " is deleted" << std::endl;
                delete temp;
                temp = head;
            }
        }
        
        void append(int v);
        void prepend(int v);
        bool insert(int index, int v);
        void delete_last();
        void delete_first();
        void delete_node(int index);
        Node* get(int index);
        bool set(int index, int v);
        void print_list();
        int get_head();
        int get_tail();
        void reverse();
    
    private:
        Node* head;
        Node* tail;
        int length{0};
};


void LinkedList::append(int v)
{
    Node* new_node = new Node(v);

    if(nullptr == head) // or alternatively if(length==0)
    {
        head = new_node;
        tail = new_node;
        length = 1;

    }
    else{
        tail->next = new_node;
        tail = new_node;
        length++;
    }
    // else         // alternative way to add but has worse time complexity
    // {
    //     Node* temp = head;
    //     while(temp->next){
    //         temp = temp->next;
    //     }
    //     temp->next = new_node;
    //     tail = new_node;
    // }
}

void LinkedList::delete_last()
{
    if(length == 0) return;
    Node* temp = head;

    if(1 == length)
    {
        // it is the case that we only have 1 node at beginning, if it is removed then head and tail still points an adress
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        Node* previous_before_tail = head;

        while(temp->next)
        {
            previous_before_tail = temp;
            temp = temp->next;
        }

        tail = previous_before_tail;    // tail moved previous since tail will be deleted
        tail->next = nullptr;
    }
    delete temp;
    length--;

    // if(length == 0) return;

    // Node* temp = head;
    // Node* previous_before_tail = head;

    // while(temp->next)
    // {
    //     previous_before_tail = temp;
    //     temp = temp->next;
    // }

    // tail = previous_before_tail;    // tail moved previous since tail will be deleted
    // tail->next = nullptr;
    // length--;
    // if(length == 0)
    // {
    //     // it is the case that we only have 1 node at beginning, if it is removed then head and tail still points an adress
    //     head = nullptr;
    //     tail = nullptr;
    // }
    // delete temp;
}

void LinkedList::delete_first()
{
    if(length == 0) return;
    
    Node* temp = head;

    if(1 == length)
    {
        // it is the case that we only have 1 node at beginning, if it is removed then head and tail still points an adress
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        head = head->next;
    }

    delete temp;
    length--;

}

void LinkedList::prepend(int v)
{
    Node* new_node = new Node(v);

    if(length == 0)
    {
        head = new_node;
        tail = new_node;
    }
    else
    {
        new_node->next = head;
        head = new_node;
    }
    
    length++;

}

Node* LinkedList::get(int index)
{
    if(index < 0 || index >= length) { return nullptr;}

    Node* temp = head;

    for(int i=0; i < index; i++) { temp = temp->next; }

    return temp;
}

bool LinkedList::set(int index, int v)
{
    if(index < 0 || index >= length) { return false;}

    Node* temp = head;

    for(int i=0; i < index; i++) { temp = temp->next; }

    temp->m_value = v;
    return true;
}

bool LinkedList::insert(int index, int v)
{
    if(index < 0 || index > length) { return false;}

    if(index == 0){
        prepend(v);
        return true;
    }
    if(index == length)
    {
        append(v);
        return true;
    }

    Node* temp = get(index-1);

    Node* new_node = new Node(v);

    new_node->next = temp->next;
    temp->next = new_node;
    length++;

    return true;
}

void LinkedList::delete_node(int index)
{
    if(index < 0 || index > length) { return;}

    if(index == 0)
    {
        delete_first();
        return;        
    }
    if(index == length - 1)
    {
        delete_last();
        return;        
    }

    Node* previous_of_deleted_node = get(index-1);

    Node* temp = previous_of_deleted_node->next;

    previous_of_deleted_node->next = temp->next;
    delete temp;
    
    length--;
}

void LinkedList::reverse()
{
    Node* temp = head;
    head = tail;
    tail = temp;
    
    Node* rev = temp->next;
    Node* before = nullptr;
    
    for(int i = 0 ; i < length-1 ; i++)
    {     
        rev = temp->next;
        temp->next = before;
        before = temp;
        temp = rev;
    }
}

void LinkedList::print_list()
{
    if(head)
    {
        Node* temp = head;

        // std::cout << "Head: " << get_head() << std::endl;
        // std::cout << "Tail : " << get_tail() << std::endl;
        while(temp)
        {
            std::cout << temp->m_value << "\t";
            temp = temp->next;
        }
        std::cout << "\n";
    }else{
        std::cout << "Linked List Empty \n";
    }
}

inline int LinkedList::get_head()
{
    return head->m_value;
}

inline int LinkedList::get_tail()
{
    return tail->m_value;
}

int ll_main()
{
    
    // LinkedList* ll = new LinkedList(67);
    // ll->print_list();
    // delete ll;  // for the pointer, it is required to call delete explicitly
    
    // {
    //     LinkedList ll_instance = LinkedList(16);
    //     ll_instance.print_list();
    // }
    // // ll_instance is deleted automatically after going out of scope

    LinkedList* ll = new LinkedList(67);
    ll->append(41);
    ll->append(6);
    ll->append(75);
    ll->prepend(16);
    ll->print_list();
    ll->delete_last();
    ll->delete_first();
    ll->delete_first();
    ll->delete_first();
    ll->delete_first();
    ll->print_list();
    ll->append(41);
    ll->append(6);
    ll->append(75);
    ll->print_list();
    std::cout << "Value at index 2 is: " << ll->get(2)->m_value << "\n";
    auto result = ll->set(2, 59);
    ll->print_list();
    std::cout << "New Element at index 2 is: " << ll->get(2)->m_value << "\n";
    ll->insert(0,0);
    ll->print_list();
    ll->insert(2,82);
    ll->print_list();
    ll->delete_node(0);
    ll->print_list();
    ll->reverse();
    ll->print_list();

    return 0;
}