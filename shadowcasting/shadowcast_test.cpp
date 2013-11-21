#include <iostream>

#include "shadowcast.h"

using namespace std;

vector<string> M;
vector<string> out;

bool opaque(int y, int x) {
    if (y < 0 || y >= M.size()) return false;
    if (x < 0 || x >= M[y].size()) return false;
    return M[y][x] == '#';
}

void mark(int y, int x) {
    if (y < 0 || y >= out.size()) return;
    if (x < 0 || x >= out[y].size()) return;
    if (out[y][x] == '@' || out[y][x] == 'a') out[y][x] = 'a';
    else if (out[y][x] == '#' || out[y][x] == '$') out[y][x] = '$';
    else out[y][x] = '*';
}

int main() {
    string s;
    while (getline(cin, s)) M.push_back(s);
    for (int y = 0; y < M.size(); ++y) {
        for (int x = 0; x < M[y].size(); ++x) {
            if (M[y][x] == '@') {
                out = M;
                shadowcast(y, x, 10, opaque, mark);
                for (int y = 0; y < M.size(); ++y) {
                    cout << out[y] << '\n';
                }
                cout << endl;
            }
        }
    }
}
