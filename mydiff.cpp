/*
 * AUTHOR: RILEY BLACK
 *
 * DESCRPTION OF FILE: THIS FILE GOES ON TO IMPLEMENT A PERSONAL VERSION OF THE COMMAND LINE 'DIFF' FUNCTION, THAT WILL ULTIMENTLY 
 *						BE ONE OF THE MANY METHODS INVOLVED IN A COMMAND LINE FILEMANAGER SYSTEM
 *
 * DATE: WEDNESDAY OCTOBER 2 2019
 *
 **/

#include <iostream>
#include "filemanager.h"

using namespace std;

int main(int argc, char * argv[]){
	if (argc != 3){ //diff call contains the actual call 'diff', file 1, and file 2 to compare, meaning 3
		cout << "Format of call is incorrect." << endl;
		return ENOTSUP;
	}
	filemanager file1(argv[1]); //creating filemanager object for the first file
	if(file1.getOwnerName() == "Delete") {
		cout << "Failed to created filemanager object with file name provided." << endl;
		return ENOTSUP;
	}
	filemanager file2(argv[2]); //creating filemanager object for the second file
	if(file2.getOwnerName() == "Delete") {
		cout << "Failed to created filemanager object with file name provided." << endl;
		return ENOTSUP;
	}	
	string result = file1.compare(file2); //comparing these two files, and storing the result
	
	if ((result != "different.")&&(result != "identical.")){ //if the test doesn't return a definitive result an error has occurred
		cout << "The following error has occured: " << result << endl;
	}
	else{ //if it has returned a definitive result, display the result
		cout << "The two files are " << result << endl;
	}
	return 0;
}
