#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QScreen>
#include <QGraphicsRectItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, QApplication::primaryScreen()->geometry().width(), QApplication::primaryScreen()->geometry().height());

    setupBuilding();
    setupElevator();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::floorSelected(int floorNumber)
{
    qDebug() << "Нажата кнопка этажа:" << floorNumber;

    for (QGraphicsItem* item : scene->items()) {
        if (QGraphicsEllipseItem* button = dynamic_cast<QGraphicsEllipseItem*>(item)) {
            if (button->data(0).toInt() == floorNumber) {
                button->setBrush(QBrush(Qt::green));
                break;
            }
        }
    }
}


void MainWindow::setupBuilding()
{
    const int floorHeight = 60;
    const int floorWidth = 100;

    for (int i = 0; i < 9; i++) {
        /// Фон этажа
        QGraphicsRectItem *floor = scene->addRect(0, i * floorHeight, floorWidth, floorHeight - 2);
        floor->setBrush(QBrush(QColor(240, 240, 240)));

        QGraphicsTextItem *label = scene->addText(QString::number(9 - i));
        label->setPos(10, i * floorHeight + 20);

        QGraphicsEllipseItem *button = scene->addEllipse(floorWidth - 40, i * floorHeight + 15, 30, 30);
        button->setBrush(QBrush(Qt::red));

        button->setData(0, 9 - i);

        /// Делаем кнопку кликабельной (при клике добавить смену цвета)
        button->setFlag(QGraphicsItem::ItemIsSelectable);

        connect(scene, &QGraphicsScene::selectionChanged, this, [this, button]() {
            if (button->isSelected()) {
                floorSelected(button->data(0).toInt());
            }
        });
    }
}

void MainWindow::setupElevator()
{
    const int floorHeight = 60;
    const int elevatorWidth = 40;
    const int floorWidth = 100;

    /// Позиция лифта - правее здания (buildingWidth + отступ) и на уровне первого этажа
    const int elevatorX = floorWidth + 20;
    const int elevatorY = 8 * floorHeight;

    QGraphicsRectItem *elevator = scene->addRect(elevatorX, elevatorY, elevatorWidth, floorHeight - 2);
    elevator->setBrush(QBrush(Qt::blue));
}
