#ifndef __COMMANDARGS_H__
#define __COMMANDARGS_H__

#include <string>
#include <vector>

struct LevelPlan;

extern bool haveLayout;
extern LevelPlan levelLayout;
extern bool gnarly;
extern bool dev;

void processArgs(int argc, char *argv[]);

#endif
