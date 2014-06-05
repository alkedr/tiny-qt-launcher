#include <QtGui>
#include <QtWidgets>

static QStringList getCompleterList() {
	QStringList result;

	QFile configFile(QStringLiteral("/home/alkedr/.config/tiny-qt-launcher"));
	if (!configFile.open(QIODevice::ReadOnly)) {
		qWarning("Couldn't open config file.");
		return result;
	}
	auto json = QJsonDocument(QJsonDocument::fromJson(configFile.readAll())).object();

	QJsonArray levelArray = json["programs"].toArray();
	for (QJsonValue programValue : levelArray) {
		qDebug() << programValue.toString();
		result.push_back(programValue.toString());
	}

	return result;
}

int main(int argc, char ** argv) {
	QApplication app(argc, argv);
	QApplication::setFont(QFont("Arial", 20));

	auto lineEdit = new QLineEdit();
	lineEdit->setAlignment(Qt::AlignHCenter);
	auto completer = new QCompleter(getCompleterList());
	completer->setCompletionMode(QCompleter::InlineCompletion);
	lineEdit->setCompleter(completer);

	QObject::connect(lineEdit, &QLineEdit::returnPressed,
		[lineEdit]() {
			(new QProcess())->start(lineEdit->text());
			QCoreApplication::quit();
		}
	);

	lineEdit->show();
	return app.exec();
}
