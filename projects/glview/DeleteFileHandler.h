#ifndef DeleteFileHandler_h_
#define DeleteFileHandler_h_

#include "SelectionListener.h"
#include <sgtools/KeyListener.h>
#include <sgtools/KeyEvent.h>
#include <sgtools/Engine.h>
#include "ImageViewNavigator.h"

class DeleteFileHandler : public SelectionListener {
	public:
		DeleteFileHandler(Engine* engine, ImageViewNavigator* navigator);
		
		virtual ~DeleteFileHandler() {
		  std::cout << "~DeleteFileHandler" << std::endl;
		}
		
		void deleteFile();
	
};

class DeleteFileListener : public KeyListener {
  
  public:
    DeleteFileListener(DeleteFileHandler* handler) : fHandler(handler) {}
    virtual ~DeleteFileListener() {}
    void keyPressed(KeyEvent* e);
  private:
    DeleteFileHandler* fHandler;
    
};

#endif // DeleteFileHandler_h_
