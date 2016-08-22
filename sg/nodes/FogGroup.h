#ifndef _FogGroup_h_
#define _FogGroup_h_

#include <sg/nodes/Group.h>
#include <sg/nodeComponents/FogAttributes.h>
#include <sg/visitors/Visitor.h>

#include <string>
       
/** Gruppe mit fog eignenschaften.
 *
 * Alle Kinder werden in den Nebel des Grauens gehuellt :))
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-03-02, cKgS, Created.
 * </ul>
 *
 * @todo FogAttributes sind nicht threadsafe.
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cKgS, $Author: koestlin $  
 */
class FogGroup : public Group {
  
  public:
    /** Erzeugt eine neue Foggruppe.
     */
    FogGroup() : fog(0) {
    }
    
    /** Raeumt auf. */
    virtual ~FogGroup() {
      if (fog != 0) {
        fog->releaseReference();
        fog = 0;
      }
    }

    void accept(Visitor* v) {
      v->visit(this);
    }
    
    /** Setzt die Nebelattribute.
     *
     * @param _fog Nebelattribute.
     */
    void setFog(FogAttributes* _fog) {
      _fog->addReference();
      if (fog != 0) {
        fog->releaseReference();  
      }
      fog = _fog;
    }

    std::string toString() {
      return("FogGroup");
    }

    
    /** Fogparametersatz. (eignetlich nur fuer die Visitoren sichtbar. */
    FogAttributes* fog;
  
};

#endif //_FogGroup_h_
