#pragma once
#include "Node.h"
class AIItem;
class EmojiPlayerItem;
class EmojiScene;
class EmojiDecisionTree;

class RootSel :public SelectorNode//����ѡ��ڵ�
{
public:
	RootSel(Node* root, EmojiDecisionTree* tree, AIItem* ai);

	AIItem* AI()
	{
		return mAI;
	}

	EmojiPlayerItem* player()
	{
		return mPlayer;
	}

	EmojiScene* scene()
	{
		return mScene;
	}

	EmojiDecisionTree* tree()
	{
		return mTree;
	}
protected:
	AIItem* mAI;
	EmojiPlayerItem* mPlayer;
	EmojiScene* mScene;
	EmojiDecisionTree* mTree;
};

class CondNear :public ConditionNode//�жϾ����Ƿ��㹻���Դ�������
{
public:
	CondNear(Node* root) :ConditionNode(root) {}
	bool exec()
	{
		return isNear();
	}
private:
	bool isNear();
};

class CondRoute : public ConditionNode
{
public:
	CondRoute(Node* root):ConditionNode(root){}
	bool exec()
	{
		return isRouteExist();
	}
private:
	bool isRouteExist();
};

class CondWalk :public ConditionNode//�ж��Ƿ�Ӧ��ˮƽ�ƶ�
{
public:
	CondWalk(Node* root) :ConditionNode(root) {}
	bool exec()
	{
		return isWalkExecutable();
	}
private:
	bool isWalkExecutable();
};

class CondJump : public ConditionNode//�ж��Ƿ�Ӧ�������ƶ�
{
public:
	CondJump(Node* root) :ConditionNode(root) {}
	bool exec()
	{
		return isJumpExecutable();
	}
private:
	bool isJumpExecutable();
};

class BehaviorHit :public BehaviorNode//ִ�й���
{
public:
	BehaviorHit(Node* root) :BehaviorNode(root) {}
	bool exec();
};

class BehaviorWalk :public BehaviorNode//ִ��ˮƽ�ƶ�
{
public:
	BehaviorWalk(Node* root) :BehaviorNode(root) {}
	bool exec();
};

class BehaviorJump :public BehaviorNode//ִ�������ƶ�
{
public:
	BehaviorJump(Node* root) :BehaviorNode(root) {}
	bool exec();
};

