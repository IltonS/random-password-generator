#include "args_parser.h"

// Print a help message
void printHelp() {
	std::string appName = "rpwdg";
	
	std::cout << "Usage: " << appName << " -L <length> [-d] [-u] [-s] || ";
	std::cout <<  appName << " -L <length> -[d][u][s] || ";
	std::cout <<  appName << " -h || ";
	std::cout <<  appName << " -v " << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "-L <length> : Specify the password length (must be between 4 and 16)" << std::endl;
	std::cout << "-d : Use digits in the password" << std::endl;
	std::cout << "-u : Use uppercase letters in the password" << std::endl;
	std::cout << "-s : Use special characters in the password" << std::endl;
	std::cout << "-h : Show this help message and exit" << std::endl;
	std::cout << "-v : Show the program version and exit" << std::endl;
}

// Print the program version
void printVersion() {
	std::cout << "Random Password Generator v1.0" << std::endl;
}

//Parse the application params
void parseArgs(int argc, char* argv[]) {
	if (argc == 1) {
		// Print an error message using cerr and exit the program
		std::cerr << "No flags were informed: " << std::endl;
		printHelp();
		exit(1);
	}
	
	// Loop through the arguments and parse them according to their flags
	for (int i = 1; i < argc; i++) {		
		if (strcmp(argv[i], "-h") == 0) { // Check if it is a flag for help	
			// Print a help message and exit the program
			printHelp();
			exit(0);
		}
		
		// Check if it is a flag for version
		if (strcmp(argv[i], "-v") == 0) {
			// Print the program version and exit the program
			printVersion();
			exit(0);
		}
		
		// Check if it is a flag for length
		if (strcmp(argv[i], "-L") == 0) {
			// Check if there is another argument after this flag
			if (i + 1 < argc) {
				// Convert it to an integer and store it in length variable
				glb::length = atoi(argv[i + 1]);
				
				// Skip the next argument
				i++;
			} else {
				// Print an error message using cerr and exit the program
				std::cerr << "Missing argument for -L flag." << std::endl;
				// Print a help message and exit the program
				printHelp();
				exit(1);
			}
		}
		else if (strcmp(argv[i], "-d") == 0) { // Check if it is a flag for digit
			// Set the useDigit variable to true
			glb::useDigit = true;
		}
		else if (strcmp(argv[i], "-u") == 0) { // Check if it is a flag for upper
			// Set the useUpper variable to true
			glb::useUpper = true;
		}
		else if (strcmp(argv[i], "-s") == 0) { // Check if it is a flag for special
			// Set the useSpecial variable to true
			glb::useSpecial = true;
		}
		else if (argv[i][0] == '-') { // Check if it is a combined flag for digit, upper, lower and special
			// Loop through the characters of the flag
			for (int j = 1; argv[i][j] != '\0'; j++) {
				// Check which option it matches and set the corresponding variable to true
				switch (argv[i][j]) {
					case 'd':
						glb::useDigit = true;
						break;
					case 'u':
						glb::useUpper = true;
						break;
					case 's':
						glb::useSpecial = true;
						break;
					default:
						// Otherwise, it is an invalid option
						std::cerr << "Invalid option: " << argv[i][j] << std::endl;
						// Print a help message and exit the program
						printHelp();
						exit(1);
				}
			} // for
		}
		else { // Otherwise, it is an invalid flag
			// Print an error message using cerr
			std::cerr << "Invalid flag: " << argv[i] << std::endl;
			
			// Print a help message and exit the program	
			printHelp();
			exit(1);
		}
	} // for
}