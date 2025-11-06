unsigned invert(unsigned x, int p, int n) {
    unsigned mask = ~(~0 << n) << (p + 1 - n);
    return x ^ mask;
}