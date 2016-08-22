#include <vecmath/Color3f.h>


Color3f* Color3f::createFromHSB(float hue, float saturation, float brightness) {
  float r = 0;
  float g = 0;
  float b = 0;
  if (saturation == 0.0) {
    r = brightness;
    g = r;
    b = r;
  } else {
    float h = hue;
	  float p = brightness * (1.0f - saturation);
	  float q = brightness * (1.0f - saturation * h);
	  float t = brightness * (1.0f - (saturation * (1.0f - h)));
    if (h >= 0 && h < 60) {
		    r = brightness;
		    g = t;
		    b = p;
    } else if (h >= 60 && h < 120) {
        r = q;
		    g = brightness;
		    b = p;
    } else if (h >= 120 && h < 180) {
		    r = p;
		    g = brightness;
		    b = t;
    } else if (h >= 180 && h < 240) {
		    r = p;
		    g = q;
		    b = brightness;
    } else if (h >= 240 && h < 300) {
		    r = t;
		    g = p;
		    b = brightness;
    } else if (h >= 300 && h < 360) {
 		    r = brightness;
		    g = p;
		    b = q;
	  }
	}
  return(new Color3f(r, g, b));
}
