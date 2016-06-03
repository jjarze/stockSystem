#include "itemlist.h"
#include <QFileDialog>
#include <QDebug>

bool ItemList::readAll(QString InputFileName){
    //read in the items from the file
    //return true if there are 1 or more items
    ItemReader reader(InputFileName);

    while(!reader.endOfFile()){
        Item temp(reader.readItem());
        this->insert(temp.getBarcode(), temp);
    }

    if(this->size() > 0){
        return true;
    }
    else{
        return false;
    }
}

void ItemList::writeAll(QString OutputFileName){
    //Loop through map and write to file
    ItemWriter writer(OutputFileName);
    foreach(Item value, *this){
        writer.writeItem(value);
    }
}

bool ItemList::readFromFile(){
    //Bring up the file dialog then read from selected file
    QFileDialog dialog(0);
    QString filename = dialog.getOpenFileName();
    if(filename.size() > 0){
        readAll(filename);
        return true;
    }
    else{
        return false;
    }
}

bool ItemList::writeToFile(){
    //Bring up the file dialog then read write to selected file
    QFileDialog dialog(0);
    QString filename = dialog.getSaveFileName();
    if(filename.size() > 0){
        writeAll(filename);
        return true;
    }
    else{
        return false;
    }
}

QString ItemList::toString(){
    //Create a QString of the entire model
    QString temp;
    foreach(Item value, *this){
        temp += value.toString() + "\n";
    }
    return temp;
}


bool ItemList::add(Item item){
    //Add item to map if the key is new
    if(this->keys().contains(item.getBarcode())){
        return false;
    }
    else{
        this->insert(item.getBarcode(), item);
        return true;
    }
}

bool ItemList::change(Item item){
    //Change the item if the barcode provided exists
    if(!(this->keys().contains(item.getBarcode()))){
        return false;
    }
    else{
        this->insert(item.getBarcode(), item);
        return true;
    }
}
