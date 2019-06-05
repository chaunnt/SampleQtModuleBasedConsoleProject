#ifndef APPUSER_H
#define APPUSER_H

#include <QObject>

class AppUser : public QObject
{
    Q_OBJECT
    QString m_Email;
    QString m_Password;
public:
    explicit AppUser(QObject *parent = nullptr);
    AppUser(QString strEmail, QString strPassword);
    QString getEmail();
    QString getPassword();

    void setEmail(QString newVal);
    void setPassword(QString newVal);
signals:

public slots:
};

#endif // APPUSER_H
