#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
using namespace std;
string HTML_Decoder(string s);
string session_creator();
int Dynamic_Pin_Genrator();
void Dynamic_Pin_updater_in_database(string idf, string passf, string seckeyf, string veransf, int dynamic_pin);
int main()
{
    size_t len = atoi(getenv("CONTENT_LENGTH"));
    string data;
    data.resize(len);
    cin.read(&data[0], len);
    data = HTML_Decoder(data);
    string id, pass, seckey, verans, dynamicpin;
    int i1 = data.find("institute_id=");
    int i2 = i1 + 13;
    int i3 = data.find("&password=");
    id = data.substr(i2, i3 - i2);
    i2 = i3 + 10;
    i3 = data.find("&secret_key=");
    pass = data.substr(i2, i3 - i2);
    i2 = i3 + 12;
    i3 = data.find("&security_answer=");
    seckey = data.substr(i2, i3 - i2);
    i2 = i3 + 17;
    i3 = data.find("&daily_pin=");
    verans = data.substr(i2, i3 - i2);
    i2 = i3 + 11;
    dynamicpin = data.substr(i2, len - i2);
    ifstream fin("C://xampp/VoteX_Private/Database/Institute_login_data.txt");
    string idf, passf, seckeyf, veransf, dynamicpinf;
    getline(fin, idf);
    getline(fin, passf);
    getline(fin, seckeyf);
    getline(fin, veransf);
    getline(fin, dynamicpinf);
    if (idf == id)
    {
        if (passf == pass)
        {
            if (seckeyf == seckey)
            {
                if (veransf == verans)
                {
                    if (dynamicpin == dynamicpinf)
                    {
                        string session = session_creator();
                        // 1. Setting Cookie
                        cout << "Content-Type: text/html; charset=UTF-8\r\n";
                        cout << "Set-Cookie: SESSION_ID=" << session << "; Path=/; HttpOnly\r\n";
                        cout << "\r\n";
                        // 2. Saving Cookie on server
                        ofstream fout("C://xampp/VoteX_Private/Database/Institute_Sessions.txt", ios::trunc);
                        fout << session << "\n";
                        fout.close();
                        // 3. To Genrate the Dynamic pin
                        int genrated_dynamic_pin;
                        genrated_dynamic_pin = Dynamic_Pin_Genrator();
                        // 4. To save the Genrated Dynamic Pin
                        Dynamic_Pin_updater_in_database(idf, passf, seckeyf, veransf, genrated_dynamic_pin);
                        // 5. To print the page
                        cout << R"VoteX(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>VoteX · Institute Dashboard</title>

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

.content h1{
    font-size:28px;
    margin-bottom:6px;
}

.welcome-text{
    font-size:14px;
    color:#94a3b8;
    margin-bottom:28px;
}

/* ================= PIN CARD ================= */
.daily-pin-box{
    width:420px;
    padding:20px;
    border-radius:14px;
    margin-bottom:36px;
    background:
        linear-gradient(180deg,rgba(56,189,248,0.08),rgba(2,6,23,0)),
        #020617;
    border:1px solid rgba(56,189,248,0.25);
    box-shadow:0 0 0 1px rgba(56,189,248,0.08);
}

.pin-title{
    font-size:14px;
    color:#94a3b8;
}

.pin-value{
    margin:8px 0;
    font-size:26px;
    font-weight:700;
    letter-spacing:4px;
    color:#38bdf8;
}

.pin-note{
    font-size:12px;
    color:#94a3b8;
}

/* ================= CARDS ================= */
.card-grid{
    display:grid;
    grid-template-columns:repeat(auto-fit,minmax(260px,1fr));
    gap:22px;
}

.card{
    padding:22px;
    border-radius:16px;
    background:
        linear-gradient(180deg,rgba(148,163,184,0.06),rgba(2,6,23,0)),
        #020617;
    border:1px solid rgba(148,163,184,0.18);
    box-shadow:
        0 0 0 1px rgba(148,163,184,0.05),
        0 20px 40px rgba(0,0,0,0.45);
}

.card h3{
    font-size:18px;
    margin-bottom:6px;
}

.card p{
    font-size:13px;
    color:#94a3b8;
    margin-bottom:16px;
}

.card button{
    width:100%;
    padding:12px;
    border:none;
    border-radius:10px;
    font-size:14px;
    font-weight:600;
    cursor:pointer;
    color:#020617;
    background:linear-gradient(135deg,#0ea5e9,#2563eb);
}

.card button.danger{
    background:linear-gradient(135deg,#ef4444,#dc2626);
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
            <li class="active">Institute Dashboard</li>
            <li>Add Admin</li>
            <li>Remove Admin</li>
            <li>Admin List</li>
            <li>Confidential Settings</li>
        </ul>
    </aside>

    <!-- Main Content -->
    <main class="content">

        <h1>Institute Dashboard</h1>
        <p class="welcome-text">
            Manage institute-level authorities and confidential access.
        </p>

        <!-- Dynamic PIN -->
        <div class="daily-pin-box">
            <div class="pin-title">Entry Security PIN</div>
            <div class="pin-value">)VoteX" << genrated_dynamic_pin
            << R"VoteX(</div>
            <div class="pin-note">
                This PIN is valid for next entry and must remain confidential.
            </div>
        </div>

        <!-- Action Cards -->
        <div class="card-grid">

            <div class="card">
                <h3>Add Admin</h3>
                <p>Authorize a new administrator for system operations.</p>
                <form action="/cgi-bin/VoteX/add_admin.cgi" method="post">
                    <button>Add Admin</button>
                </form>
            </div>

            <div class="card">
                <h3>Remove Admin</h3>
                <p>Revoke an existing administrator’s access.</p>
                <form action="/cgi-bin/VoteX/remove_admin.cgi" method="post">
                    <button class="danger">Remove Admin</button>
                </form>
            </div>

            <div class="card">
                <h3>Admin List</h3>
                <p>View all authorized administrators.</p>
                <form action="/cgi-bin/VoteX/admin_list.cgi" method="post">
                    <button>View List</button>
                </form>
            </div>

            <div class="card">
                <h3>Confidential Settings</h3>
                <p>Manage sensitive institute-level configurations.</p>
                <form action="/cgi-bin/VoteX/confidential_settings_for_institute.cgi" method="post">
                    <button>Access</button>
                </form>
            </div>

        </div>

    </main>
</div>

</body>
</html>
)VoteX";
                        return 0;
                    }
                    cout << "Status: 302 Found\r\n";
                    cout << "Location: /VoteX/institute_auth_failed.html\r\n\r\n";
                    return 0;
                }                
                cout << "Status: 302 Found\r\n";
                cout << "Location: /VoteX/institute_auth_failed.html\r\n\r\n";
                return 0;
            }
            cout << "Status: 302 Found\r\n";
            cout << "Location: /VoteX/institute_auth_failed.html\r\n\r\n";
            return 0;
        }
        cout << "Status: 302 Found\r\n";
        cout << "Location: /VoteX/institute_auth_failed.html\r\n\r\n";
        return 0;
    }
    cout << "Status: 302 Found\r\n";
    cout << "Location: /VoteX/institute_auth_failed.html\r\n\r\n";
    return 0;
}

string session_creator()
{
    int min = 0;                                  // minimum
    int max = 61;                                 // maximum
    random_device rd;                             // 1️⃣ seed
    mt19937 gen(rd());                            // 2️⃣ engine
    uniform_int_distribution<int> dist(min, max); // 3️⃣ range
    string session_origin = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string session;
    for (int i = 0; i < 32; i++)
    {
        int randomNumber = dist(gen); //  generate number
        session += session_origin[randomNumber];
    }
    return session;
}

int Dynamic_Pin_Genrator()
{
    int min = 100000;                             // minimum
    int max = 999999;                             // maximum
    random_device rd;                             // 1️⃣ seed
    mt19937 gen(rd());                            // 2️⃣ engine
    uniform_int_distribution<int> dist(min, max); // 3️⃣ range
    int randomNumber = dist(gen);
    return randomNumber;
}

void Dynamic_Pin_updater_in_database(string idf, string passf, string seckeyf, string veransf, int dynamic_pin)
{
    ofstream fout("C://xampp/VoteX_Private/Database/Institute_login_data.txt", ios::trunc);
    fout << idf << "\n"
         << passf << "\n"
         << seckeyf << "\n"
         << veransf << "\n"
         << dynamic_pin;
    fout.close();
    return;
}

string HTML_Decoder(string s)
{
    // 1. Know the string
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
    int *count = (int *)calloc(22, sizeof(int));
    int len = s.length();
    for (int i = 0; i < len; i++)
    {
        if (s[i] == '+')
        {
            count[21]++;
        }
        else if (s[i] == '%')
        {
            if (s[i + 1] == '2')
            {
                if (s[i + 2] == '0')
                {
                    count[0]++;
                    i += 2;
                }
                else if (s[i + 2] == '1')
                {
                    count[1]++;
                    i += 2;
                }
                else if (s[i + 2] == '2')
                {
                    count[2]++;
                    i += 2;
                }
                else if (s[i + 2] == '3')
                {
                    count[3]++;
                    i += 2;
                }
                else if (s[i + 2] == '4')
                {
                    count[4]++;
                    i += 2;
                }
                else if (s[i + 2] == '5')
                {
                    count[5]++;
                    i += 2;
                }
                else if (s[i + 2] == '6')
                {
                    count[6]++;
                    i += 2;
                }
                else if (s[i + 2] == '7')
                {
                    count[7]++;
                    i += 2;
                }
                else if (s[i + 2] == '8')
                {
                    count[8]++;
                    i += 2;
                }
                else if (s[i + 2] == '9')
                {
                    count[9]++;
                    i += 2;
                }
                else if (s[i + 2] == 'A')
                {
                    count[10]++;
                    i += 2;
                }
                else if (s[i + 2] == 'B')
                {
                    count[11]++;
                    i += 2;
                }
                else if (s[i + 2] == 'C')
                {
                    count[12]++;
                    i += 2;
                }
                else if (s[i + 2] == 'F')
                {
                    count[13]++;
                    i += 2;
                }
            }
            else if (s[i + 1] == '3')
            {
                if (s[i + 2] == 'A')
                {
                    count[14]++;
                    i += 2;
                }
                else if (s[i + 2] == 'B')
                {
                    count[15]++;
                    i += 2;
                }
                else if (s[i + 2] == 'D')
                {
                    count[16]++;
                    i += 2;
                }
                else if (s[i + 2] == 'F')
                {
                    count[17]++;
                    i += 2;
                }
            }
            else if (s[i + 1] == '4' && s[i + 2] == '0')
            {
                count[18]++;
                i += 2;
            }
            else if (s[i + 1] == '5')
            {
                if (s[i + 2] == 'B')
                {
                    count[19]++;
                    i += 2;
                }
                else if (s[i + 2] == 'D')
                {
                    count[20]++;
                    i += 2;
                }
            }
        }
    }
    for (int i = 0; i < 22; i++)
    {
        if (count[i] == 0)
        {
            continue;
        }
        else if (i == 0)
        {
            // space decoder
            for (int j = 0; j < count[0]; j++)
            {
                int ind = s.find("%20");
                s.replace(ind, 3, " ");
            }
        }
        else if (i == 1)
        {
            // Exclamation(!) decoder
            for (int j = 0; j < count[1]; j++)
            {
                int ind = s.find("%21");
                s.replace(ind, 3, "!");
            }
        }
        else if (i == 2)
        {
            // Double Quote decoder
            for (int j = 0; j < count[2]; j++)
            {
                int ind = s.find("%22");
                s.replace(ind, 3, "\"");
            }
        }
        else if (i == 3)
        {
            // Hash Decoder
            for (int j = 0; j < count[3]; j++)
            {
                int ind = s.find("%23");
                s.replace(ind, 3, "#");
            }
        }
        else if (i == 4)
        {
            // Dollar decoder
            for (int j = 0; j < count[4]; j++)
            {
                int ind = s.find("%24");
                s.replace(ind, 3, "$");
            }
        }
        else if (i == 5)
        {
            // Percentage decoder
            for (int j = 0; j < count[5]; j++)
            {
                int ind = s.find("%25");
                s.replace(ind, 3, "%");
            }
        }
        else if (i == 6)
        {
            // Ampersand decoder
            for (int j = 0; j < count[6]; j++)
            {
                int ind = s.find("%26");
                s.replace(ind, 3, "&");
            }
        }
        else if (i == 7)
        {
            // Single Quote decoder
            for (int j = 0; j < count[7]; j++)
            {
                int ind = s.find("%27");
                s.replace(ind, 3, "'");
            }
        }
        else if (i == 8)
        {
            // Open Parenthesis decoder
            for (int j = 0; j < count[8]; j++)
            {
                int ind = s.find("%28");
                s.replace(ind, 3, "(");
            }
        }
        else if (i == 9)
        {
            // Closed Parenthesis decoder
            for (int j = 0; j < count[9]; j++)
            {
                int ind = s.find("%29");
                s.replace(ind, 3, ")");
            }
        }
        else if (i == 10)
        {
            // Star decoder
            for (int j = 0; j < count[10]; j++)
            {
                int ind = s.find("%2A");
                s.replace(ind, 3, "*");
            }
        }
        else if (i == 11)
        {
            // Plus decoder
            for (int j = 0; j < count[11]; j++)
            {
                int ind = s.find("%2B");
                s.replace(ind, 3, "+");
            }
        }
        else if (i == 12)
        {
            // Comma decoder
            for (int j = 0; j < count[12]; j++)
            {
                int ind = s.find("%2C");
                s.replace(ind, 3, ",");
            }
        }
        else if (i == 13)
        {
            // Front Slash decoder
            for (int j = 0; j < count[13]; j++)
            {
                int ind = s.find("%2F");
                s.replace(ind, 3, "/");
            }
        }
        else if (i == 14)
        {
            // Colon decoder
            for (int j = 0; j < count[14]; j++)
            {
                int ind = s.find("%3A");
                s.replace(ind, 3, ":");
            }
        }
        else if (i == 15)
        {
            // Semicolon decoder
            for (int j = 0; j < count[15]; j++)
            {
                int ind = s.find("%3B");
                s.replace(ind, 3, ";");
            }
        }
        else if (i == 16)
        {
            // Equal to decoder
            for (int j = 0; j < count[16]; j++)
            {
                int ind = s.find("%3D");
                s.replace(ind, 3, "=");
            }
        }
        else if (i == 17)
        {
            // Question mark decoder
            for (int j = 0; j < count[17]; j++)
            {
                int ind = s.find("%3F");
                s.replace(ind, 3, "?");
            }
        }
        else if (i == 18)
        {
            // at the rate decoder
            for (int j = 0; j < count[18]; j++)
            {
                int ind = s.find("%40");
                s.replace(ind, 3, "@");
            }
        }
        else if (i == 19)
        {
            // Open Square Bracket decoder
            for (int j = 0; j < count[19]; j++)
            {
                int ind = s.find("%5B");
                s.replace(ind, 3, "[");
            }
        }
        else if (i == 20)
        {
            // Closed Square bracket decoder
            for (int j = 0; j < count[20]; j++)
            {
                int ind = s.find("%5D");
                s.replace(ind, 3, "]");
            }
        }
        else if (i == 21)
        {
            // Space decoder
            for (int j = 0; j < count[21]; j++)
            {
                int ind = s.find("+");
                s.replace(ind, 1, " ");
            }
        }
    }
    free(count);
    return s;
}