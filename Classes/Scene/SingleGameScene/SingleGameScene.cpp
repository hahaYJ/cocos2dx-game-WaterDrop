//
//  SingleGameScene.cpp
//  WaterDrop
//
//  Created by hahaYXXXJ on 2017/5/12.
//
//

#include "SingleGameScene.h"
#include "HomeMenuScene.h"
#include "NumberUtil.h"

#define BG_TIME_INTERLUDE 1 // 背景过场时间


Scene* SingleGame::createScene()
{
    return SingleGame::create();
}

void SingleGame::enterSprites() {
    Director::getInstance()->getTextureCache()->addImage("rsd.png");
    Director::getInstance()->getTextureCache()->addImage("yxbj.png");
    // bgC
    this->addChild(LayerColor::create(Color4B().WHITE));
    
    // SingleGameBackground
    this->addChild(SingleGameBackground::createSingleGameBackground(Vec2(originX, originY), Size(visibleW, visibleH)));
    
    // StatusSetLayer
    this->addChild(StatusSetLayer::createStatusSetLayer(Vec2(originX, originY), Size(visibleW, visibleH)));

    // SingleGameForegroundground
    auto foregroundground = SingleGameForegroundground::createSingleGameForegroundground(Vec2(originX, originY), Size(visibleW, visibleH));
    this->addChild(foregroundground);
    
    // 暂停
    auto pauseW = visibleW * 0.05;
    auto pauseWH = pauseW * 0.5;
    auto pause = WDSprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("rsd.png"), Rect(960, 0, 64, 64));
    pause->setAnchorPoint(Vec2(0, 0));
    pause->setPosition(Vec2(visibleW - pauseW - pauseWH, visibleH - pauseW - pauseWH));
    pause->setSize(Size(pauseW, pauseW));
    this->addChild(pause);
    this->addEventListenerTouchOneByOne(pause,
                                        Rect(960, 0, 64, 64),
                                        Rect(960, 0, 64, 64),
                                        [foregroundground](WDSprite* sprite) {
                                            foregroundground->showAndHide();
                                        });
}

void SingleGame::onTouchOneByOneHandle(WDSprite* sprite, WDSprite::TouchStatus touchStatus) {
    
}


////////////////////////////////////////////////////////////////////////////
//
// SingleGameBackground
//
////////////////////////////////////////////////////////////////////////////

SingleGameBackground* SingleGameBackground::createSingleGameBackground(const Vec2& position, const Size & size) {
    auto gameBackground = SingleGameBackground::create();
    gameBackground->initGameBackground(position, size);
    return gameBackground;
}

void SingleGameBackground::initGameBackground(const Vec2& position, const Size & size) {
    // 生成批量精灵
    auto batchNode = SpriteBatchNode::createWithTexture(Director::getInstance()->getTextureCache()->addImage("yxbj.png"), 10);
    this->addChild(batchNode);
    
    // bgB
    auto bgBH = size.width * 0.25;
    auto bgB = WDSprite::createWithTexture(batchNode->getTexture(), Rect(0, 0, 512, 128));
    bgB->setAnchorPoint(Vec2(0, 0));
    bgB->setPosition(Vec2(position.x, -bgBH));
    bgB->setSize(Size(size.width, bgBH));
    batchNode->addChild(bgB);
    bgB->runAction(MoveTo::create(BG_TIME_INTERLUDE, Vec2(0, 0)));
    
    // bgT
    auto bgT = WDSprite::createWithTexture(batchNode->getTexture(), Rect(512, 0, 512, 512));
    bgT->setAnchorPoint(Vec2(0, 0));
    bgT->setPosition(position);
    bgT->setSize(Size(size.width, size.width));
    batchNode->addChild(bgT);
    bgT->runAction(MoveTo::create(BG_TIME_INTERLUDE, Vec2(position.x, -size.width + size.height)));
    
}

////////////////////////////////////////////////////////////////////////////
//
// SingleGameBackground 前景层级调用 包括：按钮、分数、成绩等
//
////////////////////////////////////////////////////////////////////////////


SingleGameForegroundground* SingleGameForegroundground::createSingleGameForegroundground(const Vec2& position, const Size & size) {
    auto gameBackground = SingleGameForegroundground::create();
    gameBackground->initGameForegroundground(position, size);
    return gameBackground;
}

void SingleGameForegroundground::initGameForegroundground(const Vec2& position, const Size & size) {
    auto singleGame = (SingleGame *) Director::getInstance()->getRunningScene();
    this->setVisible(false);
    this->setScale(0, 0);
    
    // 生成批量精灵
    auto batchNode = SpriteBatchNode::createWithTexture(Director::getInstance()->getTextureCache()->addImage("rsd.png"), 10);
    
    // 设置毛玻璃背景
    auto bg = BlurSprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("rsd.png"), Rect(0, 768, 448, 256));
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(position);
    bg->setSize(size);
    this->addChild(bg);
    
    std::function<void(WDSprite* sprite)> callback = [this](WDSprite* sprite) {
        auto director = Director::getInstance();
        if (sprite->getName() == "play") {
            director->resume();
            this->showAndHide();
        } else if (sprite->getName() == "reset") {
            director->pause();
            this->showAndHide();
        } else if (sprite->getName() == "exit") {
            director->resume();
            director->replaceScene(TransitionMoveInL::create(0.5, HomeMenu::createScene()));
            director->getEventDispatcher()->removeEventListenersForTarget(sprite);
        } else if (sprite->getName() == "pause") {
            this->setVisible(!this->isVisible());
        }
    };
    
    // 继续
    auto playW = size.width * 0.1;
    auto play = WDSprite::createWithTexture(batchNode->getTexture(), Rect(832, 384, 64, 64));
    play->setPosition(Vec2(size.width / 3, size.height * 0.5));
    play->setSize(Size(playW, playW));
    play->setName("play");
    batchNode->addChild(play);
    singleGame->addEventListenerTouchOneByOne(play,
                                              Rect(896, 384, 64, 64),
                                              Rect(832, 384, 64, 64),
                                              callback);
    
    // 重置
    auto reset = WDSprite::createWithTexture(batchNode->getTexture(), Rect(832, 448, 64, 64));
    reset->setPosition(Vec2(size.width / 2, size.height * 0.5));
    reset->setSize(Size(playW, playW));
    reset->setName("reset");
    batchNode->addChild(reset);
    singleGame->addEventListenerTouchOneByOne(reset,
                                              Rect(896, 448, 64, 64),
                                              Rect(832, 448, 64, 64),
                                              callback);
    
    // 退出
    auto exit = WDSprite::createWithTexture(batchNode->getTexture(), Rect(832, 512, 64, 64));
    exit->setPosition(Vec2(size.width / 3 * 2, size.height * 0.5));
    exit->setSize(Size(playW, playW));
    exit->setName("exit");
    batchNode->addChild(exit);
    singleGame->addEventListenerTouchOneByOne(exit,
                                              Rect(896, 512, 64, 64),
                                              Rect(832, 512, 64, 64),
                                              callback);
    
    this->addChild(batchNode);
    
}

void SingleGameForegroundground::showAndHide() {
    if (this->isVisible()) { // 消失
        this->runAction(Sequence::create(ScaleTo::create(0.25, 0, 0), Hide::create(), CallFunc::create([](){
            Director::getInstance()->resume();
        }), nullptr));
    } else { // 弹出
        this->setScale(0, 0);
        this->runAction(Sequence::create(Show::create(), ScaleTo::create(0.25, 1, 1), CallFunc::create([](){
            Director::getInstance()->pause();
        }), nullptr));
    }
}



////////////////////////////////////////////////////////////////////////////
//
// StatusBarLayer 显示血量、分数、游戏基本状态集合
//
////////////////////////////////////////////////////////////////////////////


StatusSetLayer* StatusSetLayer::createStatusSetLayer(const Vec2& position, const Size & size) {
    auto statusSetLayer = StatusSetLayer::create();
    statusSetLayer->initStatusSetLayer(position, size);
    return statusSetLayer;
}

void StatusSetLayer::initStatusSetLayer(const Vec2& position, const Size & size) {
    // 生成批量精灵
    batchNode = SpriteBatchNode::createWithTexture(Director::getInstance()->getTextureCache()->addImage("rsd.png"), 10);
    this->addChild(batchNode);

    // 血条
    auto bloodBarH = size.height * 0.8;
    bloodBar = WDSprite::createWithTexture(batchNode->getTexture(), Rect(832, 128, 32, 256));
    bloodBar->setAnchorPoint(Vec2(1, 0));
    bloodBar->setSize(Size(bloodBarH / 8, bloodBarH));
    bloodBar->setPosition(Vec2(size.width - bloodBar->getContentSize().width, size.height * 0.025));
    batchNode->addChild(bloodBar);
    bloodBar->setEventListenerTouchOneByOne([this, size] (WDSprite* sprite, BlurSprite::TouchStatus touchStatus) {
        this->warning();
    });
    
    // 分数
    auto scores = NumberUtil::getInstance()->showScoresRed(3415954680);
    scores->setAnchorPoint(Vec2(0, 1));
    scores->setPosition(Vec2(5, size.height - 5));
    this->addChild(scores);
    
    // 大雾
    fog = WDSprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("yxbj.png"), Rect(0, 256, 512, 256));
    this->addChild(fog);
    fog->setSize(size);
    fog->setAnchorPoint(Vec2(0, 0));
    fog->setVisible(false);
}

// 起雾攻击
void StatusSetLayer::fogAttack() {
    fog->stopAllActions();
    fog->runAction(Sequence::create(Show::create(),
                                    Place::create(Vec2(-fog->getContentSize().width * 2.2, 0)),
                                    Spawn::create(MoveTo::create(10.0f, Vec2(fog->getContentSize().width * 2.2, 0)),
                                                  Sequence::create(FadeTo::create(1.66f, 220),
                                                                   FadeTo::create(1.66f, 255),
                                                                   FadeTo::create(1.66f, 220),
                                                                   FadeTo::create(1.66f, 255),
                                                                   FadeTo::create(1.66f, 220),
                                                                   FadeTo::create(1.66f, 255),
                                                                   NULL),
                                                  NULL),
                                    Hide::create(),
                                    NULL));
}

 // 显示血量
void StatusSetLayer::showBlood(StatusSetLayer::BloodStatus bloodStatus) {
    if (bloodStatus == StatusSetLayer::BloodStatus::BLOOD_CAPACITY_100) {
        bloodBar->setTextureRect(832, 128, 32, 256);
    } else if (bloodStatus == StatusSetLayer::BloodStatus::BLOOD_CAPACITY_75) {
        bloodBar->setTextureRect(864, 128, 32, 256);
    } else if (bloodStatus == StatusSetLayer::BloodStatus::BLOOD_CAPACITY_50) {
        bloodBar->setTextureRect(896, 128, 32, 256);
    } else if (bloodStatus == StatusSetLayer::BloodStatus::BLOOD_CAPACITY_25) {
        bloodBar->setTextureRect(928, 128, 32, 256);
    } else if (bloodStatus == StatusSetLayer::BloodStatus::BLOOD_CAPACITY_0) {
        bloodBar->setTextureRect(960, 128, 32, 256);
    }
}

// 警告提示
void StatusSetLayer::warning() {
    auto cScene = (SingleGame *) Director::getInstance()->getRunningScene();
    if (warningFrame != NULL)
        batchNode->removeChild(warningFrame, true);
    // 警告框
    warningFrame = WDSprite::createWithTexture(batchNode->getTexture(), Rect(512, 768, 220, 128));
    warningFrame->setSize(Size(cScene->visibleW, cScene->visibleH));
    warningFrame->setPosition(Vec2(cScene->visibleW * 0.5, cScene->visibleH * 0.5));
    batchNode->addChild(warningFrame);
    warningFrame->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.25), FadeIn::create(0.25), NULL)));
}




































