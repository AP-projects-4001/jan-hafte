#include "graphview.h"

GraphView::GraphView(QWidget *parent)
    : QGraphicsView{parent}
{
    scene = new QGraphicsScene(this);
    this->setScene(scene);
    scene->addPixmap(QPixmap(":/Graphics/Graphics/keanu.jpg"));
}
