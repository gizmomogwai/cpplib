#ifndef _Leaf_h_
#define _Leaf_h_

#include <pragmaincludes.h>

#include <string>

#include <sg/nodes/Node.h>

#include <sg/visitors/Visitor.h>

/** Oberklasse aller Elemente, die keine Kinder mehr haben.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-27, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cK, $Author: koestlin $
 */
class Leaf : public Node {

  public:
    /** Erzeugt einen neuen Leaf.
     */
    Leaf();
    
    void accept(Visitor* v);

    /** Liefert eine StringRep.
     *
     * @return std::string Stringrep.
     */
    std::string toString();

  protected:
    /** Raeumt auf. */
    virtual ~Leaf();

};

#endif // _Leaf_h_
