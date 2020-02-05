/**
 * Author: Simon Lindholm
 * Date: 2019-05-22
 * License: CC0
 * Description: Chinese Remainder Theorem.
 *
 * \texttt{crt(a, m, b, n)} computes $x$ such that $x\equiv a \pmod m$, $x\equiv b \pmod n$.
 * If $|a| < m$ and $|b| < n$, $x$ will obey $0 \le x < \text{lcm}(m, n)$.
 * Assumes $mn < 2^{62}$.
 * Status: Works
 * Time: $\log(n)$
 */
#include "euclid.h"

pair<ll,ll> crt(ll a, ll n, ll b, ll m) {
    auto [d, x, y] = euclid(n, m);
    ll l = n * m / d;
    ll ret = (a + ((x * (b-a) / d) % (m/d)) * n) % l;
    return {(b-a) % d ? -1 : (ret + l) % l, l};
}

