# piIX
Employed VirtualBox virtual machine to access Rasperry Pi Desktop C++ compiler to create custom system utilities for file management.

##Practical Take-Away Experience
•	C++
•	Virtual machines (VirtualBox)
•	Object-oriented programming, basic language constructs, classes, and data types
•	Linux manual pages and documentation
•	Linux-based Raspberry Pi Desktop system and services
•	ssh, scp, sftp

##Utilities
•	mymv        Used to move and rename files
•	mycp   		  Used to copy files from source to destination named as parameters
•	myls   		  Used to list contents of directories and list names of other files
•	myls – l   	Used to list long form of ls (name, permissions, owner, group, size, time)
•	mycat   	  Used to display contents of files named as parameters
•	myrm   		  Used to removes files named as parameters
•	mydiff  		Used to compares two files named as parameters
•	mystat		  Used to output all information of file named as parameter

Commands also support full error tracking and reporting to the user.

##Structure
This project was designed through a file manager class that encapsulates both file information pulled from the system, as well as operations that can be performed on said files. Each file manager instance handles a single file, which includes the following information:
•	Name
•	Type
•	Size
•	Owner
•	Group
•	Permissions
•	Access time
•	Modification time
•	Status change time
•	Block size
•	Children
•	Error number
