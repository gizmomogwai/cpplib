#ifndef _ImplicitSGNode_h_
#define _ImplicitSGNode_h_

#include <sg/nodes/Node.h>
#include <sg/visitors/Visitor.h>
#include <sg/visitors/RenderVisitor.h>

/** Szenegraphenknotenklasse, die selbst fuer ihr 
 * Zeichnen verantwortlich ist.
 *
 * Die Vermutung ist, dass sich manche effekte leichter und 
 * natuerlicher mit dieser Componentenartigen paint philosophie 
 * realisieren lassen (z.b. spiegel, sonneneffekt, evtl. partikelsysteme etc.)
 *
 * In der PaintMethode sollen SGNodes evtl. dynamisch erzeugt oder 
 * manipuliert werden, die dann dem Renderer uebergeben werden koennen.
 * Denkbar sind hier z.b. auch solche sacehn wie by-Reference geometrien 
 * da per defenition die sysnchonisation bei der apllikation liegt.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-07-??, cK, Created.
 *   <li> 2001-07-05, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.2 $ $Date: 2001/07/05 09:37:48 $
 *
 * @author cK, $Author: koestlin $
 */
class ImplicitSGNode : public Node {

public:

  /** Raeumt auf. */
	virtual ~ImplicitSGNode() {
	}
  
	void accept(Visitor* visitor) {
		visitor->visit(this);
	}

  /** Wird vom Renderer aufgerufen.
   *
   * @param renderVisitor Der RenderVisitor.
   */
	virtual void paint(RenderVisitor* renderVisitor) {
	}

};

#endif // _ImplicitSGNode_h_
