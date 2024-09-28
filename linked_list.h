#ifdef LL_ITEM_TYPE

#include "helper_macros.h"

//TODO: Add some check here so that a second list of the same type cannot be created.
// ifndef LIST_$(LL_ITEM_TYPE), something like that... 

#define LL_STRUCT CAT(list_,LL_ITEM_TYPE)
#define LL_TYPE CAT(List_,LL_ITEM_TYPE)

struct LL_STRUCT;
typedef struct LL_STRUCT LL_TYPE;

/*
    Creates an empty LL_ITEM_TYPE list and returns a pointer to it
*/
LL_TYPE* CAT(LLCreate_,LL_ITEM_TYPE)();

/*
    Frees memory of a LL_ITEM_TYPE list, but does not free any of the list's items.
    If you want to free memory for each item as well, use 'LLClearAndDelete_LLITEM_TYPE'.

    Always returns NULL.
*/
LL_TYPE* CAT(LLDelete_,LL_ITEM_TYPE) (LL_TYPE* list);

/*
    Frees memory of all items in a list.
    The passed 'item_delete_function' is called with each item in the list as an
    argument.
*/
void CAT(LLClear_,LL_ITEM_TYPE) (LL_TYPE* list, \
                                 void (*item_delete_function) (LL_ITEM_TYPE));

/*
    Frees memory of all items in a list, then frees all the memory allocated for the list.

    Always returns NULL.
*/
LL_TYPE* CAT(LLClearAndDelete_,LL_ITEM_TYPE) (LL_TYPE* list, \
                                              void (*item_delete_function) (LL_ITEM_TYPE));

/*
    Inserts a new item at the start (head) of the list.
    Same as 'LL_InsertAtHead' function.
*/
void CAT(LLInsert_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE item);

/*
    Inserts a new item at the start (head) of the list.
    Same as 'LL_Insert' function.
*/
void CAT(LLInsertAtHead_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE item);

/*
    Inserts a new item at the end (tail) of the list.
    Requires linear list treversal!
*/
void CAT(LLInsertAtTail_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE item);

/*
    Inserts a new item at the given position.
    Positions are 0-indexed, e.g. 'LLInsertAtPosition(list, item, 0) is the same as
    'LLInsertAtHead(list, item).
    Does nothing if 'position' is negative or greater than list size.
*/
void CAT(LLInsertAtPosition_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE item, int position);

/*
    Returns the position of the first item that makes 'search_function(item, search_arg)' return
    any value different than 0.
    If 'search_function' is a comparator, this can be used to return the position of a given item on
    the list. 
    Returns -1 if no items in the list match the search.
    Positions are 0-indexed.
*/
int CAT(LLGetPositionBySearch_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE search_arg, \
                                              int(*search_function) (LL_ITEM_TYPE, LL_ITEM_TYPE));

//TODO: add LLGetPositionByCompare, LLRemoveByCompare, LLFindByCompare and LLTakeByCompare

/*
    Treverses the list in order and removes the position of the first item that makes 
    'search_function(item, search_arg)' return any value different than 0.
    If 'search_function' is a comparator, this can be used to remove an item with a given value. 
    Does nothing if no items in the list match the search.
*/
void CAT(LLRemoveBySearch_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE search_arg, \
                                         int (*search_function) (LL_ITEM_TYPE, LL_ITEM_TYPE));

/*
    Removes the item in the given position in the list. Does not return the removed item.
    Does nothing if the position is negative or greater than (list size-1). (list positions are 
    0-indexed).
    If you want to get the item as a return, use either the 'LLTake' or 'LLFind' functions.
*/
void CAT(LLRemoveByPosition_,LL_ITEM_TYPE) (LL_TYPE* list, int position);

/*
    Removes the item at the start (head) of the list. Does not return the removed item.
    Does nothing if the list is empty.
    If you want to get the item as a return, use either the 'LLGetHead' or 'LLTakeHead' functions. 
*/
void CAT(LLRemoveHead_,LL_ITEM_TYPE) (LL_TYPE* list);

/*
    Removes the item at the end (tail) of the list. Does not return the removed item.
    If you want to get the item as a return, use either the 'LLGetTail' or 'LLTakeTail' functions.
    Requires Linear list treversal!
*/
void CAT(LLRemoveTail_,LL_ITEM_TYPE) (LL_TYPE* list);

#ifdef LL_FAIL_VALUE
/*
    Treverses the list in order and returns the first item that makes 
    'search_function(item, search_arg)' return any value different than 0.
    If 'search_function' is a comparator, this can be used to find an item with a given value. 
    Returns LL_FAIL_VALUE if no items in the list match the search.
*/
LL_ITEM_TYPE CAT(LLFindBySearch_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE search_arg, \
                                               int (*search_function) (LL_ITEM_TYPE, LL_ITEM_TYPE));

/*
    Returns the item in the given position in the list. Does not remove the fount item.
    If you want to remove the item, use either the 'LLRemove' or 'LLTake' functions.
    Returns LL_FAIL_VALUE if 'position' is negative or greater than (list size-1) (list positions are
    0-indexed).
*/
LL_ITEM_TYPE CAT(LLFindByPosition_,LL_ITEM_TYPE) (LL_TYPE* list, int position);

/*
    Returns the item at the start (head) of the list. Does not remove the returned item.
    Returns LL_FAIL_VALUE if the list is empty.
    If you want to remove the returned item, use either the 'LLRemoveHead' or 'LLTakeHead' functions.
*/
LL_ITEM_TYPE CAT(LLGetHead_,LL_ITEM_TYPE) (LL_TYPE* list);

/*
    Returns the item at the end (tail) of the list. Does not remove the returned item.
    Returns LL_FAIL_VALUE if the list is empty.
    If you want to remove the returned item, use either the 'LLRemoveTail' or 'LLTakeTail' functions.
    Requires linear list treversal!
*/
LL_ITEM_TYPE CAT(LLGetTail_,LL_ITEM_TYPE) (LL_TYPE* list);

/*
    Treverses the list in order and removes and returns the first item that makes 
    'search_function(item, search_arg)' return any value different than 0.
    If 'search_function' is a comparator, this can be used to find an item with a given value. 
    Removes nothing and returns LL_FAIL_VALUE if no items in the list match the search.
*/
LL_ITEM_TYPE CAT(LLTakeBySearch_,LL_ITEM_TYPE) (LL_TYPE* list, LL_ITEM_TYPE search_arg, \
                                              int (*search_function) (LL_ITEM_TYPE, LL_ITEM_TYPE));

/*
    Removes and returns the item in the given position in the list.
    Removes nothing and returns LL_FAIL_VALUE if 'position' is negative or greater than (list size-1)
    (list positions are 0-indexed).
*/
LL_ITEM_TYPE CAT(LLTakeByPosition_,LL_ITEM_TYPE) (LL_TYPE* list, int position);

/*
    Removes and returns the item at the start (head) of the list.
    Removes nothing and returns LL_FAIL_VALUE if the list is empty.
*/
LL_ITEM_TYPE CAT(LLTakeHead_,LL_ITEM_TYPE) (LL_TYPE* list);

/*
    Removes and returns the item at the end (tail) of the list.
    Removes nothing and returns LL_FAIL_VALUE if the list is empty.
*/
LL_ITEM_TYPE CAT(LLTakeTail_,LL_ITEM_TYPE) (LL_TYPE* list);
#endif

/*
    Returns the number of items in a list.
*/
int CAT(LLSize_,LL_ITEM_TYPE) (LL_TYPE* list);

/*
    Returns 1 if the list is empty.
    Returns 0 if not.
*/
int CAT(LLIsEmpty_,LL_ITEM_TYPE) (LL_TYPE* list);

/*
    Calls the given function for each item in the list, passing that item as argument.
    'function' must receive only one argument, of type LL_ITEM_TYPE.
    If you want to use a function with arguments, use 'LLTreverseArg' instead.
    
    If you want to fetch any data from the treversal, you can use 'LLTreverseArg', pass 'arg' as a 
    pointer to a struct and have 'function' modify the values in that struct
*/
void CAT(LLTreverse_,LL_ITEM_TYPE) (LL_TYPE* list, void (*function) (LL_ITEM_TYPE));

/*
    Calls the given function for each item in the list, passing that item and 'arg' as arguments.
    'function' must receive only two arguments, of type LL_ITEM_TYPE and void*, respectively.
    
    If you want to fetch any data from the treversal, you can use 'LLTreverseArg', pass 'arg' as a 
    pointer to a struct and have 'function' modify the values in that struct.
*/
void CAT(LLTreverseArg_,LL_ITEM_TYPE) (LL_TYPE* list, void (*function) (LL_ITEM_TYPE, void*), void* arg);

#undef LL_STRUCT
#undef LL_TYPE

#endif