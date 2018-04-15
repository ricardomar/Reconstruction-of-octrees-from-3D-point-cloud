//
//Ricardo Filipe Alves Martins
//Email: rmartins@isr.uc.pt
//

#include "Node.h"

Node::Node(int Level,float posx,float posy, float posz,float dx,float dy,float dz)
{
	posX=posx;
	posY=posy;
	posZ=posz;
	dX=dx;
	dY=dy;
	dZ=dz;
	level=Level;

	
	for (int i=0;i<8;i++)
	{
		child[i]=NULL;
	};
};