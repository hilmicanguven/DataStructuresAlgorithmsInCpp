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