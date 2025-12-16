#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;
string HTML_Decoder(string s);
int main(){
    // cout<<"Content type: text/html\n\n"; (Dont add this line because we are using direct server redirection to the success page not the browser redirection )
    int len = atoi(getenv("CONTENT_LENGTH"));
    string data;
    data.resize(len);
    cin.read(&data[0],len);
    data=HTML_Decoder(data);
    string fn,mn,ln,mail,pass,enroll,dep,br,yr,ph,sq,sa;
    int i1=data.find("fname=");
    int i2=i1+6;
    int i3=data.find("&mname=");
    fn=data.substr(i2,i3-i2);
    i1=i3;
    i2=i3+7;
    i3=data.find("&lname=");
    mn=data.substr(i2,i3-i2);
    i1=i3;
    i2=i3+7;
    i3=data.find("&email=");
    ln=data.substr(i2,i3-i2);
    i1=i3;
    i2=i3+7;
    i3=data.find("&pass=");
    mail=data.substr(i2,i3-i2);
    i1=i3;
    i2=i3+6;
    i3=data.find("&enroll=");
    pass=data.substr(i2,i3-i2);
    i1=i3;
    i2=i3+8;
    i3=data.find("&dep=");
    enroll=data.substr(i2,i3-i2);
    i1=i3;
    i2=i3+5;
    i3=data.find("&br=");
    dep=data.substr(i2,i3-i2);
    i1=i3;
    i2=i3+4;
    i3=data.find("&year=");
    br=data.substr(i2,i3-i2);
    i1=i3;
    i2=i3+6;
    i3=data.find("&phone=");
    yr=data.substr(i2,i3-i2);
    i1=i3;
    i2=i3+7;
    i3=data.find("&security_q=");
    ph=data.substr(i2,i3-i2);
    i1=i3;
    i2=i3+12;
    i3=data.find("&security_a=");
    sq=data.substr(i2,i3-i2);
    i1=i3;
    i2=i3+12;
    i3=len;
    sa=data.substr(i2,i3-i2);
    // We parsed the data Now we are writting in the file
    ofstream fout("C://xampp/VoteX_Private/Database/voter_registered_verification_remaining.txt",ios::app);
    // string fn,mn,ln,mail,pass,enroll,dep,br,yr,ph,sq,sa;
    fout<<fn<<"|"<<mn<<"|"<<ln<<"|"<<mail<<"|"<<pass<<"|"<<enroll<<"|"<<dep<<"|"<<br<<"|"<<yr<<"|"<<ph<<"|"<<sq<<"|"<<sa<<"|\n";
    fout.close();
    cout << "Status: 303 See Other\r\n";
    cout << "Location: /VoteX/registration_success.html\r\n\r\n";
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