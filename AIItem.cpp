#include "AIItem.h"
#include "EmojiNodes.h"
#include "EmojiDecisionTree.h"
#include <QTimer>
#include <QPropertyAnimation>

AIItem::AIItem(const QPixmap& pixmap,
	EmojiScene* parentScene,
	QGraphicsItem* parent)
	:EmojiPlayerItem(pixmap, parentScene, parent)
{	
	mDecisionTree = new EmojiDecisionTree(this);
	mAITimer = new QTimer;
	mAITimer->setInterval(30);
	mAITimer->start();

	//ÿ30msִ��һ�ξ�����
	connect(mAITimer, &QTimer::timeout,
		this, &AIItem::traverseDecisionTree);
	
	mPlayerTimer = new QTimer;
	mPlayerTimer->setInterval(30);
	
	//ÿ30ms�ж�һ���Ƿ��ƶ����Ƿ�����
	connect(mPlayerTimer, &QTimer::timeout,
		this, &AIItem::moveHorizontalEmojiPlayer);
	connect(mPlayerTimer, &QTimer::timeout,
		this, &AIItem::moveDownEmojiPlayer);
}

//���ھ�����û�м̳�QObject ������Ҫ�ֶ�delete
AIItem::~AIItem()
{
	delete mDecisionTree;
}

void AIItem::traverseDecisionTree()
{
	if (QAbstractAnimation::Running == mDownAnimation->state()
		|| QAbstractAnimation::Running == mBeHitAnimation->state())
	{
		return;
	}

	if (!mDecisionTree->root()->exec())
	{
		setDirection(0);
	}
}
