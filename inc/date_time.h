#pragma once

#include <QDateTime>

#include <QDebug>   
#include <QObject>
#include <QString>
#include <QJSValue>
#include <QJSValueList>
#include <QJSEngine>

class MyDateTime : public QObject {
    Q_OBJECT

    public:

        MyDateTime(QJSValueList args, QObject* parent = nullptr );

        Q_INVOKABLE void now();
        Q_INVOKABLE QString toString() const;
        Q_INVOKABLE QString toString(const QString&) const;
        
        ~MyDateTime() {
            qDebug() << "MyDateTime destructor called";           
        }
    private:
        QDateTime date_time_;
 };

class MyDateTimeFactory : public QObject {
    Q_OBJECT

    QJSEngine& engine_;

    public:
    MyDateTimeFactory(QJSEngine& engine, QObject* parent = nullptr)
        : engine_{engine} {}

    Q_INVOKABLE QJSValue create(QJSValueList args);
};