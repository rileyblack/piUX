/*
 * AUTHOR: RILEY BLACK
 *
 * DESCRPTION OF FILE: THIS FILE GOES ON TO IMPLEMENT A PERSONAL VERSION OF THE COMMAND LINE 'RM' FUNCTION, THAT WILL ULTIMENTLY 
 *						BE ONE OF THE MANY METHODS INVOLVED IN A COMMAND LINE FILEMANAGER SYSTEM
 *
 * DATE: WEDNESDAY OCTOBER 2 2019
 *
 **/

#include <iostream>
#include "filemanager.h"

using namespace std;

int main(int argc, char * argv[]) {
	if (argc < 2) { //rm call contains the actual call 'rm', and at least one file, but can be multiple files, meaning 2+
		cout << "Format of call is incorrect." << endl;
		return ENOTSUP;
	}
	for (int i = 0; i < argc-1; i++){ //for each file passed as an arguement
		filemanager file(argv[i + 1]); //create a filemanager object for this file
		if(file.getOwnerName() == "Delete") {
			cout << "Failed to created filemanager object with file name provided." << endl;
			return ENOTSUP;
		}
		int result = file.remove(); //call the rmeove function and store the result
		if (result != 0){ //check to see if remove worked okay
			cout << "The following error has occured: " << file.getErrorNumberString();
			cout << "Operation aborted." << endl;
			return result;
		}
	}
	return 0;
}
