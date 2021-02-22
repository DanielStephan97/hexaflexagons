/**
 * Author: Niko Hastrich
 * Date: 2020-02-05
 * License: CC0
 * Source: CP-Algorithms, https://codeforces.com/blog/entry/56264
 * Description: Solves \(a^x=b \pmod m\) for x for \(a,b\) coprime \(m\). Let \([x_0,t] = discrete\_log(a, b, m)\) then
 * forall \(k \geq 0\) the equation \(a^{x_0 + kt} = b \pmod m\) holds and their are no other solutions. If \(t= 0\)
 * holds then there is exactly one solution. If \(t=-1\) then there are no solutions.
 * Status: Tested
 */

#include "Factor.h"

ll discrete_log_coprime(ll b, const ll e, const ll m) {
    unordered_map<ll, ll> table;
    ll n = floor(sqrt(m)), x = e, a = 1;
    for (ll i = 0; i < n; i++, a = (a * b) % m, x = (x * b) % m) {
        auto it = table.find(x);
        if (it != table.end())
            it->second = i;
        else
            table.emplace(x, i);
    }
    ll d = a, v = d;
    for (ll j = n; j - n < m; j += n, v = (v * d) % m) {
        auto it = table.find(v);
        if (it != table.end())
            return j - it->second;
    }
    return -1;
}

pair<ll, ll> discrete_log(ll a, ll b, ll m) {
    auto d = gcd(a, m);
    if (gcd(b, m) % d != 0) return {-1, -1};
    else if (d == 1) return {discrete_log_coprime(a, b, m), discrete_log_coprime(a, 1, m)};
    else {
        ll m1 = 1, m2 = m;
        for(auto p:prime_factors(gcd(a, m))) while (m2 % p == 0) m1 *= p, m2 /= p;

        ll n = 1, t = a;
        for (; t % m1 != 0; n++, t = t * a % m)
            if (t % m1 == b % m1 && t % m2 == b % m2)
                return {n, -1};

        ll sol = discrete_log_coprime(a % m2, b % m2, m2);
        if (sol == -1) return {-1, -1};
        ll sol_per = discrete_log_coprime(a, 1, m2);
        while (sol < n) sol += sol_per;
        return {sol, sol_per};
    }
}

