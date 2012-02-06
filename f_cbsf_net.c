#include "f_cbsf.h"

struct cbsf_net *cbsf_net_create(char *name)
{
	struct cbsf_net *n;
	
	if (!name)
		return NULL;
	n = malloc(sizeof(struct cbsf_net));
	if (!n)
		return NULL;
	strcpy(n->name, name);
	n->obj.type = CBSF_TYPE_NET;
	n->obj.magic = CBSF_OBJECT_MAGIC;
	n->nobjs = 0;
	n->objects = NULL;

	return n;
}

int cbsf_net_addobj(struct cbsf_net *net, uint64_t obj)
{
	int n;
	uint64_t *ptr;

	if (!net)
		return -1;
	
	n = net->nobjs + 1;
	ptr = malloc(sizeof(uint64_t)*n);
	for (i = 0; i < net->nobjs; i++)
		ptr[i] = net->objects[i];
	ptr[i] = obj;
	if (net->objects)
		free(net->objects);
	net->objects = ptr;

	return 0;
}

void cbsf_net_free(struct cbsf_net *net)
{
	if (!net)
		return;
	if (net->objects)
		free(net->objects);
	free(net);
}

struct cbsf_net *cbsf_net_read(FILE *)
{
}

int cbsf_net_write(FILE *, struct cbsf_net *)
{
}

void cbsf_net_print(struct cbsf_net *)
{
}
