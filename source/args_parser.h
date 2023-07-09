#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#pragma once

#include "globals.h"
#include "install_utils.h"
#include <iostream>
#include <string>
#include <windows.h>

// Print a help message
void printHelp(bool complete = false);

// Print the program version
void printVersion();

//Parse the application params
void parseArgs(int argc, char* argv[]);

#endif