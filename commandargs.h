#ifndef __COMMANDARGS_H__
#define __COMMANDARGS_H__

#include <string>
#include <vector>

struct LevelPlan;

// Whether or not we have read a layout from a file, and that layout if it is there
extern bool haveLayout;
extern LevelPlan levelLayout;
// gnarly mode includes all DLC
extern bool gnarly;
// dev mode contains the cheatyelf class for testing purposes
extern bool dev;

// Processes the command line arguments
void processArgs(int argc, char *argv[]);

#endif
