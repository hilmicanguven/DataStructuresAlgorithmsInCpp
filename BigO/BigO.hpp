/*

Big O Notation
--------------

Yazdığımız kodların yalnızca çalışması yeterli değildir. Aynı zamanda verimli olmasını ve en optimumunu bulmaya çalışırız.
En iyi kodu tanımlayacak "en" i bulmak biraz zor olabilir. 
En iyiyi belirleyen kriterler vardır. Bir kodu diğer koddan daha iyi yapan bazı perspektifler bulunur.

- Time Complexity

    İki kodu çalıştırarak aynı sonucu elde etmek için gerekli süreye göre kodları sıralamaya yarar.
    Basit bir şekilde kodun çalışma süresini ölçerek kıyas yaparız.

- Space Complexity

    Çalışan kodların bellekte ne kadar yer kapladığına göre sıralamaya yarar.
    Bazı durumlarda elimizde bellek miktarı limitli olduğunda time-complexity ile bir trade-off içerisinde daha ön planda tutulabilir.
    Ancak genellikle kodun hızlı çalıştığı çözümler tercih edilmektedir.


    | Worst Case : Çözmeye çalıştığımız problem her input için aynı Time complexity'ye sahip olmayacaktır.
                    "Bir Array'de aradığımız bir elemanı bulmak" problemi array'de bulunduğu konuma göre
                        - Best Case (Array'in ilk elemanında bulmak)            Ω   (Omage)
                        - Average Case (Array'de genellikle ortalarda bulmak)   Θ θ (Teta)
                        - Worst Case (Array'de ki son elemanda bulmak)          O   (Big O)
                    olarak farklı durumlarda değerlendirebiliriz. Bizim aradığımız complexity çözümlerinde biz worst case senaryoyu düşüneceğiz.


- Big O(n)

    Sahip olduğumuz algoritmanın input sayısı kadar çalışmasıdır.

    Örneğin,
        "for" döngüsü içinde n tane elemanı konsola bastırmak. Input n ne kadar ise cout işlemi o kadar çalışacaktır.
    
    Big O gösterimlerinde katsayıların bir önemi input sayısı arttıkça önemsizleşecektir. Bu nedenle algoritmaları değerlendirdiğimizde bunları "ignore" ederiz.
    Aynı algoritmada da arka arka iki "for" döngüsü (Dikkat: iç içe değil, birbirinden bağımsız arka arkaya ) O(n) +O(n) = O(2n) olacaktır ki bu da O(n) e denk sayarız. 
    Bizim için artış oranı önemlidir. O(2n) de olsa Lineer bir artış olur

- Big O(n^2)

    Sahip olduğumuz algoritma input sayısının n olduğu durumda n*n=n^2 kadar çalışmasıdır. En az verimli olandır.

    Örneğin,
        "for" döngüsü içinde "for", iç içe "for" döngüsdür.
        Artık n=10 olan bir konsola sayı bastırma işleminde 100 kere konsolda sayılar görünecektir.
        Input sayısı 11 olduğunda ise artık 11 adet değil 11*11=121 kere bastırılacaktır

    Yine karışık algoritmaların karışıklığını basite indirgemek gerekirse, non-dominant olan Big O'lar "ignore" edilebilir.
    O(n^2) + O(n) = O (n^2 + n) olan bir algoritmayı O(n^2) olarak düşünebiliriz.


- Big O(1)

    Algoritmada yapılan işlem, input boyutundan bağımsız olduğu durumdur. Ve işlem süresi hep aynı complexity'ye sahip olacatır.

    Örneğin,
        gelen input değerinin 10 katını döndüren bir fonksiyon.

- Big O(log n)

    Algoritmada yapılan işlemin input sayısının çok daha az oranında yapılmasıdır. Bu oranı logaritmik şekilde ifade edebiliriz.
    Bir diğer deyiş ile, Input sayısı n olan durumda, log2 tabanında n ifadesi kerede çözüme ulaşabilirim. 

    Örneğin,
        Küçükten büyüğe "sort" edilmiş bir array'de aradığımız değeri bulmak için elemanları tek tek bakmak yerine,
        halihazırda sort edildiği için,
        Array'i 2 ye böler ve hangi yarıda olduğunu bulur, sonra aynı yarıya böldüğümüz parçayı tekrar 2 ye bölüp yine hangi yarıda olduğunu bulabiliriz.
        Input sayısı 8 olan bir array'de toplamda 3 iterasyonda aradığımız sayıyı bulabiliriz. 
        (önce 8 taneye bakıp yarıya bölüp 4 tanesi, sonra yarıya 2 tanesi, sonradan 2 taneden hangisi olduğuna bakarız)
        log2 tabanında 8 ifadesi = 3 olarak karşımıza çıkmaktadır.
        Çok bir fark yok gibi gözüküyor değil mi? 
        Eğer ki input sayısı (Array'in boyutu) 1,073,741,824 olsaydı yalnızca 31 iterasyon aradığımız sayıyı bulmak için yeterli olacaktır. :)
        how good is that, right?
    
    O(log n) karmaşıklığa sahip algoritmalar O(1) e oldukça yakınsar inpur sayısı arttıkça.
    Buna divide-conquer şeklinde bir benzetme yapabiliriz.


Big O(n logn)

    Bazı "sorting" (heap, Quick) algoritmaları bu karmaşıklığa sahiptir.


Çok çok iyi bir kaynak olarak -->
                    https://www.bigocheatsheet.com/
*/