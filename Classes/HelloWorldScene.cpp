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
		userid = 0;

		CC_BREAK_IF(!Layer::init());
		auto wsize = Director::getInstance()->getWinSize();

		//退出按钮
		MenuItemImage *pCloseItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuCloseCallback, this)
			);
		CC_BREAK_IF(!pCloseItem);
		pCloseItem->setPosition(Vec2(wsize.width - 20, wsize.height - 20));
		Menu* pMenu1 = Menu::create(pCloseItem, NULL);
		pMenu1->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenu1);

		//网络按钮
		MenuItemImage *pLinkItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuLinkCallback, this)
			);
		CC_BREAK_IF(!pLinkItem);
		pLinkItem->setPosition(Vec2(wsize.width / 2 - 60, 20));
		Menu* pMenu2 = Menu::create(pLinkItem, NULL);
		pMenu2->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenu2);

		//登陆按钮
		MenuItemImage *pLoginItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuLoginCallback, this)
			);
		CC_BREAK_IF(!pLoginItem);
		pLoginItem->setPosition(Vec2(wsize.width / 2, 20));
		Menu* pMenu3 = Menu::create(pLoginItem, NULL);
		pMenu3->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenu3);

		//发送按钮
		MenuItemImage *pSendItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuSendCallback, this)
			);
		CC_BREAK_IF(!pSendItem);
		pSendItem->setPosition(Vec2(wsize.width / 2 + 60, 20));
		Menu* pMenu4 = Menu::create(pSendItem, NULL);
		pMenu4->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenu4);

		//动画按钮
		MenuItemImage *pAnimateItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuAnimateCallback, this)
			);
		CC_BREAK_IF(!pAnimateItem);
		pAnimateItem->setPosition(Vec2(wsize.width - 80, wsize.height - 20));
		Menu* pMenu5 = Menu::create(pAnimateItem, NULL);
		pMenu5->setPosition(Point::ZERO);
		CC_BREAK_IF(!pMenu5);


		//添加三个按钮到player层
		this->addChild(pMenu1, 2);
		this->addChild(pMenu2, 2);
		this->addChild(pMenu3, 2);
		this->addChild(pMenu4, 2);
		this->addChild(pMenu5, 2);

		// 创建输入框
		//txtInput = TextFieldTTF::textFieldWithPlaceHolder("input message", "Arial", 24);
		//txtInput->setPosition(Vec2(wsize.width / 2, 80));
		//txtInput->attachWithIME();
		//txtInput->setString("xfs");
		//this->addChild(txtInput, 3);
		// 创建输入框
		txtInput = CursorTextField::textFieldWithPlaceHolder(this, "Input Text", "Thonburi", 24);
		txtInput->setAnchorPoint(Point(0.0f, 0.0f));
		txtInput->setInputWidth(wsize.width);
		txtInput->setPosition(Vec2(wsize.width / 5, 80));
		txtInput->setString("xfs");
		this->addChild(txtInput, 0);


		//内容显示
		txtLabel = Label::createWithSystemFont("content", "Arial", 24);
		txtLabel->setAnchorPoint(Point(0, 0));
		txtLabel->setPosition(Vec2(40, 150));
		this->addChild(txtLabel, 4);


		//设置背景
		Sprite *bg = Sprite::create("HelloWorld.png");
		bg->setPosition(Vec2(wsize.width, wsize.height));
		bg->setContentSize(Size(wsize.width, wsize.height));
		float spx = bg->getTextureRect().getMaxX();
		float spy = bg->getTextureRect().getMaxY();
		bg->setScaleX(wsize.width / spx); //设置精灵宽度缩放比例
		bg->setScaleY(wsize.height / spy);
		//this->addChild(bg, 0);

		auto red = LayerColor::create(Color4B(255, 100, 100, 128), wsize.width, wsize.height);
		this->addChild(red, 0);


		//定时调度
		this->schedule(schedule_selector(HelloWorld::msgLogic), 0.1f);

		//监听事件
		NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HelloWorld::userLogin), "login_ok", nullptr);

		//预加载动画
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("roleanimate/1001_effup.plist", "roleanimate/1001_effup.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("roleanimate/1001_role.plist", "roleanimate/1001_role.png");
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.1f);
		auto animation2 = Animation::create();
		animation2->setDelayPerUnit(0.1f);
		for (int j = 0; j < 439; j++){
			auto sfName = String::createWithFormat("1001_effup/%04d", j)->getCString();
			auto sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName);
			animation->addSpriteFrame(sf);

			auto sfName2 = String::createWithFormat("1001_role/%04d", j)->getCString();
			auto sf2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName2);
			animation2->addSpriteFrame(sf2);
		}
		AnimationCache::getInstance()->addAnimation(animation, String::create("1001_effup")->getCString());
		AnimationCache::getInstance()->addAnimation(animation2, String::create("1001_role")->getCString());

		bRet = true;
	} while (0);

	return bRet;
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
	// "close" menu item clicked
	Director::getInstance()->end();
}
void HelloWorld::menuAnimateCallback(Ref* pSender)
{
	auto animation1 = AnimationCache::getInstance()->getAnimation(String::create("1001_effup")->getCString());
	auto animate1 = RepeatForever::create(Animate::create(animation1));
	animate1->setTag(1);

	auto animation2 = AnimationCache::getInstance()->getAnimation(String::create("1001_role")->getCString());
	auto animate2 = RepeatForever::create(Animate::create(animation2));
	animate2->setTag(2);

	//auto animate3 = Spawn::create(Animate::create(animation1), Animate::create(animation2), NULL);
	//animate3->setTag(3);

	auto wsize = Director::getInstance()->getWinSize();

	auto heard_sp1 = Sprite::create("CloseNormal.png");
	heard_sp1->setPosition(Point(wsize.width / 2, wsize.height / 2));
	heard_sp1->runAction(animate1);
	auto heard_sp2 = Sprite::create("CloseNormal.png");
	heard_sp2->setPosition(Point(wsize.width / 2, wsize.height / 2));
	heard_sp2->runAction(animate2);

	this->addChild(heard_sp1, 2);
	this->addChild(heard_sp2, 2);
}

void HelloWorld::menuLinkCallback(Ref* pSender)
{
	CCLOG(txtInput->getString().c_str());
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

void HelloWorld::menuLoginCallback(Ref* pSender)
{
	TcpMsg* TcpMsg = TcpMsg::shareTcpMsg();

	//protocol buffer
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	talkbox::talk_create user;
	user.set_name(txtInput->getString().c_str());
	user.set_userid(123);
	std::string userbuf;
	user.SerializeToString(&userbuf);
	TcpMsg->pushSendQueue(userbuf, 1003);

	CCLOG("menuLoginCallback");

	//TcpMsg->sendFunc();
}

void HelloWorld::menuSendCallback(Ref* pSender)
{
	TcpMsg* TcpMsg = TcpMsg::shareTcpMsg();

	GOOGLE_PROTOBUF_VERIFY_VERSION;
	talkbox::talk_message msg;
	msg.set_msg(txtInput->getString().c_str());
	msg.set_touserid(-1);
	msg.set_fromuserid(userid);
	std::string msgbuf;
	msg.SerializeToString(&msgbuf);
	TcpMsg->pushSendQueue(msgbuf, 1005);

	CCLOG("menuSendCallback");

	//TcpMsg->sendFunc();
}

//登陆事件
void HelloWorld::userLogin(Ref* pSender){
	NotificationCenter::getInstance()->removeObserver(this, "login_ok");

	TcpMsg* TcpMsg = TcpMsg::shareTcpMsg();

	GOOGLE_PROTOBUF_VERIFY_VERSION;
	talkbox::talk_message msg;
	msg.set_msg("hello every,i am newer!");
	msg.set_touserid(-1);
	msg.set_fromuserid(userid);
	std::string msgbuf;
	msg.SerializeToString(&msgbuf);
	TcpMsg->pushSendQueue(msgbuf, 1005);
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
						userid = create.userid();

						//发送事件
						NotificationCenter::getInstance()->postNotification("login_ok", nullptr);
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
