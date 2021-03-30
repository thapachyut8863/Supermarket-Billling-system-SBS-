#include "cashierwindow.h"
#include "ui_cashierwindow.h"

CashierWindow::CashierWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CashierWindow)
{
    ui->setupUi(this);
    QDate date;
    QString currentDate=date.currentDate().toString();
    ui->currentDate->setText(currentDate);
    ui->privacyStack->setCurrentIndex(0);
    ui->cashierStack->setCurrentIndex(3);
    ui->billStack->setCurrentIndex(2);
    ui->billTableStack->setCurrentIndex(0);
    showCashier_LoginDetails();
    showCompanyDetails();
}

CashierWindow::~CashierWindow()
{
    delete ui;
}

void CashierWindow::showCashier_LoginDetails()
{
    Dbase_Cashier db("SBS.db");
    if(!db.isOpen())
    {
        qDebug()<<"Not opening database";
    }
    else
    {
        qDebug()<<"Opening Database";
        QString name,username,gender,mobileno,email,passwd;
        QList<QString> cashier_details=db.getCashier_loginDetails();
        if(cashier_details.isEmpty())
        {
            qDebug()<<"error in retriving cashier details";
        }
        else
        {
            qDebug()<<"retriving data from cashier";
            //retriving data from Cashier
            passwd=cashier_details.takeAt(0);
            email=cashier_details.takeAt(0);
            mobileno=cashier_details.takeAt(0);
            gender=cashier_details.takeAt(0);
            username=cashier_details.takeAt(0);
            name=cashier_details.takeAt(0);

           //Showing information
            ui->cashierUsernameLabel_2->setText(username);
            ui->cashierNameLabel->setText(name);
            ui->cashierMobileLabel->setText(mobileno);
            ui->cashierEmailLabel->setText(email);
           if(gender=="Male") ui->profileButton->setStyleSheet("border-image: url(:/male.jpeg);");
            if(gender=="Female") ui->profileButton->setStyleSheet("border-image: url(:/female.png);");
        }

    }
}

void CashierWindow:: showCompanyDetails()
{
    Dbase_Cashier db("SBS.db");
    if(!db.isOpen())
    {
        qDebug()<<"Not opening database";
    }
    else
    {
        //retriving data from database
        QString name,vat,phone,address,email,website;
        QList<QString> com_det=db.getComDetails();
        if(!com_det.isEmpty())
        {
           //retriving data from list
            website=com_det.takeAt(0);
            email=com_det.takeAt(0);
            address=com_det.takeAt(0);
            phone=com_det.takeAt(0);
            vat=com_det.takeAt(0);
            name=com_det.takeAt(0);

            //Showing results
            ui->companyName->setText(name);
            ui->nameLabel_2->setText(name);
            ui->vatLabel_2->setText(vat);
            ui->phoneLabel_2->setText(phone);
            ui->addressLabel_2->setText(address);
            ui->emailLabel_2->setText(email);
            ui->websiteLabel_2->setText(website);
        }
        else
        {
            qDebug()<<"Error in getting list";
        }
    }
}

void CashierWindow::on_homeButton_clicked()
{
    ui->privacyStack->setCurrentIndex(0);
    ui->cashierStack->setCurrentIndex(0);
    ui->homeStack->setCurrentIndex(0);
    showCashier_LoginDetails();
    showCompanyDetails();
}

void CashierWindow::on_productButton_clicked()
{
    ui->privacyStack->setCurrentIndex(0);
    ui->cashierStack->setCurrentIndex(1);
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM Product");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
    setProductTable();
}

void CashierWindow::on_invoiceButton_clicked()
{
    ui->privacyStack->setCurrentIndex(0);
    ui->cashierStack->setCurrentIndex(3);
}

void CashierWindow::setTransactionTable()
{
    ui->transactionTable->setColumnWidth(0,150);
    ui->transactionTable->setColumnWidth(1,200);
    ui->transactionTable->setColumnWidth(2,200);
    ui->transactionTable->setColumnWidth(3,250);
}

void CashierWindow::on_saleButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT Bill,Date,Amount FROM History WHERE Cashier=:cashier");
    qry->bindValue(":cashier",ui->cashierUsernameLabel_2->text());
    qry->exec();

    model->setQuery(*qry);
    ui->privacyStack->setCurrentIndex(0);
    ui->cashierStack->setCurrentIndex(2);
    ui->historyStack->setCurrentIndex(0);
    ui->transactionTable->setModel(model);
    setTransactionTable();
}

void CashierWindow::on_profileButton_clicked()
{
    int curind=ui->privacyStack->currentIndex();
    if(curind==0)
    {
     ui->privacyStack->setCurrentIndex(1);
    }
    else
    {
      ui->privacyStack->setCurrentIndex(0);
    }
}

void CashierWindow::on_logoutButton_clicked()
{
    //delete Cashier_Login Table
    Dbase_Cashier db("SBS.db");
    db.deleteCashier_Login();

//    mainwindow=new QMainWindow(this);
    this->hide();
    QWidget *parent = this->parentWidget();
    parent->show();
//    mainwindow->show();
}

void CashierWindow::setProductTable()
{
    ui->productTable->setColumnWidth(0,150);
    ui->productTable->setColumnWidth(1,300);
    ui->productTable->setColumnWidth(2,200);
    ui->productTable->setColumnWidth(3,150);
}

void CashierWindow::on_allButton_clicked()
{
    on_productButton_clicked();
}

void CashierWindow::on_groceryButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM Product WHERE Category='Grocery'");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
    setProductTable();
}

void CashierWindow::on_fashionButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM Product WHERE Category='Fashion'");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
    setProductTable();
}

void CashierWindow::on_homeappButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM Product WHERE Category='Home Appliances'");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
    setProductTable();
}

void CashierWindow::on_kidButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM Product WHERE Category='Kids'");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
    setProductTable();
}

void CashierWindow::on_liquorButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM Product WHERE Category='Liquor'");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
    setProductTable();
}

void CashierWindow::on_giftsButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM Product WHERE Category='Games'");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
    setProductTable();
}

void CashierWindow::on_otherButton_clicked()
{
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT * FROM Product WHERE Category='Other'");

    qry->exec();

    model->setQuery(*qry);
    ui->cashierStack->setCurrentIndex(1);
    ui->productTable->setModel(model);
    setProductTable();
}

void CashierWindow::on_editCashierButton_clicked()
{
  ui->privacyStack->setCurrentIndex(0);
  ui->cashierStack->setCurrentIndex(4);
}

void CashierWindow::on_saveChangeButton_clicked()
{
    QString username=ui->userName->text();
    QString opasswd=ui->oldPassword->text();
    QString npasswd=ui->newPassword->text();
    QString conpasswd=ui->confirmPassword->text();

    Dbase_Cashier db("SBS.db");
    if(db.validCashier(username,opasswd))
    {
        if(!(npasswd==conpasswd)){QMessageBox::warning(this,"Confirm Password","Confirm password doennot match");}
        else
        {
            db.updateCashier(username,npasswd);
            QMessageBox::information(this,"Change Password","Password Changed Sucessfully");
            {
              on_logoutButton_clicked();
            }
        }
    }
    else
    {
        QMessageBox::information(this,"Change Password","Incorrect UserName or Password");
    }
}

void CashierWindow::on_checkProduct_clicked()
{
    QString id=ui->productID->text();
    QString particulars;
    Dbase_Cashier db("SBS.db");
    //check product validation
    if(!db.validProduct(id)){QMessageBox::information(this,"Check Product","Invalid Product"); ui->productID->setText("");}
    else
    {
        QList<QString>pro = db.getProductDetails(id);
        QString name=pro[2];
        if(name.count()>=12){
         particulars=name.left(12);
        }
        if(name.count()<12){
            for(int i=name.count();i<12;i++)
            {
                name+=" ";
            }
            particulars=name;
        }
        ui->checkedProduct->setText(particulars);
        if(!db.product_IdExists(id)){ui->billStack->setCurrentIndex(0);}
        else{ui->billStack->setCurrentIndex(1);}
    }
}

void CashierWindow::on_addProduct_clicked()
{
    QString id,name;
    int quantity;
    double amount;
    QString particulars;
    id=ui->productID->text();
    quantity=ui->quantityBox->value();

    Dbase_Cashier db("SBS.db");
    QList<QString>pro = db.getProductDetails(id);
    double temp;
    temp = pro[0].toDouble();
    name=pro[2];
    if(name.count()>=12){
     particulars=name.left(12);
    }
    if(name.count()<12){
        for(int i=name.count();i<12;i++)
        {
            name+=" ";
        }
        particulars=name;
    }
    amount=quantity*temp;
    db.createBillTable();
    if(db.addProduct(id,particulars,quantity,temp,amount))
    {
        ui->productID->setText("");
        ui->billStack->setCurrentIndex(2);
       showbillTable(id,particulars,temp,quantity,amount);
       showAmount();
       ui->checkedProduct->setText("");
    }
}

void CashierWindow::showbillTable(const QString &id,const QString &particulars, const double &rate, const int &quantity, const double &amount)
{
    QString R=QString::number(rate);
    QString Q=QString::number(quantity);
    QString A=QString::number(amount);
     ui->billTableStack->setCurrentIndex(1);
    //show headers
    ui->billTable->setColumnCount(5);
    QStringList titles;
    titles <<"ID"<<"Particulars" <<"Rate" <<"Quantity" <<"Amount";
    ui->billTable->setHorizontalHeaderLabels(titles);
    ui->billTable->setColumnWidth(0,100);
    ui->billTable->setColumnWidth(1,300);
    ui->billTable->setColumnWidth(2,150);
    ui->billTable->setColumnWidth(3,250);
    ui->billTable->insertRow(ui->billTable->rowCount());
    int row=ui->billTable->rowCount() -1;
    ui->billTable->setItem(row,ID,new QTableWidgetItem(id));
    ui->billTable->setItem(row,Particulars,new QTableWidgetItem(particulars));
    ui->billTable->setItem(row,Rate,new QTableWidgetItem(R));
    ui->billTable->setItem(row,Quantity,new QTableWidgetItem(Q));
    ui->billTable->setItem(row,Amount,new QTableWidgetItem(A));
}

void CashierWindow::on_removeProduct_clicked()
{
    QString id=ui->productID->text();
    Dbase_Cashier db("SBS.db");

    QSqlQuery qry;
    qry.prepare("DELETE FROM Bill WHERE ID=:id");
    qry.bindValue(":id",id);
    if(qry.exec())
    {
        showAmount();
        ui->productID->setText("");
        ui->billStack->setCurrentIndex(2);

        ui->billTableStack->setCurrentIndex(1);
        int rows=ui->billTable->rowCount();
        int i;
        for(i=0;i<rows;i++)
        {
            if(ui->billTable->item(i,0)->text()==id)
            {
                break;
            }
        }
        ui->billTable->removeRow(i);
        ui->checkedProduct->setText("");
    }
}

void CashierWindow::on_additionMode_clicked()
{
   QString id=ui->productID->text();
   Dbase_Cashier db("SBS.db");

   QSqlQuery qry;
   qry.prepare("SELECT * FROM Bill WHERE ID=:id");
   qry.bindValue(":id",id);

   if(qry.exec())
   {
       if(qry.next()){
       int quantity=qry.value(3).toInt();
       double rate=qry.value(2).toDouble();
       quantity=quantity+1;
       double amount=rate*quantity;
       QString Q=QString::number(quantity);
       QString A=QString::number(amount);
       QSqlQuery query;
       query.prepare("UPDATE Bill SET Quantity=:quantity,Amount=:amount WHERE ID=:id");
       query.bindValue(":quantity",quantity);
       query.bindValue(":amount",amount);
       query.bindValue(":id",id);
       if(query.exec()){
           int rows=ui->billTable->rowCount();
           int i;
           for(i=0;i<rows;i++)
           {
               if(ui->billTable->item(i,0)->text()==id)
               {
                   break;
               }
           }
           ui->billTable->setItem(i,3,new QTableWidgetItem(Q));
           ui->billTable->setItem(i,4,new QTableWidgetItem(A));
      showAmount();
   }
   }
}
}

void CashierWindow::on_deductionMode_clicked()
{
    QString id=ui->productID->text();
    Dbase_Cashier db("SBS.db");

    QSqlQuery qry;
    qry.prepare("SELECT * FROM Bill WHERE ID=:id");
    qry.bindValue(":id",id);

    if(qry.exec())
    {
        if(qry.next()){
        int quantity=qry.value(3).toInt();
        double rate=qry.value(2).toDouble();
        quantity=quantity-1;
        double amount=rate*quantity;
        QString Q=QString::number(quantity);
        QString A=QString::number(amount);
        QSqlQuery query;
        query.prepare("UPDATE Bill SET Quantity=:quantity,Amount=:amount WHERE ID=:id");
        query.bindValue(":quantity",quantity);
        query.bindValue(":amount",amount);
        query.bindValue(":id",id);
        if(query.exec()){
            int rows=ui->billTable->rowCount();
            int i;
            for(i=0;i<rows;i++)
            {
                if(ui->billTable->item(i,0)->text()==id)
                {
                    break;
                }
            }
            ui->billTable->setItem(i,3,new QTableWidgetItem(Q));
            ui->billTable->setItem(i,4,new QTableWidgetItem(A));
       showAmount();
    }
    }
 }
}

void CashierWindow::showAmount()
{
    QString subtotal;
    Dbase_Cashier db("SBS.db");
    QList<QString> amountdetails=db.getAmount();
    double total;
    if(amountdetails.isEmpty())
    {
        qDebug()<<"empty";
        subtotal='0';
    }
    else
    {
        for(int i=0;i<amountdetails.count();i++)
        {
            total+=amountdetails[i].toDouble();
        }
        qDebug()<<total;
        subtotal=QString::number(total);
     }
        ui->subTotal->setText(subtotal);
}

void CashierWindow::on_printBillButton_clicked()
{
    QFile nFile("path.txt");

      if(!nFile.open(QFile::ReadOnly | QFile::Text))
      {
        qDebug() << "could not open file for reading";
        return;
      }
      QTextStream in(&nFile);
      QString path = in.readAll();
    nFile.close();
    Dbase_Cashier db("SBS.db");
    int billno=db.getBillNo();
    qDebug()<<billno;
    QDate Date;
    QString currentDate=Date.currentDate().toString("dd/MM/yyyy");
    QString subtotal=ui->subTotal->text();
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         qDebug()<<"file not open";

       QTextStream out(&file);
       QString companyName=ui->companyName->text();
       QString companyAddress=ui->addressLabel_2->text();
       QString companyPhone=ui->phoneLabel_2->text();
       QString companyEmail=ui->emailLabel_2->text();
       QString companyVAT=ui->vatLabel_2->text();
       QString cashier=ui->cashierUsernameLabel_2->text();
       out <<"                   "<<companyName<<endl;
       out <<"                   "<<companyAddress<<endl;
       out <<"                   "<<companyPhone<<","<<companyEmail<<endl;
       out <<"                   "<<"VAT No.:"<<companyVAT<<endl;
       out <<"                   "<<"ABBREVIATED TAX INVOICE"<<endl;
       out <<endl<<endl;
       out <<"Bill # :"<<billno<<endl;
       out <<"Date   :"<<ui->currentDate->text()<<endl;
       out<<"Payment Mode: Cash"<<endl;
       out <<"-------------------------------------------------------------"<<endl;
       out <<"ID\t" <<"Particulars\t"<<"Rate\t"<<"Quan.\t"<<"Amount"<<endl;
       out <<"-------------------------------------------------------------"<<endl;
       QString textData;
       int rows = ui->billTable->rowCount();
       int columns = ui->billTable->columnCount();
       for (int i = 0; i < rows; i++) {
           for (int j = 0; j < columns; j++){
                    textData += ui->billTable->item(i,j)->text();
                    textData += "\t";
           }
           textData += "\n";
       }
       int quantity=0;
       for (int i = 0; i < rows; i++) {
                    quantity += ui->billTable->item(i,3)->text().toInt();
           }
       out<<textData<<endl;
       out<<"                            -----------------------------------"<<endl;
       out<<"                                "<<"Total: "<<subtotal<<endl;
       out<<"                            -----------------------------------"<<endl;
       out<<"                                "<<"Total Quantity: "<<quantity<<endl;
       out<<"                            -----------------------------------"<<endl;
       out<<"Thank you for purchasing from "<<companyName<<endl<<"Please visit again!"<<endl;
       out <<"-------------------------------------------------------------"<<endl;
       out<<"Bill Printed By:"<<ui->cashierUsernameLabel_2->text()<<endl;
       out <<"-------------------------------------------------------------"<<endl;
        ui->productID->setText("");
        db.deleteBillTable();
        db.createHistoryTable();
        qDebug()<<rows;
        if(db.addHistory(currentDate,ui->subTotal->text().toDouble(),cashier))
        {
            ui->billTable->setRowCount(0);
             ui->billStack->setCurrentIndex(2);
             ui->billTableStack->setCurrentIndex(0);
        }
}

void CashierWindow::on_todayHistory_clicked()
{
    ui->historyStack->setCurrentIndex(0);
    QDate Date;
    QString currentDate=Date.currentDate().toString("dd/MM/yyyy");
    Dbase_Cashier db("SBS.db");
    QSqlQueryModel *model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery();
    qry->prepare("SELECT Bill,Date,Amount FROM History WHERE Date=:date AND Cashier=:cashier");
    qry->bindValue(":date",currentDate);
    qry->bindValue(":cashier",ui->cashierUsernameLabel_2->text());
    qry->exec();

    model->setQuery(*qry);
   ui->transactionTable->setModel(model);
   setTransactionTable();
}

void CashierWindow::on_gotodateHistory_clicked()
{
    ui->historyStack->setCurrentIndex(1);
}

void CashierWindow::on_okButton_clicked()
{
    QString day=ui->dCombo->currentText();
    QString month=ui->mCombo->currentText();
    QString year=ui->yCombo->currentText();
    if(day=="Day"||month=="Month"||year=="Year")
    {
        QMessageBox::information(this,"GoTo Date","Please Specify Correct Date");
    }
    else
    {
        QString date=day+'/'+month+'/'+year;
        Dbase_Cashier db("SBS.db");
        QSqlQueryModel *model= new QSqlQueryModel();

        QSqlQuery *qry=new QSqlQuery();
        qry->prepare("SELECT Bill,Date,Amount FROM History WHERE Date=:date AND Cashier=:cashier");
        qry->bindValue(":date",date);
        qry->bindValue(":cashier",ui->cashierUsernameLabel_2->text());
        qry->exec();

        model->setQuery(*qry);
       ui->transactionTable->setModel(model);
       setTransactionTable();
    }
}
