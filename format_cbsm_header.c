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

#include "format_cbsm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cbsm_header *cbsm_header_read(FILE *stream)
{
	int ret;
	struct cbsm_header *header = NULL;

	if (!stream) {
		printf("error: stream is NULL\n");
		return NULL;
	}
	header = (struct cbsm_header *)malloc(sizeof(struct cbsm_header));
	if (!header) {
		printf("failed to allocate header\n");
		return NULL;
	}
	if (fseek(stream, 0, SEEK_SET) < 0) {
		printf("error seeking\n");
		free(header);
		return NULL;
	}
	ret = fread((void *)header, sizeof(struct cbsm_header), 1, stream);
	if (ret < 0) {
		printf("failed to read stream");
		free(header);
		return NULL;
	}
	return header;
}

void cbsm_header_print(struct cbsm_header *header)
{
	printf("Version: %d:%d\n", header->version.ver_major, header->version.ver_minor);
	printf("Magic: %04x\n", header->magic);
	printf("Flags: %08x\n", header->flags);

	return;
}

struct cbsm_header *cbsm_header_create(uint8_t vmaj, uint8_t vmin,
	uint32_t flags)
{
	struct cbsm_header *header = NULL;

	header = (struct cbsm_header *)malloc(sizeof(struct cbsm_header));
	if (!header) {
		printf("failed to allocate header\n");
		return NULL;
	}
	memset(header, 0, sizeof(struct cbsm_header));
	header->version.ver_major = vmaj;
	header->version.ver_minor = vmin;
	header->magic = CBSM_HEADER_MAGIC;
	header->flags = flags;

	return header;
}

int cbsm_header_write(FILE *stream, struct cbsm_header *header)
{
	int ret;

	if (!stream || !header) {
		printf("error: stream/header is NULL\n");
		return -1;
	}
	ret = fwrite((void *)header, sizeof(struct cbsm_header), 1, stream);
	if (ret < 0) {
		printf("failed to write stream");
		free(header);
		return ret;
	}
}

void cbsm_header_free(struct cbsm_header *header)
{
	if (header)
		free(header);
}
