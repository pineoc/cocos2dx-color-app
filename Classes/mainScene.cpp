#include "mainScene.h"

Scene* main::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = main::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool main::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !LayerColor::initWithColor(Color4B(255,255,255,255)))
	{
		return false;
	}

	//set values
	modeBit = NORMALMODE;
	brushSize = BRUSHSMALLSIZE;
	eraserSize = ERASERSMALLSIZE;
	brushColor = Color4B::BLACK;
	BlendFunc tmpBlendFunc = { GL_ONE, GL_ZERO };
	blendFunc = tmpBlendFunc;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	target = RenderTexture::create(visibleSize.width, visibleSize.height, kCCTexture2DPixelFormat_RGBA8888);
	target->retain();
	target->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(target);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(main::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 ,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	auto blackSetItem = MenuItemImage::create(
		"blacksetBtn.png", "blacksetBtn.png",
		CC_CALLBACK_1(main::blackSet, this));

	blackSetItem->setPosition(Vec2(origin.x + 800, origin.y + 50));
	blackSetItem->setScale(COLORSCALE);

	auto blackItem = MenuItemImage::create(
		"btn.png", "btn.png",
		CC_CALLBACK_1(main::changeColor, this));

	blackItem->setPosition(Vec2(origin.x + 100, origin.y + 50));
	blackItem->setColor(Color3B(0,0,0));
	blackItem->setTag(BLACKCOLORTAG);
	blackItem->setScale(COLORSCALE);

	auto toRedItem = MenuItemImage::create(
		"btn.png", "btn.png",
		CC_CALLBACK_1(main::changeColor, this));

	toRedItem->setPosition(Vec2(origin.x + 200, origin.y + 50));
	toRedItem->setColor(Color3B::RED);
	toRedItem->setTag(REDCOLORTAG);
	toRedItem->setScale(COLORSCALE);

	auto toOrangeItem = MenuItemImage::create(
		"btn.png", "btn.png",
		CC_CALLBACK_1(main::changeColor, this));

	toOrangeItem->setPosition(Vec2(origin.x + 300, origin.y + 50));
	toOrangeItem->setColor(Color3B::ORANGE);
	toOrangeItem->setTag(ORANGECOLORTAG);
	toOrangeItem->setScale(COLORSCALE);

	auto toYellowItem = MenuItemImage::create(
		"btn.png", "btn.png",
		CC_CALLBACK_1(main::changeColor, this));

	toYellowItem->setPosition(Vec2(origin.x + 400, origin.y + 50));
	toYellowItem->setColor(Color3B::YELLOW);
	toYellowItem->setTag(YELLOWCOLORTAG);
	toYellowItem->setScale(COLORSCALE);

	auto toGreenItem = MenuItemImage::create(
		"btn.png", "btn.png",
		CC_CALLBACK_1(main::changeColor, this));

	toGreenItem->setPosition(Vec2(origin.x + 500, origin.y + 50));
	toGreenItem->setColor(Color3B::GREEN);
	toGreenItem->setTag(GREENCOLORTAG);
	toGreenItem->setScale(COLORSCALE);

	auto toBlueItem = MenuItemImage::create(
		"btn.png", "btn.png",
		CC_CALLBACK_1(main::changeColor, this));

	toBlueItem->setPosition(Vec2(origin.x + 600, origin.y + 50));
	toBlueItem->setColor(Color3B::BLUE);
	toBlueItem->setTag(BLUECOLORTAG);
	toBlueItem->setScale(COLORSCALE);

	auto eraserItem = MenuItemImage::create(
		"eraser.png", "eraser.png",
		CC_CALLBACK_1(main::changeColor, this));
	eraserItem->setPosition(Vec2(origin.x + 700, origin.y + 50));
	eraserItem->setTag(ERASERTAG);
	eraserItem->setScale(COLORSCALE);

	// create menu, it's an autorelease object
	auto colorMenu = Menu::create(blackSetItem, blackItem, toRedItem, toOrangeItem, toYellowItem,
		toGreenItem, toBlueItem, eraserItem, NULL);
	colorMenu->setPosition(Vec2::ZERO);
	this->addChild(colorMenu, 2);

	MenuItemFont::setFontSize(30);
	auto clearMenu = MenuItemFont::create("Clear", CC_CALLBACK_1(main::clearFunc, this));
	brushSizeMenu = MenuItemFont::create("Brush Size: S", CC_CALLBACK_1(main::sizeUpBrush, this));
	eraserSizeMenu = MenuItemFont::create("Eraser Size : S", CC_CALLBACK_1(main::sizeUpEraser, this));

	toolMenu = Menu::create(brushSizeMenu, eraserSizeMenu, clearMenu, nullptr);
	toolMenu->alignItemsHorizontallyWithPadding(20);
	toolMenu->setColor(Color3B::BLACK);
	toolMenu->setPosition(Vec2(visibleSize.width - 300, visibleSize.height - 30));
	this->addChild(toolMenu, 2);

	auto listener = EventListenerTouchAllAtOnce::create();
	//listener->setSwallowTouches(true);

	listener->onTouchesBegan = CC_CALLBACK_2(main::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(main::onTouchesMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}


void main::menuCloseCallback(Ref* pSender)
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

void main::changeColor(Ref* pSender)
{
	MenuItemImage* mi = (MenuItemImage*)pSender;
	int tag = mi->getTag();
	switch (tag)
	{
	case BLACKCOLORTAG:
		brushColor = Color4B::BLACK;
		break;
	case REDCOLORTAG:
		brushColor = Color4B::RED;
		break;
	case ORANGECOLORTAG:
		brushColor = Color4B::ORANGE;
		break;
	case YELLOWCOLORTAG:
		brushColor = Color4B::YELLOW;
		break;
	case GREENCOLORTAG:
		brushColor = Color4B::GREEN;
		break;
	case BLUECOLORTAG:
		brushColor = Color4B::BLUE;
		break;
	case ERASERTAG:
		brushColor = Color4B::WHITE;
		if(BLACKMODE == modeBit)
			modeBit = BLACKFILLMODE;
		else if(BLACKFILLMODE == modeBit)
			modeBit = BLACKMODE;
		break;
	default:
		break;
	}
}
void main::blackSet(Ref* pSender)
{
	if(this->getChildByTag(BLACKSETTAG))
		this->removeChild(pRTex);

	toolMenu->setColor(Color3B::WHITE);

	pRTex = RenderTexture::create(visibleSize.width, visibleSize.height);
	pRTex->setPosition(Vec2(visibleSize.width/2+2000.0f, visibleSize.height/2));
	pRTex->setTag(BLACKSETTAG);
	this->addChild(pRTex, 1);

	modeBit = BLACKMODE;

	Sprite* blackSprite = Sprite::create("b.png");
	blackSprite->setAnchorPoint(Vec2(0.5,0.5));
	blackSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	blackSprite->setScaleX(visibleSize.width / blackSprite->getContentSize().width);
	blackSprite->setScaleY(visibleSize.height / blackSprite->getContentSize().height);
	blackSprite->setColor(Color3B::BLACK);

	pRTex->begin();
	blackSprite->visit();
	pRTex->end();

	auto movAct = MoveTo::create(1,Vec2(visibleSize.width/2,visibleSize.height/2));
	pRTex->runAction(movAct);
}
void main::sizeUpBrush(Ref* pSender)
{
	if(BRUSHSMALLSIZE == brushSize)
	{
		brushSizeMenu->setString("Brush Size: L");
		brushSize = BRUSHLARGESIZE;
	}
	else
	{
		brushSizeMenu->setString("Brush Size: S");
		brushSize = BRUSHSMALLSIZE;
	}
}
void main::sizeUpEraser(Ref* pSender)
{
	if(ERASERSMALLSIZE == eraserSize)
	{
		eraserSizeMenu->setString("eraser Size: L");
		eraserSize = ERASERLARGESIZE;
	}
	else
	{
		eraserSizeMenu->setString("eraser Size: S");
		eraserSize = ERASERSMALLSIZE;
	}
}

void main::clearFunc(Ref* pSender)
{
	target->clear(0, 0, 0, 0);
	if(this->getChildByTag(BLACKSETTAG))
		pRTex->clear(0,0,0,0);
	modeBit = NORMALMODE;
	toolMenu->setColor(Color3B::BLACK);
}

void main::onTouchesBegan(const std::vector<Touch*>&touches, Event* unused_event)
{}

void main::onTouchesMoved(const std::vector<Touch*>&touches, Event* unused_event)
{
	Touch *touch = *touches.begin();
	Point start = touch->getLocation();
	Point end = touch->getPreviousLocation();

	if(NORMALMODE == modeBit)
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
				sprite->setColor(Color3B(brushColor));
				sprite->setOpacity(20);
				_brushs.pushBack(sprite);
			}
			for (int i = 0; i < d; ++i)
			{
				float difx = end.x - start.x;
				float dify = end.y - start.y;
				float delta = (float)i / distance;
				_brushs.at(i)->setPosition(Vec2(start.x + (difx * delta), start.y + (dify * delta)));
				_brushs.at(i)->setRotation(rand() % 360);
				float r = (float)(rand() % 50 / 50.f) + 0.25f;
				_brushs.at(i)->setScale(brushSize * r);
				if(Color4B::WHITE == _brushs.at(i)->getColor())
					_brushs.at(i)->setScale(eraserSize / 5 * r);
				_brushs.at(i)->visit();
			}
		}
		target->end();
	}
	else
	{
		pRTex->begin(); //black board draw start
		float distance = start.getDistance(end);
		if (distance > 1)
		{
			int d = (int)distance;
			_erasers.clear();
			for(int i = 0; i < d; ++i)
			{
				Sprite* node;
				//DrawNode* node = DrawNode::create();
				if (ERASERLARGESIZE == eraserSize)
					node = Sprite::create("b_eraser.png");
				else
					node = Sprite::create("b_eraser_small.png");


				if (BLACKMODE == modeBit)
				{ // erase blackset
					//node->drawDot(Vec2(), eraserSize, Color4F(0, 0, 0, 0));
					node->setColor(Color3B::WHITE);
					node->setOpacity(0);
				}
				else
				{ // fill blackset
					//node->drawDot(Vec2(), eraserSize, Color4F::BLACK);
					node->setColor(Color3B::BLACK);
					node->setOpacity(255);
				}
				_erasers.pushBack(node);
			}
			for (int i = 0; i < d; ++i)
			{
				float difx = end.x - start.x;
				float dify = end.y - start.y;
				float delta = (float)i / distance;
				_erasers.at(i)->setPosition(Vec2(start.x + (difx * delta), start.y + (dify * delta)));
				_erasers.at(i)->setRotation(rand() % 360);
				float r = (float)(rand() % 50 / 50.f) + 0.25f;
				_erasers.at(i)->setScale(r);
				if(BLACKMODE == modeBit)
					_erasers.at(i)->setBlendFunc(blendFunc);
				_erasers.at(i)->visit();
			}
		}
		pRTex->end(); //black board draw end
	}
}
