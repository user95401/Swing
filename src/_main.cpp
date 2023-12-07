#include "mod_utils.hpp"
#include "hooks.hpp"
#include "jute.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gd;

class ReplaceAllFramesByName {
public:
    inline static std::string by;
    inline static std::string to;
};
inline FLAlertLayer* popuptoreplace;

#define TouchGarage "TouchGarage"
#define AddSwingPortal "AddSwingPortal"
#define AddObjectAtIndex "AddObjectAtIndex"
#define AddObjectToTab "AddObjectToTab"
#define AddBackPart "AddBackPart"
#define AddParticles "AddParticles"
#define ReplaceShip "ReplaceShip"

void InitializeConfig() {
    ModUtils::log(__func__);
    std::filesystem::create_directories("geode/config");
    //Swing
    CSimpleIni Swing;
    Swing.LoadFile("geode/config/Swing.ini");
    //TouchGarage; add stuff on garage layer
    if (!(Swing.KeyExists("Swing", "TouchGarage")))
        Swing.SetBoolValue("Swing", "TouchGarage", true, "; add stuff on garage layer");
    //AddSwingPortal; add custom swing portal game object
    if (!(Swing.KeyExists("Swing", "AddSwingPortal")))
        Swing.SetBoolValue("Swing", "AddSwingPortal", true, "; add custom swing portal game object");
    //AddObjectAtIndex; to change place in create tab
    if (!(Swing.KeyExists("Swing", "AddObjectAtIndex")))
        Swing.SetLongValue("Swing", "AddObjectAtIndex", 29, "; to change place in create tab");
    //AddObjectAtIndex; to change place in create tab
    if (!(Swing.KeyExists("Swing", "AddObjectToTab")))
        Swing.SetLongValue("Swing", "AddObjectToTab", 6, "; to change tab");
    //AddBackPart; add back part sprite for custom swing portal
    if (!(Swing.KeyExists("Swing", "AddBackPart")))
        Swing.SetBoolValue("Swing", "AddBackPart", true, "; add back part sprite for custom swing portal");
    //AddParticles; add particles for portal
    if (!(Swing.KeyExists("Swing", "AddParticles")))
        Swing.SetBoolValue("Swing", "AddParticles", true, "; add particles for portal");
    //ReplaceShip; ship becomes swing
    if (!(Swing.KeyExists("Swing", "ReplaceShip")))
        Swing.SetBoolValue("Swing", "ReplaceShip", false, "; ship becomes swing");
    //save Swing
    Swing.SaveFile("geode/config/Swing.ini");
}

void(__thiscall* FLAlertLayer_show_0x23560)(FLAlertLayer* self);//0x23560
void __fastcall FLAlertLayer_show_0x23560_H(FLAlertLayer* self, void*) {
    if (popuptoreplace) self = popuptoreplace;
    popuptoreplace = nullptr;
    FLAlertLayer_show_0x23560(self);
}

class GJGarageLayerExt : public GJGarageLayer {
public:
    static GJGarageLayerExt* create() {
        return reinterpret_cast<GJGarageLayerExt * (__fastcall*)()>(base + 0x125220)();
    }
    int currentSwing;
    void onSwings(cocos2d::CCObject* pSender) {
        currentSwing = GameManager::sharedState()->getIntGameVariable("6969");
        currentSwing = currentSwing == 0 ? 1 : currentSwing;
        FLAlertLayer* SwingSelLayer_ = nullptr;
        SwingSelLayer_ = FLAlertLayer::create(nullptr,
            "Select Swing",
            "Close", nullptr, 220.000f,
            "\n \n \n"
        );
        SwingSelLayer_->show();
        CCMenuItemSpriteExtra* edit_rightBtn_001 = CCMenuItemSpriteExtra::create(ModUtils::createSprite("edit_rightBtn_001.png"), this, menu_selector(GJGarageLayerExt::nextSwing));
        edit_rightBtn_001->setPositionY(58.000f);
        edit_rightBtn_001->setPositionX(58.000f);
        edit_rightBtn_001->setSizeMult(1.500f);
        edit_rightBtn_001->CCMenuItemSpriteExtra::setScale(1.350f);
        SwingSelLayer_->m_pButtonMenu->addChild(edit_rightBtn_001);
        CCMenuItemSpriteExtra* edit_leftBtn_001 = CCMenuItemSpriteExtra::create(ModUtils::createSprite("edit_leftBtn_001.png"), this, menu_selector(GJGarageLayerExt::backwardSwing));
        edit_leftBtn_001->setPositionY(58.000f);
        edit_leftBtn_001->setPositionX(-58.000f);
        edit_leftBtn_001->setSizeMult(2.500f);
        edit_leftBtn_001->CCMenuItemSpriteExtra::setScale(1.350f);
        SwingSelLayer_->m_pButtonMenu->addChild(edit_leftBtn_001);
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
                SwingSelLayer_->m_pButtonMenu->addChild(CCMenuItemSpriteExtra_, 0, ie);
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
        m_pPlayerPreview = SimplePlayer::create(1);
        m_pPlayerPreview->updatePlayerFrame(1, IconType::kIconTypeShip);
        //currentSwingPrev
        auto currentSwingPrev = dynamic_cast<CCNode*>(pSender)->getParent()->getChildByTag(currentSwing);
        if (!currentSwingPrev)return;
        currentSwingPrev->setVisible(false);
        //decr
        --currentSwing;
        //save...
        saveSelectedSwing(pSender);
    }
};

bool(__thiscall* GJGarageLayer_init)(GJGarageLayerExt*);//0x1255D0
bool __fastcall GJGarageLayer_init_H(GJGarageLayerExt* self) {
    GJGarageLayer_init(self);
    CSimpleIni Swing;
    Swing.LoadFile("geode/config/Swing.ini");
    if (!Swing.GetBoolValue("Swing", TouchGarage, true)) return true;

    CCMenu* pTabToggleBarMenu = CCMenu::create();
    CCArray* pObjectArray = self->getChildren();
    for (int i = 0; i < pObjectArray->count(); i++) {
        auto pObject = pObjectArray->objectAtIndex(i);
        if (auto pTabToggleBarMenuMaybe = dynamic_cast<CCMenu*>(pObject)) {
            pTabToggleBarMenu = pTabToggleBarMenuMaybe->getChildrenCount() > 6 && pTabToggleBarMenuMaybe->getChildrenCount() < 10 ? pTabToggleBarMenuMaybe : pTabToggleBarMenu;
        }
    }
    //why
    pTabToggleBarMenu->setTouchMode(ccTouchesMode::kCCTouchesOneByOne);

    twoTimesBoolCallEscapeByParrentNode(self);

    //new menu :skull:
    CCMenu* pSwingAttitionMenu = CCMenu::create();
    self->addChild(pSwingAttitionMenu, pSwingAttitionMenu->getZOrder(), 3452);
    pSwingAttitionMenu->setPosition(pTabToggleBarMenu->getPosition());
    //pSwingAttition
    CCMenuItemSpriteExtra* pSwingAttition = CCMenuItemSpriteExtra::create(ModUtils::createSprite("gj_swingBtn_off_001.png"), self, menu_selector(GJGarageLayerExt::onSwings));
    pSwingAttition->setPositionX(168.000f);
    pSwingAttition->CCMenuItemSpriteExtra::setScale(0.900f);
    pSwingAttitionMenu->addChild(pSwingAttition, 0, 8639);

    return true;
}

bool bIsSwing;
class PlayLayerExt : public PlayLayer {
public:
};

void(__thiscall* updateProgressbar)(PlayLayerExt*);
void __fastcall updateProgressbar_H(PlayLayerExt* self) {
    updateProgressbar(self);
    //fire
    if (self->m_isDead) {
        self->m_pPlayer1->removeChildByTag(5903);//fup
        self->m_pPlayer1->removeChildByTag(7638);//fmid
        self->m_pPlayer1->removeChildByTag(9562);//fdown
        self->m_pPlayer2->removeChildByTag(5903);//fup
        self->m_pPlayer2->removeChildByTag(7638);//fmid
        self->m_pPlayer2->removeChildByTag(9562);//fdown
    }
}

void(__thiscall* PlayLayer_resetLevel)(PlayLayerExt*);
void __fastcall PlayLayer_resetLevel_H(PlayLayerExt* self) {
    PlayLayer_resetLevel(self);
    if (bIsSwing && !self->m_isPracticeMode || !self->m_pPlayer1->m_isShip) {
        bIsSwing = false;
    }
}

void updateToSwing(gd::PlayerObject* __this) {
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
        if (__this->unk4FC) __this->unk4FC->setAnchorPoint({ 0.500f, 0.500f });
        if (__this->unk504) __this->unk504->setAnchorPoint({ 0.500f, 0.500f });
        return;
    };

    int currentSwing = GameManager::sharedState()->getIntGameVariable("6969");
    currentSwing = currentSwing == 0 ? 1 : currentSwing;
    std::string strnum = ((std::stringstream() << std::setw(2) << std::setfill('0') << currentSwing).str());
    //setframe
    CCSpriteFrame* pt1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + strnum + "_001.png").c_str());
    if (pt1) __this->unk4F8->setDisplayFrame(pt1); else __this->unk4F8->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("edit_eeNoneBtn_001.png"));
    CCSpriteFrame* pt2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + strnum + "_2_001.png").c_str());
    if (pt2) __this->unk4FC->setDisplayFrame(pt2); else __this->unk4F8->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("edit_eeNoneBtn_001.png"));
    CCSpriteFrame* pt3 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + strnum + "_extra_001.png").c_str());
    if (pt3) __this->unk504->setDisplayFrame(pt3); __this->unk504->setVisible(pt3);
    CCSpriteFrame* pt4 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + strnum + "_glow_001.png").c_str());
    if (pt4) __this->unk508->setDisplayFrame(pt4); else __this->unk4F8->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("edit_eeNoneBtn_001.png"));
    //set pos
    __this->unk4F8->setPosition({
        __this->unk4F8->displayFrame()->getOriginalSize().width / __this->unk4F8->getContentSize().width,
        __this->unk4F8->displayFrame()->getOriginalSize().height / __this->unk4F8->getContentSize().height,
        });
    __this->unk4FC->setPosition(__this->unk4F8->getContentSize() / 2);// ({ 16.600f, 16.200f });
    __this->unk504->setPosition(__this->unk4F8->getContentSize() / 2);// ({ 16.800f, 16.200f });
    __this->unk508->setPosition({
        __this->unk508->displayFrame()->getOriginalSize().width / __this->unk508->getContentSize().width,
        __this->unk508->displayFrame()->getOriginalSize().height / __this->unk508->getContentSize().height,
        });
}

void updateSwingFire(gd::PlayerObject* __this) {
    CCSprite* UpperFireThing = ModUtils::createSprite("fireBoost_001.png");
    CCSprite* FireThing = ModUtils::createSprite("fireBoost_001.png");
    CCSprite* DownFireThing = ModUtils::createSprite("fireBoost_001.png");
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

static void update_swing_copter(gd::PlayerObject* __this, const float delta) {
    if (!__this || !__this->m_isShip) return;
    __this->setScaleY((fabs(__this->getScaleY())));
    __this->deactivateParticle();
    __this->m_gravity = 0.06;
    updateSwingFire(__this);
    updateToSwing(__this);

    const auto _direction = __this->m_isUpsideDown ? -1.f : 1.f;
    const auto _size = (__this->m_vehicleSize != true) ? .85f : 1.f;
    const auto _gravity = (std::fabs(__this->m_yAccel) > 6.) ? __this->m_gravity + 1. : __this->m_gravity;

    const auto modifier = -.5 * _gravity * delta * _direction / _size;
    const auto y_acceleration = __this->m_yAccel + modifier;

    if (std::fabs(__this->m_yAccel) <= 6. || std::fabs(y_acceleration) <= std::fabs(__this->m_yAccel))
        __this->m_yAccel = y_acceleration;

    if (__this->m_isHolding && __this->m_hasJustHeld) {
        __this->m_hasJustHeld = false;
        __this->m_isHolding = false;
        __this->flipGravity(!__this->m_isUpsideDown, true);
    }
}

void(__thiscall* PlayerObject_update) (gd::PlayerObject* __this, float delta);//0x1e8200
void  __fastcall  PlayerObject_update_H(gd::PlayerObject* __this, float delta) {

    CSimpleIni Swing;
    Swing.LoadFile("geode/config/Swing.ini");
    if (Swing.GetBoolValue("Swing", ReplaceShip, false)) bIsSwing = __this->m_isShip;

    //sWin copter
    __this->m_vehicleGroundParticles->setVisible(bIsSwing ? false : true);
    if (!bIsSwing) {
        if (__this->m_gravity == 0.06) __this->m_gravity = 0.958199;
    }

    //fire
    if (!bIsSwing) {
        __this->removeChildByTag(5903);
        __this->removeChildByTag(7638);
        __this->removeChildByTag(9562);
    }

    //ORIGINAL and SWING UPDATE
    PlayerObject_update(__this, delta);
    bIsSwing ? update_swing_copter(__this, delta) : update_swing_copter(nullptr, delta);

}

class GameObjectExt : public GameObject {
public:
    void createAndAddParticle(const char* path, int zOrder) {
        if (this->m_pParticleSystem)
        {
            CC_SAFE_RELEASE(this->m_pParticleSystem);
            this->m_pParticleSystem->cleanup();
            this->m_pParticleSystem = nullptr;
        }
        this->m_pParticleSystem = CCParticleSystemQuad::create(path);
        this->m_pParticleSystem->setZOrder(zOrder);
        this->m_pParticleSystem->retain();
        this->m_pParticleSystem->stopSystem();
        this->m_pParticleSystem->setPositionType(kCCPositionTypeGrouped);
        this->m_pParticleSystem->setRotation(getRotation());
        //if (auto pGMPlayLayer = GameManager::sharedState()->getPlayLayer()) pGMPlayLayer
        this->addChild(m_pParticleSystem);
        this->m_pParticleSystem->runAction(CCRepeatForever::create(CCMoveTo::create(0.0, {
                this->getContentSize().width / 2,
                this->getContentSize().height / 2
            })));
        this->m_obPortalPosition.y = -9999;
    }
};

void(__thiscall* GameObject_activateObject)(GameObjectExt*, PlayerObject*);//0xEF0E0
void __fastcall GameObject_activateObject_H(GameObjectExt* self, int, PlayerObject* player) {
    GameObject_activateObject(self, player);
    CSimpleIni Swing;
    Swing.LoadFile("geode/config/Swing.ini");
    if (!Swing.GetBoolValue("Swing", AddSwingPortal, true)) return;
    if ("SwingCopter") {
        if (self->m_nObjectID == 1933) {
            bIsSwing = true;
            player->toggleRobotMode(true);
            player->toggleFlyMode(true);
        }
        else if (self->m_nObjectType == kGameObjectTypeShipPortal ||
            self->m_nObjectType == kGameObjectTypeCubePortal ||
            self->m_nObjectType == kGameObjectTypeBallPortal ||
            self->m_nObjectType == kGameObjectTypeUfoPortal ||
            self->m_nObjectType == kGameObjectTypeWavePortal ||
            self->m_nObjectType == kGameObjectTypeRobotPortal ||
            self->m_nObjectType == kGameObjectTypeSpiderPortal) {
            if (self->m_nObjectID == 13 && bIsSwing) {
                player->toggleRobotMode(true);
                player->toggleFlyMode(true);
            }
            bIsSwing = false;
        }
    }
}

void(__thiscall* GameObject_customSetup)(GameObjectExt*);//0xd1c10
void __fastcall GameObject_customSetup_H(GameObjectExt* self, int) {
    GameObject_customSetup(self);
    CSimpleIni Swing;
    Swing.LoadFile("geode/config/Swing.ini");

    if (
        (Swing.GetBoolValue("Swing", AddSwingPortal, true) && self->m_nObjectID == 1933) ||
        (Swing.GetBoolValue("Swing", ReplaceShip, false) && self->m_nObjectID == 13)
        ) {//swing portal or ship
        if (Swing.GetBoolValue("Swing", AddBackPart, true) && !self->m_bEditor) {
            std::string sSwingPortalFrameName = "portal_18_back_001.png";
            if (!CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(sSwingPortalFrameName.c_str())) sSwingPortalFrameName = "portal_17_back_001.png";
            CCSprite* pPortalBack = CCSprite::createWithSpriteFrameName(sSwingPortalFrameName.c_str());
            pPortalBack->setPosition({
                self->getContentSize().width / 2,
                self->getContentSize().height / 2
                });
            self->addChild(pPortalBack);
        }
    }

    if (!Swing.GetBoolValue("Swing", AddSwingPortal, true)) return;

    if (self->m_nObjectID == 1933) {//swing portal
        self->m_bTrigger = true;
        self->m_nObjectType = GameObjectType::kGameObjectTypeShipPortal;
        self->m_obObjectSize.setSize(25.000000, 75.000000);
        if(!self->m_bEditor && Swing.GetBoolValue("Swing", AddParticles, true)) self->createAndAddParticle("portalEffect02.plist", 3);
    }

}

void(__thiscall* EditorUI_setupCreateMenu)(EditorUI*);
void __fastcall EditorUI_setupCreateMenu_H(EditorUI* self, void*) {
    EditorUI_setupCreateMenu(self);
    CSimpleIni Swing;
    Swing.LoadFile("geode/config/Swing.ini");
    if (!Swing.GetBoolValue("Swing", AddSwingPortal, true)) return;
    //tab
    if (auto tab = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(Swing.GetLongValue("Swing", AddObjectToTab, 6)))) {
        tab->insertButton(self->getCreateBtn(1933, 4), Swing.GetLongValue("Swing", AddObjectAtIndex, 29));
    }
}

void(__thiscall* ObjectToolbox_init)(ObjectToolbox*);
bool __fastcall ObjectToolbox_init_H(ObjectToolbox* self) {
    ObjectToolbox_init(self);
    CSimpleIni Swing;
    Swing.LoadFile("geode/config/Swing.ini");
    std::string sSwingPortalFrameName = "portal_18_front_001.png";
    if (!CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(sSwingPortalFrameName.c_str())) sSwingPortalFrameName = "portal_17_front_001.png";
    if (Swing.GetBoolValue("Swing", AddSwingPortal, true)) ObjectToolbox::sharedState()->addObject(1933, sSwingPortalFrameName.c_str());
    if (Swing.GetBoolValue("Swing", ReplaceShip, false)) ObjectToolbox::sharedState()->addObject(13, sSwingPortalFrameName.c_str());
    return true;
}


class ConfirmHandler : public cocos2d::CCLabelTTF, public FLAlertLayerProtocol {
public:
    ConfirmHandler* setDataString(std::string str) {
        this->setString(str.c_str());
        return this;
    }
    void FLAlert_Clicked(FLAlertLayer*, bool btn2) {
        //CCMessageBox(this->getString(), __FUNCTION__);
        if (!btn2);
        else {
            std::vector<std::string> DataString = ModUtils::explode(std::string(this->getString()), ',');
            if (DataString[0] == "!>OpenSwingSelectPop") {
                //CCMessageBox(DataString[0].c_str(), __FUNCTION__);
                GJGarageLayerExt::create()->onSwings(CCNode::create());
            }
            if (DataString[0] == "!FOpen") {
                //CCMessageBox(DataString[0].c_str(), __FUNCTION__);
                ShellExecute(NULL, ("open"), (CCFileUtils::sharedFileUtils()->fullPathForFilename(DataString[1].c_str(), 0).c_str()), NULL, NULL, 1);
            }
        }
    }
    static ConfirmHandler* create() {
        auto ret = new ConfirmHandler();
        if (ret && ret->init()) { ret->autorelease(); ret->retain(); }//robert 1 :D
        else { delete ret; ret = nullptr; }//robert -1
        return ret;
    }
    bool init() { return CCLabelTTF::init(); }
};

CCSprite* (__cdecl* CCSprite_createWithSpriteFrameName)(const char*);
CCSprite* CCSprite_createWithSpriteFrameName_H(const char* name) {
    if (ReplaceAllFramesByName::by != "" && ReplaceAllFramesByName::by == std::string(name)) name = ReplaceAllFramesByName::to.c_str();
    return CCSprite_createWithSpriteFrameName(name);
}

CCLabelBMFont* (__cdecl* CCLabelBMFont_create)(const char*, const char*);
CCLabelBMFont* CCLabelBMFont_create_H(const char* str, const char* fntFile) {
    //settings
    if ("settings") {
        //!>OpenSwingSelectPop
        if (strstr(std::string(str).c_str(), "!sign2,") && std::string(fntFile) == "bigFont.fnt") {
            ReplaceAllFramesByName::by = "GJ_infoIcon_001.png";
            ReplaceAllFramesByName::to = "d_sign_img_02_001.png";
            std::vector<std::string> ValueBombered = ModUtils::explode(str, ',');
            return CCLabelBMFont_create(ValueBombered[1].c_str(), fntFile);
        }
        if (strstr(std::string(str).c_str(), "!>OpenSwingSelectPop")) {
            FLAlertLayer* pFLAlertLayer = FLAlertLayer::create(ConfirmHandler::create()->setDataString("!>OpenSwingSelectPop"), "Open swing select", "NO", "YES", "Are you sure?");
            popuptoreplace = pFLAlertLayer;
        }
        //file
        if (strstr(std::string(str).c_str(), "!FName,") && std::string(fntFile) == "bigFont.fnt") {
            ReplaceAllFramesByName::by = "GJ_infoIcon_001.png";
            ReplaceAllFramesByName::to = "geode.loader/changelog.png";
            std::vector<std::string> ValueBombered = ModUtils::explode(str, ',');
            return CCLabelBMFont_create(ValueBombered[1].c_str(), fntFile);
        }
        if (strstr(std::string(str).c_str(), "!FOpen,")) {
            std::vector<std::string> OpenOpenFileInfo = ModUtils::explode(std::string(str), ',');
            jute::jValue json = jute::parser::parse_file((std::stringstream() << "geode/unzipped/" << ModUtils::GetModDev() << "." << ModUtils::GetModName() << "/mod.json").str());
            std::vector<std::string> realinfostring = ModUtils::explode(
                (json["settings"][OpenOpenFileInfo[1]]["description"]).as_string(),
                ','
            );
            FLAlertLayer* pFLAlertLayer = FLAlertLayer::create(ConfirmHandler::create()->setDataString("!FOpen," + realinfostring[2]), "Open File", "NO", "YES", "Are you sure?");
            popuptoreplace = pFLAlertLayer;
        }
        //value...
        if (strstr(std::string(str).c_str(), "!VName,") && std::string(fntFile) == "bigFont.fnt") {
            ReplaceAllFramesByName::by = "GJ_infoIcon_001.png";
            ReplaceAllFramesByName::to = "geode.loader/pencil.png";
            std::vector<std::string> ValueBombered = ModUtils::explode(str, ',');
            return CCLabelBMFont_create(ValueBombered[1].c_str(), fntFile);
        }
        if (strstr(std::string(str).c_str(), "!BVSPop,")) {
            std::vector<std::string> OpenValueSetupPopupInfo = ModUtils::explode(std::string(str), ',');
            jute::jValue json = jute::parser::parse_file((std::stringstream() << "geode/unzipped/" << ModUtils::GetModDev() << "." << ModUtils::GetModName() << "/mod.json").str());
            std::vector<std::string> realinfostring = ModUtils::explode(
                (json["settings"][OpenValueSetupPopupInfo[1]]["description"]).as_string(),
                ','
            );
            popuptoreplace = ValueSetupPopup::create(
                realinfostring[1].data(),
                realinfostring[2].data(),
                realinfostring[3].data(),
                realinfostring[4].data()
            )->isBoolean();
        }
        if (strstr(std::string(str).c_str(), "!VSPop,")) {
            std::vector<std::string> OpenValueSetupPopupInfo = ModUtils::explode(std::string(str), ',');
            jute::jValue json = jute::parser::parse_file((std::stringstream() << "geode/unzipped/" << ModUtils::GetModDev() << "." << ModUtils::GetModName() << "/mod.json").str());
            std::vector<std::string> realinfostring = ModUtils::explode(
                (json["settings"][OpenValueSetupPopupInfo[1]]["description"]).as_string(),
                ','
            );
            popuptoreplace = ValueSetupPopup::create(
                realinfostring[1].data(),
                realinfostring[2].data(),
                realinfostring[3].data(),
                realinfostring[4].data()
            );
        }
        //footer or hader
        if (
            bool(ReplaceAllFramesByName::to == "geode.loader/pencil.png" && ReplaceAllFramesByName::by == "GJ_infoIcon_001.png")
            &&
            std::string(str) == "---------------------------"
            &&
            std::string(fntFile) == "bigFont.fnt"
            )
        {
            ReplaceAllFramesByName::by = "";
            ReplaceAllFramesByName::to == "";
        }
    }
    return CCLabelBMFont_create(str, fntFile);
}

DWORD WINAPI PROCESS_ATTACH(void* hModule) {
    InitializeConfig();
    MH_SafeInitialize();
    HOOK(base + 0x1255D0, GJGarageLayer_init);
    HOOK(base + 0x208020, updateProgressbar);
    HOOK(base + 0x20BF00, PlayLayer_resetLevel);
    HOOK(base + 0x1e8200, PlayerObject_update);
    HOOK(base + 0xEF0E0, GameObject_activateObject);
    HOOK(base + 0xd1c10, GameObject_customSetup);
    HOOK(base + 0x7CAF0, EditorUI_setupCreateMenu);//huh
    HOOK(base + 0x198b20, ObjectToolbox_init);//huh
    HOOK(base + 0x23560, FLAlertLayer_show_0x23560);//huh
    CC_HOOK("?createWithSpriteFrameName@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_createWithSpriteFrameName);
    CC_HOOK("?create@CCLabelBMFont@cocos2d@@SAPAV12@PBD0@Z", CCLabelBMFont_create);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) 
        CreateThread(0, 0, PROCESS_ATTACH, hModule, 0, 0);
    return TRUE;
}
