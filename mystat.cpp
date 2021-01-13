/*
 * AUTHOR: RILEY BLACK
 *
 * DESCRPTION OF FILE: THIS FILE GOES ON TO IMPLEMENT A PERSONAL VERSION OF THE COMMAND LINE 'STAT' FUNCTION, THAT WILL ULTIMENTLY 
 *						BE ONE OF THE MANY METHODS INVOLVED IN A COMMAND LINE FILEMANAGER SYSTEM
 *
 * DATE: WEDNESDAY OCTOBER 2 2019
 *
 **/


#include <iostream>
#include "filemanager.h"

using namespace std;

int main(int argc, char * argv[]) {
	if (argc != 2) { //stat call contains the actual call 'stat', and the name of the file, meaning 2
		cout << "Format of call is incorrect." << endl;
		return ENOTSUP;
	}
	filemanager file(argv[1]);
	if (file.getOwnerName() == "Delete") {
		cout << "Failed to created filemanager object with file name provided." << endl;
		return ENOTSUP;
	}
	cout << endl << endl << "            File Information" << endl;
	cout << "_______________________________________" << endl;
	cout << "File name: " << file.getName() << endl;
	cout << "File type: " << file.getTypeStringRep() << endl;
	cout << "File size: " << file.getSize() << " bytes" << endl;
	cout << "File owner: " << file.getOwnerName() << endl;
	cout << "File group: " << file.getGroupName() << endl;
	cout << "File permissions: " << file.getPermStringRep() << endl;
	cout << "Time of last access: " << file.getAccessTime();
	cout << "Time of last modification: " << file.getModTime();
	cout << "Time of last status change: " << file.getStatChangeTime();
	cout << "File block size: " << file.getBlockSize() << " bytes" << endl;
	cout << "File children: ";
	for (int i = 0; i < file.getChildren().size(); i++) //continue through all children
	{
		cout << file.getChildren().at(i).getName() << "	";
	}
	cout << endl << "File error number: " << file.getErrorNumberString() << endl << endl;
	
	return 0;
}