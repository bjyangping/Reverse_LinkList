//20170427 reverse the linklist
#include<stdio.h>

#define NODE_N 10		//All the nodes in linklist, include the last NULL node
typedef struct linklist
{
	struct linklist * p;
	int iContent;
} NODE;


NODE * fReverse(NODE *p, int iLen);
void fPrintList(NODE *p);
NODE * fCreateList(void);
NODE *fNullNode(NODE *p);
NODE * fReverse_K(NODE *p, int K);

NODE nodeArray[NODE_N];
void main(void)
{
	NODE *pListOriginal=fCreateList();
	printf("---------------------before reverse-------------\n");
	fPrintList(pListOriginal);
	
	int K=3;		//Reversed every K nodes
	printf("---------------------after reverse_K(%d)-------------\n",K);
	NODE *pListReverse_K=fReverse_K(pListOriginal, K);
	fPrintList(pListReverse_K);
	
}


void fPrintList(NODE *p)
{
	int i=1;
	NODE *pTemp=p;
	do
	{
		printf("In %d node the content is: %d\n", i, pTemp->iContent);
		pTemp=pTemp->p;
		i++;
	}while(pTemp!=NULL);
}



NODE * fCreateList(void)
{
	for(int i=0; i<NODE_N-1; i++)
	{
		nodeArray[i].iContent=i+1;
		nodeArray[i].p=nodeArray+i+1;
	}
	nodeArray[i].iContent=i+1;
	nodeArray[i].p=NULL;
	return nodeArray;
}


NODE * fReverse_K(NODE *p, int K)
{
	NODE *pTemp=p;
	int iCntNode=0;		//count nodes in linklist ;include the NULL node
	int iCntReversed=0;	//count the segment linklist which are reversed
	NODE *pListHead=p;
	
	NODE *pSegHeadOriginal=p;
	NODE *pSegHeadReversed;
	NODE *pSegEndReversed;
	NODE *pSegEndReversedOld;
	NODE *pRemainHead;
	while(pTemp->p!=NULL)
	{
		iCntNode++;
		//printf("iCntNode=%d\n",iCntNode);
		
		pTemp=pTemp->p;
		if(iCntNode%K==0 && iCntNode>0)
		{
			
			iCntReversed++;
			//printf("iCntReversed=%d\n",iCntReversed);
			pRemainHead=pTemp;
			pSegHeadReversed=fReverse(pSegHeadOriginal, K);
			pSegHeadOriginal=pTemp;
			
			pSegEndReversed=fNullNode(pSegHeadReversed);
			if(iCntReversed>1)		//connect two segment linklist
			{
				pSegEndReversedOld->p=pSegHeadReversed;
				pSegEndReversedOld=pSegEndReversed;
			}
			else if(iCntReversed==1)		// record the new head of linklist and update last segment end
			{
				pListHead=pSegHeadReversed;
				pSegEndReversedOld=pSegEndReversed;
			}
			
			
		}
		
	}
	
	if(iCntReversed!=0)		//If there is some segment broken, connect them
	{
		pSegEndReversed->p=pRemainHead;
	}
	
	return pListHead;
	
}



NODE *fNullNode(NODE *p)
{
	NODE *pTemp=p;
	while(pTemp->p!=NULL)
	{
		pTemp=pTemp->p;
	}
	return pTemp;
}


NODE * fReverse(NODE *p, int iLen)		//Reverse the prefore "iLen" node, if iLen< length of input linklist, change the iLen node to NULL
{
	NODE *pTemp=p;
	NODE *pHeadReversed;
	int iNodeCover;
	if(iLen==1)		//only one node
	{
		pTemp->p=NULL;
		return pTemp;
	}
	else if( iLen==2)	//one head node and one null node
	{
		pHeadReversed=pTemp->p;
		pTemp->p->p=pTemp;
		pTemp->p=NULL;
		return pHeadReversed;
	}
	else if( iLen==3)	//one head, one middle, one null 
	{
		pHeadReversed=pTemp->p->p;
		pTemp->p->p->p=pTemp->p;
		pTemp->p->p=pTemp;
		pTemp->p=NULL;
		return pHeadReversed;
	}
	else 	//more than 4 nodes
	{	
		NODE *pBegin=pTemp->p->p;
		NODE *pEnd=pTemp->p;
		pEnd->p=pTemp;
		iNodeCover=3;
		do{
			iNodeCover++;
			pTemp=pBegin;			//temp save for pBegin;
			pBegin=pBegin->p;		//update, find the newer pBegin node before change pBegin node
			pTemp->p=pEnd;			//conect
			pEnd=pTemp;				//update
		}while(pBegin->p!=NULL && iNodeCover<iLen);		//when pBegin->p==NULL£¬there is no node after it, it will the new head of reversed linklist
		pBegin->p=pEnd;
		NODE *pNewEnd=p;
		pNewEnd->p=NULL;	//set new end of the reversed linklist
		return pBegin;
	}
}