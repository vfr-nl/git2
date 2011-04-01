#include "builtin.h"

#include <stdio.h>
#include <string.h>

void print_usage()
{
	int i, nr;
	printf("Git2 available commands:\n");
	nr = sizeof(commands) /  sizeof(commands[0]);
	for (i = 0; i < nr; i++)
		printf("\t%s\n", commands[i].cmd);
}


cmd_handler lookup_handler(char *cmd)
{
	int i;
	for (i = 0; i < sizeof(commands); i++)
		if (!strcmp(commands[i].cmd, cmd))
			return commands[i].handler;
	return NULL;
}


int main(int argc, char **argv)
{
	cmd_handler handler;

	if (argc < 2) {
		print_usage();
		return -1;
	}

	if ((handler = lookup_handler(argv[1])) == NULL) {
		printf("Unknown command '%s'.\n", argv[1]);
		print_usage();
		return -1;
	}

	return handler(argc-2, (const char**)(argv+2));
}
