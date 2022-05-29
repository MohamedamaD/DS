#include "Client.h"

Client::Client(void) : ID(""), phoneNum(""), Name(""), Email(""), Address(""), IsSeller(false) { cart = gcnew Cart(); }

Client::Client(String^ id, String^ name, String^ email, String^ password, String^ address, String^ phonenum, bool iseller) : ID(id), Name(name), Email(email), Password(password), Address(address), phoneNum(phonenum), IsSeller(iseller) { cart = gcnew Cart(); }

Client::Client(cli::array<String^>^ Info)
{
	ID = Info[0];
	Name = Info[1];
	Email = Info[2];
	Address = Info[3];
	phoneNum = Info[4];
	Password = Info[5];
	IsSeller = bool::Parse(Info[6]);
	cart = gcnew Cart();
}

String^ Client::getID() { return ID; }

String^ Client::getPhoneNumber() { return phoneNum; }

bool Client::getIsSeller() { return IsSeller; }

String^ Client::getAddress() { return Address; }

String^ Client::getName() { return Name; }

String^ Client::getEmail() { return Email; }

String^ Client::getPassword() { return Password; }


