#ifndef _MenuItem_h_
#define _MenuItem_h_

#include <gui/WinTarget.h>

#include <string>

#include <windows.h>

#ifdef _WINNT
  #include <map>
#endif
    
class JMenuItem {
  public:
    JMenuItem(std::string name);


    JMenuItem* createSeparator();
    
    virtual ~JMenuItem();
    
    virtual void actionPerformed() {
    }

    MENUITEMINFO* getItemInfo();

    static bool first;
    
  private:
    JMenuItem();

    MENUITEMINFO info;

    std::string menuName;

#ifdef _WINNT
  public:
    static JMenuItem* getJMenuItem(UINT id);
  private:
    void registerID();
    static std::map<UINT, JMenuItem*> id2JMenuItems;
#endif

  
};

#endif // _MenuItem_h_
