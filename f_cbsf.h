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

/*
 * This file describes the structures for the CERN Binary Schematic Format.
 * The structures have been optimized for space and aligned properly to
 * allow for efficient processing of data. Note that the internal unit of
 * distance is picometers.
 */

#ifndef FORMAT_CBSF_H
#define FORMAT_CBSF_H

#include <stdint.h>
#include <stdio.h>

#define CBSF_HEADER_MAGIC 	0xdeed
#define CBSF_OBJECT_MAGIC 	0xdeadbeef

#define CBSF_FILE_SCHEMATIC	0x00
#define CBSF_FILE_LAYOUT	0x01
#define CBSF_FILE_LIBRARY	0x02
#define CBSF_FILE_TYPE_MASK	(0xff)

uint64_t get_new_objid();

/* Header format and related functions */
struct cbsf_version {
	uint8_t ver_major;
	uint8_t ver_minor;
};

struct cbsf_header {
	uint16_t magic;
	struct cbsf_version version;
	uint32_t flags;
};

struct cbsf_header *cbsf_header_create(uint8_t, uint8_t, uint32_t);
void cbsf_header_free(struct cbsf_header *);
struct cbsf_header *cbsf_header_read(FILE *);
int cbsf_header_write(FILE *, struct cbsf_header *);
void cbsf_header_print(struct cbsf_header *);

struct cbsf_object {
	uint32_t magic;
	uint32_t type;
};

#define CBSF_OBJECT_LINE	0x0

/* Simple lines and related functions */
struct cbsf_line {
	struct cbsf_object obj;
	uint64_t id;
	uint64_t startx;
	uint64_t starty;
	uint64_t endx;
	uint64_t endy;
};

struct cbsf_line *cbsf_line_create(uint64_t, uint64_t, uint64_t, uint64_t);
void cbsf_line_free(struct cbsf_line *);
struct cbsf_line *cbsf_line_read(FILE *);
int cbsf_line_write(FILE *, struct cbsf_line *);
void cbsf_line_print(struct cbsf_line *);

#define CBSF_OBJECT_NET		0x1

struct cbsf_net {
	struct cbsf_object obj;
	char name[64];
	uint32_t nobjs;
	uint64_t *objects;
};

struct cbsf_net *cbsf_net_create(char *name);
int cbsf_net_addobj(struct cbsf_net *, uint64_t);
void cbsf_net_free(struct cbsf_net *);
struct cbsf_net *cbsf_net_read(FILE *);
int cbsf_net_write(FILE *, struct cbsf_net *);
void cbsf_net_print(struct cbsf_net *);

#endif
