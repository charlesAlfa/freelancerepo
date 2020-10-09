#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


string buffer;
string names[10];
string pwds[10];
string modules[10][5];
int lecturer_count = 0;
string students[10];
string marks[10];
int student_count = 0;

string decrypt (string s) {
    for (int i=0 ; i < s.length(); i++)
        s[i]++;

    return s;
}


void init() {
    ifstream ifs("pwds.txt");
    while (getline(ifs, buffer)) {

        stringstream ss(buffer);
        ss >> names[lecturer_count];
        ss >> pwds[lecturer_count];
        ss >> modules[lecturer_count][0];

        int mods = 1;
        do {
            if (ss.eof()) {
                modules[lecturer_count][mods++] = "0";
            } else {
                ss >> modules[lecturer_count][mods++];
            }
        } while (mods < 5);

        pwds [lecturer_count] = decrypt(pwds[lecturer_count]);

        lecturer_count++;
    }
    ifs.close();


}

void load_students(string module) {
    string filename = module +".txt";
    ifstream ifs(filename);

    while (getline(ifs, buffer)) {

        stringstream ss(buffer);
        ss >> students[student_count];
        ss >> marks[student_count];

        student_count++;
    }
    ifs.close();


}

void show_students () {
    for (int i = 0; i < student_count; i++ ) {
        cout << i << ": " << students [i] << " " << marks [i] << endl;
    }
}


bool password_correct(string name, string password) {
    int i = 0;
    bool match = false;
    do {
        match = ((name == names[i]) && (password == pwds[i]));
        i++;
    } while ((match == false) && (i < lecturer_count));
    return match;
}

string get_module_choice(string name) {
    cout << endl;
    cout << "Welcome " << name << ". Here are your modules:" << endl;
    int leci = 0;
    while (names[leci] != name) leci++;

    for (int modi=0; modules[leci][modi] != "0" && modi < 5; modi++) {
        cout << modules[leci][modi] << endl;
    }

    cout << "Please select a module: ";

    string module;
    cin >> module;
    return module;
}


void save_students(string module) {

    string filename = module +".txt";

    ofstream ofs;
    ofs.open(filename);

    for (int i = 0; i < student_count; i++ ) {
        ofs << students[i] << " " << marks[i] << endl;
    }

    ofs.close();


    
}


int main () {
    string name;
    string password;

    init();
    cout << "Enter your name: " << endl;
    cin >> name;
    cout << "Enter your password: " << endl;
    cin >> password;
    if (!password_correct(name, password)) {
        exit(0);
    }

    string module;
    module = get_module_choice(name);
    
    load_students (module);
    show_students ();
    
    cout << "Select a student by number : " << endl;
    int which_student;
    cin >> which_student;
    cout << "Enter new mark for student" << endl;
    cin >> marks[which_student];

    cout << "Now saving back to file " << endl;

    save_students (module);





}
