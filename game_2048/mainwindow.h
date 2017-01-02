#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void randGen();
    void rightRight();
    void leftLeft();
    void upUp();
    void downDown();
    void calVacancy();
    bool isWin();
    bool isLose();

private:
    std::vector<std::vector<int>> board;
    int vacancy;
};

#endif // MAINWINDOW_H
