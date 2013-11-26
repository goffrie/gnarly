#ifndef __COMMANDARGS_H__
#define __COMMANDARGS_H__

#include <string>
#include <vector>

extern std::string layoutFile;
extern std::vector<std::string> levelLayout;
extern bool gnarly;
extern bool dev;

void processArgs(int argc, char *argv[]);

#endif
