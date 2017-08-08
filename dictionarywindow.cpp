#include "dictionarywindow.h"
#include "ui_dictionarywindow.h"
#include "superedit.h"

#include <QMessageBox>
#include <QCloseEvent>

DictionaryWindow::DictionaryWindow(DataBase *_db, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DictionaryWindow)
    , db(_db)
{
    sql_model = new QSqlTableModel;
    sql_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->setupUi(this);
    ui->dictTableView->setModel(sql_model);
    ui->dictTableView->setItemDelegateForColumn(2, new SuperEditDelegate(this));
}

DictionaryWindow::~DictionaryWindow()
{
    delete ui;
}

void DictionaryWindow::ShowTable() {
    this->show();
    db->ShowAllEntries(sql_model);

    ui->dictTableView->hideColumn(0);
    ui->dictTableView->show();
}

void DictionaryWindow::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Save", "Save changes?",
                                                              QMessageBox::No|QMessageBox::Yes);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        if (!sql_model->submitAll()) {
            qDebug() << "Submit all FAILED!!!!!!\n";
        }
    } else {
        qDebug() << "No was clicked";
        sql_model->revertAll();
    }
    event->accept();
}

void DictionaryWindow::on_saveButton_clicked()
{
    if (!sql_model->submitAll()) {
        qDebug() << "Submit all FAILED!!!!!!\n";
    }
}

void DictionaryWindow::on_findButton_clicked()
{

}

void DictionaryWindow::on_revertButton_clicked()
{
    sql_model->revertAll();
}
