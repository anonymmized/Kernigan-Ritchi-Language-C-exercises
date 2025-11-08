char* escape(char* s, char* t) {
    int i = 0, j = 0;
    while (s[i] != '\0') {
        switch (s[i]) {
            case '\n':
                t[j++] = '\\';
                t[j++] = 'n';
                break;
            case '\t':
                t[j++] = '\\';
                t[j++] = 't';
                break;
            default:
                t[j++] = s[i];
                break;
        }
        i++;
    }
    t[j] = '\0';
    return t;
}