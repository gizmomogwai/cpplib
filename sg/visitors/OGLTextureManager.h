#pragma once

#include <iostream>
#include <map>
#include <list>

#include <lang/Mutex.h>

#include <sg/nodeComponents/app/TextureListener.h>
#include <sg/nodeComponents/app/Texture.h>
#include <sg/nodeComponents/app/SGImage.h>
#include <image/Image.h>

#ifdef OSX
  #include <OpenGL/gl.h>
#else
  #include <GL/gl.h>
#endif

#include <assert.h>

typedef std::map<unsigned long, GLuint> OGLTextureHashMap;


/** Primitiver TextureManager fuer OGL-Texturen.
 *
 * Dabei wird zur Textur noch eine evtl. vorhandene GLuint (id)
 * gespeichert.
 *
 * Theoretisch sollte dieser Manager beim zerstoeren alle referenzen
 * herunterzaehlen, und vor allem alle angemeldeten oglids wieder
 * aufraeumen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-16, cK, Created.
 *   <li> 2001-02-06, cKgS, Problem mit dem texturenloeschen
 *        in dem flaschen thread ...
 *   <li> 2001-03-31, cK, An linux angepasst (stl liefert bei
 *        map.erase nichts zurueck???
 * </ul>
 *
 *
 * @version $Revision: 1.3 $, $Date: 2001/09/13 13:11:13 $
 *
 * @author cK, $Author: koestlin $
 */
class OGLTextureManager : public TextureListener, public Mutex{

  public:
    /** Erzeugt einen neuen OGL-TextureManager. */
    OGLTextureManager() {
    }

    /** Raeumt auf. */
    ~OGLTextureManager() {
      std::cout << "Da ist noch nicht das letzte wort gesprochen," <<
        " die referenzen muessen released werden" << std::endl;
    }


    /** Aktiviert eine Textur.
     *
     * Zunaechst wird getestet, ob die Textur schon bekannt ist.
     * Ist das nicht der fall wird die Textur im Manager eingetragen.
     *
     * Dann wird getestet, ob schon eine OGL-ID vergeben wurde. Ist dies nicht
     * der fall, dann wird eine TexturID erzeugt und die Textur zur Karte
     * hochgeladen. (die lokale textur kann geloescht werden).
     * Ist dies der Fall wird die ID aktiviert!
     *
     * @param texture Textur.
     */
    void activate(Texture* texture) {

      assert(texture != 0);

      lock();

      OGLTextureHashMap::iterator found =
        textures.find((unsigned long)texture);

      if (found != textures.end()) {
        GLuint id = found->second;
        glBindTexture(GL_TEXTURE_2D, id);
        assert(glGetError() == GL_NO_ERROR);
        std::cout << "Texture found" << std::endl;
      } else {
        std::cout << "Texture miss" << std::endl;
        SGImage* sgImage = texture->getImage();
        if (sgImage != 0) {
          Image* image = sgImage->getImage();
          if (image != 0) {
            GLuint id;
            glGenTextures(1, &id);
            assert(glGetError() == GL_NO_ERROR);

            glBindTexture(GL_TEXTURE_2D, id);
            assert(glGetError() == GL_NO_ERROR);

            if (image->getFormat().bytePerPixel == 3) {

              glTexImage2D(GL_TEXTURE_2D,
                           0,
                           3,
                           image->getWidth(),
                           image->getHeight(),
                           0,
                           GL_RGB,
                           GL_UNSIGNED_BYTE,
                           image->getBuffer()->getData());
            } else if (image->getFormat().bytePerPixel == 4) {

              glTexImage2D(GL_TEXTURE_2D,
                           0,
                           4,
                           image->getWidth(),
                           image->getHeight(),
                           0,
                           GL_RGBA,
                           GL_UNSIGNED_BYTE,
                           image->getBuffer()->getData());

            }
            assert(glGetError() == GL_NO_ERROR);

//            texture->setListener(this);

            sgImage->deleteImage();

            glTexParameteri(GL_TEXTURE_2D,
                            GL_TEXTURE_MIN_FILTER,
                            GL_LINEAR);
            assert(glGetError() == GL_NO_ERROR);

            glTexParameteri(GL_TEXTURE_2D,
                            GL_TEXTURE_MAG_FILTER,
                            GL_LINEAR);
            assert(glGetError() == GL_NO_ERROR);

            // jetzt noch in der tabelle speichern
            textures.insert(std::make_pair((unsigned long)texture, id));

          }
          sgImage->releaseReference();
        }
      }

      unlock();
    }

    /** Wird aufgerufen, wenn eine Textur nicht mehr benoetigt wird
     * (weder applikation noch szenegraph)
     *
     * @param t Texture.
     */
    void deleteTexture(Texture* t) {
      lock();

      toDelete.push_back((unsigned long)t);

      unlock();
    }

    /** Loescht die Texturen vom gfxkartenspeicher.
     *
     * Darf nur im renderthread aufgerufen werden.
     */
    void deleteUnusedTextures() {

      lock();

      std::list<unsigned long>::iterator i = toDelete.begin();
      while (i != toDelete.end()) {

        OGLTextureHashMap::iterator found = textures.find((unsigned long)*i);
        i++;

        if (found != textures.end()) {
          GLuint id = found->second;

          glDeleteTextures(1, &id);
          assert(glGetError() == GL_NO_ERROR);

          textures.erase(found);
        }
      }

      toDelete.clear();

      unlock();
    }

  private:
    /** Mapt texturepointer auf openglids. */
    OGLTextureHashMap textures;

    /** Liste mit zu loeschenden Texturen. */
    std::list<unsigned long> toDelete;


};
