#pragma once
#include <QGraphicsPixmapItem>
class QPropertyAnimation;
class EmojiScene;
class QPropertyAnimation;
class QTimer;
class AtkPointItem;

class EmojiPlayerItem :
    public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    //��Property����ִ����Ծ����
    Q_PROPERTY(qreal jumpFactor
        READ jumpFactor
        WRITE setJumpFactor
        NOTIFY jumpFactorChanged)
    //��Property����ִ�����䶯��
    Q_PROPERTY(qreal downFactor
        READ downFactor
        WRITE setDownFactor
        NOTIFY downFactorChanged)
    //��Property����ִ�б����򶯻�
    Q_PROPERTY(qreal beHitFactor
        READ beHitFactor
        WRITE setBeHitFactor
        NOTIFY beHitFactorChanged)
public:
    EmojiPlayerItem(const QPixmap& pixmap,
        EmojiScene* parentScene,
        QGraphicsItem* parent = Q_NULLPTR);

    virtual void setJumpAnimation();
    virtual void setDownAnimation();
    virtual void setBeHitAnimation();

    QPropertyAnimation* jumpAnimation();
    QPropertyAnimation* downAnimation();
    QPropertyAnimation* beHitAnimation();

    QTimer* playerTimer();
    void checkTimer();//���ʱ��ȷ��ƽ�Ʒ���

    int direction()const;
    void setDirection(int direction);
    int lastDirction();//���ص�ǰ����

    virtual bool checkOutsideOfGameView();//����Ƿ����Ӷ���Ҫ����
    virtual void restoreLife();
    virtual int life()const;
    virtual void setLife();
    
    //����ϵ��,ϵ��Խ�߱����ԽԶ
    virtual int coefficient()const;
    virtual void restorecoefficient();
    virtual void addcoefficient();

    //���ø����
    void setStartPosX(qreal x);
    void setStartPosY(qreal y);
    qreal startPosX()const;
    qreal startPosY()const;

    //����ƽ�Ƶĺ���
    void addHorizontalInput(int input);
    void setHorizontalInput(int input);

    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);

    virtual void jump();
    virtual void beHit();

    void setBeHitDirection(int value);
    
    AtkPointItem* point();

public:
    //ͨ��factor�����ƶ���ִ�н���
    qreal jumpFactor()const;
    void setJumpFactor(const qreal &jumpFactor);

    qreal downFactor()const;
    void setDownFactor(const qreal& downFactor);

    qreal beHitFactor()const;
    void setBeHitFactor(const qreal& beHitFactor);

signals:
    void jumpFactorChanged(qreal);
    void downFactorChanged(qreal);
    void beHitFactorChanged(qreal);

public slots:
    void moveHorizontalEmojiPlayer();
    void moveDownEmojiPlayer();

protected:
    int mLastDirection;//ֻ������1����-1�ĳ���
    int mDirection;//��ɫ�ĳ���

    int mLife;//��ɫ����
    int mCoefficient;//Ӱ��ϵ��
    int mHorizontalInput;//��������

    qreal mJumpStartLevel;
    qreal mLastJumpValue;
    qreal mJumpHeight = 180;

    qreal mDownStartLevel;
    qreal mDownHeight = 180;

    qreal mBeHitStartLevel;
    qreal mLastBeHitValue;
    qreal mBeHitStartPos;
    qreal mBeHitHeight = 180;
    int mBeHitDirection;//���������ɵķ���

    qreal mStartPosX;
    qreal mStartPosY;//����������

    EmojiScene* mParentScene;
    AtkPointItem* mPoint;
    QTimer* mPlayerTimer;

    QPropertyAnimation* mJumpAnimation;
    QPropertyAnimation* mDownAnimation;
    QPropertyAnimation* mBeHitAnimation;

    qreal mJumpFactor;
    qreal mDownFactor;
    qreal mBeHitFactor;

    int mWorldSpeed = 5;
    int mFilter = 0;//������ʱû���ɿ�����,keyReleaseEvent�л���ɸ�������,
    //������Ҫ���˵�����֮ǰ�İ����ź�

    //������ֵ���ڽ������ʱͬʱ��סa��d����ɵ�����
    bool mAPressed = 0;
    bool mDPressed = 0;
};

