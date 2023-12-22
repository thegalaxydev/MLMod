// Fill out your copyright notice in the Description page of Project Settings.


#include "RLAgent.h"

RLAgent::RLAgent()
{
	m_decisions = DecisionTree();
	m_observations = TArray<float>();
	m_actionCount = 0;
	m_lastAction = 0;
}


Node* RLAgent::getDecision()
{
	Node* node = m_decisions.getClosest(m_observations);
	
	if (node == nullptr)
	{
		int32 randNumber = FMath::FRandRange(0, m_actionCount);

		node = new Node(m_observations, randNumber);

		m_decisions.insert(node);
	}

	m_lastAction = node;

	return node;
}