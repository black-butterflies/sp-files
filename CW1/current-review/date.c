// Lewis Ponsonby, Username: 2464980p Password: 91215013
// SP Exercise 1a
// This is my own work as defined in the Academics Ethics Agreement I have signed


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"

struct date {
        int day;
        int month;
        int year;
};

Date *date_create(char *datestr) {
        char copy[11];
        strcpy(copy, datestr);
        copy[10] = '\0';
        int day = atoi(strtok(copy,"/"));
        int month = atoi(strtok(NULL,"/"));
        int year = atoi(strtok(NULL,"/"));
        struct date *d;
        d = (struct date *)malloc(sizeof(struct date));
        d->day=day;
        d->month=month;
        d->year=year;
        return d;
}

Date *date_duplicate(Date *d) {
        struct date *new_d;
        new_d = (struct date *)malloc(sizeof(struct date));
        new_d->day=d->day;
        new_d->month=d->month;
        new_d->year=d->year;
        return new_d;
}

void date_destroy(Date* d) {
        free(d);
}


int date_compare(Date *date1, Date *date2) {
        if (date1->year>date2->year) {
                return 1;
        }
        else if (date1->year<date2->year) {
                return -1;
        }
        else {
                if (date1->month>date2->month) {
                        return 1;
                }
                else if (date1->month<date2->month) {
                        return -1;
                }
                else {
                        if (date1->day>date2->day) {
                                return 1;
                        }
                        else if (date1->day<date2->day) {
                                return -1;
                        }
                        else {
                                return 0;
                        }
                }
        }
}

