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

#ifndef FORMAT_CBSM_H
#define FORMAT_CBSM_H

#include <stdint.h>
#include <stdio.h>

#define CBSM_HEADER_MAGIC 	0xdeed
#define CBSM_OBJECT_MAGIC 	0xdeadbeef

#define CBSM_FILE_SCHEMATIC	0x00
#define CBSM_FILE_LAYOUT	0x01
#define CBSM_FILE_LIBRARY	0x02
#define CBSM_FILE_TYPE_MASK	(0xff)

/* Header format and related functions */
struct cbsm_version {
	uint8_t ver_major;
	uint8_t ver_minor;
};

struct cbsm_header {
	uint16_t magic;
	struct cbsm_version version;
	uint32_t flags;
};

struct cbsm_header *cbsm_header_create(uint8_t, uint8_t, uint32_t);
void cbsm_header_free(struct cbsm_header *);
struct cbsm_header *cbsm_header_read(FILE *);
int cbsm_header_write(FILE *, struct cbsm_header *);
void cbsm_header_print(struct cbsm_header *);

struct cbsm_object {
	uint32_t magic;
	uint32_t type;
};

#define CBSM_OBJECT_LINE 0x0

/* Simple lines and related functions */
struct cbsm_line {
	struct cbsm_object obj;
	uint64_t startx;
	uint64_t starty;
	uint64_t endx;
	uint64_t endy;
};

struct cbsm_line *cbsm_line_create(uint64_t, uint64_t, uint64_t, uint64_t);
void cbsm_line_free(struct cbsm_line *);
struct cbsm_line *cbsm_line_read(FILE *);
int cbsm_line_write(FILE *, struct cbsm_line *);
void cbsm_line_print(struct cbsm_line *);

#endif
