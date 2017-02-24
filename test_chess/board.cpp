#include "board.h"
#include <QPainter>
#include <QMouseEvent>

Board::Board(QWidget *parent) : QWidget(parent)
{
    //给棋子初始化
    for(int i=0;i<32;++i)
    {
        //棋子的初始化函数
        _c[i].initChess(i);
    }
}

void Board::paintEvent(QPaintEvent *)
{
    //定义画家
    QPainter painter(this);

    int d=_d;
    //画线 10条横线
    for(int i=1;i<=10;++i)
    {
        painter.drawLine(QPoint(d,i*d),QPoint(8*d+d,i*d));
    }

    //9条竖线
    for(int i=1;i<=9;++i)
    {
        if(i==1||i==9)
        {
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,9*d+d));

        }
        else
        {
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
            painter.drawLine(QPoint(i*d,6*d),QPoint(i*d,9*d+d));
        }

    }

    //画格子
    painter.drawLine(QPoint(4*d,d),QPoint(6*d,3*d));
    painter.drawLine(QPoint(6*d,d),QPoint(4*d,3*d));
    painter.drawLine(QPoint(4*d,8*d),QPoint(6*d,10*d));
    painter.drawLine(QPoint(4*d,10*d),QPoint(6*d,8*d));

    //绘制32颗棋子
    for(int i=0;i<32;++i)
    {
        drawChess(painter,i);
    }



}

//返回棋子的行列
QPoint Board::centre(int id)
{
    return centre(_c[id]._row,_c[id]._col);
}


//返回棋子中心的像素坐标
QPoint Board::centre(int row, int col)
{
    QPoint ret;
    //QPoint rx(),ry()返回坐标的引用
    ret.rx()=col*_d+_d;
    ret.ry()=row*_d+_d;
    return ret;
}



//绘制棋子函数
void Board::drawChess(QPainter& painter,int id)
{
    if(_c[id]._dead)
            return;
    QPoint c=centre(id);
    //设置画刷背景色
    if(id==_selectId)
    {
        painter.setBrush(QBrush(Qt::gray));
    }
    else
    {
        painter.setBrush(QBrush(QColor(255,255,0)));
    }
    //设置黑色画笔
    painter.setPen(Qt::black);

    painter.drawEllipse(c,_r,_r);

    //规定绘制字的矩形区域
    QRect rect=QRect(c.rx()-_r,c.ry()-_r,_d,_d);

    //判断棋子颜色
    if(_c[id]._red)
    {
        painter.setPen(Qt::red);
    }
    else
    {
        painter.setPen(Qt::black);
    }

    //改变字体大小
    painter.setFont(QFont("Times",_r,1000));

    //第一个参数指在规定矩形区域中绘制
    //QTextOption(Qt::AlignCenter)：指定对齐方式
    painter.drawText(rect,_c[id].getText(),QTextOption(Qt::AlignCenter));//绘制字符串
}

//判断鼠标是否点击棋子 此种方法效率不高
bool Board::getRowCol(QPoint pt, int &row, int &col)
{
    for(row=0;row<=9;++row)
    {
        for(col=0;col<=8;col++)
        {
            QPoint c=centre(row,col);
            int dx=c.x()-pt.x();
            int dy=c.y()-pt.y();
            int dist=dx*dx+dy*dy;
            if(dist<_r*_r)
                return true;
        }
    }
    return false;
}

bool Board::canMove_JIANG(int moveId,int row,int col,int killId)
{
    //在九宫格内移动
    //移动步长为1
    //两个老将面对面
    if(_c[moveId]._red)
    {
        if(row>2) return false;
    }
    else
    {
        if(row<7) return false;
    }
    if(col<3||col>5)
    {
        return false;
    }

    int dr=_c[moveId]._row-row;
    int dc=_c[moveId]._col-col;

    //***************
    int d=abs(dr)*10+abs(dc);//判断步长
    if(d==1||d==10)
        return true;

    return true;
}

bool Board::canMove_SHI(int moveId,int row,int col,int killId)
{
    return true;
}

bool Board::canMove_XIANG(int moveId,int row,int col,int killId)
{
    return true;
}

bool Board::canMove_MA(int moveId,int row,int col,int killId)
{
    return true;
}

bool Board::canMove_PAO(int moveId,int row,int col,int killId)
{
    return true;
}

bool Board::canMove_JU(int moveId,int row,int col,int killId)
{
    return true;
}

bool Board::canMove_BING(int moveId,int row,int col,int killId)
{
    return true;
}

bool Board::canMove(int moveId, int row, int col, int killId)
{
    if(_c[moveId]._red==_c[killId]._red)
    {
        //换选择
        _selectId=killId;
        update();
        return false;
    }
    switch(_c[moveId]._type)
    {
    case Chess::JIANG:
        return canMove_JIANG(moveId,row,col,killId);
        break;
    case Chess::SHI:
        return canMove_SHI(moveId,row,col,killId);
        break;
    case Chess::XIANG:
        return canMove_XIANG(moveId,row,col,killId);
        break;
    case Chess::JU:
        return canMove_JU(moveId,row,col,killId);
        break;
    case Chess::MA:
        return canMove_MA(moveId,row,col,killId);
        break;
    case Chess::BING:
        return canMove_BING(moveId,row,col,killId);
        break;
    case Chess::PAO:
        return canMove_PAO(moveId,row,col,killId);
        break;

    }

    return true;

}

void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt=ev->pos();//获取鼠标点击位置
    //判断鼠标是否点击棋子
    //将pt转化位棋子的行列值，判断行列值上是否有棋子

    //鼠标点击位置所属的列和行
    int row,col;

    //判断点击位置
    bool bRet=getRowCol(pt,row,col);
    if(bRet==false)
    {
        return;//点到棋盘外或非棋子
    }


    int i=0;
    int clickId=-1;//当前单击位置
    for(;i<32;i++)
    {
        if(_c[i]._row==row&&_c[i]._col==col&&_c[i]._dead==false)
        {
             break;
        }

    }

    if(i<32)
    {
        clickId=i;
    }

    //需要判断是否已经选择过棋子
    //若没有选择过棋子，那么选择棋子
    //若选择了棋子，那么可以走棋或者选择其他棋子
    if(_selectId==-1)
    {
        if(clickId!=-1)
        {
            _selectId=clickId;
            update();
        }
    }
    else//若已经选择了棋子，选择移动棋子
    {
        if(canMove(_selectId,row,col,clickId))
        {//走棋
            _c[_selectId]._row=row;
            _c[_selectId]._col=col;
            if(clickId!=-1)
            {
                _c[clickId]._dead=true;
            }
            _selectId=-1;
            update();
        }
    }

}

