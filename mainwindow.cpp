#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    xEllipse = 200;
    yEllipse = 100;
    aEllipse = 400; // ширина
    bEllipse = 230;
    xPoint = 400;
    yPoint = 400;

    std::pair<QPoint, QPoint> tmpPair;

    tmpPair.first.setX(xPoint);
    tmpPair.first.setY(yPoint);

    tmpPair.second.setX(xEllipse - aEllipse + 0.4);
    tmpPair.second.setY(getYEllipse(-aEllipse + 0.2 + 0.2,true) + yEllipse);
    minLine = tmpPair;
}

MainWindow::~MainWindow()
{}


void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    // Устанавливаем кисть абриса
    QPainter ptr(this);


    ptr.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    //for (int i = 0; i < pointsLines.size(); i++)
    //    ptr.drawLine(pointsLines[i].first, pointsLines[i].second);
    ptr.setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::FlatCap));
    ptr.drawLine(minLine.first, minLine.second);
    ptr.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap));

    //ptr.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    ptr.drawEllipse(xEllipse - aEllipse, yEllipse - bEllipse, aEllipse * 2, bEllipse * 2);
    ptr.setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::FlatCap));
    ptr.drawPoint(xPoint, yPoint);

}


void MainWindow::mouseMoveEvent(QMouseEvent* eventt)
{
    if (xEllipse - aEllipse < eventt->pos().x() && eventt->pos().x() < xEllipse + aEllipse &&
        yEllipse - bEllipse < eventt->pos().y() && eventt->pos().y() < yEllipse + bEllipse)
    {
        xEllipse = eventt->pos().x();
        yEllipse = eventt->pos().y();
    }
    else
    {
        xPoint = eventt->pos().x();
        yPoint = eventt->pos().y();
    }
    proc();

    update();
}

void MainWindow::mousePressEvent(QMouseEvent* eventt)
{

    if (xEllipse - aEllipse < eventt->pos().x() && eventt->pos().x() < xEllipse + aEllipse &&
        yEllipse - bEllipse < eventt->pos().y() && eventt->pos().y() < yEllipse + bEllipse)
    {
        xEllipse = eventt->pos().x();
        yEllipse = eventt->pos().y();
    }
    else
    {
        xPoint = eventt->pos().x();
        yPoint = eventt->pos().y();
    }
    proc();
    update();
}

void MainWindow::proc()
{
    double xBias = xEllipse - aEllipse;
    std::pair<QPoint, QPoint> tmpPair;

    tmpPair.first.setX(xPoint);
    tmpPair.first.setY(yPoint);

    tmpPair.second.setX(xEllipse - aEllipse + 0.4);
    tmpPair.second.setY(getYEllipse(-aEllipse + 0.2 + 0.2,true) + yEllipse);
    minLine = tmpPair;
    pointsLines.clear();
    for (double i = xEllipse - aEllipse; i < xEllipse + aEllipse; i += 0.1)
    {
        if (yPoint > yEllipse)
        {

        std::pair<QPoint, QPoint> tmpPair;

        tmpPair.first.setX(xPoint);
        tmpPair.first.setY(yPoint);

        tmpPair.second.setX(i);
        tmpPair.second.setY(getYEllipse(i - xBias - aEllipse, true) + yEllipse);


        if (getLenLine(minLine) > getLenLine(tmpPair))
            minLine = tmpPair;

        pointsLines.push_back(tmpPair);
        }
        else
        {


        std::pair<QPoint, QPoint> tmpPair1;

        tmpPair1.first.setX(xPoint);
        tmpPair1.first.setY(yPoint);

        tmpPair1.second.setX(i);
        tmpPair1.second.setY(getYEllipse(i - xBias - aEllipse, false) + yEllipse);

        if (getLenLine(minLine) > getLenLine(tmpPair1))
            minLine = tmpPair1;
        pointsLines.push_back(tmpPair1);
        }

    }

    update();

}

double MainWindow::getYEllipse(double x, bool isDown)
{
    double xLocal = x;
    double tmp1 = (pow(xLocal, 2) / pow(aEllipse, 2));
    double tmp2 = (1 - tmp1) * pow(bEllipse, 2);
    double tmp3 = sqrt(tmp2);
    if(isDown)
        return tmp3;
    else
        return -tmp3;
}

double MainWindow::getLenLine(std::pair<QPoint, QPoint> points)
{
    return sqrt(pow(abs(points.second.x()) - abs(points.first.x()), 2) + pow(abs(points.second.y()) - abs(points.first.y()), 2));
}