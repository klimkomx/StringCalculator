#include "mainwindow.h"

#include <stdio.h>
#include <utility>
#include <QScrollArea>
#include <QGridLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QTableWidget>
#include <QPair>
#include <QWidget>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QStringList>
#include <QTableWidgetItem>
#include <QVector>
#include <QColor>
#include <QHeaderView>
#include <QDebug>
#include <QCoreApplication>
#include <QMessageBox>
#include <QFileDialog>
#include<QDebug>
#include <string>

#include "sortst.h"
#include "map.h"

QTableWidget *table;
QTextEdit *inputString, *outputString, *polis;
QPushButton *calculate, *chooseFile;
QString expression;
bool isSet, addingValues;

double calculationResult;
string perem[100000];
string polishNotation;
int perem_size;
bool ODZ;
map<std::string, double> mperem;
queue<string> q1;

void reset() {
    polishNotation.clear();
    mperem.clear();
    perem_size = 0;
    inputString->clear();
    outputString->clear();
    polis->clear();
    addingValues = 0;
    return;
}
void resetAlmostAll() {
       polishNotation.clear();
       mperem.clear();
       perem_size = 0;
       outputString->clear();
       polis->clear();
       table->clear();
       addingValues = 0;
       ODZ = 0;
       return;
}

void table_update() {
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels(QStringList(""));
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setRowCount(perem_size);
    for (int i = 0; i < perem_size; i++) {
        QTableWidgetItem* it = new QTableWidgetItem();
        it->setText(QString::fromStdString(perem[i]));
        it->setFlags(Qt::ItemIsEnabled);
        table->setItem(i, 0, it);

        QTableWidgetItem* it2 = new QTableWidgetItem();
        table->setItem(i, 1, it2);
    }
    return;
}

void generateWarning(QString q) {
    QMessageBox w;
    w.setIcon(QMessageBox::Warning);
    w.setText(q);
    w.exec();
    return;
}

bool getTableElements() {
    for (int i = 0; i < perem_size; i++) {
        QString a = table -> item(i, 1) -> text();
        bool good;
        double value = a.toDouble(&good);
        if (!good) {
            generateWarning("Please, add variables (double only)");
            return 0;
        }
        else {
            mperem[table -> item(i, 0) -> text().toStdString()] = value;
        }
    }
    return 1;
}


void MainWindow::openFile() {
    QString filePath = QFileDialog::getOpenFileName(nullptr,"Choose Your data", "", "*.txt");
    if (filePath == "") return;
    QFile file(filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        inputString->setText(file.readLine());
        file.close();
    } else {
        generateWarning("Error : file path don't exist.");
    }
    return;
}

void MainWindow::calculationProcess() {
    if (addingValues == 1) {
        if (getTableElements()) {
            if (!calc())
                outputString -> setText(QString::number(calculationResult));
            else
                generateWarning("Function's value are not correct");
            addingValues = 0;
            return;
        }
        return;
    }
    resetAlmostAll();

    QString calculationString = inputString -> toPlainText();
    if (calculationString == "") {
        generateWarning("Error : expression can't be empty");
    }
    string expression = inputString->toPlainText().toStdString();
    expression.append("=");
    bool notOk = solve(expression);
    if (notOk) {
        generateWarning("Something wrong with input expression...");
        resetAlmostAll();
        return;
    }
    polis -> setText(QString::fromStdString(polishNotation));
    if (perem_size != 0) {
        table_update();
        addingValues = 1;
    }
    else {

        if (!calc())
            outputString -> setText(QString::number(calculationResult));
        else
            generateWarning("Function's value are not correct");
       return;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    this -> setCentralWidget(centralWidget);
    this -> setStyleSheet("background-color : rgb(80, 80, 80);");
    QGridLayout *layout = new QGridLayout(this);
    table = new QTableWidget();
    table ->setStyleSheet("background-color : rgb(180, 180, 180);"
                          "border-style : outset;"
                          "border-radius : 10px;"
                          "border-width : 2px;"
                          "border-color : beige;"
                          "font : 15px;"
                          "color : beige;");
    inputString = new QTextEdit();
    inputString -> setStyleSheet("background-color : rgb(180, 180, 180);"
                                 "border-style : outset;"
                                 "border-radius : 20px;"
                                 "border-width : 2px;"
                                 "border-color : beige;"
                                 "font : 25px;"
                                 "color : beige;"
                                 "min-height : 5em");
    outputString = new QTextEdit();
    outputString -> setStyleSheet("background-color : rgb(230, 180, 180);"
                                 "border-style : outset;"
                                 "border-radius : 20px;"
                                 "border-width : 2px;"
                                 "border-color : beige;"
                                 "font : 25px;"
                                 "color : beige;");

    inputString -> setPlaceholderText("Place your expression here");
    outputString -> setPlaceholderText("There will be result");
    polis = new QTextEdit();
    polis -> setPlaceholderText("There will be Polish notation");
    polis -> setStyleSheet("background-color : rgb(230, 180, 180);"
                                 "border-style : outset;"
                                 "border-radius : 20px;"
                                 "border-width : 2px;"
                                 "border-color : beige;"
                                 "font : 25px;"
                                 "color : beige");
    polis -> setReadOnly(1);
    calculate = new QPushButton();
    calculate -> setStyleSheet("QPushButton {background-color : orange; font : 20px; color : beige; border-style : outset; min-width : 10em; min-height : 5em; border-radius:20px}"
                               "QPushButton:hover{background-color : rgb(255, 204, 153); font : 20px; color : beige;}");
    calculate -> setText(QString("Calculate"));
    chooseFile = new QPushButton();
    chooseFile -> setStyleSheet("QPushButton {background-color : orange; font : 20px; color : beige; border-style : outset; min-width : 10em; min-height : 5em; border-radius:20px}"
                                "QPushButton:hover{background-color : rgb(255, 204, 153); font : 20px; color : beige;}");
    chooseFile -> setText(QString("Upload via file"));
    QObject :: connect(chooseFile, SIGNAL(clicked()), this, SLOT(openFile()));
    QObject :: connect(calculate, SIGNAL(clicked()), this, SLOT(calculationProcess()));
    outputString -> setReadOnly(1);

    layout -> addWidget(inputString, 0, 0, 1, 1);

    layout -> addWidget(chooseFile, 0, 3, 1, 1);
    layout -> addWidget(polis, 2, 0, 1, 2);
    layout -> addWidget(outputString, 3, 0, 1, 2);
    layout -> addWidget(calculate, 1, 3, 1, 1);
    layout -> addWidget(table, 0, 4, 4, 1);
    layout -> setColumnStretch(0, 10);

    this->centralWidget()->setLayout(layout);
}

MainWindow::~MainWindow()
{

}
