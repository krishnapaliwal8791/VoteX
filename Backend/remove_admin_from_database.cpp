#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include<vector>
using namespace std;
int main()
{
    cout << "Content-Type: text/html; charset=UTF-8\r\n\r\n";
    size_t len = atoi(getenv("CONTENT_LENGTH"));
    string data, position, id;
    data.resize(len);
    cin.read(&data[0], len);
    size_t i1 = data.find("admin_type=");
    size_t i2 = i1 + 11;
    size_t i3 = data.find("&admin_id=");
    position = data.substr(i2, i3 - i2);
    id = data.substr(i3 + 10, len);
    ifstream fin_admin_database;
    if (position == "1")
    {
        fin_admin_database.open("C://xampp/VoteX_Private/Database/Super_admin_database.csv");
    }
    else if (position == "2")
    {
        fin_admin_database.open("C://xampp/VoteX_Private/Database/Election_admin_database.csv");
    }
    else
    {
        fin_admin_database.open("C://xampp/VoteX_Private/Database/Verification_admin_database.csv");
    }
    string firstline,secondline,line,idf;
    vector<string> database;
    int lineno=-1,i=-1;
    getline(fin_admin_database,firstline);
    getline(fin_admin_database,secondline);
    while(getline(fin_admin_database,line)){
        i++;
        stringstream ssline(line);
        getline(ssline,idf,',');
        if(idf==id) lineno=i;
        database.push_back(line);
    }
    if(lineno==-1){
        cout << R"VoteX(
        <!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>VoteX · Data Not Found</title>

<style>
/* ================= BASE ================= */
*{
    margin:0;
    padding:0;
    box-sizing:border-box;
    font-family:Inter, system-ui, -apple-system, Segoe UI, Roboto, Arial, sans-serif;
}

body{
    min-height:100vh;
    display:flex;
    align-items:center;
    justify-content:center;
    color:#e5e7eb;
    background:
        radial-gradient(900px 400px at 15% 10%, #0b1220 0%, transparent 60%),
        radial-gradient(700px 300px at 85% 30%, #0a1733 0%, transparent 55%),
        linear-gradient(180deg, #020617 0%, #020617 100%);
}

/* ================= CARD ================= */
.error-card{
    width:480px;
    padding:36px;
    border-radius:18px;
    text-align:center;
    background:
        linear-gradient(180deg,rgba(148,163,184,0.06),rgba(2,6,23,0)),
        #020617;
    border:1px solid rgba(239,68,68,0.35);
    box-shadow:
        0 0 0 1px rgba(239,68,68,0.08),
        0 25px 50px rgba(0,0,0,0.55);
}

/* ================= CONTENT ================= */
.icon{
    font-size:42px;
    margin-bottom:16px;
    color:#ef4444;
}

h1{
    font-size:24px;
    margin-bottom:10px;
}

p{
    font-size:14px;
    color:#94a3b8;
    margin-bottom:28px;
    line-height:1.6;
}

/* ================= BUTTONS ================= */
.actions{
    display:flex;
    gap:14px;
}

.actions a{
    flex:1;
    padding:12px;
    border-radius:12px;
    text-decoration:none;
    font-size:14px;
    font-weight:600;
    text-align:center;
}

.retry{
    background:linear-gradient(135deg,#0ea5e9,#2563eb);
    color:#020617;
}

.dashboard{
    background:linear-gradient(135deg,#475569,#334155);
    color:#e5e7eb;
}

.actions a:hover{
    opacity:0.95;
}
</style>
</head>

<body>

<div class="error-card">
    <div class="icon">⚠️</div>

    <h1>Data Not Found</h1>

    <p>
        The information you entered does not match any record in our database.<br>
        Please verify the admin role and ID, then try again.
    </p>

    <div class="actions">
        <a href="/VoteX/index.html" class="retry">Home</a>
    </div>
</div>

</body>
</html>
)VoteX";
        return 0;
    }
    ofstream fout_admin_database;
    if (position == "1")
    {
        fout_admin_database.open("C://xampp/VoteX_Private/Database/Super_admin_database.csv",ios::trunc);
    }
    else if (position == "2")
    {
        fout_admin_database.open("C://xampp/VoteX_Private/Database/Election_admin_database.csv",ios::trunc);
    }
    else
    {
        fout_admin_database.open("C://xampp/VoteX_Private/Database/Verification_admin_database.csv",ios::trunc);
    }
    fout_admin_database<<firstline<<"\n"<<secondline;
    for(int j=0;j<database.size();j++){
        if(lineno==j) continue;
        fout_admin_database<<"\n"<<database[j];
    }
    fout_admin_database.close();
    cout<<R"VoteX(<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>VoteX · Admin Deleted</title>

<style>
/* ================= BASE ================= */
*{
    margin:0;
    padding:0;
    box-sizing:border-box;
    font-family:Inter, system-ui, -apple-system, Segoe UI, Roboto, Arial, sans-serif;
}

body{
    min-height:100vh;
    color:#e5e7eb;
    background:
        radial-gradient(900px 400px at 15% 10%, #0b1220 0%, transparent 60%),
        radial-gradient(700px 300px at 85% 30%, #0a1733 0%, transparent 55%),
        linear-gradient(180deg, #020617 0%, #020617 100%);
}

/* ================= TOPBAR ================= */
.topbar{
    height:64px;
    display:flex;
    align-items:center;
    justify-content:space-between;
    padding:0 28px;
    border-bottom:1px solid rgba(148,163,184,0.12);
    background:linear-gradient(180deg,#020617,#020617);
}

.logo{
    font-size:18px;
    font-weight:600;
    color:#38bdf8;
}

.admin-info{
    display:flex;
    gap:16px;
    align-items:center;
    font-size:14px;
}

.logout-btn{
    color:#ef4444;
    text-decoration:none;
}

/* ================= LAYOUT ================= */
.layout{
    display:flex;
    min-height:calc(100vh - 64px);
}

/* ================= SIDEBAR ================= */
.sidebar{
    width:240px;
    padding:20px;
    border-right:1px solid rgba(148,163,184,0.12);
    background:linear-gradient(180deg,#020617,#020617);
}

.sidebar ul{
    list-style:none;
}

.sidebar li{
    padding:12px 14px;
    margin-bottom:6px;
    border-radius:8px;
    font-size:14px;
    color:#cbd5f5;
}

.sidebar li.active{
    background:linear-gradient(135deg,#0ea5e9,#2563eb);
    color:#020617;
    font-weight:600;
}

/* ================= CONTENT ================= */
.content{
    flex:1;
    padding:36px;
}

/* ================= SUCCESS CARD ================= */
.success-card{
    max-width:520px;
    padding:28px;
    border-radius:18px;
    background:
        linear-gradient(180deg,rgba(34,197,94,0.08),rgba(2,6,23,0)),
        #020617;
    border:1px solid rgba(34,197,94,0.35);
    box-shadow:
        0 0 0 1px rgba(34,197,94,0.08),
        0 24px 50px rgba(0,0,0,0.55);
}

.success-title{
    font-size:22px;
    font-weight:700;
    color:#22c55e;
    margin-bottom:10px;
}

.success-text{
    font-size:14px;
    color:#94a3b8;
    margin-bottom:24px;
    line-height:1.6;
}

.success-actions{
    display:flex;
    gap:14px;
}

.success-actions a{
    flex:1;
    text-align:center;
    padding:12px;
    border-radius:10px;
    font-size:14px;
    font-weight:600;
    text-decoration:none;
}

.btn-primary{
    color:#020617;
    background:linear-gradient(135deg,#0ea5e9,#2563eb);
}

.btn-secondary{
    color:#e5e7eb;
    border:1px solid rgba(148,163,184,0.25);
}
</style>
</head>

<body>

<header class="topbar">
    <div class="logo">VoteX · Institute Panel</div>
    <div class="admin-info">
        <span>Institute Authority</span>
        <a href="/VoteX/index.html" class="logout-btn">Logout</a>
    </div>
</header>

<div class="layout">

    <!-- Sidebar -->
    <aside class="sidebar">
        <ul>
            <li>Institute Dashboard</li>
            <li>Add Admin</li>
            <li class="active">Remove Admin</li>
            <li>Admin List</li>
            <li>Confidential Settings</li>
        </ul>
    </aside>

    <!-- Main Content -->
    <main class="content">

        <div class="success-card">
            <div class="success-title">Admin Removed Successfully</div>
            <div class="success-text">
                The selected administrator has been permanently removed from the institute database.
                All associated privileges and system access have been revoked.
            </div>

            <div class="success-actions">
                <a href="/VoteX/index.html" class="btn-primary">
                    Home
                </a>
            </div>
        </div>

    </main>
</div>

</body>
</html>)VoteX";
    return 0;
}