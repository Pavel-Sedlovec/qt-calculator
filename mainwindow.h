#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QObject>
#include <QtWidgets>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int counter;
    QWidget *m_widget;
    QGridLayout *m_grid;
    QPushButton *m_num_1;
    QPushButton *m_num_2;
    QPushButton *m_num_3;
    QPushButton *m_num_4;
    QPushButton *m_num_5;
    QPushButton *m_num_6;
    QPushButton *m_num_7;
    QPushButton *m_num_8;
    QPushButton *m_num_9;
    QPushButton *m_num_0;

    QPushButton *m_div;
    QPushButton *m_sum;
    QPushButton *m_minus;
    QPushButton *m_multiply;
    QPushButton *m_equally;

    QLineEdit *m_lineEdit;
    MainWindow(QWidget *parent = nullptr);

    void OnClick();
    void onClick_equally();

    ~MainWindow();
};
#endif // MAINWINDOW_H
