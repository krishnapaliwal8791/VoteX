# 🗳 VoteX

*VoteX* is a secure, efficient, and user-friendly voting application designed to streamline the polling process of our institute level election, for quick decision-making, VoteX provides a transparent platform for real-time vote tracking and management.

---

## 🚀 Features

* *Secure Authentication:* User verification using alloted *Institute identifier name, Password, Institute secondary key, Institute secret key, Security verification answer* and dynamically changing *Administrative PIN* that is provided in *Institute_Login_Data.txt* file.

* *Create & Manage Polls:* Super Admin and Election Admins can easily create elections with multiple candidates.
* *Results:* View vote counts after voting pool ends and voting gets concluded.
* *Responsive Design:* Optimized for desktop only for now.
* *Anonymity:* Ensures voter privacy and data integrity.
* *Cutting-edge benifit:* Ultra fine and fast C++ backend for faster response during high user traffic.  

## 🛠 Tech Stack

*Frontend:*
* HTML5 & CSS3

*Backend:*
*  CGI, C++

*Database:*
*  File handling

## 📸 Screenshots

<img src="https://github.com/PrateekSingh2/VoteX2.0/blob/808c891766318cd90ef57e21a612ee651d00f9e5/assets/Screenshot%202025-12-27%20185928.png" alt="Home page">
(Actual screenshots of VoteX👆)

## ⚙ Installation & Setup

Follow these steps to run the project locally.

*Prerequisites:*
* XAMPP installation

*Steps:*

  ***1.)** Clone the repository*
    
    git clone https://github.com/krishnapaliwal8791/VoteX.git
     

***2.)** Setup XAMPP for VoteX:*
   Go to Local Disk C:  where your windows is installed.
Then, go to XAMPP folder and setup with following things:
* Copy VoteX folder that you cloned from GIT and paste in "htdocs" named folder inside XAMPP folder.
* Then move out of it, and copy VoteX_Private folder and paste in XAMPP itself.
* Then go to "cgi-bin" name folder in parent folder of XAMPP and create a folder named as "VoteX" and in that create ".cgi" extension files of all the C++ files that are listed in VoteX->Backend folder from CMD by executing

```
g++ yourfile.cpp -o yourfile.cgi
```
    

**3.)** *Run the Application*
  Open XAMPP dashboard and then run Apache server.
Now open your browser and type:


```
localhost/VoteX/index.html
 ```
   

## 🪜Hierarchy
There are four levels of hierarchy in this Voting system:

**1.)**  **Voter/Representative:** Any person who is voting to thier favourable representative in the election. He/She has only rights to first get registered themself on portal and then can be able to give vote to only one person and that vote cannot be changed further.

**2.)** **Verification Admin:** This is the department where registered voters and representative gets verified to be listed in the list of voters and representatives in electon.

**3.)** **Election Admin:** This department manage main elections tasks like deleting voters if they have done any mal-practiced or any representative have done any unfair activity that violates election rules. This department can permanently ban users from this portal for future use.

**4.)** **Super Admin:** This department consists of only one person which is the Head of the election and Votex. Who operates this whole election and on behalf of this Super Admin other admin do thier respected task. This Admin takes care of fare behaviour of other Admins and voters and proper functioning/working/ and execution of VoteX and election.




## 🤝 Contributing

Contributions are welcome! Please follow these steps:
1.  Fork the repository.
2.  Create a new branch (git checkout -b feature/AmazingFeature).
3.  Commit your changes (git commit -m 'Add some AmazingFeature').
4.  Push to the branch (git push origin feature/AmazingFeature).
5.  Open a Pull Request.



## 📞 Contact

*Krishna Paliwal*
* GitHub: [krishnapaliwal8791](https://github.com/krishnapaliwal8791)
* Email: 25ai1kr75@mitsgwl.ac.in

Project Link: [https://github.com/krishnapaliwal8791/VoteX](https://github.com/krishnapaliwal8791/VoteX)
