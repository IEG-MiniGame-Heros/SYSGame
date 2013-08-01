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
	 * @brief ��ȡ����
	 */
	Character* getHead() const;

	/** 
	 * @brief �Ƿ��ڶ��е���
	 */
	bool isInQueue(Character* pCha) const;

	/** 
	 * @brief ��ȡǰ��Ķ���
	 * @param pCha �����������ȡ��ǰ��Ķ���
	 */
	Character* getPrivousCharacter(Character* pCha) const;

	CCArray* getCharacters() const;

	/** 
	 * @brief ������������MoveVector, ����������ö�����ÿ��Character��setMoveVector
	 * @param move_vector Ҫ���õ��ƶ�����
	 */
	void setMoveVector(CCPoint move_vector);

	/** 
	 * @brief ��һ��Character���ں���
	 */
	void appendCharacter(Character* character);

	/** 
	 * @brief ��һ��Character�Ӷ������Ƴ�
	 */
	bool removeFromQueue(Character* character);

	/** 
	 * @brief ����һ����β�����λ��
	 */
	CCPoint getPositionBehindTail() const;

	/// Test begin
public:
	void onUpdate(float dt);
	/// Test End

protected:
	CCArray*		m_pCharacters;			// ָ������ָ��


};

#endif