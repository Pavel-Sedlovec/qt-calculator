#include "mainwindow.h"
#include "core.h"

void MainWindow::OnClick()
{
    QPushButton *but = (QPushButton *) sender();
    QString str = m_lineEdit->text();
    str += but->text();
    m_lineEdit->setText(str);
}

void MainWindow::onClick_equally()
{
    try {
        std::vector<Token> vec = tokenize(m_lineEdit->text().toStdString());

        qDebug() << "Tokens size" << vec.size();
        for (int i = 0; i < vec.size(); i++) {
            qDebug() << vec[i].type << vec[i].value;
        }

        Parser parser(vec);
        double res = parser.parse();

        qDebug() << res;
        m_lineEdit->setText(QString::number(res));
    } catch (const std::runtime_error &error) {
        m_lineEdit->setText("Error: " + QString::fromStdString(error.what()));
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    counter = 0;
    m_widget = new QWidget();
    m_grid = new QGridLayout();
    m_widget->setLayout(m_grid);
    m_lineEdit = new QLineEdit();
    QRegularExpression rx("^[0-9,+\\-*/()]*$");

    QRegularExpressionValidator *validator = new QRegularExpressionValidator(rx, this);

    m_lineEdit->setValidator(validator);

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

    //connect(m_lineEdit, &QLineEdit::textChanged, m_num_1, &QPushButton::setText);

    connect(m_num_1, &QPushButton::clicked, this, &MainWindow::OnClick);
    connect(m_num_2, &QPushButton::clicked, this, &MainWindow::OnClick);
    connect(m_num_3, &QPushButton::clicked, this, &MainWindow::OnClick);
    connect(m_num_4, &QPushButton::clicked, this, &MainWindow::OnClick);
    connect(m_num_5, &QPushButton::clicked, this, &MainWindow::OnClick);
    connect(m_num_6, &QPushButton::clicked, this, &MainWindow::OnClick);
    connect(m_num_7, &QPushButton::clicked, this, &MainWindow::OnClick);
    connect(m_num_8, &QPushButton::clicked, this, &MainWindow::OnClick);
    connect(m_num_9, &QPushButton::clicked, this, &MainWindow::OnClick);
    connect(m_num_0, &QPushButton::clicked, this, &MainWindow::OnClick);

    connect(m_div, &QPushButton::clicked, this, &MainWindow::OnClick);
    connect(m_sum, &QPushButton::clicked, this, &MainWindow::OnClick);
    connect(m_minus, &QPushButton::clicked, this, &MainWindow::OnClick);
    connect(m_multiply, &QPushButton::clicked, this, &MainWindow::OnClick);
    connect(m_equally, &QPushButton::clicked, this, &MainWindow::onClick_equally);

    m_grid->addWidget(m_lineEdit, 0, 0, 1, 3);
    m_grid->addWidget(m_num_1, 1, 0);
    m_grid->addWidget(m_num_2, 1, 1);
    m_grid->addWidget(m_num_3, 1, 2);
    m_grid->addWidget(m_num_4, 2, 0);
    m_grid->addWidget(m_num_5, 2, 1);
    m_grid->addWidget(m_num_6, 2, 2);
    m_grid->addWidget(m_num_7, 3, 0);
    m_grid->addWidget(m_num_8, 3, 1);
    m_grid->addWidget(m_num_9, 3, 2);

    m_grid->addWidget(m_num_0, 4, 0, 1, 3);

    m_grid->addWidget(m_div, 1, 3);
    m_grid->addWidget(m_sum, 2, 3);
    m_grid->addWidget(m_minus, 3, 3);
    m_grid->addWidget(m_multiply, 4, 3);
    m_grid->addWidget(m_equally, 0, 3);

    this->setCentralWidget(m_widget);
}

MainWindow::~MainWindow() {}
