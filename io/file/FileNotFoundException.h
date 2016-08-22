#ifndef _FileNotFoundException_h_
#define _FileNotFoundException_h_

#include <io/IoApi.h>

#include <lang/Exception.h>

class IO_API FileNotFoundException : public Exception {
public:
	FileNotFoundException(const std::string _msg, 
												const char* _fileName, 
												const int _lineNr) 
		: Exception(_msg, _fileName, _lineNr) {
	}

};

#endif // _FileNotFoundException_h_
