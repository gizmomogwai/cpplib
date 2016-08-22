#ifndef _PrintProfileVisitor_h_
#define _PrintProfileVisitor_h_

#include <util/UtilApi.h>

#include <util/profile/ProfileVisitor.h>
#include <sstream>

/** Gibt die Daten eines Profilers auf std-out aus.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-09-06, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2002/10/28 23:39:50 $
 *
 * @author cK $Author: gizmo $
 */
class UTIL_API PrintProfileVisitor : public ProfileVisitor {

  public:

    /** Erzeugt einen neuen Visitor.
     */
    PrintProfileVisitor() : offset(0), out(new std::ostringstream()), currentRoot(0), parent(0) {
    }

    /** Raeumt auf. */
	  virtual ~PrintProfileVisitor() {
      delete(out);
	  }

	  void visit(Profile* profile);
    void visit(Profiler* profiler);

    /** Liefert eine Stringrepraesentation des abgegangenn Profilers.
     *
     * @return std::string Stringrep.
     */
    std::string toString() {
      *(out) << std::ends;
      std::string res(out->str());
      return(res);
    }

  private:
    /** Einzug. */
    int offset;

    /** Stream, an den die Ausgabe gepuffert wird. */
    std::ostringstream* out;

    /** Root, das momentan verarbeitet wird, ein Profile kann mehrere Roots
		 * haben. 
		 */ 
    Profile* currentRoot;

    /** Aktueller Parent. */
    Profile* parent;

    /** Druckt eine Zeile in die Ausgabe.
     *
     * @param profileName Name des profiles.
     * @param profileTotal Totalzeit des Profiles.
     * @param root Aktueller Root.
     * @param parent Direkter Vater.
     */
    void print(std::string profileName, 
               double profileTotal, 
               Profile* root, 
               Profile* parent);

    /** Druckt eine gewisse anzahl von spaces (von offset abhaengig) in die
		 * Ausgabe.
     */
    void printSpaces();

};

#endif // _PrintProfileVisitor_h_
