#include <sg/visitors/OGLTextureActivator.h>

#include <util/ListIterator.h>
#include <assert.h>
#include <sg/visitors/OglTools.h>

#include <image/Image.h>

#include <sg/nodeComponents/app/SGImage.h>
#include <sg/nodeComponents/app/Texture.h>

OGLTextureActivator::OGLTextureActivator() {
}


OGLTextureActivator::~OGLTextureActivator() {
  deleteUnusedTextures();
  deleteRegisteredTextures();
}

void OGLTextureActivator::texImage(Image* image, int nOfChannels, int format) {
  glTexImage2D(GL_TEXTURE_2D,
               0,
               nOfChannels,
               image->getWidth(),
               image->getHeight(),
               0,
               format,
               GL_UNSIGNED_BYTE,
               image->getBuffer()->getData());
}

void OGLTextureActivator::activate(Texture* texture) {
  assert(texture != 0);

  void* help = texture->getCustomData((void *)this);
  if (help == 0) {

    SGImage* sgImage = texture->getImage();
    if (sgImage != 0) {
      Image* image = sgImage->getImage();
      if (image != 0) {
        GLuint id;

        glGenTextures(1, &id);
        assert(OglTools::checkOglState(__FILE__, __LINE__));

        glBindTexture(GL_TEXTURE_2D, id);
        assert(OglTools::checkOglState(__FILE__, __LINE__));

        if (image->getFormat().bytePerPixel == 3) {
          texImage(image, 3, GL_RGB);
        } else if (image->getFormat().bytePerPixel == 4) {
          texImage(image, 4, GL_RGBA);
        } else if (image->getFormat().bytePerPixel == 1) {
          texImage(image, 1, GL_LUMINANCE);
        }
        assert(OglTools::checkOglState(__FILE__, __LINE__));

        sgImage->deleteImage();

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MIN_FILTER,
//                        GL_NEAREST);
                        GL_LINEAR);
        assert(OglTools::checkOglState(__FILE__, __LINE__));

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MAG_FILTER,
//                        GL_NEAREST);
                        GL_LINEAR);
        assert(OglTools::checkOglState(__FILE__, __LINE__));

        OGLTextureID* tID = new OGLTextureID(this, id);
        registered.push_back(tID);

        texture->setCustomData((void *)this, tID);
      }

      sgImage->releaseReference();
    }

  } else {

    OGLTextureID* id = (OGLTextureID*)help;
    glBindTexture(GL_TEXTURE_2D, id->id);
    assert(OglTools::checkOglState(__FILE__, __LINE__));
  }
}

void OGLTextureActivator::deleteTexture(OGLTextureID* t) {

  if (t->isRegistered() == true) {
    lock();

    t->setRegistered(false);
    registered.remove(t->id);

    toDelete.push_back(t->id);

    unlock();
  }
}


void OGLTextureActivator::deleteUnusedTextures() {
  lock();

  ListIterator<GLuint> i(&toDelete);
  while (i.hasNext() == true) {

    GLuint help = i.next();
    glDeleteTextures(1, &help);
    assert(OglTools::checkOglState(__FILE__, __LINE__));
  }
  toDelete.clear();

  unlock();
}

void OGLTextureActivator::deleteRegisteredTextures() {
  ListIterator<OGLTextureID*> i(&registered);
  while (i.hasNext() == true) {

    OGLTextureID* id = i.next();

    id->setRegistered(false);
    glDeleteTextures(1, &(id->id));
    assert(OglTools::checkOglState(__FILE__, __LINE__));
  }
  registered.clear();
}

void RegisterList::remove(GLuint id) {
  std::list<OGLTextureID*>::iterator i = begin();
  while (i != end()) {

    OGLTextureID* current = *i;

    if (current->id == id) {
      current->setRegistered(false);
      erase(i);
      break;
    }

    ++i;
  }

}

OGLTextureID::~OGLTextureID() {
  if (isRegistered() == true) {
    tManager->deleteTexture(this);
  }
}
