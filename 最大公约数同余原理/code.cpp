class code
{
public:
    long long gcd(long long a,long long b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
    long long lcm(long long a,long long b)
    {
        return (long long)a / gcd(a, b) * b;
    }
};

