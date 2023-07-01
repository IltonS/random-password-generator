#include "install_utils.h"

// Function to add a directory to the PATH
bool addDirectoryToPath(const std::string& dir) {
	// Open the registry key for the system environment variables
  	HKEY hKey;
  	LPCTSTR keyPath = TEXT("Environment");
  	LSTATUS lOpenStatus = RegOpenKeyEx(HKEY_CURRENT_USER, keyPath, 0, KEY_ALL_ACCESS, &hKey);
  	
  	if (lOpenStatus != ERROR_SUCCESS) {
    	std::cerr << "Error opening the registry key" << std::endl;
    	return false;
  	}
  	
  	// Get the current value of the PATH
  	char buffer[32767];
  	DWORD length = sizeof(buffer);
  	DWORD type = REG_SZ;
  	LSTATUS lGetStatus = RegQueryValueEx(hKey, TEXT("PATH"), NULL, &type, (LPBYTE)buffer, &length);
  
  	if (lGetStatus != ERROR_SUCCESS) {
    	std::cerr << "Error getting the PATH" << std::endl;
    	RegCloseKey(hKey);
    	return false;
  	}
  	
  	// Check if the directory is already in the PATH
  	std::string path = buffer;
  
  	if (path.find(dir) != std::string::npos) {
    	std::cerr << "The directory " << dir << " is already in the PATH" << std::endl;
    	RegCloseKey(hKey);
    	return false;
  	}
  	
  	// Add the directory to the PATH
  	path += ";";
  	path += dir;
  	LSTATUS lSetStatus = RegSetValueEx(hKey, TEXT("PATH"), NULL, REG_SZ, (LPBYTE)path.c_str(), path.length() + 1);
  	
	if (lSetStatus != ERROR_SUCCESS) {
    	std::cerr << "Error setting the PATH" << std::endl;
    	RegCloseKey(hKey);
    	return false;
  	}
  	
  	// Close the registry key
  	RegCloseKey(hKey);
  
  	// Broadcast a WM_SETTINGCHANGE message to notify other applications
  	SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, NULL, (LPARAM)"Environment", SMTO_BLOCK, 100, NULL);
  
  	std::cout << "The directory " << dir << " was added to the PATH" << std::endl;
  	return true;
}

// Function to remove a directory from the PATH
bool removeDirectoryFromPath(const std::string& dir) {
	// Open the registry key for the system environment variables
  	HKEY hKey;
  	LPCTSTR keyPath = TEXT("Environment");
  	LSTATUS lOpenStatus = RegOpenKeyEx(HKEY_CURRENT_USER, keyPath, 0, KEY_ALL_ACCESS, &hKey);
  
  	if (lOpenStatus != ERROR_SUCCESS) {
    	std::cerr << "Error opening the registry key" << std::endl;
    	return false;
  	}
  	
  	// Get the current value of the PATH
  	char buffer[32767];
  	DWORD length = sizeof(buffer);
  	DWORD type = REG_SZ;
  	LSTATUS lGetStatus = RegQueryValueEx(hKey, TEXT("PATH"), NULL, &type, (LPBYTE)buffer, &length);
  
  	if (lGetStatus != ERROR_SUCCESS) {
    	std::cerr << "Error getting the PATH" << std::endl;
    	RegCloseKey(hKey);
    	return false;
  	}
  
   	// Check if the directory is in the PATH
   	std::string path = buffer;
   	size_t pos = path.find(dir);
   	
	if (pos == std::string::npos) {
     	std::cerr << "The directory " << dir << " is not in the PATH" << std::endl;
     	RegCloseKey(hKey);
     	return false;
   	}
   	
   	// Remove the directory from the PATH
   	size_t end = pos + dir.length();
   	
	if (end < path.length() && path[end] == ';') {
    	end++; // Remove the trailing semicolon
   	}
   	
   	path.erase(pos, end - pos);
   	LSTATUS lSetStatus = RegSetValueEx(hKey, TEXT("PATH"), NULL, REG_SZ, (LPBYTE)path.c_str(), path.length() + 1);
   
   if (lSetStatus != ERROR_SUCCESS) {
    	std::cerr << "Error setting the PATH" << std::endl;
     	RegCloseKey(hKey);
     	return false;
   }
   
	// Close the registry key
   	RegCloseKey(hKey);

	// Broadcast a WM_SETTINGCHANGE message to notify other applications
	SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, NULL, (LPARAM)"Environment", SMTO_BLOCK, 100, NULL);

	std::cout << "The directory " << dir << " was removed from the PATH" << std::endl;
	return true;
}

// Function to extract the directory from a string
std::string getDirectoryFromString(const std::string& str) {
	// Find the last occurrence of '/' or '\\'
  	size_t pos = str.find_last_of("/\\");
  
  	// If found, return the substring before it
  	if (pos != std::string::npos) {
    	return str.substr(0, pos);
  	} 
	else { 
    	// Otherwise, return an empty string
		return "";
  	}
}