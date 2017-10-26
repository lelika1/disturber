#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "addwordswindow.h"
#include "database.h"
#include "dictionarywindow.h"
#include "settings.h"
#include "studywindow.h"

#include <QMainWindow>

namespace Ui {

class StartWindow;

} // namespace Ui


class StartWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit StartWindow(DataBase *_db, QWidget *parent = 0);
    ~StartWindow();

private slots:
    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_studyButton_clicked();

    void on_settingsButton_clicked();

    void on_actionDictionary_CSV_triggered();

    void on_actionCSV_Dictionary_triggered();

private:
    Ui::StartWindow *ui;
    AddWordsWindow add_pair_form;
    DictionaryWindow dictionary_form;
    Settings setting_form;
    StudyWindow study_form;
    DataBase *db;
};

#endif // STARTWINDOW_H
