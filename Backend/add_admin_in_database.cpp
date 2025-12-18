#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
string HTML_Decoder(string s);
int main(){
    cout << "Content-Type: text/html\r\n\r\n";
    size_t len=atoi(getenv("CONTENT_LENGTH"));
    string data,name,mail,pass,admin_role;
    data.resize(len);
    cin.read(&data[0],len);
    data=HTML_Decoder(data);
    size_t i1=data.find("name=");
    size_t i2=i1+5;
    size_t i3=data.find("&mail=");
    name=data.substr(i2,i3-i2);
    i2=i3+6;
    i3=data.find("&pass=");
    mail=data.substr(i2,i3-i2);
    i2=i3+6;
    i3=data.find("&admin_role=");
    pass=data.substr(i2,i3-i2);
    admin_role=data.substr(i3+12,1);
    ifstream fin_admin_database;
    ofstream fout_admin_database;
    if(admin_role=="1"){
        fin_admin_database.open("C://xampp/VoteX_Private/Database/Super_admin_database.csv");
    } else if(admin_role=="2"){
        fin_admin_database.open("C://xampp/VoteX_Private/Database/Election_admin_database.csv");
    } else{
        fin_admin_database.open("C://xampp/VoteX_Private/Database/Verification_admin_database.csv");
    }
    string temp,previous_admin_id,admin_id;
    getline(fin_admin_database,temp);
    while(getline(fin_admin_database,temp));
    stringstream ss_admin_database(temp);
    getline(ss_admin_database,previous_admin_id,',');
    int int_previous_admin_id=stoi(previous_admin_id.substr(8));
    admin_id=previous_admin_id.substr(0,8)+to_string(int_previous_admin_id+1);
    fin_admin_database.close();
    if(admin_role=="1"){
        fout_admin_database.open("C://xampp/VoteX_Private/Database/Super_admin_database.csv",ios::app);
    } else if(admin_role=="2"){
        fout_admin_database.open("C://xampp/VoteX_Private/Database/Election_admin_database.csv",ios::app);
    } else{
        fout_admin_database.open("C://xampp/VoteX_Private/Database/Verification_admin_database.csv",ios::app);
    }
    fout_admin_database<<"\n"<<admin_id<<','<<pass<<','<<mail<<','<<'-'<<','<<name<<','<<'-'<<','<<'-';
    fout_admin_database.close();

    ifstream fin_admin_created("C://xampp/VoteX_Private/Templates/admin_created_Successfully.txt");
    string html="";
    while(getline(fin_admin_created,temp)){
        html+=temp;
        html+="\n";
    }
    fin_admin_created.close();
    
    ifstream previous_admin_fetch("C://xampp/VoteX_Private/Database/Last_admin_created.txt");
    getline(previous_admin_fetch,previous_admin_id);
    previous_admin_fetch.close();

    ofstream update_new_admin_creation("C://xampp/VoteX_Private/Database/Last_admin_created.txt",ios::trunc);
    update_new_admin_creation<<admin_id;
    update_new_admin_creation.close();
    
    size_t index=html.find(previous_admin_id);
    int length=previous_admin_id.length();
    html.replace(index,length,admin_id);
    ofstream fout_admin_created("C://xampp/VoteX_Private/Templates/admin_created_Successfully.txt",ios::trunc);
    fout_admin_created<<html;
    fout_admin_created.close();
    
    html.clear();
    fin_admin_created.open("C://xampp/VoteX_Private/Templates/admin_created_Successfully.txt");
    while(getline(fin_admin_created,temp)){
        html+=temp;
        html+="\n";
    }
    cout<<html;
    return 0;
}   




string HTML_Decoder(string s){
    //1. Know the string 
/*Original | Encoded      |
| -------- | ------------ |
| space    | `+` or `%20` |
| !        | `%21`        |
| "        | `%22`        |
| #        | `%23`        |
| $        | `%24`        |
| %        | `%25`        |
| &        | `%26`        |
| '        | `%27`        |
| (        | `%28`        |
| )        | `%29`        |
| *        | `%2A`        |
| +        | `%2B`        |
| ,        | `%2C`        |
| /        | `%2F`        |
| :        | `%3A`        |
| ;        | `%3B`        |
| =        | `%3D`        |
| ?        | `%3F`        |
| @        | `%40`        |
| [        | `%5B`        |
| ]        | `%5D`        |
*/
// Array contain all counts in the order
    int *count=(int*)calloc(22,sizeof(int));
    int len=s.length();
    for(int i=0;i<len;i++){
        if(s[i]=='+'){
            count[21]++;
        } else if(s[i]=='%'){
            if(s[i+1]=='2'){
                if(s[i+2]=='0'){
                    count[0]++;
                    i+=2;
                } else if(s[i+2]=='1'){
                    count[1]++;
                    i+=2;
                } else if(s[i+2]=='2'){
                    count[2]++;
                    i+=2;
                } else if(s[i+2]=='3'){
                    count[3]++;
                    i+=2;
                } else if(s[i+2]=='4'){
                    count[4]++;
                    i+=2;
                } else if(s[i+2]=='5'){
                    count[5]++;
                    i+=2;
                } else if(s[i+2]=='6'){
                    count[6]++;
                    i+=2;
                } else if(s[i+2]=='7'){
                    count[7]++;
                    i+=2;
                } else if(s[i+2]=='8'){
                    count[8]++;
                    i+=2;
                } else if(s[i+2]=='9'){
                    count[9]++;
                    i+=2;
                } else if(s[i+2]=='A'){
                    count[10]++;
                    i+=2;
                } else if(s[i+2]=='B'){
                    count[11]++;
                    i+=2;
                } else if(s[i+2]=='C'){
                    count[12]++;
                    i+=2;
                } else if(s[i+2]=='F'){
                    count[13]++;
                    i+=2;
                }
            } else if(s[i+1]=='3'){
                if(s[i+2]=='A'){
                    count[14]++;
                    i+=2;
                } else if(s[i+2]=='B'){
                    count[15]++;
                    i+=2;
                } else if(s[i+2]=='D'){
                    count[16]++;
                    i+=2;
                } else if(s[i+2]=='F'){
                    count[17]++;
                    i+=2;
                }
            } else if(s[i+1]=='4' && s[i+2]=='0'){
                count[18]++;
                i+=2;
            } else if(s[i+1]=='5'){
                if(s[i+2]=='B'){
                    count[19]++;
                    i+=2;
                } else if(s[i+2]=='D'){
                    count[20]++;
                    i+=2;
                }
            }
        }
    }
    for(int i=0;i<22;i++){
        if(count[i]==0){
            continue;
        } else if(i==0){
            // space decoder
            for(int j=0;j<count[0];j++){
                int ind=s.find("%20");
                s.replace(ind,3," ");
            }
        } else if(i==1){
            // Exclamation(!) decoder
            for(int j=0;j<count[1];j++){
                int ind=s.find("%21");
                s.replace(ind,3,"!");
            }
        } else if(i==2){
            // Double Quote decoder
            for(int j=0;j<count[2];j++){
                int ind=s.find("%22");
                s.replace(ind,3,"\"");
            }
        } else if(i==3){
            // Hash Decoder
            for(int j=0;j<count[3];j++){
                int ind=s.find("%23");
                s.replace(ind,3,"#");
            }
        } else if(i==4){
            // Dollar decoder
            for(int j=0;j<count[4];j++){
                int ind=s.find("%24");
                s.replace(ind,3,"$");
            }
        } else if(i==5){
            // Percentage decoder
            for(int j=0;j<count[5];j++){
                int ind=s.find("%25");
                s.replace(ind,3,"%");
            }
        } else if(i==6){
            // Ampersand decoder
            for(int j=0;j<count[6];j++){
                int ind=s.find("%26");
                s.replace(ind,3,"&");
            }
        } else if(i==7){
            // Single Quote decoder
            for(int j=0;j<count[7];j++){
                int ind=s.find("%27");
                s.replace(ind,3,"'");
            }
        } else if(i==8){
            // Open Parenthesis decoder
            for(int j=0;j<count[8];j++){
                int ind=s.find("%28");
                s.replace(ind,3,"(");
            }
        } else if(i==9){
            // Closed Parenthesis decoder
            for(int j=0;j<count[9];j++){
                int ind=s.find("%29");
                s.replace(ind,3,")");
            }
        } else if(i==10){
            // Star decoder
            for(int j=0;j<count[10];j++){
                int ind=s.find("%2A");
                s.replace(ind,3,"*");
            }
        } else if(i==11){
            // Plus decoder
            for(int j=0;j<count[11];j++){
                int ind=s.find("%2B");
                s.replace(ind,3,"+");
            }
        } else if(i==12){
            // Comma decoder
            for(int j=0;j<count[12];j++){
                int ind=s.find("%2C");
                s.replace(ind,3,",");
            }
        } else if(i==13){
            // Front Slash decoder
            for(int j=0;j<count[13];j++){
                int ind=s.find("%2F");
                s.replace(ind,3,"/");
            }
        } else if(i==14){
            // Colon decoder
            for(int j=0;j<count[14];j++){
                int ind=s.find("%3A");
                s.replace(ind,3,":");
            }
        } else if(i==15){
            // Semicolon decoder
            for(int j=0;j<count[15];j++){
                int ind=s.find("%3B");
                s.replace(ind,3,";");
            }
        } else if(i==16){
            // Equal to decoder
            for(int j=0;j<count[16];j++){
                int ind=s.find("%3D");
                s.replace(ind,3,"=");
            }
        } else if(i==17){
            // Question mark decoder
            for(int j=0;j<count[17];j++){
                int ind=s.find("%3F");
                s.replace(ind,3,"?");
            }
        } else if(i==18){
            // at the rate decoder
            for(int j=0;j<count[18];j++){
                int ind=s.find("%40");
                s.replace(ind,3,"@");
            }
        } else if(i==19){
            // Open Square Bracket decoder
            for(int j=0;j<count[19];j++){
                int ind=s.find("%5B");
                s.replace(ind,3,"[");
            }
        } else if(i==20){
            // Closed Square bracket decoder
            for(int j=0;j<count[20];j++){
                int ind=s.find("%5D");
                s.replace(ind,3,"]");
            }
        } else if(i==21){
            // Space decoder
            for(int j=0;j<count[21];j++){
                int ind=s.find("+");
                s.replace(ind,1," ");
            }
        }
    }
    free(count);
    return s;
}