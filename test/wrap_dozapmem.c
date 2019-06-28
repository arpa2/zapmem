/* Be sure to clear memory but DO NOT increment the counter */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <arpa2/zapmem.h>


/*
 * Define a simpler function than memset_s() to clear memory.
 * However, do not actually clear it.
 */
void arpa2_zapmem (volatile void *mem, size_t memsz) {
	printf ("TEST version of arpa2_zapmem() overtakes library call\n");
	printf ("This is a test program, to see if the counter is tested\n");
	memset ((void *) mem, 0, memsz);
}
