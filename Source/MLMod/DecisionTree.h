// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node.h"
#include <vector>

/**
 * 
 */
class MLMOD_API DecisionTree
{
public:
	DecisionTree(float comparisonThreshold = 0.7);
	~DecisionTree();

	bool isEmpty() const;

	void insert(Node* node);

	void remove(TArray<float> value);

	Node* find(TArray<float> value);

	Node* getRandom();
	Node* getRandom(int seed);

	Node* getClosest(TArray<float> value);

	float getComparisonThreshold() { return m_comparisonThreshold; }
	void setComparisonThreshold(float value) { m_comparisonThreshold = value; }

private:
	bool findNode(TArray<float> searchValue, Node*& nodeFound, Node*& nodeParent);
	void collectNodes(Node* node, std::vector<Node*>& nodes);
	Node* m_root = nullptr;

	float m_comparisonThreshold;

};
