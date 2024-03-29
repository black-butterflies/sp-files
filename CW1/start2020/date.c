/*
 * Sarahi Villegas Quinonez - 2477179V
 * SP Exercise 1a
 *
 * This is my own work as defined in the Academics Ethics agreement I have signed
 */

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
    if (date != NULL)
    {
        date->day = day;
        date->month = month;
        date->year = year;
    }
    else
    {
        free(date);
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
    if (dup != NULL)
    {
        dup->day = d->day;
        dup->month = d->month;
        dup->year = d->year;
    }
    else
    {
        free(dup);
    }

    return dup;
}

int date_compare(Date *d1, Date *d2)
{
    if (!d1 || !d2)
    {
        // One of them is null, just return 1
        return 1;
    }

    if (d1->year == d2->year)
    {
        if (d1->month == d2->month)
        {
            if (d1->day == d2->day)
            {
                return 0;
            }
            else if (d1->day > d2->day)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
        else if (d1->month > d2->month)
        {
            return 2;
        }
        else
        {
            return -2;
        }
    }
    else if (d1->year > d2->year)
    {
        return 3;
    }
    else
    {
        return -3;
    }
}

void date_destroy(Date *d)
{
    // will this be enough? I'm only using ints with it
    free(d);
}
