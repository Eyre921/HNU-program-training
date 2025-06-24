#include <iostream>
#include <vector>
#include <cmath>      // For sqrt
#include <algorithm>  // For sort
#include <cfloat>     // For DBL_MAX
using namespace std;

// 定义点结构体
struct Point
{
    double x, y;
};

// 比较函数，用于按 x 坐标排序
bool compareX(Point a, Point b)
{
    return a.x < b.x;
}

// 比较函数，用于按 y 坐标排序
bool compareY(Point a, Point b)
{
    return a.y < b.y;
}

// 计算两点距离的平方
double distSq(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

// 暴力法求解最近点对（用于小规模问题）
// points[] 是按y坐标排序的子数组
double bruteForce(const vector<Point> &points, int left, int right)
{
    double min_dist_sq = DBL_MAX;
    for (int i = left; i <= right; ++i)
    {
        for (int j = i + 1; j <= right; ++j)
        {
            min_dist_sq = min(min_dist_sq, distSq(points[i], points[j]));
        }
    }
    return min_dist_sq;
}

// 寻找条带区域内的最近点对
// strip[] 是y坐标有序的
// d_sq 是已知的最小距离平方
double stripClosest(vector<Point> &strip, double d_sq)
{
    double min_dist_sq = d_sq;

    // 遍历条带中的每个点
    for (size_t i = 0; i < strip.size(); ++i)
    {
        // 对于每个点，检查其后y坐标差小于sqrt(d_sq)的点
        // 这个内层循环最多只会执行常数次（理论上是7次）
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < min_dist_sq;
             ++j)
        {
            min_dist_sq = min(min_dist_sq, distSq(strip[i], strip[j]));
        }
    }
    return min_dist_sq;
}

// 递归函数，寻找最近点对
// px 是按x坐标排序的点集
// py 是按y坐标排序的点集
double closestUtil(vector<Point> &px, vector<Point> &py)
{
    int n = px.size();

    // 基本情况：如果点数很少，直接使用暴力法
    if (n <= 3)
    {
        return bruteForce(px, 0, n - 1);
    }

    // 找到中间点，用于分割
    int mid = n / 2;
    Point midPoint = px[mid];

    // 根据中间点，将y排序的点集py分割成左右两部分 pyl 和 pyr
    vector<Point> pyl, pyr;
    for (const auto &p: py)
    {
        if (p.x <= midPoint.x)
        {
            pyl.push_back(p);
        } else
        {
            pyr.push_back(p);
        }
    }

    // 将x排序的点集px也分割成左右两部分
    vector<Point> px_left(px.begin(), px.begin() + mid);
    vector<Point> px_right(px.begin() + mid, px.end());

    // 递归计算左右两部分的最小距离平方
    double dl_sq = closestUtil(px_left, pyl);
    double dr_sq = closestUtil(px_right, pyr);
    double d_sq = min(dl_sq, dr_sq);

    // 构建一个条带区域(strip)，包含所有与分割线距离小于 sqrt(d_sq) 的点
    vector<Point> strip;
    for (const auto &p: py)
    {
        if (abs(p.x - midPoint.x) * abs(p.x - midPoint.x) < d_sq)
        {
            strip.push_back(p);
        }
    }

    // 在条带区域内寻找更近的点对，并返回最终的最小距离平方
    return min(d_sq, stripClosest(strip, d_sq));
}

// 主函数，用于启动整个过程
double closestPair(vector<Point> &points)
{
    if (points.size() < 2)
    {
        return DBL_MAX; // 或抛出异常
    }

    vector<Point> px = points;
    vector<Point> py = points;

    // 预排序
    sort(px.begin(), px.end(), compareX);
    sort(py.begin(), py.end(), compareY);

    // 调用递归函数并返回最终的距离（非平方）
    return sqrt(closestUtil(px, py));
}

int main()
{
    vector<Point> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};

    cout << "Points: ";
    for (const auto &p: points)
    {
        cout << "(" << p.x << ", " << p.y << ") ";
    }
    cout << endl;

    double min_distance = closestPair(points);

    cout << "MinDistance: " << min_distance << endl;

    return 0;
}
