#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <stack>

using namespace std;

// Struktur objek Data Supir
struct DataSupir {
    int id;
    string name;
    int birthdate, birthmonth, birthyear;
    char gender;
    string address;
};

// Struktur node linked list
struct Node {
    DataSupir data;
    string id; 
    Node *next;
};

struct Order {
    string id;
    string nama;
    string supir;
    string platNomor;
    string tujuan;
    string status;
    Order* next;
};

class DriverList {
    Node *head;
    Node *tail;
    int idCounter;
    
    Order *headOrder;
    Order *tailOrder;
    stack<Order> completedOrders;

private:
    queue<Order> antrianPesanan;
    queue<Order> acceptedOrders;
    queue<Order> deniedOrders;
    queue<Order> orderQueue;

public:
    // Constructor
    DriverList() : head(nullptr) {
        head = NULL;
        tail = NULL;
        headOrder = NULL;
        tailOrder = NULL;
        idCounter = 0;
        Order* headOrder = nullptr;

    }

    Order* getHeadOrder() {
        return headOrder;
    }

    void displayCompletedOrders() {
        stack<Order> tempStack = completedOrders;
        cout << "Completed Orders:" << endl;
        while (!tempStack.empty()) {
            Order currentOrder = tempStack.top();
            cout << "Id : " << currentOrder.id << endl;
            cout << "Nama : " << currentOrder.nama << endl;
            cout << "Supir : " << currentOrder.supir << endl;
            cout << "Plat Nomor : " << currentOrder.platNomor << endl;
            cout << "Tujuan : " << currentOrder.tujuan << endl;
            cout << endl;
            tempStack.pop();

            Order* current = headOrder;
    while (current != nullptr && current->status != "diproses") {
        current = current->next;
    }

    if (current != nullptr) {
        current->status = "completed";
        
        }
    }
    }

void addOrderToList(Order newOrder) {
    Order* newNode = new Order;
    newNode->id = newOrder.id;
    newNode->nama = newOrder.nama;
    newNode->supir = newOrder.supir;
    newNode->platNomor = newOrder.platNomor;
    newNode->tujuan = newOrder.tujuan;
    newNode->next = nullptr;

    if (headOrder == nullptr) {
        headOrder = newNode;
    } else {
        Order* current = headOrder;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

    // Fungsi untuk menambahkan data order
    void addOrder(Order newOrder) {
        Order *newNode = new Order;
        newNode->id = newOrder.id;
        newNode->nama = newOrder.nama;
        newNode->supir = newOrder.supir;
        newNode->platNomor = newOrder.platNomor;
        newNode->tujuan = newOrder.tujuan;
        newNode->next = NULL;

        if (headOrder == NULL) {
            headOrder = newNode;
            tailOrder = newNode;
        } else {
            tailOrder->next = newNode;
            tailOrder = newNode;
        }
    }

    // Fungsi untuk menampilkan daftar order dalam proses pesanan
    void displayOrders() {
        Order *current = headOrder;
        while (current != NULL) {
            cout << "Id : " << current->id << endl;
            cout << "Nama : " << current->nama << endl;
            cout << "Supir : " << current->supir << endl;
            cout << "Plat Nomor : " << current->platNomor << endl;
            cout << "Tujuan : " << current->tujuan << endl;
            cout << endl;
            current = current->next;
        }
    }

    // Fungsi untuk menghasilkan ID supir
    string generateID(DataSupir supir) {
        string id = "";
        int hurufAwal = abs(tolower(supir.name[0]) - tolower(supir.name[supir.name.length() - 1]));
        id += to_string(hurufAwal / 10) + to_string(hurufAwal % 10);

        if (supir.gender == 'l' || supir.gender == 'L') {
            id += "1";
        } else {
            id += "0";
        }

        int date = supir.birthdate % 10;
        int month = (supir.birthmonth / 10) + (supir.birthmonth % 10);
        int year = supir.birthyear % 1000;
        int digit4 = (date + month + year) % 9;
        id += to_string(digit4);

        int duplikat = 0;
        Node *temp = head;
        while (temp != NULL) {
            if (temp->id == id + to_string(duplikat)) {
                duplikat++;
            }
            temp = temp->next;
        }
        id += to_string(duplikat);

        return id;
    }

    // Fungsi untuk menambahkan data supir
    void addSupir() {
        DataSupir supir;
        cout << "Nama : ";
        getline(cin >> ws, supir.name);
        cout << "Tgl Lahir (dd mm yy): ";
        cin >> supir.birthdate >> supir.birthmonth >> supir.birthyear;
        cout << "Kelamin (L/P) : ";
        cin >> supir.gender;
        cin.ignore();
        cout << "Alamat : ";
        getline(cin >> ws, supir.address);

        string id = generateID(supir);
        Node *newNode = new Node;
        newNode->data = supir;
        newNode->id = id;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        idCounter++;

        cout << "Data berhasil ditambahkan !" << endl;
    }

    // Fungsi untuk menampilkan data supir
    void displaySupir(Node *current) {
        cout << "\n";
        cout << "|Nama : " << current->data.name << endl;
        cout << "|Id : " << current->id << "\n";
        cout << "|Tgl Lahir: " << current->data.birthdate << "-" << current->data.birthmonth << "-" << current->data.birthyear << endl;
        cout << "|Kelamin : " << current->data.gender << endl;
        cout << "|Alamat : " << current->data.address << endl;
        cout << "\n";
    }

    // Fungsi untuk menampilkan data supir pada mode admin
    void displayListAdmin() {
        int index = 0;
        Node *current = head;

        while (true) {
            displaySupir(current);
            char choice;
            cout << "1. Next" << endl;
            cout << "2. Previous" << endl;
            cout << "3. Exit" << endl;
            cout << "> ";
            cin >> choice;

            if (choice == '1') {
                if (current->next == NULL) {
                    current = head;
                } else {
                    current = current->next;
                }
            } else if (choice == '2') {
                if (current == head) {
                    while (current->next != NULL) {
                        current = current->next;
                    }
                } else {
                    Node *temp = head;
                    while (temp->next != current) {
                        temp = temp->next;
                    }
                    current = temp;
                }
            } else if (choice == '3') {
                break;
            } else {
                cout << "Pilihan tidak valid." << endl;
            }
        }
    }

    // Fungsi untuk mengedit data supir
    void editSupir() {
        string idSupir;
        cout << "Masukkan Id Supir yang ingin diubah : ";
        cin >> idSupir;
        
        Node* current = head;
        while (current != NULL && current->id != idSupir) {
            current = current->next;
        }
        if (current == NULL) {
            cout << "Id Supir tidak ditemukan." << endl;
            return;
        }
        
        int choice;
        cout << "- Mengubah supir dengan Id " << idSupir << " -" << endl;
        cout << "1. Ubah Nama" << endl;
        cout << "2. Ubah Tgl Lahir" << endl;
        cout << "3. Ubah Kelamin" << endl;
        cout << "4. Ubah Alamat" << endl;
        cout << "> ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                cout << "Masukkan Nama yang baru : ";
                cin.ignore();
                getline(cin >> ws, current->data.name);
                current->id = generateID(current->data);
                cout << "Data Id " << idSupir << " telah berubah !" << endl;
                break;
            }
            case 2: {
                cout << "Masukkan Tgl Lahir (dd mm yyyy) : ";
                cin >> current->data.birthdate >> current->data.birthmonth >> current->data.birthyear;
                current->id = generateID(current->data);
                cout << "Data Id " << idSupir << " telah berubah !" << endl;
                break;
            }
            case 3: {
                cout << "Masukkan Kelamin (L/P) : ";
                cin >> current->data.gender;
                current->id = generateID(current->data);
                cout << "Data Id " << idSupir << " telah berubah !" << endl;
                break;
            }
            case 4: {
                cout << "Masukkan Alamat yang baru : ";
                cin.ignore();
                getline(cin >> ws, current->data.address);
                break;
            }
            default:
            cout << "Pilihan tidak valid." << endl;
        }
        cout << "Data berhasil diperbarui!" << endl;
    }

    // Fungsi untuk menghapus data supir
    void delSupir() {
        string idSupir;
        cout << "Id yang ingin dihapus : ";
        cin >> idSupir;
        
        Node* current = head;
        Node* prev = NULL;
        
        while (current != NULL && current->id != idSupir) {
            prev = current;
            current = current->next;
        }
        if (current == NULL) {
            cout << "Id Supir tidak ditemukan." << endl;
        return;
        }
        
        char confirm;
        cout << "Supir dengan data berikut akan dihapus :" << endl;
        
        displaySupir(current);
        cout << "Lanjutkan ? (Y/N) > ";
        cin >> confirm;
        
        if (confirm == 'Y' || confirm == 'y') {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
        delete current;
        idCounter--;
        cout << "Supir dengan Id " << idSupir << " berhasil dihapus !" << endl;
        } else {
            cout << "Penghapusan data supir dibatalkan." << endl;
        }
    }

    
//----------------------------------------------------------------
// GENERATE ID ORDER JANGAN DI RUSAKAN
//----------------------------------------------------------------
    string generateOrderId(int driverId, const string& tujuan, const string& customerName, const string& plateNumber) {
    string orderId;

    // Mengambil 2 digit pertama dari urutan alfabet karakter pertama plat nomor
    orderId += to_string(toupper(plateNumber[0]) - 'A' + 1);
    orderId = string(2 - orderId.length(), '0') + orderId;

    // Mengambil 5 digit dari ID supir
    orderId += to_string(driverId);
    orderId = string(5 - orderId.length(), '0') + orderId;

    // Mengambil 2 digit dari urutan alfabet 2 karakter terakhir tujuan
    int tujuanSum = toupper(tujuan[tujuan.length() - 2]) - 'A' + 1 +
                         toupper(tujuan[tujuan.length() - 1]) - 'A' + 1;
    orderId += to_string(tujuanSum);
    orderId = string(2 - orderId.length(), '0') + orderId;

    // Mengambil digit terakhir dari penjumlahan urutan alfabet nama pelanggan
    int nameSum = 0;
    for (char c : customerName) {
        nameSum += toupper(c) - 'A' + 1;
    }
    orderId += to_string(nameSum % 10);

    return orderId;
}

//----------------------------------------------------------------
//----------------------------------------------------------------

    /// Fungsi untuk menampilkan daftar supir (mode user)
void displayListUser() {
    Node *current = head;
    queue<Order> orderQueue; // Deklarasi orderQueue sebagai variabel lokal
    string idSupir;

    while (true) {
        displaySupir(current);

        char choice;
        cout << "1. Next" << endl;
        cout << "2. Previous" << endl;
        cout << "3. Order" << endl;
        cout << "4. Exit" << endl;
        cout << "> ";
        cin >> choice;

        if (choice == '1') {
            if (current->next == NULL) {
                current = head;
            } else {
                current = current->next;
            }
        } else if (choice == '2') {
            if (current == head) {
                while (current->next != NULL) {
                    current = current->next;
                }
            } else {
                Node *temp = head;
                while (temp->next != current) {
                    temp = temp->next;
                }
                current = temp;
            }
        } else if (choice == '3') {
            orderMenu();
        } else if (choice == '4') {
            break;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }
}

void orderMenu() {
    string namaPelanggan;
    string tujuanPelanggan;
    char orderLagi;

    do {
        cout << "Masukkan nama pelanggan: ";
        cin >> namaPelanggan;
        cout << "Masukkan tujuan pelanggan: ";
        cin >> tujuanPelanggan;

        // Menampilkan daftar supir untuk memilih supir yang akan mengambil order
        string idSupir;
        Node *currentSupir = head;
        cout << "Daftar Supir:" << endl;
        while (currentSupir != NULL) {
            cout << "Nama: " << currentSupir->data.name << " | ID: " << currentSupir->id << endl;
            currentSupir = currentSupir->next;
        }
        cout << "Masukkan ID supir yang dipilih: ";
        cin >> idSupir;

        // Cari supir berdasarkan ID
        Node *current = head;
        while (current != NULL && current->id != idSupir) {
            current = current->next;
        }

        if (current != NULL) {
            DataSupir supirPilihan = current->data;

            // Membuat ID order sesuai aturan
            string orderId;
            orderId += to_string(toupper("L 1996 YZ"[0]) - 'A' + 1);
            orderId = string(2 - orderId.length(), '0') + orderId;
            orderId += idSupir;
            orderId = string(7 - orderId.length(), '0') + orderId;
            int tujuanSum = toupper(tujuanPelanggan[tujuanPelanggan.length() - 2]) - 'A' + 1 +
                            toupper(tujuanPelanggan[tujuanPelanggan.length() - 1]) - 'A' + 1;
            orderId += to_string(tujuanSum);
            orderId = string(9 - orderId.length(), '0') + orderId;
            int nameSum = 0;
            for (char c : namaPelanggan) {
                nameSum += toupper(c) - 'A' + 1;
            }
            orderId += to_string(nameSum % 10);

            Order newOrder;
            newOrder.id = orderId;
            newOrder.nama = namaPelanggan;
            newOrder.supir = supirPilihan.name;
            newOrder.platNomor = "L 1996 YZ";
            newOrder.tujuan = tujuanPelanggan;

            orderQueue.push(newOrder);

            cout << endl;
            cout << "Order telah dilakukan !!!" << endl;
            cout << "Id : " << newOrder.id << endl;
            cout << "Nama : " << newOrder.nama << endl;
            cout << "Supir : " << newOrder.supir << endl;
            cout << "Plat Nomor : " << newOrder.platNomor << endl;
            cout << "Tujuan : " << newOrder.tujuan << endl;
            cout << endl;
        } else {
            cout << "ID supir tidak valid. Silakan coba lagi.\n";
        }

        cout << "Ingin melakukan order lagi? (y/n): ";
        cin >> orderLagi;

    } while (orderLagi == 'y' || orderLagi == 'Y');
}

void processOrder() {
    if (!orderQueue.empty()) {
        Order order = orderQueue.front();
        orderQueue.pop();
        cout << "Id : " << order.id << "\n";
        cout << "Nama : " << order.nama << "\n";
        cout << "Supir : " << order.supir << "\n";
        cout << "Plat nomor : " << order.platNomor << "\n";
        cout << "Tujuan : " << order.tujuan << "\n";

        char acceptOrder;
        cout << "Terima pesanan ini? (y/n): ";
        cin >> acceptOrder;

        if (acceptOrder == 'y' || acceptOrder == 'Y') {
            acceptedOrders.push(order);
        } else {
            deniedOrders.push(order);
        }
    } else {
        cout << "Tidak ada order untuk diproses.\n";
    }
}
};




int main() {
    int choice;

    DriverList driverList; // Buat objek dari kelas DriverList

    while (true) {
        cout << "=================================================================" << endl;
        cout << "WELCOME TO APLIKASI ORDER SUPIR" << endl;
        cout << "1. Masuk sebagai Admin" << endl;
        cout << "2. Masuk sebagai User" << endl;
        cout << "3. Exit" << endl;
        cout << "=================================================================" << endl;
        cout << "> ";
        cin >> choice;

        if (choice == 1) {
            int adminChoice;
            while (true) {
                cout << "=================================================================" << endl;
                cout << " Menu Admin " << endl;
                cout << "=================================================================" << endl;
                cout << "1. Tambah Supir" << endl;
                cout << "2. Edit Supir" << endl;
                cout << "3. Hapus Supir" << endl;
                cout << "4. Lihat Daftar Supir" << endl;
                cout << "5. Proses Pesanan" << endl;
                cout << "0. Kembali" << endl;
                cout << "> ";
                cin >> adminChoice;

                if (adminChoice == 1) {
                    driverList.addSupir();
                } 
                else if (adminChoice == 2) {
                    driverList.editSupir();
                } 
                else if (adminChoice == 3) {
                    driverList.delSupir();
                } 
                else if (adminChoice == 4) {
                    driverList.displayListAdmin();
                } else if (adminChoice == 5) {
                    driverList.processOrder();
                } else if (adminChoice == 0) {
                    break;
                } else {
                    cout << "Pilihan tidak valid." << endl;
                }
            }
        } else if (choice == 2) {
            driverList.displayListUser();
        } else if (choice == 3) {
            break;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}