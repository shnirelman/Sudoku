#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    string filename = argv[1];

    filename.replace(filename.find('.') - 2, 2, "out");

    ifstream fin1(filename);
    ifstream fin2("output.txt");

    bool res = true;
    while(!fin1.eof() && res) {
        if(fin2.eof()) {
            res = false;
        } else {
            string s1, s2;
            fin1 >> s1;
            fin2 >> s2;
            if(s2[0] == 'C') {
                cout << filename << " unsolved" << endl;
                return 0;
            }
            res &= (s1 == s2);
        }
    }

    cout << filename << ' ' << (res ? "ok" : "error") << endl;
}
