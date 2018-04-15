//
//Ricardo Filipe Alves Martins
//Email: rmartins@isr.uc.pt
//

#include "OctreeTree.h"


OctreeTree::OctreeTree(FILE * dataFileXYZ, int minnumPoints, int maxlevel)
{
	minNumPoints=minnumPoints;
	maxLevel=maxlevel;
	rootNode=new Node(1,0,0,0,10,10,10);
	
	while (true)
	{	
		float x,y,z;
		fscanf(dataFileXYZ, "%f",&x);
		fscanf(dataFileXYZ, "%f",&y);
		fscanf(dataFileXYZ, "%f",&z);	
			
		if(feof(dataFileXYZ))
		{	
			break;
		}
		else
		{			

			Point temp;
			temp.x=x;
			temp.y=y;
			temp.z=z;
			rootNode->pointArray.push_back(temp);	
		};	
	};	
	fclose(dataFileXYZ);
	ProcessDataset();
	
};

void OctreeTree::ProcessDataset(void)
{
	float minX,minY,minZ,maxX,maxY,maxZ,Xc=0,Yc=0,Zc=0,sumX=0,sumY=0,sumZ=0;
	int nPoints;
	
	minX=rootNode->pointArray[0].x;
	minY=rootNode->pointArray[0].y;
	minZ=rootNode->pointArray[0].z;
	maxX=rootNode->pointArray[0].x;
	maxY=rootNode->pointArray[0].y;
	maxZ=rootNode->pointArray[0].z;
	
	for (int i=0;i<(int)rootNode->pointArray.size();i++)
	{
		if (rootNode->pointArray[i].x<minX)
		{
			minX=rootNode->pointArray[i].x;
		}
		else if(rootNode->pointArray[i].x>maxX)
		{
			maxX=rootNode->pointArray[i].x;
		};
		
		if (rootNode->pointArray[i].y<minY)
		{
			minY=rootNode->pointArray[i].y;
		}	
		else if(rootNode->pointArray[i].y>maxY)
		{
			maxY=rootNode->pointArray[i].y;
		};
		
		if (rootNode->pointArray[i].z<minZ)
		{
			minZ=rootNode->pointArray[i].z;
		}	
		else if(rootNode->pointArray[i].z>maxZ)
		{
			maxZ=rootNode->pointArray[i].z;
		};		
		
		sumX=sumX+rootNode->pointArray[i].x;
		sumY=sumY+rootNode->pointArray[i].y;
		sumZ=sumZ+rootNode->pointArray[i].z;
		nPoints++;		
	};
	
	Xc=sumX/(float)nPoints;
	Yc=sumY/(float)nPoints;
	Zc=sumZ/(float)nPoints;
	rootNode->posX=minX-Xc;
	rootNode->posY=minY-Yc;
	rootNode->posZ=minZ-Zc;
	
	if((maxX-minX)>=(maxY-minY) && (maxX-minX)>=(maxZ-minZ))
	{
		rootNode->dX=maxX-minX;
		rootNode->dY=maxX-minX;
		rootNode->dZ=maxX-minX;
	}
	else if ((maxY-minY)>(maxX-minX) && (maxY-minY)>(maxZ-minZ))
	{
		rootNode->dX=maxY-minY;
		rootNode->dY=maxY-minY;
		rootNode->dZ=maxY-minY;
	}
	else
	{
		rootNode->dX=maxZ-minZ;
		rootNode->dZ=maxZ-minZ;
		rootNode->dZ=maxZ-minZ;
	};
	
	for (int i=0;i<(int)rootNode->pointArray.size();i++)
	{
		rootNode->pointArray[i].x=rootNode->pointArray[i].x-Xc;
		rootNode->pointArray[i].y=rootNode->pointArray[i].y-Yc;
		rootNode->pointArray[i].z=rootNode->pointArray[i].z-Zc;
	};	
};


void OctreeTree::BuildOctree(Node *n)
{
	int points=n->pointArray.size();
	printf(" ");

	if (points > minNumPoints && n->level <=maxLevel)
	{
		for (int i=0;i<8;i++)
		{
			BuildOctree(BuildNode(n,i));
		};
	};

};

Node *OctreeTree::BuildNode(Node *nParent, int index)
{	
	int numParentPoints;
	Node * Child;
	
	switch(index)
	{
		case 0:
			Child= new Node(nParent->level+1,nParent->posX + nParent->dX/2,nParent->posY + nParent->dY/2,Child->posZ=nParent->posZ,nParent->dX/2,nParent->dY/2,nParent->dZ/2);
			nParent->child[index]=Child;
			break;
	 	case 1:
	 		Child = new Node(nParent->level+1,nParent->posX,nParent->posY + nParent->dY/2,nParent->posZ,nParent->dX/2,nParent->dY/2,nParent->dZ/2);
			nParent->child[index]=Child;
			break;
		case 2:
			Child = new Node(nParent->level+1,nParent->posX,nParent->posY,nParent->posZ,nParent->dX/2,nParent->dY/2,nParent->dZ/2);
			nParent->child[index]=Child;
			break;
		case 3:
			Child = new Node(nParent->level+1,nParent->posX + nParent->dX/2,nParent->posY,nParent->posZ,nParent->dX/2,nParent->dY/2,nParent->dZ/2);
			nParent->child[index]=Child;
			break;
		case 4:
			Child = new Node(nParent->level+1,nParent->posX + nParent->dX/2,nParent->posY + nParent->dY/2,nParent->posZ + nParent->dZ/2,nParent->dX/2,nParent->dY/2,nParent->dZ/2);
			nParent->child[index]=Child;
			break;
		case 5:
			Child = new Node(nParent->level+1,nParent->posX,nParent->posY + nParent->dY/2,nParent->posZ + nParent->dZ/2,nParent->dX/2,nParent->dY/2,nParent->dZ/2);
			nParent->child[index]=Child;
			break;
		case 6:
			Child = new Node(nParent->level+1,nParent->posX,nParent->posY,nParent->posZ + nParent->dZ/2,nParent->dX/2,nParent->dY/2,nParent->dZ/2);
			nParent->child[index]=Child;		;
			break;
		case 7:
			Child = new Node(nParent->level+1,nParent->posX + nParent->dX/2,nParent->posY,nParent->posZ + nParent->dZ/2,nParent->dX/2,nParent->dY/2,nParent->dZ/2);
			nParent->child[index]=Child;
			break;	
	};
	
	numParentPoints=(int) nParent->pointArray.size();
	
   	switch(index)
    {
                case 0:
                        for(int i = 0; i < numParentPoints; i++)
                        {
                                if( nParent->pointArray[i].x > nParent->posX+nParent->dX/2 && nParent->pointArray[i].y > nParent->posY + nParent->dY/2 && nParent->pointArray[i].x <= nParent->posX + nParent->dX && nParent->pointArray[i].y <= nParent->posY + nParent->dY && nParent->pointArray[i].z > nParent->posZ && nParent->pointArray[i].z <= nParent->posZ + nParent->dZ/2)
                                {
                                        Point temp;
                                        temp.x=nParent->pointArray[i].x;
                                        temp.y=nParent->pointArray[i].y;
                                        temp.z=nParent->pointArray[i].z;
                                        Child->pointArray.push_back(temp);
                                };
                        };
                        break;
                case 1:
                        for(int i = 0; i < numParentPoints; i++)
                        {
                                if(  nParent->pointArray[i].x > nParent->posX && nParent->pointArray[i].y > nParent->posY + nParent->dY/2 && nParent->pointArray[i].x <= nParent->posX + nParent->dX/2 && nParent->pointArray[i].y <= nParent->posY + nParent->dY && nParent->pointArray[i].z > nParent->posZ && nParent->pointArray[i].z <= nParent->posZ + nParent->dZ/2)
                                {
                                	    Point temp;
                                        temp.x=nParent->pointArray[i].x;
                                        temp.y=nParent->pointArray[i].y;
                                        temp.z=nParent->pointArray[i].z;
                                        Child->pointArray.push_back(temp);
                                };
                        }; 
                        break;
                case 2:
                        for(int i = 0; i < numParentPoints; i++)
                        {
                                if(nParent->pointArray[i].x > nParent->posX && nParent->pointArray[i].y > nParent->posY && nParent->pointArray[i].x <= nParent->posX + nParent->dX/2 && nParent->pointArray[i].y <= nParent->posY + nParent->dY/2 && nParent->pointArray[i].z > nParent->posZ && nParent->pointArray[i].z <= nParent->posZ + nParent->dZ/2)
                                {   
                                        Point temp;
                                        temp.x=nParent->pointArray[i].x;
                                        temp.y=nParent->pointArray[i].y;
                                        temp.z=nParent->pointArray[i].z;
                                        Child->pointArray.push_back(temp);	
                                };
                        };
                        break;
                        
                case 3:
                        for(int i = 0; i < numParentPoints; i++)
                        {
                                if( nParent->pointArray[i].x > nParent->posX +  nParent->dX/2 && nParent->pointArray[i].y > nParent->posY && nParent->pointArray[i].x <= nParent->posX + nParent->dX && nParent->pointArray[i].y <= nParent->posY + nParent->dY/2 && nParent->pointArray[i].z > nParent->posZ && nParent->pointArray[i].z <= nParent->posZ + nParent->dZ/2)
                                {
                                	    Point temp;
                                        temp.x=nParent->pointArray[i].x;
                                        temp.y=nParent->pointArray[i].y;
                                        temp.z=nParent->pointArray[i].z;
                                        Child->pointArray.push_back(temp);
                                };
                        };
                        break;
                        
                case 4:
                        for(int i = 0; i < numParentPoints; i++)
                        {                        
                                if( nParent->pointArray[i].x > nParent->posX+nParent->dX/2 && nParent->pointArray[i].y > nParent->posY + nParent->dY/2 && nParent->pointArray[i].x <= nParent->posX + nParent->dX && nParent->pointArray[i].y <= nParent->posY + nParent->dY && nParent->pointArray[i].z >nParent->posZ + nParent->dZ/2 && nParent->pointArray[i].z <= nParent->posZ + nParent->dZ)
                                {
                                	
                                	    Point temp;
                                        temp.x=nParent->pointArray[i].x;
                                        temp.y=nParent->pointArray[i].y;
                                        temp.z=nParent->pointArray[i].z;
                                        Child->pointArray.push_back(temp);
                                };
                        };
                        break;
                case 5:
                        for(int i = 0; i < numParentPoints; i++)
                        {
                                if( nParent->pointArray[i].x > nParent->posX && nParent->pointArray[i].y > nParent->posY + nParent->dY/2 && nParent->pointArray[i].x <= nParent->posX + nParent->dX/2 && nParent->pointArray[i].y <= nParent->posY + nParent->dY && nParent->pointArray[i].z >nParent->posZ + nParent->dZ/2 && nParent->pointArray[i].z <= nParent->posZ + nParent->dZ)
                                {
                                	    Point temp;
                                        temp.x=nParent->pointArray[i].x;
                                        temp.y=nParent->pointArray[i].y;
                                        temp.z=nParent->pointArray[i].z;
                                        Child->pointArray.push_back(temp);                                        
                                };
                        }; 
                        break;
                case 6:
                        for(int i = 0; i < numParentPoints; i++)
                        {                        	
                                if( nParent->pointArray[i].x > nParent->posX && nParent->pointArray[i].y > nParent->posY && nParent->pointArray[i].x <= nParent->posX + nParent->dX/2 && nParent->pointArray[i].y <= nParent->posY + nParent->dY/2 && nParent->pointArray[i].z >nParent->posZ + nParent->dZ/2 && nParent->pointArray[i].z <= nParent->posZ + nParent->dZ)
                                {   
                                	
                                	    Point temp;
                                        temp.x=nParent->pointArray[i].x;
                                        temp.y=nParent->pointArray[i].y;
                                        temp.z=nParent->pointArray[i].z;
                                        Child->pointArray.push_back(temp);
                                };
                        };
                        break;
                        
                case 7:
                        for(int i = 0; i < numParentPoints; i++)
                        {
                                if( nParent->pointArray[i].x > nParent->posX +  nParent->dX/2 && nParent->pointArray[i].y > nParent->posY && nParent->pointArray[i].x <= nParent->posX + nParent->dX && nParent->pointArray[i].y <= nParent->posY + nParent->dY/2 && nParent->pointArray[i].z >nParent->posZ + nParent->dZ/2 && nParent->pointArray[i].z <= nParent->posZ + nParent->dZ)
                                {
                                	    Point temp;
                                        temp.x=nParent->pointArray[i].x;
                                        temp.y=nParent->pointArray[i].y;
                                        temp.z=nParent->pointArray[i].z;
                                        Child->pointArray.push_back(temp);
                                };
                        };
                        break;                        
                        
        };
        return Child;
};


