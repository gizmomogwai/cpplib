#ifndef JpegImage_h_
#define JpegImage_h_

#include <image/ImageApi.h>

#include <io/file/File.h>
#include <image/codecs/JpegImageCodec.h>
#include <ExifTypeDefs.h>

class Date;
class Rotation;

class IMAGE_API JpegImage {
  public:
    JpegImage(const File& file);

    virtual ~JpegImage();

    void rotateLeft();

    void rotateRight();

    void normalizeRotation();
    void resetRotation();

    bool isExifDateInSyncWithFileDate();

    void adjustFileDateFromExifDate();

    Date* getExifDate();

    void setExifDate(const Date& date);
    void setDateTimeDigitized(const Date& date);
    void setDateTimeOriginal(const Date& date);
    /**
     * Returns the Thumbnail of a Jpeg (0 if there is no thumbnail stored)
     */
    Image* getThumbnail();

    void setThumbnail(Image& image);

   private:
     void setTagByDate(unsigned int tag, ExifTagLocation location, const Date& d);

     File fFile;

     // void rotate(JXFORM_CODE transform);

     static const char* format;
     static const char* easyFormat;

     Rotation* getRotation();

     void setRotation(int rotation);
     static std::string date2String(const Date& date);

};

#endif
