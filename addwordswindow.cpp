#include "addwordswindow.h"
#include "ui_addwordswindow.h"

#include <QMessageBox>


AddWordsWindow::AddWordsWindow(DataBase *_db, QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::AddWordsWindow)
    , db(_db)
{
    ui->setupUi(this);
    db->GetTopicsList(topics);
}

AddWordsWindow::~AddWordsWindow() {
    delete ui;
}

void AddWordsWindow::Exec() {
    for (const auto& topic : topics) {
        ui->topicsComboBox->addItem(topic);
    }

    QSortFilterProxyModel proxy(ui->topicsComboBox);
    proxy.setSourceModel(ui->topicsComboBox->model());
    ui->topicsComboBox->model()->setParent(&proxy);
    ui->topicsComboBox->setModel(&proxy);
    ui->topicsComboBox->model()->sort(0);

    ui->topicsComboBox->setCurrentText("ANDERE");

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
    QString topic = ui->topicsComboBox->currentText().simplified().toUpper();
    topic = (topic.size() != 0)? topic : "ANDERE";

    if (ru_word.size() == 0 || de_word.size() == 0) {
        QMessageBox msgBox;
        msgBox.setText("All words should be not empty!");
        msgBox.exec();
    } else {
        if (db->AddEntry(ru_word, de_word, topic)) {
            QMessageBox msgBox;
            msgBox.setText(QString("Add entry (%1, %2) failed!").arg(ru_word).arg(de_word));
            msgBox.exec();
        }
        if (topics.find(topic) == topics.end()) {
            topics.insert(topic);
            ui->topicsComboBox->addItem(topic);
        }

        ui->ruWordEdit->setText("");
        ui->deWordEdit->setText("");
        ui->ruWordEdit->setFocus();
    }
}
