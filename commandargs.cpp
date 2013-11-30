#include "commandargs.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "levelgen/filegen.h"
#include "levelgen/levelplan.h"

using namespace std;

bool haveLayout = false;
LevelPlan levelLayout;
bool gnarly = false;
bool dev = false;

void processArgs(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-gnarly") == 0) {
            gnarly = true;
        } else if (strcmp(argv[i], "-dev") == 0) {
            dev = true;
        } else if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 >= argc) {
                cout << "Invalid number of arguments. -f must be followed with a file" << endl;
                exit(1);
            }
            haveLayout = true;
            i++;
            ifstream file(argv[i]);
            static vector<FileGen> gens;
            while (file) {
                vector<string> layout;
                for (int i = 0; i < 25; ++i) {
                    string next;
                    if (!getline(file, next)) break;
                    layout.push_back(next);
                }
                if (layout.size() < 25) break;
                gens.push_back(FileGen(layout));
            }
            for (int i = 0; i < gens.size(); ++i) {
                levelLayout.levels.push_back(&gens[i]);
            }
        } else {
            cout << "Invalid argument " << argv[i] << endl;
            exit(1);
        }
    }
}
