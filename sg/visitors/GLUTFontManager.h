#ifndef _GLUTFontManager_h_
#define _GLUTFontManager_h_

#include <sg/nodeComponents/geom/Text3D.h>

#include <sg/visitors/OGLFontManager.h>

/** FontManager, der mithilfe der Glut versucht die fonts zu rendern.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2001-02-11, cK, Created.
 *  <li> 2001-02-13, cK, Commentare erweitert.
 *  <li> 2001-02-13, cK, In GLUTFontManager umgewandelt.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cK, $Author: koestlin $
 */
class GLUTFontManager : public OGLFontManager {

  public:
    /** Erzeugt den Manager. */
    GLUTFontManager() {
    }

    /** Raeumt auf. */
    virtual ~GLUTFontManager() {
    }

    void render(Text3D* text3d);

};

#endif // _GLUTFontManager_h_
