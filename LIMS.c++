#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>

using namespace std;

class Library {
public:
    int id;
    char book_name[1000];
    char author_name[1000];
    char student_name[1000];
    int price;
    int pages;

    void inputDetails() {
        cout << "Enter Book Id: ";
        cin >> id;
        cin.ignore(); 
        cout << "Enter Book Name: ";
        cin.getline(book_name, 1000, '$');
        cout << "Enter Author Name: ";
        cin.getline(author_name, 1000, '$');
        cout << "Enter Student Name: ";
        cin.getline(student_name, 1000, '$');
        cout << "Enter Book Price: ";
        cin >> price;
        cout << "Enter Book Pages: ";
        cin >> pages;
        cin.ignore();
    }

    void display() const {
        cout << left << setw(10) << "BOOK ID:" << id << endl;
        cout << left << setw(10) << "NAME:" << book_name << endl;
        cout << left << setw(10) << "AUTHOR:" << author_name << endl;
        cout << left << setw(10) << "STUDENT:" << student_name << endl;
        cout << left << setw(10) << "PRICE:" << price << endl;
        cout << left << setw(10) << "PAGES:" << pages << endl;
    }
};

void saveToFile(Library* lib, int count) {
    ofstream outfile("library_data.txt");
    for (int i = 0; i < count; i++) {
        outfile << lib[i].id << endl;
        outfile << lib[i].book_name << endl;
        outfile << lib[i].author_name << endl;
        outfile << lib[i].student_name << endl;
        outfile << lib[i].price << endl;
        outfile << lib[i].pages << endl;
    }
    outfile.close();
}

void loadFromFile(Library* lib, int& count) {
    ifstream infile("library_data.txt");
    while (infile >> lib[count].id) {
        infile.ignore();
        infile.getline(lib[count].book_name, 1000);
        infile.getline(lib[count].author_name, 1000);
        infile.getline(lib[count].student_name, 1000);
        infile >> lib[count].price;
        infile >> lib[count].pages;
        infile.ignore();
        count++;
    }
    infile.close();
}

int main() {
    Library lib[25];
    int input = 0;
    int count = 0;

    loadFromFile(lib, count); // Load existing data

    while (input != 3) {
        cout << "1. Input book details\n2. Display books\n3. Quit\n";
        cin >> input;
        cin.ignore();

        switch (input) {
            case 1:
                if (count < 25) {
                    lib[count].inputDetails();
                    count++;
                    saveToFile(lib, count); // Save after adding
                } else {
                    cout << "Library is full! Cannot add more books." << endl;
                }
                break;

            case 2:
                if (count == 0) {
                    cout << "No entries found." << endl;
                } else {
                    for (int i = 0; i < count; i++) {
                        lib[i].display();
                    }
                }
                break;

            case 3:
                exit(0);
                break;

            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}
