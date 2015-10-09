//
//  CardSprite.hpp
//  GameTestDemo
//
//  Created by zhuyongqing on 15/9/26.
//
//

#ifndef CardSprite_hpp
#define CardSprite_hpp

#include "cocos2d.h"

class CardSprite:public::cocos2d::Sprite
{

    int number;
    
    cocos2d::LayerColor* colorBackground;
    cocos2d::Label* labelCardNumber;
    
public:
    
    static CardSprite* createCard(int number,int width,int height,float CardSpriteX,float CardSpriteY);
    
    void initCard(int number,int width,int height,float CardSpriteX,float CardSpriteY);
    
    int getNumber();
    
    void setNumber(int num);
    
    void changeBig();
    
    void moved(cocos2d::Point point);
    
    CREATE_FUNC(CardSprite);
};


#endif /* CardSprite_hpp */
