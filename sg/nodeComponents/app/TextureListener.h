#ifndef _TextureListener_h_
#define _TextureListener_h_

#include <sg/nodeComponents/app/Texture.h>

class TextureListener {

  public:
    /** Raeumt auf. */
    virtual ~TextureListener() {}

    /** 
     * Wird ausgefuehrt, wenn die Textur nicht mehr benoetigt wird.
     *
     * @param texture Die Textur.
     */
    virtual void deleteTexture(Texture* t) = 0;

};

#endif // _TextureListener_h_
