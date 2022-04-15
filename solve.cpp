#include <bits/stdc++.h>

#define f first
#define s second

using namespace std;
using pii = pair<int, int>;

const int N = 9;

mt19937 rnd(45768);

int a[N][N];
int can[N][N];

int all = (1 << N) - 1;

queue<pii> q;
map<int, int> pw2;
int unknown = N * N;

void try_set(int i, int j, string mes) {
    if(pw2.count(can[i][j])) {
        assert(a[i][j] == -1);
        a[i][j] = pw2[can[i][j]];
        q.emplace(i, j);
    }
}

void on_set(int i, int j) {
    unknown--;
    for(int k = 0; k < N; k++) {
        if(a[i][k] == -1) {
            can[i][k] &= (all ^ (1 << a[i][j]));
            try_set(i, k, "by can row");
        }

        if(a[k][j] == -1) {
            can[k][j] &= (all ^ (1 << a[i][j]));
            try_set(k, j, "by can column");
        }
    }

    for(int k1 = 0; k1 < 3; k1++) {
        for(int k2 = 0; k2 < 3; k2++) {
            int i1 = i / 3 * 3 + k1, j1 = j / 3 * 3 + k2;
            if(a[i1][j1] == -1) {
                can[i1][j1] &= (all ^ (1 << a[i][j]));
                try_set(i1, j1, "by can");
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if(argc > 1) {
        freopen(argv[1], "r", stdin);
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> a[i][j];
            a[i][j]--;

            if(a[i][j] != -1) {
                can[i][j] = (1 << a[i][j]);
            } else {
                can[i][j] = all;
            }
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(a[i][j] != -1)
                q.emplace(i, j);
        }
    }


    for(int i = 0; i < N; i++)
        pw2[1 << i] = i;

    while(unknown > 0) {
        while(!q.empty()) {
            int i = q.front().f, j = q.front().s;
            q.pop();

            on_set(i, j);
        }

        break;
    }

    if(unknown > 0)
        cout << "Can't solve" << endl;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++)
            cout << a[i][j] + 1 << ' ';
        cout << endl;
    }
}
