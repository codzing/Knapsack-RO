#include <iostream>
using namespace std;
const int max_var = 100;

//fungsi mengcopy array2 ke array1
void copy(double val1[], double val2[], int iter){
    for(int i=0; i<iter; i++){
        val1[i] = val2[i];
    }
}

//Buat Sorting
void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}
void swap(double &a, double &b){
    double temp = a;
    a = b;
    b = temp;
}
void maksimumsort(int index[],int weight[],double cost[], int n){
    for(int i = 1; i < n; ++i){
        
        for(int j = i; j>0; j--){
            if(cost[j]/weight[j] > cost[j-1]/weight[j-1]){
                swap(index[j],index[j-1]);
            }
        }
    }
}   


//Knapsack Algorithm
void knapsack(int index[], int sol[], int weight[], int capacty, int iter){
    int d[iter];
    for(int i = 0; i<iter; i++){
        d[index[i]] = capacty/weight[index[i]];
    }
    for(int i = 0; i<iter ; i++){
        sol[index[i]] = (d[index[i]])<(capacty/weight[index[i]])?(d[index[i]]):(capacty/weight[index[i]]);
        capacty = capacty-sol[index[i]]*weight[index[i]];
        cout << "\ncapacity : " << capacty;
        if(capacty == 0){
            break;
        }
    }
}

//Fungsi menghitung nilai total
double totVal(double val[],int sol[],int iter){
double total=0;
    for(int i = 0; i<iter; i++){
        total+=val[i]*sol[i];
    }
return total;
}

int main(){

    double objfunc[max_var], temp[max_var], value;
    int totvar, constraint[max_var], maxCap,solution[max_var], index[max_var];
    index[0] = 0;
    cout << "Masukkan jumlah variabel : ";
    cin >> totvar;

    for(int i = 0; i<totvar; i++){
        cout << "Masukkan koef tujuan x" << (i+1) << " : ";
        cin >> objfunc[i];
        solution[i] = 0;
        if(i > 0){
        index[i] = index[i-1]+1;
        }
    }
    cout << endl;
    
    copy(temp, objfunc, totvar);
    cout << endl;
    cout << "Input batasan : \n";

    for(int i=0; i<totvar; i++){
        cout << "Masukkan koef batasan x" << (i+1) << " : ";
        cin >> constraint[i];
    }
    cout << "\ninput Kapasitas maks : ";
    cin >> maxCap;

    cout << "Fungsi tujuannya adalah : \n";

    for(int i = 0; i<totvar; i++){
        cout << objfunc[i] << "x" << (i+1) << " ";
        if(i<totvar-1){
            cout << " + ";
        }
    }
    
    cout << "\nDengan batasan :\n";
    for(int i = 0; i<totvar; i++){
        cout << constraint[i] << "x" << (i+1) << " ";
        if(i < totvar-1){
            cout << " + ";
        }
    }
    cout << " <= " << maxCap;
   
    maksimumsort(index, constraint, objfunc, totvar);
    cout << endl;
    
    knapsack(index, solution, constraint, maxCap, totvar);
    value = totVal(objfunc, solution, totvar);

    cout << "\nsolusinya :\n";
    cout << "{";
    for(int i = 0; i<totvar; i++){
        cout << solution[i];
        if(i < totvar-1){
            cout << ", ";
        }
    }
    cout << "}";

    cout << "\ndengan nilai total = " << value;
    for(int i=0;i<totvar;i++){
        cout << index[i];
    }

return 0;
}
