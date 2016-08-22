#ifndef _Engine_h_
#define _Engine_h_

#include <sg/visitors/Visitor.h>
#include <list>
#include <util/ListIterator.h>
#include <sgtools/EngineCleanUp.h>
#include <sgtools/KeyListener.h>
class Root;

/** Schnittstelle fuer alle Engines. 
 *
 * <p>
 * Curriculum Vitae.
 * <ul>
 *   <li> 2001-04-10, cK, Aus der GLUTEngine herausfaktorisiert.
 *   <li> 2001-04-11, cK, Aufraeumen angepasst ... visitoren werden 
 *        als letzes aufgeraeumt, damit sich z.b. die texturen noch
 *        ordnungsgemaess abmelden koennen.
 * </ul>
 *
 * @@version $Revision: 1.3 $, $Date: 2001/08/06 15:41:29 $
 *
 * @@author cK, $Author: koestlin $
 */
class Engine {

 public:
	/** Initialisiert die Engine. */
	Engine() : root(0) {
	}

	/** Raeumt auf. */
	virtual ~Engine() {
	}

	/** Setzt die aktuelle Groesse des Canvases.
	 *
	 * @@param width Breite des Canvases.
	 * @@param height Hoehe des Canvases.
	 */
	virtual void setSize(int width, int height) = 0;

	/** Raeumt alles auf, was die Engine verwaltet. */
	virtual void quit();
		
	/** Fuegt einen Visitor hinzu.
	 *
	 * @@param v Neuer Visitor, geht in den Besitz der Engine ueber.
	 */
	void addVisitor(Visitor* v) {
		visitors.push_back(v);	
	}


	/** Fuegt einen Keylistener hinzu.
	 *
	 * @@param l Neuer Listener, geht in den Besitz der Engine ueber.
	 */
	virtual void addKeyListener(KeyListener* l) {
		keyListeners.push_back(l);
	}

		
	/** Setzt das zu rendernde.
	 *
	 * @@param _root Geht in den Besitz der Engine ueber.
	 */
	virtual void setRoot(Root* _root);
	
	/** Laesst die Engine loslaufen. */
	virtual void run() = 0;
		
	/** Fuegt ein Aufraeumobjekt hinzu.
	 *
	 * @@param cleanup Aufraeumer.
	 */
	virtual void addEngineCleanUp(EngineCleanUp* cleanup) {
		cleanups.push_back(cleanup);
	}

 protected:
	/** Liste mit visitoren. */
	std::list<Visitor*> visitors;

	/** Liste mit KeyListenern. */
	std::list<KeyListener*> keyListeners;

	/** Liste mit aufraeumern. */
	std::list<EngineCleanUp*> cleanups;

	/** Breite. */
	int width;

	/** Hoehe. */
	int height;

	/** Root. */
	Root* root;

};

#endif // _Engine_h_

