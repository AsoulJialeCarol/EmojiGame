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
    
    //��Property����ִ�����߶���
    Q_PROPERTY(qreal walkFactor
        READ walkFactor
        WRITE setWalkFactor
        NOTIFY walkFactorChanged)
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

    virtual void setWalkAnimation();
    virtual void setJumpAnimation();
    virtual void setDownAnimation();
    virtual void setBeHitAnimation();

    QPropertyAnimation* walkAnimation();
    QPropertyAnimation* jumpAnimation();
    QPropertyAnimation* downAnimation();
    QPropertyAnimation* beHitAnimation();

    void stopAnimations();

    EmojiScene* scene();

    QTimer* playerTimer();
    void checkTimer();//���ʱ��ȷ��ƽ�Ʒ���

    int direction()const;
    void setDirection(int direction);
    int lastDirction();//���ص�ǰ����

    //virtual bool checkOutsideOfGameView();//����Ƿ����Ӷ���Ҫ����
    virtual void restoreLife();
    virtual int life()const;
    virtual void setLife();
    
    //����ϵ��,ϵ��Խ�߱����ԽԶ
    virtual int coefficient()const;
    virtual void restoreCoefficient();
    virtual void addCoefficient();

    //���ø����
    void setStartPosX(qreal x);
    void setStartPosY(qreal y);
    qreal startPosX()const;
    qreal startPosY()const;

    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);

    virtual void jump();
    virtual void beHit();

    void setBeHitDirection(int value);
    
    AtkPointItem* point();

    void setCurrPlatform(int index);
    int platform();

public:
    //ͨ��factor�����ƶ���ִ�н���
    qreal walkFactor()const;
    void setWalkFactor(const qreal& walkFactor);

    qreal jumpFactor()const;
    void setJumpFactor(const qreal &jumpFactor);

    qreal downFactor()const;
    void setDownFactor(const qreal& downFactor);

    qreal beHitFactor()const;
    void setBeHitFactor(const qreal& beHitFactor);

signals:
    void walkFactorChanged(qreal);
    void jumpFactorChanged(qreal);
    void downFactorChanged(qreal);
    void beHitFactorChanged(qreal);
    void directionChanged(int);
    void jumpStart();
    void hitStart();

public slots:
    void addHorizontalInput(int input); //ͨ���޸�mDirectionֵ���������߷���
    void moveHorizontalEmojiPlayer();
    void moveUpEmojiPlayer();
    void hitAIPlayer();
    void checkOutsideOfGameView();
    void checkMoveCollision();

protected:
    EmojiScene* mScene;

    int mLastDirection;//ֻ������1����-1�ĳ���
    int mDirection;//��ɫ�ĳ���
    int mCurrPlatform;

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

    QPropertyAnimation* mWalkAnimation;
    QPropertyAnimation* mJumpAnimation;
    QPropertyAnimation* mDownAnimation;
    QPropertyAnimation* mBeHitAnimation;

    qreal mWalkFactor;
    qreal mJumpFactor;
    qreal mDownFactor;
    qreal mBeHitFactor;

    qreal mWorldSpeed = 1;
};

