#ifndef ADVBOARDMAIN_H
#define ADVBOARDMAIN_H

#include <QMainWindow>

namespace Ui {
class AdvBoardMain;
}

class AdvBoardMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdvBoardMain(QWidget *parent = 0);
    ~AdvBoardMain();

private:
    Ui::AdvBoardMain *ui;
};

#endif // ADVBOARDMAIN_H
