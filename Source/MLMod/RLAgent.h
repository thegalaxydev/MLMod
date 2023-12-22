// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "DecisionTree.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MLMOD_API RLAgent : public UActorComponent
{

public:
	RLAgent();

	void addObservation(float observation) { m_observations.Add(observation); }

	Node* getDecision();

	DecisionTree getDecisionTree() { return m_decisions; }

	int getActionCount() { return m_actionCount; }
	void setActionCount(int value) { m_actionCount = value; }
private:
	TArray<float> m_observations;
	DecisionTree m_decisions;
	int m_actionCount;

	Node* m_lastAction;
};
