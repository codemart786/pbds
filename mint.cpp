//Date: 02-09-22 //Author: Rishabh Paul
//Taken from codeforces, useful in modular arithmetic

#include<bits/stdc++.h>
using namespace std;
using i64 = long long;
const int P = 1e9 + 7;

template<class T>
inline T power(T a, i64 b) {
    T res = 1;
    for (; b ; b >>= 1, a *= a)
        if (b & 1) res *= a;
    return res;
}

inline int norm(int &x) {
    if (x < 0) x += P;
    if (x >= P) x -= P;
    return x;
}

struct Z {
    int x;
	Z(int _x = 0) : x(norm(_x)) {}
	inline Z operator-() const {
		if (!x) return 0;
		return Z(P - x);
	}
	inline Z &operator+=(const Z &rhs) {
		x += rhs.x;
		if (x >= P) x -= P;
		return *this;
	}
	inline Z &operator-=(const Z &rhs) {
		x -= rhs.x;
		if (x < 0) x += P;
		return *this;
	}
	inline Z &operator*=(const Z &rhs) {
		x = 1ull * x * rhs.x % P;
		return *this;
	}
	inline Z inv() const {
		return power(*this, P - 2);
	}
	inline Z &operator/=(const Z &rhs) {
		*this *= rhs.inv();
		return *this;
	}
	inline friend Z operator+(const Z &lhs, const Z &rhs) {
		Z res = lhs;
		return res += rhs, res;
	}
	inline friend Z operator-(const Z &lhs, const Z &rhs) {
		Z res = lhs;
		return res -= rhs, res;
	}
	inline friend Z operator*(const Z &lhs, const Z &rhs) {
		Z res = lhs;
		return res *= rhs, res;
	}
	inline friend Z operator/(const Z &lhs, const Z &rhs) {
		Z res = lhs;
		return res /= rhs, res;
	}
};


int main () {

    return 0;
}
