//
//  Macros.h
//  WaterDrop
//
//  Created by hahaYXXXJ on 2017/5/10.
//
//

#ifndef Macros_h
#define Macros_h

// 是否启用调试标记
#define IsDebug              1
#define IfDebug              if(IsDebug)
#define Debug(format, ...)   if(IsDebug) cocos2d::log(format, ##__VA_ARGS__)

// 通过比例转换纹理坐标
#define TransformTextureRect(x, y, w, h) WDSprite::transformTextureRect(*(new Rect(x, y, w, h)))

#endif /* Macros_h */
