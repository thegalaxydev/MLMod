// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MLMOD_API Node
{
public:
	Node(TArray<float> value, int task);

	bool hasLeft();
	bool hasRight();

	float compare(Node* other);
	float compare(TArray<float> other);

	TArray<float> getObservations();
	void setObservations(TArray<float> value);

	Node* getRight();
	Node* getLeft();

	void setLeft(Node* node);
	void setRight(Node* node);

	int getActionID() { return m_action; }

	Node* getParent() { return m_parent; }
	void setParent(Node* parent) { m_parent = parent; }
private:
	TArray<float> m_observations;
	int m_action;
	int m_score;

	Node* m_left;
	Node* m_right;

	Node* m_parent;
};
