#include "../utilities/template.h"

#include "../../content/data-structures/FenwickTreeRURQ.h"

static unsigned R;
int ra() {
	R *= 791231;
	R += 1231;
	return (int)(R >> 1);
}

volatile int res;
int main() {
	int N = 10;
	/*
	vi v{{0,0,1,2,3,3,3,3,3,3}};
	FTR ft(N);
	ft.update(1,4,1);
	rep(i,0,N) rep(j,i,N) assert(v[j] - (i ? v[i] : 0) == ft.query(i, j));
	*/
	vi v(N);
	FTR tr(N);
	iota(all(v), 0);
	random_shuffle(all(v), [](int x) { return ra() % x; });
	rep(i,0,N) tr.update(i, i+1, v[i]);
	rep(i,0,N) rep(j,0,N) if (i <= j) {
		int s = 0;
		rep(k,i,j) s += v[k];
		assert(s == tr.query(i,j));
	}
	rep(it,0,1000000) {
		int i = ra() % (N+1), j = ra() % (N+1);
		if (i > j) swap(i, j);
		int x = (ra() % 10) - 5;

		int r = ra() % 100;
		if (r < 50) {
			::res = tr.query(i, j);
			int s = 0;
			rep(k,i,j) s += v[k];
			assert(s == ::res);
		}
		else {
			tr.update(i, j, x);
			rep(k,i,j) v[k] += x;
		}
	}
	cout<<"Tests passed!"<<endl;
}
