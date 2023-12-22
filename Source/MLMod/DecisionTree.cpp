// Fill out your copyright notice in the Description page of Project Settings.


#include "DecisionTree.h"

#include <random>

DecisionTree::DecisionTree(float comparisonThreshold = 0.7)
{
	m_root = nullptr;

	m_comparisonThreshold = comparisonThreshold;
}

DecisionTree::~DecisionTree()
{
	while (m_root)
	{
		remove(m_root->getObservations());
	}
}

bool DecisionTree::isEmpty() const
{
	return !m_root;
}

void DecisionTree::insert(Node* node)
{
	
	if (!m_root)
	{
		m_root = node;
		return;
	}

	Node* current = m_root;

	while (current)
	{

		if (current->compare(node) < m_comparisonThreshold)
		{
			if (current->getLeft())
			{
				current = current->getLeft();
			}
			else
			{
				node->setParent(current);
				current->setLeft(node);
				break;
			}
		}
		else
		{
			if (current->getRight())
			{
				current = current->getRight();
			}
			else
			{
				node->setParent(current);
				current->setRight(node);
				break;
			}
		}
	}
}

void DecisionTree::remove(TArray<float> value)
{
	Node* current = nullptr;
	Node* parent = nullptr;

	if (!findNode(value, current, parent))
		return;

	if (current->hasLeft() && current->hasRight())
	{
		Node* predecessor = current->getLeft();
		Node* predecessorParent = current;
		while (predecessor->hasRight())
		{
			predecessorParent = predecessor;
			predecessor = predecessor->getRight();
		}

		current->setObservations(predecessor->getObservations());

		parent = predecessorParent;
		current = predecessor;
	}

	Node* child = (current->hasLeft()) ? current->getLeft() : current->getRight();
	if (!parent)
		m_root = child;
	else if (parent->getLeft() == current)
		parent->setLeft(child);
	else
		parent->setRight(child);

	delete current;
}

Node* DecisionTree::find(TArray<float> value)
{
	Node* current = m_root;

	while (current && current->getObservations() != value)
	{
		if (current->compare(value) < m_comparisonThreshold)
			current = current->getLeft();
		else
			current = current->getRight();
	}

	return current;
}

Node* DecisionTree::getClosest(TArray<float> value)
{
	std::vector<Node*> nodes;
	collectNodes(m_root, nodes);

	if (nodes.empty()) {
		return nullptr;
	}

	if (nodes.size() == 1)
	{
		if (nodes[0]->compare(value) >= m_comparisonThreshold)
			return nodes[0];
		else
			return nullptr;
	}

	Node* currentNode = nodes[0];
	Node* closestNode = (nodes[0]->compare(value) >= m_comparisonThreshold) 
		? nodes[0] : nullptr;

	for (int i = 1; i < nodes.size(); i++)
	{
		float comparison = currentNode->compare(value);
		float otherComparison = nodes[i]->compare(value);
		if (otherComparison > comparison && otherComparison >= m_comparisonThreshold)
			closestNode = nodes[i];
	}

	return closestNode;
}

Node* DecisionTree::getRandom(int seed) 
{
	std::vector<Node*> nodes;
	collectNodes(m_root, nodes);

	if (nodes.empty()) {
		return nullptr;
	}

	std::mt19937 gen(seed);
	std::uniform_int_distribution<> distrib(0, nodes.size() - 1);

	return nodes[distrib(gen)];
}

Node* DecisionTree::getRandom() 
{
	std::vector<Node*> nodes;
	collectNodes(m_root, nodes);

	if (nodes.empty()) {
		return nullptr;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, nodes.size() - 1);

	return nodes[distrib(gen)];
}

bool DecisionTree::findNode(TArray<float> searchValue, Node*& nodeFound, Node*& nodeParent)
{
	nodeFound = m_root;
	nodeParent = nullptr;

	while (nodeFound)
	{
		if (nodeFound->getObservations() == searchValue)
			return true;
		else
		{
			nodeParent = nodeFound;
			if (nodeFound->compare(searchValue) < m_comparisonThreshold)
				nodeFound = nodeFound->getLeft();
			else
				nodeFound = nodeFound->getRight();
		}
	}

	return false;
}

void DecisionTree::collectNodes(Node* node, std::vector<Node*>& nodes) {
	if (node == nullptr) {
		return;
	}

	nodes.push_back(node);

	collectNodes(node->getLeft(), nodes);
	collectNodes(node->getRight(), nodes);
}

