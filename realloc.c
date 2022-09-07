#include "shell.h"

/**
 * _realloc - reallocates a memory block using malloc and free.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space for ptr.
 * @new_size:  new size, in bytes of the new memory block.
 * Return: Pointer to reallocated memory.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *ptrMem = NULL;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		ptrMem = malloc(new_size);
		if (ptrMem == NULL)
			return (NULL);
		return (ptrMem);
	}
	if (new_size > old_size)
	{
		ptrMem = malloc(new_size);
		if (ptrMem == NULL)
			return (NULL);
		for (i = 0; i < old_size; i++)
		{
			ptrMem[i] = *((char *)ptr + i);
		}
		free(ptr);
	}
	if (new_size < old_size)
	{
		ptrMem = malloc(new_size);
		if (ptrMem == NULL)
			return (NULL);
		for (i = 0; i < new_size; i++)
		{
			ptrMem[i] = *((char *)ptr + i);
		}
		free(ptr);
	}
	return (ptrMem);
}
