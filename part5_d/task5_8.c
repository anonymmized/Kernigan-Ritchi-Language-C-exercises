static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    if (year < 1 || month < 1 || month > 12) {
        return 0;
    }
    int leap, i;
    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    if (day < 1 || day > daytab[leap][month]) {
        return 0;
    }
    for (i = 1; i < month; i++) {
        day += daytab[leap][i];
    }
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    if (year < 1 || yearday < 1) {
        *pmonth = 0;
        *pday = 0;
        return;
    }
    int i, leap;
    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    for (i = 1; yearday > daytab[leap][i]; i++) {
        yearday -= daytab[leap][i];
    }
    if (yearday > (leap ? 366 : 365)) {
        *pmonth = 0;
        *pday = 0;
        return;   
    }
    *pmonth = i;
    *pday = yearday;
}