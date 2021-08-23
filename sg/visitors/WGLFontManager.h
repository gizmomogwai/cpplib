#ifndef _WGLFontManager_h_
#define _WGLFontManager_h_

#include <sg/visitors/OGLFontManager.h>

#ifdef OSX
  #include <OpenGL/gl.h>
#else
  #include <GL/gl.h>
#endif

/** Stellt Text3D mithilfe von wglfunktionen dar.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-02-13, cK, Created.
 *   <li> 2001-03-13, cK, fonts anhand von glyphmetrics skaliert.
 *   <li> 2001-07-19, gS, Extrusion rausgemacht, und bold
 * </ul>
 *
 * @version $Revision: 1.3 $, $Date: 2001/08/08 14:32:20 $
 *
 * @author cK, $Author: schaefer $
 */
class WGLFontManager : public OGLFontManager {

#ifdef WIN32
  public:
    /** Erzeugt den Manager. */
    WGLFontManager(float extrusion=0.35f);

    /** Raeumt auf. */
    virtual ~WGLFontManager();

    void render(Text3D* text3d);
  private:
    /** OGL-Objectid des ersten erzeugten Buchstabens. */
    GLuint first;

    /** Basis, die aktiviert werden muss, um bytearrays
     * mit den generierten calllists zu rendern.
     */
    GLuint base;

    /** Metricen der buchstaben. */
    GLYPHMETRICSFLOAT* glyphs;

    /** Der eignetliche Font. */
    HFONT theFont;

    /** Anzahl an verwendeten Displaylisten. */
    unsigned int totalChars;

#endif
};


#endif // _WGLFontManager_h_
