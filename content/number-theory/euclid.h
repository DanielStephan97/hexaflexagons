/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Finds the Greatest Common Divisor to the integers $a$ and $b$.
 * Euclid also finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$.
 * If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
 */
array<ll,3> euclid(ll a, ll b) {
    if (a == 0)
        return {b, 0, 1};
    auto [d, x1, y1] = gcd(b % a, a);
    return {d, y1 - (b / a) * x1, x1};
}

