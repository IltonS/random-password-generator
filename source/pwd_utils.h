#ifndef PWD_UTILS_H
#define PWD_UTILS_H

#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

// A function to check if a character is a digit
bool isDigit(char c);

// A function to check if a character is an uppercase letter
bool isUpper(char c);

// A function to check if a character is a lowercase letter
bool isLower(char c);

// A function to check if a character is a special character
bool isSpecial(char c);

// A function to generate a random character
char randomChar();

// A function to generate a random password of a given length with some criteria and no consecutive characters
std::string randomPassword(int length, bool useDigit, bool useUpper, bool useLower, bool useSpecial);

// A function to determine how strong a password is based on its length and criteria
std::string passwordStrength(std::string password);

#endif
