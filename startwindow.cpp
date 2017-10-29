#include "startwindow.h"
#include "ui_startwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QMessageBox>

StartWindow::StartWindow(DataBase *_db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
    , dictionary_form(_db)
    , study_form(_db)
    , db(_db)
{
    ui->setupUi(this);
}

StartWindow::~StartWindow() {
    delete ui;
}


void StartWindow::on_studyButton_clicked() {
    QRect wGeom = this->geometry();
    study_form.setGeometry(QRect(wGeom.x(), wGeom.y(),
                           study_form.geometry().width(),
                           study_form.geometry().height()));
    study_form.Show();
}

void StartWindow::on_action_Options_triggered() {
    QRect wGeom = this->geometry();
    options_form.setGeometry(QRect(wGeom.x(), wGeom.y(),
                             options_form.geometry().width(),
                             options_form.geometry().height()));
    options_form.Show();
}

void StartWindow::on_actionEdit_dictionary_triggered() {
    dictionary_form.setGeometry(QApplication::desktop()->screenGeometry());
    dictionary_form.Show();
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
    QString csvFilePath = QFileDialog::getSaveFileName(this, tr("Export Dictionary"), ".", tr("Dictionary (*.csv)"));
    if (csvFilePath.size() == 0) {
        return;
    }

    if (!csvFilePath.endsWith(".csv")) {
        csvFilePath += ".csv";
    }

    if (db->ExportDictionaryToCSV(csvFilePath)) {
        QMessageBox msgBox;
        msgBox.setText(QString("Dictionary export to file %1 failed!").arg(csvFilePath));
        msgBox.exec();
        return;
    }

    QMessageBox msgBox;
    msgBox.setText(QString("Dictionary was exported to file: %1.").arg(csvFilePath));
    msgBox.exec();
}
