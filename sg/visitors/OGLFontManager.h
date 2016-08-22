#ifndef _OGLFontManager_h_
#define _OGLFontManager_h_

#include <sg/nodeComponents/geom/Text3D.h>

/** Interface fuer alle Klassen, die als Fontmanager auftreten wollen.
 *
 * <p>
 * Curriculum Virtae:
 * <ul>
 *   <li> 2001-02-13, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cK, $Author: koestlin $
 */
class OGLFontManager {
   
  public:
    /** Raeumt auf. */
    virtual~OGLFontManager() {}
            
    /** Rendert einen Text3D.
     * 
     * @param text3d Zu rendernder Text.
     */        
    virtual void render(Text3D* text3d) = 0;
             
};


#endif // _OGLFontManager_h_
