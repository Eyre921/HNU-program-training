#include <iostream>
#include <set>        // 包含 std::set
#include <algorithm>  // 包含 set_union, set_intersection 等
#include <iterator>   // 包含 std::inserter
using namespace std;
// 辅助函数，用于打印 set 内容，方便查看结果

string trans(string &s)
{
	for (auto &c : s) c = tolower(c);
	return s;
}

int main()
{
	int n, m;
	cin >> n >> m;
	set<string> set1, set2;
	while (n--)
	{
		string word;
		cin >> word;
		set1.insert(trans(word));
	}
	while (m--)
	{
		string word;
		cin >> word;
		set2.insert(trans(word));
	}
	set<string> union_one, intersection_one;
	set_intersection(
	set1.begin(), set1.end(),
	set2.begin(), set2.end(),
	inserter(intersection_one, intersection_one.begin())
);
	set_union(
	    set1.begin(), set1.end(),
	    set2.begin(), set2.end(),
	    inserter(union_one, union_one.begin())
	);

	cout << intersection_one.size() << endl << union_one.size();
}
