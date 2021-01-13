/*
 * AUTHOR: RILEY BLACK
 *
 * DESCRPTION OF FILE: THIS FILE GOES ON TO IMPLEMENT A PERSONAL VERSION OF THE COMMAND LINE 'CP' FUNCTION, THAT WILL ULTIMENTLY 
 *						BE ONE OF THE MANY METHODS INVOLVED IN A COMMAND LINE FILEMANAGER SYSTEM
 *
 * DATE: WEDNESDAY OCTOBER 2 2019
 *
 **/

#include <iostream>
#include "filemanager.h"

using namespace std;

int main(int argc, char * argv[]) {
	if (argc != 3) { //cp call contains the actual call 'cp', the source, and the destination, meaning 3
		cout << "Format of call is incorrect." << endl;
		return ENOTSUP;
	}
	filemanager source(argv[1]); //create filemanager object for source 
	if(source.getOwnerName() == "Delete") {
		cout << "Failed to created filemanager object with file name provided." << endl;
		return ENOTSUP;
	}
	if (source.getTypeStringRep() != "Regular File"){ //insuring regular file
		cout << "This operation only works on Regular Files." << endl;
		return ENOTSUP;
	}
	string destination = argv[2]; //create filemanager object for destination
	ofstream dest{destination}; //create open destination stream (file)
	if(dest.bad()){
		cout << "Issue moving file." << endl;
		cout << "Operation aborted." << endl;
		return EIO;
	}

	int result = source.dump(&dest); //dumping the source contents into the destination file and checking if it went okay
	if (result != 0) { //dump returns zero on success, and the error number on a fault
		cout << "The following error has occured: " << source.getErrorNumberString() << endl;
		cout << "Operation aborted." << endl;
		return result;
	}
	return 0;
}
