#include "mainwindow.h"
#include "appcontext.h"
#include "entrypoint.h"
#include "logic.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBoxSource->addItem("BIN", 2);
    ui->comboBoxSource->addItem("OCT", 8);
    ui->comboBoxSource->addItem("DEC", 10);
    ui->comboBoxTarget->addItem("BIN", 2);
    ui->comboBoxTarget->addItem("OCT", 8);
    ui->comboBoxTarget->addItem("DEC", 10);
    ui->pushButton->setText("Translate");

    connect(ui->comboBoxSource, &QComboBox::currentIndexChanged, this, &MainWindow::onSourceBaseChanged);
    connect(ui->comboBoxTarget, &QComboBox::currentIndexChanged, this, &MainWindow::onTargetBaseChanged);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onPushButtonClicked);

    ui->comboBoxSource->setCurrentIndex(0);
    ui->comboBoxTarget->setCurrentIndex(2);
    initialization();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialization() {
    executeOperation(INITIALIZATION, nullptr, &context);
}

void MainWindow::onSourceBaseChanged() {
    AppProperties props;
    props.selectedSystem = ui->comboBoxSource->currentData().toInt();
    executeOperation(SOURCE_BASE_CHANGED, &props, &context);
}

void MainWindow::onTargetBaseChanged() {
    AppProperties props;
    props.selectedSystem = ui->comboBoxTarget->currentData().toInt();
    executeOperation(TARGET_BASE_CHANGED, &props, &context);
}

void MainWindow::onPushButtonClicked()
{
    AppProperties props;
    props.userInput = ui->userInput->text();
    executeOperation(BUTTON_CLICKED, &props, &context);
    ui->output->setText(context.output);
    updateErrorDisplay();
}

void MainWindow::updateErrorDisplay()
{
    if (context.errorType != OK) {
        QString errorMessage;
        switch (context.errorType) {
        case NOT_ENTERED_TEXT:
            errorMessage = "The text is not entered!";
            break;
        case SYSTEM_NOT_SET:
            errorMessage = "The number system is not selected!";
            break;
        case INVALID_INPUT:
            errorMessage = "Invalid input!";
            break;
        case BIG_NUM:
            errorMessage = "The number is too high!";
            break;
        default:
            errorMessage = "Unknown error!";
            break;
        }
        QMessageBox::warning(this, "ERROR", errorMessage);
    }
}
