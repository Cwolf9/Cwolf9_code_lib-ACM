#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;
int main() {
#ifdef LH_LOCAL
    freopen("D:in.txt", "r", stdin);
    //freopen("D:out.txt", "w", stdout);
#endif
    string s;
    while (getline(cin , s)) {
        cout << "\"" << s << "\"," << endl;
    }
    return 0;
}
