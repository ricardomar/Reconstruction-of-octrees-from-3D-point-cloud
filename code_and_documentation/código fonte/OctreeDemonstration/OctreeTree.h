//
//Ricardo Filipe Alves Martins
//Email: rmartins@isr.uc.pt
//


#ifndef OCTREETREE_H_
#define OCTREETREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "Node.h"

using namespace std;



class OctreeTree
{
	private:
		int level;
		int n;
		int minNumPoints;
		int maxLevel;
		Node *BuildNode(Node*,int);
		void ProcessDataset(void);

	public:
		Node *rootNode;
		OctreeTree(FILE*,int,int);
		void BuildOctree(Node*);
};

#endif 