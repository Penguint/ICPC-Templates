## pengeo
 - require:
 - [x] 封装
 - [x] 测试

```cpp
namespace pengeo {
    
typedef double db;
const db PI = acos(-1.0);
const db EPS = 1e-6;

// 2D point & vector
struct P2 {
    db x, y;
    P2 operator+(const P2 b) const { return (P2){x + b.x, y + b.y}; }
};
typedef P2 v2; // define vector as alias of point

// rotate/turn
P2 rotate(P2 p, db a) {
    db x = p.x;
    db y = p.y;
    return {x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)};
}
P2 turn(P2 p, db a) { return rotate(p, a); }

// radius/degree conversion
db dtor(db d) { return d * PI / 180; }
db rtod(db r) { return r * 180 / PI; }

// pow
db pow2(db x) { return x * x; }
db pow3(db x) { return x * x * x; }

// distance
db dis(P2 p1, P2 p2) {
    db p1x = p1.x;
    db p1y = p1.y;
    db p2x = p2.x;
    db p2y = p2.y;
    return sqrt(pow2(p2x - p1x) + pow2(p1y - p2y));
}

// circle
struct circle {
    P2 o;
    db r;
};

// angle C from triangle edges
db angle(db a, db b, db c) {
    return acos((a * a + b * b - c * c) / (2 * a * b));
}

// sign negative: -1
//      zero:     0
//      positive: 1
int sign(db x) {
    if (abs(x) < EPS)
        return 0;
    else
        return x > 0 ? 1 : -1;
}

// in_triangle ------ need turn
int spc(db x, db y, db m, db b) { return y - (m * x + b) > 0; }
bool in_triangle(P2 p0, P2 p1, P2 p2, P2 p3) {
    db p0x = p0.x;
    db p0y = p0.y;
    db p1x = p1.x;
    db p1y = p1.y;
    db p2x = p2.x;
    db p2y = p2.y;
    db p3x = p3.x;
    db p3y = p3.y;

    db m1 = (p2y - p1y) / (p2x - p1x);
    db b1 = p2y - m1 * p2x;
    db m2 = (p3y - p2y) / (p3x - p2x);
    db b2 = p3y - m2 * p3x;
    db m3 = (p1y - p3y) / (p1x - p3x);
    db b3 = p1y - m3 * p1x;

    db pcx = (p1x + p2x + p3x) / 3;
    db pcy = (p1y + p2y + p3y) / 3;

    int spc1 = spc(pcx, pcy, m1, b1);
    int spc2 = spc(pcx, pcy, m2, b2);
    int spc3 = spc(pcx, pcy, m3, b3);

    int sp01 = spc(p0x, p0y, m1, b1);
    int sp02 = spc(p0x, p0y, m2, b2);
    int sp03 = spc(p0x, p0y, m3, b3);

    int s1 = 1 - spc1 - sp01;
    int s2 = 1 - spc2 - sp02;
    int s3 = 1 - spc3 - sp03;

    int s = s1 * s2 * s3;
    return s;
}

} // namespace pengeo

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