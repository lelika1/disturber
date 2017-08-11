#include "superedit.h"
#include "ui_superedit.h"

SuperEdit::SuperEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuperEdit)
{
    ui->setupUi(this);
}

SuperEdit::~SuperEdit()
{
    delete ui;
}

SuperEditDelegate::SuperEditDelegate(QObject *parent) : QItemDelegate(parent) {}

QWidget* SuperEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const {
    return new SuperEdit(parent);
}

void SuperEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QString value = index.model()->data(index).toString();
    SuperEdit* edit = static_cast<SuperEdit*>(editor);
    edit->ui->lineEdit->setText(value);
}

void SuperEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    SuperEdit* edit = static_cast<SuperEdit*>(editor);
    model->setData(index, edit->ui->lineEdit->text());
}

void SuperEdit::on_printAeButton_clicked()
{
    ui->lineEdit->insert(ui->printAeButton->text().simplified());
    ui->lineEdit->setFocus();
}

void SuperEdit::on_printOeButton_clicked()
{
    ui->lineEdit->insert(ui->printOeButton->text().simplified());
    ui->lineEdit->setFocus();
}

void SuperEdit::on_printUeButton_clicked()
{
    ui->lineEdit->insert(ui->printUeButton->text().simplified());
    ui->lineEdit->setFocus();
}

void SuperEdit::on_printSsButton_clicked()
{
    ui->lineEdit->insert(ui->printSsButton->text().simplified());
    ui->lineEdit->setFocus();
}
