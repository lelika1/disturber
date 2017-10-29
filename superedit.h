#ifndef SUPEREDIT_H
#define SUPEREDIT_H

#include <QKeyEvent>
#include <QLineEdit>
#include <QWidget>
#include <QItemDelegate>

namespace Ui {
class SuperEdit;
}

class SuperEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit SuperEdit(QWidget *parent = 0);
    ~SuperEdit();

    QString text();
    void setText(const QString &str);
    void setFocusOnEdit();

    void setButtonsVisable(bool enable);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_printAeButton_clicked();

    void on_printOeButton_clicked();

    void on_printUeButton_clicked();

    void on_printSsButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    friend class SuperEditDelegate;

    Ui::SuperEdit *ui;
};

class SuperEditDelegate : public QItemDelegate {
public:
    SuperEditDelegate(QObject *parent = 0);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // SUPEREDIT_H
