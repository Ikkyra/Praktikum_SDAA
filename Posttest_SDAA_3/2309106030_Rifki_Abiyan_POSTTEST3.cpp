#include <iostream>
#include <chrono>
#include <thread>

struct bass_guitar {
    std::string nama_bass;
    std::string brand;
    float harga;
};

struct Node {
    bass_guitar data;
    Node* next;
};

void jeda(int detik);
int isInteger();
float isFloat();
void tambah_bass(Node** head);
void tampilkan_bass(Node* head);
void edit_bass(Node* head);
void hapus_bass(Node** head);
int menu();

void jeda(int detik) {
    std::this_thread::sleep_for(std::chrono::seconds(detik));
}

int isInteger() {
    int nilai;
    while(true) {
        std::cin >> nilai;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Inputan Harus Berupa Angka." << std::endl;
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
            std::cout << "Inputan Harus Berupa Angka." << std::endl;
        } else {
            return nilai;
        }
    }
}

void tambah_bass(Node** head) {
    system("clear");
    Node* new_node = new Node();

    std::cout << "Masukkan Model Bass: ";
    std::getline(std::cin, new_node->data.nama_bass);

    std::cout << "Masukkan Brand Bass: ";
    std::getline(std::cin, new_node->data.brand);

    std::cout << "Masukkan Harga Bass: ";
    new_node->data.harga = isFloat();

    new_node->next = nullptr;

    if (*head == nullptr) {
        *head = new_node;
    } else {
        Node* temp = *head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    std::cout << "Informasi Bass Guitar Berhasil Dimasukkan." << std::endl;
    jeda(3);
}

void tampilkan_bass(Node* head) {
    if (head == nullptr) {
        std::cout << "Tidak Ada Data Bass Guitar." << std::endl;
        jeda(3);    
        return;
    }
    Node* temp = head;
    int i = 1;
    while (temp != nullptr) {
        std::cout << "Bass Guitar ke-" << i++ << std::endl;
        std::cout << "Model Bass Guitar: " << temp->data.nama_bass << std::endl;
        std::cout << "Brand: " << temp->data.brand << std::endl;
        std::cout << "Harga: " << temp->data.harga << std::endl;
        temp = temp->next;
    }
    jeda(3);
}

void edit_bass(Node* head) {
    if (head == nullptr) {
        std::cout << "Tidak Ada Data Untuk Diedit." << std::endl;
        jeda(3);
        return;
    }
    int index, i = 1;
    std::cout << "Masukkan Bass Guitar Yang Ingin Diedit (1-n): ";
    index = isInteger();

    Node* temp = head;
    while (temp != nullptr && i < index) {
        temp = temp->next;
        i++;
    }

    if (temp == nullptr) {
        std::cout << "Index Tidak Valid" << std::endl;
        return;
    }

    std::cout << "Masukkan Model Bass Guitar: ";
    std::getline(std::cin, temp->data.nama_bass);
    
    std::cout << "Masukkan Brand Bass Guitar: ";
    std::getline(std::cin, temp->data.brand);

    std::cout << "Masukkan Harga Bass Guitar: ";
    temp->data.harga = isFloat();
    std::cout << "Data Bass Guitar Berhasil Diedit" << std::endl;
}

void hapus_bass(Node** head) {
    if (*head == nullptr) {
        std::cout << "Tidak Ada Data Untuk Dihapus" << std::endl;
        jeda(3);
        return;
    }
    int index, i = 1;
    std::cout << "Masukkan Index Bass Guitar Yang Ingin Dihapus (1-n): ";
    index = isInteger();

    Node* temp = *head;
    Node* prev = nullptr;

    while (temp != nullptr && i < index) {
        prev = temp;
        temp = temp->next;
        i++;
    }

    if (temp == nullptr) {
        std::cout << "Index Tidak Valid" << std::endl;
        return;
    }

    if (prev == nullptr) {
        *head = (*head)->next;  
    } else {
        prev->next = temp->next;
    }

    delete temp;

    if (*head == nullptr) {
        std::cout << "Semua Data Telah Dihapus." << std::endl;
        jeda(3);
    } else {
        std::cout << "Data Bass Guitar Berhasil Dihapus" << std::endl;
        jeda(3);
    }
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
        pilihan = isInteger();
    }
    return pilihan;
}

int main() {
    Node* head = nullptr;
    int pilihan;

    do {
        pilihan = menu();

        switch (pilihan) {
            case 1:
                tambah_bass(&head);
                break;
            case 2:
                tampilkan_bass(head);
                break;
            case 3:
                edit_bass(head);
                break;
            case 4:
                hapus_bass(&head);
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
