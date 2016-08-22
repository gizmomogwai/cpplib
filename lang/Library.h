#ifndef Library_h_
#define Library_h_

#include <lang/LangApi.h>

#include <string>
#include <lang/Exception.h>

#ifdef LINUX

#elif WIN32
  #include <windows.h> 
#endif

class LANG_API Library {

  public:
    Library(std::string& fileName) throw (Exception);  
    ~Library();
    void* getFunction(std::string& functionName) throw (Exception);
	
  private:
	  #ifdef LINUX
      void* fHandle;
  	#elif WIN32
	    HMODULE fModule;
	  #endif
    
};

#endif
