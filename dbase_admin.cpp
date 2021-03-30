#include "dbase_admin.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>


    Dbase_admin::Dbase_admin(const QString &path)
    {
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path);
        if(!db.open())
        {
            qDebug() <<"Error:Connection with database";
        }
        else
        {
            qDebug() <<"Sucess:Connection with database";
        }
    }

    Dbase_admin::~Dbase_admin()
    {
        if(db.open())
        {
            db.close();
        }
    }

    bool Dbase_admin::isOpen() const
    {
        return db.isOpen();
    }
bool Dbase_admin::userAuth(const QString &uname, const QString &pass) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT UserName FROM Admin WHERE UserName =:uname AND Password = :pass");
    checkQuery.bindValue(":uname", uname);
    checkQuery.bindValue(":pass", pass);
    if (checkQuery.exec()){
        if (checkQuery.next()){
            qDebug()<<"admin exists";
            exists = true;
        }
    }else{
        qDebug() << "user exists failed: " << checkQuery.lastError();
    }
    return exists;
}

  void Dbase_admin::createCompanyTable()
  {

      QSqlQuery qry;
      qry.prepare("CREATE TABLE Company(Name TEXT,VAT TEXT,Phone TEXT,Address TEXT,Email TEXT,Website TEXT)");

      if (!qry.exec())
      {
          qDebug() <<"Couldn't create Table,one might already exist";

      }
      else
      {
          qDebug()<<"Create table";
      }

  }

  bool Dbase_admin::addCompanyDetails(const QString &name, const QString &vat, const QString &phone, const QString &address, const QString &email, const QString &website)
  {
      bool sucess=false;
      QSqlQuery qry;
      qry.prepare("INSERT INTO Company(Name,VAT,Phone,Address,Email,Website) VALUES (:name,:vat,:phone,:address,:email,:website)");

      qry.bindValue(":name",name);
      qry.bindValue(":vat",vat);
      qry.bindValue(":phone",phone);
      qry.bindValue(":address",address);
      qry.bindValue(":email",email);
      qry.bindValue(":website",website);

      if(!qry.exec())
      {
          qDebug()<<"Add Details Failed"<<qry.lastError();
          sucess=false;
      }
      else
      {
          qDebug()<<"Details added Sucessfully";
          sucess=true;
      }
      return sucess;
  }

  bool Dbase_admin::getCompanyDetails()
  {
      bool sucess=false;
      QSqlQuery qry;
      qry.prepare("SELECT * FROM Company");
      if(!qry.exec())
      {
          sucess=false;
      }
      else
      {
          sucess=true;
      }
      return sucess;
  }

  QList<QString> Dbase_admin::getComDetails()
  {
      QList<QString> companydetails;
      QSqlQuery qry;
      qry.prepare(QString("SELECT * FROM Company"));
      if(!qry.exec())
      {
          qDebug()<<"Error in retriving data"<<qry.lastError();
      }
      else
      {

         if(qry.next())
         {
             QString name=qry.value(0).toString();
             QString vat=qry.value(1).toString();
             QString phone=qry.value(2).toString();
             QString address=qry.value(3).toString();
             QString email=qry.value(4).toString();
             QString website=qry.value(5).toString();

             companydetails.push_front(name);
             companydetails.push_front(vat);
             companydetails.push_front(phone);
             companydetails.push_front(address);
             companydetails.push_front(email);
             companydetails.push_front(website);
         }
         else
         {
             qDebug()<<"not executing qyery";
         }

      }
        return companydetails;
  }

  bool Dbase_admin::removeCompanyDetails()
  {
      bool  sucess=false;
      QSqlQuery qry;
      qry.prepare("DELETE FROM Company");
      if(qry.exec())
      {
          sucess=true;
      }
      else
      {
          sucess=false;
          qDebug()<<"failed to delete company";
      }
      return sucess;
  }

  void Dbase_admin::createCashierTable()
  {

      QSqlQuery qry;
      qry.prepare("CREATE TABLE Cashier(Name TEXT,UserName TEXT,Gender TEXT,Phone TEXT,Email TEXT,Password TEXT)");

      if (!qry.exec())
      {
          qDebug() <<"Couldn't create Table,one might already exist";

      }
      else
      {
          qDebug()<<"Create table";
      }

  }

  bool Dbase_admin::addCashierDetails(const QString &name, const QString &uname,const QString &gender,const QString &phone, const QString &email, const QString &password)
  {
      bool sucess=false;
      QSqlQuery qry;
      qry.prepare("INSERT INTO Cashier(Name,UserName,Gender,Phone,Email,Password) VALUES (:name,:uname,:gender,:phone,:email,:password)");

      qry.bindValue(":name",name);
      qry.bindValue(":uname",uname);
      qry.bindValue(":gender",gender);
      qry.bindValue(":phone",phone);
      qry.bindValue(":email",email);
      qry.bindValue(":password",password);

      if(!qry.exec())
      {
          qDebug()<<"Add Details Failed"<<qry.lastError();
          sucess=false;
      }
      else
      {
          qDebug()<<"Details added Sucessfully";
          sucess=true;
      }
      return sucess;
  }

  bool Dbase_admin::modifyCashierDetails(const QString &uname)
  {
      bool sucess=false;
      QSqlQuery qry;
      qry.prepare("SELECT * FROM Company WHERE UserName=:uname");
      if(!qry.exec())
      {
          sucess=false;
      }
      else
      {
          sucess=true;
      }
      return sucess;
  }

  void Dbase_admin::removeCashier(const QString &uname,const QString &email)
  {
      QSqlQuery qry;
      qry.prepare("DELETE FROM Cashier WHERE UserName=:uname OR Email=:email");
      qry.bindValue(":uname",uname);
      qry.bindValue(":email",email);
       qry.exec();
  }

bool Dbase_admin::removeCashierTable()
{
    QSqlQuery qry;
    qry.prepare("DROP TABLE Cashier");
    qry.exec();
    return true;
}

bool Dbase_admin::validCashier(const QString &uname, const QString &email)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Cashier WHERE UserName=:uname OR Email=:email");
    qry.bindValue(":uname",uname);
    qry.bindValue(":email",email);
    if(qry.exec())
    {
        if(qry.next())
        {
          qDebug()<<"Cashier found";
          return true;
        }

    }
    else
    {
        qDebug()<<"No Cashier Found";
        return false;
    }
}

bool Dbase_admin::cashier_unameExists(const QString &uname)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Cashier WHERE UserName=:uname");
    qry.bindValue(":uname",uname);
    if(qry.exec())
    {
        if(qry.next())
        {
          return true;
        }

    }
    else
    {
        return false;
    }

 }

bool Dbase_admin::cashier_emailExists(const QString &email)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Cashier WHERE Email=:email");
    qry.bindValue(":email",email);
    if(qry.exec())
    {
        if(qry.next())
        {
          return true;
        }

    }
    else
    {
        return false;
    }
}

 void Dbase_admin::viewCashier()
{
     QSqlQueryModel *model= new QSqlQueryModel();

     QSqlQuery *qry=new QSqlQuery(db);
     qry->prepare("SELECT * FROM Cashier");

     qry->exec();

     model->setQuery(*qry);
}

  void Dbase_admin::deleteAdmin_Login()
  {
      QSqlQuery qry;
      qry.prepare("DROP TABLE Admin_Login");
      if(qry.exec())
      {
          qDebug()<<"Admin_Login Table deleted";
      }
      else
      {
          qDebug()<<"Couldn't delete table";
      }
   }

  QList<QString> Dbase_admin::getAdmin_LoginDetails()
  {
      QList<QString> admindetails;
      QSqlQuery qry;
      qry.prepare(QString("SELECT * FROM Admin_Login"));
      if(!qry.exec())
      {
          qDebug()<<"Error in retriving data"<<qry.lastError();
      }
      else
      {

         if(qry.next())
         {
             QString fname=qry.value(0).toString();
             QString lname=qry.value(1).toString();
             QString username=qry.value(2).toString();
             QString mobileno=qry.value(3).toString();
             QString email=qry.value(4).toString();
             QString passwd=qry.value(5).toString();

             admindetails.push_front(fname);
             admindetails.push_front(lname);
             admindetails.push_front(username);
             admindetails.push_front(mobileno);
             admindetails.push_front(email);
             admindetails.push_front(passwd);
         }
         else
         {
             qDebug()<<"not executing qyery";
         }

      }
        return admindetails;
  }

bool Dbase_admin::uNameExists(const QString &uname)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Admin_Login WHERE UserName=:uname");
    qry.bindValue(":uname",uname);
    if(qry.exec())
    {
        if(qry.next())
        {
            qDebug()<<"Username exists";
            return true;
        }

    }
    else
    {
        qDebug()<<"Username doesn't exist";
        return false;
    }
}

bool Dbase_admin::passwordValid(const QString &passwd)
{
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM Admin_Login WHERE Password=:passwd");
    checkQuery.bindValue(":passwd",passwd);
    if(checkQuery.exec())
    {
        if(checkQuery.next())
        {
            qDebug()<<"password valid";
            return true;
        }

    }
    else
    {
        qDebug()<<"password invalid";
        return false;
    }
}

void Dbase_admin::changeAdminPassword(const QString& uname,const QString& npasswd)
{
    QSqlQuery qry;
    qry.prepare("UPDATE Admin SET Password=:npasswd WHERE UserName=:uname");
    qry.bindValue(":npasswd",npasswd);
    qry.bindValue(":uname",uname);
    if(qry.exec())
    {
        qDebug()<<"Password changed(Admin)";
    }
    else
    {
        qDebug()<<"password couldn't be changed(Admin)"<<qry.lastError();
    }
}

void Dbase_admin::changeAdmin_LoginPassword(const QString& uname,const QString& npasswd)
{
    QSqlQuery qry;
    qry.prepare("UPDATE Admin_Login SET Password=:npasswd WHERE UserName=:uname");
    qry.bindValue(":npasswd",npasswd);
    qry.bindValue(":uname",uname);
    if(qry.exec())
    {
        qDebug()<<"Password changed(Admin_Login)";
    }
    else
    {
        qDebug()<<"password couldn't be changed(Admin_Login)"<<qry.lastError();
    }
}

void Dbase_admin::createProductTable()
{
    QSqlQuery qry;
    qry.prepare("CREATE TABLE Product(ID TEXT,Name TEXT,Category TEXT,Price REAl)");

    if (!qry.exec())
    {
        qDebug() <<"Couldn't create Table,one might already exist";

    }
    else
    {
        qDebug()<<"Create table";
    }
}

bool Dbase_admin::addProduct(const QString &id, const QString &name, const QString &category, const QString &price)
{
    bool sucess=false;
    QSqlQuery qry;
    qry.prepare("INSERT INTO Product(ID,Name,Category,Price) VALUES (:id,:name,:category,:price)");

    qry.bindValue(":id",id);
    qry.bindValue(":name",name);
    qry.bindValue(":category",category);
    qry.bindValue(":price",price);

    if(!qry.exec())
    {
        qDebug()<<"Add Details Failed"<<qry.lastError();
        sucess=false;
    }
    else
    {
        qDebug()<<"Details added Sucessfully";
        sucess=true;
    }
    return sucess;
}


bool Dbase_admin::product_IdExists(const QString &id)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Product WHERE ID=:id");
    qry.bindValue(":id",id);
    if(qry.exec())
    {
        if(qry.next())
        {
            qDebug()<<"ID exists";
            return true;
        }

    }
    else
    {
        qDebug()<<"ID doesn't exist";
        return false;
    }
}

bool Dbase_admin::product_NameExists(const QString &name)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Product WHERE Name=:name");
    qry.bindValue(":name",name);
    if(qry.exec())
    {
        if(qry.next())
        {
            qDebug()<<"name exists";
            return true;
        }

    }
    else
    {
        qDebug()<<"name doesn't exist";
        return false;
    }
}

void Dbase_admin::deleteProducts(const QString &id, const QString &category)
{
    QSqlQuery qry;
    qry.prepare("DELETE FROM Product WHERE ID=:id OR Category=:category");
    qry.bindValue(":id",id);
    qry.bindValue(":category",category);
    qry.exec();
}

bool Dbase_admin::validProduct(const QString &id, const QString &category)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Product WHERE ID=:id OR Category=:category");
    qry.bindValue(":id",id);
    qry.bindValue(":category",category);
    if(qry.exec())
    {
        if(qry.next())
        {
            qDebug()<<"product found";
            return true;
        }
    }
    else
    {
        qDebug()<<"No Product Found";
        return false;
    }
}
