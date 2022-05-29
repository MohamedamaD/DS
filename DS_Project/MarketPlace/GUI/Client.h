#pragma once
#include "Cart.h"
using namespace System;
ref class Client
{

	String^ ID, ^ Name, ^ Email, ^ Address, ^ phoneNum, ^ Password;
	bool IsSeller;
	public:
		Cart^  cart;
		Client(void);
		Client(String^ id, String^ name, String^ email, String^ password,  String^ address, String^ phonenum, bool iseller);
		Client(cli::array<String^>^ Info);
		String^ getID();
		String^ getPhoneNumber();
		String^ getAddress();
		String^ getName();
		String^ getEmail();
		String^ getPassword();
		bool getIsSeller();
};

