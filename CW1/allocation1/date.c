/* Program tldmonitor.c
 * File date.c
 *
 * AUTHORSHIP STATEMENT
 * Name:    Giorgio Ciacchella
 * GUID:    2481024c
 * This is my own work, as defined in the Academic Ethics Agreement I have
 * signed.
*/

#ifndef _STD_INCLUDED_
#define _STD_INCLUDED_
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#endif
#ifndef _DATE_H_INCLUDED_
#include "date.h"

typedef struct date {
    long day;
    long month;
    long year;
} Date;


/*
 * date_create creates a Date structure from `datestr`
 * `datestr' is expected to be of the form "dd/mm/yyyy"
 * returns pointer to Date structure if successful,
 *         NULL if not (syntax error)
 */
Date* date_create (char* datestr)
{
    // dynamic memory allocation CANNOT be here as an invalid datestr would
    // allocate a chunk but return NULL, which CANNOT be freed causing a memory
    // leak of sizeof(Date)
    if (datestr[2] == '/' && datestr[5] == '/')
    {
        // dynamic memory allocation should instead be here, after checking the
        // validity of the input and ensuring a proper Date* is returned to be
        // freed in the future
        Date* d = malloc( sizeof(Date) );
        if (d)
        {
            //printf("date malloc @\t\t%p:\t", (void*)d);
            
            // parse and tokenise the input hostname
            // strtok reference:
            // https://en.cppreference.com/w/c/string/byte/strtok
            long i = 0;
            char* date_tokens[3];
            const char* delimiter = "/";
            char *token = strtok(datestr, delimiter);
            while(token)
            {
                date_tokens[i] = token;
                i++;
                token = strtok(NULL, delimiter);
            }

            // convert the substrings to long
            // strtol reference:
            // https://en.cppreference.com/w/c/string/byte/strtol
            d->day = (long) strtol(date_tokens[0], NULL, 10);
            d->month = (long) strtol(date_tokens[1], NULL, 10);
            d->year = (long) strtol(date_tokens[2], NULL, 10);

            //printf("%02d/%02d/%d\n", d->day, d->month, d->year);
        }

        return d;
    }

    else
    {
        // on the other hand, when the input is invalid and NULL is returned,
        // no memory is allocated dynamically avoiding a memory leak
        return NULL;
    }
}


/*
 * date_duplicate creates a duplicate of `d'
 * returns pointer to new Date structure if successful,
 *         NULL if not (memory allocation failure)
 */
Date* date_duplicate (Date* d)
{
    Date* d_dup = malloc( sizeof(Date) );
    if (d_dup)
    {
        d_dup->day = d->day;
        d_dup->month = d->month;
        d_dup->year = d->year;
    }
    return d_dup;
}


/*
 * date_compare compares two dates, returning <0, 0, >0 if
 * date1<date2, date1==date2, date1>date2, respectively
 */
int date_compare (Date* date1, Date* date2)
{
    //printf("%02d/%02d/%d vs %02d/%02d/%d:\t", date1->day, date1->month, date1->year, date2->day, date2->month, date2->year);

    int result = 0;

    if (date1->year < date2->year) result = -1;
    else if (date1->year > date2->year) result = 1;
    else
    {
        if (date1->month < date2->month) result = -1;
        else if (date1->month > date2->month) result = 1;
        else
        {
            if (date1->day < date2->day) result = -1;
            else if (date1->day > date2->day) result = 1;
        }
    }

    //printf("%d\n", result);
    return result;
}


/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy (Date *d)
{
    free(d);
    ////printf("date free'd @\t\t%p\n", (void*)d);
}

#endif