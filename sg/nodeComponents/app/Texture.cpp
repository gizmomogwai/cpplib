#include <sg/nodeComponents/app/Texture.h>


Texture::Texture(SGImage* _image) 
  : wrapS(true), wrapT(true) {

  image.set(_image);	
}

Texture::~Texture() {
}

SGImage* Texture::getImage() {
  return image.get();
}

void Texture::setTextureWrap(bool newWrapS, bool newWrapT) {
  wrapS = newWrapS;
  wrapT = newWrapT;
}
