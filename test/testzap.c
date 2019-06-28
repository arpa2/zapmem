#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <arpa2/zapmem.h>


int main (int argc, char *argv []) {
	int errors = 0;
	int got_ctr = 0;
	int exp_ctr = 0;
	if (argc >= 2) {
		exp_ctr = atoi (argv [1]);
		got_ctr = 1;
	}
	printf ("Zapping NULL pointer...\n");
	arpa2_zapmem (NULL, 123);
	printf ("Allocating 123 bytes...\n");
	char *m = malloc (123);
	if (m == NULL) {
		fprintf (stderr, "malloc() failed\n");
		exit (1);
	}
	int i;
	for (i=0; i<123; i++) {
		m [i] = i + 1;
	}
	printf ("Zapping allocated bytes...\n");
	arpa2_zapmem (m, 123);
	for (i=0; i<123; i++) {
		if (m [i] != 0x00) {
			fprintf (stderr, "Byte at offset %d not cleared\n", i);
			errors++;
		}
	}
	printf ("Freeing memory...\n");
	free (m);
	printf ("Wiping variable with zapvar...\n");
	arpa2_zapvar (m);
	if (m != NULL) {
		fprintf (stderr, "Variable did not get wiped to NULL\n");
		errors++;
	}
	if (got_ctr) {
		if (errors != exp_ctr) {
			fprintf (stderr, "Found %d errors (expected %d)\n", errors, exp_ctr);
			errors++;
		} else {
			// Error count as expected -- which is good
			errors = 0;
		}
	}
	exit (errors);
}
