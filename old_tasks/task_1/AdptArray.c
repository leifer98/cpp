#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct AdptArray_
{
    /* data */
    COPY_FUNC COPY;
    DEL_FUNC DEL;
    PRINT_FUNC PRINT;
    PElement *pArr;
    int size;
}AdptArray_;

// Allocate memory for a new AdptArray and initialize its properties.
PAdptArray CreateAdptArray(COPY_FUNC COPY, DEL_FUNC DEL, PRINT_FUNC PRINT)
{
    PAdptArray p = (PAdptArray)malloc(sizeof(AdptArray_));
    if (p == NULL)
    { 
        printf("Memory allocation failed.");
        return NULL;
    }
    p->COPY = COPY;
    p->DEL = DEL;
    p->PRINT = PRINT;
    p->pArr = (PElement*)calloc(1, sizeof(PElement));
    if (p->pArr == NULL)
    { 
        printf("Memory allocation failed.");
        free(p);
        return NULL; 
    }
    p->size = 0;

    return p;
}

// Delete an existing AdptArray and free all its associated memory.
void DeleteAdptArray(PAdptArray array)
{
    if (array == NULL) return;
    for (int i = 0; i < (array->size) ; i++)
    {
        if (((array->pArr)[i]) != NULL)
            array->DEL(((array->pArr)[i]));
    }
    if (array->pArr!= NULL) free(array->pArr);
    free(array);
}

// Set the element at the specified index in the AdptArray.
Result SetAdptArrayAt(PAdptArray array, int i, PElement element)
{
    if (i < 0 || array == NULL)
        return FAIL;
    // If the new index is greater than the array's current size, increase the size of the array.
    if (array->pArr==NULL || array->size <= i)
    {
        PElement *old = array->pArr;
        array->pArr = (PElement)calloc((i + 1),sizeof(PElement));
        if (array->pArr == NULL)
        { 
            printf("Memory allocation failed.");
            exit(1);
        }
        for (int i = 0; i < array->size; i++)
        {
            if (old[i] != NULL) {
                ((array->pArr)[i]) = array->COPY( old[i] );
                array->DEL( old[i] );
            }
        }
        if (old != NULL)
            free(old);
        array->size = i + 1;
    }
    // If the element at the specified index already exists, delete the old element first.
    else if ((array->pArr)[i] != NULL)
    {
        PElement old = ((array->pArr)[i]);
        array->DEL(old);
    }

    (array->pArr)[i] = array->COPY(element);

    return SUCCESS;
}

// retrieves an element at a specified index in the PAdptArray
PElement GetAdptArrayAt(PAdptArray array, int i)
{
    if (array->pArr == NULL)
        return NULL;
    if (i < 0 || i >= array->size)
        return NULL;
    if (((array->pArr)[i]) == NULL)
        return NULL;
    return array->COPY(((array->pArr)[i]));
}

// retrieves the size of the PAdptArray
int GetAdptArraySize(PAdptArray array)
{
    if (array == NULL) return -1;
    return array->size;
}

// prints the elements in the PAdptArray using the array's PRINT function
void PrintDB(PAdptArray array)
{
    if (array == NULL) return;
    if (array->pArr == NULL) return;
    if (array->PRINT == NULL) return;
    for (int i = 0; i < array->size; i++)
    {
        if (((array->pArr)[i]) != NULL)
            array->PRINT(((array->pArr)[i]));
    }
}