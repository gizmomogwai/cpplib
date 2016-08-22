#ifndef _VisibilityVisitor_h_
#define _VisibilityVisitor_h_

#include <sg/visitors/Visitor.h>

/** Klasse die dafuer zustaendig ist, die sichtbaren Teile eines
 * Szenegraphen als sichtbar zu markieren.
 *
 * Dazu wird benoetigt:
 * <ul>
 *   <li> Aktuelles Frustum der SGObserver 
 *        (bzw. allgemein der Projectionsgruppen). Momentan aber nur 
 *        Berechnung der Sichbarkeiten unter einem SGObserver.
 * </ul>
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-07-14, cK, Begonnen.
 * </ul>
 *
 * @version $Revision$ $Date$
 *
 * @author cK $Author$
 */
class VisibilityVisitor : public Visitor {
	public:
		std::string toString() {
			return "VisibilityVisitor";
		}

};

#endif // _VisibilityVisitor_h_
