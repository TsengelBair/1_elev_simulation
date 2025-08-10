#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QScreen>
#include <QGraphicsRectItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, QApplication::primaryScreen()->geometry().width(), QApplication::primaryScreen()->geometry().height());

    setupBuilding();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupBuilding()
{
    const int floorHeight = 60;
    const int buildingWidth = 100;

    for (int i = 0; i < 9; i++) {
        /// Фон этажа
        QGraphicsRectItem *floor = scene->addRect(0, i * floorHeight, buildingWidth, floorHeight - 2);
        floor->setBrush(QBrush(QColor(240, 240, 240)));

        QGraphicsTextItem *label = scene->addText(QString::number(9 - i));
        label->setPos(10, i * floorHeight + 20);

        QGraphicsEllipseItem *button = scene->addEllipse(buildingWidth - 40, i * floorHeight + 15, 30, 30);
        button->setBrush(QBrush(Qt::red));

        /// Делаем кнопку кликабельной (при клике добавить смену цвета)
        button->setFlag(QGraphicsItem::ItemIsSelectable);
    }
}
