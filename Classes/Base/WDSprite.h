//
//  WDSprite.hpp
//  WaterDrop
//
//  Created by hahaYXXXJ on 2017/5/6.
//
//

#ifndef WDSprite_hpp
#define WDSprite_hpp

#include "cocos2d.h"

class WDSprite : public cocos2d::Sprite
{
public:
    enum class TouchStatus
    {
        TOUCHBEGAN,
        TOUCHENDED
    };
    
    typedef std::function<void(WDSprite*, TouchStatus)> wdTouchOneByOneCallback;

    void setSize(const cocos2d::Size & size);
    void setEventListenerTouchOneByOne(wdTouchOneByOneCallback onTouch);
    
    static const cocos2d::Rect& transformTextureRect(cocos2d::Rect& rect);
    static WDSprite* createWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect& rect, bool rotated);
    static WDSprite* createWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect& rect);
    static WDSprite* create(const std::string& filename, const cocos2d::Rect& rect);
    
    void setTextureRect(float x, float y, float width, float height);
};

////////////////////////////////////////////////////////////////////////////
//
// BlurSprite 毛玻璃精灵
//
////////////////////////////////////////////////////////////////////////////


class BlurSprite : public WDSprite {
    
public:
    static BlurSprite *createWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect& rect);
    
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    
    void initGLProgramState(const std::string &fragmentFilename, const cocos2d::Size &size);
    
};

#endif /* WDSprite_hpp */
