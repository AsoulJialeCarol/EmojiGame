#pragma once
#include <QObject>
class RootSel;
class AIItem;

class EmojiDecisionTree
{
public:
    EmojiDecisionTree(AIItem* ai);
    ~EmojiDecisionTree();

    RootSel* root();//ȡ�ø��ڵ�ĺ���

private:
    RootSel* mRoot;
    AIItem* mAI;
};
