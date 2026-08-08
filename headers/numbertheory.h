#include <cmath>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

#ifndef NUMBERTHEORY_H
#define NUMBERTHEORY_H

#define ll long long int


const ll fl = 1e6+10;
ll MOD = 1e9 + 7;
ll fact[fl];

ll addM(ll a, ll b, ll m) {
	return ((a % m + b % m) % m);
}

ll subM(ll a, ll b, ll m) {
	return (((a % m) - (b % m) + m) % m);
}

ll multiM(ll a, ll b, ll m) {
	return (((a % m) * (b % m)) % m);
}

ll fastpow(ll x, ll n) {
	ll result = 1;
	while (n > 0) {
		if (n % 2 == 1) {
			result *= x;
		}
		x *= x;
		n /= 2;
	}
	return result;
}

ll modpow(ll x, ll n,ll m) {
	ll result = 1;
	while (n > 0) {
		if (n % 2 == 1) {
			result = multiM(result,x,m);
		}
		x = multiM(x,x,m);
		n /= 2;
	}
	return result;
}

vector<ll> divisors(ll x,bool first = 1,bool last = 1) {
	vector<ll>d;
	stack<ll>s;
	if (first) d.push_back(1);
	for (ll i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			d.push_back(i);
			if (i * i != x) {
				s.push((x / i));
			}
		}
	}
	while (!s.empty()) {
		d.push_back(s.top());
		s.pop();
	}
	if (last) d.push_back(x);
	return d;
}

vector<ll> primeFactors(int x) {
	vector<ll>pf;
	for (int i = 2; i * i <= x; i++) {
		while (x % i == 0) {
			x /= i;
			pf.push_back(i);
		}
	}
	if (x != 1) {
		pf.push_back(x);
	}
	return pf;
}

ll gcd(ll a,ll b) {
	while (b != 0) {
		ll a2 = a;
		a = b;
		b = a2 % b;
	}
	return a;
}

ll lcm(ll a, ll b) {
	return 	((a / gcd(a, b)) * b);
}

ll EER(int a, int b, int& x, int& y) {           //Extended Eucliden Algorithm
	if (b == 0) {                                //ax + by = gcd(a,b)     // bx1 + (a%b)y1 = gcd(a,b)   // a%b = a-b*floor(a/b)
		x = 1;                                   
		y = 0;
		return a;     //return the gcd
	}
	int x1, y1;
	int d = EER(b, (a % b), x1, y1);
	x = y1;
	y = x1 - y1 * floor(a / b);
	return d;     //return the gcd
}

ll modInverse(ll a, ll m) {
	return modpow(a, (m - 2), m);
}

ll divM(ll a,ll b, ll m) {
	ll n1 = modpow(b, (m - 2), m);
	return multiM(a, n1, m);
}

ll ncr(int n,int r) {
	return multiM(fact[n], modInverse(multiM(fact[n-r],fact[r], MOD), MOD), MOD);
}

const int sz = 1e6+6;
bool nonPrime[sz];
void sieveSOE() {               //sieve of eratosthenes                 n(log(log(n)))
	nonPrime[0] = nonPrime[1] = 1;
	for (int i = 2; i*i <= sz; i++) {
		if (!nonPrime[i]) {
			for (int j = i * i; j <= sz; j += i) {
				nonPrime[j] = 1;
			}
		}
	}
}

bool composite[sz];
void segmentedSieveNoPreGen(long long L, long long R) {

	for (long long i = 2; i * i <= R; ++i) {
		for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i) {
			composite[j - L] = true;
		}
	}
	if (L == 1) { composite[0] = true;}
}


#endif