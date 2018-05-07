/*
 * UiMgr.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */

#include <UiMgr.h>
#include <Engine.h>
#include <GfxMgr.h>
#include <GameMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <Types381.h>

std::string intToString(int x){
	char tmp[10000];
	sprintf(tmp, "%i", x);
	return std::string(tmp);
}

UiMgr::UiMgr(Engine* eng): Mgr(eng){
	// Initialize the OverlaySystem (changed for Ogre 1.9)
	    mOverlaySystem = new Ogre::OverlaySystem();
	    mTrayMgr = 0;
	    mLabel = 0;
	    engine->gfxMgr->mSceneMgr->addRenderQueueListener(mOverlaySystem);

	    //Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);
	    std::cout << "end uicons" << std::endl;

	    uiState = InitMenuState;
	    mButton = 0;
		GladiusBtn = 0;
		HastatusBtn = 0;
		GladiusLbl= 0;
		HastatusLbl = 0;

}

UiMgr::~UiMgr(){ // before gfxMgr destructor

}

void UiMgr::Init(){
	//init sdktrays

    mInputContext.mKeyboard = engine->inputMgr->mKeyboard;
    mInputContext.mMouse = engine->inputMgr->mMouse;
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->gfxMgr->mWindow, mInputContext, this);
    //mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    //mTrayMgr->hideCursor();
}

void UiMgr::stop(){

}

void UiMgr::LoadLevel(){
	//mTrayMgr->showBackdrop("ECSLENT/UI");
	mButton = mTrayMgr->createButton(OgreBites::TL_TOPRIGHT,"helpBtn","Instructions",250);
	mTrayMgr->createButton(OgreBites::TL_TOPRIGHT, "credit", "Credits", 250);
	//mTrayMgr->createButton(OgreBites::TL_BOTTOMLEFT,"test","test",250);
}

void UiMgr::Tick(float dt){
	mTrayMgr->refreshCursor();
	switch(uiState)
	{
	//Splash Screen Invocation States////////////////////////////////////
	case InitMenuState:
		engine->paused = true;
		mTrayMgr->hideBackdrop();
		mTrayMgr->showBackdrop("ECSLENT/SPLASH");

		/*mButton = (OgreBites::Button*)mTrayMgr->getWidget("helpBtn");
		if( mButton == NULL)
		{
			mButton = mTrayMgr->createButton(OgreBites::TL_TOPRIGHT,"helpBtn","Instructions",250);
		}*/
		break;

	case ReSplashMenuState:
		engine->paused = true;
		mTrayMgr->hideBackdrop();
		mTrayMgr->showBackdrop("ECSLENT/INSTRUCTION");

		mButton->setCaption("Play");

		break;
	//////////////////////////////////////////////////////////////////////

	//During piloting/////////////////////////////////////////////////////
	case PilotUIState:
		engine->paused = false;
		mTrayMgr->hideBackdrop();


		mLabel = (OgreBites::Label*)mTrayMgr->getWidget("PILOT_POINTS");
		if( mLabel == NULL)
			mLabel = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT,"PILOT_POINTS", "0",250);

		mLabel->setCaption(intToString( engine->gameMgr->points));

		//BottomRight-bound stats.
			//HP
		OgreBites::ProgressBar* hp;
		hp = (OgreBites::ProgressBar*)mTrayMgr->getWidget("PILOT_HP");
		if(hp == NULL) hp = mTrayMgr->createProgressBar(OgreBites::TL_BOTTOMRIGHT, "PILOT_HP", "HEALTH", 250., 240.);
		hp->show();

		OgreBites::Label* wave;
		wave = (OgreBites::Label*)mTrayMgr->getWidget("WAVE");
		if(wave == NULL) wave = mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT, "WAVE", "WAVE 1", 250);
		if(engine->gameMgr->waveTwoUnlocked) wave->setCaption("WAVE 2");
		if(engine->gameMgr->waveThreeUnlocked) wave->setCaption("WAVE 3");

		//Instructions button placement
		mButton = (OgreBites::Button*)mTrayMgr->getWidget("helpBtn");
		if( mButton == NULL)
		{
			mButton = mTrayMgr->createButton(OgreBites::TL_TOPRIGHT,"helpBtn","Instructions",250);
		}



		hp->setProgress(engine->entityMgr->playerEntity->currentHealth/(engine->entityMgr->playerEntity->maxHealth)); //TODO: Base on proper max

		mButton->setCaption("Instructions");

		mTrayMgr->getTrayContainer(OgreBites::TL_BOTTOMRIGHT)->show();

		mTrayMgr->showTrays();
		mTrayMgr->showBackdrop("ECSLENT/PILOT_UI");
		break;
	/////////////////////////////////////////////////////////////////////helpBtn/

	//Pause Menu (What would traditionally be bound to ESC)///////////////
	case PauseMenuState:
		engine->paused = true;
		mTrayMgr->hideBackdrop();
		//mTrayMgr->destroyAllWidgets();

		mTrayMgr->hideAll();

		mButton = (OgreBites::Button*)mTrayMgr->getWidget("helpBtn");
		mTrayMgr->showCursor();
		mTrayMgr->showTrays();

		mTrayMgr->getTrayContainer(OgreBites::TL_BOTTOMRIGHT)->hide();

		break;
	//////////////////////////////////////////////////////////////////////

	case respawState:

		engine->paused = true;
		mTrayMgr->showBackdrop();

		HastatusLbl = (OgreBites::Label*)mTrayMgr->getWidget("HastatusPointLabel");
		if( mButton == NULL)
			mTrayMgr->createLabel(OgreBites::TL_CENTER, "HastatusPointLabel","100",250.);

		HastatusBtn = (OgreBites::Button*)mTrayMgr->getWidget("HastatusButton");
		if( mButton == NULL)
			mTrayMgr->createButton(OgreBites::TL_CENTER,"HastatusButton", "Hastatus");

		GladiusLbl = (OgreBites::Label*)mTrayMgr->getWidget("GladiusPointLabel");
		if( mButton == NULL)
			mTrayMgr->createLabel(OgreBites::TL_CENTER, "GladiusPointLabel","250",250.);

		GladiusBtn = (OgreBites::Button*)mTrayMgr->getWidget("GladiusButton");
		if( mButton == NULL)
			mTrayMgr->createButton(OgreBites::TL_CENTER, "GladiusButton","Gladius");

		//mTrayMgr->createLabel(OgreBites::TL_CENTER, "HastatusPointLabel","100",250.);
		//mTrayMgr->createButton(OgreBites::TL_CENTER, "","");

		break;

	case creditState:
		mTrayMgr->hideBackdrop();
		mTrayMgr->showBackdrop("ECSLENT/Credits");
		//Instructions button placement
		mButton = (OgreBites::Button*)mTrayMgr->getWidget("helpBtn");
		if( mButton == NULL)
		{
			mButton = mTrayMgr->createButton(OgreBites::TL_TOPRIGHT,"helpBtn","Instructions",250);
		}

		break;

	}


}

void UiMgr::windowResized(Ogre::RenderWindow* rw){
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = engine->inputMgr->mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void UiMgr::windowClosed(Ogre::RenderWindow* rw){

}

bool UiMgr::keyPressed(const OIS::KeyEvent &arg) {
	std::cout << "Key Pressed: " << arg.key << std::endl;
	return true;
}
bool UiMgr::keyReleased(const OIS::KeyEvent &arg){
	return true;
}
bool UiMgr::mouseMoved(const OIS::MouseEvent &arg){
    if (mTrayMgr->injectMouseMove(arg)) return true;
	return false;
}
bool UiMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid) {
	std::cout << "mouse clicked" << std::endl;
	if (mTrayMgr->injectMouseDown(me, mid)) return true;
	return false;
}
bool UiMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    return false;
}

void UiMgr::buttonHit(OgreBites::Button *b){

	std::cout << "do I ever happen" << std::endl;
    if(b->getName() == "helpBtn"){
    	std::cout << "Help Button pressed" << std::endl;
    	if(uiState!= ReSplashMenuState) uiState = ReSplashMenuState;
    	else uiState = PilotUIState;
    }

    if(b->getName() == "credit"){
    	std::cout << "Help Button pressed" << std::endl;
    	uiState = creditState;
    }


    /*
    else if(b->getName()=="HastatusButton")
    {

    }
    else if(b->getName()=="GladiusButton")
    {

    }*/

}

void UiMgr::itemSelected(OgreBites::SelectMenu *m){
    Ogre::Vector3 pos;
    pos.x = 0;
    pos.y = 0;
    pos.z = 100;
    switch(m->getSelectionIndex()){
    case 1:
    	engine->entityMgr->CreateEntityOfTypeAtPosition(friendlyTypeOne,pos);
    	break;
    case 2:
    	engine->entityMgr->CreateEntityOfTypeAtPosition(friendlyTypeTwo,pos);
    	break;

    default:
    	break;
    }

}
