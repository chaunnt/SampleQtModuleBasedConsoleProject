#include "ImageData.h"
#include "SampleModule/SampleModuleDefines.h"

#include <QDebug>

ImageData::ImageData(QObject *parent) : QObject(parent)
{

}

ImageData::ImageData(QString strImgId, QString strImgPath, QString strImgPreview)
{
    m_imageId = strImgId;
    m_imagePath = strImgPath;
    m_imagePreview = strImgPreview;
}

QString ImageData::getImageId()
{
    return m_imageId;
}

QString ImageData::getImagePath()
{
    return m_imagePath;
}

QString ImageData::getImagePreview()
{
    return m_imagePreview;
}

QString ImageData::getImageType()
{
    return m_imageType;
}

QString ImageData::getImageUrl()
{
    return m_imageUrl;
}

QString ImageData::getImageSrc()
{
    if (m_imagePreview != "")
    {
        return m_imagePreview;
    }
    else if (m_imagePath != "")
    {
        return m_imagePath;
    }
    else if (m_imageUrl != "")
    {
        return m_imageUrl;
    }
    return "";
}


void ImageData::setImageId(QString newVal)
{
    m_imageId = newVal;
    emit imageDataChanged();
}

void ImageData::setImagePath(QString newVal)
{
    m_imagePath = newVal;
    emit imageDataChanged();
}

void ImageData::setImagePreview(QString newVal)
{
    m_imagePreview = newVal;
    emit imageDataChanged();
}

void ImageData::setImageType(QString newVal)
{
    m_imageType = newVal;
    emit imageDataChanged();
}

void ImageData::setImageUrl(QString newVal)
{
    m_imageUrl = newVal;
    emit imageDataChanged();
}

void ImageData::importFromJSON(QByteArray jsonData)
{
    QJsonObject jsObj = QJsonDocument::fromJson(jsonData).object();
    importFromJSONObject(jsObj);
}

void ImageData::importFromJSONObject(QJsonObject jsObj)
{
    m_imageUrl = jsObj.value(c_ImageLink).toString();
    int tempimageType = jsObj.value(c_ImageType).toInt();
    if (tempimageType == 1)
    {
        m_imageType = c_ImageType_PNG;
    }
    else if (tempimageType == 2)
    {
        m_imageType = c_ImageType_JPEG;
    }
    else if (tempimageType == 3)
    {
        m_imageType = c_ImageType_GIF;
    }
    m_imageId = QString::number(jsObj.value(c_DataId).toInt());
}

QString ImageData::convertToJSON()
{
    return QJsonDocument(convertToJSONObject()).toJson();
}

QJsonObject ImageData::convertToJSONObject()
{
    QJsonObject jsObj;
    if (m_imageId != DEFAULT_INT_VALUE)
    {
        jsObj[c_DataId] = m_imageId;
    }

    if (m_imageType != DEFAULT_TEXT)
    {
        if (m_imageType == c_ImageType_PNG)
        {
            jsObj[c_ImageType] = 1;
        }
        else if (m_imageType == c_ImageType_GIF)
        {
            jsObj[c_ImageType] = 3;
        }
        else
        {
            jsObj[c_ImageType] = 2;
        }
    }

    if (m_imageUrl != DEFAULT_TEXT)
    {
        jsObj[c_ImageLink] = m_imageUrl;
    }

    return jsObj;
}


