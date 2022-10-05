#pragma once
#include <qgraphicsview.h>
#include <QPointer>
class PauseWindow;
class EmojiScene;

class EmojiView :
    public QGraphicsView
{
    Q_OBJECT
public:
    void mySetScene(EmojiScene* scene);//�ú�����������mScene��Ա,�Ӷ�����keyEvent
signals:
    void backToMainWindow();
    void backToLastWindow();

private:
    void keyPressEvent(QKeyEvent* event);

    EmojiScene* mScene;
    QPointer<PauseWindow> mPauseWindow;
};

