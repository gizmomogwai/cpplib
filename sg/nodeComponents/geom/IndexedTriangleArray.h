#ifndef _IndexedTriangleArray_h_
#define _IndexedTriangleArray_h_

#ifdef WIN32
  #pragma warning(disable:4786)
#endif // WIN32

#include <sg/data/Array1i.h>
#include <sg/nodeComponents/geom/TriangleArray.h>
#include <util/UpdateObject.h>

/** Indexed Triangle Array.
 *
 * Analog zu einem normalen TriangleArray.
 *
 * Nur wird hier zusaetzlich die Reihenfolge der Punkte durch das Indexfeld
 * veraendert, das angibt, in welcher Reihenfolge das TriangleArray
 * abgearbeitet werden soll. 
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-29, cK, Created.
 *   <li> 2001-01-04, cK, Auf Multitex angepasst.
 * </ul>
 *
 * @todo int Indices sind doof!
 *
 * @version $Revision: 1.2 $, $Date: 2001/05/14 12:08:30 $
 *
 * @author cK, $Author: koestlin $
 */
class IndexedTriangleArray : public TriangleArray {

  public:
    /** Erzeugt ein neues TriangleArray gegebenen typs.
     *
     * @param _type Type (siehe TriangleArray).
     * @param _maxMultiTextures (siehe TriangleArray).
     */
    IndexedTriangleArray(const TriangleArrayType type, int _maxMultiTextures);

    void accept(Visitor* v) {
      v->visit(this);
    }
    
    /** Setzt die Indices.
     *
		 * SG-maessiges setzen.
		 *
     * @param _indices Indexe.
     */
    void setIndices(Array1i* _indices);

    /** Die Indices. */
    UpdateObject<Array1i>* indices;

  protected:
    /** Raeumt auf. */
    virtual ~IndexedTriangleArray();

};

#endif // _IndexedTriangleArray_h_
