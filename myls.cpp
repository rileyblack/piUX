/*
 * AUTHOR: RILEY BLACK
 *
 * DESCRPTION OF FILE: THIS FILE GOES ON TO IMPLEMENT A PERSONAL VERSION OF THE COMMAND LINE 'LS' FUNCTION, THAT WILL ULTIMENTLY 
 *						BE ONE OF THE MANY METHODS INVOLVED IN A COMMAND LINE FILEMANAGER SYSTEM
 *
 * DATE: WEDNESDAY OCTOBER 2 2019
 *
 **/

#include <iostream>
#include <unistd.h>
#include "filemanager.h"

using namespace std;

int main(int argc, char * argv[]) {	
	if (argc == 1) {//case for if only ls is typed (must be within a directory so no check needed)
		char * cwd = get_current_dir_name(); //error check gets current working directory 
		filemanager file(cwd); //error check creates filemanager object from current working directory
		if(file.getOwnerName() == "Delete") {
			cout << "Failed to created filemanager object with file name provided." << endl;
			return ENOTSUP;
		}
		file.expand(); //error check expands children of object containing current working directory 
		int vect_sz = file.getChildren().size(); //error check retrieve how many children the directory has
		for (int i = 0; i < vect_sz; i++) {//for each child
			string curr_element_name = file.getChildren().at(i).getName(); //error check 
			cout << curr_element_name << endl; //print the child name
		}
		return 0;
	}
	else {//case for if something more than just ls is typed
		string argument = argv[1]; //grab second word typed into the call
		if ((argument == "-l") || (argument == "-L")) { //case if ls -l or ls -L is typed
			if (argc == 2) { //case if ONLY ls -l or ls -L is typed (must be within a directory so no check needed)
				char * cwd = get_current_dir_name(); //error check gets current working directory
				filemanager file(cwd); //error check creates filemanager object from current working directory
				if(file.getOwnerName() == "Delete") {
					cout << "Failed to created filemanager object with file name provided." << endl;
					return ENOTSUP;
				}
				file.expand(); //error check expands children of object containing current working directory 
				int vect_sz = file.getChildren().size();  //error check retrieve how many children the directory has
				for(int i = 0 ; i < vect_sz ; i++){ //for each child
					string permissions = file.getChildren().at(i).getPermStringRep();    //error
					string owner = file.getChildren().at(i).getOwnerName();    //error
					string group = file.getChildren().at(i).getGroupName();    //error
					int size = file.getChildren().at(i).getSize();    //error
					string time = file.getChildren().at(i).getModTime();    //error
					string name = file.getChildren().at(i).getName();    //error
					
					cout << endl << name << "  " << permissions << "  " << owner << "  " << group << "  " << size << "  " << time;
					
					}
				return 0;
			}
			else { //case if ls -l (filename) is typed
				filemanager file(argv[2]); //grabs file path specified and created filemanager object with path/name
				if(file.getOwnerName() == "Delete") {
					cout << "Failed to created filemanager object with file name provided." << endl;
					return ENOTSUP;
				}
				string file_type = file.getTypeStringRep(); //determines type of file
				if(file_type == "Directory"){ //case if ls -l (directory) is typed
					file.expand();  //error check expands children of object specified by file path/name
					int vect_sz = file.getChildren().size();   //error check retrieve how many children the directory has
					for(int i = 0 ; i < vect_sz ; i++) { //for each child
						string permissions = file.getChildren().at(i).getPermStringRep();   //error
						string owner = file.getChildren().at(i).getOwnerName();   //error
						string group = file.getChildren().at(i).getGroupName();   //error
						int size = file.getChildren().at(i).getSize();   //error
						string time = file.getChildren().at(i).getModTime();   //error
						string name = file.getChildren().at(i).getName();   //error
					
						cout << endl << name << "  " << permissions << "  " << owner << "  " << group << "  " << size << "  " << time;
						
					}
					return 0;
				}
				else{ //case if ls -l (not directory) is typed simply print file details
					string permissions = file.getPermStringRep();  //error
					string owner = file.getOwnerName();  //error
					string group = file.getGroupName();  //error
					int size = file.getSize();  //error
					string time = file.getModTime();  //error
					string name = file.getName();  //error
					
					cout << endl << name << "  " << permissions << "  " << owner << "  " << group << "  " << size << "  " << time;
					
				}
			}
		}
		else { //case if ls (filename) is typed
			filemanager file(argv[1]); //grabs file path specified and created filemanager object with path/name
			if(file.getOwnerName() == "Delete") {
				cout << "Failed to created filemanager object with file name provided." << endl;
				return ENOTSUP;
			}
			string file_type = file.getTypeStringRep(); //determines type of file
			if (file_type == "Directory") { //case if ls (directory) is typed
				file.expand(); //error check expands children of object specified by file path/name
				int vect_sz = file.getChildren().size();    //error check retrieve how many children the directory has
				for(int i = 0 ; i < vect_sz ; i++) { //for each child
					string curr_element_name = file.getChildren().at(i).getName();    //error check
					cout << curr_element_name << endl;
				}
				return 0;
			}
			else { //case if ls (not directory) is typed simply print file name
				string file_name = file.getName();     //error check
				cout << file_name << endl;
			}
		}
	}
}
