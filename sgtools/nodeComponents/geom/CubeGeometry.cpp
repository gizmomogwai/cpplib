#include <sgtools/nodeComponents/geom/CubeGeometry.h>

CubeGeometry::CubeGeometry(float size, int maxMultiTextures) 
  : IndexedTriangleArray(TRIS, maxMultiTextures) {

  Array3f* coords = new Array3f(8);
  float size2 = size / 2.0f;
  coords->set(0, -size2, -size2, -size2);
  coords->set(1,  size2, -size2, -size2);
  coords->set(2,  size2, -size2,  size2);
  coords->set(3, -size2, -size2,  size2);

  coords->set(4, -size2,  size2, -size2);
  coords->set(5,  size2,  size2, -size2);
  coords->set(6,  size2,  size2,  size2);
  coords->set(7, -size2,  size2,  size2);
  
  setCoordinates(coords);
  coords->releaseReference();

  Array3f* colors = new Array3f(8);
  colors->set(0, 0, 0, 0);
  colors->set(1, 0, 0, 1);
  colors->set(2, 0, 1, 0);
  colors->set(3, 0, 1, 1);
  colors->set(4, 1, 0, 0);
  colors->set(5, 1, 0, 1);
  colors->set(6, 1, 1, 0);
  colors->set(7, 1, 1, 1);

  setColors(colors);
  colors->releaseReference();

  Array1i* indices = new Array1i(24);
  int i=0;
  indices->set(i++, 0);
  indices->set(i++, 1);
  indices->set(i++, 5);

  indices->set(i++, 0);
  indices->set(i++, 5);
  indices->set(i++, 4);

  indices->set(i++, 1);
  indices->set(i++, 2);
  indices->set(i++, 5);

  indices->set(i++, 2);
  indices->set(i++, 6);
  indices->set(i++, 5);

  indices->set(i++, 2);
  indices->set(i++, 3);
  indices->set(i++, 7);

  indices->set(i++, 7);
  indices->set(i++, 6);
  indices->set(i++, 2);

  indices->set(i++, 3);
  indices->set(i++, 0);
  indices->set(i++, 7);

  indices->set(i++, 0);
  indices->set(i++, 4);
  indices->set(i++, 7);

  setIndices(indices);
  indices->releaseReference();
}

