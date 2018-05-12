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
	    helpBtn = 0;
	    creditsBtn = 0;

		GladiusBtn = 0;
		HastatusBtn = 0;
		friendlythreeBtn = 0;

		GladiusLbl= 0;
		HastatusLbl = 0;
		hp = 0;
		prevState = uiState;
		waveLbl = 0;
		pauseLbl = 0;
		friendlyThreeLbl = 0;
		playPauseBtn = 0;
		returnToMM = 0;

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
	//create tray for Menu Screen
	helpBtn = mTrayMgr->createButton(OgreBites::TL_TOPRIGHT,"helpBtn","Controls",250);
	creditsBtn = mTrayMgr->createButton(OgreBites::TL_TOPRIGHT, "credit", "Credits", 250);
	playPauseBtn = mTrayMgr->createButton(OgreBites::TL_TOPRIGHT, "play", "Play", 250);

	//mTrayMgr->hideAll();
	//mTrayMgr->createButton(OgreBites::TL_BOTTOMLEFT,"test","test",250);
}

void UiMgr::Tick(float dt){
	mTrayMgr->refreshCursor();

	switch(uiState)
	{
	/*************************Splash Screen Invocation States********************************/
	case InitMenuState:
		engine->paused = true;
		mTrayMgr->hideBackdrop();
		mTrayMgr->showBackdrop("ECSLENT/SPLASH");
		helpBtn->setCaption( "Controls");

		mTrayMgr->getTrayContainer(OgreBites::TL_TOPLEFT)->hide();
		mTrayMgr->getTrayContainer(OgreBites::TL_CENTER)->hide();
		mTrayMgr->getTrayContainer(OgreBites::TL_LEFT)->hide();
		mTrayMgr->getTrayContainer(OgreBites::TL_TOP)->hide();
		mTrayMgr->getTrayContainer(OgreBites::TL_BOTTOM)->hide();
		mTrayMgr->getTrayContainer(OgreBites::TL_TOPRIGHT)->show();

		mTrayMgr->getTrayContainer(OgreBites::TL_TOPRIGHT)->setHeight(115.);

		if(pauseLbl != NULL)
			pauseLbl->hide();
		break;

	case ReSplashMenuState:
		engine->paused = true;
		pauseLbl->hide();
		mTrayMgr->hideBackdrop();
		mTrayMgr->showBackdrop("ECSLENT/INSTRUCTION");
		break;
	//////////////////////////////////////////////////////////////////////

	//During piloting/////////////////////////////////////////////////////
	case PilotUIState:
		engine->paused = false;
		mTrayMgr->hideBackdrop();
		mTrayMgr->getTrayContainer(OgreBites::TL_TOPLEFT)->hide();
		mTrayMgr->getTrayContainer(OgreBites::TL_CENTER)->hide();
		mTrayMgr->getTrayContainer(OgreBites::TL_LEFT)->hide();
		//mTrayMgr->hideCursor();
		playPauseBtn->hide();

		mTrayMgr->getTrayContainer(OgreBites::TL_TOPRIGHT)->setHeight(85.);

		//Number of points
		mLabel = (OgreBites::Label*)mTrayMgr->getWidget("PILOT_POINTS");
		if( mLabel == NULL)
			mLabel = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT,"PILOT_POINTS", "0",250);
		mLabel->setCaption(intToString( engine->gameMgr->points));

		//Amount of health
		hp = (OgreBites::ProgressBar*)mTrayMgr->getWidget("PILOT_HP");
		if(hp == NULL)
			hp = mTrayMgr->createProgressBar(OgreBites::TL_BOTTOMRIGHT, "PILOT_HP", "PLAYER HEALTH", 250., 240.);
		hp->show();
		hp->setProgress(engine->entityMgr->playerEntity->currentHealth/(engine->entityMgr->playerEntity->maxHealth));

		OgreBites::ProgressBar* hp2;
		hp2 = (OgreBites::ProgressBar*)mTrayMgr->getWidget("YGGDRASIL_HP");
		if(hp2 == NULL)
			hp2 = mTrayMgr->createProgressBar(OgreBites::TL_TOP, "YGGDRASIL_HP", "YGGRASIL HEALTH", 250., 240.);
		hp2->show();
		hp2->setProgress(engine->entityMgr->yggdrasil->currentHealth/(engine->entityMgr->yggdrasil->maxHealth));

		OgreBites::ProgressBar* hp3;
		hp3 = (OgreBites::ProgressBar*)mTrayMgr->getWidget("CAELESTION_HP");
		if(hp3 == NULL)
			hp3 = mTrayMgr->createProgressBar(OgreBites::TL_BOTTOM, "CAELESTION_HP", "CAELESTION HEALTH", 250., 240.);
		hp3->show();
		hp3->setProgress(engine->entityMgr->caelestion->currentHealth/(engine->entityMgr->caelestion->maxHealth));

		//Wave that you are currently on
		waveLbl = (OgreBites::Label*)mTrayMgr->getWidget("WAVE");
		if(waveLbl == NULL)
			waveLbl = mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT, "WAVE", "WAVE 1", 250);
		if(engine->gameMgr->waveTwoUnlocked)
			waveLbl->setCaption("WAVE 2");
		if(engine->gameMgr->waveThreeUnlocked)
			waveLbl->setCaption("WAVE 3");

		//Instructions button placement
		helpBtn->setCaption("Controls");

		break;
	/////////////////////////////////////////////////////////////////////helpBtn/

	//Pause Menu (What would traditionally be bound to ESC)///////////////
	case PauseMenuState:
		engine->paused = true;
		mTrayMgr->showCursor();

		mTrayMgr->getTrayContainer(OgreBites::TL_TOPRIGHT)->setHeight(85.);
		mTrayMgr->getTrayContainer(OgreBites::TL_CENTER)->hide();
		mTrayMgr->getTrayContainer(OgreBites::TL_LEFT)->hide();

		helpBtn->setCaption("Controls");

		pauseLbl = (OgreBites::Label*)mTrayMgr->getWidget("pause");
		if(pauseLbl == NULL)
			pauseLbl = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "pause", "PAUSED", 250);
		mTrayMgr->getTrayContainer(OgreBites::TL_TOPLEFT)->show();


		break;
	//////////////////////////////////////////////////////////////////////

	case respawState:
		engine->paused = true;
		mTrayMgr->hideBackdrop();
		mTrayMgr->showCursor();
		mTrayMgr->getTrayContainer(OgreBites::TL_LEFT)->hide();
		mTrayMgr->getTrayContainer(OgreBites::TL_TOPRIGHT)->setHeight(85.);


		mTrayMgr->getTrayContainer(OgreBites::TL_CENTER)->show();
		mTrayMgr->getTrayContainer(OgreBites::TL_CENTER)->setWidth(800.);
		mTrayMgr->getTrayContainer(OgreBites::TL_CENTER)->setPosition(-400.0,0.0);
		mTrayMgr->getTrayContainer(OgreBites::TL_CENTER)->setHeight(155.);


		friendlyThreeLbl= (OgreBites::Label*)mTrayMgr->getWidget("friendlyThree_label");
		if(friendlyThreeLbl == NULL)
			friendlyThreeLbl = mTrayMgr->createLabel(OgreBites::TL_CENTER, "friendlyThree_label", "# of points for frd3", 250);
		friendlyThreeLbl->getOverlayElement()->setPosition(140,5.);
		friendlyThreeLbl->getOverlayElement()->setWidth(250);


		GladiusLbl= (OgreBites::Label*)mTrayMgr->getWidget("gladius_label");
		if(GladiusLbl == NULL)
			GladiusLbl = mTrayMgr->createLabel(OgreBites::TL_CENTER, "gladius_label", "# of points for Gladuis", 250);
		GladiusLbl->getOverlayElement()->setPosition(-125,5.);
		GladiusLbl->getOverlayElement()->setWidth(250);

		HastatusLbl = (OgreBites::Label*)mTrayMgr->getWidget("Hastatus_label");
		if(HastatusLbl == NULL)
			HastatusLbl = mTrayMgr->createLabel(OgreBites::TL_CENTER, "Hastatus_label", "# of points for Hastatus", 250);
		HastatusLbl->getOverlayElement()->setPosition(-390.,5.);
		HastatusLbl->getOverlayElement()->setWidth(250);


		OgreBites::Separator* separate;
		separate = (OgreBites::Separator*)mTrayMgr->getWidget("sep");
		if( separate == NULL)
			separate = mTrayMgr->createSeparator(OgreBites::TL_CENTER,"sep", 900);
		separate->getOverlayElement()->setPosition(-400., 50.);


		HastatusBtn = (OgreBites::Button*)mTrayMgr->getWidget("hastatus_button");
		if(HastatusBtn == NULL)
			HastatusBtn = mTrayMgr->createButton(OgreBites::TL_CENTER, "hastatus_button", "Hastatus", 250);
		HastatusBtn->getOverlayElement()->setPosition(-390.,70.);
		HastatusBtn->getOverlayElement()->setWidth(250);
		HastatusBtn->getOverlayElement()->setHeight(80.);

		GladiusBtn = (OgreBites::Button*)mTrayMgr->getWidget("gladius_button");
		if(GladiusBtn == NULL)
			GladiusBtn = mTrayMgr->createButton(OgreBites::TL_CENTER, "gladius_button", "Gladius", 250);
		GladiusBtn->getOverlayElement()->setPosition(-125,70.);
		GladiusBtn->getOverlayElement()->setWidth(250);
		GladiusBtn->getOverlayElement()->setHeight(80.);

		friendlythreeBtn = (OgreBites::Button*)mTrayMgr->getWidget("friendlythree_button");
		if(friendlythreeBtn == NULL)
			friendlythreeBtn = mTrayMgr->createButton(OgreBites::TL_CENTER, "friendlythree_button", "FriendlyThree", 250);
		friendlythreeBtn->getOverlayElement()->setPosition(140.,70.);
		friendlythreeBtn->getOverlayElement()->setWidth(250);
		friendlythreeBtn->getOverlayElement()->setHeight(80.);

		break;

	case creditState:
		mTrayMgr->hideBackdrop();
		mTrayMgr->showBackdrop("ECSLENT/Credits");
		mTrayMgr->getTrayContainer(OgreBites::TL_LEFT)->hide();

		//Instructions button placement
		if(prevState == InitMenuState)
			helpBtn->setCaption("Main Menu");
		else if( prevState == PilotUIState)
			helpBtn->setCaption("Play");
		else if (prevState == respawState)
			helpBtn->setCaption( "Respawn Screen");

		break;

	case controlState:
		engine->paused = true;
		mTrayMgr->hideBackdrop();
		mTrayMgr->showBackdrop("ECSLENT/INSTRUCTION");
		mTrayMgr->getTrayContainer(OgreBites::TL_LEFT)->hide();

		if(prevState == InitMenuState)
			helpBtn->setCaption("Main Menu");
		else if( prevState == PilotUIState || prevState == PauseMenuState)
			helpBtn->setCaption("Play");
		else if (prevState == respawState)
			helpBtn->setCaption( "Respawn Screen");

		break;
	case gameLostState:
		engine->paused = true;

		//mTrayMgr->hideBackdrop();
		//mTrayMgr->showBackdrop("");		//replace with the lost screen

		mTrayMgr->getTrayContainer(OgreBites::TL_CENTER)->hide();
		mTrayMgr->getTrayContainer(OgreBites::TL_BOTTOMRIGHT)->hide();
		mTrayMgr->getTrayContainer(OgreBites::TL_LEFT)->show();
		mTrayMgr->getTrayContainer(OgreBites::TL_TOPRIGHT)->setHeight(85.);

		mTrayMgr->getTrayContainer(OgreBites::TL_LEFT)->setPosition(400,0);


		returnToMM = (OgreBites::Button*)mTrayMgr->getWidget("returnToMM_button");
				if(returnToMM == NULL)
					returnToMM = mTrayMgr->createButton(OgreBites::TL_LEFT, "returnToMM_button", "Main Menu", 250);
		break;
	case gameWinState:
		engine->paused = true;

		//mTrayMgr->hideBackdrop();
		//mTrayMgr->showBackdrop("");		//replace with the win screen

		mTrayMgr->getTrayContainer(OgreBites::TL_CENTER)->hide();
		mTrayMgr->getTrayContainer(OgreBites::TL_BOTTOMRIGHT)->hide();
		mTrayMgr->getTrayContainer(OgreBites::TL_LEFT)->show();
		mTrayMgr->getTrayContainer(OgreBites::TL_TOPRIGHT)->setHeight(85.);

		returnToMM = (OgreBites::Button*)mTrayMgr->getWidget("returnToMM_button");
						if(returnToMM == NULL)
							returnToMM = mTrayMgr->createButton(OgreBites::TL_LEFT, "returnToMM_button", "Main Menu", 250);
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
    if(b->getName() == "helpBtn"){
    	if(uiState == creditState){
    		uiState = prevState;
    	}
    	else if(uiState != controlState){
    		prevState = uiState;
    		uiState = controlState;
    	}
    	else if( prevState == PauseMenuState){
    		uiState = PilotUIState;
    	}
    	else{
    		uiState = prevState;

    	}
    }

    if(b->getName() == "credit"){
    	uiState = creditState;
    }

    if(b->getName() == "play"){
    	if( uiState != PilotUIState)
    		uiState = PilotUIState;
    	else{
    		uiState = PauseMenuState;
    	}
    }

    if(b->getName()=="hastatus_button")
    {
    	engine->entityMgr->playerEntity->switchPlayerEnt(friendlyTypeOne);
    	uiState = PilotUIState;
    }
    if(b->getName()=="gladius_button")
    {
    	engine->entityMgr->playerEntity->switchPlayerEnt(friendlyTypeTwo);
    	uiState = PilotUIState;
    }

    if(b->getName()=="friendlythree_button")
    {
    	engine->entityMgr->playerEntity->switchPlayerEnt(friendlyTypeThree);
    	uiState = PilotUIState;
    }

    if(b->getName() == "returnToMM_button"){
    	std::cout << "Button Pressed" << std::endl;
    	uiState = InitMenuState;
    	engine->gameMgr->restart();
    }

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
