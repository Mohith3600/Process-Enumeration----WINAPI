In this readme.md I will try to explain and cover all the concepts used in the program line by line 

To begin with the header which are used are 
````C
#include<Windows.h>
#include<stdio.h>
#include<TlHelp32.h>
````

As mentioned in my WinAPI repository Windows.h is important to use winapi functions in the program as it contains all the required functions 

TlHelp32.h
TlHelp32.h header file contains the functions CreateToolhelp32Snapshot <br>
For more information please refer to this link of the Microsoft documentation
https://docs.microsoft.com/en-us/windows/win32/api/tlhelp32/nf-tlhelp32-createtoolhelp32snapshot

````C
int Error(const char* msg) {  //ERROR FUNCTION TO RETURN THE ERROR
	printf("%s (%u)", msg, GetLastError);
//s - print the string pointed to by a char *
	return 1;
}

````
The Error function returns error message if any occurs in the program 

````C
HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
````
The HANDLE is a special keyword used to get the handle of the process 
hSnapShot is variable declared to the fucntion CreateToolhelp32Snapshot

CreateToolhelp32Snapshot is the actual winapi function used for enumerating the processes on the system 
It takes two parameters falgs and process ids

````C
PROCESSENTRY32 pe; //STRUCTURE 
	pe.dwSize = sizeof(pe);
````

PROCESSENTRY32 is an inbuilt function it describes an entry from from a list of the processes residing in the system address space when the snapshot was taken
You can click this link for further information
https://docs.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-processentry32

````C
if (!Process32First(hSnapShot, &pe))
		return Error("Failed in Process32First");

	do {
		printf("PID: %6u (PPID: %6u) Threads: %3u %ws\n", 
			pe.th32ProcessID, pe.th32ParentProcessID, pe.cntThreads, pe.szExeFile);





	} while (Process32Next(hSnapShot, &pe));
````
. operator is used to access the attributes which are present in the PROCESSENTRY32 <br>
6 is used for blank spaces <br>
u is used for printing the unsigned as as unsigned decimal number <br>
````C
	CloseHandle(hSnapShot); 
````
It is better to close the Handle for the file after the usage. This will be useful for not causing memory leak functions 

	return 0;
}
