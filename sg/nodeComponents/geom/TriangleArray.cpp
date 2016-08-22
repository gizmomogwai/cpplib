#include <sg/nodeComponents/geom/TriangleArray.h>

#include <sstream>

TriangleArray::TriangleArray(const TriangleArrayType _type, int _maxMultiTextures) : 
  type(_type), coords(0), colors(0), textureCoords(0), normals(0), 
  stripVertexCounts(0), maxMultiTextures(_maxMultiTextures) {

/*
  coords = new UpdateObject<Array3f>();
  colors = new UpdateObject<Array3f>();
  textureCoordinates = new UpdateObject<Array2f>();
  normals = new UpdateObject<Array3f>();
  */
}

TriangleArray::~TriangleArray() {
  if (coords != 0) {
    delete(coords);
    coords = 0;
  }
  if (colors != 0) {
    delete(colors);
    colors = 0;
  }
  if (textureCoords != 0) {
    int max = getMaxMultiTextures();
    for (int i=0; i<max; i++) {
      if (textureCoords[i] != 0) {
        delete(textureCoords[i]);
      }
    }
    delete[](textureCoords);
    textureCoords = 0;
  }
  if (normals != 0) {
    delete(normals);
    normals = 0;
  }
  if (stripVertexCounts != 0) {
    delete(stripVertexCounts);
    stripVertexCounts = 0;
  }
}

void TriangleArray::setCoordinates(Array3f* _coords) {
  if (coords == 0) {
    coords = new UpdateObject<Array3f>();
  }
  coords->set(_coords);
}

void TriangleArray::setColors(Array3f* _colors) {
  if (colors == 0) {
    colors = new UpdateObject<Array3f>();
  }
  colors->set(_colors);
}

void TriangleArray::assertMaxMultiTextures(int _texNr) {
  if ((_texNr < 0) || (_texNr > getMaxMultiTextures())) {
    std::ostringstream h;
    h << "TriangleArray::assertMaxMultiTextures(" << _texNr 
      << ") - _texNr out of range" << std::ends;
    Exception e(h.str());
    throw(e);
  }
}

void TriangleArray::setTextureCoordinates(Array2f* _textureCoords, int _texNr) {
  if (textureCoords == 0) {
    textureCoords = new UpdateObject<Array2f>*[getMaxMultiTextures()];
    for (int i=0; i<getMaxMultiTextures(); i++){
      textureCoords[i] = 0;
    }
    assertMaxMultiTextures(_texNr);
    if (textureCoords[_texNr] == 0) {
      textureCoords[_texNr] = new UpdateObject<Array2f>();
    }
  }
  textureCoords[_texNr]->set(_textureCoords);
}

void TriangleArray::setNormals(Array3f* _normals) {
  if (normals == 0) {
    normals = new UpdateObject<Array3f>();
  }
  normals->set(_normals);
}

void TriangleArray::setStripVertexCounts(Array1i* _stripVertexCounts) {
  if (stripVertexCounts == 0) {
    stripVertexCounts = new UpdateObject<Array1i>();
  }
  stripVertexCounts->set(_stripVertexCounts);
}
