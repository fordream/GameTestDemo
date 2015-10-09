//
//  GameScene.hpp
//  GameTestDemo
//
//  Created by zhuyongqing on 15/9/26.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"
#include "CardSprite.hpp"

#define CCRANDOM_0_1() ((float)rand()/RAND_MAX)

typedef enum{
    kTouchStateLeft = 1,
    kTouchStateRight,
    kTouchStateUp,
    kTouchStateDown,
    
}TouchState;

class GameScene:public::cocos2d::Layer
{
    
    int score;
    bool isTouchMoved;
    TouchState state;
    cocos2d::Label* cardNumberTTF;
    cocos2d::Vector<CardSprite *>cardArr;
    
    cocos2d::Point nowP,lastP;
    
    cocos2d::Point prePos;   //起点位置
    cocos2d::Point curPos;   //当前点位置
    float moveDistance;
    
public:
    static cocos2d::Scene* creatScene();
    
    virtual bool init();
    
    void onPause(cocos2d::Ref* sender);
    
    void createCardSprite(cocos2d::Size size);
    
    void createCardNumber();
    
    virtual bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
    
    bool doLeft();
    
    void doCheck();
    
    bool doRight();
    
    void funCallback(float dt);
    
    void doUp();
    
    void doDown();
    
    void setScore();
    
    void rightOrleft(int y,int x, int x1);
    
    CREATE_FUNC(GameScene)
};




#endif