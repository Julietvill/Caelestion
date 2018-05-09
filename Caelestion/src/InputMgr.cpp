/*
 * InputMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */
#include<cfloat>

#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <GameMgr.h>
#include <UiMgr.h>
#include <DebugDrawer.h>
#include <UiMgr.h>


#include <Utils.h>

using namespace std;


//Control, shift, and space will be primary fire, secondary fire, and special action

InputMgr::InputMgr(Engine *engine) : Mgr(engine), OIS::KeyListener(), OIS::MouseListener() {

	this->mInputMgr = 0;
	this->mKeyboard = 0;
	this->mMouse = 0;
	this->keyboardTimer = keyTime;
	deltaDesiredHeading = 5.f;
	deltaDesiredAltitude = 20;
}

InputMgr::~InputMgr() {

}

void InputMgr::Init(){

	  OIS::ParamList pl;
	  size_t windowHandle = 0;
	  std::ostringstream windowHandleStr;

	  engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHandle);
	  windowHandleStr << windowHandle;
	  pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));
	  // insert the following lines right before calling mInputSystem = OIS::InputManager::createInputSystem( paramList );
		#if defined OIS_WIN32_PLATFORM
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
		#elif defined OIS_LINUX_PLATFORM
		pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("true")));
		//pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
		#endif

	  mInputMgr = OIS::InputManager::createInputSystem(pl);

	  mKeyboard = static_cast<OIS::Keyboard*>(
	    mInputMgr->createInputObject(OIS::OISKeyboard, true));
	  mMouse = static_cast<OIS::Mouse*>(
	    mInputMgr->createInputObject(OIS::OISMouse, true));

	  int left, top;
	  unsigned int width, height, depth;

	  engine->gfxMgr->mWindow->getMetrics(width, height, depth, left, top);
	  const OIS::MouseState &ms = mMouse->getMouseState();
	  ms.width = width;
	  ms.height = height;
	  mMouse->setEventCallback(this);
	  mKeyboard->setEventCallback(this);

}



void InputMgr::Stop(){
	if(mInputMgr){
		mInputMgr->destroyInputObject(mMouse);
		mInputMgr->destroyInputObject(mKeyboard);

		OIS::InputManager::destroyInputSystem(mInputMgr);
		mInputMgr = 0;
   	}
}

void InputMgr::Tick(float dt){

	// Pause-independent code.
	mKeyboard->capture();
	keyboardTimer -= dt;


		// Kill-program
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE)){
		engine->keepRunning = false;
	}

		// Pause state engage/disengage (Open pause menu)
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_P)){
		if(engine->uiMgr->uiState != PilotUIState){
			engine->uiMgr->prevState = engine->uiMgr->uiState;
			engine->uiMgr->uiState = PilotUIState;
		}
		else
		{
			engine->uiMgr->prevState = engine->uiMgr->uiState;
			engine->uiMgr->uiState = PauseMenuState;
		}
		keyboardTimer = keyTime;
	}
	mMouse->capture();

	if(engine->paused == false)
	{
		//only handled during non-pause runtime
		UpdateCamera(dt);
		UpdatePlayerShipControl(dt);
	}

	else
	{

	}

}

void InputMgr::UpdateCamera(float dt){
}

void InputMgr::UpdatePlayerShipControl(float dt){

	Ogre::Vector3 relativeFaceAdjust = Ogre::Vector3::ZERO;
	bool resetKT = false;


	//Player Acceleration Controls.
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_LSHIFT) && !mKeyboard->isKeyDown(OIS::KC_Z)){
		resetKT = true;
		engine->entityMgr->playerEntity->acc = 1;
	}

	if((keyboardTimer < 0) && !mKeyboard->isKeyDown(OIS::KC_LSHIFT) && mKeyboard->isKeyDown(OIS::KC_Z)){
		resetKT = true;
		engine->entityMgr->playerEntity->acc = -1;
	}

	if((keyboardTimer < 0) && !mKeyboard->isKeyDown(OIS::KC_LSHIFT) && !mKeyboard->isKeyDown(OIS::KC_Z))
	{
			engine->entityMgr->playerEntity->acc = 0;

	}

	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_SPACE)){
		DebugDrawer::getSingleton().drawLine(engine->entityMgr->playerEntity->position, engine->entityMgr->playerEntity->position + (-100)* engine->entityMgr->playerEntity->actualFacing.zAxis() , Ogre::ColourValue::White);
		engine->entityMgr->playerEntity->weapons[0]->Fire(dt);
	}

/*
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_LCONTROL)){
		keyboardTimer = keyTime;
		engine->entityMgr->playerEntity->acc = -1;
	}
	*/
/*
	if((keyboardTimer < 0) && !(mKeyboard->isKeyDown(OIS::KC_LSHIFT) != mKeyboard->isKeyDown(OIS::KC_LCONTROL))){
		keyboardTimer = keyTime;
		engine->entityMgr->playerEntity->acc = 0;
	}
*/
	//Player Direction Controls
		//YAW
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD8)){
		resetKT = true;
		relativeFaceAdjust.x -= deltaDesiredHeading;
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD2)){
		resetKT = true;
		relativeFaceAdjust.x += deltaDesiredHeading;
	}
		//Yaw, ideally
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD4)){
		resetKT = true;
		relativeFaceAdjust.y -= deltaDesiredHeading;
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD6)){
		resetKT = true;
		relativeFaceAdjust.y += deltaDesiredHeading;
	}

		//Roll?
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD7)){
		resetKT = true;
		relativeFaceAdjust.z -= deltaDesiredHeading;
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD9)){
		resetKT = true;
		relativeFaceAdjust.z += deltaDesiredHeading;
	}

	if(resetKT) keyboardTimer = keyTime;


	engine->entityMgr->playerEntity->desiredRotation = engine->entityMgr->playerEntity->desiredRotation + relativeFaceAdjust;
}

void InputMgr::LoadLevel(){

}

bool InputMgr::keyPressed(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& me){
	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id){
    if (engine->uiMgr->mTrayMgr->injectMouseDown(me, id)) return true;
	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
	if (engine->uiMgr->mTrayMgr->injectMouseUp(me, mid)) return true;
	return true;
}

//check if ms.width and ms.height need to be adjusted when things change
void InputMgr::HandleMouseSelection(const OIS::MouseEvent &me){

}
/*
bool InputMgr::buttonHit(OgreBites::Button *button)
{
	std::cout << "do I ever happen" << std::endl;
	    if(button->getName() == "helpBtn"){
	    	std::cout << "Help Button pressed" << std::endl;
	    	engine->uiMgr->uiState = ReSplashMenuState;
	    }
	return true;
}
*/
