#ifndef _OGLRenderVisitor_h_
#define _OGLRenderVisitor_h_

#include <windowsinclude.h>

#ifdef OSX
  #include <OpenGL/gl.h>
  #include <OpenGL/glext.h>
#else
  #include <GL/gl.h>
  #include <GL/glext.h>
#endif

#include <sg/nodes/Group.h>
#include <sg/nodes/Root.h>
#include <sg/nodes/TGroup.h>
#include <sg/nodes/FogGroup.h>
#include <sg/nodes/ProjectionGroup.h>
#include <sg/nodes/LightGroup.h>
#include <sg/nodes/Leaf.h>
#include <sg/nodes/Node.h>
#include <sg/nodes/SwitchGroup.h>
#include <sg/nodes/SGObserver.h>
#include <sg/nodes/Shape3D.h>
#include <sg/nodes/OrientedShape3D.h>
#include <sg/nodeComponents/app/Appearance.h>
#include <sg/nodeComponents/app/TexGen.h>

#include <image/Image.h>
#include <sg/SGObject.h>
#include <sg/data/Array2f.h>
#include <sg/nodeComponents/geom/IndexedTriangleArray.h>
#include <sg/nodeComponents/geom/TeapotGeometry.h>
#include <sg/nodeComponents/geom/TriangleArray.h>
#include <sg/nodeComponents/geom/Text3D.h>
#include <sg/visitors/OGLTextureActivator.h>
#include <sg/visitors/RenderVisitor.h>

#include <sg/visitors/OGLFontManager.h>

#include <string>

/** OGLRenderVisitor.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-25, cK, Created.
 *   <li> 2000-11-29, cK, IndexedTriangleArrays eingefuehrt, 
 *                        bessere Appearanceunterstuetzung.
 *   <li> 2001-01-04, cK, Multitexturing eingebaut.
 *   <li> 2001-02-11, cK, Ist nun eine abstrakte klasse. nur 
 *        die oglbefehle sind hier drin, systemabhanegige sachen 
 *        sollten in unterklassen gemacht werden (z.b. fonts)
 *   <li> 2001-01-13, cK, Um Fontmanager erweitert.
 *   <li> 2001-02-27, cK, RenderingAttributes integriert (rudimentaer).
 *   <li> 2001-03-31, cK, An linux angepasst.
 *   <li> 2001-04-16, cK, An vecmath/Transform3D problematik angepasst.
 *   <li> 2001-04-26, cK, Eignene Projectionen verwendet.
 *   <li> 2001-04-26, cK, default fuer rendering attributes.
 *   <li> 2001-05-02, cK, An shape3d.addGeometry angepasst.
 *   <li> 2001-05-28, cK, visit PG geaendrt, damit die projectionsmatrtix 
 *        nach jeder pg zurueckgesetztwird, um das boese wavestreamkonstrukt 
 *        (gruppe unter root und dann erst pgs) zuzulassen.
 *   <li> 2001-05-28, cK, Bischen sauberer gemacht mit dem IDsetzen von 
 *        Projections und Modelviewmatrizen.
 *   <li> 2001-07-05, cK, An OGLTextureActivator statt 
 *        OGLTextureManager angepasst.
 * </ul>
 *
 * @todo sollte auch ohne multitexturingkarte gehen!
 * @todo RenderingAttributes richtig machen!
 *
 * @version $Revision: 1.13 $, $Date: 2001/10/24 14:27:40 $
 *
 * @author cK, $Author: koestlin $
 */
class OGLRenderVisitor : public RenderVisitor {

   
 public:
  /** Erzeugt den Visitor. 
   *
   * @param fontManager weiss, wie er mit Text3D etc umzugehen hat.
   *        geht in den Besitz vom RenderVisitor ueber.
   */
  OGLRenderVisitor(OGLFontManager* fontManager);
  
  /** Raeumt auf. */
  virtual ~OGLRenderVisitor();
  
  void visit(SGObserver* observer);
  
  void visit(SGObject* sgo);
  
  void visit(Node* n);
  
  void visit(Group* g);
 
  void visit(SwitchGroup* switchGroup);
  
  void visit(Root* g);
  
  void visit(TGroup* tg);
  
  void visit(FogGroup* fogGroup);
  
  void visit(ProjectionGroup* pGroup);
  
  void visit(LightGroup* lGroup);
  
  void visit(Leaf* l);
  
  void visit(Shape3D* shape3d);
  
  void visit(OrientedShape3D* oShape3d);
  
  void visit(Geometry* geometry);
  
  void visit(TriangleArray* tArray);
    
  void visit(IndexedTriangleArray* itArray);

  void visit(InterleavedTriangleArray* array);

  void visit(IndexedInterleavedTriangleArray* array);
  
  void visit(TeapotGeometry* teapot);
  
  void visit(Text3D* text3d);
  
  void visit(Appearance* app);
  
  void visit(Texture* texture);
  
  std::string toString() {
    return("OGLRenderVisitor");
  }  

  /** Texturmanager, der das anmelden/loeschen etc. der Texturen vornimmt.
   */
  OGLTextureActivator tManager;

 protected:
   /** Gibt die aktuelle ModelView und Projectionsmatrix aus. */
  void printMatrices();
  
 private:

  /** Erzeugt Billboasrdtransformationen. 
   *
   * @param observer Observer zu dem passend die 
   *        Billboardtransformationen berechnet werden sollen.
   */
  void createBillboards(SGObserver* observer);
  
  /** Gibt die bvn createBillboards erzeugten Transformationen frei. */
  void releaseBillboards();
  
  /** OGLFontRenderer. */
  OGLFontManager* fontManager;
  
  /** Berechnet aus einem TriangleArray-type eine OGl-Enum. 
   *
   * @param type TriangleArraytyp.
   *
   * @return GLEnum entweder TRIS, FAN oder Strip.
   */
  GLenum type2Enum(TriangleArrayType type);
  
  
  /** Es wird eine Textur aktiviert.
   *
   * Auslagerung wegen multitexturing.
   *
   * @param t Die Texture.
   */
  void bringUpTexture(Texture* t, TexGen* texGen);
  
  /** Beinhaltet die Operationen, die benoetigt werden, wenn 
   * eine Appearance beginnt. 
   *
   * @param a Appearance, die aktiviert werden soll.
   */
  void startApp(Appearance* a);
  
  /** Es wird eine Textur versucht aufzuraeumen.
   *
   * Auslagerung wegen multitexturing.
   *
   * @param t Die Textur.
   */
  void cleanUpTexture(Texture* texture, TexGen* texGen);
  
  /** Beinhaltet die Operationen, die benoetigt werden, wenn 
   * eine Appearance nicht mehr benoetigt wird.
   *
   * Es wird versucht, der gleiche Zustand (bzw. ein defaultzustand) wie vor
   * der Appearance zu erreichen.
   *
   * @param a Appearance
   */
  void endApp(Appearance* a);
  
  
  /** eigentlich aktivierung der tcoordinatenpointer.
   *
   * @param tCoords daten.
   */
  void activateTexCoordPointer(Array2f* tCoords);
  
  /** Aktiviert entweder 1 array von texturecoordinaten oder
   * mehere array (multitexturing).
   *
   * @param tArray Daten.
   */
  void bringUpTCoords(TriangleArray* tArray);
  
  /** eigentlich deaktivierung der tcoordinatenpointer.
   * 
   * @param tArray Daten.
   */
  void deactivateTexCoordPointer(Array2f* tArray);
  
  /** Raeumt das zuvor gemacht wieder auf.
   *
   * @param tArray Daten.
   */
  void cleanUpTCoords(TriangleArray* tArray);
  

#ifdef WIN32
  /** Funktion um eine texturunit zu aktivieren. Alle folgenden 
   * operationen, texturmapping betreffend beziehen sich auf
   * diese aktivierte textureinheit.
   */
  PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;

  /** Um mit vertexarrays zu arbeiten und den pointer setzten zu 
   * koennen.
   */
  PFNGLACTIVETEXTUREARBPROC glClientActiveTextureARB;
#endif

  void checkMatrices();
  
};

#endif // _OGLRenderVisitor_h_
