/*
 * GfxMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef GFXMGR_H_
#define GFXMGR_H_

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

#include <Mgr.h>
#include <Sample.h>

#include <Entity381.h>

class GfxMgr:
		public Mgr,
		public Ogre::WindowEventListener,
		public Ogre::FrameListener {
public:
	GfxMgr(Engine *engine);
	virtual ~GfxMgr();

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	virtual void windowClosed(Ogre::RenderWindow* rw);
//---------------
	void Init();
	void LoadLevel();
	void Tick(float dt);
	void Stop();
	void setUpCamera();

	void MakeGround();
	Ogre::Plane oceanSurface;
	void MakeSky();

	//Ogre related stuff
	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	Ogre::SceneNode *cameraNode;
	Ogre::SceneNode* yawCameraNode;
	Ogre::SceneNode* pitchCameraNode;

	Ogre::Vector3 difference;

};

#endif /* GFXMGR_H_ */
