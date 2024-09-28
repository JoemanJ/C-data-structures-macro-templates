#ifdef TST_ITEM_TYPE
#ifdef TST_FAIL_VALUE

#include "helper_macros.h"

#define TST_STRUCT CAT(tst_,TST_ITEM_TYPE)
#define TST_TYPE CAT(TST_,TST_ITEM_TYPE)

struct TST_STRUCT;
typedef struct TST_STRUCT TST_TYPE;

/*
    Cretes and returns a pointer to an empty TST.
*/
TST_TYPE* CAT(TSTCreate_,TST_ITEM_TYPE)();

/*
    Inserts a new item in the TST with the given key.
    If the key already exists, the item with that key is replaced.
    Returns the TST with the new item.
*/
TST_TYPE* CAT(TSTInsert_,TST_ITEM_TYPE)(TST_TYPE* tst, const char* key, TST_ITEM_TYPE item);

/*
    Returns the item with the given key.
    Returns TST_FAIL_VALUE if the key does not exist.
*/
TST_ITEM_TYPE CAT(TSTGet_,TST_ITEM_TYPE)(TST_TYPE* tst, char* key);

/*
    Returns an array with all keys in the TST.
    The array must be freed after use.
    Returns NULL if the TST is empty.
*/
char** CAT(TSTGetAllKeysWithValue,TST_ITEM_TYPE)(TST_TYPE* tst);

/*
    Removes the item with the given key.
    Does nothing if the key does not exist.
*/
TST_TYPE* CAT(TSTRemove_,TST_ITEM_TYPE)(TST_TYPE* tst, char* key);

/*
    Frees the memory allocated for the TST, but not for inserted items.
    If you want to free all inserted items, use 'TSTClear'.
    If you want to free memory for the TST and all it's items, use 'TSTClearAndDelete'.
    Always Returns NULL.
*/
TST_TYPE* CAT(TSTDelete_,TST_ITEM_TYPE)(TST_TYPE* tst);

/*
    Frees the memory allocated for all items in the TST.
    'item_delete_function' is called with each item in the TST as an argument.
    Always Returns NULL.
*/
void CAT(TSTClear_,TST_ITEM_TYPE)(TST_TYPE* tst, void (*item_delete_function) (TST_ITEM_TYPE));

/*
    Frees the memory allocated for all items in the TST, then frees all the memory allocated for the TST.
    Always Returns NULL.
*/
TST_TYPE* CAT(TSTClearAndDelete_,TST_ITEM_TYPE)(TST_TYPE* tst, void (*item_delete_function) (TST_ITEM_TYPE));

/*
    Calls the given function for each item in the TST, passing that item as argument.
    Treverses the TST in order.
    'function' must receive only one argument, of type TST_ITEM_TYPE.
    If you want to use a function with arguments, use 'TSTreverseArg' instead.
    
    If you want to fetch any data from the treversal, you can use 'TSTreverseArg', pass 'arg' as a 
    pointer to a struct and have 'function' modify the values in that struct
*/
void CAT(TSTTreversePreOrder_,TST_ITEM_TYPE)(TST_TYPE* tst, void (*function) (TST_ITEM_TYPE));

/*
    Calls the given function for each item in the TST, passing that item as argument.
    Treverses the TST post order.
    'function' must receive only one argument, of type TST_ITEM_TYPE.
    If you want to use a function with arguments, use 'TSTreverseArg' instead.
    
    If you want to fetch any data from the treversal, you can use 'TSTreverseArg', pass 'arg' as a 
    pointer to a struct and have 'function' modify the values in that struct
*/
void CAT(TSTTreversePostOrder_,TST_ITEM_TYPE)(TST_TYPE* tst, void (*function) (TST_ITEM_TYPE));

/*
    Calls the given function for each item in the TST, passing that item and 'arg' as arguments.
    Treverses the TST in order.
    'function' must receive only two arguments, of type TST_ITEM_TYPE and void*, respectively.
    
    If you want to fetch any data from the treversal, you can use 'TSTreverseArg', pass 'arg' as a 
    pointer to a struct and have 'function' modify the values in that struct.
*/
void CAT(TSTTreverseArgPreOrder_,TST_ITEM_TYPE)(TST_TYPE* tst, void (*function) (TST_ITEM_TYPE, void*), void* arg);

/*
    Calls the given function for each item in the TST, passing that item and 'arg' as arguments.
    Treverses the TST post order.
    'function' must receive only two arguments, of type TST_ITEM_TYPE and void*, respectively.
    
    If you want to fetch any data from the treversal, you can use 'TSTreverseArg', pass 'arg' as a 
    pointer to a struct and have 'function' modify the values in that struct.
*/
void CAT(TSTTreverseArgPostOrder_,TST_ITEM_TYPE)(TST_TYPE* tst, void (*function) (TST_ITEM_TYPE, void*), void* arg);

/*
    Calls the given function for each item in the TST, passing that item as argument.
    Treverses the TST in order.
    'function' must receive only one argument, of type TST_ITEM_TYPE.

    Print format is: <(key)(value)|left|down|right>
    For nodes with no value, the format is: <(key)|left|down|right>

    If you want to fetch any data from the treversal, you can use 'TSTreverseArg', pass 'arg' as a 
    pointer to a struct and have 'function' modify the values in that struct
*/
void CAT(TSTPrint_,TST_ITEM_TYPE)(TST_TYPE* tst, void (*item_print_function) (TST_ITEM_TYPE));

/*
    Returns 1 if the TST is empty, 0 otherwise.
*/
int CAT(TSTIsEmpty_,TST_ITEM_TYPE)(TST_TYPE* tst);

#undef TST_STRUCT
#undef TST_TYPE

#endif
#endif