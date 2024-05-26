#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent) : 
	QMainWindow(parent), 
	ui(new Ui::MainWindow) 
{ 
	ui->setupUi(this);
	
	ui->lb_t_saw->setText(_defaultText);
	ui->lv_list->setModel(&_model);
}

MainWindow::~MainWindow() 
{ 
	delete ui;
}

void MainWindow::on_pb_plus_clicked()
{
	auto digit = ui->le_input->text();

	for (auto const c : digit) {
		if (!c.isDigit()) {
			ui->lb_t_saw->setText(tr("You wrote letters, \nnot numbers. \nCan't add"));
			return;
		}
	}

	ui->lb_t_saw->setText(_defaultText);
	_list.push_back(digit);
	_model.setStringList(_list);
}

void MainWindow::on_pb_minus_clicked()
{
	auto selected = ui->lv_list->currentIndex().data();

	if(selected.isNull())
		return;

	_list.removeAt(_list.indexOf(selected.toString()));

	_model.setStringList(_list);
}


void MainWindow::on_pb_saw_clicked()
{
	if(_list.isEmpty())
	{
		ui->lb_t_saw->setText(tr("List is empty"));
		return;
	}

	auto getSaws = [this]() -> std::vector<int> {
		std::vector<int> result;
		for (const auto& c: _list) {
			result.push_back(c.toInt());
		}
		return result;
	};
	std::vector<int> saws = getSaws();

	ui->lb_t_saw->setText(_defaultText);

	int howManySaws = Core::saw(saws);

	ui->label_2->setText(QString::number(howManySaws));
}
