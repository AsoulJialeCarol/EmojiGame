#include "mainwindow.h"
#include "characterwindow.h"

#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mCharaWindow(Q_NULLPTR),
    mStartBtn(Q_NULLPTR),mPayBtn(Q_NULLPTR),mQuitBtn(Q_NULLPTR),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //������
    this->setWindowTitle("EmojiGame");
    this->setFixedSize(640,640);
    

    //��ʼ��λ
    mStartBtn = new QPushButton("Start", this);
    mStartBtn->setFixedSize(80, 30);
    mStartBtn->move(280,400);
    
    //���¿�ʼ��λ����ѡ���ɫҳ��
    connect(mStartBtn, &QPushButton::clicked,[=](){
        mCharaWindow = new CharacterWindow;
        this->hide();

        mCharaWindow = new CharacterWindow;
        mCharaWindow->show();

        //�������������ź�
        connect(mCharaWindow, &CharacterWindow::backToMainWindow, [=]() {
            mCharaWindow->setAttribute(Qt::WA_DeleteOnClose);
            mCharaWindow->close();
            this->show();    //show mainwindow
            });

        //��������һ�������ź�
        connect(mCharaWindow, &CharacterWindow::backToLastWindow, [=]() {
            mCharaWindow->setAttribute(Qt::WA_DeleteOnClose);
            mCharaWindow->close();
            this->show();    //show mainwindow
            });
    });


    //������水ť
    mPayBtn = new QPushButton("Pay",this);
    mPayBtn->setFixedSize(80,30);
    mPayBtn->move(280, 450);

    connect(mPayBtn, &QPushButton::clicked,[=](){
        mPayWindow = new PayWindow;
        mPayWindow->show();
    });


    //�˳���ť
    mQuitBtn = new QPushButton("Quit", this);
    mQuitBtn->setFixedSize(80,30);
    mQuitBtn->move(280, 500);
   
    connect(mQuitBtn, &QPushButton::clicked,[=](){
        //ֱ�ӹر�,����delete,�����������
        this->close();
    }); 
}

MainWindow::~MainWindow()
{
    delete ui;
}

