//
//  NumberUtil.hpp
//  WaterDrop
//
//  Created by hahaYXXXJ on 2017/5/26.
//
//

#ifndef NumberUtil_hpp
#define NumberUtil_hpp

USING_NS_CC;

#include "cocos2d.h"

class NumberUtil : public Ref {
    
private:
    SpriteBatchNode *_batchNode;
    
public:
    
    static NumberUtil* getInstance();
    
    static void releaseInstance();
    
    NumberUtil();
    ~NumberUtil();
    
    /// 显示红色分数
    SpriteBatchNode* showScoresRed(unsigned int scores, const Size& singleNumberSize);
    
    /// 显示红色分数
    SpriteBatchNode* showScoresRed(unsigned int scores);
    
    /// 显示黄色分数
    SpriteBatchNode* showScoresYellow(unsigned int scores, const Size& singleNumberSize);
};

#endif /* NumberUtil_hpp */
