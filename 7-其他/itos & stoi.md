## itos & stoi
 - require: 
 - [x] 封装
 - [ ] 测试
  
```cpp
namespace penalg {

string itos(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}

int stoi(string s) {
    stringstream ss;
    ss << s;
    int res;
    ss >> res;
    return res;
}

} // namespace penalg
```
