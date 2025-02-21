#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

#include "qmouseeventtransition.h"
#include "qpainter.h"
#include <QMouseEvent>
#include <vector>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass ui;
    
    

    std::vector<std::pair<QPoint, QPoint>> pointsLines;
    std::pair<QPoint, QPoint> line;
    std::pair<QPoint, QPoint> minLine;

    int xEllipse;
    int yEllipse;
    int aEllipse;
    int bEllipse;

    int xPoint;
    int yPoint;

    double getYEllipse(double x, bool isDown);
    double getLenLine(std::pair<QPoint, QPoint> points);

public slots:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* eventt);
    void mousePressEvent(QMouseEvent* eventt);

    void proc();
};
