#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
class Bird
{
public:
    Bird( cocos2d::Layer *layer );
    
    void Fall( );
    void Fly( ) 
	{ 
		//play wing sound when click with mouse and go up
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Wing.mp3");
		isFalling = false; 
	};
    void StopFlying( ) { isFalling = true; }
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    cocos2d::Sprite *flappyBird;
    
    bool isFalling;
    
};

#endif // __BIRD_H__