//
//  GameScene.cpp
//  GameTestDemo
//
//  Created by zhuyongqing on 15/9/26.
//
//

#include "GameScene.hpp"
USING_NS_CC;
#define CardArr(num1,num2) cardArr.at(num1*4 + num2)
using namespace std;

Scene* GameScene::creatScene()
{
    auto scene = Scene::create();
    
    auto layer = GameScene::create();
    
    scene -> addChild(layer);
    
    return scene;
}


bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //获得屏幕的size
    Size winSize = Director::getInstance()->getWinSize();
    log("%f , %f",visibleSize.width,visibleSize.height);
    //背景
    auto layerColorBg = LayerColor::create(Color4B(180, 170, 160, 255));
    
    this->addChild(layerColorBg);
    
    //暂停按钮
    MenuItemFont::setFontName("Consolas");
    MenuItemFont::setFontSize(60);
    auto menuItemPause = MenuItemFont::create("PAUSE",CC_CALLBACK_1(GameScene::onPause, this));
    
    auto menu = Menu::create(menuItemPause,NULL);
    this->addChild(menu);
    menu->setPosition(Point(winSize.width-180,visibleSize.height-40));
    
    //分数label
    auto cardNumberTitle = Label::createWithSystemFont("SCORE","Consolas",60);
    
    cardNumberTitle->setPosition(Point(winSize.width-180,visibleSize.height-110));
    this->addChild(cardNumberTitle);
    
    score = 0;
    
    cardNumberTTF = Label::createWithSystemFont("0", "Consolas",60);
    cardNumberTTF->setPosition(Point(winSize.width-180,visibleSize.height-160));
    this->addChild(cardNumberTTF);
    
    //创建4*4 的方块
    createCardSprite(visibleSize);
    
    //放两个带有数字的方块
    
    createCardNumber();
    createCardNumber();
    
    //设置触摸事件
    
    auto  touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

bool GameScene::onTouchBegan(Touch* touch,Event* event)
{

    auto pos = touch->getLocation();
    isTouchMoved = false;
    //保存起始点
    prePos = pos;
    
    scheduleOnce(schedule_selector(GameScene::funCallback), 0.3f);
    
    return true;
}

void GameScene::onTouchMoved(Touch* touch,Event* event)
{
  
    auto pos = touch->getLocation();
    isTouchMoved = true;
    //随时获取当前移动点的位置
    curPos = pos;

}
void GameScene::onTouchEnded(Touch* touch, Event* event)
{
    auto pos = touch->getLocation();
}

void GameScene::funCallback(float dt)
{
    if (!isTouchMoved) {
        return;
    }
    auto sub = Vec2(prePos, curPos);
    //判断水平和垂直方向上哪个偏移量大
    //水平移动
    if (fabs(sub.x) > fabs(sub.y))
    {
        //右滑
        if (sub.x > moveDistance){
            log("right");
            doRight();
            doCheck();
            setScore();
        }
        else
            //左滑
            if (sub.x < -moveDistance){
                log("left");
                doLeft();
                doCheck();
                setScore();
            }
    }
    else
    {
        //上滑
        if (sub.y > moveDistance){
             log("up");
            doUp();
            doCheck();
            setScore();
        }
        else
            //下滑
            if (sub.y < -moveDistance){
                log("down");
                doDown();
                doCheck();
                setScore();
            }
        
    }
}

//左滑手势
bool GameScene::doLeft()
{
    bool isMove = false;
    
    for (int y = 0; y<4; y++) {
        for (int x = 0; x<4; x++) {
            for (int x1 = x+1; x1<4; x1++) {
                
                if (CardArr(y, x1) -> getNumber() > 0 ) {
                    if (CardArr(y, x)-> getNumber() <= 0) {
                        CardArr(y, x)->setNumber(CardArr(y, x1)->getNumber());
                        CardArr(y, x1)->setNumber(0);
                        x--;
                        isMove = true;
                    }
                    else if(CardArr(y, x)->getNumber() == CardArr(y, x1)->getNumber())
                    {
                        CardArr(y, x)->setNumber(CardArr(y, x1)->getNumber()*2);
                        CardArr(y, x1)->setNumber(0);
                        score += CardArr(y, x)->getNumber();
                       CardArr(y, x)->runAction(JumpTo::create(0.1,Point(CardArr(y, x)->getPosition().x,CardArr(y, x)->getPosition().y), 3,1));
                        
                        isMove = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isMove;
}

//右滑手势
bool GameScene::doRight()
{
    bool isMove = false;
    
    for (int y = 0; y<4; y++) {
        for (int x = 3; x>=0; x--) {
            for (int x1 = x-1; x1>=0; x1--) {
                if (x>0)
                {
                    if (CardArr(y, x1) -> getNumber() > 0 ) {
                        if (CardArr(y, x)-> getNumber() <= 0) {
                            CardArr(y, x)->setNumber(CardArr(y, x1)->getNumber());
                            CardArr(y, x1)->setNumber(0);
                            x++;
                            isMove = true;
                        }
                        else if(CardArr(y, x)->getNumber() == CardArr(y, x1)->getNumber())
                        {
                            CardArr(y, x)->setNumber(CardArr(y, x1)->getNumber()*2);
                            CardArr(y, x1)->setNumber(0);
                            score += CardArr(y, x)->getNumber();
                            CardArr(y, x)->runAction(JumpTo::create(0.1,Point(CardArr(y, x)->getPosition().x,CardArr(y, x)->getPosition().y), 3,1));
                            isMove = true;
                        }
                        break;
                      }
                  }
            }
        }
    }
    
    return isMove;
}





void GameScene::doDown()
{
    bool isMove = false;
    for (int y  = 0; y<4; y++) {
        for (int x = 0; x<4; x++) {
            for (int y1 = y+1; y1<4; y1++) {
                
                if (CardArr(y1, x) -> getNumber() > 0 )
                {
                    if (CardArr(y, x)-> getNumber() <= 0)
                    {
                        CardArr(y, x)->setNumber(CardArr(y1, x)->getNumber());
                        CardArr(y1, x)->setNumber(0);
                        isMove = true;
                    }
                    else if(CardArr(y1, x)->getNumber() == CardArr(y, x)->getNumber())
                    {
                        CardArr(y, x)->setNumber(CardArr(y1, x)->getNumber()*2);
                        CardArr(y1, x)->setNumber(0);
                        score += CardArr(y, x)->getNumber();
                        CardArr(y, x)->runAction(JumpTo::create(0.1,Point(CardArr(y, x)->getPosition().x,CardArr(y, x)->getPosition().y), 3,1));
                        isMove = false;
                    }
                    break;
                }

            }
        }
        if (isMove) {
            y--;
            isMove = false;
        }
    }
}

void GameScene::doUp()
{
    bool isMove = false;
    for (int y = 3; y>=0; y--) {
        for (int x = 0; x<4; x++) {
            for (int y1 = y-1; y1>=0; y1--) {
                if (y>0)
                {
                    if (CardArr(y1, x) -> getNumber() > 0 )
                    {
                        if (CardArr(y, x)-> getNumber() <= 0)
                        {
                            CardArr(y, x)->setNumber(CardArr(y1, x)->getNumber());
                            CardArr(y1, x)->setNumber(0);
                            isMove = true;
                        }
                        else if(CardArr(y1, x)->getNumber() == CardArr(y, x)->getNumber())
                        {
                            CardArr(y, x)->setNumber(CardArr(y1, x)->getNumber()*2);
                            CardArr(y1, x)->setNumber(0);
                            score += CardArr(y, x)->getNumber();
                            CardArr(y, x)->runAction(JumpTo::create(0.1,Point(CardArr(y, x)->getPosition().x,CardArr(y, x)->getPosition().y), 3,1));
                            isMove = false;
                        }
                        break;
                    }
                }
            }
        }
        if(isMove){
            y++;
            isMove = false;
        }
     }
}


void GameScene::doCheck()
{
    bool isGameOver = true;
    
    for (int y = 0; y<4; y++) {
        for (int x = 0; x<4; x++) {
            if (cardArr.at(y*4 + x) -> getNumber() == 0
                || (x<3 && cardArr.at(y*4 + x)->getNumber() == cardArr.at(y*4+x+1)->getNumber())
                || (x>0 && cardArr.at(y*4 + x)->getNumber() == cardArr.at(y*4+x-1)->getNumber())
                || (y<3 && cardArr.at((y*4) + x)->getNumber() == cardArr.at((y*4)+1+x+1)->getNumber())
                || (y>0 && cardArr.at((y*4) + x)->getNumber() == cardArr.at((y*4)-1+x+1)->getNumber())) {
                isGameOver = false;
            }
        }
    }
    
    if (!isGameOver) {
        createCardNumber();
    }
}

//创建 方块
void GameScene::createCardSprite(Size size)
{
    int cardSize = (size.width -165)/4;
    for (int i = 0; i<4; i++) {
        for (int j = 0; j<4; j++) {
//            createCard(0, 40, 40,cardSize*j+170, cardSize*i+100);
            CardSprite *card = CardSprite::createCard(0, cardSize, cardSize,(cardSize+15)*j+60, (cardSize+15)*i+200);
            cardArr.pushBack(card);
            this->addChild(card);
        }
    }
    
}

//随机创建数字
void GameScene::createCardNumber()
{
    while (1) {
        int n = CCRANDOM_0_1() * 4;
        int m = CCRANDOM_0_1() * 4;
            
        int num = n*4;
        
        for (int i = 0; i<4; i++) {
            for (int j = 0; j<4;j++) {
                if (i==n&&j==m)
                {
                  
                if (cardArr.at(num+j)->getNumber()==0)
                {
                    
                    cardArr.at(num+j)->setNumber(CCRANDOM_0_1()*10<1?4:2);
                 //  cardArr.at(num+j)->runAction(JumpTo::create(0.1,Point( cardArr.at(num+j)->getPosition().x,cardArr.at(num+j)->getPosition().y), -3,1));
                    return;
                }
                    
                }
            }
        }
    }
}


#pragma mark - 设置分数

void GameScene::setScore()
{
    cardNumberTTF ->setString(__String::createWithFormat("%i",score)->getCString());
}

void GameScene::onPause(Ref* sender)
{
    Director::getInstance()->pause();
}




