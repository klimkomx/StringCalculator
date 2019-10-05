#include <iostream>
#include <string>
#include <stdlib.h>


#include "stack.h"
#include "map.h"
#include "queue.h"
#include "sortst.h"
#include "functions.h"
#include <QtDebug>
using std::string;

const double EPS = 1e-9;
const double PI = 3.141592653589793238462643383279;
const double E = 2.718281828459045235360287471352;



char c = ' ';

string str(const char& ch) {
    string s =  "";
    s += ch;
    return s;
}
bool is_sim(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_') || (c >= '0' && c <= '9');
}

map<char, int> signs;
map<char, char> braces;
map<string, char> reserved;// = {{"sin", '$'}, {"cos", '#'}, {"log", '|'}};
map<char, string> reserved_rev;// = {{'$', "sin"}, {'#', "cos"}, {'|', "log"}};

void build() {

    signs['+'] = 0;
    signs['-'] = 0;
    signs['*'] = 1;
    signs['/'] = 1;
    signs['$'] = -1;
    signs['#'] = -1;
    signs['&'] = 0;
    signs['^'] = 2;
    signs['|'] = -1;
    braces[')'] = '(';
    braces[']'] = '[';
    reserved["sin"] = '$';
    reserved["cos"] = '#';
    reserved["log"] = '|';
    reserved_rev['$'] = "sin";
    reserved_rev['#'] = "cos";
    reserved_rev['|'] = "log";
    return;
}

extern queue<string> q1;
extern string perem[100000];
extern int perem_size;
extern map<string, double> mperem;
extern double calculationResult;
extern string polishNotation;

int log_check = 0;

bool calc() {
    stack<double> st;
    while (!q1.empty()) {
        string cur = q1.front();
        q1.pop();

        if (cur[0] >= '0' && cur[0] <= '9') {
            double val = 0;
            int fl = 0;
            for (int i = 0; i < cur.size(); ++i) {
                if (cur[i] == '.') {
                    if (i == cur.size() - 1)
                        return 1;
                    fl = i;
                    continue;
                }

                if (cur[i] == 'E') {
                    int ch = 1, j = i;
                    double rs = 0;
                    if (cur[j + 1] == '-') {
                        ch = -1;
                        j++;
                    }

                    if (cur[j + 1] == '+')
                        j++;

                    j++;

                    int fl1 = 0;
                    for (; j < cur.size(); ++j) {
                        if (cur[j] == '.') {
                            fl1 = j;
                            continue;
                        }
                        if (fl1 == 0)
                            rs = rs * 10 + (cur[j] - '0');
                        else
                            rs = rs + (cur[j] - '0') * pow(0.1, j - fl1);
                    }
                    val = val * pow(10, rs * ch);
                    break;
                }

                if (fl == 0)
                    val = val * 10 + (cur[i] - '0');
                else
                    val = val + (cur[i] - '0') * pow(0.1, i - fl);
            }

            st.push(val);
            continue;
        }

        if (is_sim(cur[0])) {
            if (cur == "pi")
                st.push(PI);
            else
            if (cur == "e")
                st.push(E);
            else
                st.push(mperem[cur]);
            continue;
        }

        if (cur[0] == '$') {
            if (st.empty())
                return 1;
            double val = st.top();
            st.pop();
            st.push(sin(val));
            continue;
        }

        if (cur[0] == '#') {
            if (st.empty())
                return 1;
            double val = st.top();
            st.pop();
            st.push(cos(val));
            continue;
        }

        if (cur == "&") {
            if (st.empty())
                return 1;
            double val = st.top();
            st.pop();
            st.push(0 - val);
            continue;
        }
qDebug() << "wat";
        if (cur[0] == '|') {
            if (st.empty())
                return 1;
            double val1 = st.top();
            st.pop();
            if (st.empty())
                return 1;
            double val2 = st.top();
            st.pop();
            if (val1 <= 0)
                return 1;
            if (val2 <= 0.0 || val2 == 1.0)
                return 1;
            qDebug() << val2 << val1;
            st.push(log(val2,val1));
            continue;
        }

        if (cur.size() == 1 && (cur == "^" || signs.find(cur[0]) != signs.end())) {
            if (st.empty())
                return 1;
            double val1 = st.top();
            st.pop();
            if (st.empty())
                return 1;
            double val2 = st.top();
            st.pop();

            if (cur[0] == '+')
                st.push(val1 + val2);
            if (cur[0] == '-')
                st.push(val2 - val1);
            if (cur[0] == '*') {
                if (val1 * val2 == -0)
                    st.push(0);
                else
                    st.push(val1 * val2);
            }
            if (cur[0] == '/') {
                if (val1 == 0)
                    return 1;
                if (val2 / val1 == -0)
                    st.push(0);
                else
                    st.push(val2 / val1);
            }
            if (cur[0] == '^') {
                if (val1 == 0 && val2 == 0)
                    return 1;
                if (val2 == 0) {
                    st.push(val2);
                    continue;
                }

                if (val2 < 0) {
                    int val3 = static_cast<int>(val1);
                    if (val3 != val1)
                        return 1;
                    if (val3 < 0) {
                        val2 = 1 / val2;
                        val3 = -val3;
                    }
                    if (val3 % 2 == 1)
                        st.push(-pow(abs(val2), val3));
                    else
                        st.push(pow(abs(val2), val3));
                    continue;
                }
                st.push(pow(val2, val1));
            }
        }
    }

    if (st.empty())
        return 1;

    double ans = st.top();
    st.pop();
    if (!st.empty())
        return 1;

    calculationResult = ans;
    return 0;
}

bool solve(string& inputString) {
    build();
    char clast = ' ';
    c = ' ';

    int fl = 0, flp = 0, iterator = 0;
    string s = "", sp = "";
    queue<string> q;
    stack<char> st;

    while (c != '=') {
        clast = c;
        c = inputString[iterator++];

        if (!(fl == 1 && c == 'E'))
            while (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))) {
                flp = 1;
                clast = '1';
                if (fl == 1)
                    return 1;

                while (is_sim(c)){
                    sp += c;
                    c = inputString[iterator++];
                }

                if (sp == "pi" || sp == "e") {
                    q.push(sp);
                    sp = "";
                    continue;
                }

                if (reserved.find(sp) != reserved.end()) {
                    if (c != '(')
                        return 1;

                    c = inputString[iterator++];
                    flp = 0;

                    if (reserved[sp] != '|') {
                        st.push('(');
                        st.push(reserved[sp]);
                        sp = "";
                    }
                    else {
                        st.push('(');
                        st.push(reserved[sp]);
                        sp = "";
                    }
                }
                else {
                    perem[perem_size++] = sp;
                    q.push(sp);
                    sp = "";
                }
            }

        if (fl == 1 && c == 'E') {
            if (!(c >= '0' && c <= '9') && c != '+' && c != '-')
                return 1;
            s += 'E';
            c = inputString[iterator++];
            s += c;
            c = inputString[iterator++];
            while (c >= '0' && c <= '9') {
                s += c;
                clast = c;
                c = inputString[iterator++];
            }
            q.push(s);
            s = "";
        }

        if (c == ',') {
            if (fl == 1 || clast == ')' || clast == ']' || flp == 1) {
                if (fl == 1) {
                    fl = 0;
                    q.push(s);
                    s = "";
                }
                flp = 0;
            }
            else return 1;

            while (!st.empty() && st.top() != '|') {
                q.push(str(st.top()));
                st.pop();
            }

            if (st.empty() || st.top() != '|')
                return 1;

            continue;
        }

        if (c == '=') {
            if (fl == 1 || clast == ')' || clast == ']' || flp == 1) {
                if (fl == 1) {
                    fl = 0;
                    q.push(s);
                    s = "";
                }
            }
            else return 1;

            continue;
        }

        if (c >= '0' && c <= '9') {
            if (clast == ')' || clast == ']') return 1;

            if (s.size() == 1 && s[0] == '0')
                s = "";

            s += c;
            fl = 1;
            continue;
        }

        if (c == '.') {
            if (fl == 0 || !(clast >= '0' && clast <= '9'))
                return 1;

            s += c;
            continue;
        }

        if (c == '-' && (clast == '(' || clast == '[' || clast == ' ' || clast == ',')) {
            st.push('&');
            continue;
        }

        if (signs.find(c) != signs.end() && c != '^') {
            if (fl == 1 || clast == ')' || clast == ']' || flp == 1) {
                if (fl == 1) {
                    fl = 0;
                    q.push(s);
                    s = "";
                }
                flp = 0;
            }
            else return 1;

            while (!st.empty() && signs.find(st.top()) != signs.end() && signs[st.top()] >= signs[c]) {
                q.push(str(st.top()));
                st.pop();
            }

            st.push(c);
            continue;
        }

        if (c == '^') {
            if (fl == 1 || clast == ')' || clast == ']' || flp == 1) {
                if (fl == 1) {
                    fl = 0;
                    q.push(s);
                    s = "";
                }
                flp = 0;
            }
            else return 1;

            st.push(c);
            continue;
        }

        if (c == braces[')'] || c == braces[']']) {
            if (fl == 1 || clast == ')' || clast == ']' || flp == 1)
                return 1;

            st.push(c);
            continue;
        }

        if (braces.find(c) != braces.end()) {
            if (fl == 1 || clast == ')' || clast == ']' || flp == 1) {
                if (fl == 1) {
                    fl = 0;
                    q.push(s);
                    s = "";
                }
                flp = 0;
            }
            else return 1;

            while (!st.empty() && st.top() != '(' && st.top() != '[') {
                q.push(str(st.top()));
                st.pop();
            }

            if (st.empty()) return 1;
            if (st.top() != braces[c]) return 1;

            st.pop();
            continue;
        }

        return 1;
    }

    while (!st.empty() && st.top() != braces[')'] && st.top() != braces[']']) {
        q.push(str(st.top()));
        st.pop();
    }

    if (!st.empty()) return 1;
    qDebug() << ";" << q.empty();
    polishNotation.clear();
    while (!q.empty()) {
        string cc = q.front();
        if (reserved_rev.find(cc[0]) != reserved_rev.end())
            polishNotation.append(reserved_rev[cc[0]] + " ");
        else
            polishNotation.append(q.front()+ " ");
        q1.push(q.front());
        q.pop();
    }
    return 0;
}

//int main() {
//    build();
//    while (true)
//        solve();

//    return 0;
//}
