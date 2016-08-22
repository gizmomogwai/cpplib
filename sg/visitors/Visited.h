#ifndef _Visited_h_
#define _Visited_h_
             
#include <sg/visitors/Visitor.h>

/** Oberklasse fuer alle Objekte, die von Visitoren besucht werden
 * koennen. 
 *
 * DoubleDispatchmechanismus, sonst, kann nicht in die richtige Methode
 * gesprungen werden.
 *
 * <p>
 * Curriculum Vitae:
 * <ul> 
 *   <li> 2000-12-07, cK, Created.
 * </ul>
 */         
class Visited {

  public:
    /** Damit der deconstructor ueberschrieben werden kann. */
    virtual ~Visited() {}                          
       
    /** Ein Visitor moechte ein Objekt besuchen. 
		 *
		 * @param v Visitor, der das Object besuchen will.
		 */
    virtual void accept(Visitor* v) = 0;   
  
};

#endif // _Visited_h_
