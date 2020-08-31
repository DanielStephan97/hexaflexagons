#include "../utilities/template.h"

#include "../../content/number-theory/ModularArithmetic.h"

const int modprime = 257, modnonprime = 259;
using ModPrime = TMod<modprime>;
using ModNonPrime = TMod<modnonprime>;
int main() {
	{
		rep(a,0,modprime) rep(b,1,modprime) {
			ModPrime ma(a), mb(b);
			auto mc = ma / mb;
			assert((mc * mb).x == a);
		}
		ModPrime a = 2;
		ll cur=1;
		rep(i, 0, modprime - 1) {
			assert((a.pow(i)).x == cur);
			cur = (cur * 2) % modprime;
			// cout << i << ": " << (a ^ i).x << endl;
		}
	}


	{
		rep(a,0,modnonprime) rep(b,1,modnonprime) {
			if (max(gcd(a, modnonprime), gcd(b,modnonprime)) == 1) {
				ModNonPrime ma(a), mb(b);
				auto mc = ma / mb;
				assert((mc * mb).x == a);
			}
		}
		ModNonPrime a = 2;
		ll cur=1;
		rep(i, 0, modnonprime - 1) {
			assert((a.pow(i)).x == cur);
			cur = (cur * 2) % modnonprime;
			// cout << i << ": " << (a ^ i).x << endl;
		}
	}
	cout<<"Tests passed!"<<endl;
}
