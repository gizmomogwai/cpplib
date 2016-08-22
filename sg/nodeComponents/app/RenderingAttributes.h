#ifndef _RenderingAttributes_h_
#define _RenderingAttributes_h_

#include <sg/nodeComponents/NodeComponent.h>

/** Klasse die RedneringAttribute kapselt.
 *
 * Zu den RenderingAttributen gehoeren momentan:
 * fog, zbuffer
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-02-27, cK, Created.
 *   <li> 2001-05-08, cK, Fog raus.
 *   <li> 2001-07-05, cK, ToDo aktualisiert.
 * </ul>
 *
 * @version $Revision: 1.3 $, $Date: 2001/07/05 13:27:23 $
 *
 * @author cK, $Author: koestlin $
 */
class RenderingAttributes : public NodeComponent {

  public:
    /** Erzeugt default renderingattributes. 
     *
     * zBufferRead == true
     * zBufferWrite == true
     */
    RenderingAttributes() : zBufferRead(true), zBufferWrite(true) {
    }

    /** Erzeugt redneringattribute.
     *
     * @param _zBufferRead an/aus.
     * @param _zBufferWrite an/aus.
     */
    RenderingAttributes(bool _zBufferRead, bool _zBufferWrite) 
      : zBufferRead(_zBufferRead), zBufferWrite(_zBufferWrite) {
    }

    /** Raeumt auf. */
    virtual ~RenderingAttributes() {
    }

    /** Ist zbufferanfrage aktiviert. */
    bool zBufferRead;

    /** Ist zbufferschrieben beim rendern aktiviert. */
    bool zBufferWrite;
 
};

#endif // _RenderingAttributes_h_
