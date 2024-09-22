#include <iostream>
#include <chrono>
#include <thread>

struct bass_guitar{
    std::string nama_bass;
    std::string brand;
    float harga;
};

void jeda(int detik);
int isInteger();
float isFloat();
void tambah_bass();
void tampilkan_bass();
void edit_bass();
void hapus_bass();
int menu();

void jeda(int detik) {
    std::this_thread::sleep_for(std::chrono::seconds(detik));
}

int isInteger(){
    int nilai;
    while(true) {
        std::cin >> nilai;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Inputan harus berupa angka." << std::endl;
        } else {
            std::cin.ignore(1000, '\n');
            return nilai;
        }
    }
}

float isFloat() {
    float nilai;
    while(true) {
        std::cin >> nilai;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Inputan harus berupa angka." << std::endl;
        } else {
            return nilai;
        }
    }
}

void tambah_bass(bass_guitar* list, int* jumlah_bass) {
    system("clear");
    std::cout << "Masukkan nama bass: ";
    std::cin >> list[*jumlah_bass].nama_bass;
    std::cout << "Masukkan brand bass: ";
    std::cin >> list[*jumlah_bass].brand;
    std::cout << "Masukkan harga bass: ";
    list[*jumlah_bass].harga = isFloat();
    (*jumlah_bass)++;
    std::cout << "Informasi Bass Guitar Berhasil Dimasukkan." << std::endl;
}

void tampilkan_bass(bass_guitar* list, int jumlah_bass) {
    if(jumlah_bass == 0) {
        std::cout << "Tidak ada data bass guitar." << std::endl;
        return;
    }
    for (int i = 0; i < jumlah_bass; i++) {
        std::cout << "Bass Guitar ke-" << i + 1 << std::endl;
        std::cout << "Nama Bass Guitar: " << list[i].nama_bass << std::endl;
        std::cout << "Brand: " << list[i].brand << std::endl;
        std::cout << "Harga: " << list[i].harga << std::endl;
    }
    jeda(3);
}

void edit_bass(bass_guitar* list, int jumlah_bass) {
    if (jumlah_bass == 0) {
        std::cout << "Tidak ada Data Untuk Diedit." << std::endl;
        return;
    }
    int index;
    std::cout << "Masukkan Bass Guitar Yang Ingin Diedit (1-" << jumlah_bass << "): ";
    index = isInteger();
    if (index < 1 || index > jumlah_bass) {
        std::cout << "Index Tidak Valid" << std::endl;
        return;
    }
    index--;
    std::cout << "Masukkan Nama Bass Guitar: ";
    std::cin >> list[index].nama_bass;
    std::cout << "Masukkan Brand Bass Guitar: ";
    std::cin >> list[index].brand;
    std::cout << "Masukkan Harga Bass Guitar: ";
    list[index].harga = isFloat();
    std::cout << "Data Bass Guitar Berhasil Diedit" << std::endl;
}

void hapus_bass(bass_guitar* list, int* jumlah_bass) {
    if (*jumlah_bass == 0) {
        std::cout << "Tidak Ada Data Untuk Dihapus" << std::endl;
        return;
    }
    int index;
    std::cout << "Masukkan Index Bass Guitar Yang Ingin Dihapus (1-" << *jumlah_bass << "): ";
    index = isInteger();
    if (index < 1 || index > *jumlah_bass) {
        std::cout << "Index Tidak Valid" << std::endl;
        return;
    }
    index--;
    for (int i = index; i < *jumlah_bass - 1; i++) {
        list[i] = list[i + 1];
    }
    (*jumlah_bass)--;
    std::cout << "Data Bass Guitar Berhasil Dihapus" << std::endl;
}

int menu() {
    system("clear");
    int pilihan;
    std::cout << "===========================" << std::endl;
    std::cout << "===  List Bass Guitar   ===" << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << "[1] Tambah Bass Guitar   []" << std::endl;
    std::cout << "[2] Daftar Bass Guitar   []" << std::endl;
    std::cout << "[3] Edit Bass Guitar     []" << std::endl;
    std::cout << "[4] Hapus Bass Guitar    []" << std::endl;
    std::cout << "[5] Keluar               []" << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << "Pilihan: ";
    pilihan = isInteger();
    while (pilihan < 1 || pilihan > 5) {
        std::cout << "Pilihan Tidak Valid, Masukkan Angka 1-5" << std::endl;
        // std::cout << "Pilihan: ";
        pilihan = isInteger();
    }
    return pilihan;
}

int main() {
    bass_guitar list[20];
    int jumlah_bass = 0;
    int pilihan;

    do {
        pilihan = menu();

        switch (pilihan) {
            case 1:
                tambah_bass(list, &jumlah_bass);
                break;
            case 2:
                tampilkan_bass(list, jumlah_bass);
                break;
            case 3:
                edit_bass(list, jumlah_bass);
                break;
            case 4:
                hapus_bass(list, &jumlah_bass);
                break;
            case 5:
                std::cout << "Keluar Dari Program" << std::endl;
                break;
            default:
                std::cout << "Pilihan Tidak Valid" << std::endl;
        }
    } while (pilihan != 5);

    return 0;
}