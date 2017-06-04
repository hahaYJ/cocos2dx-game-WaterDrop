//
//  SingleGameScene.hpp
//  WaterDrop
//
//  Created by hahaYXXXJ on 2017/5/12.
//
//

#ifndef SingleGameScene_hpp
#define SingleGameScene_hpp

#include "cocos2d.h"
#include "BaseScene.h"
USING_NS_CC;

// 游戏场景整合

class SingleGame : public BaseScene
{
public:
    static cocos2d::Scene* createScene();
    // implement the "static create()" method manually
    CREATE_FUNC(SingleGame);
    
private:
    virtual void enterSprites();
    void onTouchOneByOneHandle(WDSprite* sprite, WDSprite::TouchStatus touchStatus);
    
};

////////////////////////////////////////////////////////////////////////////
//
// SingleGameBackground 背景层级调用
//
////////////////////////////////////////////////////////////////////////////

class SingleGameBackground : public Layer {
    
public:
    static SingleGameBackground* createSingleGameBackground(const Vec2& position, const Size & size);
    void initGameBackground(const Vec2& position, const Size & size);
    CREATE_FUNC(SingleGameBackground);
};

////////////////////////////////////////////////////////////////////////////
//
// SingleGameBackground 前景层级调用 包括：按钮、分数、成绩等
//
////////////////////////////////////////////////////////////////////////////

class SingleGameForegroundground : public Layer {
    
public:
    static SingleGameForegroundground* createSingleGameForegroundground(const Vec2& position, const Size & size);
    void initGameForegroundground(const Vec2& position, const Size & size);
    void showAndHide();
    CREATE_FUNC(SingleGameForegroundground);
};

////////////////////////////////////////////////////////////////////////////
//
// StatusBarLayer 显示血量、分数、游戏基本状态集合
//
////////////////////////////////////////////////////////////////////////////

class StatusSetLayer : public Layer {
    
public:
    static StatusSetLayer* createStatusSetLayer(const Vec2& position, const Size & size);
    void initStatusSetLayer(const Vec2& position, const Size & size);
    void fogAttack(); // 起雾攻击
    
    enum class BloodStatus
    {
        BLOOD_CAPACITY_100,  // 满血
        BLOOD_CAPACITY_75,   // 75%
        BLOOD_CAPACITY_50,   // 50%
        BLOOD_CAPACITY_25,   // 25%
        BLOOD_CAPACITY_0     // 0%
    };
    // 显示血量
    void showBlood(BloodStatus bloodStatus);
    // 警告提示框
    void warning();
    CREATE_FUNC(StatusSetLayer);
    
private:
    WDSprite *fog;
    WDSprite *bloodBar;
    WDSprite *warningFrame;
    SpriteBatchNode *batchNode;
};


#endif /* SingleGameScene_hpp */










































