#include <lang/System.h>

#include <iostream>

#ifdef LINUX
void System::shutdown() {
}

void System::reboot() {
}

#endif

#ifdef WIN32
  void System::shutdown() {
    exitWindows(EWX_POWEROFF);
  } 

  void System::reboot() {
    exitWindows(EWX_REBOOT);
  }

  void System::exitWindows(UINT mode) {

    HANDLE hToken; 
	  TOKEN_PRIVILEGES tkp; 
	   
	  // Get a token for this process. 
	  if (!OpenProcessToken(GetCurrentProcess(), 
		  TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		  std::cout << "Cannot open process" << std::endl;
		  return;
	  }
 
	  // Get the LUID for the shutdown privilege. 
	  LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
	          &tkp.Privileges[0].Luid); 
	   
	  tkp.PrivilegeCount = 1;  // one privilege to set    
	  tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	   
	  // Get the shutdown privilege for this process. 
	  AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
	          (PTOKEN_PRIVILEGES)NULL, 0); 
	   
	  // Cannot test the return value of AdjustTokenPrivileges. 
	  if (GetLastError() != ERROR_SUCCESS)  {
		  std::cout << "Cannot adjust Token Privileges" << std::endl;
	  }
	   
	  // Shut down the system and force all applications to close. 
	  if (!ExitWindowsEx(mode | EWX_FORCE, 0)) {
		  std::cout << "ExitWindowsEx ging nicht" << std::endl;
	  }
  }

#endif
