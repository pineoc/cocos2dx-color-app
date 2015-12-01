#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !LayerColor::initWithColor(Color4B(255,255,255,255)))
	{
		return false;
	}

	modeBit=1;
	p_size=1.0;
	eraser_size=5.0;
	p_color = Color4B::BLACK;
	BlendFunc blendFunc1 = { GL_ONE, GL_ZERO };
	blendFunc = blendFunc1;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	target = RenderTexture::create(visibleSize.width, visibleSize.height,kCCTexture2DPixelFormat_RGBA8888);
	target->retain();
	target->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	this->addChild(target);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	auto blackItem = MenuItemImage::create(
		"btn.png","btn.png",
		CC_CALLBACK_1(HelloWorld::blackSet, this));

	blackItem->setPosition(Vec2(origin.x+100, origin.y+50));
	blackItem->setColor(Color3B(0,0,0));
	blackItem->setScale(1.5f);

	auto toRedItem = MenuItemImage::create(
		"btn.png","btn.png",
		CC_CALLBACK_1(HelloWorld::changeColor, this));

	toRedItem->setPosition(Vec2(origin.x+200, origin.y+50));
	toRedItem->setColor(Color3B::RED);
	toRedItem->setTag(1);
	toRedItem->setScale(1.5f);

	auto toOrangeItem = MenuItemImage::create(
		"btn.png","btn.png",
		CC_CALLBACK_1(HelloWorld::changeColor, this));

	toOrangeItem->setPosition(Vec2(origin.x+300, origin.y+50));
	toOrangeItem->setColor(Color3B::ORANGE);
	toOrangeItem->setTag(2);
	toOrangeItem->setScale(1.5f);

	auto toYellowItem = MenuItemImage::create(
		"btn.png","btn.png",
		CC_CALLBACK_1(HelloWorld::changeColor, this));

	toYellowItem->setPosition(Vec2(origin.x+400, origin.y+50));
	toYellowItem->setColor(Color3B::YELLOW);
	toYellowItem->setTag(3);
	toYellowItem->setScale(1.5f);

	auto toGreenItem = MenuItemImage::create(
		"btn.png","btn.png",
		CC_CALLBACK_1(HelloWorld::changeColor, this));

	toGreenItem->setPosition(Vec2(origin.x+500, origin.y+50));
	toGreenItem->setColor(Color3B::GREEN);
	toGreenItem->setTag(4);
	toGreenItem->setScale(1.5f);

	auto toBlueItem = MenuItemImage::create(
		"btn.png","btn.png",
		CC_CALLBACK_1(HelloWorld::changeColor, this));

	toBlueItem->setPosition(Vec2(origin.x+600, origin.y+50));
	toBlueItem->setColor(Color3B::BLUE);
	toBlueItem->setTag(5);
	toBlueItem->setScale(1.5f);

	auto eraserItem = MenuItemImage::create(
		"eraser.png","eraser.png",
		CC_CALLBACK_1(HelloWorld::changeColor, this));
	eraserItem->setPosition(Vec2(origin.x+700, origin.y+50));
	eraserItem->setTag(6);
	eraserItem->setScale(1.5f);

	// create menu, it's an autorelease object
	auto menu2 = Menu::create(blackItem,toRedItem,toOrangeItem,toYellowItem,
		toGreenItem,toBlueItem,eraserItem, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 2);

	MenuItemFont::setFontSize(30);
	auto item1 = MenuItemFont::create("Clear", CC_CALLBACK_1(HelloWorld::clearFunc, this));
	brushSizeMenu = MenuItemFont::create("Brush Size: S", CC_CALLBACK_1(HelloWorld::sizeUpBrush, this));
	eraserSizeMenu = MenuItemFont::create("Eraser Size : S", CC_CALLBACK_1(HelloWorld::sizeUpEraser, this));
	menu3 = Menu::create(brushSizeMenu,eraserSizeMenu,item1,nullptr);
	this->addChild(menu3,2);
	menu3->alignItemsHorizontallyWithPadding(20);
	menu3->setColor(Color3B::BLACK);
	menu3->setPosition(Vec2(visibleSize.width - 300, visibleSize.height - 30));

	auto listener = EventListenerTouchAllAtOnce::create();
	//listener->setSwallowTouches(true);

	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::eraseGL(Ref* pSender)
{
	while(this->getChildByTag(123))
		this->removeChildByTag(123);
}
void HelloWorld::changeColor(Ref* pSender)
{
	MenuItemImage* mi = (MenuItemImage*)pSender;
	int tag = mi->getTag();
	switch (tag)
	{
	case 1:
		p_color = Color4B::RED;
		break;
	case 2:
		p_color = Color4B::ORANGE;
		break;
	case 3:
		p_color = Color4B::YELLOW;
		break;
	case 4:
		p_color = Color4B::GREEN;
		break;
	case 5:
		p_color = Color4B::BLUE;
		break;
	case 6:
		p_color = Color4B::WHITE;
		if(modeBit==2)
			modeBit=3;
		else if(modeBit==3)
			modeBit=2;
		break;
	default:
		break;
	}
}
void HelloWorld::blackSet(Ref* pSender)
{
	if(this->getChildByTag(124))
		this->removeChild(pRTex);

	menu3->setColor(Color3B::WHITE);

	pRTex = RenderTexture::create(visibleSize.width, visibleSize.height);
	pRTex->setPosition(Vec2(visibleSize.width/2+2000.0f, visibleSize.height/2));
	pRTex->setTag(124);
	this->addChild(pRTex, 1);

	modeBit=2;

	Sprite* pBg = Sprite::create("b.png");
	pBg->setAnchorPoint(Vec2(0.5,0.5));
	pBg->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	pBg->setScaleX(visibleSize.width/pBg->getContentSize().width);
	pBg->setScaleY(visibleSize.height/pBg->getContentSize().height);
	pBg->setColor(Color3B::BLACK);
	pRTex->begin();
	pBg->visit();
	pRTex->end();

	auto movAct = MoveTo::create(1,Vec2(visibleSize.width/2,visibleSize.height/2));
	pRTex->runAction(movAct);
}
void HelloWorld::sizeUpBrush(Ref* pSender)
{
	if(p_size==1.0)
	{
		brushSizeMenu->setString("Brush Size: L");
		p_size=2.0;
	}
	else
	{
		brushSizeMenu->setString("Brush Size: S");
		p_size=1.0;
	}
}
void HelloWorld::sizeUpEraser(Ref* pSender)
{
	if(eraser_size==5.0)
	{
		eraserSizeMenu->setString("eraser Size: L");
		eraser_size=10.0;
	}
	else
	{
		eraserSizeMenu->setString("eraser Size: S");
		eraser_size=5.0;
	}
}

void HelloWorld::clearFunc(Ref* pSender)
{
	target->clear(0,0,0,0);
	if(this->getChildByTag(124))
		pRTex->clear(0,0,0,0);
	modeBit=1;
	menu3->setColor(Color3B::BLACK);
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>&touches, Event* unused_event)
{}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>&touches, Event* unused_event)
{
	Touch *touch = *touches.begin();
	Point start = touch->getLocation();
	Point end = touch->getPreviousLocation();
	if(modeBit==1)
	{
		target->begin();

		float distance = start.getDistance(end);
		if (distance > 1)
		{
			int d = (int)distance;
			_brushs.clear();
			for(int i = 0; i < d; ++i)
			{
				Sprite * sprite = Sprite::create("brush.png");
				sprite->setColor(Color3B(p_color));
				sprite->setOpacity(20);
				_brushs.pushBack(sprite);
			}
			for (int i = 0; i < d; i++)
			{
				float difx = end.x - start.x;
				float dify = end.y - start.y;
				float delta = (float)i / distance;
				_brushs.at(i)->setPosition(Vec2(start.x + (difx * delta), start.y + (dify * delta)));
				_brushs.at(i)->setRotation(rand() % 360);
				float r = (float)(rand() % 50 / 50.f) + 0.25f;
				_brushs.at(i)->setScale(p_size*r);
				if(_brushs.at(i)->getColor()==Color4B::WHITE)
					_brushs.at(i)->setScale(eraser_size/5*r);
				_brushs.at(i)->visit();
			}
		}
		target->end();
	}
	else
	{
		pRTex->begin();
		float distance = start.getDistance(end);
		if (distance > 1)
		{
			int d = (int)distance;
			_erasers.clear();
			for(int i = 0; i < d; ++i)
			{
				DrawNode* node = DrawNode::create();
				if(modeBit==2)
					node->drawDot(Vec2(),eraser_size,Color4F(0,0,0,0));
				else
					node->drawDot(Vec2(),eraser_size,Color4F::BLACK);
				_erasers.pushBack(node);
			}
			for (int i = 0; i < d; i++)
			{
				float difx = end.x - start.x;
				float dify = end.y - start.y;
				float delta = (float)i / distance;
				_erasers.at(i)->setPosition(Vec2(start.x + (difx * delta), start.y + (dify * delta)));
				_erasers.at(i)->setRotation(rand() % 360);
				float r = (float)(rand() % 50 / 50.f) + 0.25f;
				_erasers.at(i)->setScale(r);
				if(modeBit==2)
					_erasers.at(i)->setBlendFunc(blendFunc);
				_erasers.at(i)->visit();
			}
		}
		pRTex->end();
	}
}
