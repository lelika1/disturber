#include "dictionarywindow.h"
#include "ui_dictionarywindow.h"

DictionaryWindow::DictionaryWindow(DataBase *_db, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DictionaryWindow)
    , db(_db)
{
    ui->setupUi(this);
}

DictionaryWindow::~DictionaryWindow()
{
    delete ui;
}
