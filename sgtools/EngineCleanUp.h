#ifndef _EngineCleanUp_h_
#define _EngineCleanUp_h_

#include <list>

#include <util/ListIterator.h>

#include <sg/nodes/SGObserver.h>
#include <sg/nodes/Node.h>
#include <sg/visitors/Visitor.h>

/** Schnittstelle um Objecte aufzuraeumen, wenn die Engine beendet wird.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-10, cK, Aus dem Cleanup von Wavestream herausgezogen.
 * </ul>
 *
 * @@version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:37 $
 *
 * @@author cK, $Author: koestlin $
 */
class EngineCleanUp {

  public:
    /** Die Aufraeumarbeit sollte hier getan werden.
     */
    virtual ~EngineCleanUp() {
    }
};

#endif // _EngineCleanUp_h_

