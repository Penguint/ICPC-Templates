## pengeo
 - require:
 - [x] 封装
 - [x] 测试

```cpp
namespace pengeo {
    
/* ====== basic stuff ====== */

using db = double;
const db PI = acos(-1.0);
const db EPS = 1e-6;

// sgn neg: -1
//     zero: 0
//     pos:  1
int sgn(db x){
    if(x < -EPS) return -1;
    return x > EPS;
}

int cmp(db a, db b) { return sgn(a - b); }

// radius/degree conversion
db dtor(db d) { return d * PI / 180; }
db rtod(db r) { return r * 180 / PI; }

/* ===== end basic stuff ===== */

struct p2 {
    db x, y;
    p2() {}
    p2(db x, db y) : x(x), y(y) {}
    p2 operator+(const p2 b) const { return p2(x + b.x, y + b.y); }
    p2 operator-(const p2 b) const { return p2(x - b.x ,y - b.y); }
    p2 operator*(const db k) const { return p2(x * k, y * k); }
    p2 operator/(const db k) const { return p2(x / k, y / k); } 
    bool operator<(const p2 b) const {
        if (cmp(y, b.y) != 0) return cmp(y, b.y) < 0;
        return cmp(x, b.x) < 0;
    }
    bool operator==(const p2 b) const { return cmp(x, b.x) == 0 && cmp(y, b.y) == 0; }
    bool operator>(const p2 b) const { return !operator<(b) && !operator==(b); }
    db norm2() { return x * x + y * y; }
    db norm() { return sqrt(norm2()); }
    p2 unit() { return (*this) / norm(); }
    p2 rot90() { return p2(-y, x); } // counter-clockwise
    p2 rotate(db a) { return p2(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
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

db area(db a, db b, db c){
    db p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}
// angle C from triangle edges
db angle(db a, db b, db c) {
    return acos((a * a + b * b - c * c) / (2 * a * b));
}
db dot(p2 a, p2 b){ return a.x * b.x + a.y * b.y; }
db det(p2 a, p2 b){ return a.x * b.y - a.y * b.x; }
db dist(p2 a, p2 b){ return (a - b).norm(); }
p2 point_proj_line(p2 p, p2 a, p2 b){ return a + (b-a)*dot(p-a,b-a)/dot(b-a,b-a); }
db rad(p2 a,p2 b){ // 向量夹角 a -> b
    return atan2(det(a,b),dot(a,b));
}
db area(vector<p2> p) { // 多边形有向面积
    db s = 0;
    for (int i = 0; i < (int)p.size(); i++)
        s += det(p[i], p[(i + 1) % N]);
    return s
}


// circle
struct Circle {
    p2 o;
    db r;
    Circle() {}
    Circle(p2 o,db r) : o(o), r(r) {}
};

int typeCC(Circle a, Circle b) { //公切线个数
    double d = dist(a.o,b.o);
    if (sgn(d-(a.r+b.r))==1) return 4; // 相离
    if (sgn(d-(a.r+b.r))==0) return 3; // 外切
    if (sgn(d-abs(a.r-b.r))==1) return 2; // 相交
    if (sgn(d-abs(a.r-b.r))==0) return 1; // 内切
    return 0; // 内含
}
vector<p2> isCL(Circle c, p2 a, p2 b) { // 直线与圆交点
    p2 m = point_proj_line(c.o,a,b);
    if (sgn(dist(c.o,m)-c.r)==1) return {};
    double d = sqrt(c.r*c.r-(m-c.o).norm2());
    p2 e = (b-a).unit();
    return {m-e*d,m+e*d}; // along dir: a -> b
}
vector<p2> tanCP(Circle c, p2 p){ // 点到圆的切点
    db d = dist(c.o,p);
    if (sgn(d-c.r)<=0) return {};
    db x = c.r*c.r/d;
    p2 e = (p-c.o).unit(), m = c.o+e*x;
    e = e.rot90();
    d = sqrt(c.r*c.r-x*x);
    return {m-e*d,m+e*d}; // a counter-clock wise
}

struct Line {
    p2 a,b;
    Line(){}
    Line(p2 a, p2 b):a(a),b(b){}
};
vector<p2> isCC(Circle a,Circle b){ // 两圆交点 need to check if same circle 相等会返回(nan,nan)
    if(typeCC(a,b)%4==0) return {};
    double d = min(dist(a.o,b.o),a.r+b.r);
    double x = (a.r*a.r+d*d-b.r*b.r)/(2.0*d);
    d = sqrt(a.r*a.r-x*x);
    p2 e = (b.o-a.o).unit(), m = a.o+e*x;
    e = e.rot90();
    return {m-e*d,m+e*d}; // a counter-clock wise
}
vector<Line> extanCC(Circle a,Circle b){ // 两圆外切线
    vector<Line> res;
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
vector<Line> intanCC(Circle a,Circle b){ // 两圆内切线
    vector<Line> res;
    p2 p = (b.o*a.r+a.o*b.r)/(a.r+b.r);//god
    vector<p2> ps = tanCP(a,p), qs = tanCP(b,p);
    for(int i=0;i<(int)min(ps.size(),qs.size());i++)
        res.push_back({ps[i],qs[i]}); // a counter-clock wise
    return res;
}
vector<Line> tanCC(Circle a,Circle b){ // 两圆切线 need to check if same circle 相等会返回(nan,nan)  
    vector<Line> res;
    int type = typeCC(a,b);
    if(type>=2){
        vector<Line> r = extanCC(a,b);
        for(Line l:r) res.push_back(l);
    }
    if(type==4){
        vector<Line> r = intanCC(a,b);
        for(Line l:r) res.push_back(l);
    }
    if(type==3||type==1){
        p2 p = isCC(a,b)[0];
        res.push_back({p,p + (b.o - a.o).rot90()}); // one tangent point, a counter-clock wise to a.o->b.o
    }
    return res;
}

db areaCT(db r,p2 a,p2 b){ // directed intersect area of circle {(0,0),r} and {(0,0),a->b}
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

db areaCPolygon(Circle c,vector<p2> p){
    db ans = 0;
    for(int i=0;i<(int)p.size();i++){
        ans += areaCT(c.r,p[i]-c.o,p[(i+1)%p.size()]-c.o);
    }
    return ans;
}

p2 gravityCenter(p2 a,p2 b,p2 c){ // 重心
    return (a + b + c) / 3;
}
p2 inCenter(p2 a,p2 b,p2 c){ // 内心
    double x = (b-c).norm(), y = (c-a).norm(), z = (a-b).norm();
    return (a * x + b * y + c * z) / (x + y + z);
}
p2 circumCenter(p2 a,p2 b,p2 c){ // 外心
    p2 bb = b - a, cc = c - a;
    db dbb = bb.norm2(), dcc = cc.norm2(), d = 2 * det(bb,cc);
    return a - p2(bb.y * dcc - cc.y * dbb, cc.x * dbb - bb.x * dcc) / d;
}
p2 othroCenter(p2 a,p2 b,p2 c){ // 垂心
    p2 ba = b - a, ca = c - a, bc = b - c;
    db Y = ba.y * ca.y * bc.y,
    A = ca.x * ba.y - ba.x * ca.y,
    x0 = (Y + ca.x * ba.y * b.x - ba.x * ca.y * c.x) / A,
    y0 = -ba.x * (x0 - c.x) / ba.y + ca.y;
    return {x0, y0};
}

Circle min_circle(vector<p2> p){ // 最小圆覆盖
    random_shuffle(p.begin(),p.end());
    int n = p.size();
    p2 o = p[0]; db r = 0;
    for(int i=1;i<n;i++) if(dist(p[i],o)>r+EPS){
        for(int j=0;j<i;j++) if(dist(p[j],o)>r+EPS){
            for(int k=0;k<i;k++) if(dist(p[k],o)>r+EPS){
                o = circumCenter(p[i],p[j],p[k]);
                r = dist(o,p[i]);
            }
        }
    }
    return {o,r};
}

Circle inversionCC(Circle c,p2 o,db r){ // 圆关于(反演中心o,反演半径r)的反演
    ///disjoint version
    db d = dist(o,c.o);
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
    db d = det(b-a,o-a) / dist(a,b);
    Circle res;
    res.r = r * r / abs(d) / 2.0;
    p2 e = (b-a).rot90().unit() * res.r;
    res.o = d > 0 ? o - e : o + e;
    return res;
}

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