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
    ifstream fin("Institute_Sessions.txt");
    getline(fin,cookief);
    if(cookie!=cookief){
        cout << "Status: 302 Found\r\n";
        cout << "Location: /VoteX/institute_auth_failed.html\r\n\r\n";
        return 0;
    }
    cout << "Content-Type: text/html; charset=UTF-8\r\n";
    cout << "Set-Cookie: SESSION_ID=" << cookief << "; Path=/; HttpOnly\r\n";
    cout << "\r\n";
    string addadminhtmlpge1="",addadminhtmlpge2="",temp;
    ifstream finaddadminhtmlpage1("add_admin_html_page_1.txt");
    while(getline(finaddadminhtmlpage1,temp)){
        addadminhtmlpge1+=temp;
        addadminhtmlpge1+="\n";
    }
    finaddadminhtmlpage1.close();
    ifstream finaddadminhtmlpage2("add_admin_html_page_2.txt");
    while(getline(finaddadminhtmlpage2,temp)){
        addadminhtmlpge2+=temp;
        addadminhtmlpge2+="\n";
        temp.clear();
    }
    ifstream findynamicpin("Institute_login_data.txt");
    for(int i=0;i<5;i++){
        getline(findynamicpin,temp);
    }
    if(!temp.empty()&&temp.back()=="/r") temp.pop_back();
    string finalprint=addadminhtmlpge1+temp+"\n"+addadminhtmlpge2;
    cout<<finalprint;
    return 0;
}