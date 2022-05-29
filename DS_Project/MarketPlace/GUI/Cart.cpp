#include "Cart.h"

Cart::Cart(void) :totalPrice(0.0f) {}

Cart::Cart(Product^ p) {
	listOFProdcut.Add(p);
	totalPrice = 0.0f;
	totalPrice += p->getPrice();
}

void Cart::addProductToList(Product^ prodcut, float newPrice)
{
	listOFProdcut.Add(prodcut);
	setPrice(newPrice);
}

void Cart::setPrice(float newPrice) {
	totalPrice += newPrice;
}

float Cart::getNetPrice() {
	return totalPrice;
}


