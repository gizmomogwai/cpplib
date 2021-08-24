#ifndef _JasperRuntime_h_
#define _JasperRuntime_h_

#include <image/ImageApi.h>

#include <jasper/jasper.h>

class IMAGE_API JasperRuntime {

public:
	static void init() {
		if (inited == false) {
			inited = true;
			jas_init();
		}
	}
	
private:
	static bool inited;

};


#endif // _JasperRuntime_h_
