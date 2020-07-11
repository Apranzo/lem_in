#include "../includes/ft_hash.h"

/* String hash function */

size_t ft_hash(pointer pointer)
{
	/* This is the djb2 string hash function */

	size_t result = 5381;
	unsigned char *p;

	p = (unsigned char *) pointer;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}

	return result;
}

/* The same function, with a tolower on every character so that
 * case is ignored.  This code is duplicated for performance. */

size_t string_nocase_hash(pointer string)
{
	size_t result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + (size_t) ft_tolower(*p);
		++p;
	}

	return result;
}


size_t int_hash(pointer pointer)
{
	return (*((size_t*) pointer));
}

size_t pointer_hash(pointer pointer)
{
	return (*((size_t *) pointer));
}