#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#pragma once

#include "globals.h"
#include <iostream>

// Print a help message
void printHelp();

// Print the program version
void printVersion();

//Parse the application params
void parseArgs(int argc, char* argv[]);

#endif