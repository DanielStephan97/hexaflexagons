/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

#include "euclid.h"

using ll = long long;
template<int mod>
struct TMod {
	ll x;
	TMod(ll xx) : x(xx) {}
	TMod operator+(TMod b) { return (x + b.x) % mod; }
	TMod operator-(TMod b) { return (x - b.x + mod) % mod; }
	TMod operator*(TMod b) { return (x * b.x) % mod; }
	TMod operator/(TMod b) { return *this * invert(b); }
	TMod invert(TMod a) {
		ll x, y, g = euclid(a.x, mod, x, y);
		assert(g == 1); return (x + mod) % mod;
		// for prime mod use
		// return a.pow(mod - 2);
	}
	TMod pow(ll e) {
		if (!e) return 1;
		TMod r = this->pow(e / 2); r = r * r;
		return e&1 ? *this * r : r;
	}
};
// change to something else
using Mod = TMod<17>;
