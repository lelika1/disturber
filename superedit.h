#ifndef SUPEREDIT_H
#define SUPEREDIT_H

#include <QWidget>
#include <QItemDelegate>

namespace Ui {
class SuperEdit;
}

class SuperEdit : public QWidget
{
    Q_OBJECT

public:
    explicit SuperEdit(QWidget *parent = 0);
    ~SuperEdit();

private slots:
    void on_printAeButton_clicked();

    void on_printOeButton_clicked();

    void on_printUeButton_clicked();

    void on_printSsButton_clicked();

private:
    friend class SuperEditDelegate;

    Ui::SuperEdit *ui;
};

class SuperEditDelegate : public QItemDelegate {
public:
    SuperEditDelegate(QObject *parent = 0);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const; //создаем редактор делегата - это наш виджет
    void setEditorData(QWidget *editor, const QModelIndex &index) const; //устанавливаем данные в редакторе

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const; //а здесь данные из редактора передаем уже в модель
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // SUPEREDIT_H
