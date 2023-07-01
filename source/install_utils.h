#ifndef INSTALL_UTILS_H
#define INSTALL_UTILS_H

#pragma once

#include <iostream>
#include <windows.h>
#include <filesystem>
#include <string>

// Function to add a directory to the PATH
bool addDirectoryToPath(const std::string& dir);

// Function to remove a directory from the PATH
bool removeDirectoryFromPath(const std::string& dir);

// Function to extract the directory from a string
std::string getDirectoryFromString(const std::string& str);

#endif