// A program to generate a random password with some criteria and no consecutive characters
#include "pwd_utils.h"
#include "globals.h"
#include "args_parser.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Initialize some variables to store the parameters
int glb::length = -1;
bool glb::useDigit = false;
bool glb::useUpper = false;
bool glb::useLower = true;
bool glb::useSpecial = false;

int main(int argc, char* argv[]) {
	// Initialize the random seed
	srand(time(0));
	
	parseArgs(argc,argv);
	
	// Check if the length is between 4 and 16
	if (glb::length >= 4 && glb::length <=16) {
		// Generate and display a random password with some criteria and no consecutive characters
		string password = randomPassword(glb::length, glb::useDigit, glb::useUpper, glb::useLower, glb::useSpecial);
		cout << "Your random password is: " <<  password << endl;
	} else {
		// Print an error message using cerr
		cerr << "Invalid password length. It must be between 4 and 16." << endl;
	}
	
	return 0;
}
