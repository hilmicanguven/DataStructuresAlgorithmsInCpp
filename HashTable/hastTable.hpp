/*

Hash Table

Belirli bir "key" e göre bir unique "adress" üretir.
yalnızca tek yönlü çalışır, address'e göre key'e ulaşılamaz.
farklı "key" lere aynı address'in üretilmesi "collision" durumudur.
bu durumun bir şekilde yönetilmesi gerekir. genellikle şu yöntemleri görürüz
                                            -----------------
|-------------                              |    item_1      | address_1000
|   keys     |                              -----------------
|    "item-1"|                              |                | address_1001
|    ..      |  ->    HASH FUNCTION    ->   -----------------
|    ..      |                              |  item_2        | address_1002
|    ..      |                              |  item_3        | 
|    "item-n"|                              -----------------
|-------------                              |                | address_1003

- seperate chaining
        farklı key'ler aynı adreste depolanır
        get metodu ile adres içinde depolanan key'ler aranır

    - linear probing
        aynı adreste farklı key'ler depolanmaz, eğer bir adres doluyken
        farklı bir key yine aynı adrese koyulmak istenirse
        bu adresten sonraki ilk müsait adreste depolanır.

hash function, key'e göre nasıl adres hesaplayacağı implementasyon spesifiktir.
genellikle problemimize uygun adresleri en random şekilde dağıtabilen
ve en az sayıdaki collision sahip olan bir fonksiyon isteriz.

Big(O) of Hash Function
    Big(O) hesabında kendi örneğimizde key'lerin string uzunluğuna göre bir hesap yapmış olabiliriz
    Ancak burada "n" olarak değerlendirmemiz gereken şey "key" sayısıdır.
    Milyon tane key olduğunda 1 tane key olduğunda da aslında bizim fonksiyonumuz aynı işlemi yapacaktır.
    
    - Get ve Set için O(1) gibi düşünebiliriz
    ANCAK worst case scenario'da tüm key'ler aynı adrese eşit olursa
    bu sefer durum yine Linked List'den farklı olmayacaktır.
    Ancak matematik olarak bu durum çok mümkün olmayacağı için O(1) gibi düşünmekte sakınca yoktur.

*/

#include <iostream>
#include <vector>

using namespace std;

class Node
{
    public:
        string key;
        int value;
        /** @brief in case of collision in hast table */
        Node* next;

        Node(string k, int val)
        {
            key = k;
            value = val;
            next = nullptr;
        }
};

class HashTable
{
    private:
        static const int SIZE = 7;
        /** @brief Adresses(Values) map generated according to Keys */
        Node* data_map[SIZE];
    public:
        ~HashTable() {
            for(int i = 0; i < SIZE; i++) 
            {
                Node* head = data_map[i];
                Node* temp = head;
                while (head) 
                {
                    head = head->next;
                    delete temp;
                    temp = head;
                }
            }
        }
        
        void printTable() {
            for(int i = 0; i < SIZE; i++)
            {
                cout << i << ":" << endl;
                if(data_map[i]) 
                {
                    Node* temp = data_map[i];
                    
                    while (temp) 
                    {
                        cout << "   {" << temp->key << ", " << temp->value << "}" << endl;
                        temp = temp->next;
                    }
                }
            }
        }

        int hash(string key)
        {
            int hash = 0;

            // Create your own Hash Table Algorithm

            for(int i = 0; i < key.length(); i++)
            {
                int ascii = int(key[i]) + 13;
                // modulo is good for fitting the table 
                hash = (hash + ascii * 16) % SIZE; 
            }

            return hash;
        }

        void set(string key, int value)
        {
            int index = hash(key);
            Node * new_node = new Node(key, value);

            if(data_map[index] == nullptr)
            {
                data_map[index] = new_node;
            }
            else
            {
                Node* temp = data_map[index];
                while(temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->next = new_node;
            }
        }

        int get(string key)
        {
            int index = hash(key);

            Node* temp = data_map[index];

            while(temp != nullptr)
            {
                if (temp->key == key)
                {
                    return temp->value;
                }else
                {
                    temp = temp->next;
                }
            }

            return 0;
        }

        vector<string> keys()
        {
            vector<string> all_keys;
            for(int i = 0; i < SIZE ; i++)
            {
                Node* temp = data_map[i];

                while(temp != nullptr)
                {
                    all_keys.push_back(temp->key);
                    temp = temp->next;
                }
            }

            return all_keys;
        }
    };

    // interview quesiton

/*
IMPORTANT

iki vector arasında ortak bir sayı var mı yok mu bulmak için
akla belki de ilk gelen ve O(n^2) karmaşıklığa sahip yöntemdir.
iç içe iki foor loop ile iki vectorun elemanlarını sırasıyla kıyaslar
ve aynı değeri bulursak true döneriz. Ancak O(n^2) karmaşıklığa sahip olacak
ve kesinlikle performans açısından bizi mutlu etmeyecektir..

Bunun yerine hash table, yani unordered map, kullanabiliriz.
yine iki for loop kullanırız ancak iç içe değildir.
bu durumda karmaşıklık O(n+n) = O(2n) = O(n) olur.
ilk vector'deki itemleri hash tablosuna ekleriz.
ikinci vector'ün elemanlarını ise hash tablosunda olup olmadığına O(1) ile bakarız.

kesinlikle çok daha optimize bir yöntem olacaktır.
*/
#include <unordered_map>

bool itemInCommon(vector<int> vect1, vector<int> vect2) 
{
    unordered_map<int, bool> myMap;

    for (auto i : vect1) {
        myMap.insert({i, true});
    }

    for (auto j : vect2) {
        if (myMap[j]) return true;
    }
    
    return false;
}

vector<int> findDuplicates(const vector<int>& nums) {

	unordered_map<int, int> map = {};
	
    vector<int> duplicates = {};
	for(auto num: nums)
	{
        map[num]++;
	}

    for(const auto& j : map)
    {
        if(j.second > 1)
        {
            duplicates.push_back(j.first);
        }
    }

    return duplicates;
}

char firstNonRepeatingChar(const string& input_string) {
	//   +======================================================+
	//   |                 WRITE YOUR CODE HERE                 |
	//   | Description:                                         |
	//   | - This function finds the first non-repeating char   |
	//   |   in a given string.                                 |
	//   | - It uses an unordered_map to count char occurrences |
	//   | - Loops through the string to check counts.          |
	//   |                                                      |
	//   | Return type: char                                    |
	//   |                                                      |
	//   | Tips:                                                |
	//   | - 'charCounts' keeps track of each char's count.     |
	//   | - Loops twice: once to count, once to find answer.   |
	//   | - Returns '\0' if no non-repeating char is found.    |
	//   | - Check output from Test.cpp in "User logs".         |
	//   +======================================================+
    unordered_map<char, int> counts;

    for(auto c : input_string)
    {
        counts[c]++;
    }

    for(auto c : input_string)
    {
        if(counts[c] == 1) return c;
    }

    return '\0';
}

#include <string>
#include <algorithm>

/**
 * @brief iki kelime aynı harflerin farklı dizilişinden oluşan kelimeler anagram olur.
 * bu fonksiyonda bu kelimeleri birbirleri ile gruplamamız gerekiyor
 * 
 * algoritma: map'e stringlere eklemeden önce STL'deki sort fonksiyonu
 * yardımı ile anagram olanları sort yaparak bulabiliriz.
 * sort etmeden orjinal string'i yedekler, sort olmuş hali
 * map içerisinde varsa value=vector_of_strings e ekleriz. yani gruplamış oluruz..
 * 
 * hello <-> hlleo   
 */
vector<vector<string>> groupAnagrams(const vector<string>& strings) {
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function groups anagrams from a given vector |
	//   |   of strings.                                       |
	//   | - It uses an unordered_map for organization.        |
	//   | - It sorts each string to form a canonical version. |
	//   | - Groups strings with the same canonical form.      |
	//   |                                                     |
	//   | Return type: vector<vector<string>>                 |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - 'anagramGroups' maps canonical strings to groups. |
	//   | - 'canonical' is a sorted version of each string.   |
	//   | - 'result' holds the final groups of anagrams.      |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+

	unordered_map<string, vector<string>> anagramGroups;

    for(auto str : strings)
    {
        auto str_sorted = str;
        std::sort(str_sorted.begin(), str_sorted.end()); // Sorts in ascending order
        anagramGroups[str_sorted].push_back(str);
    }
    
    vector<vector<string>> result;
    
    for(auto key: anagramGroups)
    {
        result.push_back(key.second);
    }

    return result;
}

/**
 * @brief bir vector da iki sayısının toplamının istediğimiz "target"
 * değerini veren ikili varsa onların index'lerini döndürmemiz gerekiyor.
 * bunun için,
 * bir map oluşturarak sayı ve bulunduğu indexi kaydederiz.
 *  her iterasyonda, o iterasyondaki sayı ile hangi sayıyı "complement" toplarsak target'a eşit olur dediğimiz sayı varsa map içerisinde onu ararız
 * eğer varsa doğrudan index'lerini döndürüz.
 * eğer yoksa Map içerisine ekleriz.
 */
vector<int> twoSum(const vector<int>& nums, int target) {
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function finds two numbers in 'nums' that    |
	//   |   sum up to the given 'target'.                     |
	//   | - It uses an unordered_map for quick look-up.       |
	//   | - It returns the indices of the numbers that add    |
	//   |   up to the target.                                 |
	//   |                                                     |
	//   | Return type: vector<int>                            |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - 'numMap' stores numbers and their indices.        |
	//   | - 'complement' is the value needed to reach target. |
	//   | - Use 'find' method for quick look-up in map.       |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+

    unordered_map<int, int> numMap;
    int index = 0;
    int complement;
    
    for(auto num : nums)
    {
        complement = target - nums[index];
        if(numMap.find(complement) != nullptr)
        {
            return {numMap[complement], index};
        }
        else
        {
            numMap.insert({num, index});
        }

        index++;
    }

    return {};
}

vector<int> subarraySum(const vector<int>& nums, int target) {
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function finds a subarray in 'nums' that     |
	//   |   sums up to the given 'target'.                    |
	//   | - It uses an unordered_map for quick look-up.       |
	//   | - It returns the indices of the start and end       |
	//   |   elements of the subarray.                         |
	//   |                                                     |
	//   | Return type: vector<int>                            |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - 'sumIndex' stores cumulative sums and their       |
	//   |   indices.                                          |
	//   | - 'currentSum' keeps track of the sum up to index i.|
	//   | - Use 'find' method for quick look-up in map.       |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+
    /*
    Key: cumulative sum up to a certain index.
    Value: the index where that sum occurred.
*/
    unordered_map<int, int> sumMap;

    sumMap[0] = -1;
    int current_sum = 0;

    for(int i = 0 ; i< nums.size() ; i++)
    {
        current_sum += nums[i];
        if(sumMap.find(current_sum - target) != sumMap.end())
        {
            return {sumMap[current_sum - target] + 1, i};
        }

        sumMap[current_sum] = i;
    }

    return {};

}

#include <unordered_set>

vector<int> removeDuplicates(const vector<int>& myList) {
    //   +=====================================================+
    //   |                 WRITE YOUR CODE HERE                |
    //   | Description:                                        |
    //   | - This function removes duplicate integers from a   |
    //   |   given vector 'myList'.                            |
    //   | - It uses an unordered_set for quick look-up and    |
    //   |   elimination of duplicates.                        |
    //   | - Returns a vector of unique integers.              |
    //   |                                                     |
    //   | Return type: vector<int>                            |
    //   |                                                     |
    //   | Tips:                                               |
    //   | - 'uniqueSet' stores unique numbers from 'myList'.  |
    //   | - Use 'begin()' and 'end()' to copy elements back   |
    //   |   to a vector.                                      |
    //   | - Check output from Test.cpp in "User logs".        |
    //   +=====================================================+
    unordered_set<int> uniqueSet;
    
    for(auto i : myList)
    {
        uniqueSet.insert(i);
    }

    vector<int> res;
    
    for(auto i : uniqueSet)
    {
        res.push_back(i);
    }
    
    return res;
}

bool hasUniqueChars(const string& str) {
    //   +=====================================================+
    //   |                 WRITE YOUR CODE HERE                |
    //   | Description:                                        |
    //   | - This function checks if a string 'str' has unique |
    //   |   characters.                                       |
    //   | - It uses an unordered_set for quick look-up.       |
    //   | - It returns a boolean value.                       |
    //   |                                                     |
    //   | Return type: bool                                   |
    //   |                                                     |
    //   | Tips:                                               |
    //   | - 'charSet' stores characters we've seen.           |
    //   | - Loop through 'str' to populate 'charSet'.         |
    //   | - Use 'find' method for quick look-up in set.       |
    //   | - If a duplicate is found, return false.            |
    //   | - Check output from Test.cpp in "User logs".        |
    //   +=====================================================+
    
    unordered_set<char> uniqueChars;
    
    for(auto c : str)
    {
        // Checking if an element is in a set
        if (uniqueChars.find(c) != uniqueChars.end()) 
        {
            return false;
        }
        
        uniqueChars.insert(c);
    }
    
    return true;    
    
}

vector<vector<int>> findPairs(const vector<int>& arr1, const vector<int>& arr2, int target) {
    //   +=========================================================+
    //   |                 WRITE YOUR CODE HERE                    |
    //   | Description:                                            |
    //   | - This function finds all pairs of integers from        |
    //   |   'arr1' and 'arr2' that sum up to 'target'.            |
    //   | - It uses an unordered_set for quick look-up.           |
    //   | - It returns a 2D vector containing the pairs.          |
    //   |                                                         |
    //   | Return type: vector<vector<int>>                        |
    //   |                                                         |
    //   | Tips:                                                   |
    //   | - 'mySet' stores numbers from 'arr1'.                   |
    //   | - 'pairs' will store the pairs that meet the target.    |
    //   | - Loop through 'arr1' to populate 'mySet'.              |
    //   | - Loop through 'arr2' to find pairs.                    |
    //   | - Use 'find' method for quick look-up in set.           |
    //   | - Check output from Test.cpp in "User logs".            |
    //   +=========================================================+
    
    unordered_set<int> mySet;
    
    for(auto i: arr1)
    {
        mySet.insert(i);
    }
    
    int complement;
    vector<vector<int>> res;
    for(auto i: arr2)
    {
        complement = target - i;
        if(mySet.find(complement) != mySet.end())
        {
            res.push_back({complement, i});
        }
    }
    
    return res;
    
}

int longestConsecutiveSequence(const vector<int>& nums) {
    //   +=====================================================+
    //   |                 WRITE YOUR CODE HERE                |
    //   | Description:                                        |
    //   | - This function finds the longest consecutive       |
    //   |   sequence of integers in a given array.            |
    //   | - It uses an unordered_set for quick look-up.       |
    //   | - Loop through each unique number in the set.       |
    //   | - For each number, check its sequence length.       |
    //   | - Update 'longestStreak' if a longer sequence is    |
    //   |   found.                                            |
    //   |                                                     |
    //   | Return type: int                                    |
    //   |                                                     |
    //   | Tips:                                               |
    //   | - 'numSet' stores unique numbers from 'nums'.       |
    //   | - 'longestStreak' keeps track of the longest        |
    //   |   sequence found so far.                            |
    //   | - Use 'find' method for quick look-up in set.       |
    //   | - Check output from Test.cpp in "User logs".        |
    //   +=====================================================+
    
    // Create a set 'numSet' to store unique numbers from 'nums'.
    unordered_set<int> numSet(nums.begin(), nums.end());
  
    int longestStreak = 0;
    
    for(auto num: numSet)
    {
        if(numSet.find(num - 1) == numSet.end())
        {
            int current_num = num;
            int current_streak = 1;
            
            while (numSet.find(current_num + 1) != numSet.end()) 
            {
                current_num++;
                current_streak++;
            }
            
            longestStreak = max(longestStreak, current_streak);
            
        }
    }
    
    return longestStreak;
}

void hash_main()
{
    HashTable* myHashTable = new HashTable();

    myHashTable->set("book", 100);
    myHashTable->set("pencil", 400);
    myHashTable->set("bag", 300);
    myHashTable->set("ruler", 200);
    cout << "Hash Table: \n";
    myHashTable->printTable();

    cout << "value of book: " << myHashTable->get("book") << "\n";
    cout << "value of book: " << myHashTable->get("bag") << "\n";
    cout << "value of book: " << myHashTable->get("potato") << "\n";

    auto keys = myHashTable->keys();

    for(auto key : keys)
        cout << key << " - ";


    vector<int> vec = {1,2,3,4,5,4,5,8,99};
    auto duplicates = findDuplicates(vec);
    std::cout << "duplicates: " << duplicates[0];
    std::cout << "duplicates: " << duplicates[1];

    return;
}


int example_set() {
    // Create a set
    unordered_set<int> mySet = {1, 2, 3, 4, 5};
 
    // Add elements to the set
    mySet.insert(6);
    mySet.insert(7);
 
    // Remove an element from the set
    mySet.erase(2);
 
    // Checking if an element is in a set
    if (mySet.find(10) != mySet.end()) {
        cout << "Found 10 in mySet" << endl;
    }
 
    // Check size of the set
    cout << "Size of mySet: " << mySet.size() << endl;
 
    // Check if a set is empty
    if (mySet.empty()) {
        cout << "Set is empty!" << endl;
    } else {
        cout << "Set is not empty!" << endl;
    }
 
    // Clearing all elements from a set
    mySet.clear();
    cout << "After clearing, size: " << mySet.size() << endl;

    return 0;
}