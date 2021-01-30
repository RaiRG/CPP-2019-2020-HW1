#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
Изменить публичный интерфейс класса User так, чтобы можно было

добавлять студентов
удалять студентов по индексу
удалять из списка студента по имени, если он там есть; если нет, то ничего не делать
получать их кол-во
*/

class User{
    int age; // private
    QString name; //private
    static int total_count;
public:
    explicit User(QString name, int age=18){
        if(age>=18){
            this->age=age;
        }else{
            this->age=18;
        }
        this->name=name;
        total_count++;
    }
    QString getName(){
        return name;
    }
    int getAge(){
        return age;
    }
    static int getTotalCount(){
        return total_count;
    }
    static std::vector<User> users_;
    void addStudent(User newStudent)
    {
        users_.push_back(newStudent);
    }
    void delteStudentByNumber(int number)
    {
        users_.erase(users_.begin()+number);
    }
    void deleteStudentByName(QString name)
    {
        for (int i =0; i<(int)users_.size(); i++)
        {
            if (users_[i].name == name)
                users_.erase(users_.begin()+i);

        }
    }
    int getNumberOfStudent()
    {
        return (int)users_.size();
    }
};

int User::total_count = 0;
std::vector<User> User::users_;

void MainWindow::on_submitPushButton_clicked()
{
    qDebug() << "User clicked on submit button";
    // ui->nameLineEdit->setText("Aufar");
    User student(ui->nameLineEdit->text(), ui->ageLineEdit->text().toInt());

    QMessageBox msg(QMessageBox::Information,"New student arrived!",
                    "Hello "+ student.getName() + "!");
    // qDebug() << "Name:" << student.getName();
    // qDebug() << "Age:" << student.getAge();
    qDebug() << msg.exec();
    qDebug() << User::getTotalCount();
    User::users_.push_back(student);
    //qDebug() << "Last student age:" << User::users_.end()->getAge();
    //qDebug() << "Last student name:" << User::users_.end()->getName();
    qDebug() << "Total count:" << User::users_.size();
    qDebug() << "First student name ([0]):" << User::users_[0].getName();
    qDebug() << "First student name (at):" << User::users_.at(0).getName();
    qDebug() << "------------------------";
}
