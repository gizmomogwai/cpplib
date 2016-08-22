#include <util/DebugTools.h>

#include <assert.h>

void DebugTools::printLastError(bool value) {

  if (value == false) {
#ifdef WIN32
    LPVOID lpMsgBuf;
    FormatMessage( 
		  FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		  FORMAT_MESSAGE_FROM_SYSTEM | 
		  FORMAT_MESSAGE_IGNORE_INSERTS,
		  NULL,
		  GetLastError(),
		  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		  (LPTSTR) &lpMsgBuf,
		  0,
		  NULL 
		  );

    MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );

    LocalFree( lpMsgBuf );
#endif
  }
  assert(value);
}

