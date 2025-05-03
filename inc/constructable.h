#include "evaluater.h"
#include "caller.h"

#include <QDebug>
#include <QObject>
#include <QString>
#include <QJSValue>
#include <QJSEngine>

template<typename T>
struct Constructable {

    static_assert(std::is_base_of_v<QObject, T>, "T must be derived from QObject");

    #if defined(__clang__ ) || defined(__GNUC__)
        inline static const QString startSig{"T = "};
        inline static const QString endSig{"]"};        
    #elif defined (_MSC_VER)
        inline static const QString startSig{"Constructable<class "}; 
        inline static const QString endSig{">::create"};    
    #endif

    void create(QJSEngine& engine, T* obj) {

#if defined(__clang__ ) || defined(__GNUC__)
    QString fungSig = __PRETTY_FUNCTION__;
#elif defined (_MSC_VER)
    QString fungSig = __FUNCSIG__;        
#else
     QString fungSig = typeid(T).name(); // Fallback for other compilers     
#endif

        int start = fungSig.indexOf(startSig) + startSig.length();
        int end = fungSig.indexOf(endSig, start);
        
        const QString propertyName = fungSig.mid(start, end - start);
        qDebug() << "property name:" << propertyName;

        QString className{propertyName};
        className.replace("Factory", "");
        qDebug() << "class name:" << className;
       
        QJSValue myMetaClass = engine.newQObject(obj);
        engine.globalObject().setProperty(propertyName, myMetaClass);
        qDebug() << "create function:" << propertyName << "class name:" << className;

        QString jsWraperScript = QString(
            R"~(
            function %2(...args) { return %1.create(args); }
            )~"
        ).arg(propertyName).arg(className);

        Evaluater evaluater{};
        Caller caller{};
        QJSValue result = caller(evaluater(engine, jsWraperScript), engine.globalObject());
    }   
};