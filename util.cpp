#include "util.h"

using namespace std;

vector<string> getLines(const string& t, int width) {
    vector<string> lines;
    unsigned int i = 0;
    while (i < t.size()) {
        string next = t.substr(i, width);
        // Try to split it at the first newline, try to contain the entire string,
        // or try to split it at the last space, in that order

        if (next.find('\n') != string::npos) {
            // There is a newline
            int nextPos = next.find('\n');
            lines.push_back(next.substr(0, nextPos));
            i += nextPos + 1;
        } else if (i + width > t.size()) {
            lines.push_back(next);
            break;
        } else if (next.rfind(' ') != string::npos) {
            // There is a space
            int nextPos = next.rfind(' ');
            lines.push_back(next.substr(0, nextPos));
            i += nextPos + 1;
        } else {
            // There is no space
            next[next.size() - 1] = '-';
            lines.push_back(next);
            i += width - 1;
        }
    }
    return lines;
}

string capitalize(const string& t) {
    string s = t;
    if (s.size() > 0) s[0] = toupper(s[0]);
    return s;
}

string titleCase(const string& t) {
    string s = t;
    bool cap = true;
    for (unsigned int i = 0; i < s.size(); ++i) {
        if (isspace(s[i])) {
            cap = true;
        } else if (cap) {
            s[i] = toupper(s[i]);
            cap = false;
        }
    }
    return s;
}

bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}
