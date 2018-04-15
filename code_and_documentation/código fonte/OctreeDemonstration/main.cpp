//
//Ricardo Filipe Alves Martins
//Email: rmartins@isr.uc.pt
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "OctreeTree.h"
#include "display.h"

int main(void)
{
	FILE* data_file;
	data_file=fopen("house.xyz","r");
	OctreeTree demo(data_file,10,5);
	
	demo.BuildOctree(demo.rootNode);
	
	displayOctreeTree(demo.rootNode,0);
	return 0;

};
