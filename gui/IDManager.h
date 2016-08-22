#ifndef _IDManager_h_
#define _IDManager_h_

#include <windows.h>

class IDManager {

  public:
    static UINT getNextID() {
      return(id++);
    }
    static UINT id;


};



#endif // _IDManager_h_
