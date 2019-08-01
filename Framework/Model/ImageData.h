#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include "SimpleData.h"
#include "Framework/GlobalDefine.h"

class ImageData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString imageId MEMBER m_imageId NOTIFY imageDataChanged)
    Q_PROPERTY(QString imagePath MEMBER m_imagePath NOTIFY imageDataChanged)
    Q_PROPERTY(QString imagePreview MEMBER m_imagePreview NOTIFY imageDataChanged)
    Q_PROPERTY(QString imageType MEMBER m_imageType NOTIFY imageDataChanged)
    Q_PROPERTY(QString imageUrl MEMBER m_imageUrl NOTIFY imageDataChanged)
    Q_PROPERTY(QString imageSrc READ getImageSrc NOTIFY imageDataChanged)

    QString m_imageId = "";
    QString m_imagePath = "";
    QString m_imagePreview = "";
    QString m_imageType = "";
    QString m_imageUrl = "";
public:
    explicit ImageData(QObject *parent = nullptr);
    ImageData(QString strImgId, QString strImgPath, QString strImgPreview);
    QString getImageId();
    QString getImagePath();
    QString getImagePreview();
    QString getImageType();
    QString getImageUrl();
    QString getImageSrc();


    void setImageId(QString newVal);
    void setImagePath(QString newVal);
    void setImagePreview(QString newVal);
    void setImageType(QString newVal);
    void setImageUrl(QString newVal);

    void importFromJSON(QByteArray jsonData);
    void importFromJSONObject(QJsonObject jsObj);

    QString convertToJSON();
    QJsonObject convertToJSONObject();

signals:
    void imageDataChanged();

public slots:
};
