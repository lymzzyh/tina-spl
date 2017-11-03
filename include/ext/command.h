/*
*********************************************
*
* File    : command.h
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-25
* Descript:
*********************************************
*/
#ifndef __COMMAND_H
#define __COMMAND_H

typedef void (*CmdHdle)(int argc, char **argv);
void console_start(void);
s32 cmd_register(char* name, CmdHdle handler);

#endif
