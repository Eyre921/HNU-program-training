// Original Filename: 09.电能消耗.cpp
#include<iostream>
#include<algorithm>
using namespace std;

int power(int n, int p1, int p2, int p3, int t1, int t2)
{
	if (n <= t1)return n * p1;
	else if (n > t1 && n <= t1 + t2)return p1 * t1 + (n - t1) * p2;
	else return p1 * t1 + p2 * t2 + (n - t1 - t2) * p3;
}

int main()
{
	int n, p1, p2, p3, t1, t2;
	cin >> n >> p1 >> p2 >> p3 >> t1 >> t2;
	int l[n], r[n];
	int sum = 0;
	for (int i = 0; i < n; ++i)
	{
		cin >> l[i] >> r[i];
		sum += ((r[i] - l[i]) * p1);
	}
	for (int i = 1; i < n; ++i)sum += power(l[i] - r[i - 1], p1, p2, p3, t1, t2);
	cout << sum;
}
