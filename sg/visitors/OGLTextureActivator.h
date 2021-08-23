#ifndef _OGLTextureActivator_h_
#define _OGLTextureActivator_h_

#include <list>
#include <lang/Mutex.h>

#ifdef OSX
  #include <OpenGL/gl.h>
#else
  #include <GL/gl.h>
#endif

#include <sg/visitors/CustomData.h>

class OGLTextureID;
class Texture;
class Image;

/** Liste mit zur Karte geladenen Texturobjekten.
 *
 * Die Liste erlaubt das Entfernen eines Objektes anhand der vergebenen id.
 * Bei diesem entfernen muss dem Objekt mitgeteilt werden, dass es nicht mehr registriert ist.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-10-23, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.4 $ $Date: 2001/10/24 14:27:40 $
 *
 * @author cK $Author: koestlin $
 */
class RegisterList : public std::list<OGLTextureID*> {

  public:

    /** Entfernt das Objekt aus der Liste, dessen id mit id uebereinstimmt.
     * Im Texturobjekt wird gespeichert, dass es nicht mehr registriert ist.
     *
     * @param id Zu entfernende id.
     */
    void remove(GLuint id);

};


/** Klasse um aehnlich wie der OGLTextureManager texturen auf
 * die Grafikkarte (bzw. in den Treiber) zu laden. Im Gegensatz zum
 * OGLTextureManager wird der CustomData-Mechanismus verwendet.
 *
 * das deleteTexture und deleteUnusedTextures ist noetig, um das
 * loeschen von texturen aus einem anderen thread heraus zu
 * ermoeglichen.
 *
 * Es werden 2 Listen mit TextureIDs gefuehrt:
 * toDelete verwaltet Texturobjekte, die nicht mehr vom SG benoetigt werden.
 * registered Verwaltet Texturobjekte, die zur Grafikkarte hochgeladen sind.
 * Die 2 Listen sind disjunkt (nach beendigung von deleteTexture). Texturen,
 * die registriert sind und geloescht werden (deleteTexture) werden unregistriert
 * und dann in die toDelete-Lister eingetragen, um vom richtigen Thread entsprechend
 * geloescht zu werden. Texsturen, die immer benoetigt werden, werden im destruktor von
 * deleteRegisteredTextures geloescht.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-07-05, cK, Created.
 *   <li> 2001-10-23, cK, Loeschen von Texturen korrigiert (probleme mit dem texturcache).
 * </ul>
 *
 * @todo Scheinbar ists so, dass das glBindTExture mehr
 *       textureinstellungen laedt als angenommen als kann
 *       man hier z.b. textureWrap auch nur einmal aufrufen.
 *       vgl. OGLRenderVisitor
 *
 * @version $Revision: 1.4 $ $Date: 2001/10/24 14:27:40 $
 *
 * @author cK, $Author: koestlin $
 */
class OGLTextureActivator : public Mutex {

  public:
    /** Erzeugt das Object. */
    OGLTextureActivator();

    /** Raeumt auf. */
    virtual ~OGLTextureActivator();

    /** Activiert eine Texture.
     *
     * Evtl. wird ein Textureobjekt erzeugt und zur Gfxkarte hochgeladen.
     * Ist das TextureObjekt schon auf der Grafikkarte, wird es nur aktiviert.
     *
     * Die TextureID-Objekte werden in der registered-Liste gespeichert.
     *
     * @param t Texture.
     */
    void activate(Texture* t);

    /** Fuehrt den eigentlichen glTexImage2D-call aus.
     * @param image bilddaten.
     * @param nOfChannels anzahhl der farbkanaele.
     * @param format oglformat.
     */
    void texImage(Image* image, int nOfChannels, int format);

    /** Gibt eine Textur (bzw. deren id) zum Abschuss frei.
     *
     * Die TextureID-Objekte werden aus der registered-Liste entfernt, die ids werden in die
     * toDelete-Liste aufgenommen (und das flag, dass
     * sie praktisch schon geloscht sind wird gesetzt).
     *
     * @param t Texturid.
     */
    void deleteTexture(OGLTextureID* t);

    /** Loescht alle nicht verwendeten Texturen.
     * (deren ids sind in der toDelete-Liste gespeichert).
     *
     * Dieses nicht sofortige loeschen ist noetig, da das deleteTexture
     * auch aus anderen Threads und damit in anderen OGLContexten
     * moeglich ist. Sollte am Anfang oder am Ende des Renderns des
     * Root-Knoten stattfinden.
     */
    void deleteUnusedTextures();

  private:

    /** Loescht alle zur gfx-karte hochgeladenen Texturen von der Grafikkarte. */
    void deleteRegisteredTextures();

    /** Liste mit zu loeschenden Texturen, die nicht mehr im Szenengraph benoetigt werden. */
    std::list<GLuint> toDelete;

    /** Liste mit allen zur Grafikkarte hochgeladenen Texturen. */
    RegisterList registered;

};

/** Klasse die sich eine OpenglTextureid merkt.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-07-05, cK, Created.
 *   <li> 2001-07-06, cK, Textur wird im Destruktor nun auch
 *        bei ogl aufgeraeumt, TextureListener wird nicht mehr benoetigt.
 *   <li> 2001-10-23, cK, Um registered-flag erweitert.
 * </ul>
 *
 * @version $Revision: 1.4 $ $Date: 2001/10/24 14:27:40 $
 *
 * @author cK $Author: koestlin $
 */
class OGLTextureID : public CustomData {

  public:

    /** Erzeugt das Objekt mit einer OGL-TextureID.
     *
     * @param _tManager zugehoeriger activator.
     * @param _id OGLTextureObjectID.
     */
    OGLTextureID(OGLTextureActivator* _tManager, GLuint _id)
      : id(_id), tManager(_tManager), registered(true) {
    }

    /** Raeumt auf.
     *
     * Falls die Textur noch registriert ist, muss sie von der Grtafikkarte entfernt werden,
     * ansonsten wurde das schon vom textureactivator gemacht.
     */
    virtual ~OGLTextureID();

    /** Setzt das Flag.
     *
     * @param v Neuer Wert.
     */
    void setRegistered(bool v) {
      registered = v;
    }

    /** Testet, ob die Textur noch registriert ist.
     *
     * @return bool true, falls die Textur noch registriert ist.
     */
    bool isRegistered() {
      return(registered);
    }

    /** Die ID. */
    GLuint id;


  protected:
    /** Der zugehoerige Textureaktivator. */
    OGLTextureActivator* tManager;

    /** Ist das Texturobject noch registriert. */
    bool registered;

};

#endif // _OGLTextureActivator_h_
