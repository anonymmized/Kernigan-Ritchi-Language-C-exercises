unsigned setbits(unsigned x, unsigned y, int p, int n) {
    unsigned yy = ((y) & ~(~0 << n)) << (p + 1 - n);
    unsigned mask = ~(~0 << n) << (p + 1 - n);
    unsigned xx = x & ~mask;
    return xx | yy;
}