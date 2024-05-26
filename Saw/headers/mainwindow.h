#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

private:
	QStringList _list;
	QStringListModel _model;
	QString _defaultText = "Longest saw's length is:";

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow() override;

private slots:
	void on_pb_plus_clicked();

	void on_pb_minus_clicked();

	void on_pb_saw_clicked();

private:
	Ui::MainWindow *ui;
};
#endif	// MAINWINDOW_H
