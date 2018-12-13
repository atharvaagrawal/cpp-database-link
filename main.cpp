
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <sstream>
#include<string>
#include <sqlite3.h>
#include<cstdlib>
using namespace std;

/*Global Variable */
sqlite3 *db;
char *zErrMsg = 0;
int rc;
char *sql;
const char* data = "Callback function called";


static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   for(i = 0; i<argc; i++)
   {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

class Student
{
   protected:

   string roll,clas;
   string name,phone;
};

class Result:public Student
{
    string m1,m2,m3;
    string total,avg;

    public:
            void accept();
            void display();
            void update();
            void deletep();
            void create();

};

void Result::create()
{
    /* Create SQL statement */

    sql = "CREATE TABLE STUDENT("  \
        "ROLL_NO INT PRIMARY KEY ," \
        "NAME  CHAR(20)," \
        "CLASS   INT     NOT NULL," \
        "PHONENO  BIGINT," \
        "MATH CHAR(20),"\
        "SCIENCE CHAR(20),"\
        "ENGLISH CHAR(20),"\
        "TOTAL INT ,"\
        "AVERAGE FLOAT );";


   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Table created successfully\n");
   }

}

void Result::accept()
{
    cout<<"\n\n Enter Roll number and Name: ";
    cin>>roll>>name;

    cout<<"\n\n Enter class and phone number: ";
    cin>>clas>>phone;

    cout<<"\n\n Enter 3 subject marks ";
    cout<<"\n Order Math,Science and English: ";
    cin>>m1>>m2>>m3;

    int temp_m1 = atoi(m1.c_str());
    int temp_m2 = atoi(m2.c_str());
    int temp_m3 = atoi(m3.c_str());

    int temp_total=temp_m1+temp_m2+temp_m3;
    float temp_avg=temp_total/3.0;

    // declaring output string stream
    ostringstream str1,str2;

    str1 << temp_total;
    str2 << temp_avg;

    total=str1.str();
    avg=str2.str();

    string query="insert into student values('"+roll+"','"+name+"','"+clas+"','"+phone+"','"+m1+"','"+m2+"','"+m3+"','"+total+"','"+avg+"');";

    const char* q=query.c_str();

   /* Execute SQL statement */
   rc = sqlite3_exec(db,q, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Records created successfully\n");
   }

}

void Result::display()
{
   /* Create SQL statement */
   sql = "SELECT * from STUDENT";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Operation done successfully\n");
   }
}

void Result:: update()
{
    cout<<"\n\n Enter Class to update enter roll no where to update :";
    cin>>clas>>roll;
   /* Create merged SQL statement */
   string query="update student set class='"+clas+"' where roll_no='"+roll+"' ";

   const char* q=query.c_str();

   /* Execute SQL statement */
   rc = sqlite3_exec(db, q, callback, (void*)data, &zErrMsg);

   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);

}

void Result:: deletep()
{
    cout<<"\n\n Enter Student Roll Number to Delete: ";
    cin>>roll;

   /* Create merged SQL statement */
    string query="delete from student where roll_no='"+roll+"';";


    const char* q=query.c_str();
   /* Execute SQL statement */
   rc = sqlite3_exec(db, q, callback, (void*)data, &zErrMsg);

   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Operation done successfully\n");
   }

}


int main(int argc, char* argv[])
{
   int ch;
   Result R;

   /* Open database */
   rc = sqlite3_open("test.db", &db);

   if( rc )
   {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }
   else
   {
      fprintf(stdout, "Opened database successfully\n");
   }

  while(1)
  {
      cout<<"\n\n Menu: ";
      cout<<"\n 1.Create Table ";
      cout<<"\n 2.Update ";
      cout<<"\n 3.Delete ";
      cout<<"\n 4.Display ";
      cout<<"\n 5.Insert";
      cout<<"\n 6.Exit";
      cout<<"\n\n Enter your Choice(1/2/3/4/5): ";
      cin>>ch;

      switch(ch)
      {
         case 1: R.create();
                 break;

         case 2: R.update();
                 break;

         case 3: R.deletep();
                 break;

         case 4: R.display();
                 break;

         case 5: R.accept();
                 break;

         case 6: exit(0);

         default: cout<<"\n\n Wrong Choice. ";
      }
  }

   sqlite3_close(db);

   return 0;
}
