#include "f_cbsf.h"

static uint64_t gid = 0;

uint64_t get_new_objid()
{
	return gid++;
}
