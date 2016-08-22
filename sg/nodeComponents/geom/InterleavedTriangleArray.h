#ifndef _InterleavedTriangleArray_h_
#define _InterleavedTriangleArray_h_

#include <util/UpdateObject.h>
#include <sg/data/VertexData.h>
#include <sg/visitors/Visitor.h>
#include <sg/nodeComponents/geom/Geometry.h>
#include <sg/nodeComponents/geom/TriangleArrayType.h>

/** Klasse fuer InterleavedTriangleArrays.
 *
 * Im Unterschied zu normalen TriangleArrays sind hier die Daten ineinander
 * verschraenkt.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2001-0?-??, cK, Created.
 *  <li> 2001-06-02, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.3 $ $Date: 2001/06/05 10:02:41 $
 *
 * @author cK, $Author: koestlin $
 */
class InterleavedTriangleArray : public Geometry {

 public:
	/** Erzeugt ein neues Array von TRIS oder STRIPS oder FANS.
	 *
	 * @param _type Type.
	 * @param _nOfTextures Anzahl von Texturen.
	 */
	InterleavedTriangleArray(const TriangleArrayType _type, int _nOfTextures) 
		: type(_type), nOfTextures(_nOfTextures) {
	}
	
	/** Raeumt auf. */
	virtual ~InterleavedTriangleArray() {
	}
	
	void accept(Visitor* v) {
		v->visit(this);	
	}		

	/** Setzt die VertexDaten.
	 *
	 * @param data VertexDaten.
	 */
	void setVertexData(VertexData* data) {
		vertexData.set(data);	
	}
	
	/** Die Daten. */		
	UpdateObject<VertexData> vertexData;
		
	/** Beschreibung des Datenformats. */
	TriangleArrayType type;

	/** Anzahl von Texturen. */
	int nOfTextures;
	
};

#endif // _InterleavedTriangleArray_h_
