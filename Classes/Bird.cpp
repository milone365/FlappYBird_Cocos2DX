#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird( cocos2d::Layer *layer )
{
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
    //create image and set position in the middle of screen
    flappyBird = Sprite::create( "Images/Ball.png" );
    flappyBird->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    //create "Body" collider ad add bitmask
    auto flappyBody = PhysicsBody::createCircle( flappyBird->getContentSize( ).width / 2 );
    flappyBody->setCollisionBitmask( BIRD_COLLISION_BITMASK );
    //abilitate bitmask collision
	flappyBody->setContactTestBitmask( true );
    //add body to the sprite
    flappyBird->setPhysicsBody( flappyBody );
    //add object to the scene
    layer->addChild( flappyBird, 100 );
    //deactive fly
    isFalling = true;
}

void Bird::Fall( )
{
	//position is always in the middle (x)
	//if flying go up otherwise go down
    if ( true == isFalling )
    {
        flappyBird->setPositionX( visibleSize.width / 2 + origin.x );
        flappyBird->setPositionY( flappyBird->getPositionY() - ( BIRD_FALLING_SPEED * visibleSize.height ) );
    }
    else
    {
        flappyBird->setPositionX( visibleSize.width / 2 + origin.x );
        flappyBird->setPositionY( flappyBird->getPositionY() + ( BIRD_FALLING_SPEED * visibleSize.height ) );
    }
}




