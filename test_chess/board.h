#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "chess.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);



    //绘制棋子,***QPainter& painter引用画家
    void drawChess(QPainter& painter,int id);

    //返回棋子中心的像素坐标
    QPoint centre(int row,int col);
    QPoint centre(int id);

    //判断鼠标是否点击棋子 此种方法效率不高
    bool getRowCol(QPoint pt,int &row,int &col);


    //重写虚函数：绘制窗口
    void paintEvent(QPaintEvent *event);

    //走棋规则实现
    bool canMove(int moveId,int row,int col,int killId);

    bool canMove_JIANG(int moveId,int row,int col,int killId);
    bool canMove_SHI(int moveId,int row,int col,int killId);
    bool canMove_XIANG(int moveId,int row,int col,int killId);
    bool canMove_MA(int moveId,int row,int col,int killId);
    bool canMove_PAO(int moveId,int row,int col,int killId);
    bool canMove_JU(int moveId,int row,int col,int killId);
    bool canMove_BING(int moveId,int row,int col,int killId);

    //鼠标点击实现走棋
    //void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:

public slots:

private:
    Chess _c[32];//32颗棋子
    int _r=20;//棋子半径
    int _d=40;//棋子直径

    //走棋
    int _selectId=-1;
    bool _redTurn=true;//下棋顺序
};

#endif // BOARD_H
