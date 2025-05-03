#pragma

#include "evaluater.h"
#include "caller.h"

#include <QDebug>
#include <QString>

#include <QJSValue>
#include <QJSEngine>

#if defined(__clang__ ) || defined(__GNUC__)
    static const QString startSig{"T = "};
    static const QString endSig{"]"};
#elif defined (_MSC_VER)
    static const QString startSig{"Constructable<class "};
    static const QString endSig{">::create"};
#endif

template<typename T>
concept FromQObjectInheritedAndHasFuncCreate = requires(T t, QJSValueList args) {
    std::is_base_of_v<QObject, T>;
    { t.create(args) } -> std::same_as<QJSValue>;
};

template<FromQObjectInheritedAndHasFuncCreate T>
void expose_factory_to_engine(QJSEngine& engine, T* obj)
{

#if defined(__clang__ ) || defined(__GNUC__)
    QString fungSig = __PRETTY_FUNCTION__;
#elif defined (_MSC_VER)
    QString fungSig = __FUNCSIG__;        
#else
     QString fungSig = typeid(T).name(); // Fallback for other compilers     
#endif

    const int start = fungSig.indexOf(startSig) + startSig.length();
    const int end = fungSig.indexOf(endSig, start);

    const QString exposed_obj_name = fungSig.mid(start, end - start);
    qDebug() << "exposed object name:" << exposed_obj_name;

    QString exposed_name{exposed_obj_name};
    exposed_name.replace("Factory", "");
    qDebug() << "exposed name:" << exposed_name;

    QJSValue exposed_obj = engine.newQObject(obj);
    engine.globalObject().setProperty(exposed_obj_name, exposed_obj);


    QString jsWraperScript = QString(
        R"~(
        function %2(...args) { return %1.create(args); }
        )~"
    ).arg(exposed_obj_name).arg(exposed_name);

    QJSValue result = caller(evaluater(engine, jsWraperScript), engine.globalObject());
}
