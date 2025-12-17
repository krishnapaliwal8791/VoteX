#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
using namespace std;
int main(){
    char*cook=getenv("HTTP_COOKIE");
    if(!cook){
        cout << "Status: 302 Found\r\n";
        cout << "Location: /VoteX/institute_auth_failed.html\r\n\r\n";
        return 0;
    }
    string cooki=cook;
    size_t i1=cooki.find("SESSION_ID=");
    if(i1>=cooki.size()){
        cout << "Status: 302 Found\r\n";
        cout << "Location: /VoteX/institute_auth_failed.html\r\n\r\n";
        return 0;
    }
    size_t i2=i1+11;
    string cookie=cooki.substr(i2,32),cookief;
    ifstream fin("C://xampp/VoteX_Private/Database/Institute_Sessions.txt");
    getline(fin,cookief);
    if(cookie!=cookief){
        cout << "Status: 302 Found\r\n";
        cout << "Location: /VoteX/institute_auth_failed.html\r\n\r\n";
        return 0;
    }
    cout << "Content-Type: text/html; charset=UTF-8\r\n";
    cout << "Set-Cookie: SESSION_ID=" << cookief << "; Path=/; HttpOnly\r\n";
    cout << "\r\n";
    ifstream fin_add_admin_page("C://xampp/VoteX_Private/Templates/add_admin_details_page.txt");
    string html,temp;
    while(getline(fin_add_admin_page,temp)){
        html+=temp;
        html+="\n";
        temp.clear();
    }
    fin_add_admin_page.close();
    cout<<html;
    return 0;                      
}