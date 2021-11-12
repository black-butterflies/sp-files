/* Program tldmonitor.c
 * File tldlist.c
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
#ifndef _TLDLIST_H_INCLUDED_
#include "tldlist.h"


typedef struct tldnode {
    struct tldnode* parent;
    struct tldnode* left;
    struct tldnode* right;

    struct tldlist* tree;

    Date* date;
    char domain[3];
} TLDNode;

typedef struct tldlist {
    TLDNode* root;

    Date* begin;
    Date* end;
} TLDList;

typedef struct tlditerator {
    TLDList* list;

    long i;
    long i_max;
} TLDIterator;


/*
 * tldlist_create generates a list structure for storing counts against
 * top level domains (TLDs)
 *
 * creates a TLDList that is constrained to the `begin' and `end' Date's
 * returns a pointer to the list if successful,
 *         NULL if not
 */
TLDList* tldlist_create(Date* begin, Date* end)
{
    TLDList* tldlist = malloc( sizeof(TLDList) );
    if (tldlist != NULL)
    {
        //printf("tldlist malloc @\t%p\n", (void*)tldlist);
        tldlist->root = NULL;
        tldlist->begin = begin;
        tldlist->end = end;
    }

    return tldlist;
}


/*
 * tldlist_traverse recursively traverses the BST post-order, operating the
 * "plugin" function `func' to all visited nodes,
 * and returning 1 to break out of recurrence,
 *               0 to continue
 * this effectively forms the "framework" used by most functions to perform
 * their operations
 */
int tldlist_traverse (TLDNode* root_node, int (*func)(TLDNode*, TLDNode**, void*, void*), TLDNode** arg_node, void* arg1, void* arg2)
{
    // check for non-null root node before referencing
    if(root_node)
    {
        // check for non-null left child, then enter breakable left-side
        // recursion
        if (root_node->left && tldlist_traverse(root_node->left, *func, arg_node, arg1, arg2))
        {
            //printf("traversing left @\t%p\n", (void*) root_node->left);
            return 1;
        }

        // check for non-null right child, then enter breakable right-side
        // recursion
        if (root_node->right && tldlist_traverse(root_node->right, *func, arg_node, arg1, arg2))
        {
            //printf("traversing right @\t%p\n", (void*) root_node->right);
            return 1;
        }

        // post-order call to the "plugin" function
        return func(root_node, arg_node, arg1, arg2);
    }
    else
    {
        return 0;
    }
}

/*
 * helper plugin function:
 * destroy is called by `tldlist_destroy',
 * and plugs into `tldlist_traverse',
 * deallocating the memory associated with the current node.
 */
int destroy(TLDNode* node, TLDNode** node_null, void* null1, void* null2)
{
    free(node);
    //printf("tldnode free'd @\t%p\n", (void*) node);
    return 0;
}

/*
 * tldlist_destroy destroys the list structure in `tld'
 *
 * all heap allocated storage associated with the list is returned to the heap
 */
void tldlist_destroy(TLDList *tld)
{
    //printf("traversing tree to free...\n");
    tldlist_traverse(tld->root, destroy, NULL, NULL, NULL);
    free(tld);
    //printf("tldlist free'd @\t%p\n", (void*)tld);
}


/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList* tld, char* hostname, Date* d)
{
    // check if the date falls in the window considered by the list
    if (date_compare(d, tld->begin) >= 0 &&
        date_compare(d, tld->end) <= 0)
    {
        // parse and tokenise the input hostname
        // strtok reference:
        // https://en.cppreference.com/w/c/string/byte/strtok
        const char* delimiter = ".";
        char* token_current = strtok(hostname, delimiter);
        char* token_trailing = NULL;
        while (token_current)
        {
            token_trailing = token_current;
            token_current = strtok(NULL, delimiter);
        }

        // dynamically allocate a new node -- all nodes allocated here will be
        // recursively freed under tldlist_destroy
        TLDNode* n = malloc( sizeof(TLDNode) );
        if (n)
        {
            //printf("tldnode malloc @\t%p:\t", (void*)n);
            n->tree = tld;
            n->date = date_duplicate(d);

            // copy the TLD in the last token to its dedicated location 
            // strcpy reference:
            // https://en.cppreference.com/w/c/string/byte/strcpy
            strcpy(n->domain, token_trailing);
            //printf("%s\n", n->domain);

            // search the BST to find the appropriate leaf node
            TLDNode* trailing = NULL;
            TLDNode* current = tld->root;
            while (current)
            {
                trailing = current;
                if (date_compare(d, current->date) < 0)
                {
                    current = current->left;
                }
                else
                {
                    current = current->right;
                }
            }

            // insert the node at the appropriate leaf location
            n->parent = trailing;
            if (!trailing)
            {
                //printf("node inserted as ROOT;\t");
                tld->root = n;
            }
            else if (date_compare(d, trailing->date) < 0)
            {
                //printf("node inserted as left child;\t");
                trailing->left = n;
            }
            else
            {
                //printf("node inserted as right child;\t");
                trailing->right = n;
            }

            //printf("BST rooted @ %p\n", (void*) tld->root);
            
            // return 1 for success
            return 1;
        }

        else
        {
            // if a memory allocation error occurred, return 0
            return 0;
        }
    }

    else
    {
        // if the date falls outside the window of the specified list, return 0
        return 0;
    }
}


/*
 * helper plugin function:
 * count is called by `tldlist_count',
 * and plugs into `tldlist_traverse',
 * simply increasing the value of the specified counter by one with each node
 * visited
 */
int count(TLDNode* node, TLDNode** node_null, void* counter, void* null)
{
    long* counter_ptr = (long*) counter;
    *counter_ptr = *counter_ptr + 1;
    return 0;
}

/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList* tld)
{
    long c = 0;
    long* c_ptr = &c;
    //printf("traversing tree to count all nodes...\n");
    tldlist_traverse(tld->root, count, NULL, c_ptr, NULL);
    return (long) c;
}


/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator* tldlist_iter_create(TLDList* tld)
{
    TLDIterator* iter = malloc( sizeof(TLDIterator) );
    if (iter)
    {
        iter->list = tld;
        iter->i = 0;
        iter->i_max = tldlist_count(tld);
    }
    return iter;
}

/*
 * helper plugin function:
 * next is called by `tldlist_iter_next',
 * and plugs into `tldlist_traverse',
 * using the specified counter and limit to select the next item in the
 * iterator and store the currently visited node at the location of the
 * specified pointer
 */
int next(TLDNode* node, TLDNode** node_ptr, void* counter, void* limit)
{
    long* counter_ptr = (long*) counter;
    long* limit_ptr = (long*) limit;

    if (*counter_ptr == *limit_ptr)
    {
        //printf("next tldnode @\t\t%p\t%lu==%lu\n", node, *counter_ptr, *limit_ptr);
        *node_ptr = node;

        // when the next node is found, return 1 to break out of recursion
        return 1;
    }
    else
    {
        //printf("not yet...\t\t\t\t%lu!=%lu\n", *counter_ptr, *limit_ptr);
        *counter_ptr = *counter_ptr + 1;

        // otherwise, return 0 to continue recursing
        return 0;
    }
}

/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode* tldlist_iter_next(TLDIterator* iter)
{
    //printf("finding next tldnode...\t\t\t%lu/%lu\n", iter->i, iter->i_max);
    
    // check if all elements have been returned already
    if (iter->i < iter->i_max - 1)
    {
        // initialise node pointer placeholder
        TLDNode* node = NULL;
        TLDNode** node_ptr = &node;
        
        // initialise recursion counter
        long c = 0;
        long* c_ptr = &c;

        //printf("traversing tree to find next...\n");
        tldlist_traverse(iter->list->root, next, node_ptr, c_ptr, &(iter->i));
        iter->i = iter->i + 1;
        return *node_ptr;
    }
    else
    {
        // return NULL for end of iteration
        return NULL;
    }
}


/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator* iter)
{
    free(iter);
    //printf("tldlist_iter free'd @\t%p\n", (void*)iter);
}


/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char* tldnode_tldname(TLDNode* node)
{
    return node->domain;
}

/*
 * helper plugin function:
 * count_if is called by `tldnode_count',
 * and plugs into `tldlist_traverse',
 * only increasing the specified counter if the tld of the currently visited
 * node matches the condition string
 */
int count_if(TLDNode* node, TLDNode** node_null, void* counter, void* condition)
{
    long* counter_ptr = (long*) counter;
    char* condition_ptr = (char*) condition;
    if (strcmp(node->domain, condition_ptr) == 0)
    {
        *counter_ptr = *counter_ptr + 1;
    }
    return 0;
}

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode* node)
{
    long c = 0;
    long* c_ptr = &c;
    //printf("traversing tree to count tld nodes...\n");
    tldlist_traverse(node->tree->root, count_if, NULL, c_ptr, node->domain);

    return (long) c;
}

#endif