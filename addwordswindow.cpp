#include "addwordswindow.h"
#include "ui_addwordswindow.h"

#include <QMessageBox>

AddWordsWindow::AddWordsWindow(DataBase *_db, QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::AddWordsWindow)
    , db(_db)
{
    ui->setupUi(this);
}

AddWordsWindow::~AddWordsWindow() {
    delete ui;
}

void AddWordsWindow::Exec() {
    ui->ruWordEdit->setText("");
    ui->deWordEdit->setText("");
    ui->ruWordEdit->setFocus();
    exec();
}

void AddWordsWindow::keyPressEvent(QKeyEvent *event) {
    if ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
        ui->addButton->clicked();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void AddWordsWindow::on_addButton_clicked() {
    QString ru_word = ui->ruWordEdit->text().simplified();
    QString de_word = ui->deWordEdit->text().simplified();

    if (ru_word.size() == 0 || de_word.size() == 0) {
        QMessageBox msgBox;
        msgBox.setText("All words should be not empty!");
        msgBox.exec();
    } else {
        if (db->AddEntry(ru_word, de_word)) {
            QMessageBox msgBox;
            msgBox.setText(QString("Add entry (%1, %2) failed!").arg(ru_word).arg(de_word));
            msgBox.exec();
        }
        ui->ruWordEdit->setText("");
        ui->ruWordEdit->setFocus();
        ui->deWordEdit->setText("");
    }
}
