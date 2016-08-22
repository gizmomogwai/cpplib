#ifndef _RenderVisitor_h_
#define _RenderVisitor_h_

#include <sg/visitors/Visitor.h>
#include <vecmath/Transform3D.h>

class RenderVisitor : public Visitor {

  public:

    RenderVisitor() {
    }

	  virtual ~RenderVisitor() {
	  }

    void visit(ImplicitSGNode* node);

    /** Liefert die Breite des Canvases. 
     *
     * @return int Breite des Canvases.
     */
    int getImageWidth() {
      return(imageWidth);
    }

    /** Liefert die Hoehe des Canvases. 
     *
     * @return int Hoehe des Canvases.
     */
    int getImageHeight() {
      return(imageHeight);
    }

    /** Liefert den AspectRatio (x/y) des Canvases.
     *
     * @return float aspectRatio.
     */
    float getAspectRatio() {
      return(((float)imageWidth) / ((float)imageHeight));
    }

	  /** Transformation die die Billboardmatrix zur Camera in Richtung z-Achse
	   * enthaelt. 
	   */
    Transform3D yAxisBillboard;

    Transform3D observerTransformation;

  	/** Breite des Canvases. */
    int imageWidth;

  	/** Hoehe des Canvases. */
    int imageHeight;

};

#endif // _RenderVisitor_h_
