//
//Ricardo Filipe Alves Martins
//Email: rmartins@isr.uc.pt
//


#ifndef NODE_H_
#define NODE_H_

#include <vector>

using namespace std;

struct Point
{
        float x;
        float y;
        float z;
};

class Node
{
	public:
		float posX, posY, posZ, dX,dY,dZ;
		int level;
		Node* child[8];
		vector <Point> pointArray;
		Node(int, float,float,float,float,float,float);	 
};

#endif
