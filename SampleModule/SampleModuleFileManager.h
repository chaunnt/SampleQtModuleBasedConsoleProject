#pragma once

#include "Framework/SystemFile/FileManagerBase.h"

#include <QObject>

class SampleModuleFileManager : public FileManagerBase
{
    Q_OBJECT
public:
    explicit SampleModuleFileManager(QObject *parent = nullptr);

};
