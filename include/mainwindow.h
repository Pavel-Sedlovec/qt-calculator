#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QObject>
#include <QtWidgets>
#include "qcustomplot.h"
#include "core.h"
#include "controller.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int counter;
    std::vector<std::string> vec_history;
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

    QPushButton *m_sin;
    QPushButton *m_cos;
    QPushButton *m_tan;
    QPushButton *m_log;
    QPushButton *m_ln;
    QPushButton *m_sqrt;
    QPushButton *m_fact;
    QPushButton *m_var_x;
    QPushButton *m_dot;
    QPushButton *m_clear;
    QPushButton *m_history;
    QPushButton *m_parens;


    QLineEdit *m_lineEdit;
    QCustomPlot *m_plot;
    MainWindow(QWidget *parent = nullptr);
    Controller *m_controller;

    void OnClick();
    void onClick_equally();
    void showHistoryMenu();
    void calculateResult();


    ~MainWindow();
};
#endif // MAINWINDOW_H
