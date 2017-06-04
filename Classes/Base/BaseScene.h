//
//  BaseScene.hpp
//  WaterDrop
//
//  Created by hahaYXXXJ on 2017/5/6.
//
//

#ifndef BaseScene_hpp
#define BaseScene_hpp

#include "cocos2d.h"
#include "Macros.h"
#include "WDSprite.h"

class BaseScene : public cocos2d::Scene
{
public:
    float visibleW;
    float visibleH;
    float originX;
    float originY;
    
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(BaseScene);
    
    void addEventListenerTouchOneByOne(WDSprite* target,
                                       const cocos2d::Rect& textureRectTouchBegan,
                                       const cocos2d::Rect& textureRectTouchEnded);
    void addEventListenerTouchOneByOne(WDSprite* target,
                                                  const cocos2d::Rect& textureRectTouchBegan,
                                                  const cocos2d::Rect& textureRectTouchEnded,
                                                  std::function<void(WDSprite* sprite)> wdTouchOneByOneCallback);
    
protected:

    // 调用 addEventListenerTouchOneByOne方法，sprite被点击到后回调这个函数
    virtual void onTouchOneByOneHandle(WDSprite* sprite, WDSprite::TouchStatus touchStatus){}
    virtual void enterSprites(){} // 装载精灵进入场景
};

#endif /* BaseScene_hpp */
