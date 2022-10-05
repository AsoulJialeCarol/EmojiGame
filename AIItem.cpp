#include "AIItem.h"
#include "EmojiNodes.h"
#include "EmojiDecisionTree.h"
#include "EmojiScene.h"
#include <QTimer>
#include <QPropertyAnimation>

AIItem::AIItem(const QPixmap& pixmap,
	EmojiScene* parentScene,
	EmojiPlayerItem* player,
<<<<<<< HEAD
	QGraphicsTextItem* label,
	QString name,
	QString picturePath,
	QGraphicsItem* parent)
    :EmojiPlayerItem(pixmap, parentScene, label, name,picturePath,  parent)
=======
	QGraphicsItem* parent)
	:EmojiPlayerItem(pixmap, parentScene, parent)
>>>>>>> ca7163100d4092aaa545b608dd3dde5f53caeec6
{	
	mPlayer = player;
	mDecisionTree = new EmojiDecisionTree(this);

	mAITimer = new QTimer;
	mAITimer->setInterval(30);
	mAITimer->start();

	//ÿ30msִ��һ�ξ�����
	connect(mAITimer, &QTimer::timeout,
		this, &AIItem::traverseDecisionTree);

	for (auto item : parentScene->items())
    {
        EmojiPlayerItem* player = dynamic_cast<EmojiPlayerItem*>(item);

        if (player)
        {
			mPlayer = player;
		}
    }

}

//���ھ�����û�м̳�QObject ������Ҫ�ֶ�delete
AIItem::~AIItem()
{
	delete mDecisionTree;
}

void AIItem::setPlayer(EmojiPlayerItem* player)
{
	mPlayer = player;
}

EmojiPlayerItem* AIItem::player()
{
	return mPlayer;
}

std::vector<int>& AIItem::route()
{
	return mRoute;
}

void AIItem::traverseDecisionTree()
{
	if (QAbstractAnimation::Running == mDownAnimation->state()
		|| QAbstractAnimation::Running == mBeHitAnimation->state())
	{
		return;
	}

	mDecisionTree->root()->exec();
}
