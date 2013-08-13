//#include "UILayer.h"
//
//void UILayer::draw() {
//	CCLayer::draw();
//	CCSize s = CCDirector::sharedDirector()->getWinSize();
//	ccDrawColor4F(0.0, 0.0, 0.0, 1.0);
//	glLineWidth(10);    //  instead of glColor4f
//	ccDrawLine(CCPointMake(5, s.height - 10), CCPointMake(115, s.height - 10));
//	glLineWidth(5);
//	ccDrawColor4F(1, 0, 0, 0);  
//	ccDrawLine(CCPointMake(10, s.height - 11), CCPointMake(10 + life, s.height - 11));
//}
//
//int UILayer::getlife() {
//	return life;
//}
//
//void UILayer::setlife(int temp) {
//	life = temp;
//}