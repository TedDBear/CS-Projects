#include <iostream>
#include <string>
#include "CraigTree.h"

using namespace std;

int main()
{
	TreeNode<string>* words = new TreeNode<string>("Hello");
	words->insertBTSNode(words, "Dog");
	words->insertBTSNode(words, "Teddy Bear");
	words->insertBTSNode(words, "Ferry");
	words->insertBTSNode(words, "Apple");
	words->insertBTSNode(words, "Premium");
	words->insertBTSNode(words, "Rocket");
	words->insertBTSNode(words, "Sea");
	words->insertBTSNode(words, "Wild");
	words->insertBTSNode(words, "Zig-Zag");
	words->insertBTSNode(words, "Balloon");

	cout << "Tree using levelOrderTraversal function: ";
	words->levelOrderTraversal(words);

	cout << "\n\nTree using inOrderTraversal function: ";
	words->inOrderTraverse(words);
	
	cout << "\n\nThe number of leaves on this tree: " << words->getLeafCount(words) << endl;
	
	cout << "\nThe level of \"Balloon\": " << words->getNodeLevel(words, "Balloon", 0) << endl;
	cout << "The level of \"Teddy Bear\": " << words->getNodeLevel(words, "Teddy Bear", 0) << endl;
	cout << "The level of \"Apple\": " << words->getNodeLevel(words, "Apple", 0) << endl;

	return 0;
}
