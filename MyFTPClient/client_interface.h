#ifndef CLIENT_INTERFACE_H
#define CLIENT_INTERFACE_H

#include <QMainWindow>
#include <QTreeWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class Client_interface; }
QT_END_NAMESPACE

class Client_interface : public QMainWindow
{
    Q_OBJECT

public:
    Client_interface(QWidget *parent = nullptr);
    ~Client_interface();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_2_itemClicked(QTreeWidgetItem *item, int column);

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::Client_interface *ui;
    void displayTree(QString username);
    int sd=0;
};
#endif // CLIENT_INTERFACE_H
