#ifndef PREPROCESSOR_H_INCLUDED
#define PREPROCESSOR_H_INCLUDED

#include <string>

std::string remove_comments(std::string);
std::string replace_macros(std::string);
std::string preprocessor(std::string);

#endif
