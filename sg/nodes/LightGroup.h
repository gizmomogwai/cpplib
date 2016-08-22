#ifndef _LightGroup_h_
#define _LightGroup_h_

#include <sg/nodes/Group.h>
#include <sg/nodeComponents/Light.h>

/** Gruppe deren Kinder beleuchtet sind.
 *
 * <p>
 * Curriculum Vitae:
 * <ul> 
 *   <li> 2001-03-08, cKgS, Created.
 * </ul>                            
 *
 * @todo Light sollte threadsafe werden (UpdateObject).
 * @todo Ueberlegen, wie man mehrer Lichter an den startbringt,
 * @todo ueberlegen, wie man es hinkriegt, dass man die lichter einzeln
 *       bewegen kann.
 * 
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cKgS, $Author: koestlin $
 */
class LightGroup : public Group {

  public:
    /** Erzeugt einen Gruppe mit Lichteinstellungen.
     *
     * @param _light Licht.
     */
    LightGroup(Light* _light) {
      _light->addReference();
      light = _light;  
    }
    
    /** Raeumt auf. */
    virtual ~LightGroup() {
      light->releaseReference();  
    }                           

    void accept(Visitor* v) {
      v->visit(this);
    }
    
    /** Licht mit dem die Kinder beleuchtet werden. */
    Light* light;

    std::string toString() {
      std::ostringstream out;
      out << "LightGroup[" << getChildCount() << "]" << std::ends;
      std::string res(out.str());
      return(res);
    }

};

#endif // _LightGroup_h_
