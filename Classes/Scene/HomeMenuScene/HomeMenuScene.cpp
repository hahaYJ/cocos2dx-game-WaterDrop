//
//  HomeScene.cpp
//  SimpleGame
//
//  Created by hahaYXXXJ on 2017/5/3.
//
//

#include "HomeMenuScene.h"
#include "ui/CocosGUI.h"
#include "RuleHelpScene.h"
USING_NS_CC;

#define TIME_INTERLUDE 0.5 // 过场时间
#define SPRITE_NAME_SINGLEBTN "singleBtn"
#define SPRITE_NAME_HELPBTN "helpBtn"

Scene* HomeMenu::createScene()
{
    return HomeMenu::create();
}

void HomeMenu::enterSprites() {    
    // 生成批量精灵
    auto batchNode = SpriteBatchNode::create("home.png", 17);
    this->addChild(batchNode);
    
    // 太阳
    auto sunshine = WDSprite::createWithTexture(batchNode->getTexture(), Rect(512, 0, 512, 512));
    sunshine->setAnchorPoint(Vec2(0, 0));
    sunshine->setPosition(Vec2(originX, originY - 80));
    sunshine->setSize(Size(visibleW, visibleW));
    batchNode->addChild(sunshine);
    sunshine->runAction(MoveTo::create(TIME_INTERLUDE, Vec2(originX, originY)));

    // ☁️
    auto cloudW1 = visibleW / 5;
    auto cloudLastPos = Vec2(-cloudW1, visibleH / 20 * 18);
    auto cloud1 = WDSprite::createWithTexture(batchNode->getTexture(), Rect(768, 576, 128, 64));
    cloud1->setSize(Size(cloudW1, cloudW1 / 2));
    cloud1->setPosition(cloudLastPos);
    batchNode->addChild(cloud1);
    cloud1->runAction(RepeatForever::create(
                                            Spawn::create(
                                                          Sequence::create(
                                                                           MoveTo::create(10, Vec2(visibleW + cloudW1, cloudLastPos.y)),
                                                                           Place::create(cloudLastPos), nullptr),
                                                          Sequence::create(
                                                                           ScaleTo::create(2, cloud1->getScaleX(), cloud1->getScaleY() - 0.5f),
                                                                           ScaleTo::create(2, cloud1->getScaleX(), cloud1->getScaleY()),
                                                                           ScaleTo::create(2, cloud1->getScaleX(), cloud1->getScaleY() - 0.5f),
                                                                           ScaleTo::create(2, cloud1->getScaleX(), cloud1->getScaleY()),
                                                                           ScaleTo::create(2, cloud1->getScaleX(), cloud1->getScaleY() - 0.5f),
                                                                           nullptr),
                                                          NULL)));
    
    auto cloudW2 = visibleW / 7;
    auto cloudLastPos2 = Vec2(-cloudW2, visibleH / 20 * 17);
    auto cloud2 = WDSprite::createWithTexture(batchNode->getTexture(), Rect(768, 640, 128, 64));
    cloud2->setSize(Size(cloudW2, cloudW2 / 2));
    cloud2->setPosition(cloudLastPos);
    batchNode->addChild(cloud2);
    cloud2->runAction(RepeatForever::create(Spawn::create(
                                                          Sequence::create(
                                                                           DelayTime::create(2),
                                                                           MoveTo::create(11, Vec2(visibleW + cloudW2, cloudLastPos.y)),
                                                                           Place::create(cloudLastPos), nullptr),
                                                          Sequence::create(
                                                                           ScaleTo::create(2, cloud2->getScaleX(), cloud2->getScaleY() - 0.5f),
                                                                           ScaleTo::create(2, cloud2->getScaleX(), cloud2->getScaleY()),
                                                                           ScaleTo::create(2, cloud2->getScaleX(), cloud2->getScaleY() - 0.5f),
                                                                           ScaleTo::create(2, cloud2->getScaleX(), cloud2->getScaleY()),
                                                                           ScaleTo::create(2, cloud2->getScaleX(), cloud2->getScaleY() - 0.5f),
                                                                           ScaleTo::create(2, cloud2->getScaleX(), cloud2->getScaleY()),
                                                                           nullptr),
                                                          NULL)));

    
    // 左草地
    auto grasslandLW = visibleW / 3 + 50;
    auto grasslandL = WDSprite::createWithTexture(batchNode->getTexture(), Rect(0, 512, 512, 256));
    grasslandL->setAnchorPoint(Vec2(0, 0));
    grasslandL->setPosition(Vec2(-grasslandLW, originY));
    grasslandL->setSize(Size(grasslandLW, grasslandLW / 2));
    batchNode->addChild(grasslandL);
    grasslandL->runAction(MoveTo::create(TIME_INTERLUDE, Vec2(originX, originY)));
    
    // 右草地
    auto grasslandRW = visibleW / 3 * 2;
    auto grasslandR = WDSprite::createWithTexture(batchNode->getTexture(), Rect(0, 0, 512, 512));
    grasslandR->setAnchorPoint(Vec2(1, 0));
    grasslandR->setPosition(Vec2(visibleW + grasslandRW, originY));
    grasslandR->setSize(Size(grasslandRW, grasslandRW));
    batchNode->addChild(grasslandR);
    grasslandR->runAction(MoveTo::create(TIME_INTERLUDE, Vec2(visibleW, originY)));
    
    // logo
    auto lastPos = Vec2(visibleW / 2, visibleH / 2);
    auto logo = WDSprite::createWithTexture(batchNode->getTexture(), Rect(0, 768, 512, 256));
    logo->setAnchorPoint(Vec2(0.75, 0.15));
    logo->setPosition(Vec2(lastPos.x, visibleH));
    auto logoW = visibleW / 5 * 3;
    logo->setSize(Size(logoW, logoW / 2));
    batchNode->addChild(logo);
    logo->runAction(MoveTo::create(TIME_INTERLUDE, lastPos));
    
    // 排名
    auto rankingW = visibleW / 7;
    auto ranking = WDSprite::createWithTexture(batchNode->getTexture(), Rect(512, 576, 128, 128));
    ranking->setSize(Size(rankingW, rankingW));
    ranking->setAnchorPoint(Vec2(0, 0));
    ranking->setPosition(Vec2(visibleW / 7, visibleH / 9));
    ranking->setVisible(false);
    batchNode->addChild(ranking);
    ranking->runAction(Sequence::create(DelayTime::create(TIME_INTERLUDE), Show::create(), nullptr));
    this->addEventListenerTouchOneByOne(ranking,
                                        Rect(640, 576, 128, 128),
                                        Rect(512, 576, 128, 128));
    // 小蓝💧
    auto dropW = visibleW / 15;
    auto dropSize = Size(dropW, dropW);
    auto drop = WDSprite::createWithTexture(batchNode->getTexture(), Rect(512, 704, 64, 64));
    drop->setSize(dropSize);
    drop->setVisible(false);
    drop->setAnchorPoint(Vec2(0, 0));
    drop->setPosition(Vec2(ranking->getPosition().x - dropW, ranking->getPosition().y));
    batchNode->addChild(drop);
    // 添加关键帧
    auto dropAnimation = Animation::create();
    dropAnimation->addSpriteFrameWithTexture(batchNode->getTexture(), TransformTextureRect(512, 704, 64, 64));
    dropAnimation->addSpriteFrameWithTexture(batchNode->getTexture(), TransformTextureRect(576, 704, 64, 64));
    dropAnimation->setDelayPerUnit(1.0f);
    dropAnimation->setRestoreOriginalFrame(true);
    dropAnimation->setLoops(-1);
    drop->runAction(Sequence::create(DelayTime::create(TIME_INTERLUDE), Show::create(), Animate::create(dropAnimation), nullptr));

    // 小黄💧
    auto dropYW = visibleW / 15;
    auto dropY = WDSprite::createWithTexture(batchNode->getTexture(), Rect(768, 704, 64, 64));
    dropY->setSize(Size(dropYW, dropYW));
    dropY->setVisible(false);
    dropY->setAnchorPoint(Vec2(0, 0));
    dropY->setPosition(Vec2(ranking->getPosition().x + rankingW, ranking->getPosition().y));
    batchNode->addChild(dropY);
    // 添加关键帧
    auto dropYAnimation = Animation::create();
    dropYAnimation->addSpriteFrameWithTexture(batchNode->getTexture(), TransformTextureRect(768, 704, 64, 64));
    dropYAnimation->addSpriteFrameWithTexture(batchNode->getTexture(), TransformTextureRect(832, 704, 64, 64));
    dropYAnimation->setDelayPerUnit(0.7f);
    dropYAnimation->setRestoreOriginalFrame(true);
    dropYAnimation->setLoops(-1);
    dropY->runAction(Sequence::create(DelayTime::create(TIME_INTERLUDE), Show::create(), Animate::create(dropYAnimation), nullptr));
    
    // 小红💧
    auto dropRW = visibleW / 15;
    auto dropR = WDSprite::createWithTexture(batchNode->getTexture(), Rect(640, 704, 64, 64));
    dropR->setSize(Size(dropRW, dropRW));
    dropR->setVisible(false);
    dropR->setPosition(Vec2(ranking->getPosition().x + rankingW / 2, ranking->getPosition().y + rankingW));
    batchNode->addChild(dropR);
    // 添加关键帧
    auto dropRAnimation = Animation::create();
    dropRAnimation->addSpriteFrameWithTexture(batchNode->getTexture(), TransformTextureRect(640, 704, 64, 64));
    dropRAnimation->addSpriteFrameWithTexture(batchNode->getTexture(), TransformTextureRect(704, 704, 64, 64));
    dropRAnimation->setDelayPerUnit(0.6f);
    dropRAnimation->setRestoreOriginalFrame(true);
    dropRAnimation->setLoops(-1);
    dropR->runAction(Sequence::create(DelayTime::create(TIME_INTERLUDE), Show::create(), Animate::create(dropRAnimation), nullptr));
    
    // 单人模式
    auto singleBtnW = visibleW / 6.5;
    auto singleBtn = WDSprite::createWithTexture(batchNode->getTexture(), Rect(512, 768, 128, 64));
    singleBtn->setAnchorPoint(Vec2(0, 0));
    singleBtn->setVisible(false);
    singleBtn->setSize(Size(singleBtnW, singleBtnW / 2));
    singleBtn->setPosition(visibleW / 3 * 2.1, visibleH / 2 * 1.2);
    batchNode->addChild(singleBtn);
    singleBtn->setName(SPRITE_NAME_SINGLEBTN);
    singleBtn->runAction(Sequence::create(DelayTime::create(TIME_INTERLUDE), Show::create(), nullptr));
    this->addEventListenerTouchOneByOne(singleBtn,
                                        Rect(640, 768, 128, 64),
                                        Rect(512, 768, 128, 64));

    // 同屏对战
    auto multiplayerBtnW = visibleW / 6.5;
    auto multiplayerBtn = WDSprite::createWithTexture(batchNode->getTexture(), Rect(512, 832, 128, 64));
    multiplayerBtn->setAnchorPoint(Vec2(0, 0));
    multiplayerBtn->setVisible(false);
    multiplayerBtn->setRotation(15);
    multiplayerBtn->setSize(Size(multiplayerBtnW, multiplayerBtnW / 2));
    multiplayerBtn->setPosition(visibleW / 3 * 2.2, visibleH / 2 * 0.7);
    batchNode->addChild(multiplayerBtn);
    multiplayerBtn->runAction(Sequence::create(DelayTime::create(TIME_INTERLUDE), Show::create(), nullptr));
    this->addEventListenerTouchOneByOne(multiplayerBtn,
                                        Rect(640, 832, 128, 64),
                                        Rect(512, 832, 128, 64));
    
    // 声音按钮
    auto soundBtnW = visibleW / 15;
    auto soundBtn = WDSprite::createWithTexture(batchNode->getTexture(), Rect(512, 512, 64, 64));
    soundBtn->setVisible(false);
    soundBtn->setAnchorPoint(Vec2(0, 0));
    soundBtn->setSize(Size(soundBtnW, soundBtnW));
    batchNode->addChild(soundBtn);
    soundBtn->setPosition(visibleW / 2, ranking->getPosition().y - soundBtnW / 2);
    soundBtn->runAction(Sequence::create(DelayTime::create(TIME_INTERLUDE), Show::create(), nullptr));
    this->addEventListenerTouchOneByOne(soundBtn,
                                        Rect(576, 512, 64, 64),
                                        Rect(512, 512, 64, 64));
    
    // 帮助按钮
    auto helpBtnW = visibleW / 15;
    auto helpBtn = WDSprite::createWithTexture(batchNode->getTexture(), Rect(640, 512, 64, 64));
    helpBtn->setVisible(false);
    helpBtn->setAnchorPoint(Vec2(0, 0));
    helpBtn->setSize(Size(helpBtnW, helpBtnW));
    helpBtn->setName(SPRITE_NAME_HELPBTN);
    batchNode->addChild(helpBtn);
    helpBtn->setPosition(soundBtn->getPosition().x + soundBtn->getContentSize().width + helpBtnW / 3, soundBtn->getPosition().y + helpBtnW / 2);
    helpBtn->runAction(Sequence::create(DelayTime::create(TIME_INTERLUDE), Show::create(), nullptr));
    this->addEventListenerTouchOneByOne(helpBtn,
                                        Rect(704, 512, 64, 64),
                                        Rect(640, 512, 64, 64));
    
    // 分享按钮
    auto shareBtnW = visibleW / 15;
    auto shareBtn = WDSprite::createWithTexture(batchNode->getTexture(), Rect(768, 512, 64, 64));
    shareBtn->setVisible(false);
    shareBtn->setAnchorPoint(Vec2(0, 0));
    shareBtn->setSize(Size(shareBtnW, shareBtnW));
    batchNode->addChild(shareBtn);
    shareBtn->setPosition(helpBtn->getPosition().x + helpBtn->getContentSize().width + shareBtnW / 3, soundBtn->getPosition().y);
    shareBtn->runAction(Sequence::create(DelayTime::create(TIME_INTERLUDE), Show::create(), nullptr));
    this->addEventListenerTouchOneByOne(shareBtn,
                                        Rect(832, 512, 64, 64),
                                        Rect(768, 512, 64, 64));
}

void HomeMenu::onTouchOneByOneHandle(WDSprite* sprite, WDSprite::TouchStatus touchStatus) {
    if(sprite->getName() == SPRITE_NAME_SINGLEBTN)
        Director::getInstance()->replaceScene(TransitionMoveInR::create(0.5, RuleHelp::createScene(RuleHelpSceneStyle::SINGLEGAME)));
    else if(sprite->getName() == SPRITE_NAME_HELPBTN)
        Director::getInstance()->replaceScene(TransitionMoveInR::create(0.5, RuleHelp::createScene(RuleHelpSceneStyle::ONLYHELP)));
}




























