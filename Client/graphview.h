#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QWidget>
#include <QGraphicsView>

class GraphView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphView(QWidget *parent = nullptr);

signals:

private:
    QGraphicsScene *scene;

};

#endif // GRAPHVIEW_H
