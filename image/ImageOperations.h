#ifndef ImageOperations_h_
#define ImageOperations_h_

#include <image/ImageApi.h>

#include <image/Image.h>

class IMAGE_API ImageOperations {
  public:
    /** rotates the image 90 degrees to the left.
     * @param original original image.
     * @return Image* new rotated image.
     */
    static Image* rotateLeft(Image& original);

    /** rotates the image 90 degrees to the right.
     * @param original original image.
     * @return Image* new rotated image.
     */
    static Image* rotateRight(Image& original);
    
    /** scales the image to a thumbnail.
     * @param image the image to scale.
     * @param width the width of the thumb (the height is proprtional).
     * @return Image* new resized image.
     */
    static Image* getThumbnail(Image& image, int width);
    
    static Image* getImageAsRGBA(Image& image);

};

#endif
