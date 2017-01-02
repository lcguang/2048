#include "mainwindow.h"
#include <QMessageBox>
#include <time.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    resize(200, 200);
    board.resize(4, std::vector<int>(4, 0));
    vacancy = 16;
}

MainWindow::~MainWindow() {

}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    int i, j;
    for (i = 0; i < 5; i++) {
        p.drawLine(20, 20 + i * 40, 180, 20 + i * 40);
        p.drawLine(20 + i * 40, 20, 20 + i * 40, 180);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (board[i][j] != 0) {
                std::string num = std::to_string(board[i][j]);
                QString q_num(num.c_str());
                brush.setColor(Qt::white);
                p.setBrush(brush);
                p.drawText((j + 1) * 40 - 15, (i + 1) * 40 - 10, 40, 40, 0, q_num);
            }
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *q_key) {
    if (q_key->key() == Qt::Key_Right) {
        rightRight();
        randGen();
    } else if (q_key->key() == Qt::Key_Left) {
        leftLeft();
        randGen();
    } else if (q_key->key() == Qt::Key_Up) {
        upUp();
        randGen();
    } else if (q_key->key() == Qt::Key_Down) {
        downDown();
        randGen();
    }
    if (isWin()) {
        update();
        setEnabled(false);
        QMessageBox::information(this, "Win", "Win", QMessageBox::Ok);
    }
    if (isLose()) {
        update();
        setEnabled(false);
        QMessageBox::information(this, "Lose", "Lose", QMessageBox::Ok);
    }
    update();
}

void MainWindow::randGen() {
    if (vacancy > 0) {
        srand(time(NULL));
        int pos = rand() % 16;
        while (true) {
            if (board[pos / 4][pos % 4] == 0) {
                board[pos / 4][pos % 4] = 2;
                break;
            }
            pos = (pos + 1) % 16;
        }
    }
}

void MainWindow::rightRight() {
    for (int i = 0; i < 4; i++) {
        // locate the first non-zero element
        int pre = 0, pos = 0;
        for (int j = 3; j >= 0; j--) {
            if (board[i][j] != 0) {
                pre = board[i][j];
                pos = j;
                break;
            }
        }
        // add the adjacent elements with same value and combine them to one
        for (int j = pos - 1; j >= 0; j--) {
            if (board[i][j] == 0) continue;
            else if (board[i][j] == pre) {
                board[i][pos] = pre * 2;
                board[i][j] = 0;
            } else {
                pre = board[i][j];
                pos = j;
            }
        }
        // push all the elements to the right
        int k = 3;
        for (int j = 3; j >= 0; j--) {
            if (board[i][j] != 0) {
                int temp = board[i][j];
                board[i][j] = 0;
                board[i][k--] = temp;
            }
        }
    }
    calVacancy();
}

void MainWindow::leftLeft() {
    for (int i = 0; i < 4; i++) {
        int pre = 0, pos = 0;
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0) {
                pre = board[i][j];
                pos = j;
                break;
            }
        }
        for (int j = pos + 1; j < 4; j++) {
            if (board[i][j] == 0) continue;
            else if (board[i][j] == pre) {
                board[i][pos] = pre * 2;
                board[i][j] = 0;
            } else {
                pre = board[i][j];
                pos = j;
            }
        }
        int k = 0;
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0) {
                int temp = board[i][j];
                board[i][j] = 0;
                board[i][k++] = temp;
            }
        }
    }
    calVacancy();
}

void MainWindow::upUp() {
    for (int j = 0; j < 4; j++) {
        int pre = 0, pos = 0;
        for (int i = 0; i < 4; i++) {
            if (board[i][j] != 0) {
                pre = board[i][j];
                pos = i;
                break;
            }
        }
        for (int i = pos + 1; i < 4; i++) {
            if (board[i][j] == 0) continue;
            else if (board[i][j] == pre) {
                board[pos][j] = pre * 2;
                board[i][j] = 0;
            } else {
                pre = board[i][j];
                pos = i;
            }
        }
        int k = 0;
        for (int i = 0; i < 4; i++) {
            if (board[i][j] != 0) {
                int temp = board[i][j];
                board[i][j] = 0;
                board[k++][j] = temp;
            }
        }
    }
    calVacancy();
}

void MainWindow::downDown() {
    for (int j = 0; j < 4; j++) {
        int pre = 0, pos = 0;
        for (int i = 3; i >= 0; i--) {
            if (board[i][j] != 0) {
                pre = board[i][j];
                pos = i;
                break;
            }
        }
        for (int i = pos - 1; i >= 0; i--) {
            if (board[i][j] == 0) continue;
            else if (board[i][j] == pre) {
                board[pos][j] = pre * 2;
                board[i][j] = 0;
            } else {
                pre = board[i][j];
                pos = i;
            }
        }
        int k = 3;
        for (int i = 3; i >= 0; i--) {
            if (board[i][j] != 0) {
                int temp = board[i][j];
                board[i][j] = 0;
                board[k--][j] = temp;
            }
        }
    }
    calVacancy();
}

void MainWindow::calVacancy() {
    int temp = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) temp++;
        }
    }
    vacancy = temp;
}

bool MainWindow::isWin() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 2048) return true;
        }
    }
    return false;
}

bool MainWindow::isLose() {
    calVacancy();
    if (vacancy > 0) return false;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            if (board[i][j] == board[i][j - 1]) return false;
        }
    }
    for (int j = 0; j < 4; j++) {
        for (int i = 1; i < 4; i++) {
            if (board[i][j] == board[i - 1][j]) return false;
        }
    }
    return true;
}
