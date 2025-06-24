#pragma GCC optimize(2, 3, "Ofast", "inline")

#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

//#define int long long

//#define double long double

using i64 = long long;

using ui64 = unsigned long long;

//using i128 = __int128;

#define inf (int)0x3f3f3f3f3f3f3f3f

#define INF 0x3f3f3f3f3f3f3f3f

#define yn(x) cout << (x ? "yes" : "no") << endl

#define Yn(x) cout << (x ? "Yes" : "No") << endl

#define YN(x) cout << (x ? "YES" : "NO") << endl

#define mem(x, i) memset(x, i, sizeof(x))

#define cinarr(a, n) for (int _ = 1; _ <= n; _++) cin >> a[_]

#define cinstl(a) for (auto& _ : a) cin >> _

#define coutarr(a, n) for (int _ = 1; _ <= n; _++) cout << a[_] << " \n"[_ == n]

#define coutstl(a) for (const auto& _ : a) cout << _ << ' '; cout << endl

#define all(x) (x).begin(), (x).end()

#define md(x) (((x) % mod + mod) % mod)

#define ls (s << 1)

#define rs (s << 1 | 1)

#define ft first

#define se second

#define pii pair<int, int>

#ifdef DEBUG

#include "debug.h"

#else

#define dbg(...) void(0)

#endif


const int N = 1000 + 5;

const int M = N * 40;

const int mod = 998244353;

//const int mod = 1e9 + 7;

//template <typename T> T ksm(T a, i64 b) { T ans = 1; for (; b; a = 1ll * a * a, b >>= 1) if (b & 1) ans = 1ll * ans * a; return ans; }

//template <typename T> T ksm(T a, i64 b, T m = mod) { T ans = 1; for (; b; a = 1ll * a * a % m, b >>= 1) if (b & 1) ans = 1ll * ans * a % m; return ans; }


int b[N], c[N];

int n, m, t, k, q, v;


vector<int> a[N];


int dp[N][M]; //前i个仓库，花费为j时的最大净收益


void work()

{
    cin >> n >> m >> v;

    int C = 0;

    for (int i = 1; i <= n; i++) cin >> b[i] >> c[i], C += b[i];

    for (int i = 1; i <= m; i++)

    {
        cin >> k >> t, ++t, C += c[t];

        if (c[t] < k) a[t].emplace_back(k - c[t]);
    }


    for (int i = 1; i <= n; i++)

    {
        sort(all(a[i]), greater());

        for (int j = 1; j < a[i].size(); j++)

            a[i][j] += a[i][j - 1];
    }


    int ans = inf;

    for (int i = 1; i <= n; i++)

    {
        for (int j = 0; j <= C; j++)

        {
            dp[i][j] = dp[i - 1][j];

            for (int k = 0; k < a[i].size(); k++)

            {
                if (j - b[i] - c[i] * (k + 1) < 0) break;

                dp[i][j] = max(dp[i][j], dp[i - 1][j - b[i] - c[i] * (k + 1)] + a[i][k] - b[i]);
            }

            if (dp[i][j] >= v) ans = min(ans, j);
        }
    }


    cout << ans << endl;
}


signed main()

{
#ifdef LOCAL

freopen("C:\\Users\\admin\\CLionProjects\\Practice\\data.in", "r", stdin);

freopen("C:\\Users\\admin\\CLionProjects\\Practice\\data.out", "w", stdout);

#endif

    ios::sync_with_stdio(false);

    cin.tie(0);

    cout.tie(0);

    int Case = 1;

    //cin >> Case;

    while (Case--) work();

    return 0;
}

/*

2 3 15

2 1

3 2

10 0

20 1

15 0



4

*/


/*

5 3 15

2 1

1 1

3 2

4 2

1 5

10 1

10 1

10 1



3

*/
