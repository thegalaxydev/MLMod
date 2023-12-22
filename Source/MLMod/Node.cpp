// Fill out your copyright notice in the Description page of Project Settings.


#include "Node.h"
#include <cmath>

Node::Node(TArray<float> value, int task)
{
	m_observations = value;
	m_action = task;

	m_left = nullptr;
	m_right = nullptr;
}


bool Node::hasLeft()
{
	return m_left != nullptr;
}

bool Node::hasRight()
{
	return m_right != nullptr;
}

float Node::compare(Node* other) 
{
	float similaritySum = 0.0f;
	int total = m_observations.Num();

	for (int i = 0; i < total; i++) {
		int num1 = m_observations[i];
		int num2 = other->getObservations()[i];

		int difference = std::abs(num1 - num2);
		int maxVal = std::max(num1, num2);

		float similarity = (maxVal == 0) ? 1.0f : 1.0f - (static_cast<float>(difference) / maxVal);
		similaritySum += similarity;
	}

	return total > 0 ? similaritySum / total : 0.0f;
}

float Node::compare(TArray<float> other) 
{
	float similaritySum = 0.0f;
	int total = m_observations.Num();

	for (int i = 0; i < total; i++) {
		int num1 = m_observations[i];
		int num2 = other[i];

		int difference = std::abs(num1 - num2);
		int maxVal = std::max(num1, num2);

		float similarity = (maxVal == 0) ? 1.0f : 1.0f - (static_cast<float>(difference) / maxVal);
		similaritySum += similarity;
	}

	return total > 0 ? similaritySum / total : 0.0f;
}


TArray<float> Node::getObservations()
{
	return TArray<float>();
}

void Node::setObservations(TArray<float> value)
{
	m_observations = value;
}

Node* Node::getRight()
{
	return m_right;
}

Node* Node::getLeft()
{
	return m_left;
}

void Node::setLeft(Node* node)
{
	m_left = node;
}

void Node::setRight(Node* node)
{
	m_right = node;
}
