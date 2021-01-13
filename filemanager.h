/*
 * AUTHOR: RILEY BLACK
 *
 * DESCRPTION OF FILE: IMPLEMENTED BY FILEMANAGER.CPP, THIS FILE GOES ON TO IMPLEMENT THE UNDERLYING METHODS INVOLVED IN A FILEMANAGER SYSTEM 
 *						THAT ESSENTIALLY EMULATES ELEMENTARY COMMAND LINE FUNCTIONS (IE. MV, LS, ETC.) INVOLVING VARIOUS FILE MANIPULATION
 *
 * DATE: WEDNESDAY OCTOBER 2 2019
 *
 **/

#pragma once
#include <iostream>
#include <fstream>
#include <vector>

class filemanager{	
	
public:
	filemanager(char * file); //constructor 
	~filemanager(); //desructor
	std ::string getTypeStringRep();  //method to return readable string representation of file type
	std ::string getPermStringRep();  //method to return readable string representation of file permissions
	char * getName();  //method to return file name 
	mode_t getType();  //method to return file type
	off_t getSize();  //method to return file size
	std ::string getOwnerName();  //method to return file owner name
	uid_t getOwnerId();  //method to return file owner id
	std ::string getGroupName();  //method to return file group name 
	gid_t getGroupId();  //method to return file group id 
	mode_t getPermissions();  //method to return file permissions
	std ::string getAccessTime();  //method to return latest file access time
	std ::string getModTime();  //method to return latest file modification time
	std ::string getStatChangeTime();  //method to return latest file status change time
	blksize_t getBlockSize();  //method to return file block size
	std ::vector<filemanager> getChildren();  //method to return vector of file children (filemanager objects)
	int getErrorNumber();  //method to return file error number
	std ::string getErrorNumberString();  //method to return file error number as readable string
	void setName(char * new_name);  //method to set file name
	int dump(std ::ostream * dump_yard); //dump method as described in assignment
	int reName(char * new_name); //rename method as described in assignment
	int remove(); //remove method as described in assignment
	std ::string compare(filemanager compare_file); //compare method as described in assignment
	int expand(); //expand method as described in assignment
	
	

	
private :
	char * name;  //string to store file name
	mode_t type;  //variable to store file type
	off_t size;  //variable to store file size
	std ::string owner_name;  //string to store file owner name
	uid_t owner_id;  //variable to store file owner id
	std ::string group_name;  //string to store file group name
	gid_t group_id;  //variable to store file group id
	mode_t permissions;  //variable to store file permissions code
	std ::string access_time;  //string to store readable file permissions code
	std ::string mod_time;  //string to store latest file modification time
	std ::string stat_change_time;  //string to store latest file status change time
	blksize_t blk_sz;  //variable to store file block size
	std ::vector<filemanager> children;  //vector to store file children filemanager objects
	int err_num;  //integer to store latest file error code

};

