#include "Product.h"

Product::Product(void) :id(""), sellerID(""), name(""), price(0.0f), quantity(0) {}

Product::Product(Product^ p, int newQuantity)
{
    id = p->id;
    sellerID = p->sellerID;
    name = p->name;
    price = p->price;
    quantity = newQuantity;
}

Product::Product(String^ ID, String^ SID, String^ NAME, float PRICE, int QUANTITY) : id(ID), sellerID(SID), name(NAME), price(PRICE), quantity(QUANTITY) {}

Product::Product(cli::array<String^>^ Info)
{
    id = Info[0];
    sellerID = Info[1];
    name = Info[2];
    price = float::Parse(Info[3]);
    quantity = int::Parse(Info[4]);

}

Product::Product(cli::array<String^>^ Info, cli::array<String^>^ InfoCategory)
{
    id = Info[0];
    sellerID = Info[1];
    name = Info[2];
    price = float::Parse(Info[3]);
    quantity = int::Parse(Info[4]);
    for (int i = 0; i < InfoCategory->Length; i++)
    {
        category.Add(InfoCategory[i]);
    }
}

String^ Product::getID() { return id; }

String^ Product::getSID() { return sellerID; }

String^ Product::getName() { return name; }

float Product::getPrice() { return price; }

int Product::getQuantity() { return quantity; }

void Product::setQuantity(int newQuantity)
{
    quantity = newQuantity;
}
