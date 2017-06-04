//
//  RuleHelpScene.hpp
//  WaterDrop
//
//  Created by hahaYXXXJ on 2017/5/10.
//
//

#ifndef RuleHelpScene_hpp
#define RuleHelpScene_hpp
USING_NS_CC;

#include "cocos2d.h"
#include "BaseScene.h"

class RuleHelpPhotoAlbum;

enum class RuleHelpSceneStyle
{
    ONLYHELP,
    SINGLEGAME
};

class RuleHelp : public BaseScene
{
public:
    RuleHelpSceneStyle _sceneStyle;
    bool init(RuleHelpSceneStyle style);
    static cocos2d::Scene* createScene(RuleHelpSceneStyle style);
    
private:
    RuleHelpPhotoAlbum* _photoAlbum;
    
    virtual void enterSprites();
    void onTouchOneByOneHandle(WDSprite* sprite, WDSprite::TouchStatus touchStatus);
    
};

class RuleHelpPhotoAlbum : public cocos2d::Layer
{
private:
    int _currentGroupIndex;
    int _currentPhotoIndex;
    int _totalGroup;
    Vector<WDSprite*> _vec1;
    Vector<WDSprite*> _vec2;
    Vector<WDSprite*> _vec3;
    void initPhotoAlbum();

public:
    virtual bool init();
    static RuleHelpPhotoAlbum* createRuleHelpPhotoAlbum(const Vec2& position, const Size & size);
    CREATE_FUNC(RuleHelpPhotoAlbum);

    void selectGroup(int groupIndex);
    void nextPhoto();
    void forwardPhoto();
};

#endif /* RuleHelpScene_hpp */





































