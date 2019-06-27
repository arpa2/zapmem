#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include <arpa2/zapmem.h>

int main (int argc, char *argv []) {
	printf ("Zapping NULL pointer...\n");
	arpa2_zapmem (NULL, 123);
	printf ("Allocating 123 bytes...\n");
	void *m = malloc (123);
	if (m == NULL) {
		exit (1);
	}
	printf ("Zapping allocated bytes...\n");
	arpa2_zapmem (m, 123);
	printf ("Freeing memory...\n");
	free (m);
	printf ("Wiping variable with zapvar...\n");
	arpa2_zapvar (m);
	if (m != NULL) {
		exit (1);
	}
	return 0;
}
