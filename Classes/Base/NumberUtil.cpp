//
//  NumberUtil.cpp
//  WaterDrop
//
//  Created by hahaYXXXJ on 2017/5/26.
//
//

#include "NumberUtil.h"
#include "Macros.h"
#include "WDSprite.h"

static NumberUtil *_instance = nullptr;

NumberUtil::NumberUtil() {
    Director::getInstance()->getTextureCache()->addImage("number1.png");
}

NumberUtil::~NumberUtil() {
    CC_SAFE_RELEASE_NULL(_batchNode);
    Director::getInstance()->getTextureCache()->removeTextureForKey("number1.png");
}

NumberUtil* NumberUtil::getInstance() {
    if (_instance == NULL) {
        _instance = new NumberUtil();
        CC_SAFE_RETAIN(_instance);
    }
    return _instance;
}

void NumberUtil::releaseInstance() {
    CC_SAFE_RELEASE_NULL(_instance);
}

/// 显示红色分数
SpriteBatchNode* NumberUtil::showScoresRed(unsigned int scores) {
    return this->showScoresRed(scores, Size(16, 16));
}

/// 显示红色分数
SpriteBatchNode* NumberUtil::showScoresRed(unsigned int scores, const Size& singleNumberSize) {
    if (_batchNode == NULL) {
        _batchNode = SpriteBatchNode::createWithTexture(Director::getInstance()->getTextureCache()->addImage("number1.png"), 10);
        CC_SAFE_RETAIN(_batchNode);
    }
    auto scoresStr = Value(scores).asString();
    auto len = scoresStr.length();
    for (int i=0;i<len;++i) {
        auto v = scoresStr[i] - 48; // ascII 对应关系
        auto number = _batchNode->getChildByTag(i);
        if (number == NULL) {
            auto number = WDSprite::createWithTexture(_batchNode->getTexture(), Rect(v * 32, 0, 32, 32));
            number->setSize(singleNumberSize);
            number->setAnchorPoint(Vec2(0, 0));
            number->setPosition(Vec2(i * singleNumberSize.width, 0));
            number->setTag(i);
            _batchNode->addChild(number);
        } else {
            ((WDSprite *) number)->setTextureRect(v * 32, 0, 32, 32);
        }
    }
    _batchNode->setContentSize(Size(singleNumberSize.width * len, singleNumberSize.height));
    return _batchNode;
}

/// 显示黄色分数
SpriteBatchNode* NumberUtil::showScoresYellow(unsigned int scores, const Size& singleNumberSize) {
    if (_batchNode == NULL) {
        _batchNode = SpriteBatchNode::createWithTexture(Director::getInstance()->getTextureCache()->addImage("number1.png"), 10);
        CC_SAFE_RETAIN(_batchNode);
    }
    auto scoresStr = Value(scores).asString();
    auto len = scoresStr.length();
    for (int i=0;i<len;++i) {
        auto v = scoresStr[i] - 48; // ascII 对应关系
        auto number = _batchNode->getChildByTag(i);
        if (number == NULL) {
            auto number = WDSprite::createWithTexture(_batchNode->getTexture(), Rect(v * 32, 32, 32, 32));
            number->setSize(singleNumberSize);
            number->setAnchorPoint(Vec2(0, 0));
            number->setPosition(Vec2(i * singleNumberSize.width, 0));
            number->setTag(i);
            _batchNode->addChild(number);
        } else {
            ((WDSprite *) number)->setTextureRect(v * 32, 32, 32, 32);
        }
    }
    _batchNode->setContentSize(Size(singleNumberSize.width * len, singleNumberSize.height));
    return _batchNode;
}






























