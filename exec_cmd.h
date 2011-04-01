#ifndef EXEC_CMD_H
#define EXEC_CMD_H

typedef int (*cmd_handler)(int, const char**);

struct cmd_struct
{
	char *cmd;
	cmd_handler handler;
};


#endif /* EXEC_CMD_H */
