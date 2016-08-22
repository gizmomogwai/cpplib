#ifndef ListIterator_h_
#define ListIterator_h_

#include <pragmaincludes.h>

#include <util/UtilApi.h>

#include <lang/Exception.h>
#include <util/Iterator.h>

#include <list>
#include <vector>

using namespace std;

/** Iterator fuer stl-listen.
 *
 * Das Problem mit den Iteratoren der stl ist, dass zum iterieren sowohl
 * den iterator als auch das zu iterierende Objekt kennen muss:
 * 
 * <ul>
 *   <li> list<int> l;
 *   <li> list<int>::iterator i = l->begin();
 *   <li> while (i != l->end()) {
 *   <ul>
 *     <li> int help = *i;
 *     <li> i++;
 *   </ul>
 *   <li>}
 * </ul>
 * Damit wird es unmoeglich, nur einen Iterator zu liefern.
 *
 * Implementierung ist wegen vc6 im header.
 *
 * std::vector, std::list haben keine gemeinsame oberklasse, deswegen muss
 * man fuer verschiedene container den iterator komplett copy&pasten.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-24, cK, Created.
 *   <li> 2000-11-25, cK, Commented.
 *   <li> 2001-07-05, cK, ToDos oben als verlautbarung/begruendung 
 *        untergebracht.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:49 $
 *
 * @author cK, $Author: gizmo $
 */
template <class T, class CT> 
class UTIL_API StlIterator : public Iterator<T> {

 public:
	/** Erzeugt einen neuen Iterator aus einer stl-liste.
	 *
	 * @param container stl-Liste.
	 */
	StlIterator(CT* container) {
    if (container == 0) {
      throw Exception("cannot iterate over 0");
    }
		fContainer = container;
    
  	i = fContainer->begin();
	}

  /** Raeumt auf. */
  virtual ~StlIterator() {
  }

	/** Testet, ob noch mehr Elemente vorhanden sind.
	 *
	 * @return bool true falls noch mehr Elemente vorhanden sind.
	 */
	virtual bool hasNext() {
		return i != fContainer->end();
	}

	/** Liefert das naechste Element.
	 *
	 * @return T Naechstes Element.
	 */
	virtual T next() {
		return *i++;
	}

 protected:
	/** zugrundeliegende stl-Liste. */
	CT* fContainer;

	/** zugrundeliegender stl-iterator. */
	typename CT::iterator i;
	
};


template <class T> class UTIL_API ListIterator : public StlIterator<T, std::list<T> > {
  public:
    ListIterator(std::list<T>* container) : StlIterator<T, std::list<T> >(container) {}
};

template <class T> class UTIL_API VectorIterator : public StlIterator<T, std::vector<T> > {
  public:
    VectorIterator(std::vector<T>* container) : StlIterator<T, std::vector<T> >(container) {}  
};

#endif // ListIterator_h_

