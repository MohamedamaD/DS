#pragma once
#include <fstream>
#include <string>
#include "Client.h"
#include "Product.h"
#include <array>

namespace GUI {


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace System::IO;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	
	
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		// main variable
		Dictionary<String ^, Client^> ClientInformation; // get client to programm
		String^ ClientKey; // clinet that using application now 
		Dictionary<String^, Product^> Products; // get products to programm
		System::Collections::Generic::List<String ^> ProductKey; // product that user dealing with it
		System::Collections::Generic::List<String^> localCategory; // to enter category
		String ^ productCategoryKey;
		// files variable
		String^ path; 
		System::IO::StreamWriter^ WFile;

	public:
		System::IO::StreamReader^ RFile;

	public:
		MyForm(void)
		{
			InitializeComponent();
			transferDataFromFileToVector();
			transferProductsFromFileToVector();
			transferCartFromFileToVector();
		}

		// store and get data 

		void transferDataFromFileToVector() {
			path = "D:\\DS_Project\\Files Store Data\\Client.csv";
			RFile = gcnew StreamReader(path); // open file
			int count = 1; RFile->ReadLine();
			while(!RFile->EndOfStream) // !NULL
			{
				cli::array<String^>^ str = RFile->ReadLine()->Split(',');
				ClientInformation[str[0]] = gcnew Client(str);
				count++;
			}
			RFile->Close();
		}

		void transferDataFromVectorToFile() {
			path = "D:\\DS_Project\\Files Store Data\\Client.csv";
			WFile = gcnew StreamWriter(path);
			WFile->WriteLine(
				"Id,Name,Email,Address,PhoneNum,Password,seller"
			);
			for each (KeyValuePair<String ^, Client^> var in ClientInformation)
			{
				WFile->WriteLine(
					var.Value->getID() + "," +
					var.Value->getName() + "," +
					var.Value->getEmail() + "," +
					var.Value->getAddress() + "," +
					var.Value->getPhoneNumber() + "," +
					var.Value->getPassword() + "," +
					var.Value->getIsSeller()
				);
			}
			WFile->Close();
		}

		void transferProductsFromFileToVector() {
			path = "D:\\DS_Project\\Files Store Data\\Products.csv";
			RFile = gcnew StreamReader(path);
			int count = 1; RFile->ReadLine();
			while (!RFile->EndOfStream) // !NULL
			{
				cli::array<String^>^ str = RFile->ReadLine()->Split(',');
				cli::array<String^>^ strCategory = str[5]->Split('|');

				Product^ p = gcnew Product(str, strCategory);
				Products[p->getID()] = p;
				count++;
			}
			RFile->Close();
		}

		void transferProductsFromVectortoFile() {
			path = "D:\\DS_Project\\Files Store Data\\Products.csv";
			WFile = gcnew StreamWriter(path);
			WFile->WriteLine(
				"Id,SellerID,Name,Price,Quantity,Category"
			);
			String^ lineCategory = "";
			for each (KeyValuePair<String^, Product^> var in Products)
			{
				for (int x = 0; x < var.Value->category.Count; x++)
				{
					if (var.Value->category.Count - 1 == x)
						lineCategory += (var.Value->category[x]);
					else
						lineCategory += (var.Value->category[x] + "|");
				}
				WFile->WriteLine(
					var.Value->getID() + "," +
					var.Value->getSID() + "," +
					var.Value->getName() + "," +
					var.Value->getPrice() + "," +
					var.Value->getQuantity() + "," +
					lineCategory
				);
				lineCategory = "";
			}
			WFile->Close();
		}

		void transferCartFromFileToVector() {
			path = "D:\\DS_Project\\Files Store Data\\CART.csv";
			RFile = gcnew StreamReader(path); // open file
			RFile->ReadLine();
			while (!RFile->EndOfStream) // !NULL
			{
				cli::array<String^>^ str = RFile->ReadLine()->Split(',');
				for each (KeyValuePair<String^, Client^> var in ClientInformation)
				{
					if (var.Key == str[0]) {
						var.Value->cart->setPrice(float::Parse(str[5]) * int::Parse(str[6]));
						var.Value->cart->listOFProdcut.Add(gcnew Product(str[2], str[3], str[4], float::Parse(str[5]), int::Parse(str[6])));
					}
				}
			}
			RFile->Close();
		}

		void transferCartFromVectorToFile() {
			path = "D:\\DS_Project\\Files Store Data\\CART.csv";
			WFile = gcnew StreamWriter(path);
			WFile->WriteLine(
				"Client ID,Total Price,Product ID,Seller ID,Product Name,Price,Quantity"
			);
			for each (KeyValuePair<String^, Client^> var in ClientInformation)
			{
				for (int i = 0; i < var.Value->cart->listOFProdcut.Count; i++)
				{
					WFile->WriteLine(
						var.Value->getID() + "," +
						var.Value->cart->getNetPrice() + "," +
						var.Value->cart->listOFProdcut[i]->getID() + "," +
						var.Value->cart->listOFProdcut[i]->getSID() + "," +
						var.Value->cart->listOFProdcut[i]->getName() + "," +
						var.Value->cart->listOFProdcut[i]->getPrice() + "," +
						var.Value->cart->listOFProdcut[i]->getQuantity()
					);
				}
			}
			WFile->Close();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			transferDataFromVectorToFile();
			transferProductsFromVectortoFile();
		}

	public : 
	private: System::Windows::Forms::Panel^ PMainProgramm;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Panel^ PNav;
	private: System::Windows::Forms::Button^ BAddProduct;
	private: System::Windows::Forms::Label^ LLogo;
	private: System::Windows::Forms::Panel^ PContent;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Panel^ PHeader;
	private: System::Windows::Forms::Button^ BBack;
	private: System::Windows::Forms::Panel^ v;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ TRegID;
	private: System::Windows::Forms::Label^ LID;
	private: System::Windows::Forms::TextBox^ TRegPhone;
	private: System::Windows::Forms::TextBox^ TRegAddress;
	private: System::Windows::Forms::TextBox^ TRegPassword;
	private: System::Windows::Forms::TextBox^ TRegEmail;
	private: System::Windows::Forms::TextBox^ TRegUsername;
	private: System::Windows::Forms::Label^ LPhone;
	private: System::Windows::Forms::Label^ LAddress;
	private: System::Windows::Forms::Label^ LPassword;
	private: System::Windows::Forms::Label^ LEmail;
	private: System::Windows::Forms::Label^ LUsername;
	private: System::Windows::Forms::Panel^ PRegistration;
	private: System::Windows::Forms::Button^ BSubmit;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Panel^ PSignIn;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ TSignInPassword;
	private: System::Windows::Forms::TextBox^ TSignInEmail;
	private: System::Windows::Forms::Button^ BSignUP;
	private: System::Windows::Forms::Button^ BLogin;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::RadioButton^ RSeller;
	private: System::Windows::Forms::RadioButton^ RCustomer;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ TProductID;
	private: System::Windows::Forms::TextBox^ TProductQuantity;
	private: System::Windows::Forms::TextBox^ TProductPrice;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::ComboBox^ TProductCategory;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ BAddCategory;
	private: System::Windows::Forms::Button^ BDelCategory;
	private: System::Windows::Forms::Button^ BSave;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ TProductName;
	private: System::Windows::Forms::Button^ BLogOut;
	private: System::Windows::Forms::Button^ BCancel;
	private: System::Windows::Forms::Panel^ PCustomer;
	private: System::Windows::Forms::Panel^ PCHeader;
	private: System::Windows::Forms::FlowLayoutPanel^ PCNav;
	private: System::Windows::Forms::FlowLayoutPanel^ PINFOProduct;
	private: System::Windows::Forms::Panel^ PSearchTools;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ BSearch;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Button^ BSearchByName;
	private: System::Windows::Forms::Button^ BSearchByCate;
	private: System::Windows::Forms::Button^ BCart;
	private: System::Windows::Forms::Panel^ PSearchName;
	private: System::Windows::Forms::Button^ BCLogout;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Panel^ panel6;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Panel^ PInformationCustomer;
	private: System::Windows::Forms::Panel^ PCSBCategory;
	private: System::Windows::Forms::ListBox^ listProducts;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Label^ LabelPrice;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Label^ LabelQuantity;
	private: System::Windows::Forms::Panel^ panel5;
	private: System::Windows::Forms::TextBox^ TItemNo;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::Panel^ panel7;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ CaneclBuy;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::ListBox^ listBoxProductCat;
	private: System::Windows::Forms::Panel^ panel9;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Panel^ panel10;
	private: System::Windows::Forms::Label^ label22;
	private: System::Windows::Forms::Panel^ panel11;
	private: System::Windows::Forms::TextBox^ TItem;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::Panel^ panel12;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Panel^ panel8;
	private: System::Windows::Forms::Button^ BSearchCatgory;
	private: System::Windows::Forms::TextBox^ TSearchCategory;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::Panel^ PCart;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel2;
	private: System::Windows::Forms::ListBox^ LBDisplayProducts;
	private: System::Windows::Forms::Label^ lTotalPrice;
	private: System::Windows::Forms::Button^ BConfirm;
	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->v = (gcnew System::Windows::Forms::Panel());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->LUsername = (gcnew System::Windows::Forms::Label());
			this->LEmail = (gcnew System::Windows::Forms::Label());
			this->LPassword = (gcnew System::Windows::Forms::Label());
			this->LAddress = (gcnew System::Windows::Forms::Label());
			this->LPhone = (gcnew System::Windows::Forms::Label());
			this->TRegUsername = (gcnew System::Windows::Forms::TextBox());
			this->TRegEmail = (gcnew System::Windows::Forms::TextBox());
			this->TRegPassword = (gcnew System::Windows::Forms::TextBox());
			this->TRegAddress = (gcnew System::Windows::Forms::TextBox());
			this->TRegPhone = (gcnew System::Windows::Forms::TextBox());
			this->PRegistration = (gcnew System::Windows::Forms::Panel());
			this->PInformationCustomer = (gcnew System::Windows::Forms::Panel());
			this->BBack = (gcnew System::Windows::Forms::Button());
			this->TRegID = (gcnew System::Windows::Forms::TextBox());
			this->LID = (gcnew System::Windows::Forms::Label());
			this->RSeller = (gcnew System::Windows::Forms::RadioButton());
			this->RCustomer = (gcnew System::Windows::Forms::RadioButton());
			this->BSubmit = (gcnew System::Windows::Forms::Button());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->PSignIn = (gcnew System::Windows::Forms::Panel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->TSignInPassword = (gcnew System::Windows::Forms::TextBox());
			this->TSignInEmail = (gcnew System::Windows::Forms::TextBox());
			this->BSignUP = (gcnew System::Windows::Forms::Button());
			this->BLogin = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->PMainProgramm = (gcnew System::Windows::Forms::Panel());
			this->PContent = (gcnew System::Windows::Forms::Panel());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->BCancel = (gcnew System::Windows::Forms::Button());
			this->BSave = (gcnew System::Windows::Forms::Button());
			this->BDelCategory = (gcnew System::Windows::Forms::Button());
			this->BAddCategory = (gcnew System::Windows::Forms::Button());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->TProductCategory = (gcnew System::Windows::Forms::ComboBox());
			this->TProductID = (gcnew System::Windows::Forms::TextBox());
			this->TProductQuantity = (gcnew System::Windows::Forms::TextBox());
			this->TProductPrice = (gcnew System::Windows::Forms::TextBox());
			this->TProductName = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->PNav = (gcnew System::Windows::Forms::Panel());
			this->BAddProduct = (gcnew System::Windows::Forms::Button());
			this->PHeader = (gcnew System::Windows::Forms::Panel());
			this->BLogOut = (gcnew System::Windows::Forms::Button());
			this->LLogo = (gcnew System::Windows::Forms::Label());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->PCustomer = (gcnew System::Windows::Forms::Panel());
			this->PCart = (gcnew System::Windows::Forms::Panel());
			this->lTotalPrice = (gcnew System::Windows::Forms::Label());
			this->BConfirm = (gcnew System::Windows::Forms::Button());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->LBDisplayProducts = (gcnew System::Windows::Forms::ListBox());
			this->PCSBCategory = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->listBoxProductCat = (gcnew System::Windows::Forms::ListBox());
			this->panel9 = (gcnew System::Windows::Forms::Panel());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->panel10 = (gcnew System::Windows::Forms::Panel());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->panel11 = (gcnew System::Windows::Forms::Panel());
			this->TItem = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->panel12 = (gcnew System::Windows::Forms::Panel());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->panel8 = (gcnew System::Windows::Forms::Panel());
			this->BSearchCatgory = (gcnew System::Windows::Forms::Button());
			this->TSearchCategory = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->PSearchName = (gcnew System::Windows::Forms::Panel());
			this->PINFOProduct = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->listProducts = (gcnew System::Windows::Forms::ListBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->LabelPrice = (gcnew System::Windows::Forms::Label());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->LabelQuantity = (gcnew System::Windows::Forms::Label());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->TItemNo = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->CaneclBuy = (gcnew System::Windows::Forms::Button());
			this->PSearchTools = (gcnew System::Windows::Forms::Panel());
			this->BSearch = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->PCNav = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->BSearchByName = (gcnew System::Windows::Forms::Button());
			this->BSearchByCate = (gcnew System::Windows::Forms::Button());
			this->BCart = (gcnew System::Windows::Forms::Button());
			this->PCHeader = (gcnew System::Windows::Forms::Panel());
			this->BCLogout = (gcnew System::Windows::Forms::Button());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->PRegistration->SuspendLayout();
			this->PInformationCustomer->SuspendLayout();
			this->PSignIn->SuspendLayout();
			this->PMainProgramm->SuspendLayout();
			this->PContent->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->panel1->SuspendLayout();
			this->PNav->SuspendLayout();
			this->PHeader->SuspendLayout();
			this->panel6->SuspendLayout();
			this->PCustomer->SuspendLayout();
			this->PCart->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			this->PCSBCategory->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->panel9->SuspendLayout();
			this->panel10->SuspendLayout();
			this->panel11->SuspendLayout();
			this->panel12->SuspendLayout();
			this->panel8->SuspendLayout();
			this->PSearchName->SuspendLayout();
			this->PINFOProduct->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel4->SuspendLayout();
			this->panel5->SuspendLayout();
			this->panel7->SuspendLayout();
			this->PSearchTools->SuspendLayout();
			this->PCNav->SuspendLayout();
			this->PCHeader->SuspendLayout();
			this->SuspendLayout();
			// 
			// v
			// 
			this->v->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"v.BackgroundImage")));
			this->v->Dock = System::Windows::Forms::DockStyle::Fill;
			this->v->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16));
			this->v->Location = System::Drawing::Point(0, 0);
			this->v->Name = L"v";
			this->v->Size = System::Drawing::Size(1248, 632);
			this->v->TabIndex = 10;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 22));
			this->label7->ForeColor = System::Drawing::Color::DarkRed;
			this->label7->Location = System::Drawing::Point(916, 233);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(344, 78);
			this->label7->TabIndex = 0;
			this->label7->Text = L"Registration";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// LUsername
			// 
			this->LUsername->AutoSize = true;
			this->LUsername->Location = System::Drawing::Point(43, 54);
			this->LUsername->Name = L"LUsername";
			this->LUsername->Size = System::Drawing::Size(240, 65);
			this->LUsername->TabIndex = 1;
			this->LUsername->Text = L"Username";
			// 
			// LEmail
			// 
			this->LEmail->AutoSize = true;
			this->LEmail->Location = System::Drawing::Point(43, 162);
			this->LEmail->Name = L"LEmail";
			this->LEmail->Size = System::Drawing::Size(141, 65);
			this->LEmail->TabIndex = 2;
			this->LEmail->Text = L"Email";
			// 
			// LPassword
			// 
			this->LPassword->AutoSize = true;
			this->LPassword->Location = System::Drawing::Point(388, 162);
			this->LPassword->Name = L"LPassword";
			this->LPassword->Size = System::Drawing::Size(225, 65);
			this->LPassword->TabIndex = 3;
			this->LPassword->Text = L"Password";
			// 
			// LAddress
			// 
			this->LAddress->AutoSize = true;
			this->LAddress->Location = System::Drawing::Point(13, 15);
			this->LAddress->Name = L"LAddress";
			this->LAddress->Size = System::Drawing::Size(197, 65);
			this->LAddress->TabIndex = 4;
			this->LAddress->Text = L"Address";
			// 
			// LPhone
			// 
			this->LPhone->AutoSize = true;
			this->LPhone->Location = System::Drawing::Point(13, 114);
			this->LPhone->Name = L"LPhone";
			this->LPhone->Size = System::Drawing::Size(162, 65);
			this->LPhone->TabIndex = 5;
			this->LPhone->Text = L"Phone";
			// 
			// TRegUsername
			// 
			this->TRegUsername->BackColor = System::Drawing::Color::Black;
			this->TRegUsername->ForeColor = System::Drawing::Color::White;
			this->TRegUsername->Location = System::Drawing::Point(49, 102);
			this->TRegUsername->Name = L"TRegUsername";
			this->TRegUsername->Size = System::Drawing::Size(249, 71);
			this->TRegUsername->TabIndex = 6;
			this->TRegUsername->TextChanged += gcnew System::EventHandler(this, &MyForm::validButtonChangeText);
			// 
			// TRegEmail
			// 
			this->TRegEmail->BackColor = System::Drawing::Color::Black;
			this->TRegEmail->ForeColor = System::Drawing::Color::White;
			this->TRegEmail->Location = System::Drawing::Point(49, 207);
			this->TRegEmail->Name = L"TRegEmail";
			this->TRegEmail->Size = System::Drawing::Size(249, 71);
			this->TRegEmail->TabIndex = 7;
			this->TRegEmail->TextChanged += gcnew System::EventHandler(this, &MyForm::validButtonChangeText);
			// 
			// TRegPassword
			// 
			this->TRegPassword->BackColor = System::Drawing::Color::Black;
			this->TRegPassword->ForeColor = System::Drawing::Color::White;
			this->TRegPassword->Location = System::Drawing::Point(394, 207);
			this->TRegPassword->Name = L"TRegPassword";
			this->TRegPassword->Size = System::Drawing::Size(249, 71);
			this->TRegPassword->TabIndex = 8;
			this->TRegPassword->UseSystemPasswordChar = true;
			this->TRegPassword->TextChanged += gcnew System::EventHandler(this, &MyForm::validButtonChangeText);
			// 
			// TRegAddress
			// 
			this->TRegAddress->BackColor = System::Drawing::Color::Black;
			this->TRegAddress->ForeColor = System::Drawing::Color::White;
			this->TRegAddress->Location = System::Drawing::Point(19, 61);
			this->TRegAddress->Name = L"TRegAddress";
			this->TRegAddress->Size = System::Drawing::Size(249, 71);
			this->TRegAddress->TabIndex = 9;
			this->TRegAddress->TextChanged += gcnew System::EventHandler(this, &MyForm::validButtonChangeText);
			// 
			// TRegPhone
			// 
			this->TRegPhone->BackColor = System::Drawing::Color::Black;
			this->TRegPhone->ForeColor = System::Drawing::Color::White;
			this->TRegPhone->Location = System::Drawing::Point(19, 159);
			this->TRegPhone->Name = L"TRegPhone";
			this->TRegPhone->Size = System::Drawing::Size(249, 71);
			this->TRegPhone->TabIndex = 10;
			this->TRegPhone->TextChanged += gcnew System::EventHandler(this, &MyForm::validButtonChangeText);
			// 
			// PRegistration
			// 
			this->PRegistration->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PRegistration.BackgroundImage")));
			this->PRegistration->Controls->Add(this->PInformationCustomer);
			this->PRegistration->Controls->Add(this->BBack);
			this->PRegistration->Controls->Add(this->TRegID);
			this->PRegistration->Controls->Add(this->LID);
			this->PRegistration->Controls->Add(this->RSeller);
			this->PRegistration->Controls->Add(this->RCustomer);
			this->PRegistration->Controls->Add(this->BSubmit);
			this->PRegistration->Controls->Add(this->label13);
			this->PRegistration->Controls->Add(this->TRegPassword);
			this->PRegistration->Controls->Add(this->TRegEmail);
			this->PRegistration->Controls->Add(this->TRegUsername);
			this->PRegistration->Controls->Add(this->LPassword);
			this->PRegistration->Controls->Add(this->LEmail);
			this->PRegistration->Controls->Add(this->LUsername);
			this->PRegistration->Controls->Add(this->label7);
			this->PRegistration->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PRegistration->Location = System::Drawing::Point(0, 0);
			this->PRegistration->Name = L"PRegistration";
			this->PRegistration->Size = System::Drawing::Size(1248, 632);
			this->PRegistration->TabIndex = 10;
			this->PRegistration->Visible = false;
			// 
			// PInformationCustomer
			// 
			this->PInformationCustomer->Controls->Add(this->TRegPhone);
			this->PInformationCustomer->Controls->Add(this->TRegAddress);
			this->PInformationCustomer->Controls->Add(this->LPhone);
			this->PInformationCustomer->Controls->Add(this->LAddress);
			this->PInformationCustomer->Location = System::Drawing::Point(30, 260);
			this->PInformationCustomer->Name = L"PInformationCustomer";
			this->PInformationCustomer->Size = System::Drawing::Size(294, 231);
			this->PInformationCustomer->TabIndex = 20;
			// 
			// BBack
			// 
			this->BBack->BackColor = System::Drawing::Color::Black;
			this->BBack->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BBack->Location = System::Drawing::Point(392, 419);
			this->BBack->Name = L"BBack";
			this->BBack->Size = System::Drawing::Size(108, 46);
			this->BBack->TabIndex = 19;
			this->BBack->Text = L"Back";
			this->BBack->UseVisualStyleBackColor = false;
			this->BBack->Click += gcnew System::EventHandler(this, &MyForm::BBack_Click);
			// 
			// TRegID
			// 
			this->TRegID->BackColor = System::Drawing::Color::Black;
			this->TRegID->ForeColor = System::Drawing::Color::White;
			this->TRegID->Location = System::Drawing::Point(394, 102);
			this->TRegID->Name = L"TRegID";
			this->TRegID->Size = System::Drawing::Size(249, 71);
			this->TRegID->TabIndex = 18;
			this->TRegID->TextChanged += gcnew System::EventHandler(this, &MyForm::validButtonChangeText);
			// 
			// LID
			// 
			this->LID->AutoSize = true;
			this->LID->Location = System::Drawing::Point(388, 54);
			this->LID->Name = L"LID";
			this->LID->Size = System::Drawing::Size(75, 65);
			this->LID->TabIndex = 17;
			this->LID->Text = L"ID";
			// 
			// RSeller
			// 
			this->RSeller->AutoSize = true;
			this->RSeller->Location = System::Drawing::Point(551, 297);
			this->RSeller->Name = L"RSeller";
			this->RSeller->Size = System::Drawing::Size(176, 69);
			this->RSeller->TabIndex = 16;
			this->RSeller->Text = L"Seller";
			this->RSeller->UseVisualStyleBackColor = true;
			this->RSeller->CheckedChanged += gcnew System::EventHandler(this, &MyForm::RSeller_CheckedChanged);
			// 
			// RCustomer
			// 
			this->RCustomer->AutoSize = true;
			this->RCustomer->Checked = true;
			this->RCustomer->Location = System::Drawing::Point(392, 293);
			this->RCustomer->Name = L"RCustomer";
			this->RCustomer->Size = System::Drawing::Size(263, 69);
			this->RCustomer->TabIndex = 15;
			this->RCustomer->TabStop = true;
			this->RCustomer->Text = L"Customer";
			this->RCustomer->UseVisualStyleBackColor = true;
			this->RCustomer->CheckedChanged += gcnew System::EventHandler(this, &MyForm::RCustomer_CheckedChanged);
			// 
			// BSubmit
			// 
			this->BSubmit->BackColor = System::Drawing::Color::Black;
			this->BSubmit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BSubmit->Enabled = false;
			this->BSubmit->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->BSubmit->Location = System::Drawing::Point(392, 360);
			this->BSubmit->Name = L"BSubmit";
			this->BSubmit->Size = System::Drawing::Size(108, 46);
			this->BSubmit->TabIndex = 14;
			this->BSubmit->Text = L"Submit";
			this->BSubmit->UseVisualStyleBackColor = false;
			this->BSubmit->Click += gcnew System::EventHandler(this, &MyForm::BSubmit_Click);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 22));
			this->label13->ForeColor = System::Drawing::Color::Green;
			this->label13->Location = System::Drawing::Point(1042, 282);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(169, 78);
			this->label13->TabIndex = 13;
			this->label13->Text = L"Form";
			this->label13->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// PSignIn
			// 
			this->PSignIn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PSignIn.BackgroundImage")));
			this->PSignIn->Controls->Add(this->label6);
			this->PSignIn->Controls->Add(this->label5);
			this->PSignIn->Controls->Add(this->label4);
			this->PSignIn->Controls->Add(this->TSignInPassword);
			this->PSignIn->Controls->Add(this->TSignInEmail);
			this->PSignIn->Controls->Add(this->BSignUP);
			this->PSignIn->Controls->Add(this->BLogin);
			this->PSignIn->Controls->Add(this->label3);
			this->PSignIn->Controls->Add(this->label2);
			this->PSignIn->Controls->Add(this->label1);
			this->PSignIn->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PSignIn->Location = System::Drawing::Point(0, 0);
			this->PSignIn->Name = L"PSignIn";
			this->PSignIn->Size = System::Drawing::Size(1248, 632);
			this->PSignIn->TabIndex = 11;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24));
			this->label6->ForeColor = System::Drawing::Color::Aqua;
			this->label6->Location = System::Drawing::Point(1041, 321);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(386, 86);
			this->label6->TabIndex = 16;
			this->label6->Text = L"Marketplace";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 28));
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(1023, 272);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(118, 100);
			this->label5->TabIndex = 15;
			this->label5->Text = L"To";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 28));
			this->label4->ForeColor = System::Drawing::Color::Fuchsia;
			this->label4->Location = System::Drawing::Point(939, 221);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(349, 100);
			this->label4->TabIndex = 14;
			this->label4->Text = L"Welcome";
			// 
			// TSignInPassword
			// 
			this->TSignInPassword->BackColor = System::Drawing::Color::Black;
			this->TSignInPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->TSignInPassword->ForeColor = System::Drawing::Color::White;
			this->TSignInPassword->Location = System::Drawing::Point(42, 338);
			this->TSignInPassword->Name = L"TSignInPassword";
			this->TSignInPassword->Size = System::Drawing::Size(267, 57);
			this->TSignInPassword->TabIndex = 13;
			this->TSignInPassword->UseSystemPasswordChar = true;
			// 
			// TSignInEmail
			// 
			this->TSignInEmail->BackColor = System::Drawing::Color::Black;
			this->TSignInEmail->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->TSignInEmail->ForeColor = System::Drawing::Color::White;
			this->TSignInEmail->Location = System::Drawing::Point(42, 238);
			this->TSignInEmail->Name = L"TSignInEmail";
			this->TSignInEmail->Size = System::Drawing::Size(267, 57);
			this->TSignInEmail->TabIndex = 12;
			// 
			// BSignUP
			// 
			this->BSignUP->BackColor = System::Drawing::Color::Black;
			this->BSignUP->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BSignUP->ForeColor = System::Drawing::Color::White;
			this->BSignUP->Location = System::Drawing::Point(176, 404);
			this->BSignUP->Name = L"BSignUP";
			this->BSignUP->Size = System::Drawing::Size(133, 49);
			this->BSignUP->TabIndex = 11;
			this->BSignUP->Text = L"Sign Up";
			this->BSignUP->UseVisualStyleBackColor = false;
			this->BSignUP->Click += gcnew System::EventHandler(this, &MyForm::BSignUP_Click);
			// 
			// BLogin
			// 
			this->BLogin->BackColor = System::Drawing::Color::Black;
			this->BLogin->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BLogin->ForeColor = System::Drawing::Color::White;
			this->BLogin->Location = System::Drawing::Point(42, 404);
			this->BLogin->Name = L"BLogin";
			this->BLogin->Size = System::Drawing::Size(110, 49);
			this->BLogin->TabIndex = 10;
			this->BLogin->Text = L"Login";
			this->BLogin->UseVisualStyleBackColor = false;
			this->BLogin->Click += gcnew System::EventHandler(this, &MyForm::BLogin_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Black;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(37, 297);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(202, 59);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Password";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Black;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(37, 200);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(126, 59);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Email";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Black;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 30));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(35, 124);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(287, 106);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Sign In";
			// 
			// PMainProgramm
			// 
			this->PMainProgramm->Controls->Add(this->PContent);
			this->PMainProgramm->Controls->Add(this->PNav);
			this->PMainProgramm->Controls->Add(this->PHeader);
			this->PMainProgramm->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PMainProgramm->Location = System::Drawing::Point(0, 0);
			this->PMainProgramm->Name = L"PMainProgramm";
			this->PMainProgramm->Size = System::Drawing::Size(1248, 632);
			this->PMainProgramm->TabIndex = 12;
			this->PMainProgramm->Visible = false;
			// 
			// PContent
			// 
			this->PContent->Controls->Add(this->groupBox1);
			this->PContent->Controls->Add(this->panel1);
			this->PContent->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PContent->Location = System::Drawing::Point(152, 73);
			this->PContent->Name = L"PContent";
			this->PContent->Size = System::Drawing::Size(1096, 559);
			this->PContent->TabIndex = 2;
			this->PContent->Visible = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->BCancel);
			this->groupBox1->Controls->Add(this->BSave);
			this->groupBox1->Controls->Add(this->BDelCategory);
			this->groupBox1->Controls->Add(this->BAddCategory);
			this->groupBox1->Controls->Add(this->label15);
			this->groupBox1->Controls->Add(this->TProductCategory);
			this->groupBox1->Controls->Add(this->TProductID);
			this->groupBox1->Controls->Add(this->TProductQuantity);
			this->groupBox1->Controls->Add(this->TProductPrice);
			this->groupBox1->Controls->Add(this->TProductName);
			this->groupBox1->Controls->Add(this->label14);
			this->groupBox1->Controls->Add(this->label12);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->label10);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox1->ForeColor = System::Drawing::Color::White;
			this->groupBox1->Location = System::Drawing::Point(0, 60);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(1096, 499);
			this->groupBox1->TabIndex = 10;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Informaiion";
			// 
			// BCancel
			// 
			this->BCancel->BackColor = System::Drawing::Color::Black;
			this->BCancel->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->BCancel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->BCancel->Location = System::Drawing::Point(218, 358);
			this->BCancel->Name = L"BCancel";
			this->BCancel->Size = System::Drawing::Size(144, 39);
			this->BCancel->TabIndex = 15;
			this->BCancel->Text = L"Cancel";
			this->BCancel->UseVisualStyleBackColor = false;
			this->BCancel->Click += gcnew System::EventHandler(this, &MyForm::BCancel_Click);
			// 
			// BSave
			// 
			this->BSave->BackColor = System::Drawing::Color::Black;
			this->BSave->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BSave->Enabled = false;
			this->BSave->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->BSave->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->BSave->Location = System::Drawing::Point(48, 358);
			this->BSave->Name = L"BSave";
			this->BSave->Size = System::Drawing::Size(144, 39);
			this->BSave->TabIndex = 14;
			this->BSave->Text = L"Save";
			this->BSave->UseVisualStyleBackColor = false;
			this->BSave->Click += gcnew System::EventHandler(this, &MyForm::BSave_Click);
			// 
			// BDelCategory
			// 
			this->BDelCategory->BackColor = System::Drawing::Color::Black;
			this->BDelCategory->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BDelCategory->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->BDelCategory->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->BDelCategory->Location = System::Drawing::Point(880, 198);
			this->BDelCategory->Name = L"BDelCategory";
			this->BDelCategory->Size = System::Drawing::Size(136, 39);
			this->BDelCategory->TabIndex = 13;
			this->BDelCategory->Text = L"Del Category";
			this->BDelCategory->UseVisualStyleBackColor = false;
			this->BDelCategory->Click += gcnew System::EventHandler(this, &MyForm::BDelCategory_Click);
			// 
			// BAddCategory
			// 
			this->BAddCategory->BackColor = System::Drawing::Color::Black;
			this->BAddCategory->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BAddCategory->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->BAddCategory->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->BAddCategory->Location = System::Drawing::Point(722, 198);
			this->BAddCategory->Name = L"BAddCategory";
			this->BAddCategory->Size = System::Drawing::Size(144, 39);
			this->BAddCategory->TabIndex = 12;
			this->BAddCategory->Text = L"Add Category";
			this->BAddCategory->UseVisualStyleBackColor = false;
			this->BAddCategory->Click += gcnew System::EventHandler(this, &MyForm::BAddCategory_Click);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16));
			this->label15->Location = System::Drawing::Point(717, 51);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(197, 59);
			this->label15->TabIndex = 11;
			this->label15->Text = L"Category";
			// 
			// TProductCategory
			// 
			this->TProductCategory->FormattingEnabled = true;
			this->TProductCategory->Location = System::Drawing::Point(722, 99);
			this->TProductCategory->Name = L"TProductCategory";
			this->TProductCategory->Size = System::Drawing::Size(294, 73);
			this->TProductCategory->TabIndex = 10;
			// 
			// TProductID
			// 
			this->TProductID->Location = System::Drawing::Point(376, 96);
			this->TProductID->Name = L"TProductID";
			this->TProductID->Size = System::Drawing::Size(224, 71);
			this->TProductID->TabIndex = 9;
			this->TProductID->TextChanged += gcnew System::EventHandler(this, &MyForm::TProductName_TextChanged);
			// 
			// TProductQuantity
			// 
			this->TProductQuantity->Location = System::Drawing::Point(376, 201);
			this->TProductQuantity->Name = L"TProductQuantity";
			this->TProductQuantity->Size = System::Drawing::Size(224, 71);
			this->TProductQuantity->TabIndex = 8;
			this->TProductQuantity->TextChanged += gcnew System::EventHandler(this, &MyForm::TProductName_TextChanged);
			// 
			// TProductPrice
			// 
			this->TProductPrice->Location = System::Drawing::Point(47, 201);
			this->TProductPrice->Name = L"TProductPrice";
			this->TProductPrice->Size = System::Drawing::Size(224, 71);
			this->TProductPrice->TabIndex = 7;
			this->TProductPrice->TextChanged += gcnew System::EventHandler(this, &MyForm::TProductName_TextChanged);
			// 
			// TProductName
			// 
			this->TProductName->Location = System::Drawing::Point(47, 96);
			this->TProductName->Name = L"TProductName";
			this->TProductName->Size = System::Drawing::Size(224, 71);
			this->TProductName->TabIndex = 6;
			this->TProductName->TextChanged += gcnew System::EventHandler(this, &MyForm::TProductName_TextChanged);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16));
			this->label14->Location = System::Drawing::Point(371, 151);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(188, 59);
			this->label14->TabIndex = 5;
			this->label14->Text = L"Quantity";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16));
			this->label12->Location = System::Drawing::Point(43, 155);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(116, 59);
			this->label12->TabIndex = 4;
			this->label12->Text = L"Price";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16));
			this->label11->Location = System::Drawing::Point(371, 51);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(66, 59);
			this->label11->TabIndex = 3;
			this->label11->Text = L"ID";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16));
			this->label10->Location = System::Drawing::Point(43, 51);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(138, 59);
			this->label10->TabIndex = 2;
			this->label10->Text = L"Name";
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->label8);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1096, 60);
			this->panel1->TabIndex = 1;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(393, 13);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(526, 65);
			this->label8->TabIndex = 0;
			this->label8->Text = L"Fill Product Information";
			// 
			// PNav
			// 
			this->PNav->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(11)), static_cast<System::Int32>(static_cast<System::Byte>(11)),
				static_cast<System::Int32>(static_cast<System::Byte>(11)));
			this->PNav->Controls->Add(this->BAddProduct);
			this->PNav->Dock = System::Windows::Forms::DockStyle::Left;
			this->PNav->Location = System::Drawing::Point(0, 73);
			this->PNav->Name = L"PNav";
			this->PNav->Size = System::Drawing::Size(152, 559);
			this->PNav->TabIndex = 0;
			// 
			// BAddProduct
			// 
			this->BAddProduct->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(11)), static_cast<System::Int32>(static_cast<System::Byte>(11)),
				static_cast<System::Int32>(static_cast<System::Byte>(11)));
			this->BAddProduct->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BAddProduct->FlatAppearance->BorderSize = 0;
			this->BAddProduct->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->BAddProduct->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->BAddProduct->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"BAddProduct.Image")));
			this->BAddProduct->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->BAddProduct->Location = System::Drawing::Point(0, 19);
			this->BAddProduct->Name = L"BAddProduct";
			this->BAddProduct->Size = System::Drawing::Size(152, 41);
			this->BAddProduct->TabIndex = 0;
			this->BAddProduct->Text = L"Add Product";
			this->BAddProduct->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->BAddProduct->UseVisualStyleBackColor = false;
			this->BAddProduct->Click += gcnew System::EventHandler(this, &MyForm::BAddProduct_Click);
			// 
			// PHeader
			// 
			this->PHeader->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(11)), static_cast<System::Int32>(static_cast<System::Byte>(11)),
				static_cast<System::Int32>(static_cast<System::Byte>(11)));
			this->PHeader->Controls->Add(this->BLogOut);
			this->PHeader->Controls->Add(this->LLogo);
			this->PHeader->Dock = System::Windows::Forms::DockStyle::Top;
			this->PHeader->Location = System::Drawing::Point(0, 0);
			this->PHeader->Name = L"PHeader";
			this->PHeader->Size = System::Drawing::Size(1248, 73);
			this->PHeader->TabIndex = 1;
			// 
			// BLogOut
			// 
			this->BLogOut->BackColor = System::Drawing::Color::Black;
			this->BLogOut->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BLogOut->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->BLogOut->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->BLogOut->Location = System::Drawing::Point(1092, 21);
			this->BLogOut->Name = L"BLogOut";
			this->BLogOut->Size = System::Drawing::Size(144, 39);
			this->BLogOut->TabIndex = 15;
			this->BLogOut->Text = L"Logout";
			this->BLogOut->UseVisualStyleBackColor = false;
			this->BLogOut->Click += gcnew System::EventHandler(this, &MyForm::BLogOut_Click);
			// 
			// LLogo
			// 
			this->LLogo->AutoSize = true;
			this->LLogo->Location = System::Drawing::Point(7, 22);
			this->LLogo->Name = L"LLogo";
			this->LLogo->Size = System::Drawing::Size(287, 65);
			this->LLogo->TabIndex = 0;
			this->LLogo->Text = L"MarketPlace";
			// 
			// panel6
			// 
			this->panel6->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel6->Controls->Add(this->textBox3);
			this->panel6->Controls->Add(this->label18);
			this->panel6->Location = System::Drawing::Point(3, 3);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(248, 171);
			this->panel6->TabIndex = 0;
			// 
			// textBox3
			// 
			this->textBox3->Enabled = false;
			this->textBox3->Location = System::Drawing::Point(27, 101);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(192, 31);
			this->textBox3->TabIndex = 1;
			this->textBox3->Text = L"name prodcut test";
			this->textBox3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(44, 38);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(142, 25);
			this->label18->TabIndex = 0;
			this->label18->Text = L"ProductName";
			// 
			// PCustomer
			// 
			this->PCustomer->Controls->Add(this->PCart);
			this->PCustomer->Controls->Add(this->PCSBCategory);
			this->PCustomer->Controls->Add(this->PSearchName);
			this->PCustomer->Controls->Add(this->PCNav);
			this->PCustomer->Controls->Add(this->PCHeader);
			this->PCustomer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PCustomer->Location = System::Drawing::Point(0, 0);
			this->PCustomer->Name = L"PCustomer";
			this->PCustomer->Size = System::Drawing::Size(1248, 632);
			this->PCustomer->TabIndex = 1;
			this->PCustomer->Visible = false;
			// 
			// PCart
			// 
			this->PCart->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->PCart->Controls->Add(this->lTotalPrice);
			this->PCart->Controls->Add(this->BConfirm);
			this->PCart->Controls->Add(this->flowLayoutPanel2);
			this->PCart->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PCart->Location = System::Drawing::Point(170, 73);
			this->PCart->Name = L"PCart";
			this->PCart->Size = System::Drawing::Size(1078, 559);
			this->PCart->TabIndex = 7;
			this->PCart->Visible = false;
			// 
			// lTotalPrice
			// 
			this->lTotalPrice->AutoSize = true;
			this->lTotalPrice->Location = System::Drawing::Point(478, 20);
			this->lTotalPrice->Name = L"lTotalPrice";
			this->lTotalPrice->Size = System::Drawing::Size(244, 65);
			this->lTotalPrice->TabIndex = 2;
			this->lTotalPrice->Text = L"Total Price";
			// 
			// BConfirm
			// 
			this->BConfirm->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BConfirm->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->BConfirm->Location = System::Drawing::Point(478, 67);
			this->BConfirm->Name = L"BConfirm";
			this->BConfirm->Size = System::Drawing::Size(120, 44);
			this->BConfirm->TabIndex = 1;
			this->BConfirm->Text = L"Confirm";
			this->BConfirm->UseVisualStyleBackColor = true;
			this->BConfirm->Click += gcnew System::EventHandler(this, &MyForm::BConfirm_Click);
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->Controls->Add(this->LBDisplayProducts);
			this->flowLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Left;
			this->flowLayoutPanel2->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Padding = System::Windows::Forms::Padding(20);
			this->flowLayoutPanel2->Size = System::Drawing::Size(458, 557);
			this->flowLayoutPanel2->TabIndex = 0;
			// 
			// LBDisplayProducts
			// 
			this->LBDisplayProducts->FormattingEnabled = true;
			this->LBDisplayProducts->ItemHeight = 65;
			this->LBDisplayProducts->Location = System::Drawing::Point(23, 23);
			this->LBDisplayProducts->Name = L"LBDisplayProducts";
			this->LBDisplayProducts->Size = System::Drawing::Size(406, 394);
			this->LBDisplayProducts->TabIndex = 0;
			// 
			// PCSBCategory
			// 
			this->PCSBCategory->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->PCSBCategory->Controls->Add(this->flowLayoutPanel1);
			this->PCSBCategory->Controls->Add(this->panel8);
			this->PCSBCategory->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PCSBCategory->Location = System::Drawing::Point(170, 73);
			this->PCSBCategory->Name = L"PCSBCategory";
			this->PCSBCategory->Size = System::Drawing::Size(1078, 559);
			this->PCSBCategory->TabIndex = 4;
			this->PCSBCategory->Visible = false;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->listBoxProductCat);
			this->flowLayoutPanel1->Controls->Add(this->panel9);
			this->flowLayoutPanel1->Controls->Add(this->panel10);
			this->flowLayoutPanel1->Controls->Add(this->panel11);
			this->flowLayoutPanel1->Controls->Add(this->panel12);
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel1->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			this->flowLayoutPanel1->Location = System::Drawing::Point(378, 0);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Padding = System::Windows::Forms::Padding(5);
			this->flowLayoutPanel1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->flowLayoutPanel1->Size = System::Drawing::Size(698, 557);
			this->flowLayoutPanel1->TabIndex = 3;
			this->flowLayoutPanel1->Visible = false;
			// 
			// listBoxProductCat
			// 
			this->listBoxProductCat->FormattingEnabled = true;
			this->listBoxProductCat->ItemHeight = 65;
			this->listBoxProductCat->Location = System::Drawing::Point(8, 8);
			this->listBoxProductCat->Name = L"listBoxProductCat";
			this->listBoxProductCat->Size = System::Drawing::Size(237, 394);
			this->listBoxProductCat->TabIndex = 0;
			this->listBoxProductCat->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBoxProductCat_SelectedIndexChanged);
			// 
			// panel9
			// 
			this->panel9->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel9->Controls->Add(this->label20);
			this->panel9->Location = System::Drawing::Point(8, 408);
			this->panel9->Name = L"panel9";
			this->panel9->Size = System::Drawing::Size(198, 101);
			this->panel9->TabIndex = 3;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(9, 36);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(180, 65);
			this->label20->TabIndex = 0;
			this->label20->Text = L"Price :  ";
			// 
			// panel10
			// 
			this->panel10->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel10->Controls->Add(this->label22);
			this->panel10->Location = System::Drawing::Point(251, 8);
			this->panel10->Name = L"panel10";
			this->panel10->Size = System::Drawing::Size(198, 101);
			this->panel10->TabIndex = 4;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(3, 36);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(258, 65);
			this->label22->TabIndex = 0;
			this->label22->Text = L"Quantity :  ";
			// 
			// panel11
			// 
			this->panel11->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel11->Controls->Add(this->TItem);
			this->panel11->Controls->Add(this->label23);
			this->panel11->Location = System::Drawing::Point(251, 115);
			this->panel11->Name = L"panel11";
			this->panel11->Size = System::Drawing::Size(202, 101);
			this->panel11->TabIndex = 6;
			// 
			// TItem
			// 
			this->TItem->Location = System::Drawing::Point(72, 36);
			this->TItem->Name = L"TItem";
			this->TItem->Size = System::Drawing::Size(121, 71);
			this->TItem->TabIndex = 1;
			this->TItem->TextChanged += gcnew System::EventHandler(this, &MyForm::TItem_TextChanged);
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(3, 36);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(123, 65);
			this->label23->TabIndex = 0;
			this->label23->Text = L"Item";
			// 
			// panel12
			// 
			this->panel12->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel12->Controls->Add(this->button3);
			this->panel12->Controls->Add(this->button4);
			this->panel12->Location = System::Drawing::Point(251, 222);
			this->panel12->Name = L"panel12";
			this->panel12->Size = System::Drawing::Size(248, 64);
			this->panel12->TabIndex = 5;
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::Black;
			this->button3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button3->Enabled = false;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->button3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->button3->Location = System::Drawing::Point(9, 14);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(101, 39);
			this->button3->TabIndex = 16;
			this->button3->Text = L"AddItem";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::Black;
			this->button4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->button4->ForeColor = System::Drawing::Color::White;
			this->button4->Location = System::Drawing::Point(116, 14);
			this->button4->Margin = System::Windows::Forms::Padding(3, 3, 3, 20);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(117, 39);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Cancel";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// panel8
			// 
			this->panel8->Controls->Add(this->BSearchCatgory);
			this->panel8->Controls->Add(this->TSearchCategory);
			this->panel8->Controls->Add(this->label19);
			this->panel8->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel8->Location = System::Drawing::Point(0, 0);
			this->panel8->Name = L"panel8";
			this->panel8->Size = System::Drawing::Size(378, 557);
			this->panel8->TabIndex = 1;
			// 
			// BSearchCatgory
			// 
			this->BSearchCatgory->BackColor = System::Drawing::Color::Black;
			this->BSearchCatgory->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->BSearchCatgory->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16));
			this->BSearchCatgory->Location = System::Drawing::Point(16, 73);
			this->BSearchCatgory->Name = L"BSearchCatgory";
			this->BSearchCatgory->Size = System::Drawing::Size(137, 47);
			this->BSearchCatgory->TabIndex = 2;
			this->BSearchCatgory->Text = L"Search";
			this->BSearchCatgory->UseVisualStyleBackColor = false;
			this->BSearchCatgory->Click += gcnew System::EventHandler(this, &MyForm::BSearchCatgory_Click);
			// 
			// TSearchCategory
			// 
			this->TSearchCategory->Location = System::Drawing::Point(195, 17);
			this->TSearchCategory->Name = L"TSearchCategory";
			this->TSearchCategory->Size = System::Drawing::Size(162, 71);
			this->TSearchCategory->TabIndex = 1;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->label19->Location = System::Drawing::Point(14, 17);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(314, 51);
			this->label19->TabIndex = 0;
			this->label19->Text = L"Product Category";
			// 
			// PSearchName
			// 
			this->PSearchName->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->PSearchName->Controls->Add(this->PINFOProduct);
			this->PSearchName->Controls->Add(this->PSearchTools);
			this->PSearchName->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PSearchName->Location = System::Drawing::Point(170, 73);
			this->PSearchName->Name = L"PSearchName";
			this->PSearchName->Size = System::Drawing::Size(1078, 559);
			this->PSearchName->TabIndex = 4;
			this->PSearchName->Visible = false;
			// 
			// PINFOProduct
			// 
			this->PINFOProduct->Controls->Add(this->listProducts);
			this->PINFOProduct->Controls->Add(this->panel2);
			this->PINFOProduct->Controls->Add(this->panel4);
			this->PINFOProduct->Controls->Add(this->panel5);
			this->PINFOProduct->Controls->Add(this->panel7);
			this->PINFOProduct->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PINFOProduct->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			this->PINFOProduct->Location = System::Drawing::Point(378, 0);
			this->PINFOProduct->Name = L"PINFOProduct";
			this->PINFOProduct->Padding = System::Windows::Forms::Padding(5);
			this->PINFOProduct->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->PINFOProduct->Size = System::Drawing::Size(698, 557);
			this->PINFOProduct->TabIndex = 2;
			this->PINFOProduct->Visible = false;
			// 
			// listProducts
			// 
			this->listProducts->FormattingEnabled = true;
			this->listProducts->ItemHeight = 65;
			this->listProducts->Location = System::Drawing::Point(8, 8);
			this->listProducts->Name = L"listProducts";
			this->listProducts->Size = System::Drawing::Size(237, 394);
			this->listProducts->TabIndex = 0;
			this->listProducts->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listProducts_SelectedIndexChanged);
			// 
			// panel2
			// 
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->LabelPrice);
			this->panel2->Location = System::Drawing::Point(8, 408);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(198, 101);
			this->panel2->TabIndex = 3;
			// 
			// LabelPrice
			// 
			this->LabelPrice->AutoSize = true;
			this->LabelPrice->Location = System::Drawing::Point(9, 36);
			this->LabelPrice->Name = L"LabelPrice";
			this->LabelPrice->Size = System::Drawing::Size(180, 65);
			this->LabelPrice->TabIndex = 0;
			this->LabelPrice->Text = L"Price :  ";
			// 
			// panel4
			// 
			this->panel4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel4->Controls->Add(this->LabelQuantity);
			this->panel4->Location = System::Drawing::Point(251, 8);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(198, 101);
			this->panel4->TabIndex = 4;
			// 
			// LabelQuantity
			// 
			this->LabelQuantity->AutoSize = true;
			this->LabelQuantity->Location = System::Drawing::Point(3, 36);
			this->LabelQuantity->Name = L"LabelQuantity";
			this->LabelQuantity->Size = System::Drawing::Size(258, 65);
			this->LabelQuantity->TabIndex = 0;
			this->LabelQuantity->Text = L"Quantity :  ";
			// 
			// panel5
			// 
			this->panel5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel5->Controls->Add(this->TItemNo);
			this->panel5->Controls->Add(this->label21);
			this->panel5->Location = System::Drawing::Point(251, 115);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(202, 101);
			this->panel5->TabIndex = 6;
			// 
			// TItemNo
			// 
			this->TItemNo->Location = System::Drawing::Point(72, 36);
			this->TItemNo->Name = L"TItemNo";
			this->TItemNo->Size = System::Drawing::Size(121, 71);
			this->TItemNo->TabIndex = 1;
			this->TItemNo->TextChanged += gcnew System::EventHandler(this, &MyForm::TItemNo_TextChanged);
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(3, 36);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(123, 65);
			this->label21->TabIndex = 0;
			this->label21->Text = L"Item";
			// 
			// panel7
			// 
			this->panel7->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel7->Controls->Add(this->button2);
			this->panel7->Controls->Add(this->CaneclBuy);
			this->panel7->Location = System::Drawing::Point(251, 222);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(248, 64);
			this->panel7->TabIndex = 5;
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Black;
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->Enabled = false;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->button2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->button2->Location = System::Drawing::Point(9, 14);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(101, 39);
			this->button2->TabIndex = 16;
			this->button2->Text = L"AddItem";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// CaneclBuy
			// 
			this->CaneclBuy->BackColor = System::Drawing::Color::Black;
			this->CaneclBuy->Cursor = System::Windows::Forms::Cursors::Hand;
			this->CaneclBuy->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->CaneclBuy->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->CaneclBuy->ForeColor = System::Drawing::Color::White;
			this->CaneclBuy->Location = System::Drawing::Point(116, 14);
			this->CaneclBuy->Margin = System::Windows::Forms::Padding(3, 3, 3, 20);
			this->CaneclBuy->Name = L"CaneclBuy";
			this->CaneclBuy->Size = System::Drawing::Size(117, 39);
			this->CaneclBuy->TabIndex = 3;
			this->CaneclBuy->Text = L"Cancel";
			this->CaneclBuy->UseVisualStyleBackColor = false;
			this->CaneclBuy->Click += gcnew System::EventHandler(this, &MyForm::CaneclBuy_Click);
			// 
			// PSearchTools
			// 
			this->PSearchTools->Controls->Add(this->BSearch);
			this->PSearchTools->Controls->Add(this->textBox1);
			this->PSearchTools->Controls->Add(this->label17);
			this->PSearchTools->Dock = System::Windows::Forms::DockStyle::Left;
			this->PSearchTools->Location = System::Drawing::Point(0, 0);
			this->PSearchTools->Name = L"PSearchTools";
			this->PSearchTools->Size = System::Drawing::Size(378, 557);
			this->PSearchTools->TabIndex = 0;
			// 
			// BSearch
			// 
			this->BSearch->BackColor = System::Drawing::Color::Black;
			this->BSearch->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->BSearch->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16));
			this->BSearch->Location = System::Drawing::Point(16, 73);
			this->BSearch->Name = L"BSearch";
			this->BSearch->Size = System::Drawing::Size(137, 47);
			this->BSearch->TabIndex = 2;
			this->BSearch->Text = L"Search";
			this->BSearch->UseVisualStyleBackColor = false;
			this->BSearch->Click += gcnew System::EventHandler(this, &MyForm::BSearch_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(195, 17);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(162, 71);
			this->textBox1->TabIndex = 1;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(13, 12);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(332, 65);
			this->label17->TabIndex = 0;
			this->label17->Text = L"Product Name";
			// 
			// PCNav
			// 
			this->PCNav->Controls->Add(this->BSearchByName);
			this->PCNav->Controls->Add(this->BSearchByCate);
			this->PCNav->Controls->Add(this->BCart);
			this->PCNav->Dock = System::Windows::Forms::DockStyle::Left;
			this->PCNav->Location = System::Drawing::Point(0, 73);
			this->PCNav->Name = L"PCNav";
			this->PCNav->Size = System::Drawing::Size(170, 559);
			this->PCNav->TabIndex = 3;
			// 
			// BSearchByName
			// 
			this->BSearchByName->BackColor = System::Drawing::Color::Black;
			this->BSearchByName->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BSearchByName->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->BSearchByName->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->BSearchByName->ForeColor = System::Drawing::Color::White;
			this->BSearchByName->Location = System::Drawing::Point(3, 3);
			this->BSearchByName->Margin = System::Windows::Forms::Padding(3, 3, 3, 20);
			this->BSearchByName->Name = L"BSearchByName";
			this->BSearchByName->Size = System::Drawing::Size(167, 42);
			this->BSearchByName->TabIndex = 0;
			this->BSearchByName->Text = L"Search By Name";
			this->BSearchByName->UseVisualStyleBackColor = false;
			this->BSearchByName->Click += gcnew System::EventHandler(this, &MyForm::BSearchByName_Click);
			// 
			// BSearchByCate
			// 
			this->BSearchByCate->BackColor = System::Drawing::Color::Black;
			this->BSearchByCate->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BSearchByCate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->BSearchByCate->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
			this->BSearchByCate->ForeColor = System::Drawing::Color::White;
			this->BSearchByCate->Location = System::Drawing::Point(3, 68);
			this->BSearchByCate->Margin = System::Windows::Forms::Padding(3, 3, 3, 20);
			this->BSearchByCate->Name = L"BSearchByCate";
			this->BSearchByCate->Size = System::Drawing::Size(167, 42);
			this->BSearchByCate->TabIndex = 1;
			this->BSearchByCate->Text = L"Search By Category";
			this->BSearchByCate->UseVisualStyleBackColor = false;
			this->BSearchByCate->Click += gcnew System::EventHandler(this, &MyForm::BSearchByCate_Click);
			// 
			// BCart
			// 
			this->BCart->BackColor = System::Drawing::Color::Black;
			this->BCart->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BCart->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->BCart->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->BCart->ForeColor = System::Drawing::Color::White;
			this->BCart->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"BCart.Image")));
			this->BCart->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->BCart->Location = System::Drawing::Point(3, 133);
			this->BCart->Name = L"BCart";
			this->BCart->Size = System::Drawing::Size(167, 42);
			this->BCart->TabIndex = 2;
			this->BCart->Text = L"Cart";
			this->BCart->UseVisualStyleBackColor = false;
			this->BCart->Click += gcnew System::EventHandler(this, &MyForm::BCart_Click);
			// 
			// PCHeader
			// 
			this->PCHeader->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(11)), static_cast<System::Int32>(static_cast<System::Byte>(11)),
				static_cast<System::Int32>(static_cast<System::Byte>(11)));
			this->PCHeader->Controls->Add(this->BCLogout);
			this->PCHeader->Controls->Add(this->label16);
			this->PCHeader->Dock = System::Windows::Forms::DockStyle::Top;
			this->PCHeader->Location = System::Drawing::Point(0, 0);
			this->PCHeader->Name = L"PCHeader";
			this->PCHeader->Size = System::Drawing::Size(1248, 73);
			this->PCHeader->TabIndex = 2;
			// 
			// BCLogout
			// 
			this->BCLogout->BackColor = System::Drawing::Color::Black;
			this->BCLogout->Cursor = System::Windows::Forms::Cursors::Hand;
			this->BCLogout->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->BCLogout->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
			this->BCLogout->Location = System::Drawing::Point(1092, 21);
			this->BCLogout->Name = L"BCLogout";
			this->BCLogout->Size = System::Drawing::Size(144, 39);
			this->BCLogout->TabIndex = 15;
			this->BCLogout->Text = L"Logout";
			this->BCLogout->UseVisualStyleBackColor = false;
			this->BCLogout->Click += gcnew System::EventHandler(this, &MyForm::BCLogout_Click);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(7, 22);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(287, 65);
			this->label16->TabIndex = 0;
			this->label16->Text = L"MarketPlace";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(27, 65);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlText;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(1248, 632);
			this->Controls->Add(this->PCustomer);
			this->Controls->Add(this->PMainProgramm);
			this->Controls->Add(this->PRegistration);
			this->Controls->Add(this->PSignIn);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::Color::White;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MarketPlace";
			this->PRegistration->ResumeLayout(false);
			this->PRegistration->PerformLayout();
			this->PInformationCustomer->ResumeLayout(false);
			this->PInformationCustomer->PerformLayout();
			this->PSignIn->ResumeLayout(false);
			this->PSignIn->PerformLayout();
			this->PMainProgramm->ResumeLayout(false);
			this->PContent->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->PNav->ResumeLayout(false);
			this->PHeader->ResumeLayout(false);
			this->PHeader->PerformLayout();
			this->panel6->ResumeLayout(false);
			this->panel6->PerformLayout();
			this->PCustomer->ResumeLayout(false);
			this->PCart->ResumeLayout(false);
			this->PCart->PerformLayout();
			this->flowLayoutPanel2->ResumeLayout(false);
			this->PCSBCategory->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->panel9->ResumeLayout(false);
			this->panel9->PerformLayout();
			this->panel10->ResumeLayout(false);
			this->panel10->PerformLayout();
			this->panel11->ResumeLayout(false);
			this->panel11->PerformLayout();
			this->panel12->ResumeLayout(false);
			this->panel8->ResumeLayout(false);
			this->panel8->PerformLayout();
			this->PSearchName->ResumeLayout(false);
			this->PINFOProduct->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			this->panel7->ResumeLayout(false);
			this->PSearchTools->ResumeLayout(false);
			this->PSearchTools->PerformLayout();
			this->PCNav->ResumeLayout(false);
			this->PCHeader->ResumeLayout(false);
			this->PCHeader->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	// Signup
	private: System::Void BSignUP_Click(System::Object^ sender, System::EventArgs^ e) {
		PRegistration->Visible = true;
	}
    // Check Customer Feild
	void Checked() {
		if (RCustomer->Checked) {
			if (TRegUsername->Text->Length < 1 || TRegID->Text->Length < 8 || TRegPhone->Text->Length < 8 || TRegAddress->Text->Length < 8 || TRegEmail->Text->Length < 1 || TRegPassword->Text->Length < 8)
				BSubmit->Enabled = false;
			else
				BSubmit->Enabled = true;
		}
		else {
			if (TRegUsername->Text->Length < 1 || TRegID->Text->Length < 8 || TRegPassword->Text->Length < 8 || TRegEmail->Text->Length < 1)
				BSubmit->Enabled = false;
			else
				BSubmit->Enabled = true;
		}
	}
	private: System::Void validButtonChangeText(System::Object^ sender, System::EventArgs^ e) {
		Checked();
	}
	private: System::Void RSeller_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		Checked();
		TRegAddress->Clear();
		TRegPhone->Clear();
	}
	// Clear Data Feild
	void clearDataRegist() {
		TRegUsername->Clear();
		TRegEmail->Clear();
		TRegPassword->Clear();
		TRegID->Clear();
		TRegAddress->Clear();
		TRegPhone->Clear();
	}
	// Submit Information
	private: System::Void BSubmit_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ message = "";
		for each (KeyValuePair<String^, Client^> var in ClientInformation)
		{
			if (var.Value->getName() == TRegUsername->Text)
				message = "USERNAME IS EXIST";
			else if (var.Value->getID() == TRegID->Text)
				message += "ID IS EXIST ";
			else if (var.Value->getEmail() == TRegEmail->Text)
				message += "Email IS EXIST ";
		}
		if (TRegEmail->Text->Contains("@")) {
			String^ lengthBeforeMark = TRegEmail->Text->Substring(0, TRegEmail->Text->IndexOf("@"));
			if (lengthBeforeMark->Length < 4) {
				message += "Email Must be Like Email@mail.com ";
			}
		}
		else
		{
			message += "Email hasn't '@'";
		}
		if (message != "") {
			MessageBox::Show(message, "INVALID DATA");
			message = "";
		}
		else {
			if (RCustomer->Checked)
				ClientInformation.Add(
					TRegID->Text,
					gcnew Client(
						TRegID->Text,
						TRegUsername->Text,
						TRegEmail->Text,
						TRegPassword->Text,
						TRegAddress->Text,
						TRegPhone->Text,
						false
					)
				);
			else
				ClientInformation.Add(
					TRegID->Text,
					gcnew Client(
						TRegID->Text,
						TRegUsername->Text,
						TRegEmail->Text,
						TRegPassword->Text,
						"",
						"",
						true
					)
				);
			PRegistration->Visible = false;
			clearDataRegist();
		}
	}
	// Display more info
	private: System::Void RCustomer_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		Checked();
		if (RCustomer->Checked) {
			PInformationCustomer->Visible = true;
		}
		else {
			PInformationCustomer->Visible = false;
		}
	}
	// Login
	private: System::Void BLogin_Click(System::Object^ sender, System::EventArgs^ e) {
		bool ValidLogin = false;
		for each (KeyValuePair<String^, Client^> var in ClientInformation)
		{
			if (var.Value->getEmail() == TSignInEmail->Text && var.Value->getPassword() == TSignInPassword->Text) {
				ValidLogin = true;
				ClientKey = var.Key;
				break;
			}
		}
		if (ValidLogin) {
			if (ClientInformation[ClientKey]->getIsSeller()) {
				PMainProgramm->Visible = true;
			}
			else
			{
				PCustomer->Visible = true;
			}
		}
		else {
			MessageBox::Show("Email && Password Doesn't Match");
		}
	}
	// return to login
	private: System::Void BBack_Click(System::Object^ sender, System::EventArgs^ e) {
		PRegistration->Visible = false;
		clearDataRegist();
	}
	// logout
	private: System::Void BLogOut_Click(System::Object^ sender, System::EventArgs^ e) {
		PMainProgramm->Visible = false;
		TSignInEmail->Clear();
		TSignInPassword->Clear();
	}
	// display panal addproduct
	private: System::Void BAddProduct_Click(System::Object^ sender, System::EventArgs^ e) {
		PContent->Visible = true;
	}
	// disapper panal addproduct
	private: System::Void BCancel_Click(System::Object^ sender, System::EventArgs^ e) {
		PContent->Visible = false;
		clearData();
	}
	// Check product Feild
	void checkfeildProduct() {
		if (TProductID->Text->Length < 4 || TProductName->Text->Length < 1 || TProductPrice->Text->Length < 1 || TProductQuantity->Text->Length < 1 || TProductCategory->Items->Count < 1)
			BSave->Enabled = false;
		else
			BSave->Enabled = true;
	}
	private: System::Void TProductName_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		checkfeildProduct();
	}
	// Clear Data Feild
	void clearData() {
		TProductID->Clear();
		TProductName->Clear();
		TProductPrice->Clear();
		TProductQuantity->Clear();
		TProductCategory->Items->Clear();
	}
	// submit product
	private: System::Void BSave_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ message = "";
		for each (KeyValuePair<String^, Product^> var in Products)
		{
			if (var.Value->getID() == TProductID->Text)
				message += "Change ID of Product";
		}
		if (message == "")
		{
			Product^ LocalProdcut = gcnew Product(TProductID->Text, ClientInformation[ClientKey]->getID(), TProductName->Text, float::Parse(TProductPrice->Text), int::Parse(TProductQuantity->Text));
			for (int i = 0; i < localCategory.Count; i++)
				LocalProdcut->category.Add(localCategory[i]);
			localCategory.Clear();
			Products.Add(LocalProdcut->getID(),LocalProdcut);
			delete LocalProdcut;
			
			MessageBox::Show("Complete Process", "ACCEPT");
			PContent->Visible = false;
			clearData();
		}
		else
		{
			MessageBox::Show(message, "INVALID DATA");
			message = "";
		}
	}
	// add new category
	private: System::Void BAddCategory_Click(System::Object^ sender, System::EventArgs^ e) {
		if (TProductCategory->Items->Contains(TProductCategory->Text) || TProductCategory->Text == "")
			MessageBox::Show("That Category is Exist", "Invaild Data");
		else {
			TProductCategory->Items->Add(TProductCategory->Text);
			localCategory.Add(TProductCategory->Text);
			checkfeildProduct();
		}
	}
	// cancel new category
	private: System::Void BDelCategory_Click(System::Object^ sender, System::EventArgs^ e) {
		if (TProductCategory->Items->Contains(TProductCategory->Text)) {
			TProductCategory->Items->Remove(TProductCategory->Text);
			localCategory.Remove(TProductCategory->Text);
		}
		else
			MessageBox::Show("That Category Not Exist", "Invaild Data");
		checkfeildProduct();
	}
	// logout
	private: System::Void BCLogout_Click(System::Object^ sender, System::EventArgs^ e) {
		transferCartFromVectorToFile();
		PCustomer->Visible = false;
		TSignInEmail->Clear();
		TSignInPassword->Clear();
	}
	// display search panal
	private: System::Void BSearchByName_Click(System::Object^ sender, System::EventArgs^ e) {
		PSearchName->Visible = true;
		PCSBCategory->Visible = false;
		PCart->Visible = false;
	}
	// search by name
	private: System::Void BSearch_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox1->Text == "")
			MessageBox::Show("Enter Product Name", "Empty Feild");
		else
		{
			listProducts->Items->Clear();
			ProductKey.Clear();
			for each (KeyValuePair<String^, Product^> var in Products)
			{
				if (textBox1->Text == var.Value->getName())
				{
					listProducts->Items->Add("Product ID : " + var.Value->getID());
					ProductKey.Add(var.Key);
				}
			}
			if (ProductKey.Count != 0)
			{
				PINFOProduct->Visible = true;
			}
			else
			{
				MessageBox::Show("Product isn't exist", "Not Found Data");
				PINFOProduct->Visible = false;
			}
		}
	}
	// display PCSBCategory
	private: System::Void BSearchByCate_Click(System::Object^ sender, System::EventArgs^ e) {
		PCSBCategory->Visible = true;
		PSearchName->Visible = false;
		PCart->Visible = false;
	}
	// canecel buy
	private: System::Void CaneclBuy_Click(System::Object^ sender, System::EventArgs^ e) {
		PINFOProduct->Visible = false;
	}
	// display data to textbox
	private: System::Void listProducts_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (listProducts->SelectedIndex >= 0 && listProducts->SelectedIndex < ProductKey.Count) {
			LabelPrice->Text = "Price : " + Products[ProductKey[listProducts->SelectedIndex]]->getPrice().ToString();
			LabelQuantity->Text = "Quantity : " + Products[ProductKey[listProducts->SelectedIndex]]->getQuantity().ToString();
		}
	}
	// add product to cart
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (int::Parse(TItemNo->Text) > 0 && int::Parse(TItemNo->Text) <= int::Parse(LabelQuantity->Text->Split(':')[1]))
		{
			Products[ProductKey[listProducts->SelectedIndex]]->setQuantity(Products[ProductKey[	listProducts->SelectedIndex]]->getQuantity() - int::Parse(TItemNo->Text));
			LabelQuantity->Text = "Quantity : " + Products[ProductKey[listProducts->SelectedIndex]]->getQuantity().ToString();
			ClientInformation[ClientKey]->cart->addProductToList(gcnew Product(Products[ProductKey[listProducts->SelectedIndex]], int::Parse(TItemNo->Text)), int::Parse(TItemNo->Text) * Products[ProductKey[listProducts->SelectedIndex]]->getPrice());
			MessageBox::Show("Complete Process", "Great");
		}
		else
		{
			MessageBox::Show("enter number from 1 to " + Products[ProductKey[listProducts->SelectedIndex]]->getQuantity().ToString(), "Invaild Data");
		}
	}
	private: System::Void TItemNo_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		if (TItemNo->Text->Length > 0)
			button2->Enabled = true;
		else
			button2->Enabled = false;
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		flowLayoutPanel1->Visible = false;
	}
	// category search
	private: System::Void BSearchCatgory_Click(System::Object^ sender, System::EventArgs^ e) {
		if (TSearchCategory->Text == "")
			MessageBox::Show("Enter Product Category", "Empty Feild");
		else
		{
			listBoxProductCat->Items->Clear();
			for each (KeyValuePair<String^, Product^> var in Products)
			{
				if (var.Value->category.Contains(TSearchCategory->Text))
					listBoxProductCat->Items->Add(var.Value->getName());
			}
			if (listBoxProductCat->Items->Count != 0) {
				flowLayoutPanel1->Visible = true;
			}
			else
			{
				MessageBox::Show("Category isn't exist", "Not Found Data");
			}
		}
	}
	private: System::Void listBoxProductCat_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		for each (KeyValuePair<String ^, Product ^> var in Products)
		{
			if (listBoxProductCat->Text == var.Value->getName() && var.Value->category.Contains(TSearchCategory->Text)) {
				productCategoryKey = var.Key;
				label20->Text = "Price : " + var.Value->getPrice().ToString();
				label22->Text = "Quantity : " + var.Value->getQuantity().ToString();
			}
		}
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		if (int::Parse(TItem->Text) > 0 && int::Parse(TItem->Text) <= Products[productCategoryKey]->getQuantity()) {
			Products[productCategoryKey]->setQuantity(Products[productCategoryKey]->getQuantity() - int::Parse(TItem->Text));
			label22->Text = "Quantity : " + Products[productCategoryKey]->getQuantity();
			ClientInformation[ClientKey]->cart->addProductToList(gcnew Product(Products[productCategoryKey], int::Parse(TItem->Text)), int::Parse(TItem->Text) * Products[productCategoryKey]->getPrice());
			MessageBox::Show("Complete Process", "Great");
		}
		else
		{
			MessageBox::Show("enter number from 1 to " + Products[productCategoryKey]->getQuantity(), "Invaild Data");
		}
	}
	private: System::Void TItem_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		if (TItem->Text->Length > 0)
			button3->Enabled = true;
		else
			button3->Enabled = false;
	}
	private: System::Void BCart_Click(System::Object^ sender, System::EventArgs^ e) {
		PCSBCategory->Visible = false;
		PSearchName->Visible = false;
		PCart->Visible = true;
		LBDisplayProducts->Items->Clear();
		for each (Product ^ var in ClientInformation[ClientKey]->cart->listOFProdcut)
		{
			LBDisplayProducts->Items->Add(var->getName() + " price " + var->getPrice());
		}
		lTotalPrice->Text = "Total Price " + ClientInformation[ClientKey]->cart->getNetPrice().ToString();
	}
private: System::Void BConfirm_Click(System::Object^ sender, System::EventArgs^ e) {
	ClientInformation[ClientKey]->cart->listOFProdcut.Clear();
	LBDisplayProducts->Items->Clear();
	lTotalPrice->Text = "Total Price " + "0";
}
};
}