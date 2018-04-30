/*
 * UiMgr.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */

#include <UiMgr.h>
#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <Types381.h>

UiMgr::UiMgr(Engine* eng): Mgr(eng){
	// Initialize the OverlaySystem (changed for Ogre 1.9)
	    mOverlaySystem = new Ogre::OverlaySystem();
	    mTrayMgr = 0;
	    mLabel = 0;
	    engine->gfxMgr->mSceneMgr->addRenderQueueListener(mOverlaySystem);

	    //Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);
	    std::cout << "end uicons" << std::endl;

	    uiState = InitMenuState;
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
    mTrayMgr->hideCursor();
}

void UiMgr::stop(){

}

void UiMgr::LoadLevel(){
	//mTrayMgr->showBackdrop("ECSLENT/UI");
}

void UiMgr::Tick(float dt){
	//mTrayMgr->refreshCursor();
	switch(uiState)
	{
	//Splash Screen Invocation States////////////////////////////////////
	case InitMenuState:
	case ReSplashMenuState:
		engine->paused = true;
		mTrayMgr->showBackdrop("ECSLENT/SPLASH");
		break;
	//////////////////////////////////////////////////////////////////////

	//During piloting/////////////////////////////////////////////////////
	case PilotUIState:
		engine->paused = false;
		mTrayMgr->hideBackdrop();

		//BottomRight-bound stats.
			//HP
		OgreBites::ProgressBar* hp;
		hp = (OgreBites::ProgressBar*)mTrayMgr->getWidget("PILOT_HP");
		if(hp == NULL) hp = mTrayMgr->createProgressBar(OgreBites::TL_BOTTOMRIGHT, "PILOT_HP", "", 250., 250.);
		hp->show();
		hp->setProgress(.5);



		mTrayMgr->showTrays();
		mTrayMgr->showBackdrop("ECSLENT/PILOT_UI");
		break;
	//////////////////////////////////////////////////////////////////////

	//Pause Menu (What would traditionally be bound to ESC)///////////////
	case PauseMenuState:
		engine->paused = true;
		mTrayMgr->hideBackdrop();
		mTrayMgr->destroyAllWidgets();




		break;
	//////////////////////////////////////////////////////////////////////
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
    //if (mTrayMgr->injectMouseMove(arg)) return true;
	return false;
}
bool UiMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid) {
	std::cout << "mouse clicked" << std::endl;
	//if (mTrayMgr->injectMouseDown(me, mid)) return true;
	return false;
}
bool UiMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
    //if (mTrayMgr->injectMouseUp(arg, id)) return true;
    /* normal mouse processing here... */
	return false;
}

void UiMgr::buttonHit(OgreBites::Button *b){
    if(b->getName()=="MyButton")
    {
        std::cout <<"Boat Spawned!" << std::endl;
        Ogre::Vector3 pos;
        pos.x = 0;
        pos.y = 0;
        pos.z = -100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(friendlyTypeOne,pos);
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
