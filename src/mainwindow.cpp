#include "mainwindow.h"
#include "core.h"
#include "controller.h"

void MainWindow::OnClick()
{
    QPushButton *but = (QPushButton *) sender();
    QString btnText = but->text();
    QString currentText = m_lineEdit->text();

    if (btnText == "=") {
        calculateResult();
        return;
    }

    if (btnText == "C") {
        m_lineEdit->clear();
        return;
    }

    if (btnText == "sin()" || btnText == "cos()" || btnText == "tan()" ||
        btnText == "log()" || btnText == "ln()"  || btnText == "sqrt()" || btnText == "()")
    {
        m_lineEdit->insert(btnText);

        m_lineEdit->setCursorPosition(m_lineEdit->cursorPosition() - 1);

        return;
    }

    m_lineEdit->insert(btnText);
}

void MainWindow::calculateResult()
{

    std::string expression = m_lineEdit->text().toStdString();

    CalcRes res = m_controller->processExpression(expression);

    if (!res.isSuccess) {
        m_lineEdit->setText("Error: " + res.errorMessage);
        vec_history.push_back(expression+" = "+res.errorMessage.toStdString());
        return;
    }

    if (res.isGraph) {
        m_plot->clearGraphs();

        m_plot->addGraph();
        m_plot->graph(0)->setData(res.xData, res.yData);

        m_plot->rescaleAxes();
        m_plot->replot();

        m_lineEdit->setText("График построен");
        vec_history.push_back(expression + " -- График построен");
    }
    else {
        m_lineEdit->setText(QString::number(res.result));
        vec_history.push_back(expression + " = " + std::to_string(res.result));
    }
}

void MainWindow::showHistoryMenu(){
    QMenu *menu = (QMenu *) sender();

    menu->clear();
    if(vec_history.empty()){
        QAction *action = menu->addAction("История пуста");
        return;
    }
    for (int i = vec_history.size() - 1; i >= 0; --i) {
        QString historyItem = QString::fromStdString(vec_history[i]);
        QAction *action = menu->addAction(historyItem);
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    counter = 0;
    m_controller = new Controller();
    m_widget = new QWidget();
    m_grid = new QGridLayout();
    m_widget->setLayout(m_grid);

    m_grid->setSpacing(6);
    m_grid->setContentsMargins(10, 10, 10, 10);

    m_lineEdit = new QLineEdit();

    QFont lineEditFont = m_lineEdit->font();
    lineEditFont.setPointSize(18);
    m_lineEdit->setFont(lineEditFont);
    m_lineEdit->setAlignment(Qt::AlignRight);
    m_lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QMenuBar *menuBar = this->menuBar();
    QMenu *historyMenu = menuBar->addMenu("История");

    connect(historyMenu, &QMenu::aboutToShow, this, &MainWindow::showHistoryMenu);

    // QRegularExpression rx("^[0-9.+\\-*/()]*$");

    // QRegularExpressionValidator *validator = new QRegularExpressionValidator(rx, this);

    // m_lineEdit->setValidator(validator);

    m_num_1 = new QPushButton("1");
    m_num_2 = new QPushButton("2");
    m_num_3 = new QPushButton("3");
    m_num_4 = new QPushButton("4");
    m_num_5 = new QPushButton("5");
    m_num_6 = new QPushButton("6");
    m_num_7 = new QPushButton("7");
    m_num_8 = new QPushButton("8");
    m_num_9 = new QPushButton("9");
    m_num_0 = new QPushButton("0");

    m_div = new QPushButton("/");
    m_sum = new QPushButton("+");
    m_minus = new QPushButton("-");
    m_multiply = new QPushButton("*");
    m_equally = new QPushButton("=");

    m_sin = new QPushButton("sin()");
    m_cos = new QPushButton("cos()");
    m_tan = new QPushButton("tan()");
    m_log = new QPushButton("log()");
    m_ln = new QPushButton("ln()");
    m_sqrt = new QPushButton("sqrt()");
    m_fact = new QPushButton("!");
    m_var_x = new QPushButton("x");
    m_dot = new QPushButton(".");
    m_clear = new QPushButton("C");
    m_history = new QPushButton("H");
    m_parens = new QPushButton("()");

    QList<QPushButton*> allButtons = {
        m_num_1, m_num_2, m_num_3, m_num_4, m_num_5, m_num_6, m_num_7, m_num_8, m_num_9, m_num_0,
        m_div, m_sum, m_minus, m_multiply, m_equally,
        m_sin, m_cos, m_tan, m_log, m_ln, m_sqrt, m_fact, m_var_x, m_dot, m_clear, m_history,m_parens
    };

    QFont btnFont = m_num_1->font();
    btnFont.setPointSize(11);

    for (QPushButton* btn : allButtons) {
        btn->setFont(btnFont);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btn->setFocusPolicy(Qt::NoFocus);

        connect(btn, &QPushButton::clicked, this, &MainWindow::OnClick);
    }

    m_plot = new QCustomPlot();
    m_plot->addGraph();
    m_plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //connect(m_lineEdit, &QLineEdit::textChanged, m_num_1, &QPushButton::setText);

    m_grid->addWidget(m_lineEdit, 0, 0, 1, 6);

    m_grid->addWidget(m_sin,   1, 0);
    m_grid->addWidget(m_cos,   1, 1);
    m_grid->addWidget(m_tan,   1, 2);
    m_grid->addWidget(m_log,   1, 3);
    m_grid->addWidget(m_ln,    1, 4);
    m_grid->addWidget(m_sqrt,  1, 5);

    m_grid->addWidget(m_num_7, 2, 0);
    m_grid->addWidget(m_num_8, 2, 1);
    m_grid->addWidget(m_num_9, 2, 2);
    m_grid->addWidget(m_div,   2, 3);
    m_grid->addWidget(m_clear, 2, 4);
    m_grid->addWidget(m_history, 2, 5);

    m_grid->addWidget(m_num_4, 3, 0);
    m_grid->addWidget(m_num_5, 3, 1);
    m_grid->addWidget(m_num_6, 3, 2);
    m_grid->addWidget(m_multiply, 3, 3);
    m_grid->addWidget(m_parens, 3, 4);
    m_grid->addWidget(m_fact,  3, 5);

    m_grid->addWidget(m_num_1, 4, 0);
    m_grid->addWidget(m_num_2, 4, 1);
    m_grid->addWidget(m_num_3, 4, 2);
    m_grid->addWidget(m_minus, 4, 3);
    m_grid->addWidget(m_var_x, 4, 4);
    m_grid->addWidget(m_dot,   4, 5);

    m_grid->addWidget(m_num_0, 5, 0, 1, 2);
    m_grid->addWidget(m_sum,   5, 2, 1, 2);
    m_grid->addWidget(m_equally, 5, 4, 1, 2);

    m_grid->addWidget(m_plot, 0, 6, 6, 1);

    m_grid->setColumnStretch(6, 1);

    for(int i = 0; i < 6; ++i) {
        m_grid->setColumnStretch(i, 1);
    }

    m_grid->setColumnStretch(6, 5);

    m_grid->setRowStretch(0, 2);
    m_grid->setRowStretch(1, 1);
    for(int i = 2; i <= 5; ++i) {
        m_grid->setRowStretch(i, 1);
    }

    this->setCentralWidget(m_widget);
    this->resize(950, 550);

    connect(m_lineEdit, &QLineEdit::returnPressed, this, &MainWindow::calculateResult);

}

MainWindow::~MainWindow() {}
