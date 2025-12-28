// Not 100% succeded
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
using namespace std;
int main(){
    size_t len=atoi(getenv("CONTENT_LENGTH"));
    string data,id,pass,seckey,verans,phr;
    data.resize(len);
    cin.read(&data[0],len);
    cout << "Content-Type: text/html\r\n\r\n";
    ifstream fin;
    ofstream fout;
    string temp;
    size_t i1,i2,i3;
    i1=data.find("new_institute_id=");
    if(i1==string::npos) goto Details_Not_registered;
    i2=i1+17;
    i3=data.find("&new_password=");
    if(i3==string::npos) goto Details_Not_registered;
    id=data.substr(i2,i3-i2);
    i2=i3+14;
    i3=data.find("&new_secret_key=");
    if(i3==string::npos) goto Details_Not_registered;
    pass=data.substr(i2,i3-i2);
    i2=i3+16;
    i3=data.find("&new_verification_answer=");
    if(i3==string::npos) goto Details_Not_registered;
    seckey=data.substr(i2,i3-i2);
    i2=i3+25;
    i3=data.find("&confirm_phrase=");
    verans=data.substr(i2,i3-i2);
    if(i3==string::npos) goto Details_Not_registered;
    i2=i3+14;
    phr=data.substr(i2,14);
    if(phr!="CONFIRM CHANGE") goto Details_Not_registered;
        
    fin.open("C://xampp/VoteX_Private/Database/Institute_login_data.txt");
    getline(fin,data);
    getline(fin,data);
    getline(fin,data);
    getline(fin,data);
    getline(fin,data);
    fout.open("C://xampp/VoteX_Private/Database/Institute_login_data.txt",ios::trunc);
    fout<<id<<"\n"<<pass<<"\n"<<seckey<<"\n"<<verans<<"\n"<<data;
    fout.close();
    cout<<R"VoteX(<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>VoteX · Update Successful</title>

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
    background:#020617;
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
    background:#020617;
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

/* ================= CONTENT ================= */
.content{
    flex:1;
    padding:36px;
}

.content h1{
    font-size:30px;
    margin-bottom:8px;
    color:#22c55e;
}

.subtitle{
    font-size:14px;
    color:#94a3b8;
    margin-bottom:30px;
}

/* ================= SUCCESS CARD ================= */
.success-box{
    max-width:560px;
    padding:28px;
    border-radius:16px;
    background:
        linear-gradient(180deg,rgba(34,197,94,0.1),rgba(2,6,23,0)),
        #020617;
    border:1px solid rgba(34,197,94,0.4);
    box-shadow:
        0 0 0 1px rgba(34,197,94,0.1),
        0 20px 40px rgba(0,0,0,0.45);
}

.success-box h2{
    font-size:20px;
    margin-bottom:10px;
}

.success-box p{
    font-size:14px;
    color:#cbd5f5;
    margin-bottom:18px;
    line-height:1.6;
}

.success-actions{
    display:flex;
    gap:14px;
}

.success-actions a{
    text-decoration:none;
    padding:12px 18px;
    border-radius:10px;
    font-size:14px;
    font-weight:600;
    color:#020617;
    background:linear-gradient(135deg,#0ea5e9,#2563eb);
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
            <li>Remove Admin</li>
            <li>Admin List</li>
            <li>Confidential Settings</li>
        </ul>
    </aside>

    <!-- Main Content -->
    <main class="content">

        <h1>Update Successful</h1>
        <p class="subtitle">
            Institute login credentials updated successfully
        </p>

        <div class="success-box">
            <h2>Login Details Updated</h2>
            <p>
                The institute login credentials have been securely updated
                and stored in the system.
            </p>
            <p>
                Please ensure the updated credentials are kept confidential.
                All future logins will require the new details.
            </p>

            <div class="success-actions">
                
            </div>
        </div>

    </main>
</div>

</body>
</html>
)VoteX";
return 0;
    
    Details_Not_registered: 
        cout<<R"VoteX(<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>VoteX · Update Failed</title>

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
    background:#020617;
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
    background:#020617;
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

/* ================= CONTENT ================= */
.content{
    flex:1;
    padding:36px;
}

.content h1{
    font-size:30px;
    margin-bottom:8px;
    color:#ef4444;
}

.subtitle{
    font-size:14px;
    color:#94a3b8;
    margin-bottom:30px;
}

/* ================= ERROR CARD ================= */
.error-box{
    max-width:560px;
    padding:28px;
    border-radius:16px;
    background:
        linear-gradient(180deg,rgba(239,68,68,0.08),rgba(2,6,23,0)),
        #020617;
    border:1px solid rgba(239,68,68,0.35);
    box-shadow:
        0 0 0 1px rgba(239,68,68,0.1),
        0 20px 40px rgba(0,0,0,0.45);
}

.error-box h2{
    font-size:20px;
    margin-bottom:10px;
}

.error-box p{
    font-size:14px;
    color:#cbd5f5;
    margin-bottom:18px;
    line-height:1.6;
}

.error-actions{
    display:flex;
    gap:14px;
}

.error-actions a{
    text-decoration:none;
    padding:12px 18px;
    border-radius:10px;
    font-size:14px;
    font-weight:600;
    color:#020617;
    background:linear-gradient(135deg,#0ea5e9,#2563eb);
}

.error-actions a.secondary{
    background:linear-gradient(135deg,#ef4444,#dc2626);
    color:#fff;
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
            <li>Remove Admin</li>
            <li>Admin List</li>
            <li>Confidential Settings</li>
        </ul>
    </aside>

    <!-- Main Content -->
    <main class="content">

        <h1>Update Failed</h1>
        <p class="subtitle">
            Login credentials could not be updated
        </p>

        <div class="error-box">
            <h2>Unable to Change Login Details</h2>
            <p>
                The system was unable to update the institute login credentials.
                This may occur due to invalid confirmation details, a processing
                error, or a temporary system issue.
            </p>
            <p>
                No changes have been applied. Your existing credentials remain
                safe and unchanged.
            </p>

            <div class="error-actions">
                
            </div>
        </div>

    </main>
</div>

</body>
</html>
)VoteX";
        return 0;
}