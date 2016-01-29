#include "HelloWorldScene.h"
//#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"




USING_NS_CC;
//using namespace cocostudio::timeline;

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
			CC_CALLBACK_1(HelloWorld::menuCloseCallback, this)
		);
		CC_BREAK_IF(!pCloseItem);
		pCloseItem->setPosition(Vec2(wsize.width - 20, 20));
		Menu* pMenu1 = Menu::create(pCloseItem, NULL);
		pMenu1->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenu1);
		
		//开始按钮
		MenuItemImage *pBeginItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuBeginCallback, this)
		);
		CC_BREAK_IF(!pBeginItem);
		pBeginItem->setPosition(Vec2(wsize.width / 4, wsize.height / 2));
		Menu* pMenu2 = Menu::create(pBeginItem, NULL);
		pMenu2->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenu2);

		//发送按钮
		MenuItemImage *pSendItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuSendCallback, this)
		);
		CC_BREAK_IF(!pSendItem);
		pSendItem->setPosition(Vec2(wsize.width - 100, wsize.height / 2));
		Menu* pMenu3 = Menu::create(pSendItem, NULL);
		pMenu3->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenu3);


		//添加三个按钮到player层
		this->addChild(pMenu1, 1);
		this->addChild(pMenu2, 2);
		this->addChild(pMenu3, 3);

		//内容显示
		txtLabel = Label::createWithSystemFont("content", "Arial", 24);
		txtLabel->setPosition(Vec2(wsize.width / 2, wsize.height / 3));
		this->addChild(txtLabel, 101);

		//设置背景
		Sprite *bg = Sprite::create("HelloWorld.png");
		bg->setPosition(Vec2(wsize.width, wsize.height));
		bg->setContentSize(Size(wsize.width, wsize.height));
		float spx = bg->getTextureRect().getMaxX();
		float spy = bg->getTextureRect().getMaxY();
		bg->setScaleX(wsize.width / spx); //设置精灵宽度缩放比例
		bg->setScaleY(wsize.height / spy);
		this->addChild(bg, 0);
		

		//定时调度
		this->schedule(schedule_selector(HelloWorld::msgLogic), 0.1f);

		bRet = true;
	} while (0);

	return bRet;
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
	// "close" menu item clicked
	Director::getInstance()->end();
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

	//protocol buffer
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	talkbox::talk_create user;
	user.set_name("xfs");
	user.set_userid(123);
	std::string userbuf;
	user.SerializeToString(&userbuf);
	TcpMsg->pushSendQueue(userbuf, 1003);

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
		if (pk->id == 0){
			sprintf(txt, "\nnew msg:%s", pk->msg);
		}else{
			
			switch (pk->id)
			{
				case 1000://登陆结果
					GOOGLE_PROTOBUF_VERIFY_VERSION;
					{
					talkbox::talk_result result;
					result.ParseFromString(pk->msg);
					sprintf(txt, "\nlogin result: msgid:%d,len:%d,result:%d", pk->id, strlen(pk->msg), result.id());
					}
					break;
				case 1008://登陆成功信息
					GOOGLE_PROTOBUF_VERIFY_VERSION;
					{
						talkbox::talk_create create;
						create.ParseFromString(pk->msg);
						sprintf(txt, "\nlogin info: msgid:%d,len:%d,userid:%d,name:%s", pk->id, strlen(pk->msg), create.userid(),create.name().c_str());
					}
					break;
				case 1010://获得消息
					GOOGLE_PROTOBUF_VERIFY_VERSION;
					{
						talkbox::talk_message message;
						message.ParseFromString(pk->msg);
						sprintf(txt, "\nnew msg: msgid:%d,len:%d,fromuserid:%d,touserid:%d,msg:%s", pk->id, strlen(pk->msg), message.fromuserid(),message.touserid(),message.msg().c_str());
					}
					break;
				case 1002://获得用户
					GOOGLE_PROTOBUF_VERIFY_VERSION;
					{
						talkbox::talk_users users;
						users.ParseFromString(pk->msg);
						for (int i = 0; i < users.users_size(); i++) {
							const talkbox::talk_users_talk_user user = users.users(i);
							sprintf(txt, "\nnew user: msgid:%d,len:%d,userid:%d,name:%s", pk->id, strlen(pk->msg), user.userid(), user.name().c_str());
						}
					}
					break;
				default:
					sprintf(txt, "\nunkonw msg: msgid:%d,len:%d", pk->id, strlen(pk->msg));
					break;
			}
		}
		std::string oldtxt = txtLabel->getString();
		oldtxt.append(txt);
		txtLabel->setString(oldtxt);

	}
	//CCLOG("msgLogic");
}
