/*

Tree (Ağaç)

Tree içerisindeki data'ları da yine Node ile benzer bir yapı ile kuracağız.
Ancak LinkedList de next pointer varken burada,
Binary Tree düşünürsek, left ve right pointer olarak düşüneceğiz.
Elbette binary olmak zorunda değil ancak şu an yalnızca 2 adet child olabileceği senaryoyu değerlendireceğiz.

            + (Parent)
        ++ (Child)(Also Parent)     ++  (Child)(Also Parent)     // ik child, siblings
    ++      ++                 ++      ++

// Leaf Node: hiç child node'u olmatan Node bu şekilde isimlendirilir.


- Full Tree     : Her bir node 2 veya 0 sayıda child-node a sahipse full node deriz.
- Perfect Tree  : Her bir node hem 2 sayıda node'a hem de Root Node a göre simetrik ise perfect tree olarak adlandırırız.
- Complete Tree : Soldan sağa doğru gittiğimizde tüm node'lar dolu ise buna complete tree denir.
                    (Soldan sağa doğru gitmek derken şunu kast ederiz:
                        en alt seviyede en sağdaki node'dan başlayarak aynı seviyedik en sola,
                        sonrasında bir üst seviye en sağa
                        sonrasında tekrar aynı seviyedeki en sola
                        sonra tekrar bir seviye ve aynı işlem tekrarlanır.
                        Eğer boş node yok ise buna complete tree diyebiliriz.)


Binary Search Tree: binary tree'den farklı olarak tree yapısının belirli bir paternde oluşmuş olması gerekir.
    Eğer child parent node'dan büyük ise sağ Node'a yer alır.
    47 - 76 - 52 -21 - 82 - 18 - 27 sırasıyla eklenirse BST bu şekilde yerleşir.
    47'den büyük sayılar ağacın sağında, diğerleri solunda yer alır.

        47
    21        76
18     27       52  82


Complexity of BST : Bir node'a erişmek için
                    2^n-1 where ne is the level/deep of the tree
                    which is θ(log n)
                    "Divide and Conquer" olarak isimlendirebiliriz.
                    bir sayıyı aradığımızda, Parent'ten büyük veya küçük olma durumuna göre
                    ağacın yalnızca sağ yarısına bakarız.
                    ***Bunu average olarak isimlendiririz***
                    Worst case scenario'da ise aslında sürekli sağa gittiğimizi düşünelim,
                    aslında Linked Listten bir farkı olmamış olur ve O(n) diyebiliriz.


Recursive BST
    İlk yazdığımız BST fonksiyonlarında iterative yöntem ile implemente ettik.
    yani "loop" kullanarak implemente etmiştik.
    burada ise recursive function call ile yapacağız.

    rContains:
        contains function'ı implemente ederek başlayacağız.
        recursive olarak implemente edeceğimiz fonksiyonda current_node değişkenine sahip olmamız gerekiyor
        çünkü bu node'a göre nerede recursive çağrıyı sonlandıracağımıza karar vereceğiz.
        ancak kullanıcıya bunu belirtmeden yapmak için function overloading yaparak yalnızca value alacak şekilde bir fonk oluşturacağız.
        contains fonksiyonunun algoritması oldukça basit,
            current node null değilse, mevcut node'a eşitse true değilse false döneriz.

    rInsert:
        insert'ü de yine recursive olarak yazabiliriz.
        insert etmek istediğimiz pozisyonu bulmak gerekir.
        bunun için aynı fonksiyonu value comparison yaparak left veya right child ile tekrar çağırırız

    rDelete:
        öncelikle tüm ağacı traverse etmeliyiz.
        sonrasında aradığımız node'u bulunca sileriz.
        leaf node silmek en basit senaryodur.
        ancak leaf olmayan(child'i bulunan) node'u silince ağacı tekrar düzenlemek gerekir
        sileceğimiz nodu'un altındaki sub-tree'deki en küçük değeri bulup sildiğimiz node'un değerine bu node'u atar ve bu node'u(lowest in the subtree) sileriz.


*/

#include <iostream>

using namespace std;

class Node
{
    public:
        Node(int val) : value(val) 
        {
            right = nullptr;
            left = nullptr; 
        };
        
        Node* right;
        Node* left; 
        int value;
};

class BinarySearchTree
{
    public:
        BinarySearchTree(int value)
        {
            Node* new_node = new Node(value);
            root = new_node;
        }

        BinarySearchTree()
        {
            root = nullptr;
        }
    
        Node* root;

        bool insert(int val)
        {
            Node* new_node = new Node(val);
            
            if(root == nullptr)
            {
                root = new_node;
                return true;
            }

            Node* temp = root;
            
            while(true)
            {
                // not allowed for duplicate values
                if(new_node->value == temp->value)
                {
                    return false;
                }

                if(new_node->value < temp->value)
                {
                    // saller value, forward to left branch
                    if(temp->left == nullptr)
                    {
                        temp->left = new_node;
                        return true;

                    }

                    temp = temp->left;
                }
                else
                {
                    // greater, move to right child
                    
                    if(temp->right == nullptr)
                    {
                        temp->right = new_node;
                        return true;

                    }

                    temp = temp->right;
                }
                
            }

        }

        bool contain(int val)
        {
            Node* temp = root;
            
            while(temp != nullptr)
            {
                if(val < temp->value)
                {
                    temp = temp->left;
                }
                else if(val > temp->value)
                {
                    temp = temp->right;
                }
                else
                {
                    // values found
                    return true;
                }
            }

            return false;
        }

        bool rContains(int value)
        {
            return rContains(root, value);
        }
        
        /** @brief recursive function to check occurence of a value in the BST */
        bool rContains(Node* current_node, int val)
        {
            if(current_node == nullptr ) return false;

            if(current_node->value == val) return true;
            
            if(current_node->value > val)
            {
                return rContains(current_node->left, val);
            }
            else
            {
                return rContains(current_node->right, val);
            }
        }

        /** @brief recursive insert function */
        Node* rInsert(Node* cn, int val)
        {
            if(nullptr == cn) return new Node(val);
            
            if(cn->value > val)
            {
                cn->left = rInsert(cn->left, val);
            }
            else if(cn->value < val)
            {
                cn->right = rInsert(cn->right, val);
            }

            // no duplicates allowed, return existing one to its parent.
            return cn;
        }

        void rInsert(int val)
        {
            if(root == nullptr) root = new Node(val);

            rInsert(root, val);
        }

        Node* deleteNode(Node* current_node, int value )
        {
            if( current_node == nullptr) return nullptr;

            if(value < current_node->value)
            {
                current_node->left = deleteNode(current_node->left, value);
            }
            else if(value > current_node->value)
            {
                current_node->right = deleteNode(current_node->right, value);
            }
            else
            {
                // found the node that will be deleted
                // must handle 4 different cases... 1-leaf node 2-only have right child 3- only have left child
                // and relatively harder, 4- it has both left and right child

                if(current_node->left == nullptr && current_node->right == nullptr )
                {
                    delete(current_node);
                    return nullptr; // update parent node's child
                }
                else if(current_node->left == nullptr)
                {
                    Node* temp = current_node->right;
                    delete(current_node);
                    return temp;
                }
                else if(current_node->right == nullptr)
                {
                    // open on the right, has child on left
                    Node* temp = current_node->left;
                    delete(current_node);
                    return temp;
                }
                else
                {
                    // has node on eacn side
                    int subTreeMin = minValue(current_node->right);
                    current_node->value = subTreeMin;
                    current_node->right = deleteNode(current_node->right, subTreeMin);
                }

            }

            return current_node;
        }

        void deleteNode(int value)
        {
            root = deleteNode(root, value);
        }

        /** @brief the function find minumum value under the @ref current_node */
        int minValue(Node* current_node)
        {
            while(current_node != nullptr)
            {
                current_node = current_node->left;
            }

            return current_node->value;
        }
    };

void tree_main()
{

    BinarySearchTree* bst = new BinarySearchTree();
    bst->insert(47);
    bst->insert(21);
    bst->insert(76);
    bst->insert(52);
    bst->insert(82);
    bst->insert(27);

    cout << "Val: " << bst->root->left->right->value << "\n";
    cout << boolalpha << "is contains: " << bst->contain(76) << "\n";
    cout << "is contains: " << bst->contain(9999) << "\n";
    return;
}