/*
 * AUTHOR: RILEY BLACK
 *
 * DESCRPTION OF FILE: THIS FILE GOES ON TO IMPLEMENT A PERSONAL VERSION OF THE COMMAND LINE 'MV' FUNCTION, THAT WILL ULTIMENTLY 
 *						BE ONE OF THE MANY METHODS INVOLVED IN A COMMAND LINE FILEMANAGER SYSTEM
 *
 * DATE: WEDNESDAY OCTOBER 2 2019
 *
 **/

#include <iostream>
#include <string.h>
#include "filemanager.h"

using namespace std;

int main(int argc, char * argv[]) {
	if (argc != 3) { //mv call contains the actual call 'mv', the source, and the destination, meaning 3
		cout << "Format of call is incorrect." << endl;
		return ENOTSUP;
	}
	filemanager source(argv[1]); //create filemanager object for the course file to be copied
	if(source.getOwnerName() == "Delete") {
		cout << "Failed to created filemanager object with file name provided." << endl;
		return ENOTSUP;
	}
	if (source.reName(argv[2]) != 0){ //simply try and rename the file to a different location, and check if this works
		ofstream dest{argv[2]}; //if this doesn't work, we will use dump and remove, so open a new file with the name of argument 2
		if(dest.bad()){ //check if creating file went okay
			cout << "Issue moving file." << endl;
			cout << "Operation aborted." << endl;
			return EIO;
		}
		int result = source.dump(&dest); //dump the source into the destination, and store the result
		if (result != 0) { //check if dump was okay
			cout << "The following error has occured: " << source.getErrorNumberString() << endl;
			cout << "Operation aborted." << endl;
			return result;
		}
		int result1 = source.remove(); //remove the source file so that only the new one remains
		if (result1 != 0) { //check if remove was okay
			cout << "The following error has occured: " << source.getErrorNumberString() << endl;
			cout << "Operation aborted." << endl;
			return result1;
		}
		dest.close(); //close the ofstream
		if (dest.bad()) { //check if close went okay
			cout << "Issue moving file." << endl;
			cout << "Operation aborted." << endl;
			return EIO;
		}
	}
	return 0;
}