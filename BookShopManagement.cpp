// +----------------------------------+
// |          HEADER FILES            |
// +----------------------------------+

#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <conio.h>
#define HOST "127.0.0.1"
#define USER "root"
#define PASS /*put the password of MySQL in here between ""*/
#define DATABASE "Management"
#define PORT 3306
#define PASSWORD /*Set a Numeric Password for Your Application*/

using namespace std;

// +--------------------------------+
// |		Global Variable     |
// +--------------------------------+

MYSQL * conn;
MYSQL_RES *res_set;
MYSQL_ROW row;
stringstream stmt;
const char * q;
string query;
// my_bool result;

typedef struct
{
	int date;
	int month;
	int year;
}date;


// +----------------------------------+
// |	         Classes Made 		  |
// +----------------------------------+

class books
{
	int id;			// Primary Key
	string name;
	string auth;
	int price;
	int qty;
public:
	void add();
	void update_price();
	void search();
	void update();
	void display();
};

class suppliers
{
	int id;				//Primary Key
	string name;
	long int phn;
	string addr_line1;
	string addr_line2;
	string addr_city;
	string addr_state;
public:
	void add_sup();
	void remove_supplier();
	void search_id();
};

class purchases
{
	int ord_id;			//Primary Key
	int book_id;		//FK ref (books)
	int sup_id;			//FK ref (suppliers)
	int qty;
	date dt_ordered;
	int eta;
	char received;		// Check(T or C or F) def (F)
	int inv;
public:
	void new_ord();
	void view();
	void mar_cancel();
	void mark_reciv();
};

class employees
{
	int id;				//Primary Key
	string name;
	string addr_line1;
	string addr_line2;
	string addr_city;
	string addr_state;
	long int phn;
	date date_of_joining;
	long int salary;
	string mgr_status;	//check(T or F) def f
public:
	void add_emp();
	void search_emp();
	void assign_mgr_stat();
	void display();
	void update_sal();
};

class members
{
    int id;				//Primary Key
	string name;
	string addr_line1;
	string addr_line2;
	string addr_city;
	string addr_state;
	long int phn;
	date beg_date;
	date end_date;
	string valid;
public:
	void add_mem();
	void refresh();
	void search_mem();
};

class sales
{
	int invoice_id;		//Primary key
 	int member_id;		//FK ref member(id)
	int book_id;		//FK ref books(id)
	int qty;
	int amount;
	date date_s;
public:
	void add();
	void find_total_sales();
};
// +----------------------------------+
// |		Main Function 	      |
// +----------------------------------+

int main()
{
	pass();
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, HOST, USER, PASS, DATABASE, PORT, NULL, 0);
	int choice;
	if(conn)
    {
		while(1)
		{
			system("cls");
			main_menu();
		}
    }
	else
	{
	    system("cls");
		cout << "Error While connection to database." << endl << "Contact Tech Expert." << endl;
		getch();
	}
	return 0;
}
