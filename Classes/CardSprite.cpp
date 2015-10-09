//
//  CardSprite.cpp
//  GameTestDemo
//
//  Created by zhuyongqing on 15/9/26.
//
//

#include "CardSprite.hpp"
USING_NS_CC;

CardSprite* CardSprite::createCard(int number,int width,int height,float CardSpriteX,float CardSpriteY)
{
    
    auto card = CardSprite::create();
    
    card->initCard(number, width, height, CardSpriteX, CardSpriteY);
    
    return card;
    
}

#pragma mark - 创建方块

void CardSprite::initCard(int number, int width, int height, float CardSpriteX, float CardSpriteY)
{
    this->number = number;
    
    colorBackground = LayerColor::create(Color4B(200,190,180,255), width, height);
    colorBackground->setPosition(Point(CardSpriteX,CardSpriteY));
    
    if (number>0) {
        labelCardNumber = Label::createWithSystemFont(__String::createWithFormat("%i",number)->getCString(), "Consolas",10);
        labelCardNumber -> setPosition(Point(colorBackground->getContentSize().width/2,colorBackground->getContentSize().height/2));
        labelCardNumber->setTag(8);
        colorBackground->addChild(labelCardNumber);
    }
    else
    {
        labelCardNumber = Label::createWithSystemFont("", "Consolas",10);
        labelCardNumber -> setPosition(Point(colorBackground->getContentSize().width/2,colorBackground->getContentSize().height/2));
        labelCardNumber->setTag(8);
        colorBackground->addChild(labelCardNumber);
    }
    this->addChild(colorBackground);
}

int CardSprite::getNumber()
{
    return number;
}

#pragma mark - 设置不同数字的颜色
void CardSprite::setNumber(int num)
{
    number = num;
    
    if (num>0) {
        labelCardNumber->setString(__String::createWithFormat("%i",num)->getCString());
    }
    else
    {
        labelCardNumber->setString("");
    }
    
    if (num>=0) {
        labelCardNumber->setSystemFontSize(50);
    }
    
    if (num >= 1024) {
        labelCardNumber->setSystemFontSize(10);
    }
    
    if (num == 0) {
        colorBackground->setColor(Color3B(200, 190, 180));
    }
    
    if (num > 0) {
        colorBackground->setColor(Color3B(100, 190, 180));
    }
    
    if (num == 2048) {
        colorBackground->setColor(Color3B(0, 130, 0));
    }
}

#pragma mark - 方块的运动

void CardSprite::moved(Point point)
{
//    Point oldP = this->getPosition();
//    auto action1 = MoveTo::create(0.2,Vec2(point.x,point.y));
//    
//    this->runAction(Sequence::create(action1, NULL));
}

void CardSprite::changeBig()
{
//    auto action1 = FadeIn::create(0.2);
//    auto acton2 = ScaleTo::create(0.2, 1.0);
//    
//    this -> runAction(Sequence::create(action1, NULL));
}

