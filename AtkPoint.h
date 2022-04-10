#pragma once
#include <QGraphicsPixmapItem>
class EmojiPlayerItem;
class AIItem;
class QPropertyAnimation;
class EmojiScene;
class QTimer;

class AtkPointItem :
    public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    //��Property����ʵ�ֻ��򶯻�
    Q_PROPERTY(qreal hitFactor
        READ hitFactor
        WRITE setHitFactor
        NOTIFY hitFactorChanged)
    
    friend EmojiPlayerItem;
    friend AIItem;

public:
    AtkPointItem(const QPixmap& pixmap, EmojiPlayerItem* player,
        EmojiScene* parentScene,
        QGraphicsItem* parent = Q_NULLPTR);

    void setHitAnimation();
    QPropertyAnimation* hitAnimation();

    //������ʵ�����ڽ�ɫ��ƫ����
    qreal offsetX();
    qreal offsetY();

    void setOffsetX(qreal x);
    void setOffsetY(qreal y);

    EmojiPlayerItem* player();
    QTimer* hitTimer();

public:
    //������������Ϊ���򶯻���ʵ�ֺ���
    qreal hitFactor()const;
    void setHitFactor(const qreal& hitFactor);
    void hit();

signals:
    void hitFactorChanged(qreal);

public slots: 
    void checkHit();//ʱ����ͣʱ����Ƿ񱻻������������򶯻�

protected:
    EmojiPlayerItem* mPlayer;//��¼�û��������������볡��
    EmojiScene* mParentScene;

    qreal mOffsetX;
    qreal mOffsetY;

    QPropertyAnimation* mHitAnimation;
    QTimer* mHitTimer;
    int mHitHeight = 100;//����߶�

    qreal mHitFactor;
};