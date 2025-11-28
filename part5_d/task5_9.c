static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    int leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (year < 1 || month < 1 || month > 12) return 0;
    int *p = daytab[leap];
    if (day < 1 || day > *(p + month)) return 0;
    for (int *q = p + 1; q < p + month; q++) {
        day += *q;
    }
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int *p = daytab[leap];
    int maxdays = leap ? 366 : 365;
    if (yearday < 1 || yearday > maxdays) {
        *pmonth = 0;
        *pday = 0;
        return;
    }
    int month = 1;
    int *q = p + 1;
    while (yearday > *q) {
        yearday -= *q;
        q++;
        month++;
    }
    *pmonth = month;
    *pday = yearday;
}