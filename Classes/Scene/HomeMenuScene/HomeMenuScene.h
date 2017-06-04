//
//  HomeScene.hpp
//  SimpleGame
//
//  Created by hahaYXXXJ on 2017/5/3.
//
//

#ifndef HomeScene_hpp
#define HomeScene_hpp

#include "cocos2d.h"
#include "BaseScene.h"

class HomeMenu : public BaseScene
{
public:    
    static cocos2d::Scene* createScene();
    // implement the "static create()" method manually
    CREATE_FUNC(HomeMenu);

private:
    virtual void enterSprites();
    void onTouchOneByOneHandle(WDSprite* sprite, WDSprite::TouchStatus touchStatus);
    
};

#endif /* HomeScene_hpp */
