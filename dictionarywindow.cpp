#include "dictionarywindow.h"
#include "ui_dictionarywindow.h"

#include "superedit.h"

#include <QCloseEvent>

DictionaryWindow::DictionaryWindow(DataBase *_db, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DictionaryWindow)
    , db(_db)
    , add_words_form(_db)
{
    sql_model = new QSqlTableModel;
    sql_model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->setupUi(this);
    ui->dictTableView->setModel(sql_model);
    ui->dictTableView->setItemDelegateForColumn(2, new SuperEditDelegate(this));
}

DictionaryWindow::~DictionaryWindow() {
    delete ui;
}

void DictionaryWindow::Show() {
    ui->findEdit->setText("");
    this->show();
    db->LoadAllEntriesToModel(sql_model);
    ui->dictTableView->hideColumn(0);
    ui->dictTableView->show();
}

void DictionaryWindow::on_findEdit_textChanged(const QString &arg1) {
    db->LoadEntriesWithFilter(sql_model, arg1.simplified());
    ui->dictTableView->hideColumn(0);
}

void DictionaryWindow::on_deleteWordsButton_clicked() {
    QModelIndexList selectedItems = ui->dictTableView->selectionModel()->selectedIndexes();
    if (selectedItems.size() != 1) {
        qDebug() << "Fail. Currently selected " << selectedItems.size() << " items\n";
        return;
    }

    sql_model->removeRow(selectedItems[0].row());
}

void DictionaryWindow::on_addWordsButton_clicked() {
    QRect g = add_words_form.geometry();
    add_words_form.setGeometry(QRect((geometry().width()  -  g.width())/2,
                                     (geometry().height() - g.height())/2,
                                     g.width(), g.height()));
    add_words_form.show();
}
