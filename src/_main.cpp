//geode
#include <Geode/Geode.hpp>
using namespace geode::prelude;

#include <Geode/modify/GJGarageLayer.hpp>
class $modify(GJGarageLayerExt, GJGarageLayer) {
	int currentSwing;
    void onSwings(cocos2d::CCObject* pSender) {
        currentSwing = GameManager::sharedState()->getIntGameVariable("6969");
        currentSwing = currentSwing == 0 ? 1 : currentSwing;
        FLAlertLayer* SwingSelLayer_ = nullptr;
        SwingSelLayer_ = FLAlertLayer::create(nullptr,
            "Select Swing",
            "\n \n \n",
            "Close", nullptr, 220.000f
        );
        SwingSelLayer_->show();
        CCMenuItemSpriteExtra* edit_rightBtn_001 = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("edit_rightBtn_001.png"), this, menu_selector(GJGarageLayerExt::nextSwing));
        edit_rightBtn_001->setPositionY(58.000f);
        edit_rightBtn_001->setPositionX(58.000f);
        edit_rightBtn_001->setSizeMult(1.500f);
        edit_rightBtn_001->CCMenuItemSpriteExtra::setScale(1.350f);
        SwingSelLayer_->m_buttonMenu->addChild(edit_rightBtn_001);
        CCMenuItemSpriteExtra* edit_leftBtn_001 = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("edit_leftBtn_001.png"), this, menu_selector(GJGarageLayerExt::backwardSwing));
        edit_leftBtn_001->setPositionY(58.000f);
        edit_leftBtn_001->setPositionX(-58.000f);
        edit_leftBtn_001->setSizeMult(2.500f);
        edit_leftBtn_001->CCMenuItemSpriteExtra::setScale(1.350f);
        SwingSelLayer_->m_buttonMenu->addChild(edit_leftBtn_001);
        std::stringstream num;
        for (int ie = 1; ie < 99; ++ie) {
            num << std::setw(2) << std::setfill('0') << ie;
            CCSprite* swingPrevPt1 = CCSprite::createWithSpriteFrameName(("swing_" + num.str() + "_001.png").c_str());
            if (swingPrevPt1) {
                //swingPrev setup
                CCNodeContainer* swingPrev = CCNodeContainer::create();
                swingPrev->setContentSize(swingPrevPt1->getContentSize());
                //pt1
                swingPrevPt1->setColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor()));
                swingPrevPt1->setPosition(swingPrev->getContentSize() / 2);
                swingPrev->addChild(swingPrevPt1);
                //pt2
                CCSprite* swingPrevPt2 = CCSprite::create();
                swingPrevPt2->setPosition(swingPrev->getContentSize() / 2);
                swingPrevPt2->setColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2()));
                swingPrev->addChild(swingPrevPt2, -5);
                CCSpriteFrame* pt2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + num.str() + "_2_001.png").c_str());
                if (pt2) swingPrevPt2->setDisplayFrame(pt2); else swingPrevPt2->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("edit_eeNone2Btn_001.png"));
                //pt3
                CCSprite* swingPrevPt3 = CCSprite::create();
                swingPrevPt3->setPosition(swingPrev->getContentSize() / 2);
                swingPrev->addChild(swingPrevPt3);
                CCSpriteFrame* pt3 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + num.str() + "_extra_001.png").c_str());
                if (pt3) swingPrevPt3->setDisplayFrame(pt3);
                //pt4
                CCSprite* swingPrevPt4 = CCSprite::create();
                swingPrevPt4->setPosition(swingPrev->getContentSize() / 2);
                swingPrevPt4->setColor(GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2()));
                if (GameManager::sharedState()->getPlayerGlow()) swingPrev->addChild(swingPrevPt4, -5);
                CCSpriteFrame* pt4 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + num.str() + "_glow_001.png").c_str());
                if (pt4) swingPrevPt4->setDisplayFrame(pt4); else swingPrevPt4->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("edit_eeNone2Btn_001.png"));
                /*
                */
                //item
                CCMenuItemSpriteExtra* CCMenuItemSpriteExtra_ = CCMenuItemSpriteExtra::create(swingPrev, CCMenuItemSpriteExtra_, nullptr);
                CCMenuItemSpriteExtra_->setPositionY(58.000f);
                CCMenuItemSpriteExtra_->CCMenuItemSpriteExtra::setScale(1.200f);
                if (ie != currentSwing) CCMenuItemSpriteExtra_->setVisible(false);
                SwingSelLayer_->m_buttonMenu->addChild(CCMenuItemSpriteExtra_, 0, ie);
            }
            num.str("");
        }
    }
    void saveSelectedSwing(cocos2d::CCObject* pSender) {
        //save
        GameManager::sharedState()->setIntGameVariable("6969", currentSwing);
    }
    void nextSwing(cocos2d::CCObject* pSender) {
        //stop if less than 1
        //if (currentSwing == 1) return;
        //nextSwingPrev
        auto nextSwingPrev = dynamic_cast<CCNode*>(pSender)->getParent()->getChildByTag(currentSwing + 1);
        if (!nextSwingPrev) return;
        nextSwingPrev->setVisible(true);
        //currentSwingPrev
        auto currentSwingPrev = dynamic_cast<CCNode*>(pSender)->getParent()->getChildByTag(currentSwing);
        if (!currentSwingPrev) return;
        currentSwingPrev->setVisible(false);
        //decr
        ++currentSwing;
        //save...
        saveSelectedSwing(pSender);
    }
    void backwardSwing(cocos2d::CCObject* pSender) {
        //stop if less than 1
        if (currentSwing == 1) return;
        //nextSwingPrev
        auto nextSwingPrev = dynamic_cast<CCNode*>(pSender)->getParent()->getChildByTag(currentSwing - 1);
        if (!nextSwingPrev) return;
        nextSwingPrev->setVisible(true);
        m_playerPreview = SimplePlayer::create(1);
        m_playerPreview->updatePlayerFrame(1, IconType::Ship);
        //currentSwingPrev
        auto currentSwingPrev = dynamic_cast<CCNode*>(pSender)->getParent()->getChildByTag(currentSwing);
        if (!currentSwingPrev)return;
        currentSwingPrev->setVisible(false);
        //decr
        --currentSwing;
        //save...
        saveSelectedSwing(pSender);
    }
	bool init() {
		GJGarageLayer::init();
		if (!Mod::get()->getSettingValue<bool>("TouchGarage")) return true;

		//pSwingAttition
		CCMenuItemSpriteExtra* pSwingAttition = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("gj_swingBtn_off_001.png"), this, menu_selector(GJGarageLayerExt::onSwings));
		//pSwingAttition->setPositionX(168.000f);
		pSwingAttition->CCMenuItemSpriteExtra::setScale(0.900f);
		this->m_tabToggleDeathEffect->getParent()->addChild(pSwingAttition);

		return true;
	}
};

bool bIsSwing;

#include <Geode/modify/PlayLayer.hpp>
class $modify(PlayLayerExt, PlayLayer) {
	void updateProgressbar() {
		PlayLayer::updateProgressbar();
        //this->m_percentLabel->setString(bIsSwing ? "bIsSwing" : "!bIsSwing");
		//fire
		if (this->m_isDead) {
			//m_player1
			this->m_player1->removeChildByTag(5903);//fup
			this->m_player1->removeChildByTag(7638);//fmid
			this->m_player1->removeChildByTag(9562);//fdown
			this->m_player1->removeChildByTag(5903);//fup
			this->m_player1->removeChildByTag(7638);//fmid
			this->m_player1->removeChildByTag(9562);//fdown
			//m_player2
			this->m_player2->removeChildByTag(5903);//fup
			this->m_player2->removeChildByTag(7638);//fmid
			this->m_player2->removeChildByTag(9562);//fdown
			this->m_player2->removeChildByTag(5903);//fup
			this->m_player2->removeChildByTag(7638);//fmid
			this->m_player2->removeChildByTag(9562);//fdown
		}
	}
	void resetLevel() {
		PlayLayer::resetLevel();
		if (bIsSwing && !this->m_isPracticeMode || !this->m_player1->m_isShip) {
			bIsSwing = false;
		}
	}
};

void updateToSwing(PlayerObject* __this) {
    //swing_01_001.png
    //self->m_pPlayer1->unk50C->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ship_82_001.png"));
    //self->m_pPlayer1->unk50C->setOpacity(90);
    //squarebase using cube and ball
    //cocos2d::CCSprite* unk4E8;-squarebase1
    //cocos2d::CCSprite* unk4EC;-squarebase2
    //cocos2d::CCSprite* unk4F0;-squarebaseExtra
    //cocos2d::CCSprite* unk4F4;-squarebaseGlow
    //vehicle using ship and bird
    //cocos2d::CCSprite* unk4F8;-vehicle1
    //cocos2d::CCSprite* unk4FC;-vehicle2
    //cocos2d::CCSprite* unk500;-bird3
    //cocos2d::CCSprite* unk504;-vehicleExtra
    //cocos2d::CCSprite* unk508;-vehicleGlow

    if (!bIsSwing) {
        if (__this->m_vehicleSpriteSecondary) __this->m_vehicleSpriteSecondary->setAnchorPoint({ 0.500f, 0.500f });
        if (__this->m_vehicleSpriteWhitener) __this->m_vehicleSpriteWhitener->setAnchorPoint({ 0.500f, 0.500f });
        return;
    };

    int currentSwing = GameManager::sharedState()->getIntGameVariable("6969");
    currentSwing = currentSwing == 0 ? 1 : currentSwing;
    std::string strnum = ((std::stringstream() << std::setw(2) << std::setfill('0') << currentSwing).str());
    //setframe
    CCSpriteFrame* pt1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + strnum + "_001.png").c_str());
    if (pt1) __this->m_vehicleSprite->setDisplayFrame(pt1); else __this->m_vehicleSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("edit_eeNoneBtn_001.png"));
    CCSpriteFrame* pt2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + strnum + "_2_001.png").c_str());
    if (pt2) __this->m_vehicleSpriteSecondary->setDisplayFrame(pt2); else __this->m_vehicleSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("edit_eeNoneBtn_001.png"));
    CCSpriteFrame* pt3 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + strnum + "_extra_001.png").c_str());
    if (pt3) __this->m_vehicleSpriteWhitener->setDisplayFrame(pt3); __this->m_vehicleSpriteWhitener->setVisible(pt3);
    CCSpriteFrame* pt4 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + strnum + "_glow_001.png").c_str());
    if (pt4) __this->m_vehicleGlow->setDisplayFrame(pt4); else __this->m_vehicleSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("edit_eeNoneBtn_001.png"));
    //set pos
    __this->m_vehicleSprite->setPosition({
        __this->m_vehicleSprite->displayFrame()->getOriginalSize().width / __this->m_vehicleSprite->getContentSize().width,
        __this->m_vehicleSprite->displayFrame()->getOriginalSize().height / __this->m_vehicleSprite->getContentSize().height,
        });
    __this->m_vehicleSpriteSecondary->setPosition(__this->m_vehicleSprite->getContentSize() / 2);// ({ 16.600f, 16.200f });
    __this->m_vehicleSpriteWhitener->setPosition(__this->m_vehicleSprite->getContentSize() / 2);// ({ 16.800f, 16.200f });
    __this->m_vehicleGlow->setPosition({
        __this->m_vehicleGlow->displayFrame()->getOriginalSize().width / __this->m_vehicleGlow->getContentSize().width,
        __this->m_vehicleGlow->displayFrame()->getOriginalSize().height / __this->m_vehicleGlow->getContentSize().height,
        });
}

void updateSwingFire(PlayerObject* __this) {
    CCSprite* UpperFireThing = CCSprite::createWithSpriteFrameName("fireBoost_001.png");
    CCSprite* FireThing = CCSprite::createWithSpriteFrameName("fireBoost_001.png");
    CCSprite* DownFireThing = CCSprite::createWithSpriteFrameName("fireBoost_001.png");
    //UpperFireThing
    if (!__this->getChildByTag(5903)) {
        UpperFireThing->setAnchorPoint({ 0.500f, 1.000f });
        UpperFireThing->setPosition({ -9.340f, 12.000f });
        UpperFireThing->setRotation(134.000f);
        __this->addChild(UpperFireThing, -1, 5903);
    }
    //update UpperFireThing
    if (__this->getChildByTag(5903)) {
        float a1 = 0.7f;
        CCAction* fireHere = CCRepeatForever::create(
            CCSequence::create(//really grabed from PlayerFireBoostSprite::loopFireAnimation(float *a1) 
                CCScaleTo::create(0.06f, a1 * 1.2, a1),
                CCScaleTo::create(0.06f, a1 * 0.6, a1 * 1.5),
                nullptr)
        );
        fireHere->setTag(69);
        CCAction* noFire = CCRepeatForever::create(CCScaleTo::create(0.2f, 0.0f, 0.0f));
        noFire->setTag(32);
        if (__this->m_isUpsideDown) {
            if (__this->getChildByTag(5903)->getActionByTag(69)) __this->getChildByTag(5903)->stopAllActions();
            if (!__this->getChildByTag(5903)->getActionByTag(32)) __this->getChildByTag(5903)->runAction(noFire);
        }
        else {
            if (__this->getChildByTag(5903)->getActionByTag(32)) __this->getChildByTag(5903)->stopAllActions();
            if (!__this->getChildByTag(5903)->getActionByTag(69)) __this->getChildByTag(5903)->runAction(fireHere);
        }
    }
    //FireThing middle one
    if (!__this->getChildByTag(7638)) {
        FireThing->setAnchorPoint({ 0.500f, 1.000f });
        FireThing->setPosition({ -14.000f, 1.000f });
        FireThing->setRotation(90.000f);//1.2f
        float a1 = 0.9f;
        FireThing->runAction(CCRepeatForever::create(CCSequence::create(//really grabed from PlayerFireBoostSprite::loopFireAnimation(float *a1) 
            CCScaleTo::create(0.06f, a1 * 1.2, a1),
            CCScaleTo::create(0.06f, a1 * 0.6, a1 * 1.5),
            nullptr)));
        __this->addChild(FireThing, -1, 7638);
    }
    //DownFireThing
    if (!__this->getChildByTag(9562)) {
        DownFireThing->setAnchorPoint({ 0.500f, 1.000f });
        DownFireThing->setPosition({ -9.340f, -10.140f });
        DownFireThing->setRotation(42.000f);
        __this->addChild(DownFireThing, -1, 9562);
    }
    //update DownFireThing
    if (__this->getChildByTag(9562)) {
        float a1 = 0.75f;
        CCAction* fireHere = CCRepeatForever::create(
            CCSequence::create(//really grabed from PlayerFireBoostSprite::loopFireAnimation(float *a1) 
                CCScaleTo::create(0.06f, a1 * 1.2, a1),
                CCScaleTo::create(0.06f, a1 * 0.6, a1 * 1.5),
                nullptr)
        );
        fireHere->setTag(69);
        CCAction* noFire = CCRepeatForever::create(CCScaleTo::create(0.2f, 0.0f, 0.0f));
        noFire->setTag(32);
        if (__this->m_isUpsideDown) {
            if (__this->getChildByTag(9562)->getActionByTag(32)) __this->getChildByTag(9562)->stopAllActions();
            if (!__this->getChildByTag(9562)->getActionByTag(69)) __this->getChildByTag(9562)->runAction(fireHere);
        }
        else {
            if (__this->getChildByTag(9562)->getActionByTag(69)) __this->getChildByTag(9562)->stopAllActions();
            if (!__this->getChildByTag(9562)->getActionByTag(32)) __this->getChildByTag(9562)->runAction(noFire);
        }
    }
}

static void update_swing_copter(PlayerObject* __this, const float delta) {
    if (!__this || !__this->m_isShip) return;
    __this->setScaleY((fabs(__this->getScaleY())));
    __this->deactivateParticle();
    __this->m_gravity = 0.06;
    updateSwingFire(__this);
    updateToSwing(__this);

    const auto _direction = __this->m_isUpsideDown ? -1.f : 1.f;
    const auto _size = (__this->m_vehicleSize != true) ? .85f : 1.f;
    const auto _gravity = (std::fabs(__this->m_jumpAccel) > 6.) ? __this->m_gravity + 1. : __this->m_gravity;

    const auto modifier = -.5 * _gravity * delta * _direction / _size;
    const auto y_acceleration = __this->m_jumpAccel + modifier;

    if (std::fabs(__this->m_jumpAccel) <= 6. || std::fabs(y_acceleration) <= std::fabs(__this->m_jumpAccel))
        __this->m_jumpAccel = y_acceleration;

    if (__this->m_isHolding && __this->m_hasJustHeld) {
        __this->m_hasJustHeld = false;
        __this->m_isHolding = false;
        __this->flipGravity(!__this->m_isUpsideDown, true);
    }
}

#include <Geode/modify/PlayerObject.hpp>
class $modify(PlayerObjectExt, PlayerObject) {
	void update(float delta) {

		if (Mod::get()->getSettingValue<bool>("ReplaceShip")) bIsSwing = this->m_isShip;

		//sWin copter
		this->m_vehicleGroundParticles->setVisible(bIsSwing ? false : true);
		if (!bIsSwing) {
			if (this->m_gravity == 0.06) this->m_gravity = 0.958199;
		}

		//fire
		if (!bIsSwing) {
			this->removeChildByTag(5903);
			this->removeChildByTag(7638);
			this->removeChildByTag(9562);
		}

		//ORIGINAL and SWING UPDATE
		PlayerObject::update(delta);
		bIsSwing ? update_swing_copter(this, delta) : update_swing_copter(nullptr, delta);

	}
};

#include <Geode/modify/GameObject.hpp>
class $modify(GameObjectExt, GameObject) {
    void createAndAddPortalParticle(const char* path, int zOrder) {
        if (this->m_particleSystem)
        {
            CC_SAFE_RELEASE(this->m_particleSystem);
            this->m_particleSystem->cleanup();
            this->m_particleSystem = nullptr;
        }
        this->m_particleSystem = CCParticleSystemQuad::create(path);
        this->m_particleSystem->setZOrder(zOrder);
        this->m_particleSystem->retain();
        this->m_particleSystem->stopSystem();
        this->m_particleSystem->setPositionType(kCCPositionTypeGrouped);
        this->m_particleSystem->setRotation(getRotation());
        //if (auto pGMPlayLayer = GameManager::sharedState()->getPlayLayer()) pGMPlayLayer
        this->addChild(m_particleSystem);
        this->m_particleSystem->runAction(CCRepeatForever::create(CCMoveTo::create(0.0, {
                (this->getContentSize().width / 2) - 5,
                this->getContentSize().height / 2
            })));
        this->m_portalPosition.y = -9999;
    }
	void activatedByPlayer(GameObject* player) {
		GameObject::activatedByPlayer(player);
		if (!Mod::get()->getSettingValue<bool>("AddSwingPortal")) return;
		if ("SwingCopter") {
			if (this->m_objectID == 1933) {
				bIsSwing = true;
				//player->toggleRobotMode(true);
                dynamic_cast<PlayerObject*>(player)->m_lastActivatedPortal = GameObject::createWithKey(1933);
				dynamic_cast<PlayerObject*>(player)->toggleFlyMode(true);
			}
			else if (
				this->getType() == GameObjectType::ShipPortal ||
				this->getType() == GameObjectType::CubePortal ||
				this->getType() == GameObjectType::BallPortal ||
				this->getType() == GameObjectType::UfoPortal ||
				this->getType() == GameObjectType::WavePortal ||
				this->getType() == GameObjectType::RobotPortal ||
				this->getType() == GameObjectType::SpiderPortal) {
				if (this->m_objectID == 13 && bIsSwing) {
					dynamic_cast<PlayerObject*>(player)->toggleRobotMode(true);
					dynamic_cast<PlayerObject*>(player)->toggleFlyMode(true);
				}
				bIsSwing = false;
			}
		}
	}
	void customSetup() {
		GameObject::customSetup();
		
		if (
			(Mod::get()->getSettingValue<bool>("AddSwingPortal") && this->m_objectID == 1933) ||
			(Mod::get()->getSettingValue<bool>("ReplaceShip") && this->m_objectID == 13)
			) {//swing portal or ship
			if (Mod::get()->getSettingValue<bool>("AddBackPart") && !this->m_editor) {
				std::string sSwingPortalFrameName = "portal_18_back_001.png";
				if (!CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(sSwingPortalFrameName.c_str())) sSwingPortalFrameName = "portal_17_back_001.png";
				CCSprite* pPortalBack = CCSprite::createWithSpriteFrameName(sSwingPortalFrameName.c_str());
				pPortalBack->setPosition({
					this->getContentSize().width / 2,
					this->getContentSize().height / 2
					});
				this->addChild(pPortalBack);
			}
		}

		if (!Mod::get()->getSettingValue<bool>("AddSwingPortal")) return;

		if (this->m_objectID == 1933) {//swing portal
			this->m_modifier = true;
			this->m_objectType = GameObjectType::UfoPortal;
			this->m_objectSize.setSize(25.000000, 75.000000);
			if( 
                (!this->m_editor && Mod::get()->getSettingValue<bool>("AddParticles"))
                ||
                (Mod::get()->getSettingValue<bool>("EditorParticles") && Mod::get()->getSettingValue<bool>("AddParticles"))
             ) this->createAndAddPortalParticle("portalEffect02.plist", 3);
		}

	}
};

#include <Geode/modify/EditorUI.hpp>
class $modify(EditorUIExt, EditorUI) {
	void setupCreateMenu() {
		EditorUI::setupCreateMenu();
		if (!Mod::get()->getSettingValue<bool>("AddSwingPortal")) return;
		//tab
		if (auto tab = (EditButtonBar*)(this->m_createButtonBars->objectAtIndex(Mod::get()->getSettingValue<int64_t>("AddObjectToTab")))){
			auto AddObjectAtIndex = Mod::get()->getSettingValue<int64_t>("AddObjectAtIndex");
            tab->m_buttonArray->insertObject(this->getCreateBtn(1933, 4), AddObjectAtIndex);
            tab->loadFromItems(
                tab->m_buttonArray, 
                GameManager::sharedState()->getIntGameVariable("0049"), 
                GameManager::sharedState()->getIntGameVariable("0050"), 
                (bool)"idk");
        ;}
	}
};

#include <Geode/modify/ObjectToolbox.hpp>
class $modify(ObjectToolboxExt, ObjectToolbox) {
	bool init() {
        ObjectToolbox::init();
        std::string sSwingPortalFrameName = "portal_18_front_001.png";
        if (!CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(sSwingPortalFrameName.c_str())) sSwingPortalFrameName = "portal_17_front_001.png";
        if (Mod::get()->getSettingValue<bool>("AddSwingPortal")) ObjectToolbox::sharedState()->addObject(1933, sSwingPortalFrameName.c_str());
        if (Mod::get()->getSettingValue<bool>("ReplaceShip")) ObjectToolbox::sharedState()->addObject(13, sSwingPortalFrameName.c_str());
        return true;
    }
};