#ifndef __COMMANDARGS_H__
#define __COMMANDARGS_H__

#include <string>

extern std::string layoutFile;
extern bool useCurses;
extern bool dev;

void processArgs(int argc, char *argv[]);

#endif
