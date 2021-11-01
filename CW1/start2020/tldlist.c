#include <stdlib.h>
#include <string.h>
#include "date.h"
#include "tldlist.h"

struct tldnode
{
    char *domain;
    struct tldnode *parent;
    struct tldnode *right_child;
    struct tldnode *left_child;
};
typedef struct tldnode TLDNode;

struct tldlist
{
    TLDNode *head;
    long elements;
    Date *begin_date;
    Date *end_date;
};
typedef struct tldlist TLDList;

struct tlditerator
{
    // implement
};
typedef struct tlditerator TLDIterator;

static TLDNode *tldnode_create(char *domain)
{
    TLDNode *node = malloc(sizeof(TLDNode));
    if (node)
    {
        node->domain = domain;
        // we create an empty node with no children
        node->parent = node->left_child = node->right_child = NULL;
    }

    return node;
}

TLDList *tldlist_create(Date *begin, Date *end)
{
    if (!begin || !end)
    {
        return NULL;
    }

    TLDNode *head = tldnode_create(NULL);
    if (!head)
    {
        return NULL;
    }

    TLDList *list = malloc(sizeof(TLDList));
    if (list)
    {
        list->head = head;
        list->begin_date = begin;
        list->end_date = end;
        list->elements = 0;
    }

    return list;
}

/* 
 * Free the space associated with a node
 */
static void tldnode_destroy(TLDNode *node)
{
    // recursion might get me a stack overflow error so revise this and implement it iteratively
    tldnode_destroy(node->left_child);
    tldnode_destroy(node->right_child);

    free(node);
}

void tldlist_destroy(TLDList *tld)
{
    tldnode_destroy(tld->head);

    free(tld);
}

int tldlist_add(TLDList *tld, char *hostname, Date *d)
{
    // make sure that the date is within the range of the list
    int comp = date_compare(d, tld->begin_date);
    if (comp < 0)
    {
        return 0;
    }
    comp = date_compare(d, tld->end_date);
    if (comp > 0)
    {
        return 0;
    }

    // if the list given is null, we can't add anything
    if (!tld)
    {
        return 0;
    }

    if (!tld->head->domain)
    {
        // if the head is null, insert it in the head
    }
    else
    {
        // otherwise insert it in the bst
    }
}

long tldlist_count(TLDList *tld)
{
    // keep in each node a count of how many times a TLD was added to the list
    // iterate through the bst and add all the entries that were succesfully added
    return 0;
}

TLDIterator *tldlist_iter_create(TLDList *tld)
{
    // create the iterator
    // could be a linked list with all the elements
    // OR could be an array (keep track of how many elements etc)
}