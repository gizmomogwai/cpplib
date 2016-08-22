#ifndef _ProjectionGroup_h_
#define _ProjectionGroup_h_

#include <sg/nodes/Group.h>

#include <sg/visitors/Visitor.h>

#include <vecmath/Camera.h>
#include <vecmath/ParallelProjection.h>

                             
/** Gruppe mit eigener Projection.
 *
 * Momentan nicht threadsafe.
 *
 * Eine ProjectionGroup sollte direkt unter dem RootKnoten liegen.
 * Entweder Camera oder ParallelProjection sollte gesetzt sein.
 *
 * <p>
 * Curriculum Vitae:
 * <ul> 
 *   <li> 2001-03-02, cKgS, Created.
 *   <li> 2001-04-04, cK, Leere Konstructor und setMethoden.
 * </ul>                           
 *
 * @todo Threadsafeness.
 *
 * @version $Revision: 1.2 $, $Date: 2001/08/06 16:07:05 $
 *
 * @author gScK, $Author: koestlin $  
 */
class ProjectionGroup : public Group {

  public:
    /** Erzeugt eine Gruppe mit perspectivischer Abbildung.
     *
     * @param _camera Cameramodel fuer die Projecgtion,
     *        geht in den Besitz der ProjectionGroup ueber.
     */
    ProjectionGroup(Camera* c) : camera(c), parallel(0) {
    }

    /** Erzeugt eine Gruppe mit isometrischer Abbildung.
     *
     * @param _parallel ParallelProjection. Caller verliert den Besitz.
     */
    ProjectionGroup(ParallelProjection* _parallel) : 
      camera(0), parallel(_parallel) {
    }

    /** Erzeugt eine Gruppe ohne gesetzte Projection.
     * 
     * das muss per setCamera oder setParallel nachgeholt werden.
     */
    ProjectionGroup() : camera(0), parallel(0) {
    }

    void accept(Visitor* v) {
      v->visit(this);
    }

    /** Setzt die Cameraprojection.
     *
     * @param _camera Cameraabbildung. Geht in den Besitz der 
     *        ProjectionGruppe ueber.
     */
    void setCamera(Camera* _camera) {
      if (camera != 0) {
        delete(camera);
      }
      camera = _camera;
    }

    /** Setzt die Parallelprojection. 
     *
     * @param _parallel ParallelProjection. Geht in den Besitz der 
     *        Projectiongruppe ueber.
     */
    void setParallel(ParallelProjection* _parallel) {
      if (parallel != 0) {
        delete(parallel);
      }
      parallel = _parallel;
    }

    /** Cameramodel. nur fuer visitoren public. */
    Camera* camera;

    /** ParallelProjection. */
    ParallelProjection* parallel;

    std::string toString() {
      std::ostringstream out;
      out << "ProjectionGroup[" << getChildCount() << "]" << std::ends;
      std::string res(out.str());
      return(res);
    }


  protected:
    /** Raeumt auf. */
    virtual ~ProjectionGroup() {
      if (camera != 0) {
        delete(camera);
        camera = 0;
      }
      if (parallel != 0) {
        delete(parallel);
        parallel = 0;
      }
    }
  
};
                             
#endif // _ProjectionGroup_h_
