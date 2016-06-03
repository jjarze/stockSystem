#include "editdialog.h"
#include <QInputDialog>
#include <QLabel>
#include <QGridLayout>

EditDialog::EditDialog(ItemList *model, QWidget *parent) :
    QDialog(parent)
{
    modelP = model;
}

bool EditDialog::add(){

        //Get the new barcode from the user
        QInputDialog dialog_barcode(this);
        QString newBarcode = "";

        do{
            newBarcode = dialog_barcode.getText(0, "Please enter a unique barcode", "Barcode:");
        }
        while(modelP->keys().contains(newBarcode) || newBarcode == "");

        //Created a custom dialog to get the Item details from the user
        add_dialog = new QDialog;
        QGridLayout *layout = new QGridLayout;
        barcodeEdit = new QLineEdit();
        barcodeEdit->setDisabled(true);
        barcodeEdit->setText(newBarcode);
        descEdit = new QLineEdit();
        stockEdit = new QSpinBox();
        priceEdit = new QDoubleSpinBox();

        QLabel *barcodeLabel = new QLabel;
        QLabel *descLabel = new QLabel();
        QLabel *stockLabel = new QLabel();
        QLabel *priceLabel = new QLabel;
        barcodeLabel->setText("Barcode:");
        descLabel->setText("Description");
        stockLabel->setText("Stock");
        priceLabel->setText("Price");

        ok = new QPushButton("Add");

        QObject::connect(ok, SIGNAL(clicked()), this, SLOT(addPost()));

        layout->addWidget(barcodeLabel);
        layout->addWidget(barcodeEdit);
        layout->addWidget(descLabel);
        layout->addWidget(descEdit);
        layout->addWidget(stockLabel);
        layout->addWidget(stockEdit);
        layout->addWidget(priceLabel);
        layout->addWidget(priceEdit);
        layout->addWidget(ok);


        add_dialog->setLayout(layout);
        add_dialog->exec();
        return true;

}
bool EditDialog::addPost(){
    //Close the dialog and add the item to the model
    add_dialog->close();
    return modelP->add(Item(barcodeEdit->text(), descEdit->text(), stockEdit->value(), priceEdit->value()));

}

QString EditDialog::remove(){
    //get the barcode of the item to remove from the user
    return QInputDialog::getText(0, "Remove Item", "Enter Barcode of item to remove: ");
}
