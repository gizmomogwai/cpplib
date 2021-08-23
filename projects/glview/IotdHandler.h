#ifndef IotdHandler_h_
#define IotdHandler_h_

#include <io/file/File.h>
#include <io/file/FileInputStream.h>
#include <io/file/FileOutputStream.h>

#include <lang/CleanUpObject.h>

#include <sgtools/KeyListener.h>
#include <sgtools/KeyEvent.h>
#include <sgtools/Engine.h>

class Properties;

#include "SelectionListener.h"
#include "ImageViewNavigator.h"
#include "InfoNode.h"

class IotdHandler : public SelectionListener {
  public:
    IotdHandler(Engine* engine, ImageViewNavigator* navigator, SwitchableWatermark* iotd);
    virtual ~IotdHandler();
    void selectionChanged(File* f);
    void toggleIotd();
  private:
    SwitchableWatermark* fIotd;

    void getProperties(File* file, Properties& p);
    File* getPropertiesFile();
    void loadPropertiesIfExistant(Properties& p);
    bool isIotd(Properties& p);
};

class IotdKeyListener : public KeyListener {
  public:
    IotdKeyListener(IotdHandler* handler);
    virtual~ IotdKeyListener() {}
    void keyPressed(KeyEvent* event);

  private:
    IotdHandler* fIotdHandler;
};

#endif
