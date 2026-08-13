#include <iostream>
#include <cmath>
#include <stack>
#include <vector>


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

vector<ll> divisors(ll x,bool first = 1,bool last = 1) {        // O(n^(1/2)) 
	vector<ll>d;                                                // first if you want to include 1
	stack<ll>s;                                                 // last if you want to include the number it self
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

vector<ll> primeFactors(int x) {             // O(n^(1/2))
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
bool nonPrime[sz] = {0};        // at first we declare all numbers as prime
vector<ll>primes;
void sieveSOE() {               //sieve of eratosthenes                 O(n(log(log(n))))
	nonPrime[0] = nonPrime[1] = 1;          // 0 and 1 are not prime
	for (int i = 2; i*i <= sz; i++) {
		if (!nonPrime[i]) {                               //if the number is prime then all its nultiples are not
			for (int j = i * i; j <= sz; j += i) {
				nonPrime[j] = 1;
			}
		}
	}

	for (int i = 0;i < sz;i++) {            //collect all primes in a vector
		if (!nonPrime[i]) {
			primes.push_back(i);
		}
	}
}

bool composite[sz];
void segmentedSieveNoPreGen(long long L, long long R) {        //O((R-L+1)loglog(R))
	for (long long i = 2; i * i <= R; ++i) {
		for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i) {
			composite[j - L] = true;
		}
	}
	if (L == 1) { composite[0] = true;}
}

bool isprime(ll x) {                              // O(n^(1/2))
    if (x < 2) return false;

    for (ll i = 2;i*i <= x;i++) {
        if (x % i == 0) return false;
    }

    return true;
}

int fib(int n) {
    int a = 0;
    int b = 1;
    for (int i = 0; i < n; i++) {
        int tmp = a + b;
        a = b;
        b = tmp;
    }
    return a;
}

struct matrix {
   ll mat[2][2];
   matrix friend operator * (const matrix& A,const matrix& B) {
      matrix C;
      for (int i = 0;i < 2;i++) {
         for (int j = 0;j < 2;j++) {
            C.mat[i][j] = 0;
            for (int k = 0;k < 2;k++) {
               C.mat[i][j] += A.mat[i][k]*B.mat[k][j];
               C.mat[i][j] %= MOD;
            }
         }
      }
      return C;
   }
};

matrix matpow(matrix A,ll n) {
   matrix ans = {{
      {1,0},
      {0,1},
   }} ;
   while(n) {
      if (n % 2 == 1) {
         ans = ans*A;
      }
      A = A*A;
      n /= 2;
   }
   return ans;
}

ll calculateNthFib(ll n,ll mod) {
   matrix X = {{
      {1,1},
      {1,0},
   }};
   matrix nX = matpow(X,n);
   ll nthFib = nX.mat[1][0];
   return nthFib;
}

ll gray(ll n) {               //get gray code to any number
	return n ^ (n >> 1);
}

ll reverseGray(ll g) {       //get number from gray code
	ll n = 0;
	for (;g;g >>= 1) {
		n ^= g;
	}
	return n;
}

#endif