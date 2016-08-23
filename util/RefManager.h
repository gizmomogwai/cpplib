#ifndef _RefManager_h_
#define _RefManager_h_

class RefCountedObject;

#include <iostream>
#include <sstream>
#include <string>
#include <map>

/** Verwaltet alle RefCountedObjects (zumindest falls _DEBUG gesetzt ist).
 *
 * Singleton.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-11, cK, Created.
 * </ul>
 *
 * @todo Ist das so mit der Hashtabelle sinnvoll???
 * @todo make_pair bracuht einen copy-operator ... uebernimmt seine daten 
 *    also per value d.h. objecte nur per cast da rein, damit eine zahl 
 *    an den start geht (pointer)????
 * @todo Synchronisieren!
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:49 $
 *
 * @author cK, $Author: gizmo $
 */
class RefManager {

 public:
    
	/** Raeumt das Singleton auf. */
	static void cleanUp() {
		if (instance != 0) {
			delete(instance);
			instance = 0;
		}
	}

	/** Liefert die Instanz des RefManagers.
	 *
	 * @return RefManager Der Manager.
	 */
	static RefManager* getInstance() {
		if (instance == 0) {
			instance = new RefManager();
		}
		return(instance);
	}

	/** Fuegt ein RefCountedObject hinzu.
	 *
	 * Wird aufgerufen, wenn ein solches Object erzeugt wird.
	 *
	 * @param o Object.
	 */
	void add(RefCountedObject* o) {
		refObjects->insert(std::make_pair(((unsigned long)o), o));
	}

	/** Entfernt ein RefCountedObject ...
	 *
	 * Wird normalerweise aufgerufen, wenn der desctructor aufgerufen wird.
	 *
	 * @param o Object.
	 */
	void remove(RefCountedObject* o) {
		refObjects->erase((unsigned long)o);
	}

	/** Erzeugt eine Stringrepraesentation. 
	 *
	 * @return std::string Stringrep.
	 */
	std::string toString() {
		std::ostringstream help;
		help << "RefManager [" << refObjects->size() << std::endl;
		std::map<unsigned long, 
			RefCountedObject*>::iterator i = refObjects->begin();
		while (i != refObjects->end()) {
			//        help << *i << std::endl;
			i++;
		}
		help << std::endl << std::ends;
		std::string res(help.str());
		return(res);
	}

 private:
	/** Singleton instance. */
	static RefManager* instance;

	/** Erzeugt den Manager. */
	RefManager() {
		refObjects = new std::map<unsigned long, RefCountedObject*>();
	}

	/** Raeumt auf. */
	~RefManager() {
		std::cout << "RefManager::~RefManager" << std::endl;
		delete(refObjects);
	}

	/** Hashtabelle von Adresse des RefCountedObjects auf das Object ???? 
	 * Ist das sinnvoll. 
	 */
	std::map<unsigned long, RefCountedObject*>* refObjects;
  
};

#endif // _RefManager_h_
