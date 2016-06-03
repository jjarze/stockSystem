#ifndef ITEMREADER_H
#define ITEMREADER_H

#include "item.h"
#include <QString>
#include <QFile>

class ItemReader
{
private:
    QFile inputFile;
public:
    ItemReader(QString fname);
    Item readItem();
    bool endOfFile();
    ~ItemReader();
};

#endif // ITEMREADER_H
