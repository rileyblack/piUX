/*
 * AUTHOR: RILEY BLACK
 *
 * DESCRPTION OF FILE: THIS FILE GOES ON TO IMPLEMENT A PERSONAL VERSION OF THE COMMAND LINE 'CAT' FUNCTION, THAT WILL ULTIMENTLY 
 *						BE ONE OF THE MANY METHODS INVOLVED IN A COMMAND LINE FILEMANAGER SYSTEM
 *
 * DATE: WEDNESDAY OCTOBER 2 2019
 *
 **/

#include <iostream>
#include "filemanager.h"

using namespace std;

int main(int argc, char * argv[]) { //cat call contains the actual call 'cat', and at least one file, but can be multiple files, meaning 2+
	if (argc < 2) {
		cout << "Format of call is incorrect." << endl;
		return ENOTSUP;
	}
	for (int i = 0; i < argc - 1; i++) { //for all the files
		cout << endl;
		filemanager file(argv[i + 1]);
		if (file.getTypeStringRep() != "Regular File") {//insuring regular file
			cout << "This operation only works on Regular Files." << endl;
			return ENOTSUP;
		}
		if (file.getOwnerName() == "Delete") { //checking if filemanager object was created okay
			cout << "Failed to created filemanager object with file name provided." << endl;
			return ENOTSUP;
		}
		int result = file.dump(&cout); //dumping file to cout
		if (result != 0) { //checking if dump went okay
			cout << "The following error has occured: " << file.getErrorNumberString();
			cout << "Operation aborted." << endl;
			return result;
		}
		cout << endl << endl;
	}
	return 0;
}
