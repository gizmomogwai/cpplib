#ifndef _Group_h_
#define _Group_h_

#include <string>
#include <list>

#include <util/ListIterator.h>
#include <util/ReleaseRefCountedObject.h>

#include <util/UpdateObject.h>
#include <util/Iterator.h>

#include <sg/nodes/Node.h>
#include <sg/visitors/Visitor.h>

class BranchGroup;

#include <sstream>

/** stl-liste, die gleichzeitig ReferenceCounted ist.
 *
 * Damit einem Iterator nicht einfach die NodeListe entzogen werden kann.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-12, cK, Created.
 *   <li> 2001-03-08, cK, Destructor veraendert.
 *   <li> 2001-05-29, cK, Kommentare erweitert.
 * </ul>
 *
 * @version $Revision: 1.3 $, $Date: 2001/08/06 15:53:24 $
 *
 * @author cK, $Author: koestlin $
 */
class NodeList : public std::list<Node*>, public RefCountedObject {
  public:
    /** Replace, dass das refcounting beruecksichtigt.
     *
     * @param idx Index der ersetz werden soll.
     * @param n Neuer Knoten fuer den Index.
     */
    void replace(unsigned int idx, Node* n) {
      if (idx >= size()) {
        std::ostringstream error;
        error << "NodeList::replace - illegal index (" << idx << " with size " << size() << ")" << std::ends;
        throw Exception(error.str(), __FILE__, __LINE__);
      }

      std::list<Node*>::iterator i = begin();

      for (unsigned int count=0; count<idx; count++) {
        i++;
      }

      (*i)->setParent(0);
      (*i)->releaseReference();
      n->addReference();

      insert(i, n);
      erase(i);
    }

  protected:
    /** Zaehlt bei allen Nodes in der Liste den Referencecounter runter. */
    virtual ~NodeList() {
      std::cout << "~NodeList" << std::endl;

      std::list<Node*>::iterator i = begin();
      while (i != end()) {
        Node* help = *i++;
        help->releaseReference();
        remove(help);
      }
    }
};

/** Hilfsklasse um ueber eine NodeList zu iterieren (und am ende die
 * referenz herunterzuzaehlen).
 *
 * Das ist noetig, weil man irgendwannmal die NodeList per get von einem
 * UpdateObject holt (hauptsaechlich die Visitoren gehen ueber
 * alle Kinder einer Gruppe).
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-12, cK, Craeted.
 *   <li> 2001-03-08, cK, ReleaseRefCountedObject eingebaut...
 *   <li> 2001-03-08, cK, Vermutung Release... geht nicht ...
 * </ul>
 *
 * @version $Revision: 1.3 $, $Date: 2001/08/06 15:53:24 $
 *
 * @author cK, $Author: koestlin $
 */
class NodeListIterator : public Iterator<Node*> {
  public:
    /** Erzeugt einen neuen Iterator.
     *
     * @param _list Liste, ueber die iteriert werden soll.
     */
    NodeListIterator(NodeList* _list) {
      list = _list;
      if (list != nullptr) {
        i = list->begin();
      }
    }

    /** Raeumt auf (zaehlt reference herunter. */
    virtual ~NodeListIterator() {
      if (list != nullptr) {
        list->releaseReference();
        list = nullptr;
      }
    }

    bool hasNext() {
      if (list == nullptr) {
        return false;
      } else {
        return i != list->end();
      }
    }

    Node* next() {
      return *i++;
    }

  private:
    /** Liste. */
    NodeList* list;

    /** stl-Iteartor. */
    NodeList::iterator i;

};


/** Scenengraphobjekt, das mehrere Kinder halten kann.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2000-11-24, cK, Created.
 *  <li> 2000-11-25, cK, Commented.
 *  <li> 2001-03-08, cK, Ohne retained objecte ...
 * </ul>
 *
 * @author cK, $Author: koestlin $
 *
 * @version $Revision: 1.3 $, $Date: 2001/08/06 15:53:24 $
 */
class Group : public Node {
  public:
    /** Erzeugt ein neues Objekt.
     */
    Group(const std::string& name="");

    void accept(Visitor* v);

    /** Fuegt ein Kind hinzu.
     *
     * gleiche Philosophie wie bei setMethoden.
     *
     * @param n Neues Kind.
     */
    virtual void addChild(Node* n);
    virtual void addChildInFront(Node* newOne);

    /** Fuegt einen Knoten an ein Stelle hinzu.
     *
     * @param n Node
     * @param idx Index an den der Knoten gesetzt werden soll.
     */
    virtual void setChild(Node* n, int idx);

    /** Entfernt ein Kind aus dem Szenegraphen.
     *
     * @param n Node, der entfernt werden soll.
     */
    virtual void removeChild(Node* n);

    /** Liefert einen Iterator ueber alle Kinder.
     *
     * Der Iterator muss per delete zerstoehrt werden.
   *
     * @return NodeListIterator* Iterator ueber die Kinder.
     */
    virtual NodeListIterator* getChilds();

  /**
   * Liefert die aktuelle childlist. bitte releaseReference.
   */
  virtual NodeList* getChildsAsList() {
    return childs->get();
  }

    /** Liefert die Anzahl der Kinder.
     *
     * @return int Anzahl.
     */
    virtual int getChildCount();

    /** Liefert eine Stringrep.
     *
     * @return std::string Stringrep.
     */
    std::string toString();

    /** Liste mit Kindern. */
    UpdateObject<NodeList>* childs;

  protected:
    /** Raeumt auf. */
    virtual ~Group();

  private:
    /** Fall noch keine neue Liste vorhanden ist, wird die
     * aktuelle liste kopiert und als Childliste angemeldet. Falls
     * die neue Liste schon vorhanden ist wird nichts gemacht.
     *
     * @param oldOne Liste mit aktuellen Kindern.
     * @param newOne Liste mit Kindern fuer das naechste update.
     *
     * @return NodeList* Neue Liste mit Kindern.
     */
    NodeList* copyAndSet(NodeList* oldOne, NodeList* newOne);

    /** Loescht die Elterneintrage alle Nodes in einer Liste.
     *
     * @param list NodeList, die am ende per releaseReference aufgeraeumt wird.
     */
    void clearParents(NodeList* list);
    const std::string name;
};

#endif // _Group_h_
