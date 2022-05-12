WTS stands for windows terminal services 

````C
#include<Windows.h>
#include<stdio.h>
#include<WtsApi32.h>
#include<string>
````
WtsApi32.h primary usage for Remote Desktop Services 
WtsApi32.h header file is used for implementing WTSEnumerateProcessesEx api function 
For more infomration refer to the microsoft documentation <br>
https://docs.microsoft.com/en-us/windows/win32/api/wtsapi32/

````C
#pragma comment(lib,"wtsapi32")
`````
pragma is a special keyword used for instructing the copiler before executing the main function <br>
pragma is will the compiler to look for the specific library

````C
std::wstring GetUserNameFromSid(PSID sid) {
	if (sid == nullptr)
		return L"";
````
wstring is a C++ type that allows us to encapsulate the string in a safe way without needing to allocate memory

LookupAccountSid provides us a way to given sid to get back the username and domain name concatinate both of them to get the actual user name

L"" unicode empty string 

````C
WCHAR name[32], domain[32];
	DWORD lname = _countof(name), ldomain = _countof(domain);
	SID_NAME_USE use;
	if (!LookupAccountSid(nullptr, sid, name, &lname, domain, &ldomain, &use))
		return L"";
`````

_countof computes the number of elements isn statistically-allocated array <br>
https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/countof-macro?view=msvc-170

_countof is implemented as a function-like preprocessor macro. The C++ version has extra template machinery to detect at compile time if a pointer is passed instead of a statically declared array.

Ensure that array is actually an array, not a pointer. In C, _countof produces erroneous results if array is a pointer. <br>
In C++, _countof fails to compile if array is a pointer. An array passed as a parameter to a function decays to a pointer, which means that within the function, you can't use _countof to determine the extent of the array.


````C
WCHAR name[32], domain[32];
	DWORD lname = _countof(name), ldomain = _countof(domain);
	SID_NAME_USE use;
	if (!LookupAccountSid(nullptr, sid, name, &lname, domain, &ldomain, &use))
		return L"";

	return std::wstring(domain) + L"\\" + name;
}

````
The LookupAccountSid function accepts a security identifier (SID) as input. <br>
It retrieves the name of the account for this SID and the name of the first domain on which this SID is found.
SID stands for security identifier
If the function cannot find an account name for the SID, GetLastError returns ERROR_NONE_MAPPED. <br>
This can occur if a network time-out prevents the function from finding the name. <br>
It also occurs for SIDs that have no corresponding account name, such as a logon SID that identifies a logon session.



````C

int main()
{
	DWORD level = 1;
	WTS_PROCESS_INFO_EX* info;
	DWORD count;
	BOOL success = WTSEnumerateProcessesEx(WTS_CURRENT_SERVER_HANDLE, &level, WTS_ANY_SESSION, (LPWSTR*)&info, &count);
	if (!success)
		return 1;
	for (DWORD i = 0; i < count; i++)
	{
		PWTS_PROCESS_INFO_EX p = info + i;
		printf("PID :%6u Thread: %3u Session: %u %ws (username: %ws)\n",
		p->ProcessId, p->NumberOfThreads, p->SessionId, p->pProcessName,
			GetUserNameFromSid(p->pUserSid).c_str());
	}
	WTSFreeMemoryEx(WTSTypeSessionInfoLevel1, info, count);
	return 0;
}
````

WTSEnumerateProcessEx in general Ex in api functions are used for using the extended functions 
The api functions with Ex contains more parameters than their normal functions 




