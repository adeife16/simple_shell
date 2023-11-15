#include "main.h"

/**
 * _memoryCopy - copies information between void pointers.
 * @newPtr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void _memoryCopy(void *newPtr, const void *ptr, unsigned int size)
{
    char *charPtr = (char *)ptr;
    char *charNewPtr = (char *)newPtr;
    unsigned int i;

    for (i = 0; i < size; i++)
      charNewPtr[i] = charPtr[i];
}

/**
 * _reallocate - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @oldSize: size, in bytes, of the allocated space of ptr.
 * @newSize: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if newSize == oldSize, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_reallocate(void *ptr, unsigned int oldSize, unsigned int newSize)
{
    void *newPtr;

    if (ptr == NULL)
      return (malloc(newSize));

    if (newSize == 0)
    {
      free(ptr);
      return (NULL);
    }

    if (newSize == oldSize)
      return (ptr);

    newPtr = malloc(newSize);
    if (newPtr == NULL)
      return (NULL);

    if (newSize < oldSize)
      _memoryCopy(newPtr, ptr, newSize);
    else
      _memoryCopy(newPtr, ptr, oldSize);

    free(ptr);
    return (newPtr);
}

/**
 * myReallocDP - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @oldSize: size, in bytes, of the allocated space of ptr.
 * @newSize: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if newSize == oldSize, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_reallocateDoublePointer(char **ptr, unsigned int oldSize, unsigned int newSize)
{
    char **newPtr;
    unsigned int i;

    if (ptr == NULL)
      return (malloc(sizeof(char *) * newSize));

    if (newSize == oldSize)
      return (ptr);

    newPtr = malloc(sizeof(char *) * newSize);
    if (newPtr == NULL)
      return (NULL);

    for (i = 0; i < oldSize; i++)
      newPtr[i] = ptr[i];

    free(ptr);

    return (newPtr);
}
