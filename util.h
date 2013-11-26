#ifndef __UTIL_H__
#define __UTIL_H__

#include <vector>
#include <string>

// Splits up a line of text into multiple lines for display
std::vector<std::string> getLines(const std::string& t, int width);

// Capitalize the first letter.
std::string capitalize(const std::string& t);
// Capitalize every word.
std::string titleCase(const std::string& t);

bool isVowel(char c);

#endif
