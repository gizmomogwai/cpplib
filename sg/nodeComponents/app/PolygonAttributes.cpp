#include <sg/nodeComponents/app/PolygonAttributes.h>

const int PolygonAttributes::POLYGON_FILL = 1;
const int PolygonAttributes::POLYGON_LINE = 2;
const int PolygonAttributes::POLYGON_POINT = 4;

PolygonAttributes::PolygonAttributes(int _polyMode) throw (Exception) {
  if ((_polyMode == PolygonAttributes::POLYGON_FILL) ||
      (_polyMode == PolygonAttributes::POLYGON_LINE) ||
      (_polyMode == PolygonAttributes::POLYGON_POINT)) {
    polyMode = _polyMode;
  } else {
    throw(Exception("PolygonAttributes::PolygonAttributes - illegal type", __FILE__, __LINE__));
  }
}
