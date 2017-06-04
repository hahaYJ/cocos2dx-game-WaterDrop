//
//  WDSprite.cpp
//  WaterDrop
//
//  Created by hahaYXXXJ on 2017/5/6.
//
//

#include "WDSprite.h"
USING_NS_CC;

#define TOUCH_RANGE_INCREMENT 8 // 扩大触摸范围

void WDSprite::setSize(const cocos2d::Size & size)
{
    this->setScale(size.width / this->getContentSize().width, size.height / this->getContentSize().height);
}

void WDSprite::setEventListenerTouchOneByOne(wdTouchOneByOneCallback onTouch) {
    auto singleListener = EventListenerTouchOneByOne::create();
    singleListener->setSwallowTouches(true);
    singleListener->onTouchBegan = [onTouch](Touch* touch, Event* event) {
        auto target = (WDSprite*) (event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width + TOUCH_RANGE_INCREMENT, s.height + TOUCH_RANGE_INCREMENT);
        if (rect.containsPoint(locationInNode)) {
            onTouch(target, TouchStatus::TOUCHBEGAN);
            return true;
        }
        return false;
    };
    singleListener->onTouchEnded = [onTouch](Touch* touch, Event* event) {
        auto target = (WDSprite*) (event->getCurrentTarget());
        onTouch(target, TouchStatus::TOUCHENDED);
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(singleListener, this);
}

const Rect& WDSprite::transformTextureRect(cocos2d::Rect& rect) {
    auto scaleFactor = Director::getInstance()->getContentScaleFactor(); // 通过比例转换纹理坐标
    rect.origin.x = rect.origin.x / scaleFactor;
    rect.origin.y = rect.origin.y / scaleFactor;
    rect.size.width = rect.size.width / scaleFactor;
    rect.size.height = rect.size.height / scaleFactor;
    return rect;
}

WDSprite* WDSprite::createWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect& rect, bool rotated)
{
    WDSprite *sprite = new (std::nothrow) WDSprite();
    if (sprite && sprite->initWithTexture(texture, rect, rotated))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

WDSprite* WDSprite::createWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect& rect)
{
    auto scaleFactor = Director::getInstance()->getContentScaleFactor(); // 通过比例转换纹理坐标
    return createWithTexture(texture, Rect(rect.origin.x / scaleFactor, rect.origin.y / scaleFactor, rect.size.width / scaleFactor, rect.size.height / scaleFactor), false);
}

WDSprite* WDSprite::create(const std::string& filename, const Rect& rect)
{
    auto scaleFactor = Director::getInstance()->getContentScaleFactor(); // 通过比例转换纹理坐标
    WDSprite *sprite = new (std::nothrow) WDSprite();
    if (sprite && sprite->initWithFile(filename, Rect(rect.origin.x / scaleFactor, rect.origin.y / scaleFactor, rect.size.width / scaleFactor, rect.size.height / scaleFactor)))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void WDSprite::setTextureRect(float x, float y, float width, float height) {
    Sprite::setTextureRect(WDSprite::transformTextureRect(*(new Rect(x, y, width, height))));
}


////////////////////////////////////////////////////////////////////////////
//
// BlurSprite 毛玻璃精灵
//
////////////////////////////////////////////////////////////////////////////



BlurSprite *BlurSprite::createWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect& rect) {
    auto scaleFactor = Director::getInstance()->getContentScaleFactor(); // 通过比例转换纹理坐标
    auto ret = new (std::nothrow) BlurSprite;
    if(ret && ret->initWithTexture(texture, Rect(rect.origin.x / scaleFactor, rect.origin.y / scaleFactor, rect.size.width / scaleFactor, rect.size.height / scaleFactor))) {
        ret->initGLProgramState("shaders/example_Blur.fsh", rect.size);
        ret->autorelease();
        return ret;
    }
    CC_SAFE_RELEASE(ret);
    return nullptr;
}

void BlurSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    _trianglesCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, _polyInfo.triangles, transform, flags);
    renderer->addCommand(&_trianglesCommand);
}

void BlurSprite::initGLProgramState(const std::string &fragmentFilename, const Size &size) {
    auto fileUtiles = FileUtils::getInstance();
    auto fragmentFullPath = fileUtiles->fullPathForFilename(fragmentFilename);
    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
    auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
    auto glprogramstate = (glprogram == nullptr ? nullptr : GLProgramState::getOrCreateWithGLProgram(glprogram));
    glprogramstate->setUniformVec2("resolution", this->getTexture()->getContentSizeInPixels());
    glprogramstate->setUniformFloat("blurRadius", 10.0f);
    glprogramstate->setUniformFloat("sampleNum", 5.0f);
    this->setGLProgramState(glprogramstate);
}



























