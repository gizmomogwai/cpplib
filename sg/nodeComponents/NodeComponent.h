#ifndef _NodeComponent_h_
#define _NodeComponent_h_

#include <string>

#include <sg/SGObject.h>

/** Oberklasse aller Teile eines Nodes.
 *
 * Alles was nicht direkt im Szenegraph haengt und damit kein Node ist ...
 * also z.b. Appearances, Texturen, SGImages, TExGen, Transform3Ds, ...
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-10, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/09/13 13:11:12 $
 *
 * @author cK, $Author: koestlin $
 */
class NodeComponent : public SGObject {
  public:
    std::string toString() {
      return("NodeComponent");
    }

  protected:    
    /** Raeumt auf. */
    virtual ~NodeComponent() {}
      
};

#endif // _NodeComponent_h_
