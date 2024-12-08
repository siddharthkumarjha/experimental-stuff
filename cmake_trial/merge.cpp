#include<iostream>
#include<vector>
using namespace std;
void merge(vector<int> &arr, int l, int m, int h){
        int lsize = m-l+1;
        int rsize = h-m;
        vector<int> left;
        vector<int> right;
        for(int i=l; i<=m; i++){
                left.push_back(arr[i]);
        }
        for(int j = m+1; j <= h; j++)
                right.push_back(arr[j]);
        int i=0, j=0, k=l;
        while(i<lsize && j<rsize){
                if(left[i] <= right[j]) arr[k] = left[i++];
                else arr[k] = right[j++];
                k++;
        }
        while(i<lsize) arr[k++] = left[i++];
        while(j<rsize) arr[k++] = right[j++];
}
void mergesort(vector<int> &arr, int l, int h){
        if(l >= h) return;
        int m = l + (h-l)/2;
        mergesort(arr, l, m);
        mergesort(arr, m+1, h);
        merge(arr, l, m, h);
}
int main(void){
        vector<int> arr = {3, 2, 4, 7, 15, 12, 2, 0};
        mergesort(arr, 0, 7);
        for(auto i : arr) cout << i << ' ';
        cout << endl;
}
