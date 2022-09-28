#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

void clearScreen();

int main()
{

//initial register variables
int login_status;
string username, password, email, email_input;

//for logging in
string un, pw;

//for deleting account
string confirmCheck = "deleteAccount";
string remCheck, deleteAccount;

cout << "Press 1 to Register\nPress 2 to Login\nPress 3 to delete account\n";
cout << "Enter: ";
cin >> login_status;

if (login_status == 1) //Register
{
    clearScreen();
    cout << "Enter a username: ";
    cin >> username;
    bool exists = filesystem::exists(username + ".txt");

    if (!exists)
    {
    ofstream user_info(username + ".txt");
    //string email_input;
    if (user_info.is_open())
    {
        user_info << username << '\n';

        cout << "Enter a password: ";
        cin >> password;
        user_info << password << '\n';

        cout << "Enter your email address: ";
        cin >> email;    
        user_info << email << '\n';

        cout << "Thank you for making an account " << username << "!\n";
        user_info.close();
    } 
    } else cout << "Username already taken.\n";
}
else if (login_status == 2)
{
    cout << "Enter your username: ";
    cin >> username;
    bool exists = filesystem::exists(username + ".txt");
    ifstream user;
    
    string un;
    string pw;

    if (exists)
    {
        
        int passReset = 0;
        user.open(username + ".txt");
        while (passReset < 3)
        {
        cout << "Enter your password: ";
        cin >> password;
        if (user.is_open())
        {
            getline(user,un);
            getline(user,pw);

            if (un == username && pw == password)
            {
                cout << "Access granted. Welcome, " << username << '\n';
                return 0;
            }
            else 
            {
                cout << "Access denied.\n";
                passReset++;
            }   
        }
    }
        if (passReset == 3)
        {
            string ans;
            cout << "Would you like to reset your password? y or n\n";
            cout << "Enter: ";
            cin >> ans;
            clearScreen();
            if (ans == "y")
            {
                string tempUser;
                ofstream reset(username + ".txt");
                if (reset.is_open())
                {
                    cout << "Confirm your username: ";
                    cin >> tempUser;
                    if (tempUser == username) 
                    {
                        reset.clear();
                        reset << username << '\n';
                        cout << "Enter the email to send the ""password link"": ";
                        cin >> email;
                        cout << "Enter your new password: ";
                        cin >> password;
                        reset << password << '\n';
                        reset << email << '\n';
                    }
                    else 
                    {
                    reset.close();
                    cout << "Invalid username.";
                    }
                }
            }
        }
    }
    else cout << "No accounts with username: " << username << "\nAre you trying to Register?\n";
    user.close();
}
else if (login_status == 3)
{
    cout << "Enter your username: ";
    cin >> username;
    cout << "Are you sure you want to delete your account? y or n\n";
    cin >> remCheck;
    if (remCheck == "y")
    {
        clearScreen();
        cout << "Type in this code: " << confirmCheck << '\n';
        cin >> remCheck;
        if (remCheck == confirmCheck)
        {
            username.append(".txt");
            if (remove(username.c_str()) != 0) 
            {
                cout << "Account not deleted. Potentially never existed.\nexiting...\n";
            } 
            else 
            {
            cout << "If you ever want to make an account again feel free :)\n";
            }
        }
    else 
    {
        cout << "Wrong Code. exiting...\n";
    }
} 
else
{
    cout << "Thanks for changing your mind. exiting...\n";
}
}
else cout << "Incorrect login status. Must be 1, 2, or 3.\n";
}

void clearScreen()
{
    cout << string(100, '\n');
}