#include "startwindow.h"
#include "ui_startwindow.h"

#include "dictionarywindow.h"
#include "settings.h"
#include "setupstudywindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QMessageBox>

#include <memory>

StartWindow::StartWindow(DataBase *_db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
    , db(_db)
{
    ui->setupUi(this);
}

StartWindow::~StartWindow() {
    delete ui;
}


void StartWindow::on_studyButton_clicked() {
    std::unique_ptr<SetupStudyWindow> setup_window_ptr(new SetupStudyWindow(db));
    setup_window_ptr->Exec();
}

void StartWindow::on_action_Options_triggered() {
    Settings options_form;
    options_form.Exec();
}

void StartWindow::on_actionEdit_dictionary_triggered() {
    DictionaryWindow dictionary_form(db);
    dictionary_form.setGeometry(QApplication::desktop()->screenGeometry());
    dictionary_form.Exec();
}

void StartWindow::on_actionImport_triggered() {
    QString csvFilePath = QFileDialog::getOpenFileName(this, tr("Load CSV"), ".", tr("Dictionary file (*.csv)"));
    if (csvFilePath.size() == 0) {
        return;
    }

    db->ImportDictionaryFromCSV(csvFilePath);
    QMessageBox msgBox;
    msgBox.setText(QString("CSV was imported to Dictionary"));
    msgBox.exec();
}

void StartWindow::on_actionExport_triggered() {
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH:mm");
    QString defaultName = "./dictionary_" + currentTime + ".csv";

    QString csvFilePath = QFileDialog::getSaveFileName(this, tr("Export Dictionary"), defaultName, tr("Dictionary (*.csv)"));
    if (csvFilePath.size() == 0) {
        return;
    }

    if (!csvFilePath.endsWith(".csv", Qt::CaseInsensitive)) {
        csvFilePath += ".csv";
    }

    if (db->ExportDictionaryToCSV(csvFilePath)) {
        QMessageBox msgBox;
        msgBox.setText(QString("Dictionary export to file %1 failed!").arg(csvFilePath));
        msgBox.exec();
        return;
    }

    QMessageBox msgBox;
    msgBox.setText(QString("Dictionary was exported to file:\n%1").arg(csvFilePath));
    msgBox.exec();
}
