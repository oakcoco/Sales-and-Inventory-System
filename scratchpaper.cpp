#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;

void addCustomers()
{
	fstream customersData;
	customersData.open("customers.csv", ios::app | ios::out);

	string name, userID;

	cout << "Add Customer Data." << endl;
	cout << "Enter ID: ";
	cin.ignore();
	getline(cin, userID);
	cout << "Enter Name: ";
	cin.ignore();
	getline(cin, name);

	customersData << endl
				  << userID << "," << name;

	cout << endl
		 << "Customer Data Added Successfuly!"
		 << endl;

	customersData.close();
}
void inventoryReport()
{
	// choices between a single item, all items and the category.
	int choice, choiceCategory;

	string filename;

	cout << "How would you like to report the inventory? Single Item (1) or All Items (2): ";
	cin >> choice;

	while (!(choiceCategory == 1 || choiceCategory == 2 || choiceCategory == 3))
	{
		cout << "Product Category?"
			 << endl
			 << "1.Food"
			 << endl
			 << "2.Medical"
			 << endl
			 << "3.Liquior"
			 << endl
			 << "Enter Category:";

		cin >> choiceCategory;

		switch (choiceCategory)
		{
		case 1:
			filename = "productFood.csv";
			break;
		case 2:
			filename = "productMedical.csv";
			break;
		case 3:
			filename = "productLiquior.csv";
			break;
		}
	}

	//.c_str() is used for older compilers. pwede naman kung variable lang kaso old compiler to eh
	ifstream filenameBRUH(filename.c_str());
	string findID = "x", findNAME = "x";
	do
	{
		// Specific item search.
		if (choice == 1)
		{

			int choice1;
			do
			{
				cout << "How would you like to search the item By ID (1) or by Name (2): ";
				cin >> choice1;

				if (choice1 == 1)
				{
					cout << "Enter Item ID: ";
					cin >> findID;
				}
				else if (choice1 == 2)
				{
					// sabi ni chatgpt lagyan ko daw nere para maalis daw yung newline itong cin.ignore
					cin.ignore();
					cout << "Enter Name: ";
					getline(cin, findNAME);
				}
				else
				{
					cout << "Invalid Choice" << endl;
				}
			} while (!(choice1 == 1 || choice1 == 2));
		}
		bool notFound = true;
		string lineData;
		if (choice == 2)
		{
			getline(filenameBRUH, lineData);
		}
		while (getline(filenameBRUH, lineData))
		{
			stringstream ss(lineData);
			string id, name, quantity, soldBy, floorQuantityNotification;

			getline(ss, id, ',');
			getline(ss, name, ',');
			getline(ss, quantity, ',');
			getline(ss, soldBy, ',');
			getline(ss, floorQuantityNotification, ',');

			if (choice == 2)
			{
				notFound = false;
				cout << endl
					 << "Item ID: " << id << endl
					 << "Name: " << name << endl
					 << "Quantity: " << quantity << endl
					 << "Sold By: " << soldBy << endl
					 << "Floor Quantity: " << floorQuantityNotification << endl
					 << "Should we restock?";
			}
			else if (id == findID || name == findNAME)
			{
				notFound = false;
				cout << endl
					 << "Item ID: " << id << endl
					 << "Name: " << name << endl
					 << "Quantity: " << quantity << endl
					 << "Sold By: " << soldBy << endl
					 << "Floor Quantity: " << floorQuantityNotification << endl
					 << "Should we restock?";
			}

			stringstream threshold;
			if (choice == 2)
			{
			}
			else if (!(id == findID || name == findNAME))
			{
				continue;
			}

			if (soldBy == "Weight" || soldBy == "weight")
			{
				// conversion of string to double for weighted items
				double quantityDouble;
				double floorDouble;

				threshold << quantity;
				threshold >> quantityDouble;

				threshold.clear(); // resets the value of the temporary holder
				threshold.str(""); // declared value for no errors

				threshold << floorQuantityNotification;
				threshold >> floorDouble;

				if (quantityDouble <= floorDouble)
				{
					cout << " Yes.";
				}
				else
				{
					cout << " No.";
				}
				threshold.clear(); // resets the value of the temporary holder
				threshold.str(""); // declared value for no errors
				if (!notFound && choice == 1)
				{
					break;
				}
			}

			// conversion of string to integers for items that is sold by pieces (stoi)
			else if (soldBy == "Pieces" || soldBy == "pieces")
			{
				int quantityInt;
				int floorInt;

				threshold << quantity;
				threshold >> quantityInt;

				threshold.clear(); // resets the value of the temporary holder
				threshold.str(""); // declared value for no errors

				threshold << floorQuantityNotification;
				threshold >> floorInt;

				if (quantityInt <= floorInt)
				{
					cout << " Yes.";
				}
				else
				{
					cout << " No.";
				}

				threshold.clear(); // resets the value of the temporary holder
				threshold.str(""); // declared value for no errors
				if (!notFound && choice == 1)
				{
					break;
				}
			}
			if (choice == 2)
			{
				cout << endl
					 << "---------------------------------------";
			}
		}
		if (notFound)
		{
			cout << "Not Found in Database.";
		}

	} while (!(choice == 1 || choice == 2));
	cout << endl
		 << endl;
	filenameBRUH.close();
}
void addProduct()
{
	// file pointer
	fstream Product;
	int choiceCategory;
	while (!(choiceCategory == 1 || choiceCategory == 2 || choiceCategory == 3))
	{
		cout << "Product Category?"
			 << endl
			 << "1.Food"
			 << endl
			 << "2.Medical"
			 << endl
			 << "3.Liquior"
			 << endl
			 << "Enter Category:";

		cin >> choiceCategory;

		switch (choiceCategory)
		{
		case 1:
			Product.open("productFood.csv", ios::out | ios::app);
			break;
		case 2:
			Product.open("productMedical.csv", ios::out | ios::app);
			break;
		case 3:
			Product.open("productLiquior.csv", ios::out | ios::app);
			break;
		}
	}

	cout << "Enter Product Characteristic."
		 << endl;

	int i, productID, floorQuantityNotification;
	string name, soldBy, dateAdded;
	double quantity;

	// Read the input
	cout << "Enter Product ID: ";
	cin >> productID;
	cout << "Enter Name: ";
	cin >> name;
	cout << "Enter Quantity: ";
	cin >> quantity;
	cout << "Sold by \"Weight\" or \"Pieces\"?: ";
	cin >> soldBy;
	cout << "Set Minimum Stock Level: ";
	cin >> floorQuantityNotification;
	cout << "Date Added: ";
	cin >> dateAdded;

	// Insert the data to file
	Product << productID << ","
			<< name << ","
			<< quantity << ","
			<< soldBy << ","
			<< floorQuantityNotification << ","
			<< dateAdded
			<< endl;

	cout << "Successfully inserted the data!"
		 << endl
		 << endl;

	Product.close();
}
void delivery()
{
	string findProductID;
	int qtyRecieved, priceQty;

	cout << "Enter Product ID: ";
	cin >> findProductID;
	cout << "Enter Quantity Received: ";
	cin >> qtyRecieved;
	cout << "Price Per Quantity: ";
	cin >> priceQty;

	int choiceCategory;
	string filename;

	while (!(choiceCategory == 1 || choiceCategory == 2 || choiceCategory == 3))
	{
		cout << "Product Category?"
			 << endl
			 << "1. Food" << endl
			 << "2. Medical" << endl
			 << "3. Liquior" << endl
			 << "Enter Category: ";

		cin >> choiceCategory;

		switch (choiceCategory)
		{
		case 1:
			filename = "productFood.csv";
			break;
		case 2:
			filename = "productMedical.csv";
			break;
		case 3:
			filename = "productLiquior.csv";
			break;
		default:
			system("cls");
			break;
		}
	}

	ifstream inFile(filename.c_str()); // Original file
	ofstream outFile("temp.csv");	   // temporary file but will be permanent file

	string line;
	bool firstLine = true;
	bool found = false;

	while (getline(inFile, line))
	{
		stringstream ss(line);
		string id, name, quantity, soldBy, floorQuantity, dateAdded, deliveryPPcs;

		getline(ss, id, ',');
		getline(ss, name, ',');
		getline(ss, quantity, ',');
		getline(ss, soldBy, ',');
		getline(ss, floorQuantity, ',');
		getline(ss, dateAdded, ',');
		getline(ss, deliveryPPcs, ',');

		// eto yung 1st line yung class ng item
		if (firstLine)
		{
			outFile << line << endl;
			firstLine = false;
			continue;
		}

		if (id == findProductID)
		{
			int currentQty;
			stringstream(quantity) >> currentQty;
			int newQty = currentQty + qtyRecieved;

			outFile << id
					<< ","
					<< name
					<< ","
					<< newQty
					<< ","
					<< soldBy
					<< ","
					<< floorQuantity
					<< ","
					<< dateAdded
					<< ","
					<< priceQty
					<< endl;
			found = true;
		}
		else
		{
			// write unchanged lines from original file
			outFile << line << endl;
		}
	}

	inFile.close();
	outFile.close();

	remove(filename.c_str());			  // Remove old file
	rename("temp.csv", filename.c_str()); // Rename temp to original

	if (found)
	{
		cout << "Quantity updated successfully." << endl;
	}
	else
	{
		cout << "Item ID not found." << endl;
	}
}

void addSalesRecord()
{
}
void showSalesReport()
{
}
int main()
{
	int systemChoice;

	do
	{
		int systemChoice = 0;
		cout
			<< "Sales & Inventory System"
			<< endl
			<< endl
			<< "1. Add Product."
			<< endl
			<< "2. Add Customer."
			<< endl
			<< "3. Add Delivery."
			<< endl
			<< "4. Add Sales."
			<< endl
			<< "5. Show Sales Report."
			<< endl
			<< "6. Show Inventory Status."
			<< endl
			<< "7. Exit."
			<< endl
			<< endl
			<< "Enter Number: ";

		cin >> systemChoice;

		switch (systemChoice)
		{
		case 1:
			addProduct();
			break;
		case 2:
			addCustomers();
			break;
		case 3:
			delivery();
			break;
		case 4:
			addSalesRecord();
			break;
		case 5:
			showSalesReport();
			break;
		case 6:
			inventoryReport();
			break;

		case 7:
			system("cls");
			cout
				<< "Thank You!"
				<< endl
				<< "BULACAN AGRICULTURAL STATE UNIVERSITY | INSTITUTE OF COMPUTER STUDIES"
				<< endl
				<< endl
				<< "Final Project for the course subject Advanced Computer Programming (IT-120)."
				<< endl
				<< "Instructor (rank ni maam): Mrs. Maylene V. Samin"
				<< endl
				<< endl
				<< "Sales & Inventory System in Real World Application"
				<< endl
				<< endl
				<< "BSIT - 1D"
				<< endl
				<< "-Agulto, Elward Ashley"
				<< endl
				<< "-Artificio, Nicolo C."
				<< endl
				<< "-Cruz, Vince"
				<< endl
				<< "-Bernabe, Lowrey Ken Kaede L. "
				<< endl
				<< "-Pablo, Francis Andrei M."
				<< endl
				<< "-Pengson, Justine Paul"
				<< endl
				<< "-Viudez, Raven";
				
			return 0;

		default:
			system("cls");
			break;
		}

	} while (!(systemChoice <= 6 && 1 <= systemChoice));
}
