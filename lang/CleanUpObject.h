#pragma once

/** Templateclasse um Pointer automatisch aufzuraeumen.
 *
 * Aehnlich wie auto_ptr von stl.
 * @include CleanUpObject.example
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-0?-??, cK, Created.
 *   <li> 2001-06-02, cK, Comented.
 * </ul>
 * 
 * @version $Revision: 1.1 $ $Date: 2002/10/28 23:27:35 $
 *
 * @author cK, $Author: gizmo $
 */
template <class T> class CleanUpObject {

 public:
	/** Erzeugt das Aufraeumobject fuer ein gepointertes object.
	 *
	 * @param _toDelete Object, das bereinigt werden soll.
	 */
	CleanUpObject(T* _toDelete) : toDelete(_toDelete) {
	}

	/** Erzeugt uninitialisiertes ClenaUpObject. */
	CleanUpObject() : toDelete(0) {
	}

	/** Raeumt auf .*/
	virtual ~CleanUpObject() {
		if (toDelete != 0) {
			delete toDelete;  
			toDelete = 0;
		}
	}

	/** Setzt das aufzuraeumeende Object.
	 *
	 * @param t Aufzuraeumendes Objekt. */
	void setCleanUp(T* t) {
		toDelete = t;
	}

	T* operator*() const {
    return toDelete;
	}		
	
	T* operator->() const {
		return toDelete;
	}
	
	T* dispose() {
		T* res = toDelete;
		toDelete = 0;
		return res;
	}
    
 private:
	/** Aufzeuraeumendes Object. */
	T* toDelete;    
      
};
