#ifndef _TemplateTupelArray_h_
#define _TemplateTupelArray_h_

#include <lang/Exception.h>

#include <sg/nodeComponents/NodeComponent.h>

/** Oberklasse von Tupelarrays.
 *
 * Intern wird ein Array der groesse _size * _tupelSize von Ts angelegt.
 * _size gibt an, wieviele tupel gespeichert werden sollen, _tupelSize,
 * wieviele elemente ein tupel hat.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-12, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/08/06 16:09:14 $
 *
 * @author cK, $Author: koestlin $
 */
template <class T> class TemplateTupelArray : public NodeComponent {
 public:
	/** Erzeugt ein neues Array von Ts.
	 *
	 * @param _size Anzahl von Tupel.
	 * @param _tupelSize Anzahl von Ts pro Tupel.
	 */
   TemplateTupelArray(int _size, int _tupelSize)
     : maxIdx(_size*_tupelSize),
       data(new T[maxIdx]),
       tupelSize(_tupelSize),
       size(_size) {
	}

  /** Alternativer Konstructor, der ein von jemandem anderen Initialisiertes array
   * verarbeitet.
   *
   * @param _size Anzahl von Tupel.
   * @param _tupelSize Anzahl von Ts pro Tupel.
   * @param _data Die eignetlichen Daten.
   */
  TemplateTupelArray(int _size, int _tupelSize, T* _data)
    : maxIdx(_size*_tupelSize), data(_data), tupelSize(_tupelSize), size(_size)  {
  }

	/** Liefert die Anzahl von Tupel
	 *
	 * @return int Tupelanzahl.
	 */
	int getSize() {
		return(size);
	}

	/** Liefert die Adresse des iten Tupels.
	 *
	 * @param idx Index des Tupels.
	 *
	 * @return float* Adresse des Tupels.
	 */
	T* get(int idx) {
		return(&(data[idx * tupelSize]));
	}

	/** Setzt einen Index direkt.
	 *
	 * @param idx Index.
	 * @param v Wert.
	 */
	void set(int idx, T v) {
		if ((idx < maxIdx) && (idx >= 0)) {
			data[idx] = v;
		} else {
			throw(Exception("Arrayf::set - out Of Bounds", __FILE__, __LINE__));
		}
	}

 protected:
	/** Raeumt auf. */
	virtual ~TemplateTupelArray() {
		delete[](data);
	}


 private:
	/** Maximalindex ins array. */
	int maxIdx;

	/** Daten. */
	T* data;

	/** Anzahl von floats pro tupel. */
	int tupelSize;

	/** Anzahl von Tupeln. */
	int size;

};

#endif // _TemplateArray_h_
