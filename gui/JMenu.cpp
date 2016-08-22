#include <gui/JMenu.h>

#include <lang/Exception.h>

#include <gui/JMenuItem.h>

#include <assert.h>
#include <util/DebugTools.h>

JMenu::JMenu(std::string name, int menuHeight) : JMenuItem(name) {
  handle = CreatePopupMenu();
  assert(handle != NULL);

  #ifdef _WIN2K
    MENUINFO info;
    info.cbSize = sizeof(MENUINFO);
    info.fMask = MIM_MENUDATA | MIM_STYLE | MIM_MAXHEIGHT;
    info.dwStyle = MNS_NOTIFYBYPOS;
    info.cyMax = menuHeight;
    info.hbrBack = NULL;
    info.dwContextHelpID = 0;
    info.dwMenuData = (unsigned long)this;
    ::SetMenuInfo(getHandle(), &info);
  #endif
}

JMenu::~JMenu() {
  BOOL res = DestroyMenu(handle);
//  assert(res != 0);

  std::vector<JMenuItem*>::iterator i = childs.begin();
  while (i != childs.end()) {
    delete(*i++);
  }
}

void JMenu::addSeparator() {
  JMenuItem* newOne = JMenuItem::createSeparator();
  appendChild(newOne);
}

void JMenu::appendChild(JMenuItem* item) {


  BOOL res = InsertMenuItem(getHandle(), childs.size(), TRUE, item->getItemInfo());
  DebugTools::printLastError(res != 0);

  childs.push_back(item);
}

void JMenu::addChild(JMenu* subMenu) {

  appendChild(subMenu);

  MENUITEMINFO info;
  info.cbSize = sizeof(MENUITEMINFO);
  info.fMask = MIIM_SUBMENU;
  info.hSubMenu = subMenu->getHandle();
  BOOL res = SetMenuItemInfo(getHandle(), childs.size()-1, TRUE, &info);
  DebugTools::printLastError(res != 0);
}

void JMenu::addChild(JMenuItem* menuItem) {
  appendChild(menuItem);
}

HMENU JMenu::getHandle() {
  return(handle);
}


#ifdef _WIN2K
  JMenu* JMenu::getJMenu(HMENU handle) {
    MENUINFO info;
    info.cbSize = sizeof(MENUINFO);
    info.fMask = MIM_MENUDATA;
    BOOL res = GetMenuInfo(handle, &info);
    DebugTools::printLastError(res != 0);

    return((JMenu*)info.dwMenuData);
  }
#endif
#ifdef _WINNT
  JMenu* JMenu::getJMenu(UINT id) {
    return((JMenu*)JMenuItem::getJMenuItem(id));
  }
#endif

JMenuItem* JMenu::getChild(int idx) {
  if (idx >= childs.size()) {
    throw(Exception("No Such Element", __FILE__, __LINE__));
  }
  return(childs[idx]);
}

void JMenu::popup(HWND hWnd) {
  POINT pos;
  GetCursorPos(&pos);
  BOOL res = TrackPopupMenu(getHandle(), 
    TPM_CENTERALIGN | TPM_VCENTERALIGN | TPM_LEFTBUTTON |TPM_RECURSE, 
    pos.x, pos.y, 0, hWnd, NULL);
  DebugTools::printLastError(res != 0);
}