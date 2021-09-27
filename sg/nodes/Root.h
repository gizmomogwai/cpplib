#pragma once

#include <string>

#include <sg/nodes/Group.h>

#include <sg/visitors/Visitor.h>

/** Rootcomponente des Szenegraphen.
 *
 * Vielleicht sollte man dazu auch lieber canvas3d sagen, denn
 * die Rootcomponente weiss, wie  gross der zu  zeichnende
 * bereich sein soll.
 * Der Knoten muss von aussen immer mit den aktuellen
 * fenstergeometrien gefuettert werden.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-03-20, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cK, $Author: koestlin $
 */
class Root : public Group {

  public:
    /** Erzeugt einen neuen Rootknoten.
     */
    Root() : imageWidth(0), imageHeight(0) {
    }

    void accept(Visitor* v) {
      v->visit(this);
    }

    std::string toString() {
      return("RootGroup");
    }

    /** Breite des zu zeichnenden Bildes. */
    int imageWidth;

    /** Hoehe des zu ziechnenden Bildes. */
    int imageHeight;

  protected:
    /** Raeumt auf. */
    virtual ~Root() {
      std::cout << "Root" << std::endl;
    }

};
