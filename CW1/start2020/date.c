#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "date.h"

struct date
{
    int day;
    int month;
    int year;
};

Date *date_create(char *datestr)
{
    char err_msg[] = "Date format must be DD/MM/YYYY";

    // make sure the string has the right format
    int len = strlen(datestr);
    if (len != 10)
    {
        printf("%s\n", err_msg);
        return NULL;
    }

    char div1 = datestr[2];
    char div2 = datestr[5];
    if (div1 != '/' || div2 != '/')
    {
        printf("%s\n", err_msg);
        return NULL;
    }

    // read the formatted string
    int day, month, year;
    int values_read = sscanf(datestr, "%d/%d/%d", &day, &month, &year);
    if (values_read != 3)
    {
        printf("%s\n", err_msg);
        return NULL;
    }

    // allocate the memory for a date struct
    Date *date = malloc(sizeof(Date));
    if (date)
    {
        date->day = day;
        date->month = month;
        date->year = year;
    }

    return date;
}

Date *date_duplicate(Date *d)
{
    if (!d)
    {
        return NULL;
    }

    Date *dup = malloc(sizeof(Date));
    if (dup)
    {
        dup->day = d->day;
        dup->month = d->month;
        dup->year = d->year;
    }

    return dup;
}

int date_compare(Date *d1, Date *d2)
{
    int year_diff = 1000 * (d1->year - d2->year);
    int month_diff = 100 * (d1->month - d2->month);
    int day_diff = d1->day - d2->day;

    return year_diff + month_diff + day_diff;
}

void date_destroy(Date *d)
{
    // will this be enough? I'm only using ints with it
    free(d);
}