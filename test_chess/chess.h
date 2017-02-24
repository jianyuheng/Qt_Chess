#ifndef CHESS_H
#define CHESS_H

#include <QString>

class Chess
{
public:
    Chess();

    //枚举定义棋子类型
    enum TYPE{JIANG,BING,PAO,MA,SHI,XIANG,JU};

    //棋子的属性
    int _row;//行
    int _col;//列
    int _id;
    bool _dead=true;
    bool _red;
    TYPE _type;

    void initChess(int id)
    {
        _id=id;
        _dead=false;
        _red = id<16;//规定颜色

        struct {
                int row, col;
                TYPE type;
            } pos[16] = {
            {0, 0,JU},
            {0, 1,MA},
            {0, 2,XIANG},
            {0, 3,SHI},
            {0, 4,JIANG},
            {0, 5,SHI},
            {0, 6,XIANG},
            {0, 7,MA},
            {0, 8,JU},

            {2, 1,PAO},
            {2, 7,PAO},
            {3, 0,BING},
            {3, 2,BING},
            {3, 4,BING},
            {3, 6,BING},
            {3, 8,BING},
            };
        //上半部分棋子
        if(id<16)
        {
            _row=pos[id].row;
            _col=pos[id].col;
            _type=pos[id].type;
        }
        else
        {
            _row=9-pos[id-16].row;
            _col=8-pos[id-16].col;
            _type=pos[id-16].type;
        }
    }

    //获取棋子类型
    QString getText()
    {
        switch (this->_type) {
        case JU:
            return "車";
            break;
        case MA:
            return "马";
            break;
        case XIANG:
            return "象";
            break;
        case SHI:
            return "士";
            break;
        case PAO:
            return "炮";
            break;
        case BING:
            return "兵";
            break;
        case JIANG:
            return "将";
            break;
        default:
            return "false";
            break;
        }
    }


};

#endif // CHESS_H
