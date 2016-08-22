#include <sg/nodeComponents/app/Appearance.h>

#include <sstream>
#include <lang/Exception.h>


Appearance::Appearance(int _texNr) : maxTextures(_texNr) {
  polygonAttributes = new UpdateObject<PolygonAttributes>();
  renderingAttributes = new UpdateObject<RenderingAttributes>();
  material = new UpdateObject<Material>();
  
  textures = new UpdateObject<Texture>*[maxTextures];
  texGens = new UpdateObject<TexGen>*[maxTextures];
  for (int i=0; i<maxTextures; i++) {
    textures[i] = 0;
    texGens[i] = 0;
  }
}

Appearance::~Appearance() {
  if (polygonAttributes != 0) {
    delete(polygonAttributes);
    polygonAttributes = 0;
  }

  if (renderingAttributes != 0) {
    delete(renderingAttributes);
    renderingAttributes = 0;
  }

  if (material != 0) {
    delete(material);
    material = 0;
  }

  for (int i=0; i<getMaxMultiTextures(); i++) {
    if (textures[i] != 0) {
      delete(textures[i]);
      textures[i] = 0;
    }
    if (texGens[i] != 0) {
      delete(texGens[i]);
      texGens[i] = 0;
    }
  }
  delete[](textures);
  textures = 0;

  delete[](texGens);
  texGens = 0;

  maxTextures = 0;
}

int Appearance::getMaxMultiTextures() {
  return(maxTextures);
}


void Appearance::setPolygonAttributes(PolygonAttributes* pAtts) {
  polygonAttributes->set(pAtts);
}

void Appearance::setRenderingAttributes(RenderingAttributes* rAtts) {
  renderingAttributes->set(rAtts);
}

void Appearance::setMaterial(Material* _m) {
  material->set(_m);
}

Material* Appearance::getMaterial() {
  return(material->get());
}

void Appearance::setTexture(Texture* _texture, int _texNr) {
  // refcounting wird schon von updateobject gemacht
  assertTexNr(_texNr, "Appearance::setTexture");
  if (textures[_texNr] == 0) {
    textures[_texNr] = new UpdateObject<Texture>();
  }
  textures[_texNr]->set(_texture);  
}

void Appearance::setTexGen(TexGen* _texGen, int _texNr) {
  // refcounting wird schon von updateobject gemacht
  assertTexNr(_texNr, "Appearance::setTexGen");
  if (texGens[_texNr] == 0) {
    texGens[_texNr] = new UpdateObject<TexGen>();
  }
  texGens[_texNr]->set(_texGen);
//  texGen->set(_texGen);
}

PolygonAttributes* Appearance::getPolygonAttributes() {
  return(polygonAttributes->get());
}

RenderingAttributes* Appearance::getRenderingAttributes() {
  return(renderingAttributes->get());
}

Texture* Appearance::getTexture(int _texNr) {
  // refcounting wird schon von updateobject gemacht
  assertTexNr(_texNr, "Appearance::getTexture");
  
  Texture* res = 0;  
  if (textures[_texNr] != 0) {
    res = textures[_texNr]->get();
  }
  return(res);
}

TexGen* Appearance::getTexGen(int _texNr) {
  assertTexNr(_texNr, "Appearance::getTexGen");

  return(texGens[_texNr] == 0 ? 0 : texGens[_texNr]->get());
//  return(texGens[_texNr]->get());
//  return(texGen->get());
}

void Appearance::assertTexNr(int _texNr, const char* where) throw (Exception) {
  if ((_texNr < 0) || (_texNr >= getMaxMultiTextures())) {
    std::ostringstream h;
    h << where << "(" << _texNr << ") - _texNr zu gross)" << std::ends;
    Exception e(h.str());
    throw(e);
  }
}
