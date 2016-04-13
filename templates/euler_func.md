```C++
long long euler(long long n) {
    long long ans = n;
    for(long long i=2; i*i<=n; i+=1) {
        if(n % i == 0) {
            ans -= ans / i;
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) ans -= ans / n;
    return ans;
}
```