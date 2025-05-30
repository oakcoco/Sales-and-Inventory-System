#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int getRestockCount()
{
	int restockCount = 0;
	string lineData;
	ifstream fileProducts("Products.csv");

	getline(fileProducts, lineData);

	while (getline(fileProducts, lineData))
	{
		stringstream ss(lineData);
		string id, name, productType, productSubType, quantity, soldBy, floorQuantity, dateAdded, pricePerPcs;

		getline(ss, id, ',');
		getline(ss, name, ',');
		getline(ss, productType, ',');
		getline(ss, productSubType, ',');
		getline(ss, quantity, ',');
		getline(ss, soldBy, ',');
		getline(ss, floorQuantity, ',');
		getline(ss, dateAdded, ',');
		getline(ss, pricePerPcs, ',');

		stringstream threshold;
		double
			quantityDouble,
			floorDouble;

		threshold << quantity;
		threshold >> quantityDouble;

		threshold.clear(); // resets the value of the temporary holder
		threshold.str(""); // declared value for no errors

		threshold << floorQuantity;
		threshold >> floorDouble;

		threshold.clear(); // resets the value of the temporary holder
		threshold.str("");

		if (quantityDouble <= floorDouble)
		{
			restockCount++;
		}
	}

	fileProducts.close();
	return restockCount;
}
void addProduct()
{
	cout << endl
		 << "Enter Product Characteristic."
		 << endl;

	int prodTypeChoice,
		subTypeChoice,
		soldChoice;

	int floorQuantityNotification,
		subClass;

	double quantity = 0, pricePerPcs;

	string name,
		dateAdded,
		soldBy,
		productID,
		productType,
		productSubType;

	// Read the input

	cin.ignore();
	cout << "Enter Name: ";
	getline(cin, name);

	cout << endl
		 << "Enter Product Type:"
		 << endl
		 << "1 - Food \n"
		 << "2 - Household & Cleaning Supplies \n"
		 << "3 - Personal Care & Hygiene \n"
		 << "Enter Number of Product Type: ";
	cin >> prodTypeChoice;

	cout << endl
		 << endl
		 << "Enter Sub Class for Product: \n";
	switch (prodTypeChoice)
	{
	case 1:
		productType = "Food";
		cout
			<< "1 - Condiments \n"
			<< "2 - Dairy Product \n"
			<< "3 - Beverages \n"
			<< "4 - Meat & Seafood \n"
			<< "5 - Snacks \n"
			<< "6 - Canned Goods \n"
			<< "7 - Deli \n";
		break;

	case 2:
		productType = "Household & Cleaning Supplies";
		cout
			<< "1 - Kitchen Cleaner \n"
			<< "2 - Bathroom Cleaner \n"
			<< "3 - Glass and Metal \n"
			<< "4 - Floor & Furniture \n";
		break;

	case 3:
		productType = "Personal Care & Hygiene";
		cout
			<< "1 - Oral Care \n"
			<< "2 - Hair Care \n"
			<< "3 - Soaps \n"
			<< "4 - Feminine Hygene \n"
			<< "5 - Nail Care \n"
			<< "6 - Skin Care \n";
		break;

	default:
		cout << "Invalid. Please Try Again.";
		return;
		break;
	}
	cout << endl
		 << "Enter Number of Sub Product Type: ";
	cin >> subTypeChoice;

	switch (prodTypeChoice)
	{
	case 1:
		switch (subTypeChoice)
		{
		case 1:
			productSubType = "Condiments";
			break;
		case 2:
			productSubType = "Dairy Product";
			break;
		case 3:
			productSubType = "Beverages";
			break;
		case 4:
			productSubType = "Meat & Seafood";
			break;
		case 5:
			productSubType = "Snacks";
			break;
		case 6:
			productSubType = "Canned Goods";
			break;
		case 7:
			productSubType = "Deli";
			break;
		default:
			cout << "Invalid Sub-Class.";
			return;
		}
		break;

	case 2:
		switch (subTypeChoice)
		{
		case 1:
			productSubType = "Kitchen Cleaner";
			break;
		case 2:
			productSubType = "Bathroom Cleaner";
			break;
		case 3:
			productSubType = "Glass and Metal";
			break;
		case 4:
			productSubType = "Floor & Furniture";
			break;
		default:
			cout << "Invalid Sub-Class.";
			return;
		}
		break;

	case 3:
		switch (subTypeChoice)
		{
		case 1:
			productSubType = "Oral Care";
			break;
		case 2:
			productSubType = "Hair Care";
			break;
		case 3:
			productSubType = "Soaps";
			break;
		case 4:
			productSubType = "Feminine Hygiene";
			break;
		case 5:
			productSubType = "Nail Care";
			break;
		case 6:
			productSubType = "Skin Care";
			break;
		default:
			cout << "Invalid Sub-Class.";
			return;
		}
		break;

	default:
		cout << "Invalid Product Type.";
		return;
	}

	cout << endl
		 << "Sold By: \n"
		 << "1 - Weight (kg) \n"
		 << "2 - Pieces \n"
		 << "Enter number of the item how it is Sold: ";
	cin >> soldChoice;
	switch (soldChoice)
	{
	case 1:
		soldBy = "Weight";
		break;

	case 2:
		soldBy = "Pieces";
		break;

	default:
		cout << "Invalid. Please Try Again.";
		return;
		break;
	}

	cout << endl
		 << endl
		 << "Set Minimum Stock Level: ";
	cin >> floorQuantityNotification;
	cout << endl
		 << endl
		 << "Date Added: ";
	cin >> dateAdded;
	cout << endl
		 << endl
		 << "Price Per Quantity / Kilograms (If measured by Weight): ";
	cin >> pricePerPcs;

	// automatic ID assign
	ifstream Product("Products.csv");

	int lastFoodID = 1000;
	int lastHouseholdID = 2000;
	int lastPersonalID = 3000;

	string line;
	while (getline(Product, line))
	{
		stringstream ss(line);
		string idStr;
		getline(ss, idStr, ',');

		int id = 0;
		stringstream convert(idStr);
		convert >> id;

		if (id >= 1000 && id < 2000)
			lastFoodID = max(lastFoodID, id);
		else if (id >= 2000 && id < 3000)
			lastHouseholdID = max(lastHouseholdID, id);
		else if (id >= 3000 && id < 4000)
			lastPersonalID = max(lastPersonalID, id);

		stringstream idStream;

		if (prodTypeChoice == 1)
			idStream << (lastFoodID + 1);
		else if (prodTypeChoice == 2)
			idStream << (lastHouseholdID + 1);
		else if (prodTypeChoice == 3)
			idStream << (lastPersonalID + 1);
		else
		{
			cout << "Invalid product type.";
			return;
		}

		productID = idStream.str();
	}
	Product.close();

	// Insert the data to file
	ofstream ProductInsert("Products.csv", ios::app);

	ProductInsert << productID << ","
				  << name << ","
				  << productType << ","
				  << productSubType << ","
				  << quantity << ","
				  << soldBy << ","
				  << floorQuantityNotification << ","
				  << dateAdded << ","
				  << pricePerPcs
				  << endl;

	cout << endl
		 << "===================================="
		 << endl
		 << "| Successfully inserted the data! |"
		 << endl
		 << "===================================="
		 << endl
		 << endl;
	ProductInsert.close();

	cout << "This is the data you've inserted: \n"
		 << "Product ID: " << productID << endl
		 << "Product Name: " << name << endl
		 << "Product Type: " << productType << endl
		 << "Sub Type: " << productSubType << endl
		 << "Sold By: " << soldBy << endl
		 << "Floor Quantity: " << floorQuantityNotification << endl
		 << "Date Added: " << dateAdded << endl
		 << "Price Per Quantity/Kilograms: " << pricePerPcs
		 << endl
		 << endl;
}
void addCustomers()
{

	string name, userID;

	cout << endl
		 << "Add Customer Data."
		 << endl
		 << "Enter Name: ";
	cin.ignore();
	getline(cin, name);

	ifstream Customers("customers.csv");

	int lastNameID = 1000;
	string line;
	while (getline(Customers, line))
	{
		stringstream ss(line);
		string idStr;
		getline(ss, idStr, ',');

		int id = 0;
		stringstream convert(idStr);
		convert >> id;

		if (id >= 1000 && id < 2000)
			lastNameID = max(lastNameID, id);

		stringstream idStream;

		idStream << (lastNameID + 1);

		userID = idStream.str();
	}
	Customers.close();

	fstream customersData;
	customersData.open("customers.csv", ios::out | ios::app);
	customersData << endl
				  << userID << "," << name;

	cout << endl
		 << "===================================="
		 << endl
		 << "| Customer Data Added Successfuly! |"
		 << endl
		 << "===================================="
		 << endl
		 << endl;
	customersData.close();

	cout << "This is the Customer Data you've inputed: " << endl
		 << "Name: " << name << endl
		 << "ID: " << userID
		 << endl
		 << endl;
}
void delivery()
{
	string findProductID, productName;

	double
		totalPriceDelivered,
		newQty,
		qtyRecieved,
		totalPrice,
		pricePerPcsConverted,
		pricePerPcsDbl;

	cout << "Enter Product ID: ";
	cin >> findProductID;
	cout << "Enter Quantity Received: ";
	cin >> qtyRecieved;

	string filename;

	ifstream inFile("Products.csv"); // Original file
	ofstream outFile("temp.csv");	 // temporary file but will be permanent file

	string line;
	bool found = false;

	while (getline(inFile, line))
	{
		stringstream ss(line);
		string id, name, productType, productSubType, quantity, soldBy, floorQuantity, dateAdded, pricePerPcs;

		getline(ss, id, ',');
		getline(ss, name, ',');
		getline(ss, productType, ',');
		getline(ss, productSubType, ',');
		getline(ss, quantity, ',');
		getline(ss, soldBy, ',');
		getline(ss, floorQuantity, ',');
		getline(ss, dateAdded, ',');
		getline(ss, pricePerPcs, ',');

		if (id == findProductID)
		{
			// converter of string to double.
			double currentQty;
			stringstream(quantity) >> currentQty;
			newQty = currentQty + qtyRecieved;
			stringstream(pricePerPcs) >> pricePerPcsDbl;
			totalPriceDelivered = pricePerPcsDbl * qtyRecieved;
			productName = name;

			outFile << id << "," << name << "," << productType << "," << productSubType << "," << newQty << ","
					<< soldBy << "," << floorQuantity << "," << dateAdded << "," << pricePerPcs << endl;

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

	remove("Products.csv");				// Remove old file
	rename("temp.csv", "Products.csv"); // Rename temp to original

	if (found)
	{
		cout << endl
			 << "======================================="
			 << endl
			 << "| Product Quantity Added Successfuly! |"
			 << endl
			 << "======================================="
			 << endl
			 << endl
			 << "Product ID: " << findProductID << endl
			 << "Product Name: " << productName << endl
			 << "Quantity Recieved: " << qtyRecieved << endl
			 << "New Quantity: " << newQty << endl
			 << "Price Per Quantity/kg: " << pricePerPcsDbl << endl
			 << "Total Spent: " << totalPriceDelivered << endl
			 << endl;

		fstream DeliveryExpenses("DeliveryExpenses.csv", ios::out | ios::app);
		DeliveryExpenses << totalPriceDelivered << ",";

		DeliveryExpenses.close();
	}
	else
	{
		cout << "Item ID not found." << endl;
	}
	cout << "---------------------------------------"
		 << endl;
}
void addSalesRecord()
{
	//(CHECKLIST)CUSTOMERNAME,PRODUCTNAME
	string
		customerID,
		customerName,
		productID,
		productName,
		productTypeX,
		productSubTypeX,
		date;
	// priceperquantity

	double
		quantityBought,
		productPriceMain,
		amountRecieved,
		change;

	string line;

	bool customerNameTrue = true;
	ifstream customersData("customers.csv");
	
	cin.ignore();
	cout << "Enter Customer Name or Customer Name ID: ";
	getline(cin, customerName);

	getline(customersData, line);
	while (getline(customersData, line))
	{
		string currentID, currentName;
		stringstream customerFinder(line);

		getline(customerFinder, currentID, ',');
		getline(customerFinder, currentName, ',');

		if (customerName == currentName || customerName == currentID)
		{
			customerNameTrue = false;
			customerName = currentName;
			customerID = currentID;
			cout << endl;
			break;
		}
	}
	if (customerNameTrue)
	{
		cout << "Not Found In Database. Please Try Again." << endl;
		customersData.close();
		return;
	}
	customersData.close();

	ifstream filenameBRUH("Products.csv");

	cin.ignore();
	cout << "Enter Product Name or Product ID: ";
	getline(cin, productName);

	customerNameTrue = true;
	// hey your bool is reseted to true!!!^^^^^

	while (getline(filenameBRUH, line))
	{
		stringstream ss(line);
		string id, name, productType, productSubtype, quantity, soldBy, floorQuantity, dateAdded, productPrice;

		getline(ss, id, ',');
		getline(ss, name, ',');
		getline(ss, productType, ',');
		getline(ss, productSubtype, ',');
		getline(ss, quantity, ',');
		getline(ss, soldBy, ',');
		getline(ss, floorQuantity, ',');
		getline(ss, dateAdded, ',');
		getline(ss, productPrice, ',');

		if (productName == id || productName == name)
		{
			productName = name;
			productID = id;
			productSubTypeX = productSubtype;
			productTypeX = productType;

			stringstream temp(productPrice);
			temp >> productPriceMain;

			customerNameTrue = false;
			break;
		}
	}
	if (customerNameTrue)
	{
		cout << "Not Found In Database. Please Try Again." << endl;
		customersData.close();
		return;
	}

	double priceMarkUP = productPriceMain + (productPriceMain * 0.20);

	cout << endl
		 << "Price per Quantity/Kg: " << priceMarkUP
		 << endl
		 << "Quantity Bought: ";
	cin >> quantityBought;
	// process total
	double total;
	total = quantityBought * priceMarkUP;

	cout << endl
		 << "Enter Date Today: ";
	cin >> date;

	cout << "Amount Recieved: ";
	cin >> amountRecieved;

	change = amountRecieved - total;
	filenameBRUH.close();

	// relocation. update value of quantity because you sold an item
	ifstream inFile("Products.csv"); // Original file
	ofstream outFile("temp.csv");	 // temporary file but will be permanent file

	while (getline(inFile, line))
	{
		stringstream ss(line);
		string id, name, productType, productSubtype, quantity, soldBy, floorQuantity, dateAdded, productPrice;

		getline(ss, id, ',');
		getline(ss, name, ',');
		getline(ss, productType, ',');
		getline(ss, productSubtype, ',');
		getline(ss, quantity, ',');
		getline(ss, soldBy, ',');
		getline(ss, floorQuantity, ',');
		getline(ss, dateAdded, ',');
		getline(ss, productPrice, ',');

		if (productName == id || productName == name)
		{
			double currentQty;
			stringstream(quantity) >> currentQty;
			int newQty = currentQty - quantityBought;

			outFile << id << "," << name << "," << productTypeX << "," << productSubTypeX << "," << newQty << ","
					<< soldBy << "," << floorQuantity << "," << dateAdded << "," << productPrice << endl;
		}
		else
		{
			// write unchanged lines from original file
			outFile << line << endl;
		}
	}

	inFile.close();
	outFile.close();
	remove("Products.csv"); // Remove old file
	rename("temp.csv", "Products.csv");

	// revenue total values
	ofstream anotherFile("Revenue.csv", ios::app);
	anotherFile << total << ",";
	anotherFile.close();

	// insert of records
	ofstream file("records.txt", ios::app);
	file << endl
		 << "=============================="
		 << endl
		 << "Customer ID: " << customerID << endl
		 << "Name: " << customerName << endl
		 << "-----------------------" << endl
		 << "Product ID: " << productID << endl
		 << "Product Name: " << productName << endl
		 << "Product Type: " << productTypeX << endl
		 << "Product Sub Type: " << productSubTypeX << endl
		 << "-----------------------" << endl
		 << "Price Per Quantity: " << priceMarkUP << endl
		 << "Quantity/kg Bought: " << quantityBought << endl
		 << "-----------------------" << endl
		 << "Total Price: " << total << endl
		 << "Amount Recieved: " << amountRecieved << endl
		 << "Change: " << change << endl
		 << "-----------------------" << endl
		 << "Date: " << date << endl
		 << "==============================";
	file.close();

	cout << endl
		 << "========================================="
		 << endl
		 << "| Reciept Added Successfuly In Records! |"
		 << endl
		 << "========================================="
		 << endl
		 << endl
		 << "============Reciept==========="
		 << endl
		 << "Customer ID: " << customerID << endl
		 << "Name: " << customerName << endl
		 << "-----------------------" << endl
		 << "Product ID: " << productID << endl
		 << "Product Name: " << productName << endl
		 << "Product Type: " << productTypeX << endl
		 << "Product Sub Type: " << productSubTypeX << endl
		 << "-----------------------" << endl
		 << "Price Per Quantity: " << priceMarkUP << endl
		 << "Quantity/kg Bought: " << quantityBought << endl
		 << "-----------------------" << endl
		 << "Total Price: " << total << endl
		 << "Amount Recieved: " << amountRecieved << endl
		 << "Change: " << change << endl
		 << "-----------------------" << endl
		 << "Date: " << date << endl
		 << "=============================="
		 << endl
		 << endl;
}
void showSalesReport()
{
	// show all records
	ifstream file("records.txt");
	if (!file)
	{
		cerr << "Failed to open file." << endl;
		return;
	}

	string line;
	while (getline(file, line))
	{
		cout << line << endl;
	}
	file.close();

	// total profit
	double totalRevenue;
	ifstream revenueFile("Revenue.csv");
	{
		string line;

		while (getline(revenueFile, line))
		{
			stringstream ss(line);
			string value;

			while (getline(ss, value, ','))
			{
				double num;
				stringstream(value) >> num;
				// adds total from previous.
				// It adds the right-hand operand to the left-hand operand and assigns the result to the left-hand operand.
				// same with (total = total + num)
				totalRevenue += num;
			}
		}
	}
	revenueFile.close();
	// DeliveryExpenses
	double totalDelivery;
	ifstream deliveryFile("DeliveryExpenses.csv");
	{
		string line;

		while (getline(deliveryFile, line))
		{
			stringstream ss(line);
			string value;

			while (getline(ss, value, ','))
			{
				double num;
				stringstream(value) >> num;
				// adds total from previous.
				// It adds the right-hand operand to the left-hand operand and assigns the result to the left-hand operand.
				// same with (total = total + num)
				totalDelivery += num;
			}
		}
	}
	deliveryFile.close();

	cout << endl
		 << "======================" << endl
		 << "| Total Revenue: " << totalRevenue << " |" << endl
		 << "======================" << endl
		 << endl
		 << "======================" << endl
		 << "| Total Expenses: " << totalDelivery << " |" << endl
		 << "======================" << endl
		 << endl
		 << "======================" << endl
		 << "| Total Gross: " << totalRevenue - totalDelivery << " |" << endl
		 << "======================" << endl
		 << endl;
}
void inventoryReport()
{
	// choices between a single item, all items and the category.
	int choice, choiceCategory, x;

	int floorQty[100], quantityRestock[100];
	string itemsNeedRestockID[100], itemsNeedRestockName[100];
	string filename;

	cout << "How would you like to report the inventory? Single Item (1) or All Items (2): ";
	cin >> choice;
	cout << endl;

	//.c_str() is used for older compilers. pwede naman kung variable lang kaso old compiler to eh
	ifstream fileProducts("Products.csv");
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
		// nag skiskip ng line sa csv file.
		if (choice == 2)
		{
			getline(fileProducts, lineData);
		}
		while (getline(fileProducts, lineData))
		{
			stringstream ss(lineData);
			string id, name, productType, productSubType, quantity, soldBy, floorQuantity, dateAdded, pricePerPcs;

			getline(ss, id, ',');
			getline(ss, name, ',');
			getline(ss, productType, ',');
			getline(ss, productSubType, ',');
			getline(ss, quantity, ',');
			getline(ss, soldBy, ',');
			getline(ss, floorQuantity, ',');
			getline(ss, dateAdded, ',');
			getline(ss, pricePerPcs, ',');

			if (choice == 2)
			{
				notFound = false;
				cout << endl
					 << "Item ID: " << id << endl
					 << "Name: " << name << endl
					 << "Product Type: " << productType << endl
					 << "Product Sub Type: " << productSubType << endl
					 << "Quantity/kg: " << quantity << endl
					 << "Sold By: " << soldBy << endl
					 << "Floor Quantity: " << floorQuantity << endl
					 << "Date Added: " << dateAdded << endl
					 << "Should we restock?";
			}
			else if (id == findID || name == findNAME)
			{
				notFound = false;
				cout << endl
					 << "Item ID: " << id << endl
					 << "Name: " << name << endl
					 << "Product Type: " << productType << endl
					 << "Product Sub Type: " << productSubType << endl
					 << "Quantity/kg: " << quantity << endl
					 << "Sold By: " << soldBy << endl
					 << "Floor Quantity: " << floorQuantity << endl
					 << "Date Added: " << dateAdded << endl
					 << "Should we restock?";
			}

			// filter for all items and single items (magkasama po ito)
			if (choice == 2)
			{
			}
			else if (!(id == findID || name == findNAME))
			{
				// itong continue na to affected yung while loop ng getter ng file
				continue;
			}

			// validation for entering weight and pieces
			stringstream threshold;
			if (soldBy == "Weight" || soldBy == "weight")
			{
				// conversion of string to double for weighted items
				double quantityDouble;
				double floorDouble;

				threshold << quantity;
				threshold >> quantityDouble;

				threshold.clear(); // resets the value of the temporary holder
				threshold.str(""); // declared value for no errors

				threshold << floorQuantity;
				threshold >> floorDouble;

				if (quantityDouble <= floorDouble)
				{
					cout << " Yes.";
					itemsNeedRestockID[x] = id;
					itemsNeedRestockName[x] = name;
					floorQty[x] = floorDouble;
					quantityRestock[x] = quantityDouble;
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

				threshold << floorQuantity;
				threshold >> floorInt;

				if (quantityInt <= floorInt)
				{
					cout << " Yes.";
					itemsNeedRestockID[x] = id;
					itemsNeedRestockName[x] = name;
					floorQty[x] = floorInt;
					quantityRestock[x] = quantityInt;
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
			else
			{
				cout << " Invalid Input of weight/pieces.";
			}

			if (choice == 2)
			{
				cout << endl
					 << "---------------------------------------";
			}
			// this x++ is for itemrestock string counter
			x++;
		}
		cout << endl
			 << endl
			 << "These are the items needed restock:";

		int y = 0;
		for (x = 0; x < 100; x++)
		{
			// this variable y is for counter

			if (itemsNeedRestockName[x].empty())
			{
				continue;
			}
			y++;
			cout << endl
				 << y << ". "
				 << endl
				 << "Item ID: " << itemsNeedRestockID[x]
				 << endl
				 << "Item Name: " << itemsNeedRestockName[x]
				 << endl
				 << "Floor Quantity: " << floorQty[x]
				 << endl
				 << "Current Stock: " << quantityRestock[x]
				 << endl
				 << "-----------------------"
				 << endl;
		}
		if (notFound)
		{
			cout << "Not Found in Database.";
		}

	} while (!(choice == 1 || choice == 2));
	cout << endl
		 << endl;
	fileProducts.close();
}
int main()
{
	int systemChoice;
	do
	{
		systemChoice = 0;
		cout
			<< "Sales & Inventory System"
			<< endl;

		int restockCount = getRestockCount();
		if (restockCount > 0)
		{
			cout << endl
				 << "[x] Notifications: " << restockCount << " item(s) need restocking. Please check your inventory." << endl;
		}
		else
		{
			cout << endl
				 << "[x] Notifications: None" << endl;
		}
		cout << endl
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

	} while (!(systemChoice >= 6 && 1 >= systemChoice));
}
