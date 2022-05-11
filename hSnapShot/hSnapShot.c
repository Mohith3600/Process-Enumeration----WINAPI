#include<Windows.h>
#include<stdio.h>
#include<TlHelp32.h>

int Error(const char* msg) {  //ERROR FUNCTION TO RETURN THE ERROR
	printf("%s (%u)", msg, GetLastError);
//s - print the string pointed to by a char *
	return 1;
}
int main()
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapShot == INVALID_HANDLE_VALUE)
		return Error("Failed to create snapshot");
	
	PROCESSENTRY32 pe; //STRUCTURE 
	pe.dwSize = sizeof(pe);

	if (!Process32First(hSnapShot, &pe))
		return Error("Failed in Process32First");

	do {
		printf("PID: %6u (PPID: %6u) Threads: %3u %ws\n", 
			pe.th32ProcessID, pe.th32ParentProcessID, pe.cntThreads, pe.szExeFile);
//6 is the space 
//u print an unsigned as an unsigned decimal number 

	} while (Process32Next(hSnapShot, &pe));

	CloseHandle(hSnapShot); //GOOD PRACTISE TO CLOSE THE HANDLE
	return 0;
}