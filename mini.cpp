#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <limits>

using namespace std;

class ContactManager {
public:
    void control_panel();
    void add_contact();
    void display_contacts();
    void search_contact();
    void delete_contact();
};

void ContactManager::control_panel() {
    system("cls");
    cout<<"\t\t\t**\n";
    cout << "\t\t\tWelcome to Contact Management System" << endl ;
    cout << "\t\t\t1. Add Contact" << endl;
    cout << "\t\t\t2. Display All Contacts" << endl;
    cout << "\t\t\t3. Search Contact" << endl;
    cout << "\t\t\t4. Delete Contact" << endl;
    cout << "\t\t\t5. Exit" << endl;
    cout<<"\t\t\t*\n";
}

void ContactManager::add_contact() {
    system("cls");
    ofstream file("Contacts.txt", ios::app);
    if (!file) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    string first_name, last_name, phone_number;
    cout << "Add Contact" << endl;
    cout << "Enter First Name: ";
    cin >> first_name;
    cout << "Enter Last Name: ";
    cin >> last_name;
    bool valid = false;
    while (!valid) {
        cout << "Enter Phone Number (exactly 10 digits): ";
        cin >> phone_number;
        if (phone_number.length() == 10 ) {
            valid = true;
        } else {
            cout << "Invalid phone number. Please enter exactly 10 digits." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    file << first_name << " " << last_name << " " << phone_number << endl;
    file.close();
}

void ContactManager::display_contacts() {
    system("cls");
    ifstream file("Contacts.txt");
    if (!file) {
        cerr << "Error: File not found." << endl;
        return;
    }

    cout << "All Contacts" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "First Name\t\tLast Name\t\tPhone Number" << endl;
    cout << "-----------------------------------------------" << endl;

    string first_name, last_name, phone_number;
    while (file >> first_name >> last_name >> phone_number) {
        cout << first_name << "\t\t" << last_name << "\t\t" << phone_number << endl;
    }
    file.close();
    cout << endl;
    system("pause");
}

void ContactManager::search_contact() {
    system("cls");
    ifstream file("Contacts.txt");
    if (!file) {
        cerr << "Error: File not found." << endl;
        return;
    }

    string first_name, last_name, phone_number;
    bool found = false;
    string search_name;
    cout << "Search Contact" << endl;
    cout << "Enter First Name or Last Name: ";
    cin >> search_name;
    while (file >> first_name >> last_name >> phone_number) {
        if (first_name == search_name || last_name == search_name) {
            found = true;
            cout << "First Name: " << first_name << endl;
            cout << "Last Name: " << last_name << endl;
            cout << "Phone Number: " << phone_number << endl;
            break;
        }
    }
    if (!found) {
        cout << "Contact not found." << endl;
    }
    file.close();
    cout << endl;
    system("pause");
}

void ContactManager::delete_contact() {
    system("cls");
    ifstream file("Contacts.txt");
    if (!file) {
        cerr << "Error: File not found." << endl;
        return;
    }

    string first_name, last_name, phone_number;
    string search_name;
    cout << "Delete Contact" << endl;
    cout << "Enter First Name or Last Name of Contact to delete: ";
    cin >> search_name;

    ofstream temp_file("temp.txt");
    bool found = false;
    while (file >> first_name >> last_name >> phone_number) {
        if (first_name == search_name || last_name == search_name) {
            found = true;
            cout << "Deleted Contact Successfully" << endl;
        } else {
            temp_file << first_name << " " << last_name << " " << phone_number << endl;
        }
    }
    if (!found) {
        cout << "Contact not found." << endl;
    }
    file.close();
    temp_file.close();

    remove("Contacts.txt");
    rename("temp.txt", "Contacts.txt");
    cout << endl;
    system("pause");
}

int main() {
    ContactManager contact;
    while (true) {
        contact.control_panel();
        cout << "\t\t\tEnter your choice : ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                contact.add_contact();
                break;
            case 2:
                contact.display_contacts();
                break;
            case 3:
                contact.search_contact();
                break;
            case 4:
                contact.delete_contact();
                break;
            case 5:
                cout << "\n\t\t\tThank You for visiting" << endl;
                exit(0);
            default:
                cout << "Invalid choice" << endl;
        }
    }

}
