#include <sg/nodeComponents/geom/IndexedTriangleArray.h>

IndexedTriangleArray::IndexedTriangleArray(const TriangleArrayType _type, 
                                           int _maxMultiTextures) : 
  TriangleArray(_type, _maxMultiTextures), indices(0) {

}

IndexedTriangleArray::~IndexedTriangleArray() {
  if (indices != 0) {
    delete(indices);
    indices = 0;
  }
}

void IndexedTriangleArray::setIndices(Array1i* _indices) {
  if (indices == 0) {
    indices = new UpdateObject<Array1i>();
  }
  indices->set(_indices);
}


