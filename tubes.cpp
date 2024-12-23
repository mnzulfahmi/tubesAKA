#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono> // Untuk mengukur waktu eksekusi

using namespace std;

// ========================= Fungsi Greedy (Iteratif) =========================
void optimasiPekerjaanIteratif(int K, vector<pair<int, int>>& pekerjaan) {
    sort(pekerjaan.begin(), pekerjaan.end()); // Urutkan berdasarkan durasi

    int waktu_tersisa = K;
    vector<pair<int, int>> pekerjaan_terpilih;
    int total_waktu_dipakai = 0;

    for (const auto& p : pekerjaan) {
        if (p.first <= waktu_tersisa) {
            pekerjaan_terpilih.push_back(p);
            waktu_tersisa -= p.first;
            total_waktu_dipakai += p.first;
        }
    }

    // Output hasil
    cout << "\n[Iteratif - Greedy]\n";
    cout << "Total pekerjaan yang dapat diselesaikan: " << pekerjaan_terpilih.size() << endl;
    for (const auto& p : pekerjaan_terpilih) {
        cout << "Pekerjaan ke-" << p.second << ": " << p.first << " jam\n";
    }
    cout << "Total jam: " << total_waktu_dipakai << " jam\n";
    cout << "Sisa jam: " << waktu_tersisa << " jam\n";
}

// ========================= Fungsi Backtracking (Rekursif) =========================
vector<pair<int, int>> solusi_terbaik;
int waktu_terbaik = 0;
int jumlah_pekerjaan_terbaik = 0;

void optimasiPekerjaanRekursif(int indeks, int waktu_tersisa, int total_waktu_dipakai, 
                               int jumlah_pekerjaan, vector<pair<int, int>>& pekerjaan, 
                               vector<pair<int, int>>& pekerjaan_terpilih) {
    if (indeks == pekerjaan.size()) {
        // Prioritaskan jumlah pekerjaan, lalu total waktu
        if (jumlah_pekerjaan > jumlah_pekerjaan_terbaik || 
           (jumlah_pekerjaan == jumlah_pekerjaan_terbaik && total_waktu_dipakai > waktu_terbaik)) {
            waktu_terbaik = total_waktu_dipakai;
            jumlah_pekerjaan_terbaik = jumlah_pekerjaan;
            solusi_terbaik = pekerjaan_terpilih;
        }
        return;
    }

    // Eksplorasi tanpa memilih pekerjaan saat ini
    optimasiPekerjaanRekursif(indeks + 1, waktu_tersisa, total_waktu_dipakai, 
                              jumlah_pekerjaan, pekerjaan, pekerjaan_terpilih);

    // Eksplorasi dengan memilih pekerjaan saat ini
    if (pekerjaan[indeks].first <= waktu_tersisa) {
        pekerjaan_terpilih.push_back(pekerjaan[indeks]);
        optimasiPekerjaanRekursif(indeks + 1, waktu_tersisa - pekerjaan[indeks].first, 
                                  total_waktu_dipakai + pekerjaan[indeks].first, 
                                  jumlah_pekerjaan + 1, pekerjaan, pekerjaan_terpilih);
        pekerjaan_terpilih.pop_back(); // Backtrack
    }
}

void panggilRekursif(int K, vector<pair<int, int>>& pekerjaan) {
    vector<pair<int, int>> pekerjaan_terpilih;
    solusi_terbaik.clear();
    waktu_terbaik = 0;
    jumlah_pekerjaan_terbaik = 0;

    optimasiPekerjaanRekursif(0, K, 0, 0, pekerjaan, pekerjaan_terpilih);

    // Output hasil
    cout << "\n[Rekursif - Backtracking]\n";
    cout << "Total pekerjaan yang dapat diselesaikan: " << jumlah_pekerjaan_terbaik << endl;
    for (const auto& p : solusi_terbaik) {
        cout << "Pekerjaan ke-" << p.second << ": " << p.first << " jam\n";
    }
    cout << "Total jam: " << waktu_terbaik << " jam\n";
    cout << "Sisa jam: " << K - waktu_terbaik << " jam\n";
}

// ========================= Main Program =========================
int main() {
    int K, n;
    cout << "Masukkan batas waktu kerja dalam sehari (K jam): ";
    cin >> K;

    cout << "Masukkan jumlah pekerjaan (n): ";
    cin >> n;

    vector<pair<int, int>> pekerjaan;
    cout << "Masukkan durasi setiap pekerjaan (dalam jam):\n";
    for (int i = 0; i < n; ++i) {
        int durasi;
        cout << "Pekerjaan " << i + 1 << ": ";
        cin >> durasi;
        pekerjaan.push_back({durasi, i + 1});
    }

    // Waktu eksekusi Iteratif - Greedy
    auto start_iteratif = chrono::high_resolution_clock::now();
    optimasiPekerjaanIteratif(K, pekerjaan);
    auto end_iteratif = chrono::high_resolution_clock::now();
    double durasi_iteratif = chrono::duration<double>(end_iteratif - start_iteratif).count();
    cout << "Waktu yang digunakan untuk mengeksekusi program (Iteratif - Greedy): " 
         << durasi_iteratif << " detik\n";

    // Reset variabel global untuk Rekursif - Backtracking
    solusi_terbaik.clear();
    waktu_terbaik = 0;

    // Waktu eksekusi Rekursif - Backtracking
    auto start_rekursif = chrono::high_resolution_clock::now();
    panggilRekursif(K, pekerjaan);
    auto end_rekursif = chrono::high_resolution_clock::now();
    double durasi_rekursif = chrono::duration<double>(end_rekursif - start_rekursif).count();
    cout << "Waktu yang digunakan untuk mengeksekusi program (Rekursif - Backtracking): " 
         << durasi_rekursif << " detik\n";

    return 0;
}
