/*

Doubly Linked List - Çift Yönlü Bağlı Liste

Linked List'e oldukça benzemesine ilaveten her node kendinden bir önceki node'u gösteren bir pointer'a sahiptir.


Delete Last: Son elemanı silmek için LL'de O(n) time complexity'e sahip iken 
    Burada Tail pointer'ın "prev" pointer'ı yeni tail olacağı için tüm node'u traverse etmemize gerek kalmaz. karmaşıklığa O(1) diyebiliriz.

Get: bir optimizasyon mevcut, eğer aradığımız index listenin ilk yarısında ise head'den başlayarak ararız,
eğer ikinci yarısında ise, tail'den geri gelerek ararız
*/

#include <iostream>

class Node {
    public:
        int m_value;
        Node* next;
        Node* prev;

        Node(int val) : m_value(val)
        {
            next = nullptr;
            prev = nullptr;
        }
};

class DoublyLinkedList {
    private:
        Node* head;
        Node* tail;
        int length;
    
    public:
        DoublyLinkedList(int val) {
            Node* new_node = new Node(val);
            head = new_node;
            tail = new_node;
            length = 1;
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
        bool isPalindrome();
        void reverse();
        /** @brief divide list into to two, where first half is values smaller than "x" and second half is greater than "x" */
        void partition_list(int x);
        void reverse_between(int startIndex, int endIndex);
        
};

void DoublyLinkedList::print_list()
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

inline int DoublyLinkedList::get_head()
{
    return head->m_value;
}

inline int DoublyLinkedList::get_tail()
{
    return tail->m_value;
}

void DoublyLinkedList::append(int v)
{
    Node* new_node = new Node(v);

    if(nullptr == head) // or alternatively if(length==0)
    {
        head = new_node;
        tail = new_node;
    }
    else{
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }

    length++;
}

void DoublyLinkedList::delete_last()
{
    if( length == 0 ) return;

    Node* temp = tail;

    if(length ==1)
    {   
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        tail = tail->prev;
        tail->next = nullptr;
    }
    
    delete temp;
    length--;
}

void DoublyLinkedList::prepend(int v)
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
        head->prev = new_node;
        head = new_node;
    }

    length++;
}

void DoublyLinkedList::delete_first()
{

    if(length == 0) return;
    
    Node * temp = head;
    
    if(length == 1)
    {   
        head = nullptr;
        tail = nullptr;
    }
    else
    {

        head = head->next;
        head->prev = nullptr;
        
        delete temp;
    }

    length--;
}

Node* DoublyLinkedList::get(int index)
{
    if(index < 0 || index >= length) { return nullptr;}

    
    Node* temp = head;
    
    /*
    there is optimization, 
    if index is in firsth half, then iterate starting from head
    if not, then iterate starting from the end
    */
    if(index < length/2)
    {
        for(int i=0; i < index; i++) { temp = temp->next; }
    }
    else
    {
        temp = tail;

        for(int i=length-1; i > index; i--) { temp = temp->prev; }
    }

    return temp;
}

bool DoublyLinkedList::set(int index, int v)
{
    Node* temp = get(index);

    if(temp)
    {
        temp->m_value = v;

        return true;
    }

    return false;
}

bool DoublyLinkedList::insert(int index, int v)
{
    if(index < 0 || index > length) { return false;}

    if(index == 0)
    {
        prepend(v);
        return true;
    }
    if(index == length)
    {
        append(v);
        return true;
    }

    Node* new_node = new Node(v);
    
    Node* before = get(index-1);
    Node* after = before->next;

    new_node->prev = before;
    new_node->next = after;

    before->next = new_node;
    after->prev = new_node;

    length++;

    return true;
}

void DoublyLinkedList::delete_node(int index)
{
    if(index < 0 || index >= length) { return;}

    if(index == 0)
    {
        delete_first();
        return;
    }
    if(index == length-1)
    {
        delete_last();
        return;
    }

    
    Node* temp = get(index);
    
    Node* before = temp->prev;
    Node* after = temp->next;

    before->next = after;
    after->prev = before;

    /*
    alternatively,
    temp->next>prev = temp>prev;
    temp->prev>next = temp>next;
    */
    delete temp;

    length--;
}

int main()
{
    // std::cout << "hi lmi world!" << "\n";

    DoublyLinkedList* dll = new DoublyLinkedList(1);
    // dll->append(3);
    // dll->append(5);
    // dll->delete_last();
    // dll->prepend(0);
    // dll->delete_first();
    // dll->delete_first();
    // dll->append(3);
    // dll->append(4);
    // dll->append(35);
    // dll->append(36);
    // dll->print_list();
    // std::cout << "Value index at 3: " << dll->get(3)->m_value << "\n";
    // dll->set(3, 99);
    // dll->print_list();
    // dll->insert(2,2222);
    // dll->print_list();
    // dll->delete_node(2);
    // dll->print_list();

    // dll->append(2);
    // dll->append(3);
    // dll->append(4);
    // dll->append(5);
    // dll->isPalindrome();
    // dll->print_list();
    // dll->reverse();
    // dll->print_list();

    // dll->append(5);
    // dll->append(8);
    // dll->append(3);
    // dll->append(6);
    // dll->append(66);
    // dll->append(62);
    // dll->append(2);
    // dll->print_list();
    // dll->partition_list(0);
    // dll->print_list();

    dll->append(2);
    dll->append(3);
    dll->append(4);
    dll->append(5);
    dll->print_list();
    // dll->reverse_between(1,3);
    dll->reverse_between(0,4);
    dll->print_list();

    return 0;
}

bool DoublyLinkedList::isPalindrome()
{
    if(length == 1) return true;
    if(length == 2) return head->m_value == tail->m_value;

    Node* forward = head;
    Node* backward = tail;

    while(forward->next != backward)
    {
        if(forward->m_value != backward->m_value)
        {
            return false;
        }

        if(forward->next == backward->prev)
        {
            break;
        }

        forward = forward->next;
        backward = backward->prev;
    }

    return true;
}

void DoublyLinkedList::reverse()
{
    if(length == 1 || length == 0) return;

    Node *temp = nullptr;
    Node* current = head;
    
    // Traverse the list and reverse the links
    while (current != nullptr) {
      
        // Swap the next and prev pointers
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        // Move to the next node in the original list 
      	// (which is now previous due to reversal)
        current = current->prev;
    }

    Node* t = tail;
    tail = head;
    head = t;
}

void DoublyLinkedList::partition_list(int x)
{
    if(length == 0 || length == 1) return;

    Node* smaller_list_head = new Node(-99);
    Node* greater_list_head = new Node(-98);

    Node* smaller_list_current = smaller_list_head;
    Node* greater_list_current = greater_list_head;

    Node* current = head;

    while(current != nullptr)
    {
        if(current->m_value < x)
        {
            smaller_list_current->next = current;
            current->prev = smaller_list_current;

            smaller_list_current = smaller_list_current->next;
        }
        else
        {
            greater_list_current->next = current;
            current->prev = greater_list_current;

            greater_list_current = greater_list_current->next;
        }

        current = current->next;
    }

    // std::cout << "smallers: " << smaller_list_head->m_value << " - " << smaller_list_head->next->m_value << " - " << smaller_list_head->next->next->m_value << "\n";
    // std::cout << "greaters: " << greater_list_head->m_value << " - " << greater_list_head->next->m_value << " - " << greater_list_head->next->next->m_value << "\n";

    // std::cout << "smaller current: " << smaller_list_current->m_value << "\n";
    // std::cout << "greater current: " << greater_list_current->m_value << "\n";
    

    if(greater_list_head == greater_list_current)
    {
        // no greater values found!
        head = smaller_list_head->next;
        head->prev = nullptr;
        tail = smaller_list_current;
        tail->next = nullptr;
    }
    else if(smaller_list_head == smaller_list_current)
    {
        head = greater_list_head->next;
        head->prev = nullptr;
    }
    else
    {
        head = smaller_list_head->next;
        head->prev = nullptr;
        smaller_list_current->next = greater_list_head->next;
        greater_list_head->next->prev = smaller_list_current;
        tail = greater_list_current;
        tail->next = nullptr;
    }

    return;
}

void DoublyLinkedList::reverse_between(int left, int right)
{
    if(length == 0 || length == 1) return;
    if(left > right) return;
    if(left < 0 || right > length ) return;

    Node* temp = head;
    Node* start_node = nullptr;
    Node* end_node = nullptr;

    for(int i = 0; i < length; i++)
    {
        if(i == left) start_node = temp;
        if(i == right) end_node = temp;
        
        temp = temp->next;
        
    }
    
    Node* before_start  =   start_node->prev;
    Node* after_end     =   end_node->next;
    
    Node* current = start_node->next;
    
    std::cout << "start_node: " << start_node->m_value << "\n";
    std::cout << "end_node: " << end_node->m_value << "\n";
    std::cout << "Current: " << current->m_value << "\n";
    
    for(int j = 0; j < right-left; j++)
    {
        // Swap the next and prev pointers
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        
        current = current->prev;
    }
    
    std::cout << "reversing done: " << "\n";
    
    
    // Reconnect reversed segment with the rest of the list
    if (before_start) {
        before_start->next = end_node;
        end_node->prev = before_start;
    } else {
        // Reversed from the head
        head = end_node;
        end_node->prev = nullptr;
    }

    if (after_end) {
        start_node->next = after_end;
        after_end->prev = start_node;
    } else {
        start_node->next = nullptr;
    }


    return;
}











