#pragma once

#include <QObject>
#include <memory>

class DataAnalyzersInterface;
class DataCollectorInterface;
class DataDistributorInterface;
class AppManager : public QObject
{
    Q_OBJECT

public:
    explicit AppManager(QObject *parent = nullptr);

    void Initialize();

    void startService();

private:
    DataAnalyzersInterface* m_pDataAnalyzersInterface;
    DataCollectorInterface* m_pDataCollectorInterface;
    DataDistributorInterface* m_pDataDistributorInterface;

    Q_SLOT void _onDataCollected(QByteArray data);
};
