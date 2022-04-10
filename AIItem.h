#pragma once
#include "EmojiPlayerItem.h"
#include <QGraphicsPixmapItem>
class EmojiScene;
class EmojiDecisionTree;
class AtkPointItem;

class AIItem ://�ô�EmojiPlayerItem��̳е�AIItem����ʵ��AI
    public EmojiPlayerItem
{
    Q_OBJECT
public:
    AIItem(const QPixmap& pixmap,
        EmojiScene* parentScene, 
        QGraphicsItem* parent = Q_NULLPTR);
    ~AIItem();

public slots:   
    void traverseDecisionTree();//����������

protected:
    EmojiDecisionTree* mDecisionTree;  
    QTimer* mAITimer; //AI���е�Timer,����ִ�о�����
};

