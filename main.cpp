#include <QtGui>
#include <QtWidgets>

int main(int argc, char ** argv) {
	QApplication app(argc, argv);
	QApplication::setFont(QFont("Arial", 20));

	auto lineEdit = new QLineEdit();
	lineEdit->setAlignment(Qt::AlignHCenter);
	auto completer = new QCompleter({"thunar", "firefox", "urxvt", "subl3", "chromium", "qbittorrent", "skype"});
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
