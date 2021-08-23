#include "IotdHandler.h"
#include <util/Properties.h>

IotdKeyListener::IotdKeyListener(IotdHandler* iotdHandler) : fIotdHandler(iotdHandler) {
}

void IotdKeyListener::keyPressed(KeyEvent* e) {
  if (e->keyPressed('t') == true) {
    fIotdHandler->toggleIotd();
  }
}

IotdHandler::IotdHandler(Engine* engine, ImageViewNavigator* navigator, SwitchableWatermark* iotd) : fIotd(iotd) {
  fIotd->addReference();
  navigator->addSelectionListener(this);
  engine->addKeyListener(new IotdKeyListener(this));
}

IotdHandler::~IotdHandler() {
  std::cout << "~IotdHandler" << std::endl;
  fIotd->releaseReference();
}

void IotdHandler::toggleIotd() {
  Properties p;
  loadPropertiesIfExistant(p);
  bool iotdFlag = !isIotd(p);

  fIotd->setVisible(iotdFlag);
  std::string newValue = "false";
  if (iotdFlag) {
    newValue = "true";
  }

  p.setProperty(std::string("iotd"), newValue);
  CleanUpObject<File> f(getPropertiesFile());

  FileOutputStream fOut(*f);
  DataOutputStream dOut(&fOut, false);
  p.write(dOut);
}


void IotdHandler::selectionChanged(File* f) {
  SelectionListener::selectionChanged(f);
  Properties p;
  bool iotd = isIotd(p);
  fIotd->setVisible(iotd);
}

void IotdHandler::getProperties(File* file, Properties& p) {
  if (file->exists()) {
    FileInputStream fIn(file);
    DataInputStream dIn(&fIn, false);
    p.read(dIn);
  }
}

void IotdHandler::loadPropertiesIfExistant(Properties& p) {
  if (fCurrentFile != 0) {
    File* propertiesFile = getPropertiesFile();
    CleanUpObject<File> propertiesFileCleaner(propertiesFile);

    getProperties(propertiesFile, p);
  } else {
    throw Exception("fCurrentFile == 0");
  }
}

bool IotdHandler::isIotd(Properties& p) {
  loadPropertiesIfExistant(p);
  auto value = p.getProperty("iotd", "false");
  return value == "true";
}

File* IotdHandler::getPropertiesFile() {
  if (fCurrentFile == 0) {
    throw Exception("fCurrentFile must not be 0");
  }

  std::string fileName = fCurrentFile->toString() + ".properties";
  return new File(fileName);
}
