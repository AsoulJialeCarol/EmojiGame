#pragma once
#include "Node.h"
class AIItem;
class EmojiDecisionTree;

class RootSel :public SelectorNode//����ѡ��ڵ�
{
public:
	RootSel(Node* root, EmojiDecisionTree* tree, AIItem* ai)
		:SelectorNode(root), mTree(tree), mAI(ai) {}
	AIItem* AI()
	{
		return mAI;
	}
	EmojiDecisionTree* tree()
	{
		return mTree;
	}
protected:
	AIItem* mAI;
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

class CondWalk :public ConditionNode//�ж��Ƿ�Ӧ��ˮƽ�ƶ�
{
public:
	CondWalk(Node* root) :ConditionNode(root) {}
	bool exec()
	{
		return IsWalkExecutable();
	}
private:
	bool IsWalkExecutable();
};

class CondJump : public ConditionNode//�ж��Ƿ�Ӧ�������ƶ�
{
public:
	CondJump(Node* root) :ConditionNode(root) {}
	bool exec()
	{
		return IsJumpExecutable();
	}
private:
	bool IsJumpExecutable();
};

class CondDown :public ConditionNode//�ж��Ƿ�Ӧ�������ƶ�
{
public:
	CondDown(Node* root) :ConditionNode(root) {}
	bool exec()
	{
		return IsDownExecutable();
	}
private:
	bool IsDownExecutable();
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

class BehaviorDown :public BehaviorNode//ִ�������ƶ�
{
public:
	BehaviorDown(Node* root) :BehaviorNode(root) {}
	bool exec();
};


