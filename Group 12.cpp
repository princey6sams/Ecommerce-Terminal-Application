
//	ONLINE E-COMMERCE PLATFORM
//	Made by:\
			Alan Kochukalam George (202005773)\
			Prince Authoy Singha (202030797)\
			Jubaira Abedin Ayeshe (202025409)

//All header files used in this project
#include <fstream>
#include <iostream>
#include <string>
#include <json/json.h>
#include <json/writer.h>
#include <Windows.h>
#include <conio.h>

namespace DS
{
	//Queue Data Structure
	template <typename T>
	class Queue
	{
		struct QNode
		{
			T data;
			QNode* next;
			QNode(T);
			~QNode();
		};
		int capacity;
		QNode* front, * rear;

		void printRecursive(QNode* n, int i);
		void deQueue();
	public:
		Queue();
		void enQueue(T);
		~Queue();
		void print();
	};

	//Linked List Data Structure
	template<typename T>
	class linkedList
	{
		typedef struct node
		{
			T data;
			node* next;
			node(T);
			~node();
		}*nodePtr;
		nodePtr head, tail;
		void selectionSort(nodePtr head);
	public:
		linkedList();
		~linkedList();
		void addNode(T);
		void Delete(unsigned int);
		void print();
		bool isEmpty() const;
		void popTop(T&);
		void sort();
	};

	//Array Data Structure
	template <typename T, size_t N>
	class Array
	{
		T* arr;
		int count;
	public:
		Array();
		void insert(T data);
		~Array();
		T& operator[](int index);
	};

	//Binary Search Tree Data Structure
	template <typename T>
	class BST
	{
		typedef struct node {
			T data;
			node* left;
			node* right;
			node(T x)
				:data(x), left(NULL), right(NULL) {}
			~node()
			{
				left = NULL;
				right = NULL;
				delete left, right;
			}
			void print()
			{
				std::cout << data;
			}
		}*nodePtr;
		nodePtr root;

		nodePtr insert(T x, node* t)
		{
			if (!t)
				t = new node(x);
			else if (x < t->data)
				t->left = insert(x, t->left);
			else if (x > t->data)
				t->right = insert(x, t->right);
			return t;
		}

		void inorder(nodePtr t)
		{
			if (!t)
				return;
			inorder(t->left);
			std::cout << t->data << std::endl;
			inorder(t->right);
		}

		nodePtr find(nodePtr t, T x)
		{
			if (!t)
				return NULL;
			else if (x < t->data)
				return find(t->left, x);
			else if (x > t->data)
				return find(t->right, x);
			else
				return t;
		}

	public:
		BST()
		{
			root = NULL;
		}

		~BST()
		{
			root = NULL;
			delete root;
		}

		void insert(T x)
		{
			root = insert(x, root);
		}

		void display()
		{
			inorder(root);
		}

		void search(T x)
		{
			root = find(root, x);
			if (root)
				std::cout << root->data;
		}
	};
}

//Queue implementation
template <typename T>
DS::Queue<T>::QNode::QNode(T d)
{
	data = d;
	next = NULL;
}

template <typename T>
DS::Queue<T>::QNode::~QNode()
{
	next = NULL;
	delete next;
}

template <typename T>
void DS::Queue<T>::printRecursive(QNode* n, int index)
{
	if (n)
	{
		printRecursive(n->next, index + 1);
		std::cout << index << '.' << std::endl;
		std::cout << n->data << std::endl;
	}
}

template <typename T>
void DS::Queue<T>::deQueue()
{
	if (front == NULL)
		return;

	QNode* temp = front;
	front = front->next;

	if (front == NULL)
		rear = NULL;

	delete (temp);
}

template <typename T>
DS::Queue<T>::Queue()
{
	front = rear = NULL;
	capacity = 0;
}

template <typename T>
void DS::Queue<T>::enQueue(T x)
{
	if (capacity == 8)
	{
		deQueue();
		capacity--;
	}
	if (capacity < 8)
	{
		capacity++;
	}

	QNode* temp = new QNode(x);
	if (rear == NULL) {
		front = rear = temp;
		return;
	}
	rear->next = temp;
	rear = temp;
}

template <typename T>
DS::Queue<T>::~Queue()
{
	front = rear = NULL;
	delete front, rear;
}

template <typename T>
void DS::Queue<T>::print()
{
	int i = 1;
	printRecursive(front, i);
}

//linkedList implementation
template <typename T>
DS::linkedList<T>::node::node(T data)
{
	this->data = data;
	next = NULL;
}

template <typename T>
DS::linkedList<T>::node::~node()
{
	next = NULL;
	delete next;
}

template <typename T>
void DS::linkedList<T>::selectionSort(nodePtr head)
{
	nodePtr temp = head;
	while (temp)
	{
		nodePtr min = temp;
		nodePtr r = temp->next;

		while (r) {
			if (min->data.returnPrice() > r->data.returnPrice())
				min = r;

			r = r->next;
		}

		T x = temp->data;
		temp->data = min->data;
		min->data = x;
		temp = temp->next;
	}
}

template <typename T>
DS::linkedList<T>::linkedList()
	:head(NULL), tail(NULL) {}

template <typename T>
DS::linkedList<T>::~linkedList()
{
	head = NULL;
	tail = NULL;
	delete head, tail;
}

template <typename T>
void DS::linkedList<T>::addNode(T newData)
{
	nodePtr newNode = new node(newData);
	if (head)
		tail->next = newNode;
	else
		head = newNode;
	tail = newNode;
	return;
}

template <typename T>
void DS::linkedList<T>::print()
{
	nodePtr current = head;
	while (current)
	{
		std::cout << current->data << std::endl;
		current = current->next;
	}
}

template <typename T>
void DS::linkedList<T>::Delete(unsigned int num)
{
	nodePtr current = head, temp = head, del = NULL;
	while (current && current->data != num)
	{
		temp = current;
		current = current->next;
	}
	if (!current)
		std::cout << "\nCompany with id " << num << " was not in the Database";
	else
	{
		del = current;
		current = current->next;
		temp->next = current;
		if (del == head)
		{
			head = head->next;
			temp = NULL;
		}
		if (del == tail)
			tail = temp;
		std::cout << "\nCompany with id " << num << " was deleted";
	}
	delete del;
	return;
}

template <typename T>
void DS::linkedList<T>::popTop(T& a)
{
	nodePtr temp;
	a = head->data;
	temp = head;
	head = head->next;
	temp->next = NULL;
	delete temp;
}

template <typename T>
bool DS::linkedList<T>::isEmpty() const
{
	return head == NULL;
}

template <typename T>
void DS::linkedList<T>::sort()
{
	selectionSort(head);
}

//Array immplementation
template <typename T, size_t N>
DS::Array<T, N>::Array()
	:count(0), arr(new T[N]) {}

template <typename T, size_t N>
void DS::Array<T, N>::insert(T data)
{
	arr[count] = data;
	count++;
	return;
}

template <typename T, size_t N>
T& DS::Array<T, N>::operator[] (int index)
{
	if (index >= N)
	{
		std::cout << "Array index out of bound";
		return arr[N];
	}
	return arr[index];
}

template <typename T, size_t N>
DS::Array<T, N>::~Array()
{
	delete[] arr;
}

void gotoxy(int x, int y)
{
	COORD c = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//Actual stuff
class Product
{
	unsigned int cid, pid;
	std::string cname, pname;
	float price, discount;
public:
	Product();
	Product(unsigned int, unsigned int, std::string, std::string, float, float);
	Product(unsigned int);
	unsigned int returnCid();
	unsigned int returnPid();
	std::string returnCname();
	std::string returnPname();
	float returnPrice();
	float returnDiscount();
	friend std::ostream& operator<<(std::ostream&, const Product&);
	bool operator!=(int x);
	bool operator<(const Product&);
	bool operator>(const Product&);
};

Product::Product()
{
	pname = "";
	cname = "";
	cid = 0;
	pid = 0;
	price = 0;
	discount = 0;
}

Product::Product(unsigned int cid, unsigned int pid, std::string cname, std::string pname, float price, float discount)
	:cid(cid), pid(pid), cname(cname), pname(pname), price(price), discount(discount) {}

Product::Product(unsigned int cid)
	:cid(cid), pid(0), cname(""), pname(""), price(0), discount(0) {}

unsigned int Product::returnCid()
{
	return cid;
}

unsigned int Product::returnPid()
{
	return pid;
}

std::string Product::returnCname()
{
	return cname;
}

std::string Product::returnPname()
{
	return pname;
}

float Product::returnPrice()
{
	return price;
}

float Product::returnDiscount()
{
	return discount;
}

std::ostream& operator<<(std::ostream& out, const Product& pr)
{
	out << "\nCompany ID: " << pr.cid;
	out << "\nCompany: " << pr.cname;
	out << "\nProduct ID: " << pr.pid;
	out << "\nProduct: " << pr.pname;
	out << "\nPrice: " << pr.price;
	out << "\nDiscount: " << pr.discount << '%';
	return out;
}

bool Product::operator!=(int x)
{
	return cid != x;
}

bool Product::operator<(const Product& x)
{
	return cid < x.cid;
}

bool Product::operator>(const Product& x)
{
	return cid > x.cid;
}

void parserLinkedList(const Json::Value& param, DS::linkedList<Product>& y)
{
	unsigned int cid, pid;
	std::string cname, pname;
	float price, discount;
	for (size_t i = 0; i < param.size(); i++)
	{
		cid = param[std::to_string(i)]["CompanyID"].asUInt();
		cname = param[std::to_string(i)]["Company"].asString();
		pid = param[std::to_string(i)]["ProductID"].asUInt();
		pname = param[std::to_string(i)]["Product"].asString();
		price = param[std::to_string(i)]["Price"].asFloat();
		discount = param[std::to_string(i)]["Discount"].asFloat();
		y.addNode(Product(cid, pid, cname, pname, price, discount));
	}
}

void senderLinkedList(Json::Value& param, DS::linkedList<Product>& pr)
{
	Product a;
	unsigned int index = 0;
	while (!pr.isEmpty())
	{
		pr.popTop(a);
		param[std::to_string(index)]["Company"] = a.returnCname();
		param[std::to_string(index)]["CompanyID"] = index;
		param[std::to_string(index)]["Product"] = a.returnPname();
		param[std::to_string(index)]["ProductID"] = a.returnPid();
		param[std::to_string(index)]["Price"] = a.returnPrice();
		param[std::to_string(index)]["Discount"] = a.returnDiscount();
		index++;
	}
}

void parserBST(const Json::Value& param, DS::BST<Product>& y)
{
	unsigned int cid, pid;
	std::string cname, pname;
	float price, discount;
	for (size_t i = 0; i < param.size(); i++)
	{
		cid = param[std::to_string(i)]["CompanyID"].asUInt();
		cname = param[std::to_string(i)]["Company"].asString();
		pid = param[std::to_string(i)]["ProductID"].asUInt();
		pname = param[std::to_string(i)]["Product"].asString();
		price = param[std::to_string(i)]["Price"].asFloat();
		discount = param[std::to_string(i)]["Discount"].asFloat();
		y.insert(Product(cid, pid, cname, pname, price, discount));
	}
}

void create()
{
	system("cls");
	unsigned int pid;
	std::string cname, pname;
	float price, discount;
	std::ofstream testFile;
	Json::Value actualJson;
	unsigned int index = 0;
	char ch = 'Y';
	while (ch == 'Y' || ch == 'y')
	{
		std::cout << "\nEnter Company name: "; std::getline(std::cin >> std::ws, cname);
		std::cout << "Enter Product name: "; std::getline(std::cin >> std::ws, pname);
		std::cout << "Enter Product ID: "; std::cin >> pid;
		std::cout << "Enter price: "; std::cin >> price;
		std::cout << "Enter discount: "; std::cin >> discount;
		actualJson[std::to_string(index)]["Company"] = cname;
		actualJson[std::to_string(index)]["CompanyID"] = index;
		actualJson[std::to_string(index)]["Product"] = pname;
		actualJson[std::to_string(index)]["ProductID"] = pid;
		actualJson[std::to_string(index)]["Price"] = price;
		actualJson[std::to_string(index)]["Discount"] = discount;
		index++;
		std::cout << "Want to add more items?"; std::cin >> ch;
		std::cout << std::endl;
	}
	testFile.open("test.json", std::ios_base::binary);
	if (!testFile)
	{
		std::cout << "Could not Open the file";
		exit(-1);
	}
	testFile << actualJson.toStyledString() << std::endl;
	testFile.close();
}

void add()
{
	system("cls");
	std::fstream testFile("test.json", std::ios_base::binary | std::ios_base::in);
	if (!testFile)
	{
		std::cout << "could not open the file";
		exit(-1);
	}
	Json::Value actualJson;
	testFile >> actualJson;
	testFile.close();
	unsigned int index = actualJson.size();
	unsigned int pid;
	std::string cname, pname;
	float price, discount;
	char ch = 'Y';
	while (ch == 'Y' || ch == 'y')
	{

		std::cout << "\nEnter Company name: "; std::getline(std::cin >> std::ws, cname);
		std::cout << "Enter Product name: "; std::getline(std::cin >> std::ws, pname);
		std::cout << "Enter Product ID: "; std::cin >> pid;
		std::cout << "Enter price: "; std::cin >> price;
		std::cout << "Enter discount: "; std::cin >> discount;
		actualJson[std::to_string(index)]["Company"] = cname;
		actualJson[std::to_string(index)]["CompanyID"] = index;
		actualJson[std::to_string(index)]["Product"] = pname;
		actualJson[std::to_string(index)]["ProductID"] = pid;
		actualJson[std::to_string(index)]["Price"] = price;
		actualJson[std::to_string(index)]["Discount"] = discount;
		index++;
		std::cout << "Want to add more items?"; std::cin >> ch;
		std::cout << std::endl;
	}
	testFile.open("test.json", std::ios_base::binary | std::ios_base::out);
	if (!testFile)
	{
		std::cout << "Could not Open the file";
		exit(-1);
	}
	testFile << actualJson.toStyledString() << std::endl;
	testFile.close();
}

void display()
{
	system("cls");
	std::ifstream testFile("test.json", std::ios_base::binary);
	if (!testFile)
	{
		std::cout << "Could not Open the file";
		exit(-1);
	}
	Json::Value actualJson;
	testFile >> actualJson;
	for (unsigned int i = 0; i < actualJson.size(); i++)
	{
		std::cout << "Company: " << actualJson[std::to_string(i)]["Company"].asString() << std::endl;
		std::cout << "CompanyID: " << actualJson[std::to_string(i)]["CompanyID"] << std::endl;
		std::cout << "Product: " << actualJson[std::to_string(i)]["Product"].asString() << std::endl;
		std::cout << "ProductID: " << actualJson[std::to_string(i)]["ProductID"] << std::endl;
		std::cout << "Price: " << actualJson[std::to_string(i)]["Price"] << std::endl;
		std::cout << "Discount: " << actualJson[std::to_string(i)]["Discount"] << '%' << std::endl;
		std::cout << "\n##########################################################\n\n";
	}
	testFile.close();
}

struct customer
{
	std::string name, address;
}cus;

void cuin()
{
	std::string name, address;
	std::cout << "\nEnter Name: "; std::getline(std::cin >> std::ws, cus.name);
	std::cout << "Enter Address: "; std::getline(std::cin >> std::ws, cus.address);
}

void cuout()
{
	std::cout << "\nName: " << cus.name;
	std::cout << "\nDelivery address: " << cus.address;
}

//product menu
void menu()
{
	system("cls");
	std::cout << "\n\n\t**********************************************************";
	std::cout << "\n\n\t		          PRODUCT MENU";
	std::cout << "\n\n\t**********************************************************";
	std::ifstream f("Test.json", std::ios_base::binary);
	if (!f)
	{
		std::cout << "\nError";
		exit(0);
	}
	gotoxy(9, 8);
	std::cout << "C.No";
	gotoxy(15, 8);
	std::cout << "Company";
	gotoxy(29, 8);
	std::cout << "P.No";
	gotoxy(34, 8);
	std::cout << "Product";
	gotoxy(53, 8);
	std::cout << "Price(in CA$)";
	std::cout << "\n\t-------------------------------------------------------------";
	int i = 10;
	Json::Value actualJson;
	f >> actualJson;
	for (unsigned int x = 0; x < actualJson.size(); x++)
	{
		gotoxy(9, i);
		std::cout << actualJson[std::to_string(x)]["CompanyID"].asUInt();
		gotoxy(15, i);
		std::cout << actualJson[std::to_string(x)]["Company"].asString();
		gotoxy(29, i);
		std::cout << actualJson[std::to_string(x)]["ProductID"].asUInt();
		gotoxy(34, i);
		std::cout << actualJson[std::to_string(x)]["Product"].asString();
		gotoxy(53, i);
		std::cout << actualJson[std::to_string(x)]["Price"].asFloat();
		i++;
	}
	f.close();
}

DS::Queue<std::string> customers;

void customerMenu()
{
	DS::Array<int, 50> numberOfProducts, quantity;
	unsigned int index = 0, n, q;
	float finalAmount = 0, total = 0, initialAmount = 0;
	cuin();
	char ch;
	do
	{
		system("cls");
		menu();
		std::cout << "\n PLACE YOUR ORDER";
		std::cout << "\nEnter the product number of the product : "; std::cin >> n;
		std::cout << "\nQuantity in number: "; std::cin >> q;
		numberOfProducts.insert(n);
		quantity.insert(q);
		index++;
		std::cout << "\nDo You Want To Order Another Product (Y/N)? ";
		std::cin >> ch;

	} while (ch == 'y' || ch == 'Y');
	std::cout << "\n\nThank You For Placing The Order";
	(void)_getch();
	system("cls");
	gotoxy(1, 1);
	std::cout << "\n\n********************************INVOICE***************************************************\n";
	gotoxy(1, 4);
	std::cout << "Product";
	gotoxy(21, 4);
	std::cout << "Quantity";
	gotoxy(30, 4);
	std::cout << "Unit Price";
	gotoxy(41, 4);
	std::cout << "Amount";
	gotoxy(50, 4);
	std::cout << "Tax";
	gotoxy(55, 4);
	std::cout << "Amount after tax and discount";
	gotoxy(1, 5);
	std::cout << "\n--------------------------------------------------------------------------------------------";
	unsigned int z = 7;
	std::string string = "";
	for (size_t x = 0; x <= index; x++)
	{
		std::ifstream testFile("Test.json", std::ios_base::binary);
		Json::Value actualJson;
		if (!testFile)
		{
			exit(-1);
		}
		testFile >> actualJson;

		for (int i = 0; i < actualJson.size(); i++)
		{
			if (numberOfProducts[x] == actualJson[std::to_string(i)]["ProductID"].asUInt())
			{
				initialAmount = actualJson[std::to_string(i)]["Price"].asFloat() * quantity[x];
				finalAmount = (initialAmount * 1.15) - (initialAmount * actualJson[std::to_string(i)]["Discount"].asFloat() / 100);
				gotoxy(1, z);
				std::cout << actualJson[std::to_string(i)]["Product"].asString();
				gotoxy(21, z);
				std::cout << quantity[x];
				gotoxy(30, z);
				std::cout << actualJson[std::to_string(i)]["Price"];
				gotoxy(41, z);
				std::cout << initialAmount;
				gotoxy(50, z);
				std::cout << "15%";
				gotoxy(55, z);
				std::cout << finalAmount;
				z++;
				string += "\n(Product: " + actualJson[std::to_string(i)]["Product"].asString() + ") (Quantity: " + std::to_string(quantity[x]) + ") (Price: " + actualJson[std::to_string(i)]["Price"].asString() + ") (Initial Amount: " + std::to_string(initialAmount) + ") (Final Amount: " + std::to_string(finalAmount) + ')';
				total += finalAmount;
			}
		}
		testFile.close();
	}

	gotoxy(1, z + 3);
	cuout();
	gotoxy(1, z + 6);
	std::cout << "\bTotal number of items purchased: " << index;
	gotoxy(1, z + 9);
	std::cout << "\bTOTAL = " << total << " CA$";
	std::string customer = cus.name + ';' + cus.address;
	customer += string;
	//std::cout << std::endl << customer;
	customers.enQueue(customer);
}

void Delete()
{
	menu();
	unsigned int x;
	std::cout << "\n\nEnter the Company ID: "; std::cin >> x;
	DS::linkedList<Product> pr;
	std::fstream testFile("Test.json", std::ios_base::binary | std::ios_base::in);
	Json::Value actualJson;
	testFile >> actualJson;
	testFile.close();
	parserLinkedList(actualJson, pr);
	pr.Delete(x);
	actualJson.clear();
	senderLinkedList(actualJson, pr);
	testFile.open("Test.json", std::ios_base::binary | std::ios_base::out);
	testFile << actualJson;
	testFile.close();
}

void search()
{
	unsigned int x;
	std::cout << "Enter the Company ID: "; std::cin >> x;
	DS::BST<Product> pr;
	std::ifstream testFile("Test.json", std::ios_base::binary);
	Json::Value actualJson;
	testFile >> actualJson;
	testFile.close();
	parserBST(actualJson, pr);
	pr.search(Product(x));
}

void sortByPrice()
{
	DS::linkedList<Product> pr;
	std::ifstream testFile("Test.json", std::ios_base::binary);
	Json::Value actualJson;
	testFile >> actualJson;
	testFile.close();
	parserLinkedList(actualJson, pr);
	pr.sort();
	pr.print();
}

//admin menu
void admin()
{
	int x, i = 0;
	system("cls");
	std::cout << "\nEnter password to enter Adminstrator menu: ";
	char ch[9], c = ' ';
	while ((i < 8) && (c != '\n'))
	{
		ch[i] = _getch();
		std::cout << '*';
		++i;
	}
	ch[i] = '\0';

	if (strcmp(ch, "password") == 0)
	{
		std::cout << "\nCorrect password";
		std::cin.get();
		system("cls");
		char u = 'Y';
		while (u == 'Y' || u == 'y')
		{
			std::cout << "\n\tADMINISTRATOR MENU";
			std::cout << "\n\t1.CREATE LIST";
			std::cout << "\n\t2.ADD PRODUCT";
			std::cout << "\n\t3.SHOW ALL PRODUCTS";
			std::cout << "\n\t4.SHOW ALL CUSTOMERS";
			std::cout << "\n\t5.SEARCH AND DISPLAY BY COMPANY ID";
			std::cout << "\n\t6.DELETE PRODUCT";
			std::cout << "\n\t7.SORT BY PRICE";
			std::cout << "\n\t8.VIEW PRODUCT MENU";
			std::cout << "\n\t9.BACK TO MAIN MENU";
			std::cout << "\n\n\tEnter Your Choice (1-9) ";
			std::cout << "\nEnter choice: "; std::cin >> x;
			system("cls");
			switch (x)
			{
			case 1:
			{
				create();
				break;
			}
			case 2:
			{
				add();
				break;
			}
			case 3:
			{
				display();
				break;
			}
			case 4:
			{
				customers.print();
				break;
			}
			case 5:
			{
				search();
				break;
			}
			case 6:
			{
				Delete();
				break;
			}
			case 7:
			{
				sortByPrice();
				break;
			}
			case 8:
			{
				menu();
				break;
			}
			case 9:return;
			default: std::cout << "Invalid.";
			}
			std::cout << "\nStay in Admin menu(Y/N)?"; std::cin >> u;
			system("cls");
		}

	}
	else
	{
		std::cout << "\nIncorrect password";
		std::cin.get();
		exit(0);
	}
}
//customer menu
void customen()
{
	system("cls");
	int x;
	system("cls");
	std::cout << "1...BUY";
	std::cout << "\n2...BACK TO MAIN MENU.";
	std::cout << "\nEnter choice: "; std::cin >> x;
	switch (x)
	{
	case 1: {
		customerMenu();
		break;
	}
	case 2:break;
	default:std::cout << "\nInvalid";
	}
	std::cin.get();
}

int main()
{
	char ans = 'y';
	do
	{
		system("cls");
		gotoxy(35, 10);
		std::cout << "1. CUSTOMER";
		gotoxy(35, 12);
		std::cout << "2. ADMINISTRATOR";
		gotoxy(35, 14);
		std::cout << "3. EXIT";
		int x;
		gotoxy(35, 16);
		std::cout << "Enter choice: "; std::cin >> x;
		switch (x)
		{
		case 1: {customen();
			break;
		}
		case 2: {admin();
			break;
		}
		case 3:exit(0);
		default:std::cout << "\nInvalid.";
		}
		std::cout << "\nMain Menu(Y/N)? "; std::cin >> ans;
	} while (ans == 'y' || ans == 'Y');
}