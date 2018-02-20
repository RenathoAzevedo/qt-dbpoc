#ifndef PRODUTO_H
#define PRODUTO_H

#include <QtWidgets>
#include <QtSql>
#include <random>
#include <chrono>

// cria aliases para alguns nome
// o mesmo efeito de typedef, só que melhor,
// funciona em objetos e possibilita usar templates
using RandomEngine = std::default_random_engine;
using Random = std::uniform_int_distribution<int>;

namespace Ui {
class Produto;
}

class Produto : public QWidget
{
    Q_OBJECT

public:
    explicit Produto(QWidget *parent = 0);
    ~Produto();

    unsigned int getRandomID() const;
    QVariant data(const QModelIndex &index, int role) const;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();

private:
    Ui::Produto *ui;
    QSqlDatabase db;
};

#endif // PRODUTO_H
