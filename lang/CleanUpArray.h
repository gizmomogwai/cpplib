#pragma once

/** Templateclasse um Array-Pointer automatisch aufzuraeumen.
 *
 * Aehnlich wie auto_ptr von stl.
 * @include CleanUpArray.example
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2003-04-20, cK, Created.
 * </ul>
 */
template <class T> class CleanUpArray {

 public:
	/** Erzeugt das Aufraeumobject fuer ein gepointertes object.
	 *
	 * @param _toDelete Object, das bereinigt werden soll.
	 */
	CleanUpArray(T* _toDelete) : toDelete(_toDelete) {
	}

	/** Erzeugt uninitialisiertes ClenaUpObject. */
	CleanUpArray() : toDelete(0) {
	}

	/** Raeumt auf .*/
	virtual ~CleanUpArray() {
		if (toDelete != 0) {
			delete[] toDelete;
			toDelete = 0;
		}
	}

	/** Setzt das aufzuraeumeende Object.
	 *
	 * @param t Aufzuraeumendes Objekt. */
	void setCleanUp(T* t) {
		toDelete = t;
	}

 private:
	/** Aufzeuraeumendes Object. */
	T* toDelete;
      
};

