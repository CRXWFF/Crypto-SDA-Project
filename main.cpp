#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct KoinKripto
{
    int no;
    string nama;
    double harga;
    int jumlah;
};

struct Node
{
    KoinKripto data;
    Node *prev;
    Node *next;
};

Node *head = nullptr;
Node *tail = nullptr;

bool isEmpty()
{
    return head == nullptr;
}

void displayBeli()
{
    Node *current = head;
    bool adaKoin = false;
    while (current != nullptr)
    {
        if (current->data.jumlah > 0)
        {
            cout << "Nama: " << current->data.nama << ", Harga: " << current->data.harga << " per keping, Jumlah: " << current->data.jumlah << endl;
            adaKoin = true;
        }
        current = current->next;
    }
    if (!adaKoin)
    {
        cout << "Belum ada koin kripto yang dibeli\n";
    }
}

void beliKripto(string nama, int jumlahBeli, double harga)
{
    Node *kripto = new Node;
    kripto->data.nama = nama;
    kripto->data.jumlah = jumlahBeli;
    kripto->data.harga = harga;
    kripto->next = nullptr;

    if (isEmpty())
    {
        head = tail = kripto;
    }
    else
    {
        tail->next = kripto;
        kripto->prev = tail;
        tail = kripto;
    }
    cout << "Berhasil membeli " << jumlahBeli << " " << nama << endl;
}

void tampilkanDaftarKoin()
{
    KoinKripto koin[] = {
        {1, "Bitcoin", 600000},
        {2, "Cardano", 15},
        {3, "Ondo", 1000},
        {4, "Binance", 5000},
        {5, "XRP", 10}};

    cout << "\nDaftar Koin Kripto yang Tersedia:\n";
    for (const auto &k : koin)
    {
        cout << k.no << " " << "Nama: " << k.nama << ", Harga: " << k.harga << endl;
    }
}

void beliKoinKripto()
{
    string nama;
    int jumlahBeli;
    bool koinDitemukan = false;
    KoinKripto koin[] = {
        {1, "Bitcoin", 600000},
        {2, "Cardano", 15},
        {3, "Ondo", 1000},
        {4, "Binance", 5000},
        {5, "XRP", 10}};

    tampilkanDaftarKoin();
    cout << "Masukkan nama koin kripto: ";
    cin >> nama;

    double hargaKoin = 0.0;

    for (const auto &k : koin)
    {
        if (k.nama == nama)
        {
            koinDitemukan = true;
            hargaKoin = k.harga;
            break;
        }
    }

    if (!koinDitemukan)
    {
        cout << "Koin tidak ditemukan. Berikut adalah daftar koin yang tersedia:\n";
        tampilkanDaftarKoin();

        beliKoinKripto();
        return;
    }

    cout << "Masukkan jumlah koin yang ingin dibeli: ";
    cin >> jumlahBeli;

    if (jumlahBeli > 0)
    {
        beliKripto(nama, jumlahBeli, hargaKoin);
    }
    else
    {
        cout << "Jumlah koin yang ingin dibeli tidak valid\n";
    }
}

void jualKripto(string nama, int jumlahJual)
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->data.nama == nama)
        {
            if (current->data.jumlah >= jumlahJual)
            {
                current->data.jumlah -= jumlahJual;
                cout << "Berhasil menjual " << jumlahJual << " " << nama << endl;
                return;
            }
            else
            {
                cout << "Jumlah kripto yang dimiliki tidak mencukupi" << endl;
                return;
            }
        }
        current = current->next;
    }
    cout << "Kripto tidak ditemukan" << endl;
}

int main()
{
    int pilihan;
    do
    {
        cout << "\n=== MENU ===\n";
        cout << "1. Beli Koin Kripto\n";
        cout << "2. Jual Koin Kripto\n";
        cout << "3. Tampilkan Koin Kripto yang Dibeli\n";
        cout << "4. Tampilkan Koin Kripto yang Tersedia\n";
        cout << "5. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1)
        {
            beliKoinKripto();
        }
        else if (pilihan == 2)
        {
            string nama;
            int jumlahJual;
            tampilkanDaftarKoin();
            cout << "Masukkan nama koin kripto yang ingin dijual: ";
            cin >> nama;
            cout << "Masukkan jumlah koin yang ingin dijual: ";
            cin >> jumlahJual;
            if (jumlahJual > 0)
            {
                jualKripto(nama, jumlahJual);
            }
            else
            {
                cout << "Jumlah koin yang ingin dijual tidak valid\n";
            }
        }
        else if (pilihan == 3)
        {
            cout << "\n=== KOIN KRIPTO YANG DIBELI ===\n";
            displayBeli();
        }
        else if (pilihan == 4)
        {
            cout << "\n=== KOIN KRIPTO TERSEDIA ===\n";
            tampilkanDaftarKoin();
        }

    } while (pilihan != 5);

    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }

    return 0;
}