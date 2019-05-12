// May Trinh
// CMPS 4103 - Operating Systems
// Assignment 2 - Windows
// 3 October 2018

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <atlstr.h> 
#include <string>

using namespace std;
void _tmain()
{
	int val1, val2;
	TCHAR operation;

	cin >> operation;
	while (operation != '%') {
		if (operation == '+') {//addition operation
			cin >> val1 >> val2;
			printf("%d\n", val1 + val2);
		}
		else if (operation == '-') { //subtraction operation
			cin >> val1 >> val2;
			printf("%d\n", val1 - val2);
		}
		else //create new process when a filename path is enter
		{
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			string line;
			CString sbuffer = operation;
			getline(cin, line);
			sbuffer += line.c_str();

			LPSTR command;
			command = sbuffer.GetBuffer(sbuffer.GetLength());

			ZeroMemory(&si, sizeof(si));
			ZeroMemory(&pi, sizeof(pi));
			// Start the child process.
			if (!CreateProcess(
				NULL, // No module name (use command line)
				command, // Command line
				NULL, // Process handle not inheritable
				NULL, // Thread handle not inheritable
				FALSE, // Set handle inheritance to FALSE
				0, // No creation flags
				NULL, // Use parent's environment block
				NULL, // Use parent's starting directory
				&si, // Pointer to STARTUPINFO structure
				&pi) // Pointer to PROCESS_INFORMATION structure
				)
			{
				printf("CreateProcess failed \n");
				return;
			}
			// Wait until child process exits.
			WaitForSingleObject(pi.hProcess, INFINITE);
			// Close process and thread handles.
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
		cin >> operation;
	}
	return;
}