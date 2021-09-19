#ifndef _Color3f_h_
#define _Color3f_h_

#include <string>
#include <sstream>

/** Farbklasse.
 *
 * <p>
 * Curriculum Vitae.
 * <ul>
 *   <li> 2000-??-??, cK, Created.
 *   <li> 2001-04-05, cK, toString und Kommentare.
 *   <li> 2001-05-25, cK, In das Paket vecmath verschoben (nicht mehr
 *        refcounted).
 *   <li> 2001-05-26, cK, Leerer Konstruktor hinzugefuegt, Copy Konstructor.
 * </ul>
 *
 * @version $Revision: 1.3 $ $Date: 2001/07/16 10:02:39 $
 *
 * @author cK, $Author: koestlin $
 */
class Color3f {

  public:

    /** Erzeugt eine neue Farbe.
     *
     * @param r von 0 bis 1
     * @param g von 0 bis 1
     * @param b von 0 bis 1
     */
    Color3f(float r, float g, float b) {
      set(r, g, b);
    }

    /** CopyConstrucotr.
     *
     * @param c Farbe, die repliziert werden soll.
     */
    Color3f(Color3f* c) {
      set(c->rgb[0], c->rgb[1], c->rgb[2]);
    }

    /** Uninitislisierte Farbe. */
    Color3f() {
    }


    static Color3f* createFromHSB(float hue, float saturation, float brightness);

    /** Raeumt auf. */
    virtual ~Color3f() {
    }

    /** Berechnet eine neue Farbe, indem zwischen this und that
     * komponentenweise interpoliert wird. Dabei werden rgb linear mit
     * dem angegebenen Faktor interpoliert. bei t == 0 wird this
     * geliefert, t == 1 liefert that
     *
     * @param that Andere Farbe.
     * @param t Interpolationskoeffizient.
     *
     * @return Color3f* Neue Farbe (geht in den Besitz des Callers ueber).
     */
    Color3f* interpolate(Color3f* that, float t) {
      float r = rgb[0] * (1-t) + that->rgb[0]*t;
      float g = rgb[1] * (1-t) + that->rgb[1]*t;
      float b = rgb[2] * (1-t) + that->rgb[2]*t;

      return(new Color3f(r, g, b));
    }

    /** Setzt die Farbkomponenten.
     *
     * @parma r Rot.
     * @param g Gruen.
     * @param b Blau.
     */
    void set(float r, float g, float b) {
      rgb[0] = r;
      rgb[1] = g;
      rgb[2] = b;
    }

    /** Setzt this auf einen Farbwert.
     *
     * @param c Neue Farbe.
     */
    void set(Color3f* c) {
      rgb[0] = c->rgb[0];
      rgb[1] = c->rgb[1];
      rgb[2] = c->rgb[2];
    }

    /** Liefert stringrep. */
    std::string toString() {
      std::ostringstream help;
      help << "Color3f ("
        << rgb[0] << ", "
        << rgb[1] << ", "
        << rgb[2] << ")" << std::ends;
      std::string res(help.str());

      return(res);
    }

    /** RGBDaten. */
    float rgb[3];

};

#endif // _Color3f_h_
