#pragma once

#include <QDebug>
#include <QJSValue>
#include <QJSValueList>

QJSValue caller(const QJSValue& func)
{
    QJSValue result = func.call();
    if (result.isError()) {
        qWarning() << "Error evaluating script:" << result.toString();
    }
    return result;
}

QJSValue caller(const QJSValue& func, const QJSValue& instance,  const QJSValueList& arg = {} )
{
    QJSValue result = func.callWithInstance(instance, arg);
    if (result.isError()) {
        qWarning() << "Error evaluating script:" << result.toString();
    }
    return result;
}
