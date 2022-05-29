#pragma once

using namespace std;
using namespace System;

ref class Product
{
	int quantity;
	String^ name, ^ id, ^ sellerID;
	float price;
public:
	System::Collections::Generic::List<String ^> category;
	Product(void);
	Product(Product^ p, int newQuantity);
	Product(String^ id, String^ sellerID, String^ name, float price, int quantity);
	Product(cli::array<String^>^ Info);
	Product(cli::array<String^>^ Info, cli::array<String^>^ InfoCategory);
	String^ getID();
	String^ getSID();
	String^ getName();
	float getPrice();
	int getQuantity();
	void setQuantity(int newQuantity);
};

