/* Be sure to clear memory */


#include <stdlib.h>
#include <string.h>

#include <arpa2/zapmem.h>


/*
 * Define a simpler function than memset_s() to clear memory.
 * The implementation checks for mem==NULL with assert ()
 * and trusts the memsz without checking.
 */
void arpa2_zapmem (volatile void *mem, size_t memsz) {
	if (mem != NULL) {
		memset ((void *) mem, 0, memsz);
	}
}
