#ifndef _Array2D_h_
#define _Array2D_h_

#include <pragmaincludes.h>

/** Templateklasse fuer 2-dim arrays.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-01-29, cKgS, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:35 $
 *
 * @author cKgS, $Author: gizmo $
 */
template <class T> class Array2D {

  public:
    /** Erzeugt ein 2-dim array.
     *
     * @param _width gewuenschte Breite.
     * @param _height gewuenschte Hoehe.
     */
    Array2D(int _width, int _height) 
      : width(_width), height(_height), array(0) {

      array = new T[width*height];
    }
    
    /** Raeumt auf. */
    ~Array2D() {

      delete[](array);
    }

    /** Setzt ein Element des 2-dim arrays.
     *
     * @param x X-Index.
     * @param y Y-Index.
     * @param t Neuer wert.
     */
    void set(int x, int y, T t) {
      
      array[y*width + x] = t;
    }

    /** Liefert einen Eintrag des 2-dim. Arrays.
     *
     * @param x X-Index.
     * @param y Y-Index.
     *
     * @return T Element.
     */
    T get(int x, int y) {
    
      return(array[y*width + x]);
    }

    /** Liefert die Anzahl von Spalten.
     *
     * @return int Spalten des 2d-arrays.
     */
    int getWidth() {
      return(width);
    }

    /** Liefert die Anzahl von Reihen.
     *
     * @return int Hoehe des 2d-arrays.
     */
    int getHeight() {
      return(height);
    }

  private:
    /** Das eindim array, auf das abgebildet wird. */
    T* array;

    /** Breite des Arrays. */
    int width;

    /** Hoehe des Arrays. */
    int height;

};

#endif // _Array2D_h_
