#ifndef _RCColor3f_h_
#define _RCColor3f_h_

#include <vecmath/Color3f.h>
#include <util/RefCountedObject.h>

/** Farbe die RefCounted ist und somit vom Szenegraph 
 * verwaltet werden kann.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-05-26, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2001/05/28 09:40:54 $
 *
 * @author cK, $Author: koestlin $
 */
class RCColor3f : public Color3f, public RefCountedObject {
  public:
    /** Erzeugt eine neue Uninitialisierte Farbe. */
    RCColor3f() : Color3f() {
    }

    /** Erzegut eine Farbe aus einer anderen.
     *
     * @param c Zu kopierende Farbe.
     */
    RCColor3f(Color3f* c) : Color3f(c) {
    }

    /** Erzeugt eine neue Farbe.
     *
     * @param r Rotkomponente.
     * @param g Gruenkomponente.
     * @param b Blaukomponente.
     */
    RCColor3f(float r, float g, float b) : Color3f(r, g, b) {
    }

    /** Raeumt auf. */
    virtual ~RCColor3f() {
    }

};

#endif // _RCColor3f_h_
