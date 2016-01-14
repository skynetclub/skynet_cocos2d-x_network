#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"



USING_NS_CC;
using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();

    auto layer = HelloWorld::create();
    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		auto wsize = Director::getInstance()->getWinSize();
		
		//关闭按钮
		MenuItemImage *pCloseItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(HelloWorld::menuCloseCallback));
		CC_BREAK_IF(!pCloseItem);
		pCloseItem->setPosition(Vec2(wsize.width - 20, 20));
		Menu* pMenu = Menu::create(pCloseItem, NULL);
		pMenu->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenu);
		
		//开始按钮
		MenuItemImage *pBeginItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(HelloWorld::menuBeginCallback));
		CC_BREAK_IF(!pBeginItem);
		pBeginItem->setPosition(Vec2(wsize.width / 4, wsize.height / 2));
		Menu* pMenu2 = Menu::create(pBeginItem, NULL);
		pMenu2->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenu2);

		//发送按钮
		MenuItemImage *pSendItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(HelloWorld::menuSendCallback));
		CC_BREAK_IF(!pSendItem);
		pSendItem->setPosition(Vec2(wsize.width - 100, wsize.height / 2));
		Menu* pMenu3 = Menu::create(pSendItem, NULL);
		pMenu3->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenu3);


		//添加三个按钮到player层
		this->addChild(pMenu, 1);
		this->addChild(pMenu2, 100);
		this->addChild(pMenu3, 100);

		//内容显示
		txtLabel = LabelTTF::create("content", "Arial", 24);
		txtLabel->setPosition(Vec2(wsize.width / 2, wsize.height / 3));
		this->addChild(txtLabel, 101);

		//定时调度
		this->schedule(schedule_selector(HelloWorld::msgLogic), 0.1f);

		bRet = true;
	} while (0);

	return bRet;
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

void HelloWorld::menuBeginCallback(Ref* pSender)
{
	TcpMsg* TcpMsg = TcpMsg::shareTcpMsg();
	if (TcpMsg->isRuning())
	{
		TcpMsg->tcp_stop();
	}
	else
	{
		TcpMsg->tcp_start();
	}
	
}

void HelloWorld::menuSendCallback(Ref* pSender)
{
	TcpMsg* TcpMsg = TcpMsg::shareTcpMsg();
	std::string msg = "{\"username\":\"test106\",\"password\":\"111111\"}";
	TcpMsg->pushSendQueue(msg, 105);
	CCLOG("menuSendCallback");

	//TcpMsg->sendFunc();
}

void HelloWorld::msgLogic(float dt)
{
	Queue* recvQueue = TcpMsg::shareTcpMsg()->getRecvQueue();
	if (recvQueue != NULL && recvQueue->getSize() > 0)
	{
		Pocket* pk = recvQueue->PullPocket();
		char txt[1024] = { 0 };
		sprintf(txt, "have msg %s",pk->msg);
		txtLabel->setString(txt);
	}
	//CCLOG("msgLogic");
}