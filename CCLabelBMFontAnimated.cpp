//
//  CCLabelBMFontAnimated.cpp
//  HelloCpp
//
//  Created by Steve Barnegren on 11/11/2013.
//
//

#include "CCLabelBMFontAnimated.h"

//CREATE FUNCTIONS

CCLabelBMFontAnimated *CCLabelBMFontAnimated::create(const char *str, const char *fntFile, float width/* = kLabelAutomaticWidth*/, cocos2d::TextHAlignment alignment/* = TextHAlignment::LEFT*/, cocos2d::Point imageOffset/* = Point::ZERO*/)
{
    CCLabelBMFontAnimated *pRet = new CCLabelBMFontAnimated();
    if(pRet && pRet->initWithString(str, fntFile, width, alignment, imageOffset))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCLabelBMFontAnimated * CCLabelBMFontAnimated::create(const char *str, const char *fntFile, float width, cocos2d::TextHAlignment alignment)
{
    return CCLabelBMFontAnimated::create(str, fntFile, width, alignment, cocos2d::Point::ZERO);
}

CCLabelBMFontAnimated * CCLabelBMFontAnimated::create(const char *str, const char *fntFile, float width)
{
    return CCLabelBMFontAnimated::create(str, fntFile, width, cocos2d::TextHAlignment::LEFT, cocos2d::Point::ZERO);
}

CCLabelBMFontAnimated * CCLabelBMFontAnimated::create(const char *str, const char *fntFile)
{
    return CCLabelBMFontAnimated::create(str, fntFile, cocos2d::kLabelAutomaticWidth, cocos2d::TextHAlignment::LEFT, cocos2d::Point::ZERO);
}


#pragma mark - Set Basic Character Properties

void CCLabelBMFontAnimated::setCharScale(int index, float s){
    
    if (index >= getChildren()->count()) {
        cocos2d::log("CCLabelBMFontAnimated - Could not set character sprite scale, index out of bounds");
        return;
    }
    
    cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(index);
    charSprite->setScale(s);
}

void CCLabelBMFontAnimated::setCharOpacity(int index, float o){
    
    if (index >= getChildren()->count()) {
        cocos2d::log("CCLabelBMFontAnimated - Could not set character sprite opacity, index out of bounds");
        return;
    }
    
    GLubyte opacity = o;
    cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(index);
    charSprite->setOpacity(opacity);
}

void CCLabelBMFontAnimated::setCharRotation(int index, float r){
    
    if (index >= getChildren()->count()) {
        cocos2d::log("CCLabelBMFontAnimated - Could not set character sprite rotation, index out of bounds");
        return;
    }
    
    cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(index);
    charSprite->setRotation(r);
}


void CCLabelBMFontAnimated::setAllCharsScale(float s){
    
    const int numChars = getChildren()->count();
    
    for (int i = 0; i < numChars; i++) {
        cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(i);
        charSprite->setScale(s);
        }
}


void CCLabelBMFontAnimated::setAllCharsOpacity(float o){
    
    GLubyte opacity = o;
    
    const int numChars = getChildren()->count();
    
    for (int i = 0; i < numChars; i++) {
        cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(i);
        charSprite->setOpacity(opacity);
    }
}

void CCLabelBMFontAnimated::setAllCharsRotation(float r){
    
    const int numChars = getChildren()->count();
    
    for (int i = 0; i < numChars; i++) {
        cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(i);
        charSprite->setRotation(r);
    }
}

void CCLabelBMFontAnimated::offsetAllCharsPositionBy(cocos2d::Point offset){
    
    const int numChars = getChildren()->count();
    
    for (int i = 0; i < numChars; i++) {
        cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(i);
        charSprite->setPosition(cocos2d::Point(charSprite->getPosition().x + offset.x, charSprite->getPosition().y + offset.y));
    }
}


#pragma mark - Run Custom Actions

void CCLabelBMFontAnimated::runActionOnAllSprites(cocos2d::Action* action, bool removeOnCompletion, cocos2d::CallFunc *callFuncOnCompletion){

    const int numChars = getChildren()->count();
    
    for (int i = 0; i < numChars; i++) {
        cocos2d::Action *actionCopy = action->clone();
        cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(i);
        
        if (i == numChars-1) { //if is the last character, run the call func actions
            
            cocos2d::Array *actionsArray = cocos2d::Array::create();
            actionsArray->addObject(actionCopy);
            
            if (callFuncOnCompletion != nullptr) {
                actionsArray->addObject(callFuncOnCompletion);
            }
            if (removeOnCompletion) {
                actionsArray->addObject(cocos2d::CallFunc::create(CC_CALLBACK_0(CCLabelBMFontAnimated::removeFromParent, this)));
            }
            cocos2d::Sequence *actionsSequence = cocos2d::Sequence::create(actionsArray);
            charSprite->runAction(actionsSequence);
        }
        else{ //if is not the last character, just run the action
            charSprite->runAction(actionCopy);}
    }
}

void CCLabelBMFontAnimated::runActionOnAllSprites(cocos2d::Action* action){
    
    runActionOnAllSprites(action, false, nullptr);
    
}

void CCLabelBMFontAnimated::runActionOnAllSprites(cocos2d::Action* action, bool removeOnCompletion){
    
    runActionOnAllSprites(action, removeOnCompletion, nullptr);
    
}

void CCLabelBMFontAnimated::stopActionsOnAllSprites(){
    
    const int numChars = getChildren()->count();
    
    for (int i = 0; i < numChars; i++) {
        cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(i);
        charSprite->stopAllActions();
    }
}


void CCLabelBMFontAnimated::runActionOnAllSpritesSequentially(cocos2d::FiniteTimeAction* action, float duration, bool removeOnCompletion, cocos2d::CallFunc *callFuncOnCompletion){

    const int numChars = getChildren()->count();
    
    if (numChars < 2) {
        cocos2d::log("CCLabelBMFontAnimated - runActionOnAllSpritesSequentially() requires at least 2 children to operate");
        return;
    }
    
    for (int i = 0; i < numChars; i++) {
        
        cocos2d::DelayTime *delay = cocos2d::DelayTime::create((duration/(numChars-1)) *i);
        cocos2d::Action *actionCopy = action->clone();
        cocos2d::Sequence *delayAndAction = cocos2d::Sequence::create(delay, actionCopy, NULL);
        cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(i);
        
        if (i == numChars-1) { //if is the last character, run the call func actions
            
            cocos2d::Array *actionsArray = cocos2d::Array::create();
            actionsArray->addObject(delayAndAction);
            
            if (callFuncOnCompletion != nullptr) {
                actionsArray->addObject(callFuncOnCompletion);
            }
            if (removeOnCompletion) {
                actionsArray->addObject(cocos2d::CallFunc::create(CC_CALLBACK_0(CCLabelBMFontAnimated::removeFromParent, this)));
            }
            cocos2d::Sequence *actionsSequence = cocos2d::Sequence::create(actionsArray);
            charSprite->runAction(actionsSequence);
        }
        else{ //if is not the last character, just run the action
            charSprite->runAction(delayAndAction);}
        
    }
}

void CCLabelBMFontAnimated::runActionOnAllSpritesSequentially(cocos2d::FiniteTimeAction* action, float duration, bool removeOnCompletion){
    
    runActionOnAllSpritesSequentially(action, duration, removeOnCompletion, nullptr);
    
}

void CCLabelBMFontAnimated::runActionOnAllSpritesSequentially(cocos2d::FiniteTimeAction* action, float duration){
    
    runActionOnAllSpritesSequentially(action, duration, false, nullptr);
    
}

void CCLabelBMFontAnimated::runActionOnAllSpritesSequentiallyReverse(cocos2d::FiniteTimeAction* action, float duration, bool removeOnCompletion, cocos2d::CallFunc *callFuncOnCompletion){

    const int numChars = getChildren()->count();
    
    if (numChars < 2) {
        cocos2d::log("CCLabelBMFontAnimated - runActionOnAllSpritesSequentiallyReverse() requires at least 2 children to operate");
        return;
    }
    
    for (int i = 0; i < numChars; i++) {
        
        cocos2d::DelayTime *delay = cocos2d::DelayTime::create((duration/(numChars-1)) *((numChars-1)-i));
        cocos2d::Action *actionCopy = action->clone();
        cocos2d::Sequence *delayAndAction = cocos2d::Sequence::create(delay, actionCopy, NULL);
        cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(i);
        
        if (i == 0) { //if is the first character, run the call func actions
            
            cocos2d::Array *actionsArray = cocos2d::Array::create();
            actionsArray->addObject(delayAndAction);
            
            if (callFuncOnCompletion != nullptr) {
                actionsArray->addObject(callFuncOnCompletion);
            }
            if (removeOnCompletion) {
                actionsArray->addObject(cocos2d::CallFunc::create(CC_CALLBACK_0(CCLabelBMFontAnimated::removeFromParent, this)));
            }
            cocos2d::Sequence *actionsSequence = cocos2d::Sequence::create(actionsArray);
            charSprite->runAction(actionsSequence);
        }
        else{ //if is not the first character, just run the action
            charSprite->runAction(delayAndAction);}
    }

}

void CCLabelBMFontAnimated::runActionOnAllSpritesSequentiallyReverse(cocos2d::FiniteTimeAction* action, float duration, bool removeOnCompletion){
    
    runActionOnAllSpritesSequentiallyReverse(action, duration, removeOnCompletion, nullptr);
    
}

void CCLabelBMFontAnimated::runActionOnAllSpritesSequentiallyReverse(cocos2d::FiniteTimeAction* action, float duration){
    
    runActionOnAllSpritesSequentiallyReverse(action, duration, false, nullptr);
    
}

#pragma mark Animations

void CCLabelBMFontAnimated::flyPastAndRemove(){
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    float rescaleFactor = 1/getScale(); //if the label has been scaled down, all the action coordinates will be too small, rescale factor scales them up
    
    offsetAllCharsPositionBy(cocos2d::Point(-visibleSize.width * rescaleFactor, 0));
    
    float centrePortion = visibleSize.width*0.05;
    float centreSlowTime = 0.9;
    
    cocos2d::MoveBy *flyIn = cocos2d::MoveBy::create(0.5, cocos2d::Point((visibleSize.width* rescaleFactor) -((centrePortion* rescaleFactor)/2), 0));
    cocos2d::EaseExponentialInOut *flyInEase = cocos2d::EaseExponentialInOut::create(flyIn);
    
    cocos2d::MoveBy *centreSlowMove = cocos2d::MoveBy::create(centreSlowTime, cocos2d::Point(centrePortion * rescaleFactor, 0));
    cocos2d::ScaleTo *scaleUp = cocos2d::ScaleTo::create(centreSlowTime/2, 1.5);
    cocos2d::ScaleTo *scaleDown = cocos2d::ScaleTo::create(centreSlowTime/2, 1);
    cocos2d::Sequence *swell = cocos2d::Sequence::create(scaleUp, scaleDown, NULL);
    cocos2d::Spawn *centreMoveAndSwell = cocos2d::Spawn::create(centreSlowMove, swell, NULL);
    
    cocos2d::MoveBy *flyOut = cocos2d::MoveBy::create(0.5, cocos2d::Point((visibleSize.width*rescaleFactor) -((centrePortion*rescaleFactor)/2), 0));
    cocos2d::EaseExponentialInOut *flyOutEase = cocos2d::EaseExponentialInOut::create(flyOut);
    
    cocos2d::Sequence *flyPast = cocos2d::Sequence::create(flyInEase, centreMoveAndSwell, flyOutEase, NULL);
    
    runActionOnAllSpritesSequentiallyReverse(flyPast, 0.7, true, nullptr);
    
}

void CCLabelBMFontAnimated::animateInTypewriter(float duration){

    //set all the characters scale to zero
    setAllCharsScale(0);
    
    cocos2d::ScaleTo *appear = cocos2d::ScaleTo::create(0, 1);
    
    runActionOnAllSpritesSequentially(appear, duration);

}

void CCLabelBMFontAnimated::animateInFlyInFromLeft(float duration){

    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    float rescaleFactor = 1/getScale(); //if the label has been scaled down, all the action coordinates will be too small, rescale factor scales them up
    float offsetX = visibleSize.width * rescaleFactor;
    offsetAllCharsPositionBy(cocos2d::Point(-offsetX, 0));

    cocos2d::MoveBy *flyIn = cocos2d::MoveBy::create(1, cocos2d::Point(offsetX, 0));
    cocos2d::EaseExponentialOut *flyInEase = cocos2d::EaseExponentialOut::create(flyIn);
    
    runActionOnAllSpritesSequentially(flyInEase, duration);
    

}

void CCLabelBMFontAnimated::animateInFlyInFromRight(float duration){
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    float rescaleFactor = 1/getScale(); //if the label has been scaled down, all the action coordinates will be too small, rescale factor scales them up
    float offsetX = visibleSize.width * rescaleFactor;
    offsetAllCharsPositionBy(cocos2d::Point(offsetX, 0));
    
    cocos2d::MoveBy *flyIn = cocos2d::MoveBy::create(1, cocos2d::Point(-offsetX, 0));
    cocos2d::EaseExponentialOut *flyInEase = cocos2d::EaseExponentialOut::create(flyIn);
    
    runActionOnAllSpritesSequentiallyReverse(flyInEase, duration);

}

void CCLabelBMFontAnimated::animateInFlyInFromTop(float duration){
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    float rescaleFactor = 1/getScale(); //if the label has been scaled down, all the action coordinates will be too small, rescale factor scales them up
    float offsetY = visibleSize.height * rescaleFactor;
    offsetAllCharsPositionBy(cocos2d::Point(0, offsetY));
    
    cocos2d::MoveBy *flyIn = cocos2d::MoveBy::create(1, cocos2d::Point(0, -offsetY));
    cocos2d::EaseExponentialOut *flyInEase = cocos2d::EaseExponentialOut::create(flyIn);
    
    runActionOnAllSpritesSequentially(flyInEase, duration);

}

void CCLabelBMFontAnimated::animateInFlyInFromBottom(float duration){
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    float rescaleFactor = 1/getScale(); //if the label has been scaled down, all the action coordinates will be too small, rescale factor scales them up
    float offsetY = visibleSize.height * rescaleFactor;
    offsetAllCharsPositionBy(cocos2d::Point(0, -offsetY));
    
    cocos2d::MoveBy *flyIn = cocos2d::MoveBy::create(1, cocos2d::Point(0, offsetY));
    cocos2d::EaseExponentialOut *flyInEase = cocos2d::EaseExponentialOut::create(flyIn);
    
    runActionOnAllSpritesSequentially(flyInEase, duration);
    
}


void CCLabelBMFontAnimated::animateInDropFromTop(float duration){
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    float rescaleFactor = 1/getScale(); //if the label has been scaled down, all the action coordinates will be too small, rescale factor scales them up
    float offsetY = visibleSize.height * rescaleFactor;
    offsetAllCharsPositionBy(cocos2d::Point(0, offsetY));
    
    cocos2d::MoveBy *flyIn = cocos2d::MoveBy::create(1, cocos2d::Point(0, -offsetY));
    cocos2d::EaseBounceOut *flyInEase = cocos2d::EaseBounceOut::create(flyIn);
    
    runActionOnAllSpritesSequentially(flyInEase, duration);

}

void CCLabelBMFontAnimated::animateInSwell(float duration){
    
    setAllCharsScale(0);
    
    cocos2d::ScaleTo *scaleUp = cocos2d::ScaleTo::create(0.2, 1.5);
    cocos2d::ScaleTo *scaleDown = cocos2d::ScaleTo::create(0.2, 1);
    cocos2d::Sequence *scaleSeq = cocos2d::Sequence::create(scaleUp, scaleDown, NULL);
        
    runActionOnAllSpritesSequentially(scaleSeq, duration);

}

void CCLabelBMFontAnimated::animateInRevealFromLeft(float duration){
    
    //set all chars opacity to zero, apart from first
    setAllCharsOpacity(0);
    cocos2d::Sprite *firstChar = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(0);
    firstChar->setOpacity(255);
    //make sure the first character has higher z order than the rest, reset after the animation
    cocos2d::DelayTime *delay = cocos2d::DelayTime::create(duration);
    cocos2d::CallFunc *resetZ = cocos2d::CallFunc::create(CC_CALLBACK_0(CCLabelBMFontAnimated::reorderChild, this, firstChar, firstChar->getZOrder()));
    cocos2d::Sequence *resetZAfterAnimation = cocos2d::Sequence::create(delay, resetZ, NULL);
    this->reorderChild(firstChar, firstChar->getZOrder()+10);
    firstChar->runAction(resetZAfterAnimation);

    //reveal each char from the behind the first
    for (int i = 1; i < getChildren()->count(); i++) {
        
        cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(i);
        
        cocos2d::MoveTo *move = cocos2d::MoveTo::create(duration, charSprite->getPosition());
        cocos2d::EaseExponentialOut *moveEase = cocos2d::EaseExponentialOut::create(move);
        cocos2d::FadeIn *fadeIn = cocos2d::FadeIn::create(duration);
        cocos2d::EaseExponentialOut *fadeEase = cocos2d::EaseExponentialOut::create(fadeIn);
        cocos2d::Spawn *moveAndFade = cocos2d::Spawn::create(moveEase, fadeEase, NULL);
        
        charSprite->setPosition(cocos2d::Point(firstChar->getPosition().x, charSprite->getPosition().y));
        charSprite->runAction(moveAndFade);
    
    }
    
}

void CCLabelBMFontAnimated::animateSwell(float duration){
    
    cocos2d::ScaleTo *scaleUp = cocos2d::ScaleTo::create(0.2, 1.5);
    cocos2d::ScaleTo *scaleDown = cocos2d::ScaleTo::create(0.2, 1);
    cocos2d::Sequence *scaleSeq = cocos2d::Sequence::create(scaleUp, scaleDown, NULL);
    
    runActionOnAllSpritesSequentially(scaleSeq, duration);

}

void CCLabelBMFontAnimated::animateJump(float duration, float height){

    const int numChars = getChildren()->count();
    
    for (int i = 0; i < getChildren()->count(); i++) {
        
        
        cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(i);
        
        cocos2d::DelayTime *delay = cocos2d::DelayTime::create((duration/(numChars-1)) *i);
        cocos2d::JumpTo *jump = cocos2d::JumpTo::create(0.5, charSprite->getPosition(), height, 1);
        cocos2d::Sequence *delayThenJump = cocos2d::Sequence::create(delay, jump, NULL);
        charSprite->runAction(delayThenJump);
    
    }
    
    
}

void CCLabelBMFontAnimated::animateStretchElastic(float stretchDuration, float releaseDuration, float stretchAmount){

    for (int i = 0; i < getChildren()->count(); i++) {
        
        cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(i);
        
        cocos2d::MoveTo *stretch = cocos2d::MoveTo::create(stretchDuration,
                                                           cocos2d::Point((charSprite->getPosition().x - (getContentSize().width/4)) * stretchAmount,
                                                                          charSprite->getPosition().y));
        cocos2d::MoveTo *release = cocos2d::MoveTo::create(releaseDuration, charSprite->getPosition());
        cocos2d::EaseElasticOut *releaseElastic = cocos2d::EaseElasticOut::create(release);
        cocos2d::Sequence *animation = cocos2d::Sequence::create(stretch, releaseElastic, NULL);
        
        charSprite->runAction(animation);
        
    }
    
}

void CCLabelBMFontAnimated::animateInSpin(float duration, int spins){
    
    setAllCharsOpacity(0);
    
    for (int i = 0; i < getChildren()->count(); i++) {
        
        cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(i);
        
        cocos2d::MoveTo *moveToPosition = cocos2d::MoveTo::create(duration, charSprite->getPosition());
        cocos2d::EaseExponentialOut *moveToPositionEase = cocos2d::EaseExponentialOut::create(moveToPosition);
        float centreX = this->getContentSize().width/2;
        charSprite->setPosition(cocos2d::Point(centreX, charSprite->getPosition().y));
        charSprite->runAction(moveToPositionEase);

        cocos2d::RotateBy *counterRotate = cocos2d::RotateBy::create(duration, -360 * spins);
        cocos2d::EaseExponentialOut *counterRotateEase = cocos2d::EaseExponentialOut::create(counterRotate);
        charSprite->runAction(counterRotateEase);
        
        cocos2d::FadeIn *fadeIn = cocos2d::FadeIn::create(duration);
        charSprite->runAction(fadeIn);

    }


    //spin the label
    cocos2d::RotateBy *spin = cocos2d::RotateBy::create(duration, 360 * spins);
    cocos2d::EaseExponentialOut *spinEase = cocos2d::EaseExponentialOut::create(spin);
    this->runAction(spinEase);
    
    
}

void CCLabelBMFontAnimated::animateInVortex(bool removeOnCompletion, bool createGhosts){
    
    float duration = 2;
    
    //fade in the label
    float fadeDuration = duration * 0.25;
    cocos2d::FadeTo *fadeIn = cocos2d::FadeTo::create(fadeDuration, getOpacity());
    setOpacity(0);
    this->runAction(fadeIn);
    
    
    int spins = 15;
    
    if (createGhosts) {
        
        int numGhosts = 3;
        float ghostMaxOpacity = 100;
        
        for (int i = 0; i < numGhosts; i++) {
            
            CCLabelBMFontAnimated *ghostLabel = CCLabelBMFontAnimated::create(getString(), getFntFile(), getContentSize().width*2, cocos2d::kCCTextAlignmentCenter);
            ghostLabel->setOpacity(ghostMaxOpacity/(i+1));
            ghostLabel->setPosition(this->getPosition());
            this->getParent()->addChild(ghostLabel);
            ghostLabel->animateInVortex(true, false);
            
        }
        
    }
    
    for (int i = 0; i < getChildren()->count(); i++) {
        
        //change the spin on some chars
        int charSpins = spins;
        if (i % 2 == 0) {
            charSpins--;
        }
        else if (i % 3 == 0){
            charSpins++;
        }
        
        float staggerAmount = (arc4random() % 10)/10.0f;
        float letterDuration = duration + staggerAmount;
        
        float spinDuration = letterDuration/charSpins;

        
        cocos2d::Sprite *charSprite = (cocos2d::Sprite*)getChildren()->getObjectAtIndex(i);
    
        float radius = fabs((this->getContentSize().width/2) - charSprite->getPosition().x);
        float squareLength = sqrtf((radius*radius)/2);
        float arcAmount = radius - squareLength;
        
        float segmentDuration = spinDuration*0.25;
        
        cocos2d::Array *spinActions = cocos2d::Array::create();
        
            for (int s = 0; s < charSpins; s++){
          
            //segment 4
            cocos2d::MoveBy *segment4Straight = cocos2d::MoveBy::create(segmentDuration, cocos2d::Point(-radius, -radius));
            cocos2d::MoveBy *segment4PositiveArc = cocos2d::MoveBy::create(segmentDuration/2, cocos2d::Point(arcAmount, -arcAmount));
            cocos2d::EaseSineOut *segment4PositiveArcEase = cocos2d::EaseSineOut::create(segment4PositiveArc);
            cocos2d::MoveBy *segment4NegativeArc = cocos2d::MoveBy::create(segmentDuration/2, cocos2d::Point(-arcAmount, arcAmount));
            cocos2d::EaseSineIn *segment4NegativeArcEase = cocos2d::EaseSineIn::create(segment4NegativeArc);
            cocos2d::Sequence *segment4Arc = cocos2d::Sequence::create(segment4PositiveArcEase, segment4NegativeArcEase, NULL);
            cocos2d::Spawn *segment4Action = cocos2d::Spawn::create(segment4Straight, segment4Arc, NULL);
            
            //segment 3
            cocos2d::MoveBy *segment3Straight = cocos2d::MoveBy::create(segmentDuration, cocos2d::Point(-radius, radius));
            cocos2d::MoveBy *segment3PositiveArc = cocos2d::MoveBy::create(segmentDuration/2, cocos2d::Point(-arcAmount, -arcAmount));
            cocos2d::EaseSineOut *segment3PositiveArcEase = cocos2d::EaseSineOut::create(segment3PositiveArc);
            cocos2d::MoveBy *segment3NegativeArc = cocos2d::MoveBy::create(segmentDuration/2, cocos2d::Point(arcAmount, arcAmount));
            cocos2d::EaseSineIn *segment3NegativeArcEase = cocos2d::EaseSineIn::create(segment3NegativeArc);
            cocos2d::Sequence *segment3Arc = cocos2d::Sequence::create(segment3PositiveArcEase, segment3NegativeArcEase, NULL);
            cocos2d::Spawn *segment3Action = cocos2d::Spawn::create(segment3Straight, segment3Arc, NULL);

            //segment 1
            cocos2d::MoveBy *segment1Straight = cocos2d::MoveBy::create(segmentDuration, cocos2d::Point(radius, radius));
            cocos2d::MoveBy *segment1PositiveArc = cocos2d::MoveBy::create(segmentDuration/2, cocos2d::Point(-arcAmount, arcAmount));
            cocos2d::EaseSineOut *segment1PositiveArcEase = cocos2d::EaseSineOut::create(segment1PositiveArc);
            cocos2d::MoveBy *segment1NegativeArc = cocos2d::MoveBy::create(segmentDuration/2, cocos2d::Point(arcAmount, -arcAmount));
            cocos2d::EaseSineIn *segment1NegativeArcEase = cocos2d::EaseSineIn::create(segment1NegativeArc);
            cocos2d::Sequence *segment1Arc = cocos2d::Sequence::create(segment1PositiveArcEase, segment1NegativeArcEase, NULL);
            cocos2d::Spawn *segment1Action = cocos2d::Spawn::create(segment1Straight, segment1Arc, NULL);

            //segment 2
            cocos2d::MoveBy *segment2Straight = cocos2d::MoveBy::create(segmentDuration, cocos2d::Point(radius, -radius));
            cocos2d::MoveBy *segment2PositiveArc = cocos2d::MoveBy::create(segmentDuration/2, cocos2d::Point(arcAmount, arcAmount));
            cocos2d::EaseSineOut *segment2PositiveArcEase = cocos2d::EaseSineOut::create(segment2PositiveArc);
            cocos2d::MoveBy *segment2NegativeArc = cocos2d::MoveBy::create(segmentDuration/2, cocos2d::Point(-arcAmount, -arcAmount));
            cocos2d::EaseSineIn *segment2NegativeArcEase = cocos2d::EaseSineIn::create(segment2NegativeArc);
            cocos2d::Sequence *segment2Arc = cocos2d::Sequence::create(segment2PositiveArcEase, segment2NegativeArcEase, NULL);
            cocos2d::Spawn *segment2Action = cocos2d::Spawn::create(segment2Straight, segment2Arc, NULL);

            cocos2d::Sequence *spinAction;
            
            if ((this->getContentSize().width/2) < charSprite->getPosition().x) {
                spinAction = cocos2d::Sequence::create(segment4Action, segment3Action, segment1Action, segment2Action, NULL);
            }
            else{
                spinAction = cocos2d::Sequence::create(segment1Action, segment2Action, segment4Action, segment3Action, NULL);
            }
        
                
            spinActions->addObject(spinAction);
                
            
        }
        
        cocos2d::Sequence *animation = cocos2d::Sequence::create(spinActions);
        cocos2d::EaseSineOut *animationEase = cocos2d::EaseSineOut::create(animation);
    
        charSprite->runAction(animationEase);
 
        
    
    }

    if (removeOnCompletion) {
        cocos2d::DelayTime *waitForAnimation = cocos2d::DelayTime::create(duration * 1.5);
        cocos2d::CallFunc *remove = cocos2d::CallFunc::create(CC_CALLBACK_0(CCLabelBMFontAnimated::removeFromParent, this));
        cocos2d::Sequence *waitThenRemove = cocos2d::Sequence::create(waitForAnimation, remove, NULL);
        this->runAction(waitThenRemove);
    }

}












