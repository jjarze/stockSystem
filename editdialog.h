#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include "itemlist.h"

class EditDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EditDialog(ItemList *model, QWidget *parent = 0);
    bool add();
    QString remove();

private:
    ItemList* modelP;
    QDialog* add_dialog;
    QLineEdit *barcodeEdit, *descEdit;
    QSpinBox* stockEdit;
    QDoubleSpinBox* priceEdit;
    QPushButton *ok;


signals:

public slots:
    bool addPost();

};

#endif // EDITDIALOG_
