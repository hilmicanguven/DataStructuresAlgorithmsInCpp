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
        Node* find_middle_node();
        bool has_list_loop();
        Node* findt_ith_node_from_end(int index);
        Node* remove_ith_node_from_end(int index);
        int binary_to_decimal();
        Node* partition_list(int value);
        Node* reverse_between_list(int left, int right);
        Node* swap_pairs();

        void bubbleSort();
        void selectionSort()
		{
		    if(length < 2) return;
		    
		    Node* current = head;
		    
		    while(current->next != nullptr)
		    {
		        Node* smallest = current;
		        
		        Node* innerCurrent = current->next;
		        
		        while(innerCurrent != nullptr)
		        {
		            if (innerCurrent->m_value < smallest->m_value) 
		            {
                        smallest = innerCurrent;
                    }
                    innerCurrent = innerCurrent->next;
		        }
		        
		         if (smallest != current) 
		         {
                    int temp = current->m_value;
                    current->m_value = smallest->m_value;
                    smallest->m_value = temp;
                }
		        
		        current = current->next;
		    }
		    
		}

    
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
    if(index < 0 || index >= length) { return;}

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
    
    for(int i = 0 ; i < length ; i++)
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

Node* LinkedList::find_middle_node()
{
    Node* fast = head;
    Node* slow = head;

    // while(fast->next != nullptr)
    // {
    //     if(fast->next->next != nullptr)
    //     {
    //         fast = fast->next->next;
            
    //         slow = slow->next;

    //     }
    //     else{
    //         fast=fast->next;
    //         slow=slow->next;
    //     }
        
    // }

    while (fast != NULL && fast->next != NULL) 
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

bool LinkedList::has_list_loop()
{
    if(head == NULL || head->next == NULL) return false;

    Node* slow = head;
    Node* fast = head->next;

    while (fast != NULL && fast->next != NULL) 
    {
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast)
        {
            return true;
        }
    }

    return false;
}

/*

Input: head = [1,2,3,4,5], n = 2

Output: [1,2,3,5]
*/
Node* LinkedList::findt_ith_node_from_end(int index)
{
    if(head == nullptr || tail == nullptr) return nullptr;

    Node* slow = head;
    Node* fast = head;

    for(int i = 0; i < index ; i++)
    {
        if (fast == nullptr)
        {
            return nullptr;
        }

        fast = fast->next;
    }

    while (fast != nullptr) 
    {
        slow = slow->next;
        fast = fast->next;

    }

    return slow;
}

Node* LinkedList::remove_ith_node_from_end(int index)
{
    Node* dummy = new Node(0);

    Node* slow = dummy;
    Node* fast = dummy;

    for(int i = 0; i < index+1 ; i++)
    {
        fast = fast->next;
    }

    while (fast != nullptr) 
    {
        slow = slow->next;
        fast = fast->next;
    }

    Node* temp = slow->next;
    slow->next = slow->next->next;
    delete temp;

    return dummy;
}

int LinkedList::binary_to_decimal()
{
    int sum = 0;
    Node* temp = head;

    while(temp != nullptr)
    {
        sum = sum << 1;
        sum |= temp->m_value;
        temp = temp->next;
    }

    return sum;
}

Node* LinkedList::partition_list(int val)
{
    Node* smaller_list_head = new Node(-1);
    Node* greater_list_head = new Node(-1);

    Node* small_current;
    Node* greater_current;

    Node* current = head;

    small_current = smaller_list_head;
    greater_current = greater_list_head;

    while(current)
    {
        if(current->m_value >= val)
        {
            greater_current->next = current;
            greater_current = greater_current->next;
        }
        else
        {
            small_current->next = current;
            small_current = small_current->next;
        }

        current = current->next;
    }

    greater_current->next = nullptr;
    small_current->next = greater_list_head->next;

    return smaller_list_head->next;
}

Node* LinkedList::reverse_between_list(int m, int n)
{
    if(!head || !head->next) return head;

        Node *dummy = new Node(-1);
        dummy->next = head;
        
        Node *prev = dummy, *cur = head;
        
        //move cur "m-1" steps forward, so it become the mth node
        int i = 1;
        for(i = 1; i < m; ++i)
        {
            prev = prev->next;
            cur = cur->next;
        }

        std::cout << "prev: " << prev->m_value << " and cur: " << cur->m_value << "\n";
        
        //rdummy: the previous node of the head of reversed list
        Node *rdummy = prev;
        //rtail: the tail of reversed list
        Node *rtail = cur;
        
        //do n-m+1 times, moving "cur" from mth node to (n+1)th node
        //m -> (m-1), (m+1) -> m, ..., n->(n-1)
        for(; i <= n; ++i)
        {
            Node* next = cur->next;
            std::cout << "next: " << next->m_value << "\n";
            std::cout << "cur->next: " << cur->next->m_value << "\n";
            cur->next = prev;
            prev = cur;
            cur = next;
            std::cout << "------------------------------- " << "\n";
        }
        
        //prev is the tail of reversed list
        rdummy->next = prev;
        //cur is the next node of the tail of reversed list
        rtail->next = cur;
        
        return dummy->next;

        /*
            // 1. Initial Check:
    // If the list is empty, there's nothing to reverse.
    // So, exit the function without doing anything.
    if (head == nullptr) return;
 
    // 2. Dummy Node Creation:
    // We initiate a new 'dummy' node with value 0.
    // This is a trick to simplify the edge cases.
    Node* dummy = new Node(0);
 
    // Connect our actual list right after the dummy node.
    // So, the dummy node temporarily stands before the head.
    dummy->next = head;
 
    // 3. Positioning 'prev':
    // Start with 'prev' pointing to the dummy node.
    Node* prev = dummy;
 
    // Move 'prev' up to the node just before the starting
    // point of the section we want to reverse.
    for (int i = 0; i < m; i++) {
        prev = prev->next;
    }
 
    // 4. Setting up 'current':
    // 'current' is set right after 'prev'.
    // It marks the start of the section to be reversed.
    Node* current = prev->next;
 
    // 5. Main Reversal Logic:
    // We now enter our core reversal loop.
    for (int i = 0; i < n - m; i++) {
        // 'temp' points to the node that's next in line
        // for our reversal process.
        Node* temp = current->next;
 
        // Detach 'temp' from the current sequence by
        // making 'current' skip over 'temp'.
        current->next = temp->next;
 
        // To move 'temp' to the start of our reversed section,
        // we first let 'temp' point to whatever node 'prev' is pointing to.
        temp->next = prev->next;
 
        // Finally, we adjust 'prev' to point to 'temp', thereby
        // moving 'temp' to the front of the reversed section.
        prev->next = temp;
    }
 
    // 6. Updating Head:
    // If our reversed section included the original head of the list,
    // our list's head would have changed. 
    // So, we need to update the head of our list.
    head = dummy->next;
 
    // 7. Cleanup:
    // The dummy node has served its purpose.
    // We free up its memory to avoid memory leaks.
    delete dummy;
        
        */

}

Node* swap(Node* node){
    // length 0 or 1
    if(!node || !node->next)
        return node;
    
    Node* next = node->next;
    node->next = next->next;
    next->next = node;
    
    return next;
}

Node* LinkedList::swap_pairs()
{
    Node* dummy = new Node(0);
        
    dummy->next = head;
    
    Node* cur = dummy;
    
    while(cur)
    {
        Node* next = swap(cur->next);
        cur->next = next;
        
        cur = cur->next;
        if(cur)cur = cur->next;
    }
    
    return dummy->next;
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

    // LinkedList* ll = new LinkedList(67);
    // ll->append(41);
    // ll->append(6);
    // ll->append(75);
    // ll->prepend(16);
    // ll->print_list();
    // ll->delete_last();
    // ll->delete_first();
    // ll->delete_first();
    // ll->delete_first();
    // ll->delete_first();
    // ll->print_list();
    // ll->append(41);
    // ll->append(6);
    // ll->append(75);
    // ll->print_list();
    // std::cout << "Value at index 2 is: " << ll->get(2)->m_value << "\n";
    // auto result = ll->set(2, 59);
    // ll->print_list();
    // std::cout << "New Element at index 2 is: " << ll->get(2)->m_value << "\n";
    // ll->insert(0,0);
    // ll->print_list();
    // ll->insert(2,82);
    // ll->print_list();
    // ll->delete_node(0);
    // ll->print_list();
    // ll->reverse();
    // ll->print_list();
    // std::cout << "Middle Node: " << ll->find_middle_node()->m_value << "\n";
    // ll->append(99);
    // ll->append(99);
    // ll->print_list();
    // std::cout << "Middle Node: " << ll->find_middle_node()->m_value << "\n";
    // std::cout << "i th (3) Node From End: " << ll->findt_ith_node_from_end(3)->m_value << "\n";

    // auto new_list = ll->remove_ith_node_from_end(3);
    // std::cout << "List: " << new_list->m_value << new_list->next->m_value << new_list->next->next->m_value << new_list->next->next->next->m_value << "\n"; 

    // LinkedList* ll = new LinkedList(1);
    // ll->append(0);
    // ll->append(0);
    // ll->append(0);

    // std::cout << "Decimal correpsond of binary linked list: " << ll->binary_to_decimal() << "\n";

    // LinkedList* ll = new LinkedList(1);
    // ll->append(3);
    // ll->append(9);
    // ll->append(5);
    // ll->append(4);
    // ll->append(7);
    // ll->append(8);
    // ll->append(9);

    // auto new_list = ll->partition_list(5);
    // std::cout << "List: " << "\n"; 
    
    // while(new_list)
    // {
    //     std::cout << new_list->m_value << "\t"; 
    //     new_list = new_list->next;
    // }
    
    LinkedList* ll = new LinkedList(1);
    ll->append(2);
    ll->append(3);
    ll->append(4);
    ll->append(5);
    ll->print_list();
    std::cout << std::endl;


    auto new_list = ll->reverse_between_list(2,4);
    std::cout << "List: " << "\n"; 
    
    while(new_list)
    {
        std::cout << new_list->m_value << "\t"; 
        new_list = new_list->next;
    }
    std::cout << std::endl;
    
    ll->print_list();
    ll->swap_pairs();
    ll->print_list();
    return 0;
}

void LinkedList::bubbleSort() {
    // If the list has fewer than 2 elements, it's already sorted.
    // So, we exit the function early.
    if (length < 2) return;
 
    // Initialize a pointer called "sortedUntil".
    // This pointer marks the point until which the list is sorted.
    Node* sortedUntil = nullptr;
 
    // Continue sorting until "sortedUntil" reaches the second node in the list.
    while (sortedUntil != head->next) {
        // Initialize "current" at the head of the list. 
        // "current" will be used to traverse the list.
        Node* current = head;
 
        // Traverse the list until "current->next" becomes "sortedUntil".
        // This means we only check the unsorted part of the list.
        while (current->next != sortedUntil) {
            // "nextNode" points to the node immediately after "current".
            Node* nextNode = current->next;
 
            // Compare the value of "current" and "nextNode".
            // If they're out of order, swap them.
            if (current->m_value > nextNode->m_value) {
                int temp = current->m_value;
                current->m_value = nextNode->m_value;
                nextNode->m_value = temp;
            }
            // Move "current" to the next node.
            current = current->next;
        }
        // Update "sortedUntil" to point to the last node we've just checked.
        // This way, "sortedUntil" moves closer to the head of the list.
        sortedUntil = current;
    }
}