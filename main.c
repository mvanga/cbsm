#include "format_cbsm.h"

#define TEST_FILE "test.cbsm"

void gen()
{
	FILE *f = fopen(TEST_FILE, "w");
	struct cbsm_line *l;
	struct cbsm_header *head = cbsm_header_create(0, 1, 0);

	printf("Created header:\n");
	cbsm_header_write(f, head);
	cbsm_header_free(head);
	head = NULL;

	l = cbsm_line_create(0xa, 0xb, 0xc, 0xd);
	cbsm_line_write(f, l);
	cbsm_line_free(l);

	l = cbsm_line_create(0xa, 0xb, 0xc, 0xd);
	cbsm_line_write(f, l);
	cbsm_line_free(l);

	fclose(f);
}

void dump()
{
	FILE *f;
	struct cbsm_header *head;
	struct cbsm_line *l;

	printf("\n\n");

	f = fopen(TEST_FILE, "r");
	head = cbsm_header_read(f);
	cbsm_header_print(head);

	l = cbsm_line_read(f);
	cbsm_line_print(l);
	l = cbsm_line_read(f);
	cbsm_line_print(l);

	fclose(f);
}

int main()
{
	gen();
	dump();

	return 0;
}
