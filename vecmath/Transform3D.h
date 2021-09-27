#pragma once

#include <string>
#include <string.h>

#include <vecmath/Vector3f.h>
#include <vecmath/Point4f.h>
#include <vecmath/Point3f.h>

#include <iostream>

/** Speichert eine Transformation.
 *
 *  0  4  8 12
 *  1  5  9 13
 *  2  6 10 14
 *  3  7 11 15
 *
 * 15 sollte immer 1 sein.
 * 12 - 14 sind die translationskomponenten
 *
 * Die Matrix und Quaternionenfaq verwaltet die matrizen zeilenweise.
 * d.h. wenn in der faq steht
 * 0 -> 0
 * 1 -> 4
 * 2 -> 8
 * 3 -> 12
 * 4 -> 1
 * 5 -> 5
 * 6 -> 9
 * 7 -> 13
 * 8 -> 2
 * 9 -> 6
 * 10 -> 10
 * 11 -> 14
 * 12 -> 3
 * 13 -> 7
 * 14 -> 11
 * 15 -> 15
 *
 * Man kann auf meherer Arten auf die Daten zugreifen.
 * entweder ueber m[i] wobei i gemaess spalten aufstiegend angegeben ist.
 * oder ueber mij wobei i und j spalte und zeile angeben
 * oder ueber idxi aehnlich m[i] nur ohne arrayzugriff.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-24, cK, Created.
 *   <li> 2000-11-25, cK, Commented.
 *   <li> 2001-01-17, cKgS, setScale eingebaut.
 *   <li> 2001-02-14, cK, set(float, translation) eingebaut.
 *   <li> 2001-03-04, cKgS, equals.
 *   <li> 2001-03-10, cK, Documentiert.
 *   <li> 2001-04-15, cK, An vecmath/ angepasst.
 *   <li> 2001-04-16, cK, slebst in Vecmath bewegt, union eingefuehrt
 *        m nicht mehr per new, api aenderungen clear, getData weg.
 *   <li> 2001-04-23, cKgS, Gerds aendeungen (CopyConstructor,
 *        transformInplace(Point3f) und transpose wieder eingebaut???
 * </ul>
 *
 * @todo invertAffine richtig machen ...
 *
 * @version $Revision: 1.4 $, $Date: 2001/06/28 17:08:10 $
 *
 * @author cK, $Author: schaefer $
 */
class Transform3D {

 public:
  /** Erzeugt einen neue, auf ID initialisierte Transformation. */
  Transform3D();

  /** Erzeugt eine neue Transformation, die mit den Werten einer
   * Anderen initialisiert ist.
   *
   * @param t3d Transformation deren Werte kopiert werden sollen.
   */
  Transform3D(Transform3D* t3d);

  /** Raeumt auf. */
  virtual ~Transform3D();

  /** Kopiert newOne in this.
   *
   * @param _newOne Werte die bei this gesetzt werden sollen.
   */
  void set(Transform3D* newOne);

  /** Setzt den Rotationsteil der transformation auf eine Rotation um die
   * X-Achse.
   *
   * @param rad Winkelangabe in Radians.
   */
  void rotX(double rad);

  /** Setzt den Rotationsteil der transformation auf eine Rotation um die
   * X-Achse.
   *
   * @param rad Winkelangabe in Radians.
   */
  void rotY(double rad);

  /** Setzt den Rotationsteil der transformation auf eine Rotation um die
   * X-Achse.
   *
   * @param rad Winkelangabe in Radians.
   */
  void rotZ(double rad);

  /** Liefert die Eulerwinkel der Rotationskomponente.
   *
   * @return Vector3f* eulerwinkel der Vector muss von der Applikation
   *     befreit werden.
   */
  Vector3f* getEuler();

  /** Setzt den Rotationsteil der Matrix auf Eulerrotationsparameter.
   *
   * @param v Eulerwinkel in rad.
   */
  void setEulerXYZ(Vector3f* v);

  /** Kopiert nur den Rotationsteil der Transformation.
   *
   * @param t3d Werte, die uebernommen werden sollen.
   */
  void setRotation(Transform3D* t3d);

  /** Setzt nur den Translationsteil der Transformation.
   *
   * @param v Vector.
   */
  void setTranslation(Vector3f* v);

  /** Gibt den Translationsteil zurueck.
   *
   * @param v Vector.
   */
  void getTranslation(Vector3f* v);

  /** Setzt die Matrix auf ID. */
  void setID() {
    clear();
    indices.idx0 = 1;
    indices.idx5 = 1;
    indices.idx10 = 1;
    indices.idx15 = 1;
  }

  /** Loescht die Daten. */
  void clear() {
    memset(m, 0, 64);
  }

  /** Setzt die Matrix auf eine LookAtMatrix.
   *
   * exe, at und up muessen nicht normalisiert und orthogonal sein. ist
   * aber besser wenn.
   *
   * @param eye Augenpunkt.
   * @param at Punkt auf den geschaut werden soll.
   * @param up Vector der nach oben zeigt.
   */
  void lookAt(Vector3f* eye, Vector3f* at, Vector3f* up);

  /** Setzt die Transformation so, dass die inverse eine korrekte cameramatrix ist.
   * dabei beffindet sich dann die camera an der stelle t, schaut in richtung z, y nach
   * oben x nach rechts.
   *
   * @param x 1. Vector.
   * @param y 2. Vector.
   * @param z 3. Vector.
   * @param t Translation.
   */
  void lookAt(Vector3f* x, Vector3f* y, Vector3f* z, Vector3f* t);

  /** Methode um eine affine abbildung zu invertieren.
   *
   * Die Methode funktioniert nur mit affinen abbildungen, es wird nicht
   * untersucht, ob die Matrix tatsaechlich invertiert wurde oder werden
   * kann.
   *
   * @return Transform3D* inverse.
   */
  Transform3D* invertAffine();

  /** Setzt einen Matrixwert.
   *
   * @param col Spalte.
   * @param row Reihe.
   * @param v Neuer Wert.
   */
  void setData(int col, int row, float v);

  /** Liefert einen Wert aus der Matrix.
   *
   * @param col Matrix-Spalte.
   * @param row Matrix-Reihe.
   *
   * @return float ein Matrixeintrag.
   */
  float getData(int col, int row);

  /** Skaliert die Transformation nonuniform.
   *
   * @param scale Skalierung in den einzelnen Achsen.
   */
  void setScale(Vector3f* scale);

  /** Setzt skalierung und translation.
   *
   * Die skalierungs und translationskomponenten werden ueberschrieben,
   * die anderen Komponenten werde nicht geaendert.
   *
   * @param scale Skalierung.
   * @param translation Translation.
   */
  void set(float scale, Vector3f* translation);

  /** Liefert einen Stringrep. der Transformation.
   *
   * @return std::toString stringrep.
   */
  std::string toString();

  /** Inplace Transformation.
   *
   * @param p Der Punkt wird transformiert.
   */
  void transformInplace(Point4f* p);

  /** Inplace Transformation.
   *
   * Dabei wird als homogene Koordinate 1 verwendet.
   *
   * @param p Der Punkt wird transformiert.
   */
  void transformInplace(Point3f* p);

  /** Setzt sich auf das ergebnis der multiplikation von t1 mit t2.
   *
   * @param m1 Transformation1.
   * @param m2 Transformation2.
   */
  void mul(Transform3D* t1, Transform3D* t2) {
    float* m1 = t1->m;
    float* m2 = t2->m;

    float f1 = m1[0];
    float f2 = m1[4];
    float f3 = m1[8];
    float f4 = m1[12];
    matrix.m00 = f1 * m2[ 0] + f2 * m2[ 1] + f3 * m2[ 2] + f4 * m2[ 3];
    matrix.m10 = f1 * m2[ 4] + f2 * m2[ 5] + f3 * m2[ 6] + f4 * m2[ 7];
    matrix.m20 = f1 * m2[ 8] + f2 * m2[ 9] + f3 * m2[10] + f4 * m2[11];
    matrix.m30 = f1 * m2[12] + f2 * m2[13] + f3 * m2[14] + f4 * m2[15];

    f1 = m1[1];
    f2 = m1[5];
    f3 = m1[9];
    f4 = m1[13];
    matrix.m01 = f1 * m2[ 0] + f2 * m2[ 1] + f3 * m2[ 2] + f4 * m2[ 3];
    matrix.m11 = f1 * m2[ 4] + f2 * m2[ 5] + f3 * m2[ 6] + f4 * m2[ 7];
    matrix.m21 = f1 * m2[ 8] + f2 * m2[ 9] + f3 * m2[10] + f4 * m2[11];
    matrix.m31 = f1 * m2[12] + f2 * m2[13] + f3 * m2[14] + f4 * m2[15];


    f1 = m1[2];
    f2 = m1[6];
    f3 = m1[10];
    f4 = m1[14];
    matrix.m02 = f1 * m2[ 0] + f2 * m2[ 1] + f3 * m2[ 2] + f4 * m2[ 3];
    matrix.m12 = f1 * m2[ 4] + f2 * m2[ 5] + f3 * m2[ 6] + f4 * m2[ 7];
    matrix.m22 = f1 * m2[ 8] + f2 * m2[ 9] + f3 * m2[10] + f4 * m2[11];
    matrix.m32 = f1 * m2[12] + f2 * m2[13] + f3 * m2[14] + f4 * m2[15];

    f1 = m1[3];
    f2 = m1[7];
    f3 = m1[11];
    f4 = m1[15];
    matrix.m03 = f1 * m2[ 0] + f2 * m2[ 1] + f3 * m2[ 2] + f4 * m2[ 3];
    matrix.m13 = f1 * m2[ 4] + f2 * m2[ 5] + f3 * m2[ 6] + f4 * m2[ 7];
    matrix.m23 = f1 * m2[ 8] + f2 * m2[ 9] + f3 * m2[10] + f4 * m2[11];
    matrix.m33 = f1 * m2[12] + f2 * m2[13] + f3 * m2[14] + f4 * m2[15];
  }

  /** Berechnet this*v und speichert das Ergebnis in target
   *
   * @param v Vector.
   * @param target Ziel der Berechnung.
   *
   * @return res Neuer Vector.
   */
  void mul(Vector3f* v, Vector3f* target);

  /** Berechnet this*v.
   *
   * @param v Homogene Koordinate.
   * @param target Homogene zielkooridnaten.
   */
  void mul(Point4f* v, Point4f* target);

  /** Setzt nur den Translationsteil von this anhand von t.
   *
   * @param t Transformation deren Translation zu kopieren ist.
   */
  void setTranslation(Transform3D* t);

  /** Testet, ob this per value gleich ist mit t3d.
   *
   * @param t3d Transformation mit der verglichen werden soll.
   *
   * @return bool true falls alle matrixwerte gleich sind.
   */
  bool equals(Transform3D* t3d);

  /** Transponiert sich selbst. */
  void transpose();

  union {
    /** floatmatrix. */
    float m[16];
    struct {
      /// alternativer zugriff siehe hauptkommentar
      float idx0;
      /// alternativer zugriff siehe hauptkommentar
      float idx1;
      /// alternativer zugriff siehe hauptkommentar
      float idx2;
      /// alternativer zugriff siehe hauptkommentar
      float idx3;
      /// alternativer zugriff siehe hauptkommentar
      float idx4;
      /// alternativer zugriff siehe hauptkommentar
      float idx5;
      /// alternativer zugriff siehe hauptkommentar
      float idx6;
      /// alternativer zugriff siehe hauptkommentar
      float idx7;
      /// alternativer zugriff siehe hauptkommentar
      float idx8;
      /// alternativer zugriff siehe hauptkommentar
      float idx9;
      /// alternativer zugriff siehe hauptkommentar
      float idx10;
      /// alternativer zugriff siehe hauptkommentar
      float idx11;
      /// alternativer zugriff siehe hauptkommentar
      float idx12;
      /// alternativer zugriff siehe hauptkommentar
      float idx13;
      /// alternativer zugriff siehe hauptkommentar
      float idx14;
      /// alternativer zugriff siehe hauptkommentar
      float idx15;
      /// alternativer zugriff siehe hauptkommentar
    }indices;
    struct {

      /// alternativer zugriff siehe hauptkommentar
      float m00;
      /// alternativer zugriff siehe hauptkommentar
      float m01;
      /// alternativer zugriff siehe hauptkommentar
      float m02;
      /// alternativer zugriff siehe hauptkommentar
      float m03;
      /// alternativer zugriff siehe hauptkommentar
      float m10;
      /// alternativer zugriff siehe hauptkommentar
      float m11;
      /// alternativer zugriff siehe hauptkommentar
      float m12;
      /// alternativer zugriff siehe hauptkommentar
      float m13;
      /// alternativer zugriff siehe hauptkommentar
      float m20;
      /// alternativer zugriff siehe hauptkommentar
      float m21;
      /// alternativer zugriff siehe hauptkommentar
      float m22;
      /// alternativer zugriff siehe hauptkommentar
      float m23;
      /// alternativer zugriff siehe hauptkommentar
      float m30;
      /// alternativer zugriff siehe hauptkommentar
      float m31;
      /// alternativer zugriff siehe hauptkommentar
      float m32;
      /// alternativer zugriff siehe hauptkommentar
      float m33;
    }matrix;
  };

 private:
  /** Begrenzt einen Winkel auf 0-2PI im Radmass.
   *
   * @param v Wert dessen Bereiuchg eingegrenzt werden soll.
   *
   * @return float Eingegrenzter Wert.
   */
  float clamp(float v);

  /** Hilfmethode fuer invert affine.
   *
   * Setzt die neue Transformation, die Translation wird
   * in das neue Koordinatensystem umggerechnet.
   *
   * @param t3d Transformation
   */
  void lookAt(Transform3D* t3d);

  /** Liefert eine neue Matrix, die
   * die den Rotationsteil transponiert hat und
   * die Translationen in die entgegengesetzte richtung macht.
   *
   * @return Transform3D* Muss von der Applikation befreit werden.
   */
  Transform3D* fake();

};
