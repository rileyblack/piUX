/*
 * AUTHOR: RILEY BLACK
 *
 * DESCRPTION OF FILE: IMPLEMENTATION OF FILEMANAGER.H, THIS FILE GOES ON TO IMPLEMENT THE UNDERLYING METHODS INVOLVED IN A FILEMANAGER SYSTEM 
 *						THAT ESSENTIALLY EMULATES ELEMENTARY COMMAND LINE FUNCTIONS (IE. MV, LS, ETC.) INVOLVING VARIOUS FILE MANIPULATION
 *
 * DATE: WEDNESDAY OCTOBER 2 2019
 *
 **/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include "filemanager.h"


using namespace std;

/*
 * Name: filemanager
 * 
 * Description: constructor - sets all data members for the class using the stat() function
 * 
 * Parameters: string containing the file name (path/name) of the file that is have a class instance created
 *
 * Return Value: N/A
 *
 **/
filemanager::filemanager(char * file){
	struct stat stat_buffer;
	if (stat(file, &stat_buffer)!=0){ //stat returns 0 upon success
		this->err_num = errno;
		this->owner_name = "Delete"; //owner name of delete is used in caller to determine is file is to be destroyed
	}
	else{
		this->name = file;
		this->type = stat_buffer.st_mode;
		this->size = stat_buffer.st_size;
		this->owner_id = stat_buffer.st_uid;
		if (getpwuid(owner_id) == NULL){ //getpwuid returns NULL upon fail
			this->err_num = errno;
			this->owner_name = "Delete"; //owner name of delete is used in caller to determine is file is to be destroyed
		}
		else{
			this->owner_name = getpwuid(owner_id)->pw_name;
			this->group_id = stat_buffer.st_gid;
			if (getgrgid(group_id) == NULL){ //getgrgid returns NULL upon fail
				this->err_num = errno;
				this->owner_name = "Delete"; //owner name of delete is used in caller to determine is file is to be destroyed
			}
			else{
				this->group_name = getgrgid(group_id)->gr_name;
				this->permissions = stat_buffer.st_mode;
				this->access_time = ctime(&stat_buffer.st_atime);
				this->mod_time = ctime(&stat_buffer.st_mtime);
				this->stat_change_time = ctime(&stat_buffer.st_ctime);
				this->blk_sz = stat_buffer.st_blksize;
				this->err_num = 0;	
			}
		}
	}
}

/*
 * Name: ~filemanager
 * 
 * Description: destructor - clears all resources associated with a class instance
 * 
 * Parameters: N/A
 *
 * Return Value: N/A
 *
 **/
filemanager::~filemanager(){ }

/*
 * Name: getTypeStringRep
 * 
 * Description: getter - returns a readable string describing the type of file contained in the class instance used to call the function
 *						that is determined through sending the type code into various built in functions such as S_ISREG (determining if 
 *						regular file)
 * 
 * Parameters: N/A
 *
 * Return Value: string describing file type of object
 *
 **/
string filemanager::getTypeStringRep() {
	if (S_ISREG(type)){
		return "Regular File";
	}
	else if (S_ISDIR(type)){
		return "Directory";
	}
	else if (S_ISCHR(type)){
		return "Character Device";
	}
	else if (S_ISBLK(type)){
		return "Block Device";
	}
	else if (S_ISFIFO(type)){
		return "FIFO";
	}
	else if (S_ISLNK(type)){
		return "Symbolic Link";
	}
	else if (S_ISSOCK(type)){
		return "Socket";
	}
	else{
		return "Error recognizing file type.";
	}
}

/*
 * Name: getPermStringRep
 * 
 * Description: getter - returns a readable string describing the file permissions contained in the class instance used to call the function
 *						that is determined through using binary operators to check certain bits characteristic of each permission field 
 *						contained in the permission code
 * 
 * Parameters: N/A
 *
 * Return Value: string describing file permissions
 *
 **/
string filemanager::getPermStringRep() {
	string permission_string;
	if (permissions & S_IRUSR) {
		 //user read permissions
		permission_string += "r";  //r if permisson granted
	}
	else {
		permission_string += "-";  //- if permisson denied
	}
	
	if (permissions & S_IWUSR) {
		 //user write permissions
		permission_string += "w";  //w if permisson granted
	}
	else {
		permission_string += "-";  //- if permisson denied
	}	
	
	if (permissions & S_IXUSR) {
		 //user execute permissions
		permission_string += "x";  //x if permisson granted
	}
	else {
		permission_string += "-";  //- if permisson denied
	}	
	
	if (permissions & S_IRGRP) {
		 //group read permissions
		permission_string += "r";  //r if permisson granted
	}
	else {
		permission_string += "-";  //- if permisson denied
	}	
	
	if (permissions & S_IWGRP) {
		 //group write permissions
		permission_string += "w";  //w if permisson granted
	}
	else {
		permission_string += "-";  //- if permisson denied
	}	

	if (permissions & S_IXGRP) {
		 //group execute permissions
		permission_string += "x";  //x if permisson granted
	}
	else {
		permission_string += "-";  //- if permisson denied
	}	
	
	if (permissions & S_IROTH) {
		 //other read permissions
		permission_string += "r";  //r if permission granted
	}
	else {
		permission_string += "-";  //- if permisson denied
	}	
	
	if (permissions & S_IWOTH) {
		 //other write permissions
		permission_string += "w";  //w if permisson granted
	}
	else {
		permission_string += "-";  //- if permisson denied
	}	
	
	if (permissions & S_IXOTH) {
		 //other execute permissions
		permission_string += "x";  //x if permisson granted
	}
	else {
		permission_string += "-";  //- if permisson denied
	}
	
	return permission_string; //return overall rwx permissions string
}
	
/*
 * Name: getName
 * 
 * Description: getter - returns a readable string describing the name of file contained in the class instance used to call the function
 * 
 * Parameters: N/A
 *
 * Return Value: string describing file name of object
 *
 **/
char * filemanager::getName() {
	return name;
}

/*
 * Name: getType
 * 
 * Description: getter - returns number describing the type of file contained in the class instance used to call the function
 * 
 * Parameters: N/A
 *
 * Return Value: number describing file type of object
 *
 **/
mode_t filemanager::getType() {
	return type;
}

/*
 * Name: getSize
 * 
 * Description: getter - returns a number describing the size (in bytes) of file contained in the class instance used to call the function
 * 
 * Parameters: N/A
 *
 * Return Value: number describing file size of object
 *
 **/
off_t filemanager::getSize() {
	return size;
}

/*
 * Name: getOwnerName
 * 
 * Description: getter - returns a readable string describing the name of the owner of the file contained in the class instance used to call the function
 * 
 * Parameters: N/A
 *
 * Return Value: string describing file owner name of object
 *
 **/
string filemanager::getOwnerName() {
	return owner_name;
}

/*
 * Name: getOwnerId
 * 
 * Description: getter - returns a number describing the owner of the file contained in the class instance used to call the function
 * 
 * Parameters: N/A
 *
 * Return Value: number describing file owner id of object
 *
 **/
uid_t filemanager::getOwnerId() {
	return owner_id;
}

/*
 * Name: getGroupName
 * 
 * Description: getter - returns a readable string describing the name of the group of the file contained in the class instance used to call the function
 * 
 * Parameters: N/A
 *
 * Return Value: string describing file group name of object
 *
 **/
string filemanager::getGroupName() {
	return group_name;
}

/*
 * Name: getGroupId
 * 
 * Description: getter - returns a number describing the group of the file contained in the class instance used to call the function
 * 
 * Parameters: N/A
 *
 * Return Value: number describing file group id of object
 *
 **/
gid_t filemanager::getGroupId() {
	return group_id;
}

/*
 * Name: getPermissions
 * 
 * Description: getter - returns a number describing the file permissions contained in the class instance used to call the function
 * 
 * Parameters: N/A
 *
 * Return Value: number describing file permissions of object
 *
 **/
mode_t filemanager::getPermissions() {
	return permissions;
}

/*
 * Name: getAccessTime
 * 
 * Description: getter - returns a readable string describing the latest file access time of the file contained in the class instance used to call the function
 * 
 * Parameters: N/A
 *
 * Return Value: string describing latest file access time of object
 *
 **/
string filemanager::getAccessTime() {
	return access_time;
}

/*
 * Name: getModTime
 * 
 * Description: getter - returns a readable string describing the latest file modification time of the file contained in the class instance used to call the function
 * 
 * Parameters: N/A
 *
 * Return Value: string describing latest file modification time of object
 *
 **/
string filemanager::getModTime() {
	return mod_time;
}

/*
 * Name: getStatChangeTime
 * 
 * Description: getter - returns a readable string describing the latest file status change time of the file contained in the class instance used to call the function
 * 
 * Parameters: N/A
 *
 * Return Value: string describing latest file status change time of object
 *
 **/
string filemanager::getStatChangeTime() {
	return stat_change_time;
}

/*
 * Name: getBlockSize
 * 
 * Description: getter - returns a number describing the block size (in bytes) of the file contained in the class instance used to call the function
 * 
 * Parameters: N/A
 *
 * Return Value: number describing file block size of object
 *
 **/
blksize_t filemanager::getBlockSize() {
	return blk_sz;
}

/*
 * Name: getChildren
 * 
 * Description: getter - returns a vector of filemanager objects reflecting the 'children' files of the file contained in the class instance used to call the function
 * 
 * Parameters: N/A
 *
 * Return Value: vector of filemanager objects that are within directory of object
 *
 **/
vector<filemanager> filemanager::getChildren() {
	return children;
}

/*
 * Name: getErrorNumber
 * 
 * Description: getter - returns a number describing the latest error code of the file contained in the class instance used to call the function
 * 
 * Parameters: N/A
 *
 * Return Value: number describing latest file error code of object
 *
 **/
int filemanager::getErrorNumber() {
	return err_num;
}

/*
 * Name: getErrorNumber
 * 
 * Description: getter - returns a readable string describing the latest error code of the file contained in the class instance used to call the function
 *						using the built in strerror() function
 * 
 * Parameters: N/A
 *
 * Return Value: string describing latest file error code of object
 *
 **/
string filemanager::getErrorNumberString() {
	return strerror(err_num);
}
	
/*
 * Name: setName
 * 
 * Description: setter - updates the data member name based on string inputted as a parameter contained in the class instance used to call the function
 *						by simply using the reName() fucntion defined below
 * 
 * Parameters: string reflecting what the data member name is desired to be updated too
 *
 * Return Value: N/A
 *
 **/
void filemanager::setName(char * new_name) {
	if (reName(new_name) != 0) {
		cout << "Rename failed." << endl;
	}
}

/*
 * Name: dump
 * 
 * Description:  this function takes a file stream as a parameter and places the contents of the file used to call the function to the file contained
 *				as a parameter
 * 
 * Parameters: ostream object that will be passed the contents of the file used to call the function
 *
 * Return Value: integer reflecting either success or failure, where 0 is success and anything else is failure, with the int then reflecting the error
 *
 **/
int filemanager::dump(ostream * dump_yard){
	if (getTypeStringRep() != "Regular File"){ //checking if regular file
		err_num = ENOTSUP;
		return ENOTSUP;
	}
	if (dump_yard->bad()){ //checking if filestream is ready to be dumped on
		err_num = EIO;
		return EIO;
	}
	ifstream file; 
	file.open(name); //opening ifstream object that will supply the contents
	if (file.fail()){ //checking if the file was opened correctly 
		err_num = ENOSR;
		return ENOSR;
	}
	int loop_num = size / blk_sz; //number of blocks needed to cover entire file
	int remainder = size % blk_sz; //number of remaining bytes when no more 'full' blocks remain
	char * holder = new char[blk_sz]; //buffer to hold blocks of data
	
	for (int i = 0; i < loop_num; i++){ 
		file.read(holder, blk_sz); //grabs data from input file
		if (file.bad()){ //checks if read went okay
			err_num = EIO;
			return EIO;
		}
		dump_yard->write(holder, blk_sz); //writes data to output file
		if (dump_yard->bad()){ //checks if write went okay
			err_num = EIO;
			return EIO;
		}
	} //loops terminate when no more full blocks can be grabbed
	
	file.read(holder, remainder); //only reads the required amount of remaining bytes into buffer
	if (file.bad()) { //checks if read went okay
		err_num = EIO;
		return EIO;
	}
	dump_yard->write(holder, remainder); //only writes required amount of remaining bytes to output file
	if (dump_yard->bad()) { //checks if write went okay
		err_num = EIO;
		return EIO;
	}
	file.close(); //closes input file
	if(file.bad()) { //checks if read went okay
		err_num = EIO;
		return EIO;
	}
	err_num = 0; //sets error number to success 
	return err_num; //return 0
}

/*
 * Name: reName
 * 
 * Description:  this function chnages the name of the file from its existing name to the new name provided as a parameter to this function
 *  
 * Parameters: string reflecting the desired new name
 *
 * Return Value: integer reflecting either success or failure, where 0 is success and anything else is failure, with the int then reflecting the error
 *
 **/
int filemanager::reName(char * new_name){
	if (rename(name, new_name) == -1){ //renaming using built in rename() and checking if successful
		err_num = errno;
		return err_num;
	}
	name = new_name; //updating data member
	err_num = 0; //sets error number to success
	return err_num;	//return 0
}

/*
 * Name: remove
 * 
 * Description:  this function removes the file used to invoke this function from the file system
 *  
 * Parameters: N/A
 *
 * Return Value: integer reflecting either success or failure, where 0 is success and anything else is failure, with the int then reflecting the error
 *
 **/
int filemanager::remove(){
	this->type = NULL;
	this->size = NULL;
	this->owner_id = NULL;
	this->owner_name = "Destroy";
	this->group_id = NULL;
	this->group_name.clear();
	this->permissions = NULL;
	this->access_time.clear();
	this->mod_time.clear();
	this->stat_change_time.clear();
	this->blk_sz = NULL;
	this->err_num = NULL;
	this->children.clear();
	
	if (unlink(name) == -1) { //calling unlink and also checking if the process was successful
		err_num = errno;
		return err_num;
	}
	err_num = 0; //sets error number to success
	return err_num;	//return 0
}

/*
 * Name: compare
 * 
 * Description:  this function compares the file used to invoke this function from the file system with the file passed as a parameter to see if they are identical
 *				by first comparing if the file sizes are the same and if so, then compares block by block of each file
 *  
 * Parameters: a filemanager object that is to be compared to the filemanager object used to call this method
 *
 * Return Value: string reflecting either same, different, or failure, where the error is reflected in the string if a failure occurs
 *
 **/
string filemanager::compare(filemanager compare_file){
	if ((getTypeStringRep() != "Regular File")||(compare_file.getTypeStringRep() != "Regular File")) { //first checks if both files are regular files
		err_num = ENOTSUP;
		return "ENOTSUP";
	}
	if (size != compare_file.getSize())	{ //checks if sizes are identical
		return "different";
	}
	ifstream file1;
	ifstream file2;
	file1.open(name); //opens the file used to invoke function
	file2.open(compare_file.getName()); //opens the file to compare that is sent as a parameter
	if ((file1.fail())||(file2.fail())) { //checks if either file fails to open
		err_num = ENOSR;
		return "ENOSR";
	}
	int loop_num = size / blk_sz; //number of blocks needed to cover both files (assuming same size)
	int remainder = size % blk_sz; //number of remaining bytes when no more 'full' blocks remain (assuming same size)
	char * holder1 = new char[blk_sz]; //first file buffer
	char * holder2 = new char[blk_sz]; //second file buffer
	for (int i = 0; i < loop_num; i++) { //loops until no more full blocks to grab
		file1.read(holder1, blk_sz); //fills buffer 1 with block from file 1
		file2.read(holder2, blk_sz); //fills buffer 2 with block from file 2
		if ((file1.bad()) || (file2.bad())) { //checks if both reads went okay
			err_num = EIO;
			return "EIO";
		}
		for (int j = 0; j < blk_sz; j++){ //for all elements in the buffer
			if (holder1[j] != holder2[j]) { //if any are different
				return "different";
			}
		}
	} //loops terminate when no more full blocks can be grabbed
	
	file1.read(holder1, remainder); //only reads the required amount of remaining bytes into buffer
	file2.read(holder2, remainder);
	if ((file1.bad()) || (file2.bad())) { //checks if both reads went okay
		err_num = EIO;
		return "EIO";
	}
	for (int j = 0; j < remainder; j++) { //loops until remainder is depleted
		if (holder1[j] != holder2[j]) { //compares
			return "different";
		}
	}
	
	file1.close(); //closes file 1
	file2.close(); //closes file 2
	if((file1.bad()) || (file2.bad())) { //checks if both reads went okay
		err_num = EIO;
		return "EIO";
	}
	err_num = 0; //sets error number to success
	return "identical"; 
}

/*
 * Name: expand
 * 
 * Description:  operates on directories only and is used to fill in the children of the file object this function was invoked upon
 *  
 * Parameters: N/A
 *
 * Return Value: integer reflecting either success or failure, where 0 is success and anything else is failure, with the int then reflecting the error
 *
 **/
int filemanager::expand(){
	if (getTypeStringRep() != "Directory") { //checks if directory
		err_num = ENOTSUP;
		return ENOTSUP;
	}
	DIR * root_directory = opendir(name); //opens directory 
	if (root_directory == NULL) { //checks if opening went okay
		err_num = errno;
		return err_num;
	}
	struct dirent * child_directory = readdir(root_directory); //creates dirent object to store result from readdir()
	while (child_directory != NULL){ //while the directory has more children 
		if (((strncmp(child_directory->d_name, ".", 1)) != 0)&&((strncmp(child_directory->d_name, "..", 2))!=0)) { //used to not include . and .. files on some systems
			string adder = name; //folder name (ie. pathname of directory we are expanding)
			string more = child_directory->d_name; //the name of the child file we are adding
			string stringy = adder + "/" + more; //creating the file path for the child file we are about to create a filemanager object for so that stat works properly
			char * charey = new char[stringy.length() + 1]; //creating char * to copy the string over to
			strcpy(charey, stringy.c_str()); //convert the string to a char pointer so that it is accepted by the filemanager constructor
			filemanager some_new_file_manager(charey); //create filemanager object for the child file in question
			if (some_new_file_manager.getOwnerName() == "Delete"){ //checking to see if creation went okay
				cout << "Failed to created filemanager object with file name provided." << endl;
				return ENOTSUP;
			}
			children.push_back(some_new_file_manager); //adding child to children vector of directory  
		}
		child_directory = readdir(root_directory); //get next child
	}
	
	if (closedir(root_directory) == -1){ //close directory and check to see if it went okay
		err_num = errno;
		return err_num;
	}
	
	err_num = 0;
	return err_num;
}
