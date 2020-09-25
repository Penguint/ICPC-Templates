## pengeo
 - require:
 - [x] 封装
 - [x] 测试

```cpp
namespace pengeo {
    
// ===== basic stuff { 

using db = double;
const db EPS = 1e-6;
const db PI = acos(-1.0);

/** sgn neg: -1
 *      zero: 0
 *      pos:  1
 */
int sgn(db x) {
    if(x < -EPS) return -1;
    return x > EPS;
}

int cmp(db a, db b) { return sgn(a - b); }
struct db_less : public binary_function<db,db,bool> {
    db_less(db eps = EPS) : eps(eps) {}
    bool operator()(const db &a, const db &b) const { return cmp(a, b) == -1; }
    double eps;
};

// radius/degree conversion
db dtor(db d) { return d * PI / 180; }
db rtod(db r) { return r * 180 / PI; }

// } end basic stuff =====

// ===== 2D Point / Vector {

struct p2 {
    db x, y;
    p2() {}
    p2(db x, db y) : x(x), y(y) {}
    p2 operator+(const p2 b) const { return p2(x+b.x, y+b.y); }
    p2 operator-(const p2 b) const { return p2(x-b.x, y-b.y); }
    p2 operator*(const db k) const { return p2(x*k, y*k); }
    p2 operator/(const db k) const { return p2(x/k, y/k); } 
    bool operator<(const p2 b) const {
        if (cmp(y, b.y) != 0) return cmp(y, b.y) < 0;
        return cmp(x, b.x) < 0;
    }
    bool operator==(const p2 b) const { return cmp(x, b.x) == 0 && cmp(y, b.y) == 0; }
    bool operator>(const p2 b) const { return !operator<(b) && !operator==(b); }
    db norm2() { return x*x+y*y; }
    db norm() { return sqrt(norm2()); }
    p2 unit() { return (*this) / norm(); }
    p2 rot90() { return p2(-y, x); } // counter-clockwise
    p2 rotate(db a) { return p2(x*cos(a)-y*sin(a), x*sin(a)+y*cos(a)); }
    auto turn = rotate;
};
using v2 = p2; // alias point to vector

istream &operator>>(istream &in, p2 &p) {
    in >> p.x >> p.y;
    return in;
}
ostream &operator<<(ostream &out, p2 &p){
    out << '(' << p.x << ',' << p.y << ')';
    return out;
}
struct Hashp2 {
    size_t operator()(const p2 &p) const {
        return (hash<int>()((int)(p.x * 1e6))<<13)^hash<int>()((int)(p.y * 1e6));
    }
};

db dis(p2 a, p2 b) { return (a-b).norm(); }
db dot(p2 a, p2 b) { return a.x*b.x+a.y*b.y; }
db det(p2 a, p2 b) { return a.x*b.y-a.y*b.x; } // norm of cross vector, area of parallelogram
p2 point_proj_line(p2 p, p2 a, p2 b) { return a + (b-a)*dot(p-a,b-a)/dot(b-a,b-a); }
db rad(p2 a, p2 b){ // 向量夹角 a -> b
    return atan2(det(a,b),dot(a,b));
}
db area(p2 a, p2 b) { return det(a, b); } // 平行四边形有向面积

// } end 2D Point / Vector =====

// ===== 2D Line {

struct Line2 {
    p2 a,b;
    Line2(){}
    Line2(p2 a, p2 b) : a(a), b(b) {}
};

inline bool is_range_cross(db a1, db a2, db b1, db b2) {
    return cmp(max(min(a1, a2), min(b1, b2)), min(max(a1, a2), max(b1, b2))) <= 1; // contains touch point
}

inline bool is_rect_cross(const p2 &p1, const p2 &p2, const p2 &q1, const p2 &q2) {
    return is_range_cross(p1.x, p2.x, q1.x, q2.x) &&
           is_range_cross(p1.y, p2.y, q1.y, q2.y);
}

inline bool is_same_side(Line2 l, p2 a, p2 b) {
    return sgn(det(l.b - l.a, a - l.a)) * sgn(det(l.b - l.a, b - s.a)) <= 0;
}

inline bool is_segment_cross(Line2 a, Line2 b) {
    return is_rect_cross(a.a, a.b, b.a, b.b) && // 快速排斥实验
           is_same_side(a, b.a, b.b) && // 跨立实验
           is_same_side(b, a.a, a.b);
}

p2 intersection(Line2 a, Line2 b) {
    db t = det((b.b - b.a), (a.a - b.a)) / det((a.b - a.a), (b.b - b.a));
    return a.a + (a.b - a.a) * t;
}

// } end 2D Line =====

// ===== Polygon {

db area(vector<p2> p) { // 多边形有向面积
    db s = 0;
    for (int i=0;i<(int)p.size();i++)
        s += det(p[i],p[(i+1)%p.size()]);
    return s/2;
}
vector<p2> convex(vector<p2> p) { // 凸包 convex hull
    // todo ...
}

// } end Polygon =====

// ===== Triagle {

db area(db a, db b, db c){ // 三角形无向面积
    db p = (a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}
db angleC(db a, db b, db c) { // angle C
    return acos((a*a+b*b-c*c)/(2*a*b));
}

p2 gravityCenter(p2 a,p2 b,p2 c){ // 重心
    return (a+b+c)/3;
}
p2 inCenter(p2 a,p2 b,p2 c){ // 内心
    db x = (b-c).norm(), y = (c-a).norm(), z = (a-b).norm();
    return (a*x+b*y+c*z)/(x+y+z);
}
p2 circumCenter(p2 a,p2 b,p2 c){ // 外心
    p2 bb = b - a, cc = c - a;
    db dbb = bb.norm2(), dcc = cc.norm2(), d = 2*det(bb, cc);
    return a - p2(bb.y*dcc-cc.y*dbb, cc.x*dbb-bb.x*dcc)/d;
}
p2 othroCenter(p2 a,p2 b,p2 c){ // 垂心
    p2 ba = b - a, ca = c - a, bc = b - c;
    db Y = ba.y*ca.y*bc.y,
    A = ca.x*ba.y-ba.x*ca.y,
    x0 = (Y+ca.x*ba.y*b.x-ba.x*ca.y*c.x)/A,
    y0 = -ba.x*(x0-c.x)/ba.y+ca.y;
    return {x0, y0};
}

// } end Triangle =====

// ===== Circle {

struct Circle {
    p2 o;
    db r;
    Circle() {}
    Circle(p2 o,db r) : o(o), r(r) {}
};

int typeCC(Circle a, Circle b) { //公切线个数
    double d = dis(a.o,b.o);
    if (sgn(d-(a.r+b.r))==1) return 4; // 相离
    if (sgn(d-(a.r+b.r))==0) return 3; // 外切
    if (sgn(d-abs(a.r-b.r))==1) return 2; // 相交
    if (sgn(d-abs(a.r-b.r))==0) return 1; // 内切
    return 0; // 内含
}
vector<p2> isCL(Circle c, p2 a, p2 b) { // 直线与圆交点
    p2 m = point_proj_line(c.o,a,b);
    if (sgn(dis(c.o,m)-c.r)==1) return {};
    double d = sqrt(c.r*c.r-(m-c.o).norm2());
    p2 e = (b-a).unit();
    return {m-e*d,m+e*d}; // along dir: a -> b
}
vector<p2> tanCP(Circle c, p2 p){ // 点到圆的切点
    db d = dis(c.o,p);
    if (sgn(d-c.r)<=0) return {};
    db x = c.r*c.r/d;
    p2 e = (p-c.o).unit(), m = c.o+e*x;
    e = e.rot90();
    d = sqrt(c.r*c.r-x*x);
    return {m-e*d,m+e*d}; // a counter-clock wise
}

vector<p2> isCC(Circle a, Circle b){ // 两圆交点 need to check if same circle 相等会返回(nan,nan)
    if(typeCC(a,b)%4==0) return {};
    double d = min(dis(a.o,b.o),a.r+b.r);
    double x = (a.r*a.r+d*d-b.r*b.r)/(2.0*d);
    d = sqrt(a.r*a.r-x*x);
    p2 e = (b.o-a.o).unit(), m = a.o+e*x;
    e = e.rot90();
    return {m-e*d,m+e*d}; // a counter-clock wise
}
vector<Line2> extanCC(Circle a, Circle b){ // 两圆外切线
    vector<Line2> res;
    if(sgn(a.r-b.r)==0){
        p2 d = (b.o-a.o).unit().rot90() * a.r;
        res.push_back({a.o+d,b.o+d}), res.push_back({a.o-d,b.o-d});
    }
    else{
        p2 p = (b.o*a.r-a.o*b.r)/(a.r-b.r);//god
        vector<p2> ps = tanCP(a,p), qs = tanCP(b,p);
        for(int i=0;i<(int)min(ps.size(),qs.size());i++)
            res.push_back({ps[i],qs[i]}); // a counter-clock wise
    }
    return res;
}
vector<Line2> intanCC(Circle a, Circle b){ // 两圆内切线
    vector<Line2> res;
    p2 p = (b.o*a.r+a.o*b.r)/(a.r+b.r);//god
    vector<p2> ps = tanCP(a,p), qs = tanCP(b,p);
    for(int i=0;i<(int)min(ps.size(),qs.size());i++)
        res.push_back({ps[i],qs[i]}); // a counter-clock wise
    return res;
}
vector<Line2> tanCC(Circle a, Circle b){ // 两圆切线 need to check if same circle 相等会返回(nan,nan)  
    vector<Line2> res;
    int type = typeCC(a,b);
    if(type>=2){
        vector<Line2> r = extanCC(a,b);
        for(Line2 l:r) res.push_back(l);
    }
    if(type==4){
        vector<Line2> r = intanCC(a,b);
        for(Line2 l:r) res.push_back(l);
    }
    if(type==3||type==1){
        p2 p = isCC(a,b)[0];
        res.push_back({p,p + (b.o - a.o).rot90()}); // one tangent point, a counter-clock wise to a.o->b.o
    }
    return res;
}

db areaCT(db r, p2 a, p2 b){ // directed intersect area of circle {(0,0),r} and {(0,0),a->b}
    vector<p2> is = isCL({p2(0,0),r},a,b);
    if(is.empty()) return r*r*rad(a,b)/2;
    bool d1 = sgn(a.norm2()-r*r)==1, d2 = sgn(b.norm2()-r*r)==1;
    if(d1&&d2){
        if(sgn(dot(is[0]-a,is[0]-b))<=0) return r*r*(rad(a,is[0])+rad(is[1],b))/2 + det(is[0],is[1])/2;
        else return r*r*rad(a,b)/2;
    }
    if(d1) return (r*r*rad(a,is[0]) + det(is[0],b)) / 2;
    if(d2) return (det(a,is[1]) + r*r*rad(is[1],b)) / 2;
    return det(a,b)/2;
}

db areaCPolygon(Circle c, vector<p2> p){
    db ans = 0;
    for(int i=0;i<(int)p.size();i++){
        ans += areaCT(c.r,p[i]-c.o,p[(i+1)%p.size()]-c.o);
    }
    return ans;
}

Circle min_circle(vector<p2> p){ // 最小圆覆盖
    random_shuffle(p.begin(),p.end());
    int n = p.size();
    p2 o = p[0]; db r = 0;
    for(int i=1;i<n;i++) if(dis(p[i],o)>r+EPS){
        for(int j=0;j<i;j++) if(dis(p[j],o)>r+EPS){
            for(int k=0;k<i;k++) if(dis(p[k],o)>r+EPS){
                o = circumCenter(p[i],p[j],p[k]);
                r = dis(o,p[i]);
            }
        }
    }
    return {o,r};
}

Circle inversionCC(Circle c,p2 o,db r){ // 圆关于(反演中心o,反演半径r)的反演
    ///disjoint version
    db d = dis(o,c.o);
    assert(sgn(d-c.r)!=0);
    db x = r * r / (d - c.r) / 2.0;
    db y = r * r / (d + c.r) / 2.0;
    Circle res;
    res.r = abs(x - y);
    res.o = o + (c.o-o) * (x + y) / d;
    if(c.o==o) res.o = o;
    return res;
}
Circle inversionLC(p2 a,p2 b,p2 o,db r){ // 直线关于(反演中心o,反演半径r)的反演
    assert(sgn(det(b-a,o-a))!=0);
    db d = det(b-a,o-a) / dis(a,b);
    Circle res;
    res.r = r * r / abs(d) / 2.0;
    p2 e = (b-a).rot90().unit() * res.r;
    res.o = d > 0 ? o - e : o + e;
    return res;
}

// } end Circle =====

// ===== 3D Point / Vector {

struct p3 {
    db x, y, z;
    p3() {}
    p3(db x, db y, db z) : x(x), y(y), z(z) {}
    p3 operator+(const p3 b) const { return p3(x+b.x, y+b.y, z+b.z); }
    p3 operator-(const p3 b) const { return p3(x-b.x, y-b.y, z-b.z); }
    p3 operator*(const db k) const { return p3(x*k, y*k, z*k); }
    p3 operator/(const db k) const { return p3(x/k, y/k, z/k); } 
    db norm2() { return x*x+y*y+z*z; }
    db norm() { return sqrt(norm2()); }
    p3 unit() { return (*this)/norm(); }
};

db dis(p3 a, p3 b) { return (a-b).norm(); }
db dot(p3 a, p3 b) { return a.x*b.x+a.y*b.y+a.z*b.z; }
p3 cross(p3 a, p3 b) { return p3(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x); }
db vol(p3 a, p3 b, p3 c) { return abs(dot(a, cross(b, c))); }
db dis_p_plain(p3 p, p3 a, p3 b, p3 c) {return vol(p - a, b - a, c - a)/area(b - a, c - a); }

bool is_same_plain(p3 a, p3 b, p3 c) { return sgn(vol(a, b, c)) == 0; }

// } end 3D Point / Vector =====

// ===== 3D Line {

struct Line3 {
    p3 a, b;
    Line3(p3 a, p3 b) : a(a), b(b) {}
}

// } end 3D Line =====

} // namespace pengeo

using namespace pengeo;

struct node_t {
    int lo, hi, rot_tag = 0;
    pengeo::p2 v = {0, 0};

    void rotate(int tag) {
        rot_tag = (rot_tag + tag) % 360;
        v = pengeo::rotate(v, pengeo::dtor(tag));
    }

    void pushdown(node_t &lhs, node_t &rhs) {
        if (rot_tag == 0)
            return;
        lhs.rotate(rot_tag);
        rhs.rotate(rot_tag);
        rot_tag = 0;
    }

    void maintain(node_t &lhs, node_t &rhs) { v = lhs.v + rhs.v; }
};
```