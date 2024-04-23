#include <iostream>
#include <string>
#include <fstream>
using namespace std;
// ghaisan meledak
struct UserData
{
    string username, password;
};

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

void registerUser()
{
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    if (file.is_open())
    {
        file << username << " " << password << endl;
        file.close();
        cout << "Registrasi berhasil" << endl;
    }
    else
    {
        cout << "Gagal membuka file" << endl;
    }
}

bool loginUser()
{
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    ifstream file("users.txt");
    if (file.is_open())
    {
        string storedUsername, storedPassword;
        while (file >> storedUsername >> storedPassword)
        {
            if (storedUsername == username && storedPassword == password)
            {
                file.close();
                cout << "Login berhasil" << endl;
                return true;
            }
        }
        file.close();
    }
    else
    {
        cout << "Gagal membuka file" << endl;
    }

    cout << "Username atau password salah" << endl;
    return false;
}

int main()
{
    int pilihan;
    bool isLoggedIn = false;

    do
    {
        cout << "\n=== MENU ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Beli Koin Kripto\n";
        cout << "4. Jual Koin Kripto\n";
        cout << "5. Tampilkan Koin Kripto yang Dibeli\n";
        cout << "6. Tampilkan Koin Kripto yang Tersedia\n";
        cout << "7. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1)
        {
            registerUser();
        }
        else if (pilihan == 2)
        {
            if (loginUser())
            {
                isLoggedIn = true;
                cout << "Login berhasil" << endl;
            }
        }
        else if (pilihan == 3)
        {
            if (isLoggedIn)
            {
                beliKoinKripto();
            }
            else
            {
                cout << "Anda harus login terlebih dahulu" << endl;
            }
        }
        else if (pilihan == 4)
        {
            if (isLoggedIn)
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
            else
            {
                cout << "Anda harus login terlebih dahulu" << endl;
            }
        }
        else if (pilihan == 5)
        {
            if (isLoggedIn)
            {
                cout << "\n=== KOIN KRIPTO YANG DIBELI ===\n";
                displayBeli();
            }
            else
            {
                cout << "Anda harus login terlebih dahulu" << endl;
            }
        }
        else if (pilihan == 6)
        {
            if (isLoggedIn)
            {
                cout << "\n=== KOIN KRIPTO TERSEDIA ===\n";
                tampilkanDaftarKoin();
            }
            else
            {
                cout << "Anda harus login terlebih dahulu" << endl;
            }
        }
    } while (pilihan != 7);

    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }

    return 0;
}