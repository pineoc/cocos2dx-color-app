#ifndef __MAINSCENE_SCENE_H__
#define __MAINSCENE_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

#define BLACKSETTAG 124

#define REDCOLORTAG 1
#define ORANGECOLORTAG 2
#define YELLOWCOLORTAG 3
#define GREENCOLORTAG 4
#define BLUECOLORTAG 5
#define ERASERTAG 6

#define NORMALMODE 1
#define BLACKMODE 2
#define BLACKFILLMODE 3

#define BRUSHSMALLSIZE 1.0f
#define BRUSHLARGESIZE 2.0f

#define ERASERSMALLSIZE 5.0f
#define ERASERLARGESIZE 10.0f

#define COLORSCALE 1.5f

class main : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void changeColor(Ref* pSender);
	void blackSet(Ref* pSender);
	void clearFunc(Ref* pSender);
	void sizeUpBrush(Ref* pSender);
	void sizeUpEraser(Ref* pSender);

	//visible size param
	Size visibleSize;
	Vec2 origin;

	//Menu Object, tool menu
	Menu* toolMenu;
	MenuItemFont* brushSizeMenu;
	MenuItemFont* eraserSizeMenu;
	
	//board coloring set mode
	int modeBit;

	//brush color
	Color4B brushColor;
	float brushSize;
	float eraserSize;

	RenderTexture *target;
	Vector<Sprite*> _brushs;

	Vector<DrawNode*> _erasers;
	RenderTexture* pRTex;//black topBoard

	BlendFunc blendFunc;

	void onTouchesBegan(const std::vector<Touch*>&touches, Event* unused_event);
    void onTouchesMoved(const std::vector<Touch*>&touches, Event* unused_event);

    // implement the "static create()" method manually
    CREATE_FUNC(main);
};

#endif // __MAINSCENE_SCENE_H__
