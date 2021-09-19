#ifndef _TeapotGeometry_h_
#define _TeapotGeometry_h_

#include <string>

#ifdef OSX
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#include <sg/nodeComponents/geom/Geometry.h>

/** Geometrie, die einfach den std. teapot repraesentiert (in opengl
 * einfach ... ) aber wie geht das mit d3d ... in den demos ist das als
 * fertiges model dabei.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-28, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author $Author: koestlin $
 */
class TeapotGeometry : public Geometry {
 public:

  void accept(Visitor* v);

  std::string toString() {
    return("Teapot");
  }

 protected:
  /** Raeumt auf. */
  virtual ~TeapotGeometry();

};

#endif // _TeapotGeometry_h_
