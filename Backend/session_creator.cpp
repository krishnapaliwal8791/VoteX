#include<iostream>
#include<string>
#include<random>
using namespace std;
string session_creator();
int main(){
    cout<<session_creator();
    return 0;
}
string session_creator(){
    int min = 0;   // minimum
    int max = 62;   // maximum
    random_device rd;          // 1️⃣ seed
    mt19937 gen(rd());         // 2️⃣ engine
    uniform_int_distribution<int> dist(min, max); // 3️⃣ range
    string session_origin="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string session;
    for(int i=0;i<32;i++){
        int randomNumber = dist(gen);   //  generate number
        session+=session_origin[randomNumber];
    }
    return session;
}