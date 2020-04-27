#include "DialogueTree.h"

DialogueTree::DialogueTree()
{
}

void DialogueTree::init()
{
	DialogueNode* node0 = new DialogueNode("NPC Prompt 1");
	DialogueNode* node1 = new DialogueNode("NPC Prompt 2");
	DialogueNode* node2 = new DialogueNode("NPC Prompt 3");
	DialogueNode* node3 = new DialogueNode("NPC Prompt 4");
	DialogueNode* node4 = new DialogueNode("NPC Prompt 5");

	node0->dialogueOptions.push_back(DialogueOption("Response 1", 0, node1));
	node1->dialogueOptions.push_back(DialogueOption("Response 2", 0, node2));
	dialogueNodes.push_back(node0);
	node1->dialogueOptions.push_back(DialogueOption("Response 1", 0, node1));
	dialogueNodes.push_back(node1);
	node2->dialogueOptions.push_back(DialogueOption("Response 1", 0, node1));
}

void DialogueTree::destroyTree()
{
	for (int i = 0; i < dialogueNodes.size(); i++)
	{
		delete dialogueNodes[i];
	}
	dialogueNodes.clear();
}

int DialogueTree::performDialogue()
{
	if (dialogueNodes.empty()) return 0;
	DialogueNode *currentNode = dialogueNodes[0];
	while (true)
	{
		cout << currentNode->text << "\n\n";
		for (int i = 0; i < currentNode->dialogueOptions.size(); i++)
		{
			cout << i + 1 << ": " << currentNode->dialogueOptions[i].text << endl;
		}
		cout << endl;
		int input;
		cin >> input;
		input--;
		if (input < 0 || input > currentNode->dialogueOptions.size())
		{
			cout << "Invalid input!\n";
		}
		else
		{
			if (currentNode->dialogueOptions[input].nextNode == nullptr)
			{
				return currentNode->dialogueOptions[input].returnCode;
			}
		}
		currentNode = currentNode->dialogueOptions[input].nextNode;
		cout << endl;
	}
	return 0;
}

DialogueOption::DialogueOption(string Text, int ReturnCode, DialogueNode* NextNode)
{
	text = Text;
	returnCode = ReturnCode;
	nextNode = NextNode;
}

DialogueNode::DialogueNode(string Text)
{
	text = Text;
}
