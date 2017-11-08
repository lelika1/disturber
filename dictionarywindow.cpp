#include "dictionarywindow.h"
#include "ui_dictionarywindow.h"

#include "addwordswindow.h"
#include "superedit.h"

#include <QCloseEvent>
#include <QItemDelegate>

class NotEditableDelegate : public QItemDelegate {
public:
    NotEditableDelegate(QObject *parent = 0)
        : QItemDelegate(parent)
    {}

    bool editorEvent(QEvent */*event*/, QAbstractItemModel */*model*/, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const {
        return false;
    }

    QWidget *createEditor(QWidget */*obj*/, const QStyleOptionViewItem &/**/, const QModelIndex &/**/) const {
        return nullptr;
    }
};

DictionaryWindow::DictionaryWindow(DataBase *_db, QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::DictionaryWindow)
    , db(_db)
{
    sql_model.reset(new QSqlTableModel);
    sql_model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->setupUi(this);
    ui->dictTableView->setModel(sql_model.get());
    ui->dictTableView->setItemDelegateForColumn(2, new SuperEditDelegate(this));
    ui->dictTableView->setItemDelegateForColumn(3, new TopicColumnDelegate(db, this));
    ui->dictTableView->setItemDelegateForColumn(4, new NotEditableDelegate(this));
    ui->dictTableView->setItemDelegateForColumn(5, new NotEditableDelegate(this));
}

DictionaryWindow::~DictionaryWindow() {
    delete ui;
}

void DictionaryWindow::Exec() {
    ui->findEdit->setText("");
    ui->dictTableView->show();
    RefreshTable();
    this->exec();
}

void DictionaryWindow::RefreshTable() {
    QString findStr = ui->findEdit->text().simplified().toLower();
    db->LoadEntriesWithFilter(sql_model.get(), findStr);
    ui->dictTableView->hideColumn(0);
}

void DictionaryWindow::on_findEdit_textChanged(const QString &) {
    RefreshTable();
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
    AddWordsWindow add_words_form(db);
    add_words_form.Exec();
    RefreshTable();
}
