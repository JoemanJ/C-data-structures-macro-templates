#ifdef TST_ITEM_TYPE

#include "ternary_search_tri.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TST_STRUCT CAT(tst_,TST_ITEM_TYPE)
#define TST_TYPE CAT(TST_,TST_ITEM_TYPE)

/*
    For calling a TST function for the type at hand.
*/
#define CALL(f) CAT(f##_,TST_ITEM_TYPE)

struct TST_STRUCT
{
    char key;
    TST_ITEM_TYPE value;
    char has_value;

    TST_TYPE* left;
    TST_TYPE* down;
    TST_TYPE* right;
};

static TST_TYPE* newNode(char key, TST_ITEM_TYPE value, char has_value)
{
    TST_TYPE* new_node = (TST_TYPE*) malloc(sizeof(TST_TYPE));

    new_node->key = key;
    new_node->value = value;
    new_node->has_value = has_value;
    new_node->left = NULL;
    new_node->down = NULL;
    new_node->right = NULL;

    return new_node;
}

TST_TYPE* CAT(TSTCreate_,TST_ITEM_TYPE)()
{
    return NULL;
}

TST_TYPE* CAT(TSTInsert_,TST_ITEM_TYPE)(TST_TYPE* tst, const char* key, TST_ITEM_TYPE item)
{
    if (key[0] == '\0')
    {
        return tst;
    }

    int is_last_char = (key[1] == '\0');

    if (tst == NULL)
    {
        tst = newNode(key[0], item, is_last_char);
    }
    
    if (key[0] < tst->key)
    {
        tst->left = CALL(TSTInsert)(tst->left, key, item);
        return tst;
    }

    if (key[0] > tst->key)
    {
        tst->right = CALL(TSTInsert)(tst->right, key, item);
        return tst;
    }

    // key[0] == tst->key
    if (is_last_char)
    {
        tst->value = item;
        tst->has_value = 1;
        return tst;
    }

    else
    {
        tst->down = CALL(TSTInsert)(tst->down, &(key[1]), item);
        return tst;
    }
}

TST_ITEM_TYPE CAT(TSTGet_,TST_ITEM_TYPE)(TST_TYPE* tst, char* key)
{
    int is_last_char = (key[1] == '\0');

    if (tst == NULL)
    {
        return TST_FAIL_VALUE;
    }

    if (key[0] < tst->key)
    {
        return CALL(TSTGet)(tst->left, key);
    }

    if (key[0] > tst->key)
    {
        return CALL(TSTGet)(tst->right, key);
    }

    // key[0] == tst->key
    if (is_last_char)
    {
        if (tst->has_value)
        {
            return tst->value;
        }

        else
        {
            return TST_FAIL_VALUE;
        }
    }

    else
    {
        return CALL(TSTGet)(tst->down, &(key[1]));
    }
}

static void fillKeys(int current_index, TST_TYPE* tst, char** current_key, \
                     char*** all_keys, int* current_keys_stored, int* max_key_length)
{
    if (tst == NULL)
    {
        return;
    }

    if(current_index >= (*max_key_length))
    {
        char* temp_key = realloc((*current_key), sizeof(char) * ((*max_key_length) * 2));
        if (temp_key == NULL) {
            printf("ERROR REALLOCING current_key\n");
            exit(1);
        }
        (*current_key) = temp_key;
        (*max_key_length) *= 2;
    }

    (*current_key)[current_index] = tst->key;

    if (tst->has_value)
    {
        char** temp_keys = realloc((*all_keys), sizeof(char*) * ((*current_keys_stored) + 1));
        if (temp_keys == NULL) {
            printf("ERROR REALLOCING all_keys\n");
            exit(1);
        }
        (*all_keys) = temp_keys;
        (*all_keys)[(*current_keys_stored)] = (char*) malloc(sizeof(char) * ((current_index+1) + 1));
        strncpy((*all_keys)[(*current_keys_stored)], (*current_key), current_index+1);
        (*all_keys)[(*current_keys_stored)][current_index+1] = '\0';
        (*current_keys_stored)++;
    }

    fillKeys(current_index, tst->left, current_key, all_keys, current_keys_stored, max_key_length);
    (*current_key)[current_index] = tst->key;
    fillKeys(current_index, tst->right, current_key, all_keys, current_keys_stored, max_key_length);
    (*current_key)[current_index] = tst->key;
    fillKeys(current_index+1, tst->down, current_key, all_keys, current_keys_stored, max_key_length);
}

char** CAT(TSTGetAllKeysWithValue,TST_ITEM_TYPE)(TST_TYPE* tst)
{
    if (tst == NULL) return NULL;

    char** all_keys = (char**) malloc(sizeof(char*) * 1);
    char* current_key = (char*) malloc(sizeof(char) * 50);
    int max_key_length = 50;
    int current_keys_stored = 0;

    fillKeys(0, tst, &current_key, &all_keys, &current_keys_stored, &max_key_length);

    free(current_key);

    return all_keys;
}

TST_TYPE* CAT(TSTRemove_,TST_ITEM_TYPE)(TST_TYPE* tst, char* key)
{
    int is_last_char = (key[1] == '\0');

    if (tst == NULL)
    {
        return tst;
    }

    if (key[0] < tst->key)
    {
        tst->left = CALL(TSTRemove)(tst->left, key);

        // If the node has no children and no value, it can be removed.
        if(tst->has_value == 0 && tst->left == NULL && tst->down == NULL && tst->right == NULL)
        {
            free(tst);
            return NULL;
        }

        return tst;
    }

    if (key[0] > tst->key)
    {
        tst->right = CALL(TSTRemove)(tst->right, key);

        if(tst->has_value == 0 && tst->left == NULL && tst->down == NULL && tst->right == NULL)
        {
            free(tst);
            return NULL;
        }

        return tst;
    }

    // key[0] == tst->key
    if (is_last_char)
    {
        tst->has_value = 0;

        // If the node has no children and no value, it can be removed.
        if(tst->left == NULL && tst->down == NULL && tst->right == NULL)
        {
            free(tst);
            return NULL;
        }

        return tst;
    }

    else
    {
        tst->down = CALL(TSTRemove)(tst->down, &(key[1]));

        // If the node has no children and no value, it can be removed.
        if(tst->has_value == 0 && tst->left == NULL && tst->down == NULL && tst->right == NULL)
        {
            free(tst);
            return NULL;
        }

        return tst;
    }
}

TST_TYPE* CAT(TSTDelete_,TST_ITEM_TYPE)(TST_TYPE* tst)
{
    if (tst == NULL)
    {
        return NULL;
    }

    CALL(TSTDelete)(tst->left);
    CALL(TSTDelete)(tst->down);
    CALL(TSTDelete)(tst->right);

    free(tst);
    return NULL;
}

void CAT(TSTClear_,TST_ITEM_TYPE)(TST_TYPE* tst, void (*item_delete_function) (TST_ITEM_TYPE))
{
    if (tst == NULL)
    {
        return;
    }

    CALL(TSTClear)(tst->left, item_delete_function);
    CALL(TSTClear)(tst->down, item_delete_function);
    CALL(TSTClear)(tst->right, item_delete_function);

    if (tst->has_value)
    {
        item_delete_function(tst->value);
    }
}

TST_TYPE* CAT(TSTClearAndDelete_,TST_ITEM_TYPE)(TST_TYPE* tst, void (*item_delete_function) (TST_ITEM_TYPE))
{
    if (tst == NULL)
    {
        return NULL;
    }

    CALL(TSTClearAndDelete)(tst->left, item_delete_function);
    CALL(TSTClearAndDelete)(tst->down, item_delete_function);
    CALL(TSTClearAndDelete)(tst->right, item_delete_function);

    if (tst->has_value)
    {
        item_delete_function(tst->value);
    }
    
    free(tst);
    return NULL;
}

void CAT(TSTTreversePreOrder_,TST_ITEM_TYPE)(TST_TYPE* tst, void (*function) (TST_ITEM_TYPE))
{
    if (tst == NULL)
    {
        return;
    }

    function(tst->value);
    CALL(TSTTreversePreOrder)(tst->right, function);
    CALL(TSTTreversePreOrder)(tst->down, function);
    CALL(TSTTreversePreOrder)(tst->left, function);
}

void CAT(TSTTreversePostOrder_,TST_ITEM_TYPE)(TST_TYPE* tst, void (*function) (TST_ITEM_TYPE))
{
    if (tst == NULL)
    {
        return;
    }

    CALL(TSTTreversePostOrder)(tst->right, function);
    CALL(TSTTreversePostOrder)(tst->down, function);
    CALL(TSTTreversePostOrder)(tst->left, function);
    function(tst->value);
}

void CAT(TSTTreverseArgPreOrder_,TST_ITEM_TYPE)
    (TST_TYPE* tst, void (*function) (TST_ITEM_TYPE, void*), void* arg)
{
    if (tst == NULL)
    {
        return;
    }

    function(tst->value, arg);
    CALL(TSTTreverseArgPreOrder)(tst->right, function, arg);
    CALL(TSTTreverseArgPreOrder)(tst->down, function, arg);
    CALL(TSTTreverseArgPreOrder)(tst->left, function, arg);
}

void CAT(TSTTreverseArgPostOrder_,TST_ITEM_TYPE)
    (TST_TYPE* tst, void (*function) (TST_ITEM_TYPE, void*), void* arg)
{
    if (tst == NULL)
    {
        return;
    }

    CALL(TSTTreverseArgPostOrder)(tst->right, function, arg);
    CALL(TSTTreverseArgPostOrder)(tst->down, function, arg);
    CALL(TSTTreverseArgPostOrder)(tst->left, function, arg);
    function(tst->value, arg);
}

void CAT(TSTPrint_,TST_ITEM_TYPE)(TST_TYPE* tst, void (*item_print_function) (TST_ITEM_TYPE))
{
    if (tst == NULL)
    {
        return;
    }

    printf("<(%c)", tst->key);

    if(tst->has_value)
    {
        printf("(");
        item_print_function(tst->value);
        printf(")");
    }
    printf("|");
    CALL(TSTPrint)(tst->left, item_print_function);
        printf("|");
    CALL(TSTPrint)(tst->down, item_print_function);
        printf("|");
    CALL(TSTPrint)(tst->right, item_print_function);
    printf(">");
}

int CAT(TSTIsEmpty_,TST_ITEM_TYPE)(TST_TYPE* tst)
{
    return tst == NULL;
}

#undef TST_STRUCT
#undef TST_TYPE

#endif