#include "pwd_utils.h"

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
	return c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*' || c == '(' || c == ')' || c == '-' || c == '_' || c == '=' || c == '+';
}

// A function to generate a random character
char randomChar() {
	// Define the possible characters
	const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+";
	 
	// Get the size of the array
	int size = sizeof(chars) - 1;
	 
	// Return a random character from the array
	return chars[rand() % size];
}

// A function to generate a random password of a given length with some criteria and no consecutive characters
std::string randomPassword(int length, bool useDigit, bool useUpper, bool useLower, bool useSpecial) {
	// Initialize an empty string
	std::string password = "";
	
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

// A function to determine how strong a password is based on its length and criteria
std::string passwordStrength(std::string password) {
	// Initialize some variables to store the criteria counts
  	int digitCount = 0;
  	int upperCount = 0;
  	int lowerCount = 0;
  	int specialCount = 0;

  	// Loop through the characters of the password and update the counts accordingly
  	for (char c : password) {
    	if (isDigit(c)) {
      		digitCount++;
    	}
    
		if (isUpper(c)) {
      		upperCount++;
    	}
    
		if (isLower(c)) {
      		lowerCount++;
    	}
    
		if (isSpecial(c)) {
      		specialCount++;
    	}
  	};

  	// Calculate the total score based on the length and criteria counts
  	int score = password.length() + digitCount * 2 + upperCount * 3 + lowerCount * 2 + specialCount * 4;

  	// Return a string indicating the strength of the password based on the score
  	if (score >= 40) {
    	return "Very Strong";
  	} else if (score >= 30) {
    	return "Strong";
  	} else if (score >= 20) {
    	return "Moderate";
  	} else if (score >= 10) {
    	return "Weak";
  	} else {
    	return "Very Weak";
  }
}