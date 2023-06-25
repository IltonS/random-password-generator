// A program to generate a random password with some criteria and no consecutive characters
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// A function to check if a character is a digit
bool isDigit(char c) {
	return c >= '0' && c <= '9';
}

// A function to check if a character is an uppercase letter
bool isUpper(char c) {
	return c >= 'A' && c <= 'Z';
}

// A function to check if a character is a lowercase letter
bool isLower(char c) {
	return c >= 'a' && c <= 'z';
}

// A function to check if a character is a special character
bool isSpecial(char c) {
	return c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*' || c == '(' || c == ')';
}

// A function to generate a random character
char randomChar() {
	// Define the possible characters
	const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()";
	 
	// Get the size of the array
	int size = sizeof(chars) - 1;
	 
	// Return a random character from the array
	return chars[rand() % size];
}

// A function to generate a random password of a given length with some criteria and no consecutive characters
string randomPassword(int length, bool useDigit, bool useUpper, bool useLower, bool useSpecial) {
	// Initialize an empty string
	string password = "";
	
	// Initialize some flags to check the criteria
	bool hasDigit = false;
	bool hasUpper = false;
	bool hasLower = false;
	bool hasSpecial = false;
	
	// Initialize a variable to store the previous character
	char prev = '\0';
	
	// Loop for the given length
	for (int i = 0; i < length; i++) {
		// Generate a random character
	 	char c = randomChar();
	 
	 	// Check if it is equal to the previous character
	 	if (c == prev) {
	 		// Try again with a different character
	 		i--;
	 		continue;
		}
	
		// Check if it matches the parameters
		if (!useDigit && isDigit(c)) {
			// Try again with a different character
			i--;
			continue;
		}
		
		if (!useUpper && isUpper(c)) {
			// Try again with a different character
			i--;
			continue;
		}
		
		if (!useLower && isLower(c)) {
			// Try again with a different character
			i--;
			continue;
		}
		
		if (!useSpecial && isSpecial(c)) {
			// Try again with a different character
			i--;
			continue;
		}
		
		// Append it to the password
		password += c;
	
		// Update the flags according to the character
		if (isDigit(c)) {
			hasDigit = true;
		}
		
		if (isUpper(c)) {
			hasUpper = true;
		}
		
		if (isLower(c)) {
			hasLower = true;
		}
		
		if (isSpecial(c)) {
			hasSpecial = true;
		}
		
		// Update the previous character
		prev = c;
	} // for
	
	// Check if the password meets all the criteria
	if ( (!useDigit || (useDigit && hasDigit)) &&
		 (!useUpper || (useUpper && hasUpper)) &&
		 (!useLower || (useLower && hasLower)) &&
		 (!useSpecial || (useSpecial && hasSpecial))
	) {
		// Return the password
		return password;
	} else {
		// Try again with a new password
		return randomPassword(length, useDigit, useUpper, useLower, useSpecial);
	}
}

int main(int argc, char* argv[]) {
	// Initialize the random seed
	srand(time(0));
	
	// Initialize some variables to store the parameters
	int length = -1;
	bool useDigit = false;
	bool useUpper = false;
	bool useLower = true;
	bool useSpecial = false;
	
	if (argc == 1) {
		// Print an error message using cerr and exit the program
		cerr << "No flags were informed: " << endl;
		cerr << "Usage: " << argv[0] << " -L <length> [-d] [-u] [-l] [-s]" << endl;
		exit(1);
	}
	
	// Loop through the arguments and parse them according to their flags
	for (int i = 1; i < argc; i++) {		
		if (strcmp(argv[i], "-h") == 0) { // Check if it is a flag for help
			// Print a help message and exit the program
			cout << "Usage: " << argv[0] << " -L <length> [-d] [-u] [-l] [-s]" << endl;
			cout << "Options:" << endl;
			cout << "-L <length> : Specify the password length (must be between 4 and 16)" << endl;
			cout << "-d : Use digits in the password" << endl;
			cout << "-u : Use uppercase letters in the password" << endl;
			cout << "-l : Use lowercase letters in the password" << endl;
			cout << "-s : Use special characters in the password" << endl;
			cout << "-h : Show this help message and exit" << endl;
			cout << "-v : Show the program version and exit" << endl;
			exit(0);
		}
		
		// Check if it is a flag for version
		if (strcmp(argv[i], "-v") == 0) {
			// Print the program version and exit the program
			cout << "Random Password Generator v1.0" << endl;
			exit(0);
		}
		
		// Check if it is a flag for length
		if (strcmp(argv[i], "-L") == 0) {
			// Check if there is another argument after this flag
			if (i + 1 < argc) {
				// Convert it to an integer and store it in length variable
				length = atoi(argv[i + 1]);
				
				// Skip the next argument
				i++;
			} else {
				// Print an error message using cerr and exit the program
				cerr << "Missing argument for -L flag." << endl;
				exit(1);
			}
		}
		else if (strcmp(argv[i], "-d") == 0) { // Check if it is a flag for digit
			// Set the useDigit variable to true
			useDigit = true;
		}
		else if (strcmp(argv[i], "-u") == 0) { // Check if it is a flag for upper
			// Set the useUpper variable to true
			useUpper = true;
		}
		/*else if (strcmp(argv[i], "-l") == 0) { // Check if it is a flag for lower
			// Set the useLower variable to true
			useLower = true;
		}*/
		else if (strcmp(argv[i], "-s") == 0) { // Check if it is a flag for special
			// Set the useSpecial variable to true
			useSpecial = true;
		}
		else if (argv[i][0] == '-') { // Check if it is a combined flag for digit, upper, lower and special
			// Loop through the characters of the flag
			for (int j = 1; argv[i][j] != '\0'; j++) {
				// Check which option it matches and set the corresponding variable to true
				switch (argv[i][j]) {
					case 'd':
						useDigit = true;
						break;
					case 'u':
						useUpper = true;
						break;
					/*case 'l':
						useLower = true;
						break;*/
					case 's':
						useSpecial = true;
						break;
					default:
						// Otherwise, it is an invalid option
						cerr << "Invalid option: " << argv[i][j] << endl;
						cerr << "Usage: " << argv[0] << " -L <length> [-d] [-u] [-l] [-s]" << endl;
						exit(1);
				}
			} // for
		}
		else { // Otherwise, it is an invalid flag
			// Print an error message using cerr and exit the program
			cerr << "Invalid flag: " << argv[i] << endl;
			cerr << "Usage: " << argv[0] << " -L <length> [-d] [-u] [-l] [-s]" << endl;
			exit(1);
		}
	} // for
	
	// Check if the length is between 4 and 16
	if (length >= 4 && length <=16) {
		// Generate and display a random password with some criteria and no consecutive characters
		cout << "Generating random password..." << endl;
		string password = randomPassword(length, useDigit, useUpper, useLower, useSpecial);
		cout << "Your random password is: " <<  password << endl;
	} else {
		// Print an error message using cerr
		cerr << "Invalid password length. It must be between 4 and 16." << endl;
	}
	
	return 0;
}
