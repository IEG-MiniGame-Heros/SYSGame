#ifndef SYS_QUEUE
#define SYS_QUEUE

#include "cocos2d.h"

USING_NS_CC;

class Character;

class Queue : public cocos2d::CCNode
{
public:
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(Queue);
	
	/**
	 * @brief 获取队首
	 */
	Character* getHead() const;

	/** 
	 * @brief 是否在队列当中
	 */
	bool isInQueue(Character* pCha) const;

	/** 
	 * @brief 获取前面的队友
	 * @param pCha 就是这货，获取它前面的队友
	 */
	Character* getPrivousCharacter(Character* pCha) const;

	CCArray* getCharacters() const;

	/** 
	 * @brief 设置这个队伍的MoveVector, 将会逐个调用队伍里每个Character的setMoveVector
	 * @param move_vector 要设置的移动向量
	 */
	void setMoveVector(CCPoint move_vector);

	void appendCharacter(Character* character);

	/** 
	 * @brief 返回一个队尾后面的位置
	 */
	CCPoint getPositionBehindTail() const;

protected:
	CCArray*		m_pCharacters;			// 指向队伍的指针

};

#endif