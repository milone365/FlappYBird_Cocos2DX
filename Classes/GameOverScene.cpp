#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

unsigned int score;
//passing score when create scene
Scene* GameOverScene::createScene( unsigned int tempScore )
{
    score = tempScore;
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//load background image set in the middle and add to scene
    auto backgroundSprite = Sprite::create( "Images/Background.png" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    //add background to the scene
    this->addChild( backgroundSprite );
    //create 2 button and set position for menu or game scene
    auto retryItem = MenuItemImage::create( "Images/Retry Button.png", "Images/Retry Button Clicked.png", CC_CALLBACK_1( GameOverScene::GoToGameScene, this ) );
    retryItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3 ) );
    auto mainMenuItem = MenuItemImage::create( "Images/Menu Button.png", "Images/Menu Button Clicked.png", CC_CALLBACK_1( GameOverScene::GoToMainMenuScene, this ) );
    mainMenuItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 4 ) );
    //create menu
    auto menu = Menu::create( retryItem, mainMenuItem, NULL );
    menu->setPosition( Point::ZERO );
    //add menu to the scene
    this->addChild( menu );
    //salvatage score
	UserDefault *def = UserDefault::getInstance();
	auto hightScore = def->getIntegerForKey("HIGHSCORE",0);
	//is like unity's player prefs
	if (score > hightScore)
	{
		hightScore = score;
		def->setIntegerForKey("HIGHSCORE", hightScore);
	}
	def->flush();
	//create string for score
    __String *tempScore = __String::createWithFormat( "%i", score );
    //set font and position
    auto currentScore = LabelTTF::create( tempScore->getCString( ), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE );
    currentScore->setPosition( Point( visibleSize.width * 0.25 + origin.x, visibleSize.height / 2 + origin.y ) );
    //add to scene
    this->addChild( currentScore );
	//set font 
	__String *tempHighScore = __String::createWithFormat("%i", hightScore);
	auto h_score_label = LabelTTF::create(tempHighScore->getCString(), "fonts/Maker Felt.ttf", visibleSize.height*SCORE_FONT_SIZE);
    //change color 
	h_score_label->setColor(Color3B::YELLOW);
	//set position
	h_score_label->setPosition(Point(visibleSize.width * 0.75 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(h_score_label);

	return true;
}
//change scene functions
void GameOverScene::GoToMainMenuScene( cocos2d::Ref *sender )
{
    auto scene = MainMenuScene::createScene( );
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void GameOverScene::GoToGameScene( cocos2d::Ref *sender )
{
    auto scene = GameScene::createScene( );
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}







