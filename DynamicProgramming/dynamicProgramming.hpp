/*

Dynamic Programming

Overlapping Subproblems
    
    Büyük bir problemi daha küçük sub-problemlere bölebiliriz.
    böldüğümüz bu sub-problemler eğer ki aynı problemler ise -> "repeating subproblems" olarak adlandırabiliriz.
    
    1.numaralı sub-problem (çok büyük bir işlem gücü gerektiren bir problem olsun) birden fazla kez yapılması gerekirse
    ilk yapılan işlemin sonucunu bir yerde depolamak ve sonra ihtiyaç olduğunda bunu kullanmak
    bize inanılmaz bir verimlilik katar. bu sonucu bir array'de belirli index'te tuttuğummuzu varsayalım.
    artık buna erişmek O(1) olacaktır. how cool is that, right?

    Memoization : sub-problemlerin sonuçlarının bir yerde depolanmasına memoization adı verilir.

    karıştırmamak adına şuna açıklık getirelim
        daha önce merge sort açıklarken büyük problemi sub-problemlere bölmüştük
        büyük bir array'i daha küçük sub-array'lere bölmüştük ve sort edip tekrar bir araya getirmiştik
        orada da problemi küçük alt problemelre bölmüştük ancak
        HİÇBİR İŞLEM BİRBİRİNİ TEKRARLAMIYORDU VE SONUÇLARI TEKRAR KULLANILABİLİR DEĞİLDİ yani overlapping subproblems değildir
        yani merge sort, dynamic programming örneği değildir.


Optimized Substructure

    bir problemin optimum çözümünü, alt-problemlerin optimal çözümlerini kullanarak elde edebiliyorsak 
    "optimal substructure" propert'e sahiptir diyebiliriz.

    bunu bir graph ile açıklayalım  -> 
        A --- 10 --- B
        |            |
        |            |
        30           15
        |            |
        |            |
        C --- 20 --- D

        A'dan D'ye gitme problemini çözmek için A-B ve B-D arası ve A-C ve C-D arası weight'leri ayrı ayrı hesaplayarak buluruz


Fibonacci Sequence çözümü için Dynamic Programming

    1 1 2 3 5 8 13      

    bu işlem için 99% recursion function call şeklinde yapılır. ancak şunu fark edeceğiz ki fib(1) birden fazla hesaplanacak
              fib(3)
            /       \
        fib(2)     fib(1)
        /   \
    fib(1) fib(0)   
  

    burada fib(1) için overlapping sub-problems diyebiliriz. bir adım ileriye giedrsek
                    fib(4)
                    / \
              fib(3)  ***fib(2)***
            /       \
        ****fib(2)****     fib(1)
        /   \
    fib(1) fib(0) 
    
    daha da ileriye gidersek piramit şeklide tamamen aynı işlemlerin yapıldığını göreceğiz.

    big(O) complexity O(n^2) den O(n) e düşürebiliriz Memoization kullanarak (O(2n - 1) =~ O(n))

    Memoization için vector kullanabileceğimiz gibi, array veya unordered_map de kullanabilirdik.
    vector içindeki geçersiz(henüz çözümü hesaplanmamış sub-problemler) problemlere geçersiz, -1 gibi, değer veririz

Comparison with Other Approaches
    Approach	    Time Complexity	        Space Complexity	    Notes
Naive Recursion	        O(2^n)	                O(n) (call stack)	Very slow for large n
Memoization     	    O(n)	                O(n)	            Fast, recursive style (top-down)
Bottom-Up DP	        O(n)	                O(n)	            Iterative, safe
Space-Optimized	        O(n)	                O(1)	            Fastest, minimal memory
*/

#include <vector>

/** @brief legacy fibonacci code */
int legacy_fib(int n)
{
    if(n == 0 | n == 1) return n;

    return legacy_fib(n-1) + legacy_fib(n-2);
}

std::vector<int> memo(100, -1);

/** @brief Fibonacci with Memoization (Dynamic Programming) */
int fib_memoization(int n)
{
    if(memo[n] != -1)
    {
        // the value n is memoizated
        return memo[n];
    }

    if(n == 0 | n == 1) 
    {
        return n;
    }

    memo[n] = fib_memoization(n-1) + fib_memoization(n-2);

    return memo[n];
}

/** @brief this uses again memoization, but approach is bottop to top.
 * previous function, approach is top to down
 */
int fib_bottom_to_top(int n)
{
    if (n <= 1) return n;

    std::vector<int> fibList(n+1);

    fibList[0] = 0;
    fibList[1] = 1;

    for(int i = 2; i <=n; ++i)
    {
        fibList[i] = fibList[i-1] + fibList[i-2];
    }

    return fibList[n];
}

int fibonacciOptimized(int n) {
    if (n <= 1) return n;

    int prev = 0, curr = 1;
    for (int i = 2; i <= n; ++i) {
        int next = prev + curr;
        prev = curr;
        curr = next;
    }

    return curr;
}