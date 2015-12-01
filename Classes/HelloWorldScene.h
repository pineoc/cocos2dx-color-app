#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void eraseGL(cocos2d::Ref* pSender);
	void changeColor(Ref* pSender);
	void blackSet(Ref* pSender);
	void clearFunc(Ref* pSender);
	void sizeUpBrush(Ref* pSender);
	void sizeUpEraser(Ref* pSender);

	Size visibleSize;
	Vec2 origin;

	Menu* menu3;
	MenuItemFont* brushSizeMenu;
	MenuItemFont* eraserSizeMenu;
	
	int modeBit;

	Color4B p_color;
	float p_size;
	float eraser_size;

	RenderTexture *target;
	Vector<Sprite*> _brushs;

	Vector<DrawNode*> _erasers;
	RenderTexture* pRTex;//black topBoard

	BlendFunc blendFunc;

	void onTouchesBegan(const std::vector<Touch*>&touches, Event* unused_event);
    void onTouchesMoved(const std::vector<Touch*>&touches, Event* unused_event);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
