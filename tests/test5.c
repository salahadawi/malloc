#include "../includes/malloc.h"

int main()
{
	void *adr;

	adr = malloc(1024);
	adr = malloc(1024 * 32);
	adr = malloc(1024 * 1024);
	adr = malloc(1024 * 1024 * 16);
	adr = malloc(1024 * 1024 * 128);
	show_alloc_mem();
	return (0);
}
