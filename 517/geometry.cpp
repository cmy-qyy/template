//浮点数比较允许eps误差，根据不同题目的精度要求调节eps
const double eps = 1e-8;
int sgn(double x) {
        return x < -eps ? -1 : x > eps;
}
struct Point;
typedef Point Vector;
struct Point 
{
    double x, y;
    void in() {
        scanf("%lf%lf", &x, &y);
    }
    void print() {
        printf("%.2lf %.2lf\n", x, y);
    }
    Point(double x = 0, double y = 0) : x(x), y(y) {
    }
    //逆时针旋转ang
    inline Vector rotate(double ang) {
        return Vector(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang));
    }
    inline double dot(const Vector &a) {
        return x * a.x + y * a.y;
    }
    inline bool operator == (const Point &a) const {
        return sgn(x - a.x) == 0 && sgn(y - a.y) == 0;
    }
    inline bool operator < (const Point &a) const {
        return sgn(x - a.x) < 0 || sgn(x - a.x) == 0 && sgn(y - a.y) < 0;
    }
    inline Vector operator + (const Vector &a) const {
        return Vector(x + a.x, y + a.y);
    }
    inline Vector operator - (const Vector &a) const {
        return Vector(x - a.x, y - a.y);
    }
    inline double operator * (const Vector &a) const {
        return x * a.y - y * a.x;
    }
    inline Vector operator * (double t) const {
        return Vector(x * t, y * t);
    }
    inline double vlen() {
        return sqrt(x * x + y * y);
    }
    inline Vector norm() {
        return Point(-y, x);
    }

};

struct Seg 
{
    Point s, e;
    Seg() {
    }
    Seg(Point s, Point e): s(s), e(e) {
    }
};
struct Line
{
    int a, b, c;
};

double cross(Point a, Point b, Point c) 
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
//判断两个平行或者共线的向量是否同向
bool same_dir(Vector a, Vector b) {						
    return sgn(a.x * b.y - b.x * a.y) == 0 && sgn(a.x * b.x) >= 0 && sgn(a.y * b.y) >= 0;
}

bool dot_on_seg(Point p, Seg L) {
    return sgn((L.s - p) * (L.e - p)) == 0 && sgn((L.s - p).dot(L.e - p)) <= 0;
}

double ppdis(Point a, Point b) {							
    return sqrt((a - b).dot(a - b));
}

//点到直线距离
double pldis(Point p,Point l1,Point l2) {					
    return fabs(cross(p,l1,l2)) / ppdis(l1,l2);
} 
double pldis(Point p, Line ln)  {								
    return fabs(ln.a * p.x + ln.b * p.y + ln.c) / sqrt(ln.a * ln.a + ln.b * ln.b);
}

bool intersect(Point P, Vector v, Point Q, Vector w, Point &ret) {
    Vector u = P - Q;
    if(sgn(v * w) == 0) return false;
    double t = w * u / (v * w);
    ret = P + v * t;
    return true;
} 
//肯定有交点调用此函数
Point intersect(Point P, Vector v, Point Q, Vector w) {
    Point ret;
    Vector u = P - Q;
    double t = w * u / (v * w);
    ret = P + v * t;
    return ret;
}

//点到直线的垂足(最近点)
Point ptoline(Point p, Seg l) {
    Point vec = l.s - l.e;
    return intersect(p, vec.norm(), l.s, vec);
}

//点到线段的最近点
Point ptoseg(Point p, Seg l) {
    Point norm = (l.s - l.e).norm();
    if(sgn(norm * (p - l.s)) * sgn(norm * (p - l.e)) > 0) {
        double sa = ppdis(p, l.s);
        double sb = ppdis(p, l.e);
        return sgn(sa - sb) < 0 ? l.s : l.e;
    }
    return intersect(p, norm, l.s, l.e - l.s);
}

//快速判断线段是否相交
bool segcross(Point p1, Point p2, Point q1, Point q2) {
    return (
            std::min(p1.x, p2.x) <= std::max(q1.x, q2.x) &&
            std::min(q1.x, q2.x) <= std::max(p1.x, p2.x) &&
            std::min(p1.y, p2.y) <= std::max(q1.y, q2.y) &&
            std::min(q1.y, q2.y) <= std::max(p1.y, p2.y) && /* 跨立实验 */
            cross(p1, q2, q1) * cross(p2, q2, q1) <= 0 && 
            cross(q1, p2, p1) * cross(q2, p2, p1) <= 0  /* 叉积相乘判方向 */
           );
}

// 水平序, 注意两倍空间
struct Convex_Hull {
    static const int N = 100010;
    Point p[2 * N];
    int n;
    void init() {
        n = 0;
    }
    void in() {
        p[n].in();
        n++;
    }
    inline void push_back(const Point &np) {
        p[n++] = np;
    }
    void gao() {
        if(n < 3) {
            return ;
        }
        std::sort(p, p + n);
        std::copy(p, p + n - 1, p + n);
        std::reverse(p + n, p + 2 * n - 1);
        int m = 0, top = 0;
        for(int i = 0; i < 2 * n - 1; i++) {
            while(top >= m + 2 && sgn((p[top - 1] - p[top - 2]) * (p[i] - p[top - 2])) <= 0) {
                top --;
            }
            p[top++] = p[i];
            if(i == n - 1) {
                m = top - 1;
            }
        }
        n = top - 1;
    }
    void print() {
        for(int i = 0; i < n; i++) {
            p[i].print();
        }
    }
    double get_area() {
        double ret = 0;
        Point ori(0, 0);
        for(int i = 0; i < n; i++) {
            ret += (p[i] - ori) * (p[i + 1] - ori);
        }
        return fabs(ret) / 2;
    }
    bool in_convex(Point pt) {
        if(sgn((p[1]-p[0])*(pt-p[0])) <= 0 || sgn((p[n-1]-p[0])*(pt-p[0])) >= 0) {
            return false;
        }
        int l = 1, r = n - 2, best = -1;
        while(l <= r) {
            int mid = l + r >> 1;
            int f = sgn((p[mid]-p[0])*(pt-p[0]));
            if(f >= 0) {
                best = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return     sgn((p[best+1]-p[best])*(pt-p[best])) > 0;
    }

}convex;
