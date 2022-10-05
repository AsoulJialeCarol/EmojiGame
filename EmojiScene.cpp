#include "EmojiScene.h"
#include "EmojiPlayerItem.h"
#include "GroundItem.h"
#include "BackgroundItem.h"
#include "PlatformItem.h"
#include "AtkPoint.h"
#include "AIItem.h"
#include "EmojiMap.h"

#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QImage>
#include <QPixmap>
#include <QGraphicsTextItem>

#define PLATFORM1 460-160*2
#define PLATFORM2 460-160
#define PLATFORM3 460
//�����aiplayerʱ��Ӧ��ע�⵽��jump�����п��ܴ���emojiplayer��aiplayer��ײ�����
//����aiplayer��jump����Ӧ�������ʵ��޸ģ��Լ�mJumpStartLevel����aiplayer������
EmojiScene::EmojiScene()
	:
	mEmojiPlayer(Q_NULLPTR),
	mAIPlayer(Q_NULLPTR),
	mBackground(Q_NULLPTR)
{
	mBackground = new BackgroundItem(QPixmap("Background.png"));
	setSceneRect(mBackground->boundingRect());
	mBackground->setPos(0, 0);

	addItem(mBackground);

	QSize groundRect = QPixmap("Ground.png").size();
	QSize platformRect = QPixmap("Platform.png").size();

	mMap = new EmojiMap();
	mMap->setPlatformsPtr(&mPlatforms);
	mMap->setPlatform((width() - groundRect.width()) / 2, height() - groundRect.height(), "Ground.png");
	mMap->setPlatform(100, PLATFORM3, "Platform.png");
	mMap->setPlatform(250, PLATFORM2, "Platform.png");
	mMap->setPlatform(width() - 250 - platformRect.width(), PLATFORM2, "Platform.png");
	mMap->setPlatform(width() - 100 - platformRect.width(), PLATFORM3, "Platform.png");
	mMap->setPlatform(20, PLATFORM1, "Platform.png");
	mMap->setPlatform(280, PLATFORM1, "Platform.png");
	mMap->setPlatform(width() - 280 - platformRect.width(), PLATFORM1, "Platform.png");
	mMap->setPlatform(width() - 20 - platformRect.width(), PLATFORM1, "Platform.png");
	mMap->buildGraph(180, 180);

	for (int i = 0; i < mPlatforms.size(); ++i)
	{
		addItem(mPlatforms[i]);
	}
	
	auto& ground = *mPlatforms[0];
	mPlayerLabel = new QGraphicsTextItem("Player's Coefficient: 0%");
	mPlayerLabel->setPos(120, height() - 120);
	mPlayerLabel->setTextWidth(150);
	mEmojiPlayer = new EmojiPlayerItem(QPixmap("Player.png"), this, mPlayerLabel, "Player's Coefficient: ","Player.png");
	mEmojiPlayer->setPos(ground.pos().x() + 50,
		ground.pos().y() - mEmojiPlayer->boundingRect().height());
	mEmojiPlayer->setStartPosX(mEmojiPlayer->pos().x());
	mEmojiPlayer->setStartPosY(mEmojiPlayer->pos().y());
	mEmojiPlayer->setCurrPlatform(0);
	addItem(mPlayerLabel);
	addItem(mEmojiPlayer);

	mAIPlayerLabel = new QGraphicsTextItem("AIPlayer's Coefficient: 0%");
	mAIPlayerLabel->setPos(width() - 270, height() - 120);
	mAIPlayerLabel->setTextWidth(150);
	mAIPlayer = new AIItem(QPixmap("AI.png"), this ,mEmojiPlayer, mAIPlayerLabel,"AIPlayer's Coefficient: ","AI.png");
	mAIPlayer->setPos(ground.pos().x()
		+ ground.boundingRect().width()
		- mAIPlayer->boundingRect().width() - 50,
		ground.pos().y() - mAIPlayer->boundingRect().height());
	mAIPlayer->setStartPosX(mAIPlayer->pos().x());
	mAIPlayer->setStartPosY(mAIPlayer->pos().y());
	mAIPlayer->setCurrPlatform(0);
	addItem(mAIPlayerLabel);
	addItem(mAIPlayer);
}

EmojiScene::~EmojiScene()
{
	if (mBackground) delete mBackground;
	if (mMap) delete mMap;
}

EmojiMap* EmojiScene::map()
{
	return mMap;
}

vector<PlatformItem*>& EmojiScene::platforms()
{
	return mPlatforms;
}

//����EmojiView��keyPressEvent�����δ��ݸ�scene��item��keyPressEvent
//����Ҫ��view��event���ݸ�scene,�ٴ������
void EmojiScene::keyPressEvent(QKeyEvent* event)
{
	mEmojiPlayer->keyPressEvent(event);
}

void EmojiScene::keyReleaseEvent(QKeyEvent* event)
{
	mEmojiPlayer->keyReleaseEvent(event);
}

bool EmojiScene::checkMoveCollision(EmojiPlayerItem* player)
{

	//���ڽ�ɫ���ܲ��Ǿ�׼�Ĳ���������,������ʱ����������½�����
	//ֻ��Ҫ�жϽ�ɫ�Ų������嶥��y����֮���Ƿ���һ��С��Χ�ڼ���
	//����Ҫ������ȫ���
	
	const static qreal delta = 7;

	int dir = player->lastDirction();
	qreal playerLeft = player->pos().x();
	qreal playerRight = player->pos().x() + dir * player->boundingRect().width();
	if (dir == -1)
	{
		std::swap(playerLeft, playerRight);
	}
	qreal playerBottom = player->pos().y() + player->boundingRect().height();

	for (int i=0;i<mPlatforms.size();++i)
	{
		qreal platformLeft = mPlatforms[i]->pos().x();
 		qreal platformRight = mPlatforms[i]->pos().x() + mPlatforms[i]->boundingRect().width();
		qreal platformTop = mPlatforms[i]->pos().y();

		if (playerRight > platformLeft && playerLeft < platformRight
 			&& playerBottom > platformTop - delta && playerBottom < platformTop + delta)
		{
			player->setCurrPlatform(i);
			player->setY(platformTop - player->boundingRect().height());
			player->stopAnimations();
			if (player->point()->hitAnimation()->state()!=QAbstractAnimation::Running) 
			{
				player->setPixmap(QPixmap(player->picturePath()));
			}
				return true;
		}
	}

	return false;
}

bool EmojiScene::checkHitCollision(AtkPointItem* atkPoint)
{
	//�жϹ������Ƿ�򵽽�ɫ
	for (QGraphicsItem* item : collidingItems(atkPoint)) {
		EmojiPlayerItem* enemy = dynamic_cast<EmojiPlayerItem*>(item);
		if (enemy && enemy != atkPoint->player())
		{
			enemy->setBeHitDirection(atkPoint->player()->lastDirction());
			enemy->beHit();
			if (enemy == mEmojiPlayer)
			{
				QString tmp = "Player's Coefficient:" + QString::number(mEmojiPlayer->coefficient()) + "%";
				mPlayerLabel->setPlainText(tmp);
			}
			else 
			{
				QString tmp = "AIPlayer's Coefficient:" + QString::number(mAIPlayer->coefficient()) + "%";
				mAIPlayerLabel->setPlainText(tmp);
			}
			return true;
		}
	}
	return false;
}

