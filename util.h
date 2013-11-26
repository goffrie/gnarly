#ifndef __UTIL_H__
#define __UTIL_H__

#include <vector>
#include <string>

// Splits up a line of text into multiple lines for display
std::vector<std::string> getLines(const std::string& t, int width);

#endif
