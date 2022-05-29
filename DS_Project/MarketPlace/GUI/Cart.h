#pragma once
#include "Product.h"

using namespace std;
using namespace System;

ref class Cart
{
	float totalPrice;

public:
	System::Collections::Generic::List<Product ^>  listOFProdcut;
	Cart(void);
	Cart(Product^ product);
	void addProductToList(Product^ prodcut, float newPrice);
	float getNetPrice();
	void setPrice(float newPrice);
};

