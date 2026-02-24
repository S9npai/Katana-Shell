#ifndef PARSER_HPP
#define PARSER_HPP
#include "types.hpp"

Command parseCommand(const std::string& input);

pipeline parsePipeline(std::string &input);



#endif