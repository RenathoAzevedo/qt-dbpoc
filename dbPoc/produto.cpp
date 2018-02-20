#include "produto.h"
#include "ui_produto.h"
#include "modelproxy.h"

Produto::Produto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Produto)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setShowGrid(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->verticalScrollBar()->hide();

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Produto.sqlite");

    // tenta abrir conexão
    if(!db.open())
    {
        QMessageBox::critical(this, "Erro no Banco de Dados", db.lastError().text(),
                              QMessageBox::Cancel);
        qApp->exit(-1);
    }
    else
    {
        // seta o objeto modelo
        QSqlTableModel *model = new QSqlTableModel(this, db);

        // seta a tabela
        model->setTable("produto");

        ui->tableView->setModel(model);

        // seleciona os dados da tabela
        model->select();
        ModelProxy *proxy = new ModelProxy();
        proxy->setSourceModel(model);
        ui->tableView->setModel(proxy);

    }
}

Produto::~Produto()
{
    delete ui;
}

// Botão "Inserir"
void Produto::on_pushButton_2_clicked()
{
    if(ui->spinBox->text().isEmpty() || ui->lineEdit->text().isEmpty()
            || ui->doubleSpinBox->text().isEmpty())
        QMessageBox::warning(this, "Atenção", "Dados Inválidos!");
    else
    {
        QSqlQuery qry(db);
#define BIND_WITH_INDEX
#ifdef BIND_WITH_INDEX
        qry.prepare("INSERT INTO produto values(?, ?, ?)");
        qry.bindValue(0, ui->spinBox->value());
        qry.bindValue(1, ui->lineEdit->text());
        qry.bindValue(2, ui->doubleSpinBox->value());
#else
        qry.prepare("INSERT INTO produto values(:id, :nome, :salario)");
        qry.bindValue(":código", ui->spinBox->value());
        qry.bindValue(":produto", ui->lineEdit->text());
        qry.bindValue(":preço", ui->doubleSpinBox->value());
#endif
       if(qry.exec())
           QMessageBox::information(this, "Sucesso",
                                    "Query executado com sucesso!");
       else
           QMessageBox::warning(this, "Fracasso",
                                "Query fracassou:<br><b>" + qry.lastError().text());
    }

    qobject_cast<QSqlTableModel *>(qobject_cast<QIdentityProxyModel *>(ui->tableView->model())->sourceModel())->select();
}


// seta um ID aleatório
void Produto::on_pushButton_clicked()
{
    ui->spinBox->setValue(getRandomID());
}

// obtem um número aleatório de 1000 até 9999
unsigned int Produto::getRandomID() const
{
    static RandomEngine eng(std::time(nullptr));
    static Random rnd(1000, 9999);

    return rnd(eng);
}

void Produto::on_pushButton_3_clicked()
{
    qApp->quit();
}

void Produto::on_pushButton_4_clicked()
{
    qApp->aboutQt();
}

void Produto::on_pushButton_5_clicked()
{
    if(ui->spinBox->text().isEmpty())
        QMessageBox::warning(this, "Atenção", "Dados Inválidos!");
    else
    {
        QSqlQuery qry(db);
        qry.prepare("DELETE FROM produto WHERE código=?;");
        qry.bindValue(0, ui->spinBox->value());
        if(qry.exec())
            QMessageBox::information(this, "Sucesso",
                                     "Query executado com sucesso!");
        else
            QMessageBox::warning(this, "Fracasso",
                                 "Query fracassou:<br><b>" + qry.lastError().text());

         qobject_cast<QSqlTableModel *>(qobject_cast<QIdentityProxyModel *>(ui->tableView->model())->sourceModel())->select();
    }
}


void Produto::on_pushButton_6_clicked()
{
        QSqlQuery qry(db);
        qry.prepare("UPDATE produto set produto=?,preço=? WHERE código=?;");
        qry.bindValue(0, ui->lineEdit->text());
        qry.bindValue(1, ui->doubleSpinBox->value());
        qry.bindValue(2, ui->spinBox->value());

        if(qry.exec())
            QMessageBox::information(this, "Sucesso",
                                     "Query executado com sucesso!");
        else
            QMessageBox::warning(this, "Fracasso",
                                 "Query fracassou:<br><b>" + qry.lastError().text());
         qobject_cast<QSqlTableModel *>(qobject_cast<QIdentityProxyModel *>(ui->tableView->model())->sourceModel())->select();
}

void Produto::on_pushButton_7_clicked()
{
        ui->spinBox->text().clear();
        ui->lineEdit->text().clear();
        ui->doubleSpinBox->text().clear();

        QSqlQuery qry(db);
        qry.prepare("DELETE FROM produto;");

        if(qry.exec())
            QMessageBox::information(this, "Sucesso",
                                     "Query executado com sucesso!");
        else
            QMessageBox::warning(this, "Fracasso",
                                 "Query fracassou:<br><b>" + qry.lastError().text());

         qobject_cast<QSqlTableModel *>(qobject_cast<QIdentityProxyModel *>(ui->tableView->model())->sourceModel())->select();
}
