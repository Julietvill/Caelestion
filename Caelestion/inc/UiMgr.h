/*
 * UiMgr.h
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */

#ifndef INC_UIMGR_H_
#define INC_UIMGR_H_

#include <MenuStates.h>
#include <OgreWindowEventUtilities.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <Mgr.h>
#include <SdkTrays.h>



class UiMgr : public Mgr, public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener, public Ogre::WindowEventListener, public OgreBites::SdkTrayListener
{
private:


protected:
	virtual void windowResized(Ogre::RenderWindow *rw);
	virtual void windowClosed(Ogre::RenderWindow *rw);

    virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual void buttonHit(OgreBites::Button *b);

    void itemSelected(OgreBites::SelectMenu *m);

public:

	UiMgr(Engine *engine);
	~UiMgr();
	virtual void Init();
	virtual void Tick(float dt);
	virtual void LoadLevel();
	virtual void stop();

	OgreBites::InputContext mInputContext;
	OgreBites::SdkTrayManager* mTrayMgr;
	Ogre::OverlaySystem* mOverlaySystem;

	menuStates uiState;
	menuStates prevState;

private:
	OgreBites::Button *helpBtn;
	OgreBites::Button *creditsBtn;
	OgreBites::Button *GladiusBtn;
	OgreBites::Button *HastatusBtn;
	OgreBites::Button *friendlythreeBtn;
	OgreBites::Button *playPauseBtn;

	OgreBites::Label *mLabel;
	OgreBites::Label *GladiusLbl;
	OgreBites::Label *HastatusLbl;
	OgreBites::Label *waveLbl;
	OgreBites::Label *pauseLbl;

	OgreBites::ProgressBar *hp;
};

#endif /* INC_UIMGR_H_ */
