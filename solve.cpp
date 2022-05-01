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

bool find_unique() {
    for(int x = 0; x < N; x++) {
        for(int i = 0; i < N; i++) {
            int cnt = 0, j1 = -1;
            for(int j = 0; j < N && cnt < 2; j++) {
                if(can[i][j] & (1 << x)) {
                    if(a[i][j] != -1) {
                        cnt = 2;
                    } else {
                        cnt++;
                        j1 = j;
                    }
                }
            }

            if(cnt == 1) {
                can[i][j1] = (1 << x);
                try_set(i, j1, "by find unique");
                return true;
            }
        }


        for(int j = 0; j < N; j++) {
            int cnt = 0, i1 = -1;
            for(int i = 0; i < N && cnt < 2; i++) {
                if(can[i][j] & (1 << x)) {
                    if(a[i][j] != -1) {
                        cnt = 2;
                    } else {
                        cnt++;
                        i1 = i;
                    }
                }
            }

            if(cnt == 1) {
                can[i1][j] = (1 << x);
                try_set(i1, j, "by find unique");
                return true;
            }
        }


        for(int k1 = 0; k1 < 3; k1++) {
            for(int k2 = 0; k2 < 3; k2++) {
                int cnt = 0, i1 = -1, j1 = -1;
                for(int i = k1 * 3; i < k1 * 3 + 3 && cnt < 2; i++) {
                    for(int j = k2 * 3; j < k2 * 3 + 3 && cnt < 2; j++) {
                        if(can[i][j] & (1 << x)) {
                            if(a[i][j] != -1) {
                                cnt = 2;
                            } else {
                                cnt++;
                                i1 = i;
                                j1 = j;
                            }
                        }
                    }
                }

                if(cnt == 1) {
                    can[i1][j1] = (1 << x);
                    try_set(i1, j1, "by find unique");
                    return true;
                }
            }
        }
    }

    return false;
}

bool find_unique_set() {
    bool res = false;
    for(int i = 0; i < N; i++) {
        for(int mask = 1; mask < (1 << N); mask++) {
            int msk = 0;
            bool flag = false;
            for(int j = 0; j < N; j++) {
                if(mask & (1 << j)) {
                    if(a[i][j] != -1) {
                        flag = true;
                        break;
                    } else {
                        msk |= can[i][j];
                    }
                }
            }

            if(flag)
                continue;



            if(__builtin_popcount(mask) == __builtin_popcount(msk)) {
                for(int j = 0; j < N; j++) {
                    if((mask & (1 << j)) == 0 && a[i][j] == -1) {
                        int prev = can[i][j];
                        can[i][j] &= (all ^ msk);
                        res |= (prev != can[i][j]);
                        try_set(i, j, "by group row");
                    }
                }
            }
        }
    }

    for(int j = 0; j < N; j++) {
        for(int mask = 1; mask < (1 << N); mask++) {
            int msk = 0;
            bool flag = false;
            for(int i = 0; i < N; i++) {
                if(mask & (1 << i)) {
                    if(a[i][j] != -1) {
                        flag = true;
                        break;
                    } else {
                        msk |= can[i][j];
                    }
                }
            }

            if(flag)
                continue;



            if(__builtin_popcount(mask) == __builtin_popcount(msk)) {
                for(int i = 0; i < N; i++) {
                    if((mask & (1 << i)) == 0 && a[i][j] == -1) {
                        int prev = can[i][j];
                        can[i][j] &= (all ^ msk);
                        res |= (prev != can[i][j]);
                        try_set(i, j, "by group column");
                    }
                }
            }
        }
    }

    for(int k1 = 0; k1 < 3; k1++) {
        for(int k2 = 0; k2 < 3; k2++) {
            for(int mask = 1; mask < (1 << N); mask++) {
                int msk = 0;
                bool flag = false;
                for(int l = 0; l < N; l++) {
                    if(mask & (1 << l)) {
                        int i = k1 * 3 + l / 3;
                        int j = k2 * 3 + l % 3;
                        if(a[i][j] != -1) {
                            flag = true;
                            break;
                        } else {
                            msk |= can[i][j];
                        }
                    }
                }

                if(flag)
                    continue;

                if(__builtin_popcount(mask) == __builtin_popcount(msk)) {
                    for(int l = 0; l < N; l++) {
                        int i = k1 * 3 + l / 3;
                        int j = k2 * 3 + l % 3;
                        if((mask & (1 << l)) == 0 && a[i][j] == -1) {
                            int prev = can[i][j];
                            can[i][j] &= (all ^ msk);
                            res |= (prev != can[i][j]);
                            try_set(i, j, "by group square");
                        }
                    }
                }
            }
        }
    }

    return res;
}

bool find_unique_set_in_two() {
    bool res = false;
    for(int x = 0; x < N; x++) {
        for(int k1 = 0; k1 < 3; k1++) {
            for(int k2 = 0; k2 < 3; k2++) {
                set<pii> posi, posj;
                bool flag = false;
                for(int i = k1 * 3; i < k1 * 3 + 3 && !flag; i++) {
                    for(int j = k2 * 3; j < k2 * 3 + 3 && !flag; j++) {
                        if(a[i][j] == x)
                            flag = true;
                        else if(a[i][j] == -1 && (can[i][j] & (1 << x))) {
                            posi.emplace(i, j);
                            posj.emplace(j, i);
                        }
                    }
                }


                if(flag)
                    continue;

                if(!posi.empty() && posi.begin()->f == prev(posi.end())->f) {
                    int i = posi.begin()->f;
                    for(int j = 0; j < N; j++) if(a[i][j] == -1 && (can[i][j] & (1 << x))) {
                        if(j < k2 * 3 || j >= k2 * 3 + 3) {
                            can[i][j] ^= (1 << x);
                            res = true;
                            try_set(i, j, "by two groups");
                        }
                    }
                }

                if(!posj.empty() && posj.begin()->f == prev(posj.end())->f) {
                    int j = posj.begin()->f;

                    for(int i = 0; i < N; i++) if(a[i][j] == -1 && (can[i][j] & (1 << x))) {
                        if(i < k1 * 3 || i >= k1 * 3 + 3) {
                            can[i][j] ^= (1 << x);
                            res = true;
                            try_set(i, j, "by two groups");
                        }
                    }
                }

                if(res)
                    return res;
            }
        }

        for(int i = 0; i < N; i++) {
            set<int> pos;
            bool flag = false;
            for(int j = 0; j < N && !flag; j++) {
                if(a[i][j] == x)
                    flag = true;
                else if(a[i][j] == -1 && (can[i][j] & (1 << x)))
                    pos.insert(j);
            }

            if(flag)
                continue;

            if(!pos.empty() && *pos.begin() / 3 == *pos.rbegin() / 3) {
                int k = *pos.begin() / 3;
                for(int j = 0; j < N; j++) {
                    if(a[i][j] == -1 && (can[i][j] & (1 << x)) && (j < k * 3 || j >= k * 3 + 3)) {
                        can[i][j] ^= (1 << x);
                        res = true;
                        try_set(i, j, "by two groups");
                    }
                }
            }
        }

        for(int j = 0; j < N; j++) {
            set<int> pos;
            bool flag = false;
            for(int i = 0; i < N && !flag; i++) {
                if(a[i][j] == x)
                    flag = true;
                else if(a[i][j] == -1 && (can[i][j] & (1 << x)))
                    pos.insert(i);
            }

            if(flag)
                continue;

            if(!pos.empty() && *pos.begin() / 3 == *pos.rbegin() / 3) {
                int k = *pos.begin() / 3;
                for(int i = 0; i < N; i++) {
                    if(a[i][j] == -1 && (can[i][j] & (1 << x)) && (i < k * 3 || i >= k * 3 + 3)) {
                        can[i][j] ^= (1 << x);
                        res = true;
                        try_set(i, j, "by two groups");
                    }
                }
            }
        }
    }

    return res;
}

bool check_correctness() {
    for(int i = 0; i < N; i++) {
        set<int> st;
        for(int j = 0; j < N; j++)
            if(a[i][j] != -1) {
                if(st.count(a[i][j]))
                    return false;
                st.insert(a[i][j]);
            }
    }

    for(int j = 0; j < N; j++) {
        set<int> st;
        for(int i = 0; i < N; i++)
            if(a[i][j] != -1) {
                if(st.count(a[i][j]))
                    return false;
                st.insert(a[i][j]);
            }
    }

    for(int k1 = 0; k1 < 3; k1++) {
        for(int k2 = 0; k2 < 3; k2++) {
            set<int> st;
            for(int i = k1 * 3; i < k1 * 3 + 3; i++) {
                for(int j = k2 * 3; j < k2 * 3 + 3; j++) {
                    if(a[i][j] != -1) {
                        if(st.count(a[i][j]))
                            return false;
                        st.insert(a[i][j]);
                    }
                }
            }
        }
    }

    return true;
}

bool solve(int depth) {
    while(unknown > 0) {
        while(!q.empty()) {
            int i = q.front().f, j = q.front().s;
            q.pop();

            on_set(i, j);
        }

        if(find_unique())
            continue;

        if(find_unique_set())
            continue;

        if(find_unique_set_in_two())
            continue;

        break;
    }

    if(!check_correctness())
        return false;

    if(unknown == 0)
        return true;

    vector<vector<int>> a1(N, vector<int>(N)), can1(N, vector<int>(N));
    int unknown1 = unknown;
    pii next;
    int mn = N + 1;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            a1[i][j] = a[i][j];
            can1[i][j] = can[i][j];
            if(a[i][j] == -1 && mn > __builtin_popcount(can[i][j])) {
                next = {i, j};
                mn = __builtin_popcount(can[i][j]);
            }
        }
    }

    int i = next.f, j = next.s;

    int msk = can[i][j];
    for(int x = 0; x < N; x++) {
        if(msk & (1 << x)) {
            can[i][j] = (1 << x);
            try_set(i, j, "surplus");

            solve(depth + 1);
            if(unknown == 0 && check_correctness())
                return true;

            for(int i = 0; i < N; i++) {
                for(int j = 0; j < N; j++) {
                    can[i][j] = can1[i][j];
                    a[i][j] = a1[i][j];
                }
            }
            while(!q.empty())
                q.pop();
            unknown = unknown1;
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            can[i][j] = can1[i][j];
            a[i][j] = a1[i][j];
        }
    }

    return false;
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

    if(!solve(0))
        cout << "Can't solve" << endl;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++)
            cout << a[i][j] + 1 << ' ';
        cout << endl;
    }
}
