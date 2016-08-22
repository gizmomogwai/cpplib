#ifndef _VertexData_h_
#define _VertexData_h_

#include <lang/Exception.h>
#include <sg/nodeComponents/NodeComponent.h>

/** Vertexdatenm fuer interleavedTriangleArrays. 
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-0?-??, cK, Created.
 *   <li> 2001-06-02, cK, COmmented.
 * </ul>
 *
 * @version $Revision: 1.4 $ $Date: 2001/08/06 16:09:14 $
 *
 * @author cK, $Author: koestlin $
 */
class VertexData : public NodeComponent {
 public:
	
	/** Konstante falls Vertexdaten Koordinaten enthalten. */
	const static int COORDS;

	/** Konstante falls Vertexdaten Normalen enthalten. */
	const static int NORMALS;

	/** Konstante falls Vertexdaten Texturkoordinaten enthalten. */
	const static int TEXCOORDS;
		
	/** Erzeugt VertexData.
	 *
	 * @param _type coords muessen immer angegeben werden, normalen und
	 *	 texcoords sind optional. 
	 * @param _nOfVertices Anzahl von Punkten.
	 */
	VertexData(int _type, int _nOfVertices) : 
	    type(_type), nOfVertices(_nOfVertices) {
	    
	    tupelSize = 3;
	    coordOffset = 0;
	    if (containsCoordData() == false) {
		throw(Exception("VertexData::VertexData - Coordinaten muessen angegeben werden.", 
          __FILE__, __LINE__));
	    }
		if (containsTexCoordData() == true) {
			texCoordOffset = tupelSize;
			tupelSize += 2;
		}
		if (containsNormalData() == true) {
			normalOffset = tupelSize;
			tupelSize += 3;		
		}
		data = new float[nOfVertices*tupelSize];
	}

	/** Testet ob Coordinatendaten angegeben sind.
	 *
	 * @return bool true falls Coordinaten angegeben sind.
	 */		
	bool containsCoordData() {
		return((type & COORDS) != 0);
	}
	/** Testet ob Normalen angegeben sind.
	 *
	 * @return bool true falls Normalen gegeben sind.
	 */
	bool containsNormalData() {
		return((type & NORMALS) != 0);
	}
	/** Testet ob Texturkoordinaten angegeben sind.
	 *
	 * @return bool true falls Texturkoordinaten angegeben sind.
	 */
	bool containsTexCoordData() {
		return((type & TEXCOORDS) != 0);
	}		

	/** Setzt eine Coorkdinate.
	 *
	 * @param idx Index der Koordinaten.
	 * @param x X-Komponente.
	 * @param y Y-Komponente.
	 * @param Z Z-Komponente.
	 */
	void setCoord(int idx, float x, float y, float z) {
		float* help = data + idx * tupelSize + coordOffset;
		help[0] = x;
		help[1] = y;
		help[2] = z;
	}
	/** Setzt eine Texturkoordinate.
	 *
	 * @param idx Index der Texturkoordinate.
	 * @param u U-Komponente.
	 * @param v V-Komponente.
	 */
	void setTexCoord(int idx, float u, float v) {
		float* help = data + idx * tupelSize + texCoordOffset;
		help[0] = u;
		help[1] = v;
	}
	/** Setzt eine normale.
	 *
	 * @param idx Index der Normalen.
	 * @param nx X-Komponente des Vectors.
	 * @param ny Y-Komponente des Vectors.
	 * @param nz Z-Komponente des Vectors.
	 */
	void setNormal(int idx, float nx, float ny, float nz) {
		float* help = data + idx * tupelSize + normalOffset;	
		help[0] = nx;
		help[1] = ny;
		help[2] = nz;
	}
	/** Liefert die Koordinaten eines Indexes.
	 *
	 * @param idx Index der gewuenschten Koordinaten.
	 *
	 * @return float* Floatdaten.
	 */
	float* getCoord(int idx) {
		return(data + idx * tupelSize + coordOffset);	
	}
		
	/** Liefert die Normalen eines Indexes.
	 *
	 * @param idx Index der gewuenschten Koordinaten.
	 *
	 * @return float* Floatdaten.
	 */
	float* getNormal(int idx) {
		return(data + idx * tupelSize + normalOffset);	
	}
		
	/** Liefert die Texturkoordinaten eines Indexes.
	 *
	 * @param idx Index der gewuenschten Koordinaten.
	 *
	 * @return float* Floatdaten.
	 */
	float* getTexCoord(int idx) {
		return(data + idx * tupelSize + texCoordOffset);	
	}

	/** Alle Daten. */
	float* data;

	/** Liefert die Anzahl von Vertices.
	 *
	 * @return int Anzahl von Punkttupeln.
	 */
	int getSize() {
		return(nOfVertices);
	}
    
	/** Liefert die groesse eines Datensatzes.
	 *
	 * @return int Groesse einer Vertex.
	 */
	int getTupelSize() {
		return(tupelSize);
	}
		
 protected:
	/** Raeumt auf. */
	virtual ~VertexData() {
		delete[](data);	
	}
	
 private:
	/** Type der Daten. */
	int type;

	/** Anzahl von Vertices. */
	int nOfVertices;		
	/** Groesse eines Tupels. */
	unsigned char tupelSize;

	/** Offset zu den Coordinaten. */
	unsigned char coordOffset;

	/** Offset zu den Normalen. */
	unsigned char normalOffset;

	/** Offset zu den Texturkoordinaten. */
	unsigned char texCoordOffset;
		
};

#endif // _VertexData_h_
