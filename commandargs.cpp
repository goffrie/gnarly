#include "commandargs.h"
#include <cstring>
#include <iostream>

using namespace std;

string layoutFile = "";
bool useCurses = false;
bool dev = false;

void processArgs(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-curses") == 0) {
            useCurses = true;
        } else if (strcmp(argv[i], "-dev") == 0) {
            dev = true;
        } else if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 >= argc) {
                cout << "Invalid number of arguments. -f must be followed with a file" << endl;
                exit(1);
            }
            layoutFile = argv[i+1];
        } else {
            cout << "Invalid argument " << argv[i] << endl;
            exit(1);
        }
    }
}
