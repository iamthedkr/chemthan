#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(logN)
*/
template<class num_t> struct SegmenTree {
    vector<num_t> st;
    vector<num_t> lz;
    SegmenTree(int n) {
        st.resize(n << 2);
        lz.resize(n << 2);
    }
    void pushdown(int p, int L, int R) {
        if (lz[p]) {
            st[p] += (R - L + 1) * lz[p];
            if (L < R) {
                lz[p << 1] += lz[p];
                lz[p << 1 | 1] += lz[p];
            }
            lz[p] = 0;
        }
    }
    void upd(int p, int l, int r, int L, int R, num_t val) {
        pushdown(p, L, R);
        if (r < L || R < l) return;
        if (l <= L && R <= r) {
            lz[p] = val;
            pushdown(p, L, R);
            return;
        }
        upd(p << 1, l, r, L, L + R >> 1, val);
        upd(p << 1 | 1, l, r, (L + R >> 1) + 1, R, val);
        st[p] = st[p << 1] + st[p << 1 | 1];
    }
    num_t query(int p, int l, int r, int L, int R) {
        pushdown(p, L, R);
        if (r < L || R < l) return 0;
        if (l <= L && R <= r) return st[p];
        return query(p << 1, l, r, L, L + R >> 1) + query(p << 1 | 1, l, r, (L + R >> 1) + 1, R);
    }
    void upd(int p, int l, int r, num_t val) {
        upd(p, l, r, 0, st.size() - 1, val);
    }
    num_t query(int p, int l, int r) {
        return query(p, l, r, 0, st.size() - 1);
    }
};

const int maxn = 1e5 + 5;
int n;
int a[maxn];

int main() {
    srand(time(NULL));
    n = 1000;
    SegmenTree<int> seg(n);
    for (int it = 0; it < 1000; it++) {
        int l = rand() % n;
        int r = rand() % n;
        if (l > r) swap(l, r);
        int v = rand() % 1000;
        for (int i = l; i <= r; i++) {
            a[i] += v;
        }
        seg.upd(1, l, r, 0, n - 1, v);
        l = rand() % n;
        r = rand() % n;
        if (l > r) swap(l, r);
        int ans = 0;
        for (int i = l; i <= r; i++) {
            ans += a[i];
        }
        assert(ans == seg.query(1, l, r, 0, n - 1));    
    }
    cout << "Correct!\n";
    return 0;
}
