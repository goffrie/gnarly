#include <iostream>

#include "shadowcast.h"

using namespace std;

// Tests the FOV shadowcasting implementation

vector<string> M;
vector<string> out;
vector<vector<bool> > opaque;
vector<vector<bool> > fov;

void mark(int y, int x) {
    if (y < 0 || y >= out.size()) return;
    if (x < 0 || x >= out[y].size()) return;
}
void print() {
    for (int y = 0; y < fov.size(); ++y) {
        for (int x = 0; x < fov[y].size(); ++x) {
            if (!fov[y][x]) {
                cout << M[y][x];
                continue;
            }
            if (M[y][x] == '@') cout << 'a';
            else if (out[y][x] == '#') cout << '$';
            else cout << '*';
        }
        cout << endl;
    }
}

int main() {
    string s;
    while (getline(cin, s)) M.push_back(s);
    opaque.resize(M.size());
    for (int y = 0; y < M.size(); ++y) {
        for (int x = 0; x < M[y].size(); ++x) {
            opaque[y].push_back(M[y][x] == '#');
        }
    }
    for (int y = 0; y < M.size(); ++y) {
        for (int x = 0; x < M[y].size(); ++x) {
            if (M[y][x] == '@') {
                out = M;
                shadowcast(y, x, 20, opaque, fov);
                print();
            }
        }
    }
}
