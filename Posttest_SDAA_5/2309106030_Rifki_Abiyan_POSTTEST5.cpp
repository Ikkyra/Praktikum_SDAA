#include <iostream>
#include <chrono>
#include <thread>
#define max_stack 4 
#define max_queue 4 

struct bass_guitar {
    std::string nama_bass;
    std::string brand;
    float harga;
};

struct Node {
    bass_guitar data;
    Node* next;
};

// Stack 
void push(Node** stack_top, bass_guitar new_bass, int& stack_counter);
void pop(Node** stack_top, int& stack_counter);
void peekStack(Node* stack_top);
// Queue
void enqueue(Node** queue_front, Node** queue_rear, bass_guitar new_bass, int& queue_counter);
void dequeue(Node** queue_front, Node** queue_rear, int& queue_counter);
void peekQueue(Node* queue_front);

void frontBackSplit();
void mergeSort();
void quickSort();
void printList();
void sortMenu();

void jeda(int detik);
int isInteger();
float isFloat();
bass_guitar input_bass_data();
void display_bass(Node* node);
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

bass_guitar input_bass_data() {
    bass_guitar new_bass;
    std::cout << "Masukkan Model Bass: ";
    std::getline(std::cin, new_bass.nama_bass);
    std::cout << "Masukkan Brand Bass: ";
    std::getline(std::cin, new_bass.brand);
    std::cout << "Masukkan Harga Bass: ";
    new_bass.harga = isFloat();
    return new_bass;
}

void display_bass(Node* node) {
    if (node) {
        std::cout << "Model Bass Guitar: " << node->data.nama_bass << std::endl;
        std::cout << "Brand: " << node->data.brand << std::endl;
        std::cout << "Harga: " << node->data.harga << std::endl;
        jeda(3);
    }
}

// Stack 
void push(Node** stack_top, bass_guitar new_bass, int& stack_counter) {
    if (stack_counter == max_stack) {
        std::cout << "Stack overflow! Tidak bisa menambahkan bass lebih dari " << max_stack << " elemen." << std::endl;
        jeda(3);
        return;
    }
    Node* new_node = new Node();
    new_node->data = new_bass;
    new_node->next = *stack_top;
    *stack_top = new_node;
    stack_counter++;
    std::cout << "Bass Guitar Berhasil Ditambahkan ke Stack." << std::endl;
    jeda(3);
}

void pop(Node** stack_top, int& stack_counter) {
    if (*stack_top == nullptr) {
        std::cout << "Stack Kosong, Tidak Ada Data Untuk Dihapus." << std::endl;
        jeda(3);
        return;
    }
    Node* temp = *stack_top;
    *stack_top = (*stack_top)->next;
    delete temp;
    stack_counter--;
    std::cout << "Bass Guitar Berhasil Dihapus dari Stack." << std::endl;
    jeda(3);
}

void peekStack(Node* stack_top) {
    if (stack_top == nullptr) {
        std::cout << "Stack Kosong." << std::endl;
        jeda(3);
    } else {
        std::cout << "Bass Guitar Paling Atas di Stack:" << std::endl;
        display_bass(stack_top);
        jeda(3);
    }
}

// Queue
void enqueue(Node** queue_front, Node** queue_rear, bass_guitar new_bass, int& queue_counter) {
    if (queue_counter == max_queue) {
        std::cout << "Queue overflow! Tidak bisa menambahkan bass lebih dari " << max_queue << " elemen." << std::endl;
        jeda(3);
        return;
    }
    Node* new_node = new Node();
    new_node->data = new_bass;
    new_node->next = nullptr;
    
    if (*queue_rear == nullptr) {
        *queue_front = *queue_rear = new_node;
    } else {
        (*queue_rear)->next = new_node;
        *queue_rear = new_node;
    }
    queue_counter++;
    std::cout << "Bass Guitar Berhasil Ditambahkan ke Queue." << std::endl;
    jeda(3);
}

void dequeue(Node** queue_front, Node** queue_rear, int& queue_counter) {
    if (*queue_front == nullptr) {
        std::cout << "Queue Kosong, Tidak Ada Data Untuk Dihapus." << std::endl;
        jeda(3);
        return;
    }
    Node* temp = *queue_front;
    *queue_front = (*queue_front)->next;
    if (*queue_front == nullptr) {
        *queue_rear = nullptr; 
    }
    delete temp;
    queue_counter--;
    std::cout << "Bass Guitar Berhasil Dihapus dari Queue." << std::endl;
    jeda(3);
}

void peekQueue(Node* queue_front) {
    if (queue_front == nullptr) {
        std::cout << "Queue Kosong." << std::endl;
        jeda(3);
    } else {
        std::cout << "Bass Guitar Paling Depan di Queue:" << std::endl;
        display_bass(queue_front);
        jeda(3);
    }
}

Node* sortedMerge(Node* a, Node* b, bool ascending) {
    Node* result = nullptr;

    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;

    if (ascending ? (a->data.harga <= b->data.harga) : (a->data.harga >= b->data.harga)) {
        result = a;
        result->next = sortedMerge(a->next, b, ascending);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next, ascending);
    }
    return result;
}

void frontBackSplit(Node* source, Node** frontRef, Node** backRef) {
    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

// Merge Sort
void mergeSort(Node** headRef, bool ascending) {
    Node* head = *headRef;
    Node* a;
    Node* b;

    if ((head == nullptr) || (head->next == nullptr)) {
        return;
    }

    frontBackSplit(head, &a, &b);

    mergeSort(&a, ascending);
    mergeSort(&b, ascending);

    *headRef = sortedMerge(a, b, ascending);
}

// Quick Sort
Node* getTail(Node* cur) {
    while (cur != nullptr && cur->next != nullptr)
        cur = cur->next;
    return cur;
}

Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd, bool ascending) {
    Node* pivot = end;
    Node* prev = nullptr;
    Node* cur = head;
    Node* tail = pivot;

    while (cur != pivot) {
        if (ascending ? (cur->data.harga < pivot->data.harga) : (cur->data.harga > pivot->data.harga)) {
            if ((*newHead) == nullptr)
                (*newHead) = cur;

            prev = cur;
            cur = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;
            Node* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newHead) == nullptr)
        (*newHead) = pivot;

    (*newEnd) = tail;

    return pivot;
}

Node* quickSortRecur(Node* head, Node* end, bool ascending) {
    if (!head || head == end)
        return head;

    Node* newHead = nullptr;
    Node* newEnd = nullptr;

    Node* pivot = partition(head, end, &newHead, &newEnd, ascending);

    if (newHead != pivot) {
        Node* temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortRecur(newHead, temp, ascending);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd, ascending);

    return newHead;
}

void quickSort(Node** headRef, bool ascending) {
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef), ascending);
}

void printList(Node* node) {
    while (node != nullptr) {
        display_bass(node);
        node = node->next;
    }
}

int menu() {
    system("clear");
    int pilihan;
    std::cout << "=============================" << std::endl;
    std::cout << "===   List Bass Guitar   ===" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "[1] Push Bass ke Stack     []" << std::endl;
    std::cout << "[2] Pop Bass dari Stack    []" << std::endl;
    std::cout << "[3] Peek Bass di Stack     []" << std::endl;
    std::cout << "[4] Enqueue Bass ke Queue  []" << std::endl;
    std::cout << "[5] Dequeue Bass dari Queue[]" << std::endl;
    std::cout << "[6] Peek Bass di Queue     []" << std::endl;
    std::cout << "[7] Sorting                []" << std::endl;
    std::cout << "[8] Keluar                 []" << std::endl;  
    std::cout << "=============================" << std::endl;
    std::cout << "Pilihan: ";
    pilihan = isInteger();
    while (pilihan < 1 || pilihan > 8) {
        std::cout << "Pilihan Tidak Valid, Masukkan Angka 1-8" << std::endl;
        pilihan = isInteger();
    }
    return pilihan;
}

void sortMenu(Node** stack_top, Node** queue_front) {
    int choice;
    std::cout << "Pilih Metode Sorting:" << std::endl;
    std::cout << "[1] Merge Sort Ascending (Stack)" << std::endl;
    std::cout << "[2] Quick Sort Descending (Queue)" << std::endl;
    std::cout << "Pilihan: ";
    choice = isInteger();

    switch (choice) {
        case 1:
            mergeSort(stack_top, true);
            std::cout << "Stack setelah Merge Sort Ascending:" << std::endl;
            printList(*stack_top);
            break;
        case 2:
            quickSort(queue_front, false);
            std::cout << "Queue setelah Quick Sort Descending:" << std::endl;
            printList(*queue_front);
            break;
        default:
            std::cout << "Pilihan Tidak Valid" << std::endl;
    }
}

int main() {
    Node* stack_top = nullptr;
    Node* queue_front = nullptr;
    Node* queue_rear = nullptr;
    int stack_counter = 0;
    int queue_counter = 0;
    int pilihan;

    do {
        pilihan = menu();
        bass_guitar new_bass;

        switch (pilihan) {
            case 1:
                new_bass = input_bass_data();
                push(&stack_top, new_bass, stack_counter);
                break;
            case 2:
                pop(&stack_top, stack_counter);
                break;
            case 3:
                peekStack(stack_top);
                break;
            case 4:
                new_bass = input_bass_data();
                enqueue(&queue_front, &queue_rear, new_bass, queue_counter);
                break;
            case 5:
                dequeue(&queue_front, &queue_rear, queue_counter);
                break;
            case 6:
                peekQueue(queue_front);
                break;
            case 7:
                sortMenu(&stack_top, &queue_front);
                break;
            case 8:
                std::cout << "Keluar Dari Program" << std::endl;
                break;
            default:
                std::cout << "Pilihan Tidak Valid" << std::endl;
        }
    } while (pilihan != 8);

    return 0;
}


