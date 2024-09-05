#include "linked_list.h"

#include <stdlib.h>

/*
    These are used for the implementation only and not the interface.
    They are "undef'd" at the end of this file.
*/

struct LL_STRUCT
{
    int size;
    Node* head;
};

typedef struct node
{
    LL_ITEM_TYPE value;
    Node* next;
} Node;

/*
    For calling a LL function for the type at hand.
    This is "undef'd" at the end of this file.
*/
#define CALL(f) CAT(f##_,LL_ITEM_TYPE)

/*
    Creates a new list node with the given value and returns a pointer to it.
*/
static inline Node* createNode(LL_ITEM_TYPE item)
{
    Node* node = (Node*) malloc(sizeof(Node));
    node->next = NULL;
    node->value = item;

    return node;
}

/*
    Inserts node 'new' in front of 'at'.
*/
static inline void insertNodeAt(Node* new, Node* at)
{
    new->next = at->next;
    at->next = new;
}

/*
    Creates an empty LL_ITEM_TYPE list and returns a pointer to it
*/
LL_TYPE* CAT(LLCreate_,LL_ITEM_TYPE)()
{
    LL_TYPE* list = (LL_TYPE*) malloc(sizeof(LL_TYPE));
    list->size = 0;
    list->head = NULL;

    return list;
}

/*
    Frees memory of a LL_ITEM_TYPE list, but does not free any of the list's items.
    If you want to free memory for each item as well, use 'LLClearAndDelete_LLITEM_TYPE'.

    Always returns NULL.
*/
LL_TYPE* CAT(LLDelete_,LL_ITEM_TYPE) (LL_TYPE* list)
{
    // List is not empty, so free all nodes
    if (!(CALL(LLIsEMpty)(list)))
    {
        Node* current = list->head;
        Node* next = current->next;

        do
        {
            free(current);
            current = next;
            next = current->next;
        } while(current != NULL);
    }

    free(list);

    return NULL;
}

/*
    Frees memory of all items in a list.
    The passed 'item_delete_function' is called with each item in the list as an
    argument.
*/
void CAT(LLClear_,LL_ITEM_TYPE) (LL_TYPE* list, \
                                 void (*item_delete_function) (LL_ITEM_TYPE))
{
    // List is not empty, so free all nodes
    if (!(CALL(LLIsEMpty)(list)))
    {
        Node* current = list->head;

        do
        {
            item_delete_function(current->value);
            current = current->next;
        } while(current != NULL);
    }
}

/*
    Frees memory of all items in a list, then frees all the memory allocated for the list.

    Always returns NULL.
*/
LL_TYPE* CAT(LLClearAndDelete_,LL_ITEM_TYPE) (LL_TYPE* list, \
                                              void (*item_delete_function) (LL_ITEM_TYPE))
{
    CALL(LLClear)(list, item_delete_function);
    return CALL(LLDelete)(list);
}

/*
    Inserts a new item at the start (head) of the list.
    Same as 'LL_InsertAtHead' function.
*/
void CAT(LLInsert_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE item)
{
    CALL(LLInsertAtHead) (list, item);
}

/*
    Inserts a new item at the start (head) of the list.
    Same as 'LL_Insert' function.
*/
void CAT(LLInsertAtHead_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE item)
{
    Node* new_node = createNode(item);

    new_node->next = list->head;
    list->head = new_node;

    list->size++;
}

/*
    Inserts a new item at the end (tail) of the list.
    Requires linear list treversal!
*/
void CAT(LLInsertAtTail_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE item)
{
    if(CALL(LLIsEmpty)(list))
    {
        CALL(LLInsertAtHead)(list, item);
        return;
    }

    Node* current = list->head;
    Node* next = current->next;

    while(next != NULL)
    {
        current = next;
        next = current->next;
    }

    Node* new_node = createNode(item);
    insertNodeAt(new_node, current);
    list->size++;
}

/*
    Inserts a new item at the given position.
    Positions are 0-indexed, e.g. 'LLInsertAtPosition(list, item, 0) is the same as
    'LLInsertAtHead(list, item).
    Does nothing if 'position' is negative or greater than list size.
*/
void CAT(LLInsertAtPosition_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE item, int position)
{
    int list_size = CALL(LLSize)(list);
    if ((position < 0) || (position > list_size)) return;

    if (position == 0)
    {
        CALL(LLInsertAtHead)(list, item);
        return;
    }

    Node* current = list->head;

    int i=1; // Because 'list->head' is already position 0
    for (i=1; i<position; i++)
    {
        current = current->next;
    }

    Node* new_node = createNode(item);
    insertNodeAt(new_node, current);
    list->size++;
}

/*
    Returns the position of the first item that makes 'search_function(item, search_arg)' return
    any value different than 0.
    If 'search_function' is a comparator, this can be used to return the position of a given item on
    the list. 
    Returns -1 if no items in the list match the search.
    Positions are 0-indexed.
*/
int CAT(LLGetPositionBySearch_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE search_arg, \
                                              int(*search_function) (LL_ITEM_TYPE, LL_ITEM_TYPE))
{
    if (CALL(IsEmpty) (list)) return -1;

    int current_position = 0;
    Node* current = list->head;

    do
    {
        if (search_function(current->value, search_arg)) return current_position;
        current = current->next;
    } while(current != NULL);

    // Reached end of list.
    return -1;
}

/*
    Theverses the list in order and removes the position of the first item that makes 
    'search_function(item, search_arg)' return any value different than 0.
    If 'search_function' is a comparator, this can be used to remove an item with a given item velue. 
    Does nothing if no items in the list match the search.
*/
void CAT(LLRemoveBySearch_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE search_arg, \
                                         int (*search_function) (LL_ITEM_TYPE, LL_ITEM_TYPE))
{
    if (CALL(IsEmpty) (list)) return; // List is empty

    Node* current = list->head;
    Node* next = current->next;

    //First item matches
    if (search_function(current->value, search_arg))
    {
        CALL(LLRemoveHead)(list);
        return;
    }

    //Search for matches in other items
    while(next != NULL)
    {
        if (search_function(next->value, search_arg))
        {
            current->next = next->next;
            free(next);
            list->size--;
            return;
        }
    }

    // Reached end of list.
    return;
}

/*
    Removes the item in the given position in the list. Does not return the removed item.
    Does nothing if the position is negative or greater than (list size-1). (list positions are 
    0-indexed).
    If you want to get the item as a return, use either the 'LLTake' or 'LLFind' functions.
*/
void CAT(LLRemoveByPosition_,LL_ITEM_TYPE) (LL_TYPE* list, int position)
{
    int list_size = CALL(LLSize)(list);
    if ((position < 0) || (position > list_size-1)) return;

    if(position == 0)
    {
        CALL(LLRemoveHead)(list);
        return;
    }

    Node* current = list->head;
    Node* next = current->next;

    int i=1;
    for (i=1; i<list_size; i++)
    {
        current = next;
        next = current->next;
    }

    current->next = next->next;
    free(next);
    list->size--;
}

/*
    Removes the item at the start (head) of the list. Does not return the removed item.
    Does nothing if the list is empty.
    If you want to get the item as a return, use either the 'LLGetHead' or 'LLTakeHead' functions. 
*/
void CAT(LLRemoveHead_,LL_ITEM_TYPE) (LL_TYPE* list)
{
    if (CALL(LLIsEmpty)(list)) return;
    Node* old_head = list->head;
    list->head = old_head->next;
    free(old_head);
    list->size--;
}

/*
    Removes the item at the end (tail) of the list. Does not return the removed item.
    If you want to get the item as a return, use either the 'LLGetTail' or 'LLTakeTail' functions.
    Requires Linear list treversal!
*/
void CAT(LLRemoveTail_,LL_ITEM_TYPE) (LL_TYPE* list)
{
    if (CALL(LLIsEmpty)(list)) return;

    int list_size = CALL(LLSize)(list);

    if (list_size == 1)
    {
        CALL(LLRemoveHead)(list);
        return;
    }

    Node* current = list->head;
    Node* next = current->next;

    int i=1;
    for (i=1; i<list_size; i++)
    {
        current = next;
        next = current->next;
    }

    current->next = next->next;
    free(next);
    list->size--;
}

/*
    Theverses the list in order and returns the first item that makes 
    'search_function(item, search_arg)' return any value different than 0.
    If 'search_function' is a comparator, this can be used to find an item with a given value. 
    Does nothing if no items in the list match the search.
*/
LL_ITEM_TYPE CAT(LLFindBySearch_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE search_arg, \
                                               int (*search_function) (LL_ITEM_TYPE, LL_ITEM_TYPE))
{
    Node* current = list->head;
    while (current != NULL)
    {
        if (search_function(current->value, search_arg)) return current->value;
    }

    // No matching items found
    return NULL;
}

/*
    Returns the item in the given position in the list. Does not remove the fount item.
    If you want to remove the item, use either the 'LLRemove' or 'LLTake' functions.
    Returns NULL if 'position' is negative or greater than (list size-1) (list positions are
    0-indexed).
*/
LL_ITEM_TYPE CAT(LLFindByPosition_,LL_ITEM_TYPE) (LL_TYPE* list, int position)
{
    int list_size = CALL(LLSize)(list);
    if (position < 0 || position >= list_size+1) return NULL;

    Node* current = list->head;
    int i=0;
    for (i=0; i<position; i++)
    {
        current = current->next;
    }

    return current->value;
}

/*
    Returns the item at the start (head) of the list. Does not remove the returned item.
    Returns NULL if the list is empty.
    If you want to remove the returned item, use either the 'LLRemoveHead' or 'LLTakeHead' functions.
*/
LL_ITEM_TYPE CAT(LLGetHead_,LL_ITEM_TYPE) (LL_TYPE* list)
{
    return list->head->value;
}

/*
    Returns the item at the end (tail) of the list. Does not remove the returned item.
    Returns NULL if the list is empty.
    If you want to remove the returned item, use either the 'LLRemoveTail' or 'LLTakeTail' functions.
    Requires linear list treversal!
*/
LL_ITEM_TYPE CAT(LLGetTail_,LL_ITEM_TYPE) (LL_TYPE* list)
{
    int list_size = CALL(LLSiza)(list);
    Node* current = list->head;

    int i=0;
    for (i=0; i<list_size-1; i++)
    {
        current = current->next;
    }

    return current->value;
}

/*
    Treverses the list in order and removes and returns the first item that makes 
    'search_function(item, search_arg)' return any value different than 0.
    If 'search_function' is a comparator, this can be used to find an item with a given value. 
    Removes nothing and returns NULL if no items in the list match the search.
*/
LL_ITEM_TYPE CAT(LLTakeByValue,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE search_arg, \
                                              int (*search_function) (LL_ITEM_TYPE, LL_ITEM_TYPE))
{
    if (CALL(IsEmpty) (list)) return; // List is empty

    Node* current = list->head;
    Node* next = current->next;

    //First item matches
    if (search_function(current->value, search_arg))
    {
        LL_ITEM_TYPE return_value = current->value;
        list->head = next;
        free(current);
        list->size--;
        return return_value;
    }

    //Search for matches in other items
    while(next != NULL)
    {
        if (search_function(next->value, search_arg))
        {
            LL_ITEM_TYPE return_value = next->value;
            current->next = next->next;
            free(next);
            list->size--;
            return return_value;
        }
    }

    // Reached end of list.
    return NULL;
}

/*
    Removes and returns the item in the given position in the list.
    Removes nothing and returns NULL if 'position' is negative or greater than (list size-1)
    (list positions are 0-indexed).
*/
LL_ITEM_TYPE CAT(LLTakeByPosition_,LL_ITEM_TYPE) (LL_TYPE* list, int position)
{
    int list_size = CALL(LLSize)(list);
    if ((position < 0) || (position > list_size-1)) return;

    if(position == 0) return CALL(LLTakeHead)(list);

    Node* current = list->head;
    Node* next = current->next;

    int i=1;
    for (i=1; i<list_size; i++)
    {
        current = next;
        next = current->next;
    }

    LL_ITEM_TYPE return_value = next->value;
    current->next = next->next;
    free(next);
    list->size--;
    return return_value;
}

/*
    Removes and eturns the item at the start (head) of the list.
    Removes nothing and returns NULL if the list is empty.
*/
LL_ITEM_TYPE CAT(LLTakeHead_,LL_ITEM_TYPE) (LL_TYPE* list)
{
    LL_ITEM_TYPE return_value = CALL(LLGetHead) (list);
    CALL(LLRemoveHead) (list);
    return return_value;
}

/*
    Removes and eturns the item at the end (tail) of the list.
    Removes nothing and returns NULL if the list is empty.
*/
LL_ITEM_TYPE CAT(LLTakeTail_,LL_ITEM_TYPE) (LL_TYPE* list)
{
    if (CALL(LLIsEmpty)(list)) return;

    int list_size = CALL(LLSize)(list);

    if (list_size == 1) return CALL(LLTakeHead) (list);

    Node* current = list->head;
    Node* next = current->next;

    int i=1;
    for (i=1; i<list_size; i++)
    {
        current = next;
        next = current->next;
    }

    LL_ITEM_TYPE return_value = next->value;
    current->next = next->next;
    free(next);
    list->size--;
    return return_value;
}

/*
    Returns the number of items in a list.
*/
int inline CAT(LLSize_,LL_ITEM_TYPE) (LL_TYPE* list)
{
    return list->size;
}

/*
    Returns 1 if the list is empty.
    Returns 0 if not.
*/
int CAT(LLIsEmpty_,LL_ITEM_TYPE) (LL_TYPE* list)
{
    return list->size == 0;
}

/*
    Calls the given function for each item in the list, passing that item as argument.
    'function' must receive only one argument, of type LL_ITEM_TYPE.
    If you want to use a function with arguments, use 'LLTreverseArg' instead.
    
    If you want to fetch any data from the treversal, you can use 'LLTreverseArg', pass 'arg' as a 
    pointer to a struct and have 'function' modify the values in that struct
*/
void CAT(LLTreverse_,LL_ITEM_TYPE) (LL_TYPE* list, void (*function) (LL_ITEM_TYPE))
{
    Node* current = list->head;

    while(current != NULL)
    {
        function(current->value);
        current = current->next;
    }
}

/*
    Calls the given function for each item in the list, passing that item and 'arg' as arguments.
    'function' must receive only two arguments, of type LL_ITEM_TYPE and void*, respectively.
    
    If you want to fetch any data from the treversal, you can use 'LLTreverseArg', pass 'arg' as a 
    pointer to a struct and have 'function' modify the values in that struct.
*/
void CAT(LLTreverseArg_,LL_ITEM_TYPE) (LL_TYPE* list, void (*function) (LL_ITEM_TYPE, void*), void* arg)
{
    Node* current = list->head;

    while(current != NULL)
    {
        function(current->value, arg);
        current = current->next;
    }
}