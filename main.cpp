#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <sstream>
using namespace std;

struct UserData
{
    string username, password;
    double saldo; 
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

struct Riwayat
{
    int saldoAwal;
    string keterangan;
    int saldoAkhir;
    Riwayat* prev;
    Riwayat* next;
};


Node *head = nullptr;
Node *tail = nullptr;
Riwayat* riwayatHead = nullptr;
UserData currentUser;
double currentUserSaldo = 0;

bool isEmpty()
{
    return head == nullptr;
}

void insertRiwayat(double saldoAwal, string keterangan, double saldoAkhir) {
    Riwayat* newRiwayat = new Riwayat();
    newRiwayat->saldoAwal = saldoAwal;
    newRiwayat->keterangan = keterangan;
    newRiwayat->saldoAkhir = saldoAkhir;
    newRiwayat->prev = nullptr;
    newRiwayat->next = riwayatHead;
    if (riwayatHead != nullptr) {
        riwayatHead->prev = newRiwayat;
    }
    riwayatHead = newRiwayat;
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

void insertFirst(KoinKripto koin)
{
    Node *newNode = new Node;
    newNode->data = koin;
    newNode->prev = nullptr;
    newNode->next = head;

    if (head != nullptr)
    {
        head->prev = newNode;
    }

    head = newNode;

    if (tail == nullptr)
    {
        tail = newNode;
    }
}

void insertLast(KoinKripto koin)
{
    if (isEmpty())
    {
        insertFirst(koin);
        return;
    }

    Node *newNode = new Node;
    newNode->data = koin;
    newNode->next = nullptr;
    newNode->prev = tail;

    tail->next = newNode;
    tail = newNode;
}

void beliKripto(string nama, int jumlahBeli, double harga)
{
    Node *current = head;
    bool koinDitemukan = false;

    while (current != nullptr)
    {
        if (current->data.nama == nama)
        {
            koinDitemukan = true;
            current->data.jumlah += jumlahBeli;
            cout << "Berhasil menambah " << jumlahBeli << " " << nama << endl;
            return;
        }
        current = current->next;
    }

    if (!koinDitemukan)
    {
        KoinKripto koin;
        koin.nama = nama;
        koin.jumlah = jumlahBeli;
        koin.harga = harga;
        insertLast(koin);
    }
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
        cout << k.no << " "
             << "Nama: " << k.nama << ", Harga: " << k.harga << endl;
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
        return;
    }

    cout << "Masukkan jumlah koin yang ingin dibeli: ";
    cin >> jumlahBeli;

    if (jumlahBeli > 0)
    {
        double totalHarga = jumlahBeli * hargaKoin;

        if (currentUser.saldo >= totalHarga)
        {
            double saldoSebelum = currentUser.saldo;
            beliKripto(nama, jumlahBeli, hargaKoin);
            currentUser.saldo -= totalHarga;
            
            cout << "Transaksi berhasil" << endl;
            // Insert riwayat
            stringstream ss;
            ss << "Membeli kripto " << nama << " sebanyak " << jumlahBeli << " dengan total harga " << fixed << setprecision(2) << totalHarga;
            insertRiwayat(saldoSebelum, ss.str(), currentUser.saldo);
        }
        else
        {
            cout << "Saldo tidak mencukupi" << endl;
        }
    }
    else
    {
        cout << "Jumlah koin yang ingin dibeli tidak valid\n";
    }
}

void jualKripto(string nama, int jumlahJual)
{
    Node *current = head;
    bool koinDitemukan = false;

    while (current != nullptr)
    {
        if (current->data.nama == nama)
        {
            koinDitemukan = true;
            if (current->data.jumlah >= jumlahJual)
            {
                double saldoSebelum = currentUser.saldo;
                current->data.jumlah -= jumlahJual;
                currentUser.saldo += jumlahJual * current->data.harga;
                cout << "Berhasil menjual " << jumlahJual << " " << nama << endl;
                // Insert riwayat
                stringstream ss;
                double totalHarga = jumlahJual * current->data.harga;
                ss << "Menjual kripto " << nama << " sebanyak " << jumlahJual << " dengan total harga " << fixed << setprecision(2) << totalHarga;
                insertRiwayat(saldoSebelum, ss.str(), currentUser.saldo);
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
    if (!koinDitemukan)
    {
        cout << "Kripto tidak ditemukan" << endl;
    }
}

void registerUser()
{
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;

    cout << "Masukkan password: ";
    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (password.length() > 0)
            {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            cout << '*';
            password += ch;
        }
    }

    ofstream file("users.txt", ios::app);
    if (file.is_open())
    {
        file << username << " " << password << endl;
        file.close();
        cout << endl
             << "Registrasi berhasil" << endl;
    }
    else
    {
        cout << endl
             << "Gagal membuka file" << endl;
    }
}

bool loginUser()
{
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;

    cout << "Masukkan password: ";
    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (password.length() > 0)
            {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            cout << '*';
            password += ch;
        }
    }

    ifstream file("users.txt");
    if (file.is_open())
    {
        string storedUsername, storedPassword;
        while (file >> storedUsername >> storedPassword)
        {
            if (storedUsername == username && storedPassword == password)
            {
                file.close();
                cout << endl
                     << "Login berhasil" << endl;
                return true;
            }
        }
        file.close();
    }
    else
    {
        cout << endl
             << "Gagal membuka file" << endl;
    }

    cout << "Username atau password salah" << endl;
    return false;
}

void topUpSaldo() {
    double saldoSebelumTopup = currentUserSaldo; // Menyimpan saldo sebelum top up
    double topUpAmount;
    cout << "Masukkan jumlah saldo yang ingin ditambahkan: ";
    cin >> topUpAmount;
    if (topUpAmount > 0) {
        // Memperbarui saldo pengguna
        currentUserSaldo += topUpAmount;
        // Memasukkan riwayat top up ke dalam riwayat transaksi
        stringstream ss;
        ss << "Top up saldo sebesar " << fixed << setprecision(2) << topUpAmount;
        insertRiwayat(saldoSebelumTopup, ss.str(), currentUserSaldo);
        cout << "Saldo berhasil ditambahkan. Saldo Anda sekarang: " << fixed << setprecision(2) << currentUserSaldo << endl;
        currentUser.saldo += topUpAmount;
    }
    else {
        cout << "Jumlah saldo yang dimasukkan tidak valid" << endl;
    }
}

void displayRiwayat() {
    cout << "Riwayat Transaksi:" << endl;
    Riwayat* current = riwayatHead;
    while (current != nullptr) {
        cout << "==============================================" << endl;
        cout << "Saldo Awal: " << fixed << setprecision(2) << current->saldoAwal << endl;
        cout << "Keterangan: " << current->keterangan << endl;
        cout << "Saldo Akhir: " << fixed << setprecision(2) << current->saldoAkhir << endl;
        cout << "==============================================" << endl;
        current = current->next;
    }
}


int main()
{
    int pilihan;
    bool isLoggedIn = false;

    do
    {
        cout << "\n=== Selamat Datang di Aplikasi Kriptox! ===\n";
        cout << "\nBerikut Menu Andalan Kami:\n";
        cout << "\n=== MENU ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Top Up Saldo\n";
        cout << "4. Beli Koin Kripto\n";
        cout << "5. Jual Koin Kripto\n";
        cout << "6. Tampilkan Koin Kripto yang Dibeli\n";
        cout << "7. Tampilkan Koin Kripto yang Tersedia\n";
        cout << "8. Tampilkan Saldo\n"; 
        cout << "9. Riwayat Transaksi\n"; 
        cout << "9. Keluar\n";
        cout << "================================================\n";
        cout << "\nSelahkan Masukan Pilihan Anda: ";
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
                topUpSaldo();
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
                beliKoinKripto();
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
        else if (pilihan == 6)
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
        else if (pilihan == 7)
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
        else if (pilihan == 8)
        {
            if (isLoggedIn)
            {
                cout << "Saldo Anda: " << currentUser.saldo << endl;
            }
            else
            {
                cout << "Anda harus login terlebih dahulu" << endl;
            }
        }
        else if (pilihan == 9)
        {
            if (isLoggedIn)
            {
                displayRiwayat();
            }
            else
            {
                cout << "Anda harus login terlebih dahulu" << endl;
            }
        }
    } while (pilihan != 10);
    cout << "Program Selesai" << endl;
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }

    return 0;
}