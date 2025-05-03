#pragma once

#include <QObject>
#include <QDebug>
#include <QString>  

class ConsoleLogger : public QObject {
    Q_OBJECT

public slots:

    void log (const QString& message) {
        qDebug() << "[JS]" << message;
    }
};