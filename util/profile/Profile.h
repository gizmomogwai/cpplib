#ifndef _Profile_h_
#define _Profile_h_

#include <string>
#include <list>
#include <util/Iterator.h>

class ProfileVisitor;
class Profile;
class ProfileList;
class ProfileIterator;

/** Ein Programmbereich, zwisachen zusammengehoerigen begin und
 * end anweisungen wird Profile genannt. Hier werden alle Infos gespeichert.
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
class Profile {

  public:
    /** Erzeugt ein neues Profile mit einem schluessel.
     *
     * @param parent Optionaler Vater eines Profiles. Kann auch 0 sein.
     * @param key Schluessel, bleibt im Besitz des Callers.
     */
    Profile(Profile* parent, std::string* key);

    /** Raeumt auf. */
    virtual ~Profile();

    /** Akzeptiert einen Visitor.
     *
     * @param visitor Der Visitor.
     */
    virtual void accept(ProfileVisitor* visitor);

    /** Setzt die Startzeit. Keine Echte Zeit, muss evtl. 
     * extern noch umgerechnet werden.
     *
     * @param time Startzeit.
     */
    void setStart(double time);

    /** Setzt die Endzeit. Keine echte Zeit, muss evtl.
     * extern noch umgerechnet werden.
     *
     * @param time Endzeit.
     */
    void setEnd(double time);

    /** Loescht die Total in dem Profile verbrachte Zeit.
     */
    void clearTotal() {
      total = 0;
    }

    /** Liefert die Startzeit. 
     *
     * @return double Startzeit.
     */
    double getStart();

    /** Liefert die Endzeit.
     *
     * @return double Endzeit.
     */
    double getEnd();

    /** Fuegt der gesamtzeit im Profile Zeit hinzu.
     *
     * @param delta Echte Zeit.
     */
    void addToTotal(double delta);

    /** Sucht ein Profile in der Kinderliste.
     *
     * @param key Schluessel des Profiles.
     *
     * @return Profile* Das entsprechende Profile oder 0. 
     *         Bleibt im Besitz des Profiles.
     */
    Profile* getProfile(std::string* key);

    /** Untersucht, ob das Profile zu dem Schluessel passt.
     *
     * @param key Der Schluessel, bleuibt im Besitz des Callers.
     *
     * @return bool true, falls die Schluessel uebereinstimmen.
     */
    bool equals(const std::string* key);

    /** Liefert den Schluessel.
     *
     * @return std::string* Der Schluessel. Bleibt im Besitz des Profiles.
     */
    std::string* getKey() {
      return(&key);
    }

    /** Leifert die Totalzeit im Profile.
     *
     * @return double Zeit.
     */
    double getTotal() {
      return(total);
    }

    /** Fuegt ein Kind hinzu.
     *
     * @param profile Neues Kind, das Kind geht in den Besitz 
     *        des Profiles über und wird von ihm verwaltet.
     */
    void addChild(Profile* profile);

    /** Liefert einen iterator mit allen Kindern.
     *
     * @return Iterator<Profile*>* Neuer Iterator, 
     *     geht in den Besitz des Callers ueber.
     */
    ProfileIterator* iterator();

  private:

    /** Schluessel des Profiles. */
    std::string key;

    /** Totalzeit im Profile. */
    double total;

    /** Startzeit im Profile. */
    double start;

    /** Endzeit im Profile. */
    double end;

    /** Alle Kinder des Profiles. */
    ProfileList* childs;

};

#endif // _ProfileStack_h_
