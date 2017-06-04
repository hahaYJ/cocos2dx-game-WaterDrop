//
//  RuleHelpScene.cpp
//  WaterDrop
//
//  Created by hahaYXXXJ on 2017/5/10.
//
//

#include "RuleHelpScene.h"
#include "HomeMenuScene.h"
#include "SingleGameScene.h"

#define SPRITE_NAME_HOMEBTN "HomeBtn"
#define SPRITE_NAME_ARROWSBTNL "arrowsBtnL"
#define SPRITE_NAME_ARROWSBTNR "arrowsBtnR"
#define SPRITE_NAME_STARTGAME "startGame"
#define SPRITE_NAME_OPERATIONTAG "operationTag"
#define SPRITE_NAME_HANDBOOKTAG "handbookTag"
#define SPRITE_NAME_PROPSTAG "propsTag"

Scene* RuleHelp::createScene(RuleHelpSceneStyle style)
{
    RuleHelp *pRet = new(std::nothrow) RuleHelp();
    if (pRet && pRet->init(style))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr; 
    }
}

bool RuleHelp::init(RuleHelpSceneStyle style) {
    this->_sceneStyle = style;
    return BaseScene::init();
}

void RuleHelp::enterSprites() {
    // 生成批量精灵
    auto batchNode = SpriteBatchNode::create("help.png", 10);
    this->addChild(batchNode);

    // 背景
    auto bg = WDSprite::createWithTexture(batchNode->getTexture(), Rect(0, 0, 880, 512));
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(Vec2(originX, originY));
    bg->setSize(Size(visibleW, visibleH));
    batchNode->addChild(bg);
    
    // 返回主页
    auto homeW = visibleW / 13;
    auto homeWF = homeW / 2;
    auto home = WDSprite::createWithTexture(batchNode->getTexture(), Rect(880, 256, 64, 64));
    home->setAnchorPoint(Vec2(0, 0));
    home->setPosition(Vec2(originX + homeWF, visibleH - homeW - homeWF));
    home->setSize(Size(homeW, homeW));
    home->setName(SPRITE_NAME_HOMEBTN);
    batchNode->addChild(home);
    this->addEventListenerTouchOneByOne(home,
                                        Rect(944, 256, 64, 64),
                                        Rect(880, 256, 64, 64));
    
    // 左箭头
    auto arrowsLW = visibleW / 10;
    auto arrowsL = WDSprite::createWithTexture(batchNode->getTexture(), Rect(880, 0, 64, 64));
    arrowsL->setPosition(Vec2(originX + arrowsLW, visibleH / 2));
    arrowsL->setSize(Size(arrowsLW, arrowsLW));
    arrowsL->setName(SPRITE_NAME_ARROWSBTNL);
    batchNode->addChild(arrowsL);
    this->addEventListenerTouchOneByOne(arrowsL,
                                        Rect(944, 0, 64, 64),
                                        Rect(880, 0, 64, 64));
    
    // 右箭头
    auto arrowRW = visibleW / 10;
    auto arrowsR = WDSprite::createWithTexture(batchNode->getTexture(), Rect(880, 64, 64, 64));
    arrowsR->setPosition(Vec2(visibleW - arrowRW, visibleH / 2));
    arrowsR->setSize(Size(arrowRW, arrowRW));
    arrowsR->setName(SPRITE_NAME_ARROWSBTNR);
    batchNode->addChild(arrowsR);
    this->addEventListenerTouchOneByOne(arrowsR,
                                        Rect(944, 64, 64, 64),
                                        Rect(880, 64, 64, 64));
    
    // 单人游戏 开始按钮
    if (_sceneStyle == RuleHelpSceneStyle::SINGLEGAME) {
        auto startGameW = visibleW / 4;
        auto startGame = WDSprite::createWithTexture(batchNode->getTexture(), Rect(880, 128, 144, 64));
        startGame->setSize(Size(startGameW, startGameW / 2));
        startGame->setPosition(Vec2(visibleW / 2, originY + startGame->getContentSize().height));
        startGame->setName(SPRITE_NAME_STARTGAME);
        batchNode->addChild(startGame);
        this->addEventListenerTouchOneByOne(startGame,
                                            Rect(880, 192, 144, 64),
                                            Rect(880, 128, 144, 64));
    }
    
    // 图鉴
    auto handbookW = visibleW / 10;
    auto handbookTag = WDSprite::createWithTexture(batchNode->getTexture(), Rect(896, 384, 64, 64));
    handbookTag->setSize(Size(handbookW, handbookW));
    handbookTag->setPosition(Vec2(visibleW / 2, visibleH * 0.9));
    handbookTag->setName(SPRITE_NAME_HANDBOOKTAG);
    batchNode->addChild(handbookTag);
    this->addEventListenerTouchOneByOne(handbookTag,
                                        Rect(960, 384, 64, 64),
                                        Rect(896, 384, 64, 64));
    
    // 操作
    auto operationTag = WDSprite::createWithTexture(batchNode->getTexture(), Rect(896, 320, 64, 64));
    operationTag->setSize(Size(handbookW, handbookW));
    operationTag->setPosition(Vec2(handbookTag->getPosition().x - handbookW - 20, handbookTag->getPosition().y));
    operationTag->setName(SPRITE_NAME_OPERATIONTAG);
    batchNode->addChild(operationTag);
    this->addEventListenerTouchOneByOne(operationTag,
                                        Rect(960, 320, 64, 64),
                                        Rect(896, 320, 64, 64));
    
    // 道具
    auto propsTag = WDSprite::createWithTexture(batchNode->getTexture(), Rect(896, 448, 64, 64));
    propsTag->setSize(Size(handbookW, handbookW));
    propsTag->setPosition(Vec2(handbookTag->getPosition().x + handbookW + 20, handbookTag->getPosition().y));
    propsTag->setName(SPRITE_NAME_PROPSTAG);
    batchNode->addChild(propsTag);
    this->addEventListenerTouchOneByOne(propsTag,
                                        Rect(960, 448, 64, 64),
                                        Rect(896, 448, 64, 64));
    
    auto photoAlbumH = visibleH * 0.65;
    _photoAlbum = RuleHelpPhotoAlbum::createRuleHelpPhotoAlbum(Vec2(visibleW / 2, visibleH / 2), Size(photoAlbumH * 1.72, photoAlbumH));
    this->addChild(_photoAlbum);
}

void RuleHelp::onTouchOneByOneHandle(WDSprite* sprite, WDSprite::TouchStatus touchStatus) {
    auto spriteName = sprite->getName();
    if(spriteName == SPRITE_NAME_HOMEBTN)
        Director::getInstance()->replaceScene(TransitionMoveInL::create(0.5, HomeMenu::createScene()));
    else if(spriteName == SPRITE_NAME_OPERATIONTAG)
        _photoAlbum->selectGroup(1);
    else if(spriteName == SPRITE_NAME_HANDBOOKTAG)
        _photoAlbum->selectGroup(2);
    else if(spriteName == SPRITE_NAME_PROPSTAG)
        _photoAlbum->selectGroup(3);
    else if(spriteName == SPRITE_NAME_ARROWSBTNL)
        _photoAlbum->forwardPhoto();
    else if(spriteName == SPRITE_NAME_ARROWSBTNR)
        _photoAlbum->nextPhoto();
    else if(spriteName == SPRITE_NAME_STARTGAME)
        Director::getInstance()->replaceScene(TransitionMoveInR::create(0.5, SingleGame::createScene()));
}


//////////////////////////////////////////////////////////////////////////////////
//
// RuleHelpPhotoAlbum
//
//////////////////////////////////////////////////////////////////////////////////

RuleHelpPhotoAlbum* RuleHelpPhotoAlbum::createRuleHelpPhotoAlbum(const Vec2& position, const Size & size)
{
    auto album = RuleHelpPhotoAlbum::create();
    album->setPosition(position);
    album->setContentSize(size);
    album->initPhotoAlbum();
    return album;
}


bool RuleHelpPhotoAlbum::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    _currentGroupIndex = 1;
    _currentPhotoIndex = 0;
    _totalGroup = 3;
    _vec1 = Vector<WDSprite*>(1);
    _vec2 = Vector<WDSprite*>(1);
    _vec3 = Vector<WDSprite*>(1);
    return true;
}

void RuleHelpPhotoAlbum::initPhotoAlbum() {
    // 设置第一组
    auto po1 = WDSprite::create("czsm.png", Rect(0, 0, 880, 512));
    po1->setSize(this->getContentSize());
    _vec1.pushBack(po1);
    this->addChild(po1);
    
    // 设置第二组
    auto po2_1 = WDSprite::create("sdsm.png", Rect(0, 0, 880, 512));
    po2_1->setSize(this->getContentSize());
    auto po2_2 = WDSprite::create("pmsd.png", Rect(0, 0, 880, 512));
    po2_2->setSize(this->getContentSize());
    _vec2.pushBack(po2_2);
    _vec2.pushBack(po2_1);

    // 设置第三组
    auto po3 = WDSprite::create("djsm.png", Rect(0, 0, 880, 512));
    po3->setSize(this->getContentSize());
    _vec3.pushBack(po3);
}

void RuleHelpPhotoAlbum::selectGroup(int groupIndex) {
    do {
        CC_BREAK_IF(_currentGroupIndex == groupIndex);
        CC_BREAK_IF(groupIndex > _totalGroup || groupIndex < 1);
        _currentGroupIndex = groupIndex;
        _currentPhotoIndex = 0;
        this->removeAllChildren();
        Vector<WDSprite*> _target;
        if (_currentGroupIndex == 1)
            _target = _vec1;
        else if (_currentGroupIndex == 2)
            _target = _vec2;
        else
            _target = _vec3;
        for(auto sp : _target) {
            sp->setVisible(true);
            this->addChild(sp);
        }
    } while (0);
}

void RuleHelpPhotoAlbum::nextPhoto() {
    Vector<WDSprite*> _target;
    if (_currentGroupIndex == 1)
        _target = _vec1;
    else if (_currentGroupIndex == 2)
        _target = _vec2;
    else
        _target = _vec3;
    
    do {
        auto size =  _target.size();
        CC_BREAK_IF(_currentPhotoIndex + 1 >= size);
        auto lastS = _target.at(_currentPhotoIndex); // 显示现在的
        lastS->setVisible(true);
        _currentPhotoIndex += 1;
        auto nowS = _target.at(_currentPhotoIndex);  // 隐藏之前的
        nowS->setVisible(false);
    } while (0);
}

void RuleHelpPhotoAlbum::forwardPhoto() {
    Vector<WDSprite*> _target;
    if (_currentGroupIndex == 1)
        _target = _vec1;
    else if (_currentGroupIndex == 2)
        _target = _vec2;
    else
        _target = _vec3;
    
    do {
        CC_BREAK_IF(_currentPhotoIndex - 1 < 0);
        auto lastS = _target.at(_currentPhotoIndex); // 显示之前的
        lastS->setVisible(true);
        if (_currentPhotoIndex > 0) {
            _currentPhotoIndex -= 1;
            auto nowS = _target.at(_currentPhotoIndex); // 隐藏现在的
            nowS->setVisible(false);
        }
    } while (0);
}














































