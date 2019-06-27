/*** Be sure to clear memory ***/


#ifndef ARPA2_ZAPMEM_INCLUDED
#define ARPA2_ZAPMEM_INCLUDED


/*
 * Define a simpler function than memset_s() to clear memory.
 * The implementation checks for mem==NULL with assert ()
 * and trusts the memsz without checking.
 */
void arpa2_zapmem (volatile void *mem, size_t memsz);


/*
 * Define a utility to clear a variable.
 */
#define arpa2_zapvar(v) arpa2_zapmem (&(v), sizeof (v))


#endif /* ARPA2_ZAPMEM_INCLUDED */
