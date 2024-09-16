//Rifki Abiyan
//2309106030
//POSTTEST 1 SDAA

#include <iostream>

int faktorial(int n) {
    if (n == 0 || n == 1)
        return 1;  
    else
        return n * faktorial(n - 1);  
}

int main() {
    system("clear");
    int tingkat = 3;
    for (int i = 0; i < tingkat; i++) { // i menghitung jumlah baris, j menghitung jumlah elemen
        for (int j = 0; j <= i; j++) {
            std::cout << faktorial(i) / (faktorial(j) * faktorial(i - j)) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
