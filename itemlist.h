#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QMap>
#include "itemreader.h"
#include "itemwriter.h"

class ItemList : public QMap<QString, Item>
{
public:
    bool readAll(QString InputFileName);
    void writeAll(QString OutputFileName);

    bool readFromFile();
    bool writeToFile();

    QString toString();
    bool add(Item item);
    bool change(Item item);
};

#endif // ITEMLIST_H
