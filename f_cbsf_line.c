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
#include <endian.h>

struct cbsf_line *cbsf_line_read(FILE *stream)
{
	int ret;
	struct cbsf_line *line = NULL;

	if (!stream) {
		printf("error: stream is NULL\n");
		return NULL;
	}
	line = (struct cbsf_line *)malloc(sizeof(struct cbsf_line));
	if (!line) {
		printf("failed to allocate line\n");
		return NULL;
	}
	ret = fread((void *)line, sizeof(struct cbsf_line), 1, stream);
	if (ret < 0) {
		printf("failed to read stream");
		free(line);
		return NULL;
	}

	line->id = be64toh(line->id);
	line->startx = be64toh(line->startx);
	line->starty = be64toh(line->starty);
	line->endx = be64toh(line->endx);
	line->endy = be64toh(line->endy);
	line->obj.type = be32toh(line->obj.type);
	line->obj.magic = be32toh(line->obj.magic);

	return line;
}

void cbsf_line_print(struct cbsf_line *line)
{
	printf("Line: (%lld, %lld) --> (%lld, %lld)\n", line->startx,
		line->starty, line->endx, line->endy);
}

struct cbsf_line *cbsf_line_create(uint64_t sx, uint64_t sy, uint64_t ex,
	uint64_t ey)
{
	struct cbsf_line *line = NULL;

	line = (struct cbsf_line *)malloc(sizeof(struct cbsf_line));
	if (!line) {
		printf("failed to allocate line\n");
		return NULL;
	}
	memset(line, 0, sizeof(struct cbsf_line));
	line->startx = sx;
	line->starty = sy;
	line->endx = ex;
	line->endy = ey;
	line->id = get_new_objid();
	line->obj.type = CBSF_OBJECT_LINE;
	line->obj.magic = CBSF_OBJECT_MAGIC;

	return line;
}

int cbsf_line_write(FILE *stream, struct cbsf_line *line)
{
	int ret;
	struct cbsf_line l;

	if (!stream || !line) {
		printf("error: stream/line is NULL\n");
		return -1;
	}
	memcpy(&l, line, sizeof(struct cbsf_line));
	l.startx = htobe64(line->startx);
	l.starty = htobe64(line->starty);
	l.endx = htobe64(line->endx);
	l.endy = htobe64(line->endy);
	l.id = htobe64(line->id);
	l.obj.type = htobe32(line->obj.type);
	l.obj.magic = htobe32(line->obj.magic);

	ret = fwrite((void *)&l, sizeof(struct cbsf_line), 1, stream);
	if (ret < 0) {
		printf("failed to write stream");
		free(line);
		return ret;
	}
}

void cbsf_line_free(struct cbsf_line *line)
{
	if (line)
		free(line);
}
