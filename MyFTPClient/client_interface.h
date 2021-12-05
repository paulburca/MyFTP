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

    void on_pushButton_clicked();//login

    void on_pushButton_2_clicked();//register

    void on_pushButton1_clicked();//transfer client-server

    void on_pushButton2_clicked();//tranfer server-client

    void on_pushButton3_clicked();//newfolder

    void on_pushButton4_clicked();//newfile

    void on_pushButton5_clicked();//delete

    void on_pushButton6_clicked();//cd

    void on_pushButton7_clicked();//back

private:
    Ui::Client_interface *ui;
    void displayTree();//algoritmul pentru modificare Treewidget-ului
    int sd=0;//id-ul socket-ului catre server
    char where[4096]="";//locatia actuala in server
};
#endif // CLIENT_INTERFACE_H
