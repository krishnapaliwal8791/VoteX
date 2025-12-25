#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<sstream>
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
    if(i1==string::npos){
        cout << "Status: 302 Found\r\n";
        cout << "Location: /VoteX/institute_auth_failed.html\r\n\r\n";
        return 0;
    }
    size_t i2=i1+11;
    string cookie=cooki.substr(i2,32),cookief;
    ifstream fin("C://xampp/VoteX_Private/Database/Institute_Sessions.txt");
    getline(fin,cookief);
    if(cookief!=cookie){
        cout << "Status: 302 Found\r\n";
        cout << "Location: /VoteX/institute_auth_failed.html\r\n\r\n";
        return 0;
    }
    cout << "Content-Type: text/html; charset=UTF-8\r\n";
    vector<string> SA_name,SA_ID,SA_mail,SA_phone;
    vector<string> VA_name,VA_ID,VA_mail,VA_phone;
    vector<string> EA_name,EA_ID,EA_mail,EA_phone;
    ifstream fin_SA("C://xampp/VoteX_Private/Database/Super_admin_database.csv");
    ifstream fin_EA("C://xampp/VoteX_Private/Database/Election_admin_database.csv");
    ifstream fin_VA("C://xampp/VoteX_Private/Database/Verification_admin_database.csv");
    string dataf,temp;
    getline(fin_SA,dataf);
    getline(fin_SA,dataf);
    while(getline(fin_SA,dataf)){
        stringstream ss_SA(dataf);
        getline(ss_SA,temp,',');
        SA_ID.push_back(temp);
        getline(ss_SA,temp,',');
        getline(ss_SA,temp,',');
        SA_mail.push_back(temp);
        getline(ss_SA,temp,',');
        SA_phone.push_back(temp);
        getline(ss_SA,temp,',');
        SA_name.push_back(temp);
    }
    // <tr><td>MITS_SA_1</td><td>Rahul Sharma</td><td>rahul@mits.ac.in</td><td>9876543210</td></tr>
    string SA_final="";
    for(int i=0;i<SA_ID.size();i++){
        SA_final+="\n";
        SA_final+="<tr><td>";
        SA_final+=SA_ID[i];
        SA_final+="</td><td>";
        SA_final+=SA_name[i];
        SA_final+="</td><td>";
        SA_final+=SA_mail[i];
        SA_final+="</td><td>";
        SA_final+=SA_phone[i];
        SA_final+="</td></tr>";
    }

    getline(fin_EA,dataf);
    getline(fin_EA,dataf);
    while(getline(fin_EA,dataf)){
        stringstream ss_EA(dataf);
        getline(ss_EA,temp,',');
        EA_ID.push_back(temp);
        getline(ss_EA,temp,',');
        getline(ss_EA,temp,',');
        EA_mail.push_back(temp);
        getline(ss_EA,temp,',');
        EA_phone.push_back(temp);
        getline(ss_EA,temp,',');
        EA_name.push_back(temp);
    }

    string EA_final="";
    for(int i=0;i<EA_ID.size();i++){
        EA_final+="\n";
        EA_final+="<tr><td>";
        EA_final+=EA_ID[i];
        EA_final+="</td><td>";
        EA_final+=EA_name[i];
        EA_final+="</td><td>";
        EA_final+=EA_mail[i];
        EA_final+="</td><td>";
        EA_final+=EA_phone[i];
        EA_final+="</td></tr>";
    }


    getline(fin_VA,dataf);
    getline(fin_VA,dataf);
    while(getline(fin_VA,dataf)){
        stringstream ss_VA(dataf);
        getline(ss_VA,temp,',');
        VA_ID.push_back(temp);
        getline(ss_VA,temp,',');
        getline(ss_VA,temp,',');
        VA_mail.push_back(temp);
        getline(ss_VA,temp,',');
        VA_phone.push_back(temp);
        getline(ss_VA,temp,',');
        VA_name.push_back(temp);
    }

    string VA_final="";
    for(int i=0;i<VA_ID.size();i++){
        VA_final+="\n";
        VA_final+="<tr><td>";
        VA_final+=VA_ID[i];
        VA_final+="</td><td>";
        VA_final+=VA_name[i];
        VA_final+="</td><td>";
        VA_final+=VA_mail[i];
        VA_final+="</td><td>";
        VA_final+=VA_phone[i];
        VA_final+="</td></tr>";
    }

    cout<<R"VoteX(
    <!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>VoteX · Admin List</title>

<style>
*{
    margin:0;
    padding:0;
    box-sizing:border-box;
    font-family:Inter, system-ui, sans-serif;
}

body{
    min-height:100vh;
    background:#020617;
    color:#e5e7eb;
}

/* ================= TOPBAR ================= */
.topbar{
    height:64px;
    display:flex;
    justify-content:space-between;
    align-items:center;
    padding:0 28px;
    border-bottom:1px solid #1e293b;
}

.logo{ color:#38bdf8;font-weight:600;font-size:18px; }
.logout-btn{ color:#ef4444;text-decoration:none; }

/* ================= LAYOUT ================= */
.layout{ display:flex; }

/* ================= SIDEBAR ================= */
.sidebar{
    width:230px;
    padding:20px;
    border-right:1px solid #1e293b;
}
.sidebar li{
    list-style:none;
    padding:12px;
    border-radius:8px;
    margin-bottom:6px;
    color:#cbd5e1;
}
.sidebar li.active{
    background:#2563eb;
    color:#020617;
    font-weight:600;
}

/* ================= CONTENT ================= */
.content{
    flex:1;
    padding:32px;
}

h1{ font-size:28px;margin-bottom:6px; }
.subtitle{ color:#94a3b8;margin-bottom:24px; }

/* ================= STATS ================= */
.stats{
    display:grid;
    grid-template-columns:repeat(3,1fr);
    gap:20px;
    margin-bottom:32px;
}

.stat-card{
    padding:20px;
    border-radius:14px;
    background:#020617;
    border:1px solid #1e293b;
}
.stat-card h2{ font-size:26px;margin-bottom:4px; }
.stat-card p{ color:#94a3b8;font-size:13px; }

.super-c{ border-left:4px solid #3b82f6; }
.elec-c{ border-left:4px solid #22c55e; }
.veri-c{ border-left:4px solid #facc15; }

/* ================= TABLE ================= */
.section{
    margin-bottom:36px;
}

.section h2{
    margin-bottom:12px;
    font-size:18px;
}

table{
    width:100%;
    border-collapse:collapse;
    background:#020617;
    border:1px solid #1e293b;
    border-radius:12px;
    overflow:hidden;
}

th,td{
    padding:14px 16px;
    text-align:left;
    border-bottom:1px solid #1e293b;
}

th{ color:#38bdf8;font-size:13px; }
td{ font-size:14px; }

tr:hover{ background:#020b2d; }
</style>
</head>

<body>

<header class="topbar">
    <div class="logo">VoteX · Institute Panel</div>
    <a href="/VoteX/index.html" class="logout-btn">Logout</a>
</header>

<div class="layout">

<aside class="sidebar">
    <ul>
        <li>Dashboard</li>
        <li>Add Admin</li>
        <li>Remove Admin</li>
        <li class="active">Admin List</li>
    </ul>
</aside>

<main class="content">

<h1>Administrators</h1>
<p class="subtitle">Overview of all registered admins</p>

<!-- STATS -->
<div class="stats">
    <div class="stat-card super-c">
        <h2>)VoteX"<<SA_ID.size()<<R"VoteX(
        </h2>
        <p>Super Admins</p>
    </div>
    <div class="stat-card elec-c">
        <h2>)VoteX"<<EA_ID.size()<<R"VoteX(
        </h2>
        <p>Election Admins</p>
    </div>
    <div class="stat-card veri-c">
        <h2>)VoteX"<<VA_ID.size()<<R"VoteX(
        </h2>
        <p>Verification Admins</p>
    </div>
</div>

<!-- SUPER ADMINS -->
<div class="section">
<h2>Super Administrators</h2>
<table>
<tr><th>ID</th><th>Name</th><th>Email</th><th>Phone</th></tr>)VoteX"<<SA_final<<R"VoteX(
</table>
</div>

<!-- ELECTION ADMINS -->
<div class="section">
<h2>Election Administrators</h2>
<table>
<tr><th>ID</th><th>Name</th><th>Email</th><th>Phone</th></tr>)VoteX"<<EA_final<<R"VoteX(
</table>
</div>

<!-- VERIFICATION ADMINS -->
<div class="section">
<h2>Verification Administrators</h2>
<table>
<tr><th>ID</th><th>Name</th><th>Email</th><th>Phone</th></tr>)VoteX"<<VA_final<<R"VoteX(
</table>
</div>

</main>
</div>
</body>
</html>)VoteX";
return 0;
}