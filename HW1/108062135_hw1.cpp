#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <functional>
using namespace std;

int random_partition(vector<int>& A, int l, int r){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distr(l, r);
    int random = distr(gen);
    int pivot = A[random];
    swap(A[r], A[random]);
    int i = l-1;
    for(int j = l; j < r; j++){
        if(A[j]<= pivot){
            i++;
            swap(A[i],A[j]);
        }
    }
    swap(A[i+1], A[r]);
    return i+1;
}
int random_select(vector<int>& A, int l, int r, int k){
    if(l == r)
        return A[l];
    int pos = random_partition(A, l, r);
    int i = pos - l + 1;
    if (i == k)
        return A[pos];
    else if ( k < i )
        return random_select(A, l, pos-1, k);
    else return random_select(A, pos+1, r, k-i);
}
void sort(vector<int>& arr, int start, int end){
    //use insertion sort to sort array
    for(int i = start +1; i < end; i++){
        int j = i-1;
        int key = arr[i];
        while(j >= start && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}
int select(vector<int> A, int k, int G){
    if(A.size() <= G){
        sort(A,0, A.size());
        return A[k-1];
    }
    else{
        int size = A.size();
        vector<int> median;
        for(int i = 0; i< size; i+=G){
            vector<int> tmp;
            for(int cnt = 0; cnt < G; cnt++){
                if(i + cnt < size)
                    tmp.push_back(A[i+cnt]);
                else break;
            }
            sort(tmp, 0, tmp.size());
            median.push_back(tmp[tmp.size()/2]);
        }
        int m = select(median, median.size()/2, G);
        bool isfirst = true;
        vector<int> X, Y;
        for (int i =0 ; i < size; i++){
            if(A[i] < m){
                X.push_back(A[i]);
            }
            else if (A[i] > m){
                Y.push_back(A[i]);
            }
            else{
                if(isfirst)
                    isfirst = false;
                else
                    X.push_back(A[i]);
            }
        }    
        if(k == X.size()+1) return m;
        else if (k<= X.size())
            return select(X, k, G);
        else return select(Y, k-(X.size()+1), G);
    }

}
vector<int> genVec(int N){
	random_device rd;
    vector<int> res;
    default_random_engine gen = default_random_engine(time(NULL));
    uniform_int_distribution<int> dis(1,20000000);
    auto randfun = bind(dis, gen);
    for(int i=0; i<N; i++) {
        res.push_back(randfun());
    }
    return res;
}
int main(){
    int N, K, G;
    cin >> N >> K >> G;
    vector<int> arr = genVec(N) ;
    if(G == -1){
        cout << random_select(arr, 0, N-1, K)<< endl;
    }
    else{
        cout << select(arr, K, G) << endl;
    } 
    // vector<int> arr2 = arr;
    // vector<int> arr3 = arr;
    // vector<int> arr4 = arr;
    // vector<int> arr5 = arr;
    // float timerand = 0 , time3 = 0, time5 = 0 , time7 = 0 , time9 = 0 ;
    // clock_t begin_time, end_time;
    // for (int i = 0 ; i < 20 ; i++){
    //     cout << "ROUND : " << i+1 <<endl;;
    //     cout << "Random :";
    //     begin_time = clock();
    //     cout << random_select(arr, 0, N-1, K) << "\n";
    //     cout << "Start Time : " << begin_time << "\t";
    //     end_time = clock();
    //     cout << "End Time : " << end_time<< "\t";
    //     cout << "Time spent : "<< (float)(end_time- begin_time)/CLOCKS_PER_SEC << endl << endl;
    //     timerand += (end_time- begin_time);
    //     cout << "G = 3 :" ;
    //     begin_time = clock();
    //     cout << select(arr2, K, 3)<< "\n";
    //     cout << "Start Time : " << begin_time << "\t";
    //     end_time = clock();
    //     cout << "End Time : " << end_time<< "\t";
    //     cout << "Time spent : "<< (float)(end_time- begin_time)/CLOCKS_PER_SEC << endl << endl;
    //     time3+= (end_time- begin_time);
    //     cout << "G = 5 :" ;
    //     begin_time = clock();
    //     cout << select(arr3, K, 5)<< "\n";
    //     cout << "Start Time : " << begin_time << "\t";
    //     end_time = clock();
    //     cout << "End Time : " << end_time<< "\t";
    //     cout << "Time spent : "<< (float)(end_time- begin_time)/CLOCKS_PER_SEC << endl << endl;
    //     time5 += (end_time- begin_time);
    //     cout << "G = 7 :";
    //     begin_time = clock();
    //     cout << select(arr4, K, 7)<< "\n";
    //     cout << "Start Time : " << begin_time << "\t";
    //     end_time = clock();
    //     cout << "End Time : " << end_time<< "\t";
    //     cout << "Time spent : "<< (float)(end_time- begin_time)/CLOCKS_PER_SEC << endl << endl;
    //     time7 += (end_time- begin_time);
    //     cout << "G = 9 :";
    //     begin_time = clock();
    //     cout << select(arr5, K, 9)<< "\n";
    //     cout << "Start Time : " << begin_time << "\t";
    //     end_time = clock();
    //     cout << "End Time : " << end_time<< "\t";
    //     cout << "Time spent : "<< (float)(end_time- begin_time)/CLOCKS_PER_SEC << endl << endl;
    //     time9 += (end_time- begin_time);
    // }
    //     cout << timerand << endl << endl;
    //     cout << "Average time for Randomized-select is : " <<(float) timerand/(20*CLOCKS_PER_SEC) << " seconds." << endl;
    //     cout << "Average time for Groups 3 is : " <<(float)time3/(20*CLOCKS_PER_SEC) << " seconds." << endl;
    //     cout << "Average time for Groups 5 is : " <<(float) time5/(20*CLOCKS_PER_SEC)  << " seconds." << endl;
    //     cout << "Average time for Groups 7 is : " << (float)time7/(20*CLOCKS_PER_SEC)  << " seconds." << endl;
    //     cout << "Average time for Groups 9 is : " <<(float) time9/(20*CLOCKS_PER_SEC)  << " seconds." << endl;
    
    
}