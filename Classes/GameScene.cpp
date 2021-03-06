#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics( );
    scene->getPhysicsWorld( )->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    scene->getPhysicsWorld( )->setGravity( Vect( 0, 0 ) );
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld( ) );

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//create background in the cente 
    auto backgroundSprite = Sprite::create( "Images/Background.png" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    //add to scene node
    this->addChild( backgroundSprite );
    //create borders with physics and bitmask
    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    edgeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
    edgeBody->setContactTestBitmask( true );
    //add borders to the scene
    auto edgeNode = Node::create();
    edgeNode->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    edgeNode->setPhysicsBody( edgeBody );
    
    this->addChild( edgeNode );
    //span pipe event creation
    this->schedule( schedule_selector( GameScene::SpawnPipe ), PIPE_SPAWN_FREQUENCY * visibleSize.width );
    //create bird
    bird = new Bird( this );
    //generate collision event and collegate to the function
    auto contactListener = EventListenerPhysicsContact::create( );
    contactListener->onContactBegin = CC_CALLBACK_1( GameScene::onContactBegin, this );
    Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( contactListener, this );
    //create fly event with click 
    auto touchListener = EventListenerTouchOneByOne::create( );
    touchListener->setSwallowTouches( true );
    touchListener->onTouchBegan = CC_CALLBACK_2( GameScene::onTouchBegan, this );
    Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( touchListener, this );
    //set score to 0
    score = 0;
    //create score text, set font, color to white and position
    __String *tempScore = __String::createWithFormat( "%i", score );
    
    scoreLabel = Label::createWithTTF( tempScore->getCString( ), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE );
    scoreLabel->setColor( Color3B::WHITE );
    scoreLabel->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y ) );
    //add label to the scene
    this->addChild( scoreLabel, 10000 );
    //UPDATE
    this->scheduleUpdate( );
    
    return true;
}
//spawn pipe function
void GameScene::SpawnPipe( float dt )
{
    pipe.SpawnPipe( this );
}

bool GameScene::onContactBegin( cocos2d::PhysicsContact &contact )
{
	//make confront with 2 collider
    PhysicsBody *a = contact.getShapeA( )->getBody();
    PhysicsBody *b = contact.getShapeB( )->getBody();
    //if bird collide with obstacle
    if ( ( BIRD_COLLISION_BITMASK == a->getCollisionBitmask( ) && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BIRD_COLLISION_BITMASK == b->getCollisionBitmask( ) && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask() ) )
    {        
		//play sound hit , and create game over scene
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Hit.mp3");
		auto scene = GameOverScene::createScene( score );
        Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
    }
    else if ( ( BIRD_COLLISION_BITMASK == a->getCollisionBitmask( ) && POINT_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BIRD_COLLISION_BITMASK == b->getCollisionBitmask( ) && POINT_COLLISION_BITMASK == a->getCollisionBitmask() ) )
    {
		//add score, play point sound and update text
        score++;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Point.mp3");
        __String *tempScore = __String::createWithFormat( "%i", score );
        scoreLabel->setString( tempScore->getCString( ) );
    }
    
    return true;
}

//set fly to true and after set false
bool GameScene::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event )
{
    bird->Fly( );
    
    this->scheduleOnce( schedule_selector( GameScene::StopFlying ), BIRD_FLY_DURATION );
    
    return true;
}
//set fly false
void GameScene::StopFlying( float dt )
{
    bird->StopFlying( );
}
//"use gravity"
void GameScene::update( float dt )
{
    bird->Fall( );
}










