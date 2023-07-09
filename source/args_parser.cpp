#include "args_parser.h"

// Define the documentation as a multi-line string literal
const std::string usage = R"(Usage:
  rpwdg (-h|-v|-L <length> [-u][-d][-s]...)

Arguments:
  length  Specify the length of the password, between 4 and 16.

Options:
  -h, --help    Show this help message and exit.
  -v, --version Show the app version and exit.
  -L, --length  Use this option to specify the length of the password.
  -u, --upper   Include uppercase letters in the password.
  -d, --digits  Include digits in the password.
  -s, --special Include special characters in the password.
)";

const std::string doc = R"(rpwdg - Random Password Generator

Description:
  rpwdg is a command line app that generates random passwords of various lengths and
  characters. It can be used to create secure and unique passwords for different accounts
  or purposes.
)";

// Print a help message
void printHelp(bool complete){
	if (complete)
		std::cout << doc << std::endl << usage << std::endl;
	else
		std::cout << usage << std::endl;
} 

// Print the program version
void printVersion() {
	std::cout << "Random Password Generator v1.0.0.0" << std::endl;
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
		// Check if it is a flag for help	
		if ((strcmp(argv[i], "-h") == 0)  || (strcmp(argv[i], "--help") == 0)){ 
			// Print a help message and exit the program
			printHelp(true);
			exit(0);
		}
		
		// Check if it is a flag for version
		if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--version") == 0)) {
			// Print the program version and exit the program
			printVersion();
			exit(0);
		}
		
		//Check if it is a flag for install
		if (strcmp(argv[i], "/install") == 0) {
			// Get the full path of the executable
		    char buffer[MAX_PATH] = { 0 };
		    GetModuleFileName(NULL, buffer, MAX_PATH);
		
		    // Get the parent path of the executable, which is the actual directory
		    std::string exePath(buffer);
		    std::string dirPath = exePath.substr(0, exePath.find_last_of("\\/"));
		    
			//Add app directory to path
			if (addDirectoryToPath(dirPath)) 
				exit(0);
			else
				exit(1);
		}
		
		//Check if it is a flag for uninstall
		if (strcmp(argv[i], "/uninstall") == 0) {
			// Get the full path of the executable
		    char buffer[MAX_PATH] = { 0 };
		    GetModuleFileName(NULL, buffer, MAX_PATH);
		
		    // Get the parent path of the executable, which is the actual directory
		    std::string exePath(buffer);
		    std::string dirPath = exePath.substr(0, exePath.find_last_of("\\/"));
			
			//Remove app directory from path
			if (removeDirectoryFromPath(dirPath)) 
				exit(0);
			else
				exit(1);
		}
		
		// Check if it is a flag for length
		if ((strcmp(argv[i], "-L") == 0) || (strcmp(argv[i], "--length") == 0)) {
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
		else if ((strcmp(argv[i], "-d") == 0) || (strcmp(argv[i], "--digits") == 0)){ // Check if it is a flag for digit
			// Set the useDigit variable to true
			glb::useDigit = true;
		}
		else if ((strcmp(argv[i], "-u") == 0) || (strcmp(argv[i], "--upper") == 0)) { // Check if it is a flag for upper
			// Set the useUpper variable to true
			glb::useUpper = true;
		}
		else if ((strcmp(argv[i], "-s") == 0) || (strcmp(argv[i], "--special") == 0)) { // Check if it is a flag for special
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