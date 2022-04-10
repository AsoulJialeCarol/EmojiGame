#include "EmojiDecisionTree.h"
#include "EmojiNodes.h"
#include "AIItem.h"
#include <QObject>

EmojiDecisionTree::EmojiDecisionTree(AIItem* ai) :mAI(ai)
{

    //�����ļ��и�¼�ľ�����(DecisionTree.dot)�������ľ�����
    mRoot = new RootSel(nullptr, this, mAI);

    //ѡ���ǹ�������׷���ѡ��ڵ�
    SelectorNode* selHandle = new SelectorNode(mRoot);
    mRoot->addChild(selHandle);

    //�жϾ���Զ��
    SequenceNode* seqNear = new SequenceNode(mRoot);
    SequenceNode* seqFar = new SequenceNode(mRoot);
    selHandle->addChild(seqNear);
    selHandle->addChild(seqFar);

    //�н�
    CondNear* condNearEnough = new CondNear(mRoot);
    BehaviorHit* behaviorHit = new BehaviorHit(mRoot);
    seqNear->addChild(condNearEnough);
    seqNear->addChild(behaviorHit);

    //��Զ
    InvertNode* invertCondNear = new InvertNode(mRoot);
    CondNear* condTooFar = new CondNear(mRoot);
    invertCondNear->addChild(condTooFar);
    seqFar->addChild(invertCondNear);

    //׷��·��ѡ��ڵ�
    SelectorNode* selRoute = new SelectorNode(mRoot);
    SequenceNode* seqWalk = new SequenceNode(mRoot);
    SequenceNode* seqJump = new SequenceNode(mRoot);
    SequenceNode* seqDown = new SequenceNode(mRoot);
    seqFar->addChild(selRoute);
    selRoute->addChild(seqWalk);
    selRoute->addChild(seqJump);
    selRoute->addChild(seqDown);

    //�ж�ˮƽ�ƶ�
    CondWalk* condWalk = new CondWalk(mRoot);
    BehaviorWalk* behaviorWalk = new BehaviorWalk(mRoot);
    seqWalk->addChild(condWalk);
    seqWalk->addChild(behaviorWalk);

    //�ж������ƶ�
    CondJump* condJump = new CondJump(mRoot);
    BehaviorJump* behaviorJump = new BehaviorJump(mRoot);
    seqJump->addChild(condJump);
    seqJump->addChild(behaviorJump);

    //�ж������ƶ�
    CondDown* condDown = new CondDown(mRoot);
    BehaviorDown* behaviorDown = new BehaviorDown(mRoot);
    seqDown->addChild(condDown);
    seqDown->addChild(behaviorDown);
}

EmojiDecisionTree::~EmojiDecisionTree()
{
    delete mRoot;
}

RootSel* EmojiDecisionTree::root()
{
    return mRoot;
}