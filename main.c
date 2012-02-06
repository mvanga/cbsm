#include "f_cbsf.h"

#define TEST_FILE "test.cbsf"

void gen()
{
	FILE *f = fopen(TEST_FILE, "w");
	struct cbsf_line *l;
	struct cbsf_header *head = cbsf_header_create(0, 1,
		CBSF_FILE_SCHEMATIC);

	printf("Created header:\n");
	cbsf_header_write(f, head);
	cbsf_header_free(head);
	head = NULL;

	l = cbsf_line_create(0xa, 0xb, 0xc, 0xd);
	cbsf_line_write(f, l);
	cbsf_line_free(l);

	l = cbsf_line_create(0xa, 0xb, 0xc, 0xd);
	cbsf_line_write(f, l);
	cbsf_line_free(l);

	fclose(f);
}

void dump()
{
	FILE *f;
	struct cbsf_header *head;
	struct cbsf_line *l;

	printf("\n\n");

	f = fopen(TEST_FILE, "r");
	head = cbsf_header_read(f);
	cbsf_header_print(head);

	l = cbsf_line_read(f);
	cbsf_line_print(l);
	l = cbsf_line_read(f);
	cbsf_line_print(l);

	fclose(f);
}

int main()
{
	gen();
	dump();

	return 0;
}
