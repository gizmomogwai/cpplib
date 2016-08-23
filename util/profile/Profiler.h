#ifndef _Profiler_h_
#define _Profiler_h_

#include <lang/HPStopWatch.h>
#include <list>
#include <lang/Exception.h>
#include <util/profile/ProfileStack.h>
#include <util/Iterator.h>
#include <util/ListIterator.h>
#include <util/profile/Profile.h>
#include <util/profile/ProfileList.h>

/** Klasse mit dem Programme untersucht werden können.
 * Grundidee ist, dass man bereiche immer mit begin und end 
 * markiert, und dass zwiscchen diesen Punkten die zeit genommen wird.
 * Diese Punkte koennen auch geschachtelt werden, so dass sich ein 
 * call-baum ergibt...
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-09-05, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2002/10/28 23:39:50 $
 *
 * @author cK $Author: gizmo $
 */
class Profiler {

  public:

    /** Liefert die Instanz des Profilers. 
     *
     * @return Profiler* Die Profilerinstanz. 
     *         Geht nicht in den Besitz des Callers ueber.
     */
    static Profiler* getInstance() {
      return(&theProfiler);
    }

    /** Ein Bereich wird betreten.
     *
     * @param key Schluessel des Bereichs.
     */
    void begin(std::string& key);

    /** Ein Bereich wird verlassen.
     *
     * @param key Schluessel des Bereichs.
     *
     * @throws Exception falls der Schluessel nicht mit dem 
     *    aktuellen Bereich uebereinstimmt.
     */
    void end(std::string& key) throw (Exception);

		/** Sucht ein Root-profile. 
		 *
		 * @param key Der name des gesuchten Profiles.
		 */
  Profile* searchRootProfile(std::string* key);

	/** Liefert eine Stringrep. 
	 *
	 * @return std::string String.
	 */
  std::string toString();

	/** Setzt die Zeit in allen Profilen auf 0. */
  void clear();

	/** Visitorunterstuetzung.
	 *
	 * @param visitor ProfileVisitor.
	 */
  void accept(ProfileVisitor* visitor);

	/** Liefert einen ProfileIterator, ueber die Root-Profiles.
	 *
	 * @return ProfileIterator* Muss vom Caller freigegeben werden.
	 */
  ProfileIterator* iterator() {
    return(roots.iterator());
  }
	
	/** Raeumt auf. */
  virtual ~Profiler();
protected:
	/** Erzeugt einen neuen Profiler. */
  Profiler() {
  }

	/** Wendet einen Visitor auf alle Childs an. 
	 *
	 * @param visitor Der Visitor. Bleibt im besitz des Callers.
	 */
  void applyVisitor2Childs(ProfileVisitor* visitor);


  /** Liste mit allen Profilen auf Root. Die Profile werden von 
   * dieser Liste auch verwaltet.
   */
  ProfileList roots;

	/** Statische Profilerinstanz. */
  static Profiler theProfiler;

	/** Aktueller Callstack. */
  ProfileStack profiles;

	/** Stoppuhr. */
  HPStopWatch stopper;

};


#endif // _Profiler_h_
