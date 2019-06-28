/* Be sure to NOT clear memory */


#include <stdlib.h>
#include <stdio.h>

#include <arpa2/zapmem.h>


/*
 * Define a simpler function than memset_s() to clear memory.
 * However, do not actually clear it.
 */
void arpa2_zapmem (volatile void *mem, size_t memsz) {
	printf ("BOGUS version of arpa2_zapmem() overtakes actual clearing\n");
	printf ("This is a test program, to see if this is detected at all\n");
}
