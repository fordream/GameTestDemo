#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
//    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    // add the label as a child to this layer
//    this->addChild(label, 1);
//
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    auto white = LayerColor::create(Color4B(255, 255, 255, 255),30, 30);
    white->setPosition3D(Vec3(0, 0,0));
    white->setAnchorPoint(Point(0,0));
   // this->addChild(white);
    log("%f,%f",visibleSize.width,visibleSize.height);
    
    auto hero = Sprite::Node::create();
    hero->setContentSize(Size(30, 30));
    hero->setPosition3D(Vec3(visibleSize.width/2,visibleSize.height/2,45));
    hero->addChild(white);
    this->addChild(hero);
    log("%f",hero->getPositionY());
    auto move = JumpTo::create(0.5, Point(hero->getPositionX(),hero->getPositionY()+6),6, 1);
  //  auto moveT = MoveTo::create(0.5, Point(hero->getPositionX(),hero->getPositionY()+6));
    auto moveDone = CallFunc::create([&]{
    });
   
    hero->runAction(Sequence::create(move,moveDone, NULL));
    
     auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = [](Touch* touch, Event* event)
    {
         // 获取事件所绑定的 target
//         auto target = static_cast<Sprite*>(event->getCurrentTarget());
//         
//         // 获取当前点击点所在相对按钮的位置坐标
//         Point locationInNode = target->convertToNodeSpace(touch->getLocation());
//         Size s = target->getContentSize();
//         Rect rect = Rect(0, 0, s.width, s.height);
//         
//         // 点击范围判断检测
//         if (rect.containsPoint(locationInNode))
//         {
//             log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
//             target->setOpacity(180);
//             return true;
//         }
      
        log("tap");
        return true;
        
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event)
    {
        log("touch end");
    };
    
    listener1->onTouchMoved = [](Touch* touch, Event* event)
    {
        log("touch moved");
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    return true;
}




void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
