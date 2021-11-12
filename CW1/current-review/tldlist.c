// Lewis Ponsonby, Username: 2464980p Password: 91215013
// SP Exercise 1a
// This is my own work as defined in the Academics Ethics Agreement I have signed


// #include "date.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tldlist.h"

// Initialising tldlist structure
struct tldlist {
        struct date *begin;
        struct date *end;
        struct tldnode *root;
};


// Initialising tldnode structure
struct tldnode {
        char* tld;
        int freq;
        struct tldnode *left;
        struct tldnode *right;
};


// Initialising tlditerator structure
struct tlditerator {
        TLDNode *head;
        TLDNode *current;
};


// Function for creating an instance of TLDList
TLDList *tldlist_create(Date *begin, Date *end) {
        struct tldlist *list_p;
        list_p = (struct tldlist *)malloc(sizeof(struct tldlist));
        if (list_p) {
                list_p->begin=begin;
                list_p->end=end;
                return list_p;
        }
        else {
                return NULL;
        }
}


// Given a hostname, this function returns the tld
char* get_tld(char *hostname) {
        char* check;
        char* tld;
        char* copy = (char *)malloc(strlen(hostname) + 1);
        strcpy(copy, hostname);
        check = strtok(copy,".");
        while(check != NULL) {
                check=strtok(NULL,".");
                if (check==NULL) {
                        break;
                }
                tld=check;
        }
        return tld;
}


// Function for creating an instance of TLDNode
TLDNode *tldnode_create(char *hostname, TLDList *tld) {
        struct tldnode *node_p;
        node_p = (struct tldnode *)malloc(sizeof(struct tldnode));
        if (node_p!=NULL) {
                char* tld_to_add;
                tld_to_add = get_tld(hostname);
                node_p->tld=tld_to_add;
                node_p->freq=1;
                return node_p;
        }
        else {
                return NULL;
        }
}


// Function for freeing memory used by each TLDNode
void tldnode_destroy(TLDNode *node) {
        free(node->tld);
        free(node);
}


// Function for freeing memory used by the TLDList
void tldlist_destroy(TLDList *list) {
        free(list);
}

// Function for recursively finding the correct place to insert a TLDNode into the TLDList
TLDNode *tldlist_insert(TLDNode *root, char *hostname, TLDList *tld) {
        if (tld->root==NULL) {
                tld->root=tldnode_create(hostname,tld);
                // TLDNode *checker = tld->root;
        }
        else {

                if (root==NULL) {
                        root=tldnode_create(hostname, tld);
                        return root;
                }
                if (strcmp(root->tld, get_tld(hostname))<0) {
                        root->right = tldlist_insert(root->right, hostname, tld);
                }
                if (strcmp(root->tld, get_tld(hostname))>0) {
                        root->left=tldlist_insert(root->left, hostname, tld);
                }
                else if (strcmp(root->tld, get_tld(hostname))==0) {
                        root->freq=root->freq+1;
                }
        }
        return root;
}


// Function for adding a TLDNode to a TLDList
int tldlist_add(TLDList *tld, char *hostname, Date *d) {
        Date *begin, *end;
        TLDNode *listroot;
        listroot=tld->root;
        begin=tld->begin;
        end=tld->end;
        if (date_compare(begin, d)<0) {
                if (date_compare(d, end)<0) {
                        tldlist_insert(listroot, hostname, tld);
                        return 1;
                }
                else {
                        return 0;
                }
        }
        else {
                return 0;
        }
}

// Function for calculating the number of nodes in the TLD BST
long count_recurse(TLDNode *root) {
        if (root==NULL) {
                return 0;
        }
        return (root->freq + count_recurse(root->left) + count_recurse(root->right));
}

// Function for returning the number of nodes in the TLD BST
long tldlist_count(TLDList *tld) {
        return count_recurse(tld->root);
}


// Function to return the tld associated with the TLDNode
char *tldnode_tldname(TLDNode *node) {
        return node->tld;
}

//Function to return the frequency associated with the TLDNode
long tldnode_count(TLDNode *node) {
        return node->freq;
}

// Function to flatten the BST into a linked list
void flatten(TLDNode *root) {
        if (root==NULL) {
                return;
        }
        if (root->left==NULL && root->right==NULL) {
                return;
        }
        if (root->left != NULL) {
                flatten(root->left);

                TLDNode *temp;
                temp = root->right;
                root->right = root->left;
                root->left = NULL;

                TLDNode *current;
                current = root->right;
                while (current->right != NULL) {
                        current=current->right;
                }
                current->right=temp;
        }
        flatten(root->right);
}

TLDIterator *tldlist_iter_create(TLDList *tld) {
        struct tlditerator *new_iter;
        new_iter = (struct tlditerator *)malloc(sizeof(struct tlditerator));
        if (new_iter!=NULL) {
                new_iter->head=tld->root;
                new_iter->current=new_iter->head;
                return new_iter;
        }
        else {
                return NULL;
        }
}

TLDNode *tldlist_iter_next(TLDIterator *iter) {
        iter->current=iter->current->right;
        return iter->current;
}

void tldlist_iter_destroy(TLDIterator *iter) {
        // nothing.
}