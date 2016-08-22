#ifndef _WakeupOnElapsedFrames_h_
#define _WakeupOnElapsedFrames_h_

#include <sg/conditions/WakeupCondition.h>

/** Condition, die alle n-frames true liefert.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-01-16, cKgS, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cKgS, $Author: koestlin $
 */
class WakeupOnElapsedFrames : public WakeupCondition {

  public:
    /** Erzeugt eine Condition, die alle frames - Frames true liefert.
     *
     * @param frames Anzahl von frames nach denen true geliefert 
     *        werden soll.
     */
    WakeupOnElapsedFrames(int frames);


    /** Raeumt auf. */
    virtual ~WakeupOnElapsedFrames() {}


    bool evaluate();


  private:
    /** Alle n Frames wird true geliefert. */
    int n;

    /** soviele frames sind bis zum naechsten true noch abzuwarten. */
    int current;

};

#endif // _WakeupOnElapsedFrame_h_
