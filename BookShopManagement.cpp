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
// ------------
// class books
// ------------

void books::add()
{
    cout << "Enter the name of the book : " ;
    cin >> name;
    cout << "Enter the name of the author : ";
    cin >> auth;
    cout << "Enter the Price : ";
    cin >> price;
    cout << "Enter the Qty Recived : ";
    cin >> qty;
    stmt.str("");
    stmt << "Insert into books(name,auth,price,qty) values('" << name << "','" << auth << "'," << price << "," << qty << ");";
    query = stmt.str();
    q = query.c_str();
    mysql_query(conn,q);
    res_set = mysql_store_result(conn);
    if (!(res_set))
        cout << endl << endl << "Book Record Inserted Successfully" << endl << endl << endl;
    else
        cout << endl << endl << "Entry ERROR !" << endl << "Contact Technical Team " << endl << endl << endl;
}

void books::update_price()
{
    char choice;
    cout << "Enter the id of the book for update in price : ";
    cin >> id;
    stmt.str("");
    stmt << "Select name,price from books where id = " << id << ";";
    query = stmt.str();
    q = query.c_str();
    mysql_query(conn,q);
    res_set = mysql_store_result(conn);
    if((row = mysql_fetch_row(res_set)) != NULL)
    {
        cout << "The Name of the book is : " << row[0] << endl ;
        cout << "The current price of the book is : " << row[1] << endl ;
        cout << "Do you Want to Update the Price [y/n] : " ;
        cin >> choice;
        if (choice == 121 || choice == 89)
        {
            cout << "Enter the new price : ";
            cin >> price;
            stmt.str("");
            stmt << "Update books set price = " << price << " where id = " << id << ";";
            res_set = mysql_store_result(conn);
            if (!(res_set))
                cout << endl << endl << "Book Price Updated Successfully" << endl << endl << endl;
            else
                cout << endl << endl << "Entry ERROR !" << endl << "Contact Technical Team " << endl << endl << endl;
        }
        else
        {
            cout << "No changes Made!!";
        }
    }
    else
    {
        cout << "No Book found!!!";
    }
}

void books::search()
{
    cout << "Enter book id for details : ";
    cin >> id;
    stmt.str("");
    stmt << "Select * from books where id = " << id << ";";
    query = stmt.str();
    q = query.c_str();
    mysql_query(conn,q);
    res_set = mysql_store_result(conn);
    if((row = mysql_fetch_row(res_set)) != NULL)
    {
        cout << "The Details of Book Id " << row[0] << endl;
        cout << "The Name of the book is : " << row[1] << endl ;
        cout << "THE Author of " << row[1] << " is " << row[2] << endl;
        cout << "The Price of the book is : " << row[3] << endl ;
        cout << "The inventory count is " << row[4] << endl;
    }
    else
    {
        cout << "No record Found" << endl;
    }
}

void books::update()
{
    int b_id[100],qty[100],i = 0,max;
    stmt.str("");
    stmt << "Select book_id,qty from purchases where recieves = 'T' and inv IS NULL;";
    query = stmt.str();
    q = query.c_str();
    mysql_query(conn,q);
    res_set = mysql_store_result(conn);
    stmt.str("");
    stmt << "Update purchases set inv = 1 where recieves = 'T' and inv IS NULL;";
    query = stmt.str();
    q = query.c_str();
    mysql_query(conn,q);
    while((row = mysql_fetch_row(res_set)) != NULL)
    {
        b_id[i] = (int) row[0];
        qty[i] = (int) row[1];
        i++;
    }
    max = i;
    for(i = 0; i <= max; i++)
    {
        stmt.str("");
        stmt << "update books set qty = " << qty[i] << " where id = " << b_id[i] << ";";
        query = stmt.str();
        q = query.c_str();
        mysql_query(conn,q);
    }
    cout << "The orders recieved have been updated.";
}

void books::display()
{
    int i = 0;
    query = "Select * from books;";
    q = query.c_str();
    mysql_query(conn,q);
    res_set = mysql_store_result(conn);
    while((row = mysql_fetch_row(res_set)) != NULL)
    {
        cout << "Name for book " << ++i << " : " << row[1] << endl;
        cout << "Name of Author : " << row[2] << endl;
        cout << "Price : " << row[3] << endl;
        cout << "Quantity : " << row[4] << endl;
        cout << endl << endl << endl << endl ;
    }
}
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
