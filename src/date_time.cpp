#include "date_time.h"


MyDateTime::MyDateTime(QJSValueList args, QObject* parent) 
: QObject(parent)
, date_time_{}
{
    qDebug() << "MyDateTime constructor called";
    if(args.size() > 0)
    {
    
        if(args.size() <= 3)
        {
            uint64_t year{}, month{}, day{};
            if(args.size() == 1)
            {
                year = args.at(0).toInt();
                month = 1;
                day = 1;
            }
            else if(args.size() == 2)
            {
                year = args.at(0).toInt();
                month = args.at(1).toInt();
                day = 1;
            }
            else if(args.size() == 3)
            {
                year = args.at(0).toInt();
                month = args.at(1).toInt();
                day = args.at(2).toInt();

                date_time_ = QDateTime(QDate(year, month, day),QTime{});
            }
        }
        else if(args.size() == 6)
        {
            uint64_t year{}, month{}, day{};
            uint64_t hour{}, minute{}, second{};
            year = args.at(0).toInt();
            month = args.at(1).toInt();
            day = args.at(2).toInt();
            hour = args.at(3).toInt();
            minute = args.at(4).toInt();
            second = args.at(5).toInt();

            date_time_ = QDateTime(QDate(year, month, day), QTime(hour, minute, second));
        }
    }
}

void MyDateTime::now() 
{
    qDebug() << "MyDateTime::now() called";
    date_time_ = QDateTime::currentDateTime();
 }

QString MyDateTime::toString() const
{
    qDebug() << "MyDateTime::toString() called";
    return date_time_.toString("dd.MM.yyyy hh:mm:ss");
}

QString MyDateTime::toString(const QString& format) const
{
    qDebug() << "MyDateTime::toString(format) called";
    return date_time_.toString(format);
}

QJSValue MyDateTimeFactory::create(QJSValueList args)
{
    qDebug() << "MyDateTimeFactory::create() called";
    return engine_.newQObject(new MyDateTime(args));
}