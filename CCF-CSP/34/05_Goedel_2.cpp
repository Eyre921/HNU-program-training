#include<bits/stdc++.h>
using namespace std;

struct op
{
    int x1, x2, y1, y2, v;
} temp;

bool cmp(op &a, op &b)
{
    return a.v > b.v;
}

int main()
{

    int n, m;
    scanf("%d%d", &n, &m);
    vector<op> ops(n);
    int x1, x2, y1, y2, v;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d%d%d", &temp.x1, &temp.x2, &temp.y1, &temp.y2, &temp.v);
        ops.emplace_back(temp);
    }

    sort(ops.begin(), ops.end(), cmp);
    ++m;
    while (--m)
    {
        scanf("%d%d%d%d", &x1, &x2, &y1, &y2);
        v = 0;
        for (auto &theOp: ops)
        {
            if (theOp.x1 > x2 || theOp.x2 < x1 || theOp.y1 > y2 || theOp.y2 < y1)
            {
                continue;
            }
            v = theOp.v;
            break;
        }
        printf("%d\n", v);
    }
    return 0;
}
