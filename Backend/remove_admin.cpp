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
    if(i1==string::npos){// i1==string::npos or i1>cooki.length() 
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
    cout<<R"VoteX(
    <!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>VoteX · Remove Admin</title>

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
    font-weight:600;
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

.subtitle{
    font-size:14px;
    color:#94a3b8;
    margin-bottom:28px;
}

/* ================= FORM CARD ================= */
.form-card{
    max-width:520px;
    padding:28px;
    border-radius:18px;
    background:
        linear-gradient(180deg,rgba(148,163,184,0.06),rgba(2,6,23,0)),
        #020617;
    border:1px solid rgba(148,163,184,0.18);
    box-shadow:
        0 0 0 1px rgba(148,163,184,0.05),
        0 20px 40px rgba(0,0,0,0.45);
}

.form-group{
    margin-bottom:20px;
}

.form-group label{
    display:block;
    margin-bottom:8px;
    font-size:13px;
    color:#94a3b8;
}

select,
input{
    width:100%;
    padding:12px;
    border-radius:10px;
    background:#020617;
    border:1px solid rgba(148,163,184,0.25);
    color:#e5e7eb;
    font-size:14px;
}

select:focus,
input:focus{
    outline:none;
    border-color:#ef4444;
}

.warning-box{
    margin-bottom:22px;
    padding:14px;
    border-radius:12px;
    font-size:13px;
    color:#fecaca;
    background:rgba(239,68,68,0.08);
    border:1px solid rgba(239,68,68,0.35);
}

/* ================= BUTTON ================= */
button{
    width:100%;
    padding:14px;
    border:none;
    border-radius:12px;
    font-size:15px;
    font-weight:600;
    cursor:pointer;
    color:#020617;
    background:linear-gradient(135deg,#ef4444,#dc2626);
}

button:hover{
    opacity:0.95;
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

        <h1>Remove Administrator</h1>
        <p class="subtitle">
            Permanently revoke administrator access from the system.
        </p>

        <div class="form-card">

            <div class="warning-box">
                ⚠️ This action is irreversible. Ensure correct admin role and ID before proceeding.
            </div>

            <form action="/cgi-bin/VoteX/remove_admin_from_database.cgi" method="post">

                <div class="form-group">
                    <label for="admin_type">Select Admin Type</label>
                    <select name="admin_type" id="admin_type" required>
                        <option value="" disabled selected>-- Select Admin Role --</option>
                        <option value="1">Super Admin</option>
                        <option value="2">Election Admin</option>
                        <option value="3">Verification Admin</option>
                    </select>
                </div>

                <div class="form-group">
                    <label for="admin_id">Admin ID</label>
                    <input
                        type="text"
                        name="admin_id"
                        id="admin_id"
                        placeholder="e.g. MITS_SA_3"
                        required>
                </div>

                <button type="submit">Confirm Remove Admin</button>

            </form>
        </div>

    </main>
</div>

</body>
</html>
)VoteX";
}