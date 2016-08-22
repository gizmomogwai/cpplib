#ifndef _Menu_h_
#define _Menu_h_

#include <gui/WinTarget.h>

#include <Windows.h>

#include <vector>
#include <string>
#include <gui/JMenuItem.h>

                        
/** Menuklasse.
 * Ein Menu ist ein Menuitem, das jedoch wiederum MenuItems als Kinder haben kann.
 *
 * @todo Menueigenes Fenster muss alle Events abhandeln.
 */    
class JMenu : public JMenuItem {

  public:
    JMenu(std::string name, int menuHeight);

    virtual ~JMenu();

    void addChild(JMenu* menu);

    void addChild(JMenuItem* menuItem);

    JMenuItem* getChild(int idx);

    void actionPerformed() {
    }

    void popup(HWND hWnd);

#ifdef _WIN2K
    static JMenu* getJMenu(HMENU handle);
#endif
#ifdef _WINNT
    static JMenu* getJMenu(UINT id);
#endif

    HMENU getHandle();

    void addSeparator();

  private:
    void appendChild(JMenuItem* item);

    HMENU handle;
    
    std::vector<JMenuItem*> childs;

};

#endif // _Menu_h_
