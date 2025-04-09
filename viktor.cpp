#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int p = 0;
string s;

bool isd(char c) {
    return c >= '0' && c <= '9';
}

bool parse_u() {
    int sp = p;
    if (p < s.length() && isd(s[p])) {
        p++;
        while (p < s.length() && isd(s[p])) {
            p++;
        }
        return true;
    }
    else {
        p = sp;
        return false;
    }
}

bool parse_i() {
    int sp = p;
    if (p < s.length() && (s[p] == '-' || s[p] == '~')) {
        p++;
        if (parse_u()) {
            return true;
        }
        else {
            p = sp;
            return false;
        }
    }
    else if (parse_u()) {
        return true;
    }
    else {
        p = sp;
        return false;
    }
}

bool parse_cf(); // forward declaration

bool parse_inv() {
    int sp = p;

    // u~
    if (parse_u()) {
        if (p < s.length() && s[p] == '~') {
            p++;
            return true;
        }
        else {
            p = sp;
        }
    }

    // (cf)~
    sp = p;
    if (p < s.length() && s[p] == '(') {
        p++;
        if (parse_cf()) {
            if (p < s.length() && s[p] == ')') {
                p++;
                if (p < s.length() && s[p] == '~') {
                    p++;
                    return true;
                }
            }
        }
        p = sp;
    }

    return false;
}

bool parse_cf() {
    int sp = p;
    if (parse_i()) {
        if (p < s.length() && s[p] == '+') {
            p++;
            // вот здесь ключевое изменение:
            if (parse_i() || parse_inv()) {
                return true;
            }
            else {
                p = sp;
                return false;
            }
        }
        else {
            return true;
        }
    }
    else {
        p = sp;
        return false;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << "Строка: ";
    getline(cin, s);
    s.erase(remove(s.begin(), s.end(), ' '), s.end());

    p = 0;
    bool result = parse_cf();
    if (result && p == s.length()) {
        cout << "Является" << endl;
    }
    else {
        cout << "Не является" << endl;
    }

    return 0;
}
