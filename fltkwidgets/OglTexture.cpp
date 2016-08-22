#include <fltkwidgets/OglTexture.h>
#include <image/Image.h>
#include <image/ImageOperations.h>
#include <image/JpegImage.h>
#include <image/ImageReader.h>

OglTexture::OglTexture(std::string fileName, bool thumb) : fFileName(fileName), fId(0), fWidth(0), fHeight(0), fFailed(false), fThumb(thumb) {
}

// must be called from ogl rendering context
OglTexture::~OglTexture() {
  if (fId) {
    glDeleteTextures(1, &fId);
    assert(glGetError() == GL_NO_ERROR);
  }
}

void OglTexture::killBorder(Image& image) {
  static const unsigned char alpha = 0;
  for (unsigned int i=0; i<image.getWidth(); i++) {
    *(image.getData(i, 0)+3) = alpha;
  }
  for (unsigned int j=0; j<image.getHeight(); j++) {
    *(image.getData(0, j)+3) = alpha;
    *(image.getData(image.getWidth()-1, j)+3) = alpha;
  }
}

void OglTexture::activate() {
  if ((!fId) && (!fFailed)) {
    Image* i = 0;
    if (fThumb) {
      File f(fFileName);
      JpegImage jpeg(&f);
      i = jpeg.getThumbnail();
    } else {
      ImageReader r;
      i = r.readImage(fFileName);
    }

    if (i) {
      fWidth = i->getWidth();
      fHeight = i->getHeight();
      Image* imageWithBorder = ImageOperations::getImageAsRGBA(*i);
      delete i;
      killBorder(*imageWithBorder);

      glGenTextures(1, &fId);
      assert(glGetError() == GL_NO_ERROR);

      glBindTexture(GL_TEXTURE_2D, fId);
      assert(glGetError() == GL_NO_ERROR);

      glTexImage2D(GL_TEXTURE_2D,
		   0,
		   GL_RGBA,
		   imageWithBorder->getWidth(),
		   imageWithBorder->getHeight(),
		   0,
		   GL_RGBA,
		   GL_UNSIGNED_BYTE,
		   imageWithBorder->getBuffer()->getData());
      assert(glGetError() == GL_NO_ERROR);

      delete imageWithBorder;

      glTexParameteri(GL_TEXTURE_2D,
		      GL_TEXTURE_MIN_FILTER,
		      GL_LINEAR);
      assert(glGetError() == GL_NO_ERROR);

      glTexParameteri(GL_TEXTURE_2D,
		      GL_TEXTURE_MAG_FILTER,
		      GL_LINEAR);
      assert(glGetError() == GL_NO_ERROR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      assert(glGetError() == GL_NO_ERROR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      assert(glGetError() == GL_NO_ERROR);
    } else {
      fFailed = true;
      std::cout << "could not open thumb of " << fFileName << std::endl;
    }
  } else {
    glBindTexture(GL_TEXTURE_2D, fId);
    assert(glGetError() == GL_NO_ERROR);
  }
}

unsigned int OglTexture::getWidth() {
  return fWidth;
}

unsigned int OglTexture::getHeight() {
  return fHeight;
}

