#include "widget_factory_04.h"

#include "console_logger.h"

#include "evaluater.h"
#include "caller.h"

#include "constructable.h"

#include <QMessageBox>

#include <qDebug>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
MyFunctions::MyFunctions() { qDebug() << "ctor called"; }
MyFunctions::~MyFunctions() { qDebug() << "dtor called"; }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QJSValue MyFunctions::getTheName() const
{
	return the_name_;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MyFunctions::setTheName(QJSValue name_)
{
	the_name_ = name_.toString();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Widget_factory::Widget_factory(QObject* parent)
	: QObject(parent)
	, widgets {}
	, engine {}
	, my_date_time_factory_{engine}
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Widget_factory::setup_engine()
{
	qDebug() << "\n*** instantiate a class and expose it to QScriptEngine  ***";
	// Create a instance of a class
	auto my_funcs_ptr { new MyFunctions {} };
	// Expose the instance to QScriptEngine
	my_funcs_ptr->the_exposed_obj_ = engine.newQObject(my_funcs_ptr);
	engine.globalObject().setProperty("myFuncs", my_funcs_ptr->the_exposed_obj_);

	{
		qDebug() << "\n*** expose to QScriptEngine the named function: function(x) {return x + this.the_name} ***";
		QString script = R"(
			(function(x) {
				return x + this.the_name + "gut!<";
			})
		)";
		// Evaluate the script, loading the function into the QScriptEngine
		my_funcs_ptr->the_add_name_function_ = engine.evaluate(script);
		if (my_funcs_ptr->the_add_name_function_.isError()) {
			qWarning() << "Error evaluating function script:" << engine.evaluate("Error").toString();
		}
	}

	{
		qDebug() << "\n*** a named function: this.a_named_function = function(x) {return x + this.the_name} ***";
		QString script = R"(
			this.a_named_function = (function(x) {
				return x + this.the_name + "gut!<";
			})
		)";
		// Evaluate the script, loading the function into the QScriptEngine
		my_funcs_ptr->the_named_function_ = engine.evaluate(script);
	}

	{
		qDebug() << "\n*** expose ConsoleLoger ***";
		auto jsLogger {engine.newQObject(new ConsoleLogger{})};

		auto console {engine.newObject()};
		console.setProperty("log", jsLogger.property("log"));
		engine.globalObject().setProperty("console", console);
		qDebug() << "ConsoleLogger exposed to QScriptEngine";
		qDebug() << "console.log function:" << console.property("log").isCallable();
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Widget_factory::setup_date_time()
{
	qDebug() << "\n*** expose the MyDateTime Factory to the engine ***";
	expose_factory_to_engine(engine, &my_date_time_factory_);
	qDebug() << "\n*** End of setup date time ***";
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QVBoxLayout* Widget_factory::get_layout() const
{
	return qobject_cast<QVBoxLayout*>(
		engine.globalObject().property("theLayoutObject").toQObject());
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Widget_factory::build_layout()
{
	QVBoxLayout* layout{ new QVBoxLayout() };
	QJSValue layoutObject = engine.newQObject(layout);
	engine.globalObject().setProperty("theLayoutObject", layoutObject);

	createButton("Click this");
	createButton("Click that");

	for (QWidget* widget : widgets) {
		layout->addWidget(widget);
	}

	QPushButton* button_this = qobject_cast<QPushButton*>(widgets.at(0));
	connect(button_this, &QPushButton::clicked,
		this, &Widget_factory::onButtonClickted_this);

	QPushButton* button_that = qobject_cast<QPushButton*>(widgets.at(1));
	connect(button_that, &QPushButton::clicked,
		this, &Widget_factory::onButtonClickted_that);

	qDebug() << "Layout and buttons built.";
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Widget_factory::createButton(const QString& text)
{
	QPushButton* button{ new QPushButton{text} };
	widgets.append(button);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Widget_factory::onButtonClickted_this()
{
	QMessageBox::information(nullptr, "Button Clicked", "Buton clicked this!");
	qDebug() << "Buton clicked this!";
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Widget_factory::onButtonClickted_that()
{
	QMessageBox::information(nullptr, "Button Clicked", "Buton clicked that!");
	qDebug() << "Buton clicked that!";

	{
		qDebug() << "\n*** script QScriptEngine using a function adding the_name of an instance variable ***";

		QString func_script{ R"(
		myFuncs.the_name = "Flori ";
		var the_sum = myFuncs.add_the_name(">Laur ");
		the_sum;
		)" };

		QJSValue result = engine.evaluate(func_script);
		if (result.isError()) {
			qWarning() << "Error evaluating func_script:" << engine.evaluate("Error").toString();
		}
		else
		{
			qDebug() << "Result of Laur + Flori is: " << result.toString();
		}
	}

	{
		qDebug() << "\n*** script QJSEngine call the named function ***";

		QString func_script{ R"(
		myFuncs.the_name = "Flori ";
		var the_sum = myFuncs.call_the_name_fuction(">Laur ");
		the_sum;
		)" };

		QJSValue result = engine.evaluate(func_script);
		qDebug() << "Result named function is: " << result.toString();
	}

	{
		qDebug() << "evaluate script with MyDateTime";
		const QString script{ R"~(

			var js_obj_01 = new MyDateTime(2023, 10, 1);
			console.log("myDateTime(2023, 10, 1).toString(): " + js_obj_01.toString());

			var js_obj_02 = new MyDateTime();
			js_obj_02.now()
			console.log("now(): " + js_obj_02.toString());

			var js_obj_03 = new MyDateTime(2023, 5, 15, 12, 30, 45);
			console.log("myDateTime(2023, 5, 15, 12, 30, 45).toString(): " + js_obj_03.toString());

			var js_obj_04 = MyDateTime(2023, 5, 16, 13, 31, 46);
			console.log("myDateTime(2023, 5, 16, 13, 31, 46).toString(): " + js_obj_04.toString());

			console.log("myDateTime(2023, 10, 1).toString(): " + js_obj_01.toString());

		)~" };
		QJSValue result = evaluater(engine, script);
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QJSValue MyFunctions::add_the_name(const QJSValue& a)
{
	// We want to call the JS function with `this = the_exposed_obj_`
	// plus the single argument `a`.
	QJSValueList args;
	args << a;

	QJSValue result = the_add_name_function_.callWithInstance(the_exposed_obj_, args);
	return result;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QJSValue MyFunctions::call_the_name_fuction(const QJSValue& a)
{
	QJSValue result{};

	if (the_named_function_.isCallable())
	{
		QJSValueList args;
		args << a;
		result = the_named_function_.callWithInstance(the_exposed_obj_, args);
	}

	return result;
}
