#pragma once
#include <QGraphicsScene>
#include <QTimer>
#include <QWidget>
class EmojiPlayerItem;
class AIItem;
class BackgroundItem;
class GroundItem;
class PlatformItem;
class QPropertyAnimation;
class AtkPointItem;
class EmojiMap;

class EmojiScene :
    public QGraphicsScene
{
    Q_OBJECT
    friend class EmojiView;
public:
    EmojiScene();
    virtual ~EmojiScene();

    EmojiMap* map();
    std::vector<PlatformItem*>& platforms();

protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

public:
        
    //��ͬ����µ���ײ���
	bool checkMoveCollision(EmojiPlayerItem* player);
    bool checkHitCollision(AtkPointItem* atkPoint);

    //�ø�ֵ��ʾ���������δ��ײ�κ���������
    enum {
        CHECK_COLLISION_FAILURE_HEIGHT = -100
    };

private:
    EmojiPlayerItem* mEmojiPlayer;
    AIItem* mAIPlayer;
    BackgroundItem* mBackground;
    EmojiMap* mMap;
    std::vector<PlatformItem*> mPlatforms;
};

