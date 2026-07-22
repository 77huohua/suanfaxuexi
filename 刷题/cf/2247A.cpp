#include<iostream>
using namespace std;

int main(){
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int sum = 0;
        for (int i = 1, temp; i <= n;i++){
            cin >> temp;
            sum += temp;
        }
        if(abs(sum)%4){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }
}