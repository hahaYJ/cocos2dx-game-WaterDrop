//
//  BaseScene.cpp
//  WaterDrop
//
//  Created by hahaYXXXJ on 2017/5/6.
//
//

#include "BaseScene.h"
USING_NS_CC;


bool BaseScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto winSizeInPixels = Director::getInstance()->getWinSizeInPixels();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    IfDebug {
        log("WinSizeInPixels->W:%f H:%f", winSizeInPixels.width, winSizeInPixels.height);
        log("VisibleOrigin->X:%f Y:%f", origin.x, origin.y);
        log("VisibleSize->W:%f H:%f", visibleSize.width, visibleSize.height);
    }
    
    visibleW = origin.x + visibleSize.width;
    visibleH = origin.y + visibleSize.height;
    originX = origin.x;
    originY = origin.y;

    this->enterSprites();
    return true;
}

void BaseScene::addEventListenerTouchOneByOne(WDSprite* target,
                                             const cocos2d::Rect& textureRectTouchBegan,
                                             const cocos2d::Rect& textureRectTouchEnded) {
    target->setEventListenerTouchOneByOne( [this, textureRectTouchBegan, textureRectTouchEnded] (WDSprite* sprite, WDSprite::TouchStatus touchStatus) {
        if (touchStatus == WDSprite::TouchStatus::TOUCHBEGAN) {
            sprite->setTextureRect(textureRectTouchBegan.origin.x, textureRectTouchBegan.origin.y,
                                   textureRectTouchBegan.size.width, textureRectTouchBegan.size.height);
        } else if (touchStatus == WDSprite::TouchStatus::TOUCHENDED) {
            sprite->setTextureRect(textureRectTouchEnded.origin.x, textureRectTouchEnded.origin.y,
                                   textureRectTouchEnded.size.width, textureRectTouchEnded.size.height);
            this->onTouchOneByOneHandle(sprite, touchStatus);
        }
    });
}

void BaseScene::addEventListenerTouchOneByOne(WDSprite* target,
                                              const cocos2d::Rect& textureRectTouchBegan,
                                              const cocos2d::Rect& textureRectTouchEnded,
                                              std::function<void(WDSprite* sprite)> callback) {
    target->setEventListenerTouchOneByOne( [this, textureRectTouchBegan, textureRectTouchEnded, callback] (WDSprite* sprite, WDSprite::TouchStatus touchStatus) {
        if (touchStatus == WDSprite::TouchStatus::TOUCHBEGAN) {
            sprite->setTextureRect(textureRectTouchBegan.origin.x, textureRectTouchBegan.origin.y,
                                   textureRectTouchBegan.size.width, textureRectTouchBegan.size.height);
        } else if (touchStatus == WDSprite::TouchStatus::TOUCHENDED) {
            sprite->setTextureRect(textureRectTouchEnded.origin.x, textureRectTouchEnded.origin.y,
                                   textureRectTouchEnded.size.width, textureRectTouchEnded.size.height);
            callback(sprite);
        }
    });
}



