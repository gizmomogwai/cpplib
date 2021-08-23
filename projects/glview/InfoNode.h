#ifndef InfoNode_h_
#define InfoNode_h_

#include <sg/nodes/Group.h>
#include <sg/nodes/SwitchGroup.h>
#include <sg/nodes/ImplicitSGNode.h>
#include <sg/nodes/Shape3D.h>

#include <sg/nodeComponents/app/Texture.h>
#include <sg/nodeComponents/app/Appearance.h>

#include <sg/visitors/RenderVisitor.h>
#include <sg/visitors/UpdateVisitor.h>

#include <sg/data/Array3f.h>

#include <lang/CleanUpObject.h>


class InfoNodeHelper {
	public:
		static void addDummyNodeTo(SwitchGroup* g);
    static void setRectTexCoords(TriangleArray* triangles);
    static void setFillAndZBuffer(Appearance* app);
    static void setPoints(Array3f* points, int imagewWidth, int imageHeight, int fromLeft, int fromBottom,
                          int canvasWidth, int canvasHeight, int realWidth, int realHeight);
};

class SwitchableWatermark : public SwitchGroup {
	public:
		SwitchableWatermark(Image* image, int left, int top);

		virtual~ SwitchableWatermark() {
		  std::cout << "~SwitchableWatermark" << std::endl;
		/*
			fPoints->releaseReference();
			fWatermarkApp->releaseReference();
			*/
		}
		
		virtual std::string toString() {
		  return "SwitchableWatermark";
		}

		void update(int canvasWidth, int canvasHeight);
		
		void setImage(Image* image, int realWidth=0, int realHeight=0);
		
		void setVisible(bool flag);
		
	private:
		int fImageWidth;
		int fImageHeight;
		int fLeft;
		int fTop;
		Array3f* fPoints;
	
		Appearance* fWatermarkApp;
		int fRealImageWidth;
		int fRealImageHeight;

};


class InfoNode : public ImplicitSGNode {
  public:
	  InfoNode();
	
    void addWatermark(SwitchableWatermark* newWatermark) {
      
    }
    
		virtual ~InfoNode() {
			std::cout << "~InfoNode TODO" << std::endl;
  	}
		
  	virtual void paint(RenderVisitor* renderVisitor);
		
		void setIotd(bool value);
		
		void setSync(bool value);
		
		void addChild(SwitchableWatermark* newChild);

		/** because of pow2 issues with ogl textures. */
    void setThumbnail(Image* image, int realWidth, int realHeight);
	
	private:
		SwitchableWatermark* fIotdSwitch;
		SwitchableWatermark* fSyncSwitch;
	  SwitchableWatermark* fThumbSwitch;
		Group* fInfoNodes;
};

#endif
