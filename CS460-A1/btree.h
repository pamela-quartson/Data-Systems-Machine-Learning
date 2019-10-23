/*
 *
 * You will need to write your B+Tree almost entirely from scratch.
 *
 * B+Trees are dynamically balanced tree structures that provides efficient support for insertion, deletion, equality, and range searches.
 * The internal nodes of the tree direct the search and the leaf nodes hold the base data..
 *
 * For a basic rundown on B+Trees, we will refer to parts of Chapter 10 of the textbook Ramikrishnan-Gehrke
 * (all chapters and page numbers in this assignment prompt refer to the 3rd edition of the textbook).
 *
 * Read Chapter 10 which is on Tree Indexing in general. In particular, focus on Chapter 10.3 on B+Tree.
 */

#ifndef BTREE_H
#define BTREE_H

#ifdef _WIN32
#define bool char
#define true 1
#define false 0
#endif

#include "data_types.h"
#include "query.h"
#include <stdbool.h>

#define DEFAULT_FANOUT 5


/*
Designing your C Structs for B+Tree nodes (Chapter 10.3.1)
How will you represent a B+Tree as a C Struct (or series of C structs that work together)? There are many keyid ways to do this part of your design, and we leave it open to you to try and tune this as you progress through the project.
How will you account for a B+Tree node being an internal node or a leaf node? Will you have a single node type that can conditionally be either of the two types, or will you have two distinct struct types?
How many children does each internal node have? This is called the fanout of the B+Tree.
What is the maximum size for a leaf node? How about for an internal node?
What is the minimum threshold of content for a node, before it has to be part of a rebalancing?
*/

// TODO: here you will need to define a B+Tree node(s) struct(s)


//node struct declaration
//One node struct is used to define both leaf and internal nodes
typedef struct node
{
    int * key;
    void ** ptr;
	int size;
    bool is_leaf;
    struct node *parent;
    struct node *next;
}node;

int fanout = DEFAULT_FANOUT;


/* The following are methods that can be invoked on B+Tree node(s).
 * Hint: You may want to review different design patterns for passing structs into C functions.
 */

//node initialisation for non-leaf node
//this returns a pointer to the newly created internal node
node *init_node(void)
{
    node *n = (node*)malloc(sizeof(n));
    if(n==NULL)
    {
        exit(EXIT_FAILURE);
    }
    n->key = malloc((fanout-1)*sizeof(int));
    if(n->key==NULL)
    {
        exit(EXIT_FAILURE);
    }
    n->ptr = malloc((fanout)*sizeof(int));
    if(n->ptr==NULL)
    {
        exit(EXIT_FAILURE);
    }
    n->size = 0;
    n->is_leaf = false;
    n->parent = NULL;
    n->next = NULL;
    return *n;
}

//leaf node initialisation
//this returns a pointer to the newly created leaf node
node *init_leaf(void)
{
    node *leafNode = init_node();
    leafNode->is_leaf = true;
    return leafNode;
}


/* FIND (Chapter 10.4)
This is an equality search for an entry whose key matches the target key exactly.
How many nodes need to be accessed during an equality search for a key, within the B+Tree?
*/

// TODO: here you will need to define FIND/SEARCH related method(s) of finding key-keyues in your B+Tree.


//FIND

//find_node(): auxiliary function to help find the node where a given key's value is stored
//this traverses the tree from the root node down to the leaf node and returns the node the contains the value of the given key
//If key is not found, functions returns a null value.
node *find_node (node * root, int key)
{
    node *n = root;
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        while (!n->is_leaf)
    {
        int q = n->size;
        if (key<=n->key[1])
        {
            n=(node *)n->ptr[0];
        }
        else if (key>n->key[q-1])
        {
            n=(node *)n->ptr[q-1];
        }
        else
        {
            for (int i = 1; i < q; i++)
            {
                if (n->key[i-1]<key && n->key[i]<=key)
                {
                    n=(node *)n->ptr[i];
                }

            }

        }
        
    }
    }
    return n;

}


//find function
//this is the main find function and it returns an integer pointer to the data which is being searched
//It takes a pointer to the root node of the b+ tree and the key of the value to be seaarched for.
int *find(node *root, int key)
{
    node *n = find_node(root, key);
    int i =0;

    for(i; i<n->size; i++)
    {
        if(n->key[i]==key)
        {
            break; 
        }
    }
    return (int *)n->ptr[i];
}

/* INSERT (Chapter 10.5)
How does inserting an entry into the tree differ from finding an entry in the tree?
When you insert a key-keyue pair into the tree, what happens if there is no space in the leaf node? What is the overflow handling algorithm?
For Splitting B+Tree Nodes (Chapter 10.8.3)
*/

// TODO: here you will need to define INSERT related method(s) of adding key-keyues in your B+Tree.
node * start_tree(int key, int * val){
    node *rootNode = init_leaf();
    rootNode->key[0] = key;
    rootNode->ptr[0] = val;
    rootNode->parent = NULL;
    rootNode->size++;
    rootNode->ptr[fanout-1] = NULL;
    return rootNode;
}

void insert(int key, int  val, node *root)
{
    int *valPtr = NULL;
    node *leaf = NULL;
    valPtr = find(root,key);
    if (valPtr!=NULL)
    {
        valPtr = &val;
    }
    valPtr =  &val;

    if (root==NULL)
    {
        return start_tree(key,valPtr)
        return root;
    }

    leaf = find_node(root,key)

    if(leaf->size < fanout-1){
        leaf =  
    }

    
    
}

//The modify function is used to update the corrensponding data to a key that already holds data
void modify(int key, node *ptr, int val)
{
    

    //key of value must be equal to key of record.
    //set data pointer to the address of the new value
}


//The split function is used to split nodes when their contents exceed the maximum threshold
void split(node *nodeTosplit)
{
    node *n = nodeTosplit;
    int size;
    int i;
    int j=0;
    node *temp_ptr[fanout];
    int temp_key[fanout];
    temp_key = malloc((fanout)*sizeof(int));
    if(temp_key==NULL)
    {
        exit(EXIT_FAILURE);
    }
    temp_ptr = malloc(fanout*sizeof(int));
    if(temp_ptr==NULL)
    {
        exit(EXIT_FAILURE);
    }
    node *newNode = init_node();
    for (i = (n->size/2)-1; i < n->size; i++)
    {
        temp_ptr[j] = n->ptr[i];
        temp_key[j+1] = n->key[i];
        n->ptr[i] = NULL;
        n->key[i] = NULL;
        j++;
        size++;
    }

    newNode->key = temp_key;
    newNode->ptr = temp_ptr;
    newNode->size = size;
    newNode->parent = n->parent;

    if (n->is_leaf)
    {
        newNode->is_leaf = true;
    }
}



/* BULK LOAD (Chapter 10.8.2)
Bulk Load is a special operation to build a B+Tree from scratch, from the bottom up, when beginning with an already known dataset.
Why might you use Bulk Load instead of a series of inserts for populating a B+Tree? Compare the cost of a Bulk Load of N data entries versus that of an insertion of N data entries? What are the tradeoffs?
*/

// TODO: here you will need to define BULK LOAD related method(s) of initially adding all at once some key-keyues to your B+Tree.
// BULK LOAD only can happen at the start of a workload


/*RANGE (GRADUATE CREDIT)
Scans are range searches for entries whose keys fall between a low key and high key.
Consider how many nodes need to be accessed during a range search for keys, within the B+Tree?
Can you describe two different methods to return the qualifying keys for a range search?
(Hint: how does the algorithm of a range search compare to an equality search? What are their similarities, what is different?)
Can you describe a generic cost expression for Scan, measured in number of random accesses, with respect to the depth of the tree?
*/

// TODO GRADUATE: here you will need to define RANGE for finding qualifying keys and keyues that fall in a key range.



#endif
