#include <cstdio>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <bitset>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const double eps = 1e-10;
const double PI = acos (-1.0);
int dcmp(double x) { //三态函数，减少精度问题
    if (fabs (x) < eps) return 0;
    else    return x < 0 ? -1 : 1;
}
struct Point { //点的定义
    double x, y;
    Point () {}
    Point (double x, double y) : x (x), y (y) {}
    Point operator + (const Point &r) const { //向量加法
        return Point (x + r.x, y + r.y);
    }
    Point operator - (const Point &r) const { //向量减法
        return Point (x - r.x, y - r.y);
    }
    Point operator * (double p) const { //向量乘以标量
        return Point (x * p, y * p);
    }
    Point operator / (double p) const { //向量除以标量
        return Point (x / p, y / p);
    }
    bool operator < (const Point &r) const { //点的坐标排序
        return x < r.x || (x == r.x && y < r.y);
    }
    bool operator == (const Point &r) const { //判断同一个点
        return dcmp (x - r.x) == 0 && dcmp (y - r.y) == 0;
    }
};
typedef Point Vector; //向量的定义
Point read_point(void) { //点的读入
    double x, y;
    scanf ("%lf%lf", &x, &y);
    return Point (x, y);
}
double dot(Vector A, Vector B) { //向量点积
    return A.x * B.x + A.y * B.y;
}
double cross(Vector A, Vector B) { //向量叉积
    return A.x * B.y - A.y * B.x;
}
double polar_angle(Vector A) { //向量极角
    return atan2 (A.y, A.x);
}
double Length(Vector A) { //向量长度，点积
    return sqrt (dot (A, A));
}
double angle(Vector A, Vector B) { //向量转角，逆时针，点积
    return acos (dot (A, B) / Length (A) / Length (B));
}
Vector rotate(Vector A, double rad) { //向量旋转，逆时针
    return Vector (A.x * cos (rad) - A.y * sin (rad), A.x * sin (rad) + A.y * cos (rad));
}
Vector nomal(Vector A) { //向量的单位法向量
    double len = Length (A);
    return Vector (-A.y / len, A.x / len);
}


Point line_line_inter(Point p, Vector V, Point q, Vector W){ //两直线交点，参数方程
    Vector U = p - q;
    double t = cross (W, U) / cross (V, W);
    return p + V * t;
}


double point_to_line(Point p, Point a, Point b){ //点到直线的距离，两点式
    Vector V1 = b - a, V2 = p - a;
    return fabs (cross (V1, V2)) / Length (V1);
}
double point_to_seg(Point p, Point a, Point b){ //点到线段的距离，两点式
    if (a == b) return Length (p - a);
    Vector V1 = b - a, V2 = p - a, V3 = p - b;
    if (dcmp (dot (V1, V2)) < 0) return Length (V2);
    else if (dcmp (dot (V1, V3)) > 0) return Length (V3);
    else return fabs (cross (V1, V2)) / Length (V1);
}
Point point_line_proj(Point p, Point a, Point b){ //点在直线上的投影，两点式
    Vector V = b - a;
    return a + V * (dot (V, p - a) / dot (V, V));
}
bool can_seg_seg_inter(Point a1, Point a2, Point b1, Point b2){ //判断线段相交，两点式
    double c1 = cross (a2 - a1, b1 - a1), c2 = cross (a2 - a1, b2 - a1),
           c3 = cross (b2 - b1, a1 - b1), c4 = cross (b2 - b1, a2 - b1);
    return dcmp (c1) * dcmp (c2) < 0 && dcmp (c3) * dcmp (c4) < 0;
}
bool can_line_seg_inter(Point a1, Point a2, Point b1, Point b2){ //判断直线与线段相交，两点式
    double c1 = cross (a2 - a1, b1 - a1), c2 = cross (a2 - a1, b2 - a1);
    return dcmp (c1 * c2) <= 0;
}
bool on_seg(Point p, Point a1, Point a2){ //判断点在线段上，两点式
    return dcmp (cross (a1 - p, a2 - p)) == 0 && dcmp (dot (a1 - p, a2 - p)) < 0;
}

struct Line2 {
    double x1, x2;
    Line2 () {}
    Line2 (double x1, double x2) : x1 (x1), x2 (x2)  {}
    bool operator < (const Line2 &r) const {
        return x1 < r.x1;
    }
};

struct Line{
    Point a, b;
    Line () {}
    Line (Point a, Point b) : a (a), b (b) {}
};

int main(){
    Line h, p;
    double x1, x2, y;
    int n;
    Point p1, p2;
    while (~scanf ("%lf%lf%lf", &x1, &x2, &y)){
        if (dcmp (x1) == 0 && dcmp (x2) == 0 && dcmp (y) == 0) break;
        h.a = Point (x1, y);    h.b = Point (x2, y);
        scanf ("%lf%lf%lf", &x1, &x2, &y);
        p.a = Point (x1, y);    p.b = Point (x2, y);
        scanf ("%d", &n);
        vector<Line2> xs;
        for(int i = 0; i < n; ++i){
            scanf ("%lf%lf%lf", &x1, &x2, &y);
            if(dcmp(y - h.a.y) >= 0 || dcmp(y - p.a.y) <= 0) continue;
            p1 = Point(x1, y); p2 = Point(x2, y);
            x1 = line_line_inter(h.b, h.b-p1, p.b, p.b-p.a).x;
            x2 = line_line_inter(h.a, h.a-p2, p.b, p.b-p.a).x;
            if(dcmp(x1-x2) < 0) xs.push_back(Line2(x1,x2));
        }
        xs.push_back(Line2(p.b.x, p.b.x));
        sort(xs.begin(), xs.end());
        double left = p.a.x, ans = 0;
        int len = xs.size();
        for(int i = 0; i < len; ++i){
            Line2 buf = xs[i];
            x1 = buf.x1 , x2 = buf.x2;
            if((x1 - left) > ans) ans = x1 - left;
            if(x2 > left){
                left = x2;
                if(left >= p.b.x) break;
            } 
        }
        if(dcmp(ans) == 0) printf("No View\n");
        else printf("%.2f\n", ans);
    }
    return 0;
}
