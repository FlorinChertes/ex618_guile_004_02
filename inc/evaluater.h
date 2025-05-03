#pragma once

#include <QDebug>
#include <QString>

#include <QJSValue>
#include <QJSEngine>

QJSValue evaluater(QJSEngine& engine, QString script) {
		
	QStringList exceptionStackTrace{};
	QJSValue result = engine.evaluate(script, "script", 1, &exceptionStackTrace);
	if (result.isError()) {
		qWarning() << "Error evaluating script:" << engine.evaluate("Error").toString();
		for (const auto& exception : exceptionStackTrace) {
			qWarning() << "Exception:" << exception;
		}
	}

	return result;
}
