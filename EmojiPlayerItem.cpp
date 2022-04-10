#include "EmojiPlayerItem.h"
#include "GroundItem.h"
#include "EmojiScene.h"
#include "AtkPoint.h"
#include <QPen>
#include <QObject>
#include <QPropertyAnimation>
#include <QKeyEvent>

EmojiPlayerItem::EmojiPlayerItem
(const QPixmap& pixmap,
	EmojiScene* parentScene,
	QGraphicsItem* parent)
	: QGraphicsPixmapItem(pixmap, parent),
	mParentScene(parentScene),
	mHorizontalInput(0), mDirection(0), mLife(1),
	mCoefficient(0), mLastDirection(1),
 mPlayerTimer(new QTimer)
{
	//ÿ30ms���һ���Ƿ�ˮƽ�ƶ��������� 
	mPlayerTimer->setInterval(30);
	connect(mPlayerTimer, &QTimer::timeout, this, &EmojiPlayerItem::moveHorizontalEmojiPlayer);
	connect(mPlayerTimer, &QTimer::timeout, this, &EmojiPlayerItem::moveDownEmojiPlayer);
	
	mPoint = new AtkPointItem(QPixmap("atkpoint.png"), this, mParentScene);
	mPoint->setPos(pos().x() + boundingRect().width() / 2,
		pos().y() + 10);
	mParentScene->addItem(mPoint);
	mPoint->setOffsetX(boundingRect().width() / 2);
	mPoint->setOffsetY(10);
	mPoint->hide();

	setJumpAnimation();
	setDownAnimation();
	setBeHitAnimation();
}

void EmojiPlayerItem::setJumpAnimation()
{
	mJumpAnimation = new QPropertyAnimation;
	mJumpAnimation->setTargetObject(this);
	mJumpAnimation->setPropertyName("jumpFactor");
	mJumpAnimation->setStartValue(0);
	mJumpAnimation->setKeyValueAt(0.5, 1);
	mJumpAnimation->setEndValue(-3.5);//���ֵ�ǿ��ǵ�������������
	//����ή���ڰ����
	mJumpAnimation->setDuration(800);
	mJumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);
}

void EmojiPlayerItem::setDownAnimation()
{
	mDownAnimation = new QPropertyAnimation;
	mDownAnimation->setTargetObject(this);
	mDownAnimation->setPropertyName("downFactor");
	mDownAnimation->setStartValue(0);
	mDownAnimation->setKeyValueAt(0.5, -1.5);
	mDownAnimation->setEndValue(-5);
	//-5�ڸõ�ͼ�п��Ա�֤�����䵽����
	mDownAnimation->setDuration(600);
	mDownAnimation->setEasingCurve(QEasingCurve::InQuad);
}

void EmojiPlayerItem::setBeHitAnimation()
{
	mBeHitAnimation = new QPropertyAnimation;
	mBeHitAnimation->setTargetObject(this);
	mBeHitAnimation->setPropertyName("beHitFactor");
	mBeHitAnimation->setStartValue(0);
	mBeHitAnimation->setKeyValueAt(0.5, 1);
	mBeHitAnimation->setEndValue(-3.5);
	//��ֹͣ���ڰ����
	mBeHitAnimation->setDuration(800);
	mBeHitAnimation->setEasingCurve(QEasingCurve::OutInQuad);
}

QPropertyAnimation* EmojiPlayerItem::jumpAnimation()
{
	return mJumpAnimation;
}

QPropertyAnimation* EmojiPlayerItem::downAnimation()
{
	return mDownAnimation;
}

QPropertyAnimation* EmojiPlayerItem::beHitAnimation()
{
	return mBeHitAnimation;
}

QTimer* EmojiPlayerItem::playerTimer()
{
	return mPlayerTimer;
}

void EmojiPlayerItem::checkTimer()
{
	//����ʱ��ִ���κζ���
	if (life() == 0) {
		mPlayerTimer->stop();
		return;
	}
	//������-1 0 1����״̬,���addHorizontalInput
	if (direction() == 0) {
		mPlayerTimer->stop();
		return;
	}
	else if (!mPlayerTimer->isActive()) {
		mPlayerTimer->start();
		return;
	}
}

int EmojiPlayerItem::direction() const
{
	return mDirection;
}

void EmojiPlayerItem::setDirection(int direction)
{
	mDirection = direction;
	if (mDirection != 0) {
		mLastDirection = mDirection;
		QTransform transform;
		if (mDirection < 0) {
			//��������תͼƬ
			transform.scale(-1, 1);
		}
		setTransform(transform);
	}
}

int EmojiPlayerItem::lastDirction()
{
	//���ص�ǰ����
	return mLastDirection;
}

bool EmojiPlayerItem::checkOutsideOfGameView()
{
	//���˳����ϱ߿�,�������������
	qreal x = pos().x();
	qreal y = pos().y();
	if (x<0 || x>scene()->width() || y>scene()->height() - 150)
	{
		//������Ծ�ͱ���������endvalue���ܲ�����������,������
		//ͣ�ڰ���е����,�ʽ������ж�ֵ�ϵ�
		return true;
	}
	
	return false;
}

void EmojiPlayerItem::restoreLife()
{
	this->setPos(mStartPosX, mStartPosY);
	mLife = 1;
	mCoefficient = 0;
	mDirection = 0;
	mHorizontalInput = 0;
	mFilter = 1;
	
	return;
}

int EmojiPlayerItem::life() const{
	return mLife;
}

void EmojiPlayerItem::setLife()
{
	mLife = 0;
	return;
}

int EmojiPlayerItem::coefficient() const
{
	return mCoefficient;
}

void EmojiPlayerItem::restorecoefficient()
{
	mCoefficient = 0;
}

void EmojiPlayerItem::addcoefficient()
{
	mCoefficient += 5;
}

void EmojiPlayerItem::setStartPosX(qreal x)
{
	mStartPosX = x;
}

void EmojiPlayerItem::setStartPosY(qreal y)
{
	mStartPosY = y;
}

qreal EmojiPlayerItem::startPosX() const
{
	return mStartPosX;
}

qreal EmojiPlayerItem::startPosY() const
{
	return mStartPosX;
}

void EmojiPlayerItem::addHorizontalInput(int input)
{
	//��Ϊ1 �������� Ϊ0���� Ϊ-1����
	//����:keyPrees�е�Dʹ�ý�ɫ����,mHorizontalInputΪ1
	//ִ��keyReleaseʱ�ᴫ��-1,ʹ��Ϊ0��ֹͣ
	mHorizontalInput += input;
	setDirection(qBound(-1, mHorizontalInput, 1));
}

void EmojiPlayerItem::setHorizontalInput(int input)
{
	mHorizontalInput = input;
}

void EmojiPlayerItem::keyPressEvent(QKeyEvent* event)
{
	//�����򷵻�
	if (event->isAutoRepeat() ) {
		return;
	}

	if (life() == 0) {
		return;
	}

	//FilterΪ1����ո�����,����ʱ�������ƶ����򽫸ü���������¼����������
	//������keyReleaseEvent�й���
	if (mFilter == 1)
	{
		if (event->key() == Qt::Key_A)
		{
			mAPressed = 1;
		}
		else if (event->key() == Qt::Key_D)
		{
			mDPressed = 1;
		}
		return;
	}

	switch (event->key()) {

	case Qt::Key_A:
		mAPressed = 1;
		addHorizontalInput(-1);
		checkTimer();
		break;

	case Qt::Key_D:
		mDPressed = 1;
		addHorizontalInput(1);
		checkTimer();
		break;

	case Qt::Key_Space:
		jump();
		break;

	case Qt::Key_J:
		mPoint->show();//����ʱ�ŻὫ��������ʾ����
		mPoint->hitTimer()->start();
		mPoint->hit();
		break;

	default:
		break;
	}
}

void EmojiPlayerItem::keyReleaseEvent(QKeyEvent* event)
{
	if (event->isAutoRepeat()) {
		return;
	}
	
	if (life() == 0) return;

	//����������release�¼�����Ҫ������
	if (event->key() == Qt::Key_J || event->key() == Qt::Key_Space)
	{
		return;
	}

	//���ո������������������ڱ���ס��״̬,���ͷ�һ����������
	if (mFilter == 1 && (mAPressed && mDPressed))
	{
		switch (event->key()) {
		case Qt::Key_A:
			mAPressed = 0;
			break;
		case Qt::Key_D:
			mDPressed = 0;
			break;
		default:
			break;
		}
		return;
	}
	
	if (mFilter == 1) {
		mFilter = 0;//��������ԭ����keyRelease��ִ��
		//��һ�γ���release�Ż�ִ��
		return;
	}

	switch (event->key()) {
	case Qt::Key_A:
		mAPressed = 0;
		addHorizontalInput(1);
		checkTimer();
		break;
	case Qt::Key_D:
		mDPressed = 0;
		addHorizontalInput(-1);
		checkTimer();
		break;
	default:
		break;
	}
}

void EmojiPlayerItem::jump()
{
	if ((QAbstractAnimation::Running != mBeHitAnimation->state()
		|| QAbstractAnimation::Running != mDownAnimation->state())
		&& QAbstractAnimation::Stopped == mJumpAnimation->state()) {
		mJumpStartLevel = pos().y();
		mLastJumpValue = 0;
		mJumpAnimation->start();
	}
}

void EmojiPlayerItem::beHit()
{
	if (QAbstractAnimation::Stopped == mBeHitAnimation->state()) {
		addcoefficient();
		mBeHitStartLevel = pos().y();
		mLastBeHitValue = 0;
		mBeHitStartPos = pos().x();
		mBeHitAnimation->start();
	}
}

void EmojiPlayerItem::setBeHitDirection(int value)
{
	mBeHitDirection = value;
}

AtkPointItem* EmojiPlayerItem::point()
{
	return mPoint;
}

qreal EmojiPlayerItem::jumpFactor() const
{
	return mJumpFactor;
}

void EmojiPlayerItem::setJumpFactor(const qreal& jumpFactor)
{
	if (mJumpFactor == jumpFactor) {
		return;
	}

	mJumpFactor = jumpFactor;
	emit jumpFactorChanged(mJumpFactor);

	qreal groundY = mJumpStartLevel;
	qreal curJumpValue = mJumpAnimation->currentValue().toReal();
	qreal y = groundY - curJumpValue * mJumpHeight;
	setY(y);

	if (checkOutsideOfGameView()
		&& life() == 1) {
		restoreLife();
		mJumpAnimation->stop();
		return;
	}

	qreal collideY = mParentScene->checkColliding(this);
	if (curJumpValue < mLastJumpValue
		&& collideY != EmojiScene::CHECK_COLLIDING_FAILURE_HEIGHT)
	{
		setY(collideY);
		mJumpAnimation->stop();
		return;
	}
	mLastJumpValue = curJumpValue;
}

qreal EmojiPlayerItem::downFactor() const
{
	return mDownFactor;
}

void EmojiPlayerItem::setDownFactor(const qreal& downFactor)
{
	if (mDownFactor == downFactor) {
		return;
	}

	mDownFactor = downFactor;
	emit downFactorChanged(mDownFactor);

	qreal groundY = mDownStartLevel;
	qreal curDownValue = mDownAnimation->currentValue().toReal();
	qreal y = groundY - curDownValue * mDownHeight;

	if (checkOutsideOfGameView()
		&& life() == 1) {
		restoreLife();
		mDownAnimation->stop();
		return;
	}

	//��������м���Ƿ���Խ���
	qreal collideY = mParentScene->checkColliding(this);

	if (collideY != EmojiScene::CHECK_COLLIDING_FAILURE_HEIGHT)
	{
		setY(collideY);
		mDownAnimation->stop();
		return;
	}
	
	setY(y);
}

qreal EmojiPlayerItem::beHitFactor() const
{
	return mBeHitFactor;
}

void EmojiPlayerItem::setBeHitFactor(const qreal& beHitFactor)
{
	if (mBeHitFactor == beHitFactor) {
		return;
	}

	mBeHitFactor = beHitFactor;
	emit beHitFactorChanged(mBeHitFactor);

	qreal curBeHitTime = mBeHitAnimation->currentValue().toReal();
	qreal curBeHitStep = mBeHitAnimation->currentTime();

	const int cushionCoefficient = 20000;//�������ֵʹ����Ծ�����������

	qreal y = mBeHitStartLevel - curBeHitTime * mBeHitHeight;
	qreal x = mBeHitStartPos + curBeHitStep *
		mBeHitHeight * mBeHitDirection *
		coefficient() / cushionCoefficient;

	if (checkOutsideOfGameView()
		&& life() == 1) {
		restoreLife();
		mBeHitAnimation->stop();
		return;
	}

	//���½�ʱ����Ƿ���Խ���
	qreal curBeHitValue = mBeHitAnimation->currentValue().toReal();
	qreal collideY = mParentScene->checkColliding(this);
	if (mLastBeHitValue> curBeHitValue
		&& collideY != EmojiScene::CHECK_COLLIDING_FAILURE_HEIGHT)
	{
		setY(collideY);
		mBeHitAnimation->stop();
		return;
	}

	setX(x);
	setY(y);
	mLastBeHitValue = curBeHitValue;
}

void EmojiPlayerItem::moveHorizontalEmojiPlayer()
{
	if (QAbstractAnimation::Running == mBeHitAnimation->state())
	{
		return;
	}
	
	if (direction() == 0) {
		return;
	}

	const int dx = direction() * mWorldSpeed;
	qreal newX = pos().x() + dx;

	setX(newX);
}

void EmojiPlayerItem::moveDownEmojiPlayer()
{
	if (QAbstractAnimation::Running == mBeHitAnimation->state())
	{
		return;
	}
	if (!mParentScene->checkDownConditionColliding(this)) {
		return;
	}

	if (QAbstractAnimation::Running == mJumpAnimation->state()) {
		return;
	}
	mDownStartLevel = pos().y();
	mDownAnimation->start();
}