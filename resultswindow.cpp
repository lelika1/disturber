#include "resultswindow.h"
#include "superedit.h"
#include "ui_resultswindow.h"

ResultsWindow::ResultsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultsWindow)
{
    ui->setupUi(this);
}

ResultsWindow::~ResultsWindow() {
    delete ui;
}

void ResultsWindow::Exec(QAbstractTableModel *model) {
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegateForColumn(1, new SuperEditDelegate(this));
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setColumnWidth(0, std::max(250, ui->tableView->columnWidth(0)));
    ui->tableView->setColumnWidth(1, std::max(250, ui->tableView->columnWidth(1)));

    exec();
}

void ResultsWindow::on_submitBtn_clicked() {
    close();
}
