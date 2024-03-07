/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr)
 * @Version 20-10-2020
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */
#include <stdio.h>
#include <stdlib.h>

#include "pss.h"

void DL_Insert(struct Info **head,int id,int itm,int igp[64]){
    struct Info* current;
    struct Info* newNode = (struct Info*)malloc(sizeof(struct Info));
	newNode->iId=id;
	newNode->itm=itm;

    for(int i=0;i<64;i++){
		newNode->igp[i]=igp[i];
	}
	current=*head;
    if(*head == NULL ){
        *head=newNode;
        newNode->inext=NULL;
        newNode->iprev=NULL;
        
    }
    else if(current->itm <= newNode->itm){
        *head=newNode;
        newNode->inext=current;
        newNode->iprev=NULL;
		

    }else{  

        while(current->inext != NULL && current->inext->itm > newNode->itm){
            current=current->inext;
        }
        newNode->inext = current->inext;
        if(current->inext != NULL){
            newNode->inext->iprev = newNode;
        }
        current->inext = newNode;
        newNode->iprev = current;
        
		
    }

	
}
void DL_Delete(struct Info **head,int id){
    struct Info* current;
    struct Info* current2;
	struct Info* prev;
    current=*head;
    while(current != NULL){
		if((*head)->iId == id){
			current2=current;
			*head=current->inext;
			free(current);
			return;
		}else if (current->iId == id){
			prev=current->iprev;
			prev->inext=current->inext;
			current->iprev = prev;
			free(current);
			return;
		}
		prev=current;
        current=current->inext;
    }
	printf("Dind't find anything\n");
	return;
}
struct Info* DL_LookUp(struct Info *head,int id){
    struct Info* current;
    current=head;
    while( current != NULL){
        if(current->iId == id){
            return current;
        }
        current=current->inext;
    }
    return NULL;

}


void *DL_Print(struct Info* head){
    struct Info* current;
    current=head;
    while(current != NULL){
        printf("The information with id %d and timestamp %d\n",current->iId,current->itm);
		for(int i=0;i<64;i++){
			printf("The igp table is %d\n",current->igp[i]);
		}
        current=current->inext;
    }
}

void L_Insert(struct Subscription **head,int id){
    struct Subscription *current;
    struct Subscription *newNode = (struct Subscription*)malloc(sizeof(struct Subscription));
    newNode->sId=id;
    newNode->snext=NULL;
    if(*head == NULL){
        *head=newNode;
    }else{ 
        current=*head;
         while(current->snext != NULL){
             current=current->snext;
        }
     current->snext=newNode;
    }
}
void L_Delete(struct Subscription **head,int id){
    struct Subscription *current;
	struct Subscription *prev;
    struct Subscription *freevar;
    current=*head;
	prev=*head; 
		while( current != NULL){ 
			if((*head)->sId == id ){
				freevar=current;
				*head=current->snext;
				free(freevar);
				return;
			}else if (current->sId == id){
				freevar=current;
				prev->snext=current->snext;
				free(freevar);
				return;
			}
			prev=current;
			current=current->snext;
			
		}
		printf("Didn't find anything to delete\n");
		return;
	

}
struct Subscription* L_LookUp(struct Subscription* head, int id  ){
    struct Subscription *current;
    while(current != NULL){
        if(current->sId == id){
            return current;
        }
        current=current->snext;
    }
    printf("The Subscription with id %d doesn't\n",id);
    return NULL;
}
void L_Print(struct Subscription *head){
    struct Subscription *current;
    current=head;
    while(current != NULL){
        printf("%d ",current->sId);
        current=current->snext;
    }

}
void SL_Insert(struct SubInfo **head, int sId,int stm,struct Info *sgp[MG]){
    struct SubInfo *current;
    struct SubInfo *newNode = (struct SubInfo*)malloc(sizeof(struct SubInfo));
    newNode->sId = sId;
    newNode->stm = stm;
    for(int i=0;i<MG;i++){
        newNode->sgp[i]=sgp[i];
    }
    newNode->snext = NULL;
    if (*head == NULL || (*head)->stm >= newNode->stm){
        newNode->snext=*head;
        *head = newNode;
    }else {
        current=*head;
        while(current->snext != NULL && newNode->stm > current->snext->stm){ 
            current=current->snext;
        }
        current->snext=newNode;
    }
 }
 void SL_Delete(struct SubInfo **head,int Id){
    struct SubInfo *current;
    struct SubInfo *prev;
    struct SubInfo *tempformemallo;
    current=*head;
    while(current != NULL ){
        if((*head)->sId == Id){
            *head=current->snext;
            free(current);
            return;
        }else if(current->sId == Id){
            prev->snext = current->snext;
            free(current);
            return;
        }
        prev=current;
        current=current->snext;
    }
    printf("Dindt find anything\n");
    return;
        
}
struct SubInfo *SL_LookUp(struct SubInfo *head,int Id){
    struct SubInfo *current;
    current=head;
    while(current != NULL ){
        if(current->sId==Id){
            return current;
        }
        current=current->snext;
    }
    return NULL;
    
}
void SL_Print(struct SubInfo*head){
    struct SubInfo *current;
    current=head;
    while(current != NULL){
        printf("Subscriber with id %d and stm %d\n",current->sId,current->stm);
        current=current->snext;    
    }

}
/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */


int Insert_Info(struct Group G[64],int iTM,int iId,int* gids_arr,int size_of_gids_arr){
    int igp[64];
	int j=0;
	for(int i=0;i<64;i++){
		if(DL_LookUp(G[i].gfirst,iId) != NULL){
			printf("Already Exists\n");
			return 0;
		}
	}
	for(int k=0;k<size_of_gids_arr-1;k++){ 
		for(int i=0;i<64;i++){
			if(gids_arr[k] == G[i].gId/*i*/ ){
				igp[i] = 1 ;
			}else if(igp[i] != 1 && gids_arr[k] != G[i].gId){ 
				igp[i] = 0 ; 
			}
		}
	}

	for(int i=0;i<size_of_gids_arr-1;i++){

		DL_Insert(&G[gids_arr[i]].gfirst,iId,iTM,igp);

		struct Info* temp1=G[gids_arr[i]].gfirst;
		while(temp1->inext != NULL ){

			temp1=temp1->inext;

		}
		G[gids_arr[i]].glast = temp1;

	}
	int counter=0;
	printf("I %d %d DONE\n",iTM,iId);
	for(int i=0;i<64;i++){
		struct Info* temp1=G[i].gfirst;
		if(gids_arr[counter] == G[i].gId){ 
			printf("GROUPID = <%d>,",G[i].gId);
			counter++;
			printf("INFOLIST = ");
			while(temp1 != NULL){
				if(temp1->iId != NULL){
					printf("%d, ",temp1->iId);
				}
	
			temp1=temp1->inext;
	    }
		printf("\n");
		}
	}
    return EXIT_SUCCESS;
}
/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(struct Group G[64],struct SubInfo **head,int id){
	struct SubInfo* temp;
	//temp=*head;
    temp = SL_LookUp(*head,id);
	/*while(temp->sId != id && temp != NULL){
		temp=temp->snext;
	}*/
    if(temp == NULL){
        return 1 ;
    }
    /*for(int i=0;i<64;i++){
        if(temp->sgp[i]->iId == NULL){
            printf("%d",temp->sgp[i]->iId);
        }
    }*/
	for(int i=0;i<64;i++){
		if(temp->sgp[i] != 1){
			printf("GROUPID = <%d>,INFOLIST = <",G[i].gId);
            if(temp->sgp[i] == NULL && G[i].glast == NULL ){
                break;
            }else if( temp->sgp[i] == NULL && G[i].glast!= NULL){
                temp->sgp[i]=G[i].gfirst;
            } 
            while(temp->sgp[i]->inext != NULL){	

                printf("%d ",temp->sgp[i]->iId);
                temp->sgp[i]=temp->sgp[i]->inext;
                
            }
            printf("%d ",G[i].glast->iId);
		    printf(">,");
		    printf("NEWSGP=<%d>\n",temp->sgp[i]->iId);
		}
	}
    return EXIT_SUCCESS;
}
/**
 * @brief Subsriber Registration
 *
 * @param sTM Timestamp of arrival
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */

int Subscriber_Registration(struct Group G[64],struct SubInfo **head,int sTM,int sId,int* gids_arr,int size_of_gids_arr){
	struct Info* sgp[64];
	
	if(SL_LookUp(*head,sId) != NULL){
		printf("Already exists\n");
		return 0;
	}
	for(int k=0;k<64;k++){
		sgp[k]=(struct Info*)1;
	}
	for(int i=0;i<size_of_gids_arr-1;i++){
			
			sgp[gids_arr[i]]=G[gids_arr[i]].gfirst; //EDWWWW
            L_Insert(&G[gids_arr[i]].ggsub,sId);
	}
	SL_Insert(head,sId,sTM,sgp);


	//PRINT
	struct SubInfo *temp3;
	printf("SUBSCRIBERLIST = ");
	temp3=*head;
	printf("<");
	while(temp3 != NULL){
	 	printf("%d ",temp3->sId);
		temp3=temp3->snext;
	}
	printf(">");
	printf("\n");

	for(int i=0;i<size_of_gids_arr-1;i++){
		printf("GROUPID=<%d>,SUBLIST=<",G[gids_arr[i]].gId);
		struct Subscription* temp4;
		temp4=G[gids_arr[i]].ggsub;
		while(temp4!=NULL){
			printf(" %d",temp4->sId);
			temp4=temp4->snext;
		}
		printf(" >");
		printf("\n");
		
		
	}
	


	return EXIT_SUCCESS;
    
       
}
/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(struct Group G[64],struct SubInfo **head){
	struct Subscription *temp,*prev;
	struct Info *InfoTemp;
	int i=0;
	for(int i=0;i<64;i++){
		while(G[i].gfirst != NULL){
			DL_Delete(&G[i].gfirst,G[i].gfirst->iId);
		}
		while(G[i].ggsub != NULL){
			L_Delete(&G[i].ggsub,G[i].ggsub->sId);
		}
		
	}
	while(*head != NULL){
		SL_Delete(head,(*head)->sId);
	}
	
		
	
	return EXIT_SUCCESS;
}
/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(struct Group G[64],struct SubInfo**head, int sId){
	struct SubInfo *temp,*flag;
	struct Subscription *SubTemp;
	struct Info* InfoTemp;
	temp=*head;
	printf("D %d DONE\n",sId);
	printf("SubscriberList=<");
	while(temp != NULL){
		if(temp->sId != sId){
			printf("%d ",temp->sId);
		}else{
			flag=temp;
		}
		
		temp=temp->snext;
	}
	printf(">\n");
	for(int i=0;i<64;i++){
		if(flag->sgp[i] != 1 ){
			printf("GROUPID= <%d>,SubList=<",G[i].gId);
			SubTemp=G[i].ggsub;
			L_Delete(&SubTemp,sId);
			L_Print(SubTemp);
			printf(">\n");
			free(flag->sgp[i]);	
		}
	}
	printf("%d",flag->sId);
	SL_Delete(head,sId);


	return EXIT_SUCCESS;
}

/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */

int Print_all(struct Group G[64],struct SubInfo *head){
	int counter=0;
	int countersub=0;
	printf("P DONE\n");
	for(int i=0;i<64;i++){
		printf("GROUPID=<%d>,INFOLIST = ",G[i].gId);
		struct Info* TempInfo;
		printf("<");
		if(G[i].gfirst != NULL){
			counter++;
		}
		TempInfo=G[i].gfirst;
		while(TempInfo != NULL){
			printf("%d ",TempInfo->iId);
			TempInfo=TempInfo->inext;
		}
		printf(">");
		printf("\n");
	}
	struct SubInfo* tempSubs;
	tempSubs=head;
	printf("SubscriberList=");
	printf("<");
	while(tempSubs != NULL){
		printf("%d ",tempSubs->sId);
		countersub++;
		tempSubs=tempSubs->snext;
	}
	printf("\n");
	tempSubs=head;
	while(tempSubs!=NULL){  
		printf("SubscriberId=<%d>,",tempSubs->sId);
		printf("GROUPLIST=<");

		for(int i=0;i<64;i++){
			if(tempSubs->sgp[i] != 1){
				
				printf("%d ",G[i].gId);
			}
		}
		printf(">");
		printf("\n");
		tempSubs=tempSubs->snext;
	}
	printf("NO_GROUPS = <%d>",counter);
	printf("NO_SUBSCRIBERS =<%d>\n",countersub);
    return EXIT_SUCCESS;

}



 






