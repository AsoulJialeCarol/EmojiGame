#pragma once
#include <vector>
#include <functional>

class Node
{
public:
	Node(Node* r) :mRoot(r) {}
	virtual bool exec() = 0;
protected:
	Node* mRoot;//���ڵ��洢������������AI�볡������Ҫ��Ϣ
	//��ÿ���ڵ㶼��һ��ָ����ڵ��ָ��
};

class NonLeafNode :public Node//��Ҷ�ڵ�,��洢�ӽڵ�
{
public:
	NonLeafNode(Node* root) :Node(root) {}
	~NonLeafNode()
	{
		for (auto child : childNodes)
		{
			delete child;
		}
	}
	bool exec() = 0;
	void addChild(Node* child)
	{
		childNodes.push_back(child);
	}
protected:
	std::vector<Node*> childNodes;
};

class SelectorNode :public NonLeafNode//ѡ��ڵ�,ĳһ�ӽڵ㷵��Ϊ����ִֹͣ��
{
public:
	SelectorNode(Node* root) :NonLeafNode(root) {}
	bool exec()
	{
		for (auto child : childNodes)
		{
			if (child->exec())
			{
				return true;
			}
		}
		return false;
	}
};

class SequenceNode :public NonLeafNode//˳��ִ�нڵ�,ִ�е�ĳ���ӽڵ�Ϊ��Ϊֹ
{
public:
	SequenceNode(Node* root) :NonLeafNode(root) {}
	bool exec()
	{
		for (auto child : childNodes)
		{
			if (!child->exec())
			{
				return false;
			}
		}
		return true;
	}
};

class ParallelNode :public NonLeafNode//����ִ�нڵ�
{
public:
	ParallelNode(Node* root) :NonLeafNode(root) {}
	bool exec()
	{
		for (auto child : childNodes)
		{
			child->exec();
		}
		return true;
	}
};

class ConditionNode :public Node//�����ڵ�
{
public:
	ConditionNode(Node* root) :Node(root) {}
	bool exec() = 0;
};

class BehaviorNode :public Node//��Ϊ�ڵ�
{
public:
	BehaviorNode(Node* root) :Node(root) {}
	bool exec() = 0;
};

class OneChildNonLeafNode :public NonLeafNode
{
public:
	OneChildNonLeafNode(Node* root) :NonLeafNode(root) {}
	void addChild(Node* node)
	{
		if (!childNodes.size())
		{
			childNodes.push_back(node);
		}
	}
};

class InvertNode : public OneChildNonLeafNode //ȡ���ڵ�,ֻ����һ������
{
public:
	InvertNode(Node* root) :OneChildNonLeafNode(root) {}
	virtual bool exec()override
	{
		return !childNodes[0]->exec();
	}
};

class CountNode : public OneChildNonLeafNode {//ѭ��ִ�нڵ�
public:
	CountNode(Node* root, int cnt = 0) :OneChildNonLeafNode(root), count(cnt) {}
	virtual bool exec()override
	{
		while (--count) {
			if (childNodes[0]->exec() == false)return false;
		}
		return true;
	}
protected:
	int count;
};



