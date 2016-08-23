#ifndef _Iterator_h_
#define _Iterator_h_

/** Templateklasse (interface) fuer Iteratoren.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-24, cK, Created.
 *   <li> 2000-11-25, cK, Commented.
 *   <li> 2001-07-05, cK, ToDos angepasst.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:49 $
 *
 * @author cK, $Author: gizmo $
 */
template <class T>
class Iterator {
 public:
  
  /** Raeumt auf. */
  virtual ~Iterator() {}
  
  /** Testet, ob noch ein Element im Iterator ist.
   *
   * @return bool true falls ein Aufruf von next noch erlaubt ist.
   */
  virtual bool hasNext() = 0;
  
  /** Liefert das naechste Element.
   *
   * Sollte nur aufgerufen werden, wenn ein hasNext() true liefert.
   */
  virtual T next() = 0;
  
};

#endif // _Iterator_h_
