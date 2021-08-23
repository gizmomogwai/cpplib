#ifndef SelectionListener_h_
#define SelectionListener_h_

#include <io/file/File.h>

class SelectionListener {
  public:
		SelectionListener() : fCurrentFile(0) {
		}
		
    virtual ~SelectionListener() {
		  if (fCurrentFile != 0) {
				delete fCurrentFile;
			}
		}
		
		virtual void selectionChanged(File* f) {
			if (fCurrentFile != 0) {
				delete fCurrentFile;
			}
			fCurrentFile = new File(f);
		}
		
	protected:
		File* fCurrentFile;
};

#endif
