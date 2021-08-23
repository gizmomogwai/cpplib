#ifndef ExifDateHandler_h_
#define ExifDateHandler_h_

#include <sgtools/KeyListener.h>
#include <sgtools/KeyEvent.h>
#include <sgtools/Engine.h>
#include <util/Date.h>

#include "InfoNode.h"
#include "SelectionListener.h"
#include "ImageViewNavigator.h"

class ExifDateHandler : public SelectionListener {

  public:
    ExifDateHandler(Engine* engine, ImageViewNavigator* navigator, SwitchableWatermark* thumb, SwitchableWatermark* async);

    virtual ~ExifDateHandler();

    void selectionChanged(File* newFile);

    void adjustDate();

  private:
    void freeExifDate();
    void getExifInfos();
    void checkSyncState();
    bool isSynced();

    Date* fExifDate;

    SwitchableWatermark* fThumb;
    SwitchableWatermark* fAsync;

};

class ExifKeyListener : public KeyListener {
  public:
    ExifKeyListener(ExifDateHandler* dateHandler);
    virtual ~ExifKeyListener();
    void keyPressed(KeyEvent* event);
  private:
    ExifDateHandler* fHandler;
};


#endif
