#include <QApplication>
#include "itemlist.h"
#include "stockeditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    stockEditor editor; //editor open
    editor.show(); //show view
    return a.exec();
}
