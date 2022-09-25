#include "EmojiNodes.h"
#include "EmojiScene.h"
#include "EmojiDecisionTree.h"
#include "AIItem.h"
#include "PlatformItem.h"
#include "AtkPoint.h"
#include <vector>

//����׷���Ŀ��������ѡ��ai�ĳ���
//���������,��������̨,�ʴ���QGraphicsItem
void changeAIDirection(QGraphicsItem* item, EmojiPlayerItem* ai)
{
    qreal xPlayer = item->pos().x();
    qreal xAI = ai->pos().x();
    qreal dist = xPlayer - xAI;

    if (dist > 0)
    {
        ai->setDirection(1);
    }
    else
    {
        ai->setDirection(-1);
    }
}


//����̨���ݾ�����������С��������
bool cmp(PlatformItem* a, PlatformItem* b)
{
    return a->pos().y() > b->pos().y();
}

//����׷��·���ϵ�������̨
PlatformItem* checkNearestPlatform
(std::vector<PlatformItem*>& vPlatform,
    AIItem* ai, EmojiPlayerItem* player)
{
    std::sort(vPlatform.begin(), vPlatform.end(), cmp);
    int i = 0;
    int j = 1;
    //�����ų����Լ�������̨
    while (i < vPlatform.size()
        && vPlatform.at(i)->pos().y()
        - ai->boundingRect().height()
        >= ai->pos().y())
    {
        ++i;
    }   
    
    //i��������β������û�п�����̨
    if (i == vPlatform.size())
    {
        return Q_NULLPTR;
    }

    j = i;

    //�ҵ���һ��������̨i��,Ѱ��jʹ������[i,j)�е���̨����ͬһˮƽ����
    while (j < vPlatform.size()
        && vPlatform.at(i)->pos().y() == vPlatform.at(j)->pos().y())
    {
        ++j;
    }
    
    //���Ǹ���x������̨������ҵ�Զ����ѡ��������̨
    //����������ŵ�
    qreal playerX = player->pos().x() + player->boundingRect().width() / 2;
    qreal dist = 0x3f3f3f3f;
    PlatformItem* nearestPlatform = Q_NULLPTR;

    for (int k = i; k < j; ++k)
    {
        qreal platformX = vPlatform.at(k)->pos().x()
            + vPlatform.at(k)->boundingRect().width() / 2;
        qreal y = vPlatform.at(k)->pos().y();

        qreal distPlayer = fabs(platformX - playerX);
        if (distPlayer < dist)
        {
            dist = distPlayer;
            nearestPlatform = vPlatform.at(k);
        }
    }

    return nearestPlatform;
}

bool CondNear::isNear()
{
    RootSel* root = dynamic_cast<RootSel*>(mRoot);
    QGraphicsScene* scene = root->AI()->scene();
    for (auto item : scene->items())
    {
        EmojiPlayerItem* player = dynamic_cast<EmojiPlayerItem*>(item);
        
        if (player == root->AI())
        {
            continue;
        }
        
        if (player)
        {
            QPointF posPlayer = player->pos();
            QPointF posAI = root->AI()->pos();

            //��������֮�����ĵ�ľ������ж��Ƿ񹥻�
            qreal playerX = posPlayer.x() + player->boundingRect().width() / 2;
            qreal playerY = posPlayer.y();
            qreal AIX = posAI.x() + root->AI()->boundingRect().width() / 2;
            qreal AIY = posAI.y();

            qreal delta = 5;

            //��ˮƽ����С��120�Ҵ���ͬһˮƽ������ִ�й���
            //���ڽ�ɫ���ܲ��Ǿ�׼�Ĳ���ƽ���� ������һ��deltaֵ
            if (fabs(playerX - AIX) < 120 
                && fabs(playerY - AIY) < delta)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

bool CondWalk::isWalkExecutable()
{
    RootSel* root = dynamic_cast<RootSel*>(mRoot);
    QGraphicsScene* scene = root->AI()->scene();
    for (auto item : scene->items())
    {
        EmojiPlayerItem* player = dynamic_cast<EmojiPlayerItem*>(item);
        
        if (item == root->AI())
        {
            continue;
        }
        
        if (player)
        {
            QPointF posPlayer = player->pos();
            QPointF posAI = root->AI()->pos();
            const qreal delta = 5;

            if ((fabs(posPlayer.y() - posAI.y()) < delta)
                && fabs(posPlayer.x() - posAI.x()) >= 120)
            {
                return true;
            }
            
            return false;
        }
    }
}

bool CondJump::isJumpExecutable()
{
    RootSel* root = dynamic_cast<RootSel*>(mRoot);
    QGraphicsScene* scene = root->AI()->scene();
    for (auto item : scene->items())
    {
        EmojiPlayerItem* player = dynamic_cast<EmojiPlayerItem*>(item);

        if (item == root->AI())
        {
            continue;
        }

        if (player)
        {
            QPointF posPlayer = player->pos();
            QPointF posAI = root->AI()->pos();

            //��ұ��Լ�����ִ��
            if (posAI.y() - posPlayer.y() > 0)
            {
                return true;
            }
            return false;
        }
    }
}

bool CondDown::isDownExecutable()
{
    RootSel* root = dynamic_cast<RootSel*>(mRoot);
    QGraphicsScene* scene = root->AI()->scene();
    for (auto item : scene->items())
    {
        EmojiPlayerItem* player = dynamic_cast<EmojiPlayerItem*>(item);

        if (player == root->AI())
        {
            continue;
        }

        if (player)
        {
            //��ұ��Լ�����ִ��
            if (player->pos().y() > root->AI()->pos().y())
            {
                return true;
            }
            return false;
        }
    }
}

bool BehaviorHit::exec()
{
    RootSel* root = dynamic_cast<RootSel*>(mRoot);
    QGraphicsScene* scene = root->AI()->scene();
    AtkPointItem* point = root->AI()->point();

    //��������item,�ҵ�player��ִ�ж���
    for (auto item : scene->items())
    {
        EmojiPlayerItem* player = dynamic_cast<EmojiPlayerItem*>(item);

        if (item == root->AI())
        {            
            continue;
        }

        if (player)
        {
            changeAIDirection(player, root->AI());

            point->show();
            point->hitTimer()->start();
            point->hit();
        }
    }

    return true;
}



bool BehaviorWalk::exec()
{
    RootSel* root = dynamic_cast<RootSel*>(mRoot);
    QGraphicsScene* scene = root->AI()->scene();

    for (auto item : scene->items())
    {
        if (item == root->AI()) 
        {
            continue;
        }

        EmojiPlayerItem* player = dynamic_cast<EmojiPlayerItem*>(item);
        if (player)
        {
            changeAIDirection(player, root->AI());
            root->AI()->checkTimer();
            return true;
        }
    }
}

bool BehaviorJump::exec()
{
    RootSel* root = dynamic_cast<RootSel*>(mRoot);
    QGraphicsScene* scene = root->AI()->scene();
    std::vector<PlatformItem*> vPlatform;
    EmojiPlayerItem* player;

    for (auto item : scene->items())
    {
        PlatformItem* platform = dynamic_cast<PlatformItem*>(item);
        EmojiPlayerItem* itemPlayer = dynamic_cast<EmojiPlayerItem*>(item);

        if (itemPlayer)
        {
            if (itemPlayer == root->AI())
            {
                continue;
            }
            else
            {
                player = itemPlayer;
            }
        }


        if (platform)
        {
            vPlatform.emplace_back(platform);
        }
        
    }

    PlatformItem* nearestPlatform
        = checkNearestPlatform(vPlatform, root->AI(), player);
    if (!nearestPlatform)
    {
        return false;
    }
    changeAIDirection(nearestPlatform, root->AI());

    

    //distX1Ϊ����̨��˵ľ���,distX2Ϊ���Ҷ˵ľ���
    qreal distX1 = fabs(nearestPlatform->pos().x()
        - root->AI()->pos().x() - root->AI()->boundingRect().width() / 2);
    qreal distX2 = fabs(nearestPlatform->pos().x()
        + nearestPlatform->boundingRect().width()
        - root->AI()->pos().x() - root->AI()->boundingRect().width() / 2);
    //ѡ��Ͻ�����һ���������Ƿ���Ծ
    qreal distX = fmin(distX1, distX2);

    if (distX > 50)
    {
        root->AI()->checkTimer();
    }
    else
    {
        root->AI()->jump();
    }

    return true;

}

bool BehaviorDown::exec()
{
    RootSel* root = dynamic_cast<RootSel*>(mRoot);
    QGraphicsScene* scene = root->AI()->scene();

    for (auto item : scene->items())
    {
        if (item == root->AI())
        {
            continue;
        }

        EmojiPlayerItem* player = dynamic_cast<EmojiPlayerItem*>(item);
        if (player)
        {
            //���ý�Ϊ�򵥵��߼�:���м���ֱ�����
            //���ڵ�ͼ��Ƶ�ԭ��,���м���һ�������
            //�����ĵ�ͼ����Ҫ������ƶ���
            if (root->AI()->pos().x() < player->scene()->width() / 2)
            {
                root->AI()->setDirection(1);
            }
            else
            {
                root->AI()->setDirection(-1);
            }
            root->AI()->checkTimer();
            return true;
        }
    }
}
