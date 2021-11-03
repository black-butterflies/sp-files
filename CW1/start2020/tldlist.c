#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "date.h"
#include "tldlist.h"

struct tldnode
{
    char *domain;
    long count;
    struct tldnode *parent;
    struct tldnode *right;
    struct tldnode *left;
};

struct tldlist
{
    TLDNode *head;
    long unique_tlds;
    long elements;
    Date *begin_date;
    Date *end_date;
};

struct tlditerator
{
    TLDList *list;
    TLDNode *current_node;
};

static TLDNode *tldnode_create(char *domain)
{
    TLDNode *node = (TLDNode *)malloc(sizeof(TLDNode));
    if (node != NULL)
    {
        node->domain = (char *)malloc((strlen(domain) + 1) * sizeof(char));
        if (!node->domain)
        {
            return NULL;
        }
        strcpy(node->domain, domain);
        node->parent = node->left = node->right = NULL;
        node->count = 1;
    }

    return node;
}

TLDList *tldlist_create(Date *begin, Date *end)
{
    if (!begin || !end)
    {
        return NULL;
    }

    TLDList *list = (TLDList *)malloc(sizeof(TLDList));
    if (list != NULL)
    {
        list->head = NULL;
        list->begin_date = begin;
        list->end_date = end;
        list->elements = 0;
        list->unique_tlds = 0;
    }

    return list;
}

/*
 * Free the space associated with a node
 */
static void tldnode_destroy(TLDNode *node)
{
    if (!node)
    {
        return;
    }
    tldnode_destroy(node->left);
    tldnode_destroy(node->right);

    free(node->domain);
    node->domain = NULL;
    free(node);
    node = NULL;
}

void tldlist_destroy(TLDList *tld)
{
    tldnode_destroy(tld->head);

    free(tld);
    tld = NULL;
}

static char *get_tld(char *hostname)
{
    char *cursor = hostname;
    char *last_dot_found = NULL;

    while (*cursor != '\0')
    {
        if (*cursor == '.')
        {
            last_dot_found = cursor;
        }
        cursor++;
    }

    if (last_dot_found != NULL)
    {
        last_dot_found++;
    }

    return last_dot_found;
}

int tldlist_add(TLDList *tld, char *hostname, Date *d)
{
    // make sure that the date is wihtin the range of the list
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

    // get the domain
    char *domain = get_tld(hostname);
    if (!domain)
    {
        // the domain is invalid, so we don't add it to the list
        return 0;
    }

    if (tld->head == NULL)
    {
        // if the list is empty, add the node to the head
        TLDNode *new_node = tldnode_create(domain);
        if (!new_node)
        {
            // if there was an issue while creating the node, don't add it
            return 0;
        }
        tld->head = new_node;
        (tld->elements)++;
        (tld->unique_tlds)++;

        return 1;
    }

    // the final case: the dates are valid:
    // find the node with the appropriate domain
    // or the place in the tree where the node should go
    TLDNode *parent, *cursor = tld->head;
    while (cursor != NULL && strcmp(domain, cursor->domain) != 0)
    {
        parent = cursor;
        if (strcmp(domain, cursor->domain) < 0)
        {
            cursor = cursor->left;
        }
        else
        {
            cursor = cursor->right;
        }
    }

    if (cursor != NULL)
    {
        // we found a node with the same domain
        (cursor->count)++;
        (tld->elements)++;
        return 1;
    }
    else
    {
        // we don't have a node with that domain so we have to create it
        TLDNode *new_node = tldnode_create(domain);
        if (!new_node)
        {
            return 0;
        }
        // if the parent is null, we're at the top of the list
        if (!parent)
        {
            parent = tld->head;
        }
        new_node->parent = parent;
        // check on which side we have to add the node
        if (strcmp(domain, parent->domain) < 0)
        {
            parent->left = new_node;
        }
        else
        {
            parent->right = new_node;
        }
        // update the counters in the list
        (tld->unique_tlds)++;
        (tld->elements)++;
        return 1;
    }
}

long tldlist_count(TLDList *tld)
{
    return tld->elements;
}

static TLDNode *tree_minimum(TLDNode *node)
{
    TLDNode *cursor = node;

    while (cursor->left != NULL)
    {
        cursor = cursor->left;
    }

    return cursor;
}

TLDIterator *tldlist_iter_create(TLDList *tld)
{
    TLDIterator *iter = (TLDIterator *)malloc(sizeof(TLDIterator));
    if (iter != NULL)
    {
        iter->list = tld;
        iter->current_node = tree_minimum(tld->head);
    }

    return iter;
}

static TLDNode *sucessor(TLDNode *node)
{
    if (node->right != NULL)
    {
        return tree_minimum(node->right);
    }

    TLDNode *parent = node->parent;
    TLDNode *cursor = node;
    while (parent != NULL && cursor == parent->right)
    {
        cursor = parent;
        parent = parent->parent;
    }

    return parent;
}

TLDNode *tldlist_iter_next(TLDIterator *iter)
{
    TLDNode *current_node = iter->current_node;
    if (current_node != NULL)
    {
        iter->current_node = sucessor(current_node);
    }

    return current_node;
}

void tldlist_iter_destroy(TLDIterator *iter)
{
    free(iter);
    iter = NULL;
}

char *tldnode_tldname(TLDNode *node)
{
    return node->domain;
}

long tldnode_count(TLDNode *node)
{
    return node->count;
}
