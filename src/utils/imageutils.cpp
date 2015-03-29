#include "imageutils.h"

ImageUtils::ImageUtils()
{

}

ImageUtils::~ImageUtils()
{

}

QMatrix ImageUtils::getImageRotation(QString imagePath) {
    QMatrix rotation = QMatrix();
    ExifData* exifData = exif_data_new_from_file(imagePath.toStdString().c_str());
    if(exifData!=NULL) {
        ExifContent* content = *exifData->ifd;
        ExifEntry* entry = exif_content_get_entry(content,EXIF_TAG_ORIENTATION);
        if(entry!=NULL) {
            std::string orientation = std::string((const char*)entry->data);
            if(orientation=="Rotated 90 CCW") {
                rotation.rotate(90);
            } else if(orientation=="Rotated 90 CW") {
                rotation.rotate(-90);
            } else if(orientation=="Rotated 180") {
                rotation.rotate(180);
            }
        }
        delete exifData;
        delete content;
        delete entry;
    }
    return rotation;
}
