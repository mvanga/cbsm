/* This file is part of AndromEDA.
 *
 * AndromEDA is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AndromEDA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with AndromEDA.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "f_cbsf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cbsf_header *cbsf_header_read(FILE *stream)
{
	int ret;
	struct cbsf_header *header = NULL;

	if (!stream) {
		printf("error: stream is NULL\n");
		return NULL;
	}
	header = (struct cbsf_header *)malloc(sizeof(struct cbsf_header));
	if (!header) {
		printf("failed to allocate header\n");
		return NULL;
	}
	if (fseek(stream, 0, SEEK_SET) < 0) {
		printf("error seeking\n");
		free(header);
		return NULL;
	}
	ret = fread((void *)header, sizeof(struct cbsf_header), 1, stream);
	if (ret < 0) {
		printf("failed to read stream");
		free(header);
		return NULL;
	}
	return header;
}

void cbsf_header_print(struct cbsf_header *header)
{
	printf("Version: %d:%d\n", header->version.ver_major, header->version.ver_minor);
	printf("Magic: %04x\n", header->magic);
	printf("Flags: %08x\n", header->flags);

	return;
}

struct cbsf_header *cbsf_header_create(uint8_t vmaj, uint8_t vmin,
	uint32_t flags)
{
	struct cbsf_header *header = NULL;

	header = (struct cbsf_header *)malloc(sizeof(struct cbsf_header));
	if (!header) {
		printf("failed to allocate header\n");
		return NULL;
	}
	memset(header, 0, sizeof(struct cbsf_header));
	header->version.ver_major = vmaj;
	header->version.ver_minor = vmin;
	header->magic = CBSF_HEADER_MAGIC;
	header->flags = flags;

	return header;
}

int cbsf_header_write(FILE *stream, struct cbsf_header *header)
{
	int ret;

	if (!stream || !header) {
		printf("error: stream/header is NULL\n");
		return -1;
	}
	ret = fwrite((void *)header, sizeof(struct cbsf_header), 1, stream);
	if (ret < 0) {
		printf("failed to write stream");
		free(header);
		return ret;
	}
}

void cbsf_header_free(struct cbsf_header *header)
{
	if (header)
		free(header);
}
