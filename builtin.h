#ifndef BUILTIN_H
#define BUILTIN_H

#include "exec_cmd.h"

int cmd_rev_list(int argc, const char **argv);

struct cmd_struct commands[] = {
	{"rev-list", cmd_rev_list}
};

#endif /* BUILTIN_H */
