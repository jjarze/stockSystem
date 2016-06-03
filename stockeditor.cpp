#include "stockeditor.h"
#include "itemlist.h"
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>
#include <QInputDialog>
#include <QMenuBar>
#include <QToolBar>
#include <QIcon>
#include <QApplication>
#include <QMessageBox>

stockEditor::stockEditor(QWidget *parent) : QMainWindow(parent)
{
    //Initialise values and create the main window
    savedFlag = true;
    setWindowTitle("Stock Editor");
    setFixedWidth(700);
    setFixedHeight(550);

    //editDialog pointer for add, change dialogs
    editDialog = new EditDialog(&model, 0);
    //Create actiongroup for all actions
    actionGroup = new QActionGroup(this);

    //Create the file and edit menus
    fileMenu = menuBar()->addMenu(tr("&File"));
    editMenu = menuBar()->addMenu(tr("&Edit"));

    //Create each action
    open = new QAction(QIcon(":o.png"), "Open", this);
    exit = new QAction(QIcon(":x.png"), "Exit", this);
    save = new QAction(QIcon(":s.png"), "Save", this);
    add = new QAction(QIcon(":a.png"), "Add", this);
    remove = new QAction(QIcon(":r.png"), "Remove", this);

    //Add all the actions to the actiongroup
    actionGroup->addAction(open);
    actionGroup->addAction(save);
    actionGroup->addAction(exit);
    actionGroup->addAction(add);
    actionGroup->addAction(remove);

    //add actions to the menus
    fileMenu->addAction(open);
    fileMenu->addAction(save);
    fileMenu->addAction(exit);

    editMenu->addAction(add);
    editMenu->addAction(remove);

    //Use the actionEvent() to catch all signals
    QObject::connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(actionEvent(QAction*)));

    //Create the text area to display the contents of the model
    textEdit = new QTextEdit(this);
    textEdit->setFixedWidth(700);

    textEdit->setFixedHeight(500);
    textEdit->setDisabled(true);

    //Create the toolbar
    toolBar = addToolBar("Toolbar");
    toolBar->addActions(actionGroup->actions());
    adjustSize();
}

void stockEditor::actionEvent(QAction* act){
    //Handle each signal from the actions
    if(act == open){
         model.readFromFile();
         updateText();
    }
    if(act == save){
        if(model.writeToFile()){
            savedFlag = true;
        }
    }
    if(act == exit){
        if(savedFlag){
            QApplication::quit();
        }
        else{
            QMessageBox::information(0, "Error: Work Not Saved", QString("Please save your work before exiting"));
        }
    }
    if(act == add){
        bool tempItem = editDialog->add();
        if(tempItem){
            savedFlag = false;
            updateText();
        }
    }

    if(act == remove){
        QString barcode = editDialog->remove();
        model.remove(barcode);
        savedFlag = false;
        updateText();
    }
}

void stockEditor::updateText(){
    //update the display text
    QString textEditHeadings = QString("%1\t%2\t%3\t%4\n")
                .arg("Barcode", 13)
                .arg("Description", 20)
                .arg("Stock", 5)
                .arg("Price", 10);

   textEdit->setText(textEditHeadings + model.toString());

}
