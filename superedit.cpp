#include "superedit.h"
#include "ui_superedit.h"

#include <QComboBox>


SuperEdit::SuperEdit(QWidget *parent) :
    QLineEdit(parent),
    ui(new Ui::SuperEdit)
{
    ui->setupUi(this);
    ui->lineEdit->installEventFilter(this);
}

SuperEdit::~SuperEdit() {
    delete ui;
}


QString SuperEdit::text() {
    return ui->lineEdit->text();
}

void SuperEdit::setText(const QString &str) {
    ui->lineEdit->setText(str);
}

void SuperEdit::setFocusOnEdit() {
    ui->lineEdit->setFocus();
}

void SuperEdit::setButtonsVisable(bool enable){
    ui->printAeButton->setVisible(enable);
    ui->printOeButton->setVisible(enable);
    ui->printUeButton->setVisible(enable);
    ui->printSsButton->setVisible(enable);
}

bool SuperEdit::eventFilter(QObject *obj, QEvent *event) {
    if (obj != ui->lineEdit || event->type() != QEvent::KeyPress) {
        return QObject::eventFilter(obj, event);
    }

    QKeyEvent *keyEvent = (QKeyEvent *)event;
    if (keyEvent->modifiers() != Qt::AltModifier || !ui->printAeButton->isVisible()) {
        return QObject::eventFilter(obj, event);
    }

    switch (keyEvent->key()) {
    case Qt::Key_A:
        ui->lineEdit->insert(ui->printAeButton->text().simplified());
        ui->lineEdit->setFocus();
        break;
    case Qt::Key_O:
        ui->lineEdit->insert(ui->printOeButton->text().simplified());
        ui->lineEdit->setFocus();
        break;
    case Qt::Key_U:
        ui->lineEdit->insert(ui->printUeButton->text().simplified());
        ui->lineEdit->setFocus();
        break;
    case Qt::Key_S:
        ui->lineEdit->insert(ui->printSsButton->text().simplified());
        ui->lineEdit->setFocus();
        break;
    }
    return true;
}

SuperEditDelegate::SuperEditDelegate(QObject *parent) : QItemDelegate(parent) {}

QWidget* SuperEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const {
    return new SuperEdit(parent);
}

void SuperEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QString value = index.model()->data(index).toString();
    SuperEdit *edit = static_cast<SuperEdit*>(editor);
    edit->ui->lineEdit->setText(value);
}

void SuperEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    SuperEdit *edit = static_cast<SuperEdit*>(editor);
    model->setData(index, edit->ui->lineEdit->text().toLower());
}

void SuperEdit::on_printAeButton_clicked() {
    ui->lineEdit->insert(ui->printAeButton->text().simplified());
    ui->lineEdit->setFocus();
}

void SuperEdit::on_printOeButton_clicked() {
    ui->lineEdit->insert(ui->printOeButton->text().simplified());
    ui->lineEdit->setFocus();
}

void SuperEdit::on_printUeButton_clicked() {
    ui->lineEdit->insert(ui->printUeButton->text().simplified());
    ui->lineEdit->setFocus();
}

void SuperEdit::on_printSsButton_clicked() {
    ui->lineEdit->insert(ui->printSsButton->text().simplified());
    ui->lineEdit->setFocus();
}

void SuperEdit::on_lineEdit_textChanged(const QString &arg1) {
    textChanged(arg1);
}

TopicColumnDelegate::TopicColumnDelegate(DataBase *db, QObject *parent)
    : QItemDelegate(parent)
    , db_(db)
{}

QWidget* TopicColumnDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const {
    QComboBox *topicBox = new QComboBox(parent);
    topicBox->setEditable(true);
    return topicBox;
}

void TopicColumnDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QString value = index.model()->data(index).toString().toUpper();
    QComboBox *topicBox = static_cast<QComboBox*>(editor);

    QSet<QString> topics;
    db_->GetTopicsList(topics);
    for (const auto& topic : topics) {
        topicBox->addItem(topic);
    }

    QSortFilterProxyModel *topicProxy = new QSortFilterProxyModel(topicBox);
    topicProxy->setSourceModel(topicBox->model());
    topicBox->model()->setParent(topicProxy);
    topicBox->setModel(topicProxy);
    topicBox->model()->sort(0);

    topicBox->setCurrentText(value);
}

void TopicColumnDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QComboBox *topicBox= static_cast<QComboBox*>(editor);
    model->setData(index, topicBox->currentText().toUpper());
}

