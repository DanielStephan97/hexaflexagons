/**
 * Author: Niko Hastrich
 * Date: 2020-07-26
 * License: CC0
 * Source: CP4
 * Description: Allows to add a value $d$ to all elements in a range $[l\ldots r)$ and query the sum
 * of a range as well
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */
#pragma once

#include "FenwickTree.h"

struct FTR {
	FT a, b;
	FTR(int n) : a(n), b(n) {}
	void update(int l, int r, ll d) {
		a.update(l, d);
		a.update(r, -d);
		b.update(l, -l*d);
		b.update(r, r*d);
	}
	ll p_query(int r) {
		return r ? a.query(r) * r + b.query(r) : 0;
	}
	ll query(int l, int r) {
		return p_query(r) - p_query(l);
	}
};
