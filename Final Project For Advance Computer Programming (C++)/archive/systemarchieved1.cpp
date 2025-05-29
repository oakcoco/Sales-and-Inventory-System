#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>
using namespace std;

void addCustomers()
{
	fstream customersData;

	customersData.open("customers.csv", ios::app | ios::out);

	string name, userID;

	cout << "Enter ID: ";
	getline(cin, userID);
	cout << "Enter Name: ";
	getline(cin, name);

	customersData << endl
				  << userID << "," << name;

	cout << endl
		 << "Customer Data Added Successfuly!";

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

	do
	{
		// Specific item search.
		if (choice == 1)
		{
			string findID = "x", findNAME = "x", lineData;
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

			bool notFound = true;
			while (getline(filenameBRUH, lineData))
			{
				stringstream ss(lineData);
				string id, name, quantity, soldBy, floorQuantityNotification;

				getline(ss, id, ',');
				getline(ss, name, ',');
				getline(ss, quantity, ',');
				getline(ss, soldBy, ',');
				getline(ss, floorQuantityNotification, ',');

				if (id == findID || name == findNAME)
				{
					notFound = false;
					cout << endl
						 << "Item ID: " << id << endl
						 << "Name: " << name << endl
						 << "Quantity: " << quantity << endl
						 << "Sold By: " << soldBy << endl
						 << "Floor Quantity: " << floorQuantityNotification << endl
						 << "Should we restock?";

					stringstream threshold;

					if (soldBy == "Weight" || soldBy == "weight")
					{
						// conversion of string to double for weighted items
						double quantityDouble;
						double floorDouble;

						threshold << quantity;
						threshold >> quantityDouble;

						threshold.clear(); // Reset internal flags
						threshold.str(""); // Clear the buffer

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
						threshold.clear(); // Reset internal flags
						threshold.str(""); // Clear the buffer
					}

					// conversion of string to integers for items that is sold by pieces (stoi)
					if (soldBy == "Pieces" || soldBy == "pieces")
					{
						int quantityInt;
						int floorInt;

						threshold << quantity;
						threshold >> quantityInt;

						threshold.clear(); // Reset internal flags
						threshold.str(""); // Clear the buffer

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

						threshold.clear(); // Reset internal flags
						threshold.str(""); // Clear the buffer
					}
					cout << endl
						 << "---------------------------------------";
				}
			}
			if (notFound)
			{
				cout << "Not Found in Database.";
			}
		}

		// All Inventory
		else if (choice == 2)
		{
			string lineData;

			// This line below skips the first line in the csv file
			getline(filenameBRUH, lineData);

			while (getline(filenameBRUH, lineData))
			{
				stringstream ss(lineData);
				string id, name, quantity, soldBy, floorQuantityNotification;

				getline(ss, id, ',');
				getline(ss, name, ',');
				getline(ss, quantity, ',');
				getline(ss, soldBy, ',');
				getline(ss, floorQuantityNotification, ',');

				cout << endl
					 << "Item ID: " << id << endl
					 << "Name: " << name << endl
					 << "Quantity: " << quantity << endl
					 << "Sold By: " << soldBy << endl
					 << "Floor Quantity: " << floorQuantityNotification << endl
					 << "Should we restock?";

				stringstream threshold;

				if (soldBy == "Weight" || soldBy == "weight")
				{
					// conversion of string to double for weighted items
					double quantityDouble;
					double floorDouble;

					threshold << quantity;
					threshold >> quantityDouble;

					threshold.clear(); // Reset internal flags
					threshold.str(""); // Clear the buffer

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
					threshold.clear(); // Reset internal flags
					threshold.str(""); // Clear the buffer
				}

				// conversion of string to integers for items that is sold by pieces (stoi)
				if (soldBy == "Pieces" || soldBy == "pieces")
				{
					int quantityInt;
					int floorInt;

					threshold << quantity;
					threshold >> quantityInt;

					threshold.clear(); // Reset internal flags
					threshold.str(""); // Clear the buffer

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

					threshold.clear(); // Reset internal flags
					threshold.str(""); // Clear the buffer
				}
				cout << endl
					 << "---------------------------------------";
			}
		}

	} while (!(choice == 1 || choice == 2));
	filenameBRUH.close();
}
void addProductFood()
{
	// file pointer
	fstream foodProduct;
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
			foodProduct.open("productFood.csv", ios::out | ios::app);
			break;
		case 2:
			foodProduct.open("productMedical.csv", ios::out | ios::app);
			break;
		case 3:
			foodProduct.open("productLiquior.csv", ios::out | ios::app);
			break;
		}
	}

	cout << "Enter Product Characteristic."
		 << endl;

	int i, productID, quantity, floorQuantityNotification;
	string name, soldBy, dateAdded;

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
	foodProduct << productID << ","
				<< name << ","
				<< quantity << ","
				<< soldBy << ","
				<< floorQuantityNotification << ","
				<< dateAdded
				<< "\n";

	foodProduct.close();
}

int main()
{
	cout << "Sales & Inventory System"
		 << endl
		 << endl;
	addCustomers();
}
