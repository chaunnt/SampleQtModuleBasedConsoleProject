#pragma once

#include <QObject>

class ApplicationInitializer : public QObject
{
    Q_OBJECT
public:
    enum class State
    {
        NotStarted,
        InitialisingSettings,
        Complete
    };

    explicit ApplicationInitializer(QObject *parent = nullptr);

    void startStartupSequence();

private:
    State m_State;
};
