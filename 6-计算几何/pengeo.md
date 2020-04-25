## pengeo
 - [x] 封装
 - [x] 测试

```cpp
namespace pengeo {
const double PI = acos(-1.0);
const double EPS = 1e-6;
struct p2 {
    double x, y;
    p2 operator+(const p2 b) const { return (p2){x + b.x, y + b.y}; }
};
typedef p2 v2; // define vector as alias of point
p2 rotate(const p2 p, const double a) {
    double x = p.x * cos(a) - p.y * sin(a);
    double y = p.x * sin(a) + p.y * cos(a);
    return (p2){x, y};
}
double dtor(double d) { return d * PI / 180; }
double rtod(double r) { return r * 180 / PI; }
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