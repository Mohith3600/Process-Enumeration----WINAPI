In this readme.md I will try to explain and cover all the concepts used in the program line by line 

To begin with the header which are used are 
#include<Windows.h>
#include<stdio.h>
#include<TlHelp32.h>

As mentioned in my WinAPI repository Windows.h is important to use winapi functions in the program as it contains all the required functions 

TlHelp32.h
TlHelp32.h header file contains the functions CreateToolhelp32Snapshot <br>
For more information please refer to this link of the Microsoft documentation
https://docs.microsoft.com/en-us/windows/win32/api/tlhelp32/nf-tlhelp32-createtoolhelp32snapshot


int Error(const char* msg) {  //ERROR FUNCTION TO RETURN THE ERROR
	printf("%s (%u)", msg, GetLastError);
//s - print the string pointed to by a char *
	return 1;
}

The Error function returns error message if any occurs in the program 

HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

The HANDLE is a special keyword used to get the handle of the process 
hSnapShot is variable declared to the fucntion CreateToolhelp32Snapshot

CreateToolhelp32Snapshot is the actual winapi function used for enumerating the processes on the system 
It takes two parameters falgs and process ids


PROCESSENTRY32 pe; //STRUCTURE 
	pe.dwSize = sizeof(pe);

PROCESSENTRY32 is an inbuilt function it describes an entry from from a list of the processes residing in the system address space when the snapshot was taken
You can click this link for further information
https://docs.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-processentry32

if (!Process32First(hSnapShot, &pe))
		return Error("Failed in Process32First");

	do {
		printf("PID: %6u (PPID: %6u) Threads: %3u %ws\n", 
			pe.th32ProcessID, pe.th32ParentProcessID, pe.cntThreads, pe.szExeFile);


. operator is used to access the attributes which are present in the PROCESSENTRY32
6 is used for blank spaces 
u is used for printing the unsigned as as unsigned decimal number


	} while (Process32Next(hSnapShot, &pe));

	CloseHandle(hSnapShot); 
It is better to close the Handle for the file after the usage. This will be useful for not causing memory leak functions 

	return 0;
}