#include <gui/JMenuItem.h>

#include <gui/IDManager.h>
#include <lang/Exception.h>

#ifdef _WINNT
  std::map<UINT, JMenuItem*> JMenuItem::id2JMenuItems;
#endif

bool JMenuItem::first = true;

JMenuItem::JMenuItem(std::string name) {
  info.cbSize = sizeof(MENUITEMINFO);
#ifdef _WIN2K
  info.fMask = MIIM_DATA | MIIM_STRING | MIIM_ID;
#endif
#ifdef _WINNT
  info.fMask = MIIM_DATA | MIIM_TYPE | MIIM_ID;
  info.wID = IDManager::getNextID();
#endif
  info.fType = MFT_STRING;
  info.dwItemData = (unsigned long)this;
  /*
  TCHAR* text = new TCHAR[name.length()+1];
  text[0] = 0;
  strcat(text, name.c_str());
  info.dwTypeData = text;
  */
  menuName = name;
  info.dwTypeData = (TCHAR*)name.c_str();
  info.cch = name.length();

  #ifdef _WINNT
    registerID();
  #endif
}

JMenuItem::JMenuItem() {
}

JMenuItem* JMenuItem::createSeparator() {

  JMenuItem* res = new JMenuItem();
  res->info.cbSize = sizeof(MENUITEMINFO);
  res->info.fMask = MIIM_TYPE;
  res->info.fType = MFT_SEPARATOR;
  info.wID = IDManager::getNextID();
  res->info.dwTypeData = 0;

  #ifdef _WINNT
    registerID();
  #endif

  return(res);
}

#ifdef _WINNT
  void JMenuItem::registerID() {

    std::map<UINT, JMenuItem*>::iterator i =
      id2JMenuItems.find(info.wID);
    if (i != id2JMenuItems.end()) {
      throw(Exception("JMenuItem - id schon vorhanden", __FILE__, __LINE__));
    }
    id2JMenuItems.insert(std::make_pair(info.wID, this));
  }

  JMenuItem* JMenuItem::getJMenuItem(UINT id) {
    std::map<UINT, JMenuItem*>::iterator i = id2JMenuItems.find(id);
    if (i == id2JMenuItems.end()) {
      return(0);
    }
    return(i->second);
  }
#endif

JMenuItem::~JMenuItem() {
//  if (info.dwTypeData != 0) {
//    delete[](info.dwTypeData);
//  }
}

MENUITEMINFO* JMenuItem::getItemInfo() {
  return(&info);  
}
