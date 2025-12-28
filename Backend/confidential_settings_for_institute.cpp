#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
using namespace std;
int main(){
    char *cook=getenv("HTTP_COOKIE");
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
    if(cookie!=cookief){
        cout<<"Status: 302 Found\r\n";
        cout<<"Location: /VoteX/institute_auth_failed.html\r\n\r\n";
    }
    cout << "Content-Type: text/html; charset=UTF-8\r\n";
    cout<<R"VoteX(
    <!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>VoteX · Institute Confidential Settings</title>

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
    background:linear-gradient(135deg,#ef4444,#dc2626);
    color:#020617;
    font-weight:700;
}

/* ================= CONTENT ================= */
.content{
    flex:1;
    padding:36px;
}

.content h1{
    font-size:28px;
    margin-bottom:6px;
}

.subtext{
    font-size:14px;
    color:#94a3b8;
    margin-bottom:28px;
}

/* ================= CONFIDENTIAL CARD ================= */
.confidential-card{
    max-width:620px;
    padding:26px;
    border-radius:18px;
    background:
        linear-gradient(180deg,rgba(239,68,68,0.08),rgba(2,6,23,0)),
        #020617;
    border:1px solid rgba(239,68,68,0.35);
    box-shadow:
        0 0 0 1px rgba(239,68,68,0.08),
        0 30px 60px rgba(0,0,0,0.55);
}

.confidential-card h3{
    font-size:20px;
    margin-bottom:8px;
    color:#fecaca;
}

.confidential-card p{
    font-size:13px;
    color:#fca5a5;
    margin-bottom:20px;
    line-height:1.6;
}

/* ================= FORM ================= */
label{
    font-size:13px;
    color:#94a3b8;
}

input{
    width:100%;
    padding:13px;
    margin:8px 0 18px;
    border-radius:10px;
    border:1px solid rgba(148,163,184,0.25);
    background:#020617;
    color:#e5e7eb;
    font-family: ui-monospace, SFMono-Regular, monospace;
}

input:focus{
    outline:none;
    border-color:#ef4444;
}

/* ================= CONFIRM FIELD ================= */
.confirm-box{
    margin-top:12px;
    padding:14px;
    border-radius:12px;
    background:rgba(239,68,68,0.08);
    border:1px dashed rgba(239,68,68,0.45);
}

.confirm-box label{
    color:#fecaca;
    font-weight:600;
}

.confirm-box span{
    display:block;
    font-size:12px;
    color:#fca5a5;
    margin-bottom:8px;
}

/* ================= BUTTON ================= */
button{
    width:100%;
    padding:14px;
    margin-top:18px;
    border:none;
    border-radius:12px;
    font-size:14px;
    font-weight:800;
    cursor:pointer;
    color:#020617;
    background:linear-gradient(135deg,#ef4444,#dc2626);
}

button:hover{
    opacity:0.9;
}

/* ================= NOTE ================= */
.note{
    margin-top:14px;
    font-size:12px;
    color:#94a3b8;
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
            <li class="active">Confidential Settings</li>
        </ul>
    </aside>

    <!-- Main Content -->
    <main class="content">

        <h1>Confidential Settings</h1>
        <p class="subtext">
            You are already authenticated. Changes below affect institute identity and access.
        </p>

        <div class="confidential-card">

            <h3>⚠ Credential Update Warning</h3>
            <p>
                Modifying these credentials will immediately invalidate all sessions and require
                re-authentication using the new values.
            </p>

            <form action="/cgi-bin/VoteX/update_institute_core.cgi" method="post">

                <label>New Institute ID</label>
                <input type="text" name="new_institute_id" required>

                <label>New Password</label>
                <input type="password" name="new_password" required>

                <label>New Institute Secret Key</label>
                <input type="password" name="new_secret_key" required>

                <label>New Verification Answer</label>
                <input type="text" name="new_verification_answer" required>

                <div class="confirm-box">
                    <span>Type <b>CONFIRM CHANGE</b> to proceed</span>
                    <label>Confirmation Phrase</label>
                    <input type="text" name="confirm_phrase" placeholder="CONFIRM CHANGE" required>
                </div>

                <button type="submit">Apply Credential Changes</button>
            </form>

            <div class="note">
                This action is logged. You will be logged out after submission.
            </div>

        </div>

    </main>
</div>

</body>
</html>
)VoteX";
}