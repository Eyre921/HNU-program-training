#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, p, q;
    cin >> n >> m >> p >> q;
    int total_elements = n * m;


    for (int i = 0; i < total_elements; ++i)
    {
        int element;
        cin >> element;
        cout << element;
        if ((i + 1) % q == 0) cout << "\n";
        else cout << " ";
    }
    return 0;
}

/*
2 3 3 2
1 2 3
4 5 6

1 2
3 4
5 6

2 2 1 4
6 6
6 6

6 6 6 6
 */
