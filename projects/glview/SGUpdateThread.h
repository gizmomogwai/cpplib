#pragma once

#include <lang/Thread.h>
class Animations;
class AnimationGroup;
class File;
class Group;
class Image;
class ImageViewNavigator;
class LoadProgress;
class Node;
class Root;
class SGObserver;
class Shape3D;
class TriangleArray;

/** Thread der fuer das Laden eines Bildes und das updaten
 * des Szenegraphen zustaendig ist.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-08-11, cK, Created.
 *   <li> 2001-09-04, cK, Um LoadProgress erweitert.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2001/09/13 13:11:12 $
 *
 * @author cK $Author: koestlin $
 */
class SGUpdateThread : public Thread {

public:
  /** Erzeugt einen neuen Thread.
   *
   * @param root Hier kann eine statusanzeige eingehaengt werden, bleibt im
   *   besitz des Callers.
   * @param observer Hier wird das zerschnittene Bild eingehaengt, bleibt
   *   im besitz des Callers.
   * @param file File das geladen werden soll. Bleibt im Besitz des Callers.
   * @param loadProgress Szenengraph der beim laden angezeigt werden soll.
   */
  SGUpdateThread(Root* root,
                 SGObserver* observer,
                 File* file,
                 ImageViewNavigator* navigator,
                 LoadProgress* loadProgress,
                 Animations& animations);

  /** Raeumt auf. */
  virtual ~SGUpdateThread();

  /** Laedt das Bild und setzt den Szenegraph mit
   * dem zerschnittenen Bild. Evtl. kann man auch noch einen
   * Ladeanzeige einbauen.
   */
  void run();

private:

  /** Ersetz ein Kind einer Gruppe durch einen dummy-Knoten. */
  void setDummy(Group* g, int idx);

  /** Groesse der einzeltexturen. */
  static const int textureSize;

  /** Observer, der um den neuen Szenegraphen erweitert
   * werden soll.
   */
  SGObserver* observer;

  /** File das geladen werden soll. */
  File* file;

  /** SG fuer status laden. */
  LoadProgress* loadProgress;

  /** Imagenavigator. */
  ImageViewNavigator* navigator;

  /** Geometry for all tiles */
  TriangleArray* tileGeometry;

  void setupTileGeometry();
  /** Erzeugt zu einem Bild ein Shape.
   *
   * @param height Hoehe des gesamten Bildes.
   * @param i X-Index.
   * @param j Y-Index.
   * @param image Das Bild, caller verliert den besitz.
   */
  Shape3D* shapeForImage(int height,
                         int i,
                         int j,
                         Image* image);

  /** Gesamtzeit fuer das Zerschneiden eines Bildes. */
  float cutTime;

  /** Erzeugt ein Shape zu einem Teilbild an einer Position in
   * dem zerlegten Raster.
   *
   * @param image Bild Caller verliert den Besitz.
   * @param xPos X-Position.
   * @param yPos Y-Position.
   * @param xCount Anzahl von Kacheln in X-Richtung.
   * @param yCount Anzahl von Kacheln in Y-Richtung.
   * @param res Gruppe zu der das Shape hinzugefuegt wird.
   *        Gruppe bleibt im Besitz des Callers.
   * @param clipped Ist die Kachel komplett von Bild unterlegt
   *        oder nur zum Teil unterlegt.
   */
  void createShape(Image* image,
                   int xPos, int yPos,
                   int xCount, int yCount,
                   Group* res, bool clipped, AnimationGroup& animations);

  /** Baut einen Szenegraphen.
   *
   * @param file Bildfile.
   */
  void buildViewGraph(File* file);

  Animations& animations;
};
