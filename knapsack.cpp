#include <iostream>

using namespace std;

const int MAX_N = 100; // Maksimal jumlah jenis barang
const int MAX_W = 1000; // Maksimal kapasitas knapsack

int knapsack(int W, int n, int w[], double v[], int m[], int selected[]) {
    //inisialisasi total nilai brang dengan 0
    int dp[MAX_N + 1][MAX_W + 1] = {0};

    // Mengisi tabel dp
    for (int i = 1; i <= n; ++i) {
        for (int j = W; j >= 0; --j) {
            for (int k = 0; k <= m[i-1] && k * w[i-1] <= j; ++k) {
                if (dp[i][j] < dp[i-1][j - k * w[i-1]] + k * v[i-1]) {
                    dp[i][j] = dp[i-1][j - k * w[i-1]] + k * v[i-1];
                }
            }
        }
    }

    // Menelusuri kembali untuk menemukan barang yang dipilih
    int remainingCapacity = W;
    for (int i = n; i > 0; --i) {
        for (int k = 0; k <= m[i-1]; ++k) {
            if (remainingCapacity >= k * w[i-1] && dp[i][remainingCapacity] == dp[i-1][remainingCapacity - k * w[i-1]] + k * v[i-1]) {
                selected[i-1] = k;
                remainingCapacity -= k * w[i-1];
                break;
            }
        }
    }

    return dp[n][W];
}

int maksimum(int m[],int var){
    int maks=0;
    for(int i=0;i<var;i++){
        maks=maks>m[i]?maks:m[i];
    }

    return maks;
}

int main() {
    // Contoh data
    int w[MAX_N]; // Berat barang
    double v[MAX_N]; // Nilai barang
    int m[MAX_N]; // Kapasitas maksimal barang
    int W; // Kapasitas knapsack
    int n; // Jumlah jenis barang

    cout << "Masukkan jumlah variabel : ";
    cin >> n;

    //inpput fungsi tujuan
    for(int i=0;i<n;i++){
        cout << "Masukkan Nilai barang ke -" << (i+1) << " : ";
        cin >> v[i];
    }
    cout << endl;

    //tampilan fungsi tujuan
    cout << "Fungsi tujuan : \n";
    for(int i=0;i<n;i++){
        cout << v[i] << "x" << (i+1);
        if(i<n-1){
            cout << " + ";
        }
    }
    cout << endl;

    //input fungsi batasan pertama
    cout << "Masukkan berat barang : \n";
    for(int i=0;i<n;i++){
        cout << "Masukkan berat barang ke -" << (i+1) << " : ";
        cin >> w[i];
    }
    cout << endl;

    cout << "Masukkan kapasitas maksimum : ";
    cin >> W;
    cout << endl;

    //tampilan fungsi batasan pertama
    cout << "Fungsi batassan : \n";
    for(int i=0;i<n;i++){
        cout << w[i] << "x" << (i+1);
        if(i<n-1){
            cout << " + ";
        }
    }
    cout << " <= " << W;
    cout << endl;

    //input fungsi batasan ke i+1
    cout << "Masukkan ketersediaan barang (Jika infty = -1):\n";
    for(int i=0;i<n;i++){
        cout << "Masukkan ketersediaan barang ke -" << (i+1) << " : ";
        cin >> m[i];
    }
    cout << endl;

    //mendefinisikan ketersediaan barang yang tidak terbatas
    for(int i=0;i<n;i++){
        if(m[i]==-1){
            m[i]=maksimum(m,n)+1;
        }
    }

    int selected[MAX_N] = {0}; // Array untuk melacak barang yang dipilih

    int maxValue = knapsack(W, n, w, v, m, selected);

    cout << "Nilai maksimum yang dapat diperoleh: " << maxValue << endl;
    cout << "Barang yang dibawa: " << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Barang ke-" << (i + 1) << ": " << selected[i] << " buah" << endl;
    }

    return 0;
}
