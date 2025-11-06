unsigned rightrot(unsigned x, int n) {
    int w = sizeof(x) * 8;
    return (x >> n) | (x << (w - n));
}