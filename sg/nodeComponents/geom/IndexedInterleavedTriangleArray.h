#ifndef _IndexedInterleavedTriangleArray_h_
#define _IndexedInterleavedTriangleArray_h_

#include <sg/nodeComponents/geom/InterleavedTriangleArray.h>

#include <sg/data/Array1i.h>

/** Indiziertes InterleavedTriangleArrays.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-0?-??, cK, Created.
 *   <li> 2001-06-02, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.3 $ $Date: 2001/06/05 10:02:41 $
 *
 * @author cK, $Author: koestlin $
 */
class IndexedInterleavedTriangleArray : public InterleavedTriangleArray {
	
public:
	/** Erzeugt das Array
	 *
	 * @param _type Fan Strip oder TRIS.
	 * @param _nOfTextures Anzahl von Texturen.
	 */
	IndexedInterleavedTriangleArray(const TriangleArrayType _type, 
																	int _nOfTextures) 
		: InterleavedTriangleArray(_type, _nOfTextures) {
	}
		
	/** Raeumt auf .*/
	virtual ~IndexedInterleavedTriangleArray() {
	}
		
	void accept(Visitor* v) {
		v->visit(this);	
	}		
	/** Setzt die Indices.
	 *
	 * @param array Indizes.
	 */
	void setIndices(Array1i* array) {
		indices.set(array);
	}
		
	/** Indices. */
	UpdateObject<Array1i> indices;

};

#endif // _IndexedInterleavedTriangleArray_h_
