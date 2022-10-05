#pragma once
#include "EmojiPlayerItem.h"
#include <QGraphicsPixmapItem>
class EmojiScene;
class EmojiDecisionTree;
class AtkPointItem;
#include <vector>

class AIItem ://�ô�EmojiPlayerItem��̳е�AIItem����ʵ��AI
    public EmojiPlayerItem
{
    Q_OBJECT
public:
    AIItem(const QPixmap& pixmap,
        EmojiScene* parentScene, 
        EmojiPlayerItem* player,
        QGraphicsTextItem* label,
        QString name,
        QString picturePath,
        QGraphicsItem* parent = Q_NULLPTR);
    ~AIItem();

    void setPlayer(EmojiPlayerItem* player);
    EmojiPlayerItem* player();

    std::vector<int>& route();

public slots:   
    void traverseDecisionTree();//����������

protected:
    EmojiDecisionTree* mDecisionTree; 
    EmojiPlayerItem* mPlayer;
    QTimer* mAITimer; //AI���е�Timer,����ִ�о�����
    std::vector<int> mRoute;
};

