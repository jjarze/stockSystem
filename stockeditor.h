#ifndef STOCKEDITOR_H
#define STOCKEDITOR_H

#include <QDialog>
#include <QMainWindow>
#include <QAction>
#include <QActionGroup>
#include <QTextEdit>
#include "itemlist.h"
#include "editdialog.h"

class stockEditor : public QMainWindow
{
    Q_OBJECT
public:
    explicit stockEditor(QWidget *parent = 0);

private:
    ItemList model;
    EditDialog* editDialog;
    QActionGroup* actionGroup;
    QToolBar* toolBar;

    QAction* open;
    QAction* save;
    QAction* exit;
    QAction* add;
    QAction* change;
    QAction* remove;

    QMenu* fileMenu;
    QMenu* editMenu;

    QTextEdit* textEdit;

    bool savedFlag;
    void updateText();

signals:

public slots:
    void actionEvent(QAction* act);
};

#endif // STOCKEDITOR_H
