#ifndef _ImageViewNavigator_h_
#define _ImageViewNavigator_h_

#include <io/file/File.h>
#include <sgtools/KeyListener.h>
#include <string>
#include <util/SyncedList.h>
#include "SelectionListener.h"

class Image;
class Node;
class RenderVisitor;
class Root;
class SGObserver;
class LoadProgress;
class Animations;

/** Navigator des Bildanzeigers... kann raus, reinzoomen und pannen.
 * kann bild weiter und zurueck.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-09-04, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.3 $ $Date: 2001/09/13 13:11:12 $
 *
 * @author cK $Author: koestlin $
 */
class ImageViewNavigator : public KeyListener {

public:
  /** Erzeugt de Bildnavigator.
   *
   * @param _root Szenenwurzel.
   * @param _renderVisitor Render.
   * @param _dir Filename des ersten Files.
   */
  ImageViewNavigator(Root* _root,
                     RenderVisitor* _renderVisitor,
                     File* _dir,
                     Animations& animations);

  /** Raeumt auf. */
  virtual ~ImageViewNavigator();

  /** Setzt das Bild. Hier werden die Bilddaten (ausdehnung etc.) des
   * aktuellen bildes uebernommen).
   *
   * @param i Bild, bleibt im Besitz des Callers.
   */
  void setImage(Image* i);

  /** */
  void setTranslation(bool init=false);

  void keyPressed(KeyEvent* e);

  /** Schaltet auf ein Bild, oder das naechste Bild weiter.
   *
   * @param file Neues Bild Optional.o
   */
  void nextImage();

  /** Schaltet auf das letzte Bild zurueck.
   */
  void prevImage();

  /** laedt das bild nochmal neu (weil es z.b. auf der platte veraendert wurde.
   */
  void reload();

  /** Zeigt ein Bild an.
   *
   * @param f Bild.
   */
  void showImage(File* f);

  void addSelectionListener(SelectionListener* listener) {
    fSelectionListeners.push_back(listener);
    listener->selectionChanged(*fileIterator);
  }

private:
  void setFactor(float newFactor);
  void move(float dx,float dy);
  void centerImage(int imageWidth,int imageHeight);
  void centerImageX(int imageWidth);
  void centerImageY(int imageHeight);

  void informSelectionListener(File* newSelection);

  /** Observer gruppe, die fuer das gekachelte Bild verwendet wird. */
  SGObserver* observer;

  /** Szenengraphwurzel. */
  Root* root;

  /** Breite des aktuellen Bildes. */
  int imageWidth;

  /** Hoehe des aktuellen Bildes. */
  int imageHeight;

  /** Pan-X-Position. */
  float posX;

  /** Pan-Y-Position. */
  float posY;

  /** Zoomfaktor. */
  float factor;

  /** RenderVisitor. */
  RenderVisitor* renderVisitor;

  /** Verzeichnis das angeschaut werden soll. */
  File* dir;

  /** Liste mit allen Files. */
  FileList* files;

  /** Iterator auf diesen Files. */
  FileList::iterator fileIterator;

  /** Szenengraph fuer den Lade-status. */
  LoadProgress* loadProgress;

  /** Liste der selectionlistener */
  std::list<SelectionListener*> fSelectionListeners;

  Animations& animations;
};

#endif // _ImageViewNavigator_h_
