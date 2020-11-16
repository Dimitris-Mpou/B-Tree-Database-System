#include <stdio.h>
#include <stdlib.h>

#define MAXKEYNUM 7

typedef struct node {
    struct node *pointers[MAXKEYNUM+1];
    int keys[MAXKEYNUM];
    int is_leaf;
    int num_keys;
    struct node * next; // Used for queue.
    struct node * parent;
} node;

void init(node *node, char leaf){
	int i;
	
//	node=malloc(sizeof(node));
	node->is_leaf=leaf;
	if(!leaf){
		for(i=0; i<MAXKEYNUM+1; i++){
			node->pointers[i]=NULL;
		}
	}
		
	for(i=0; i<MAXKEYNUM; i++){
		node->keys[i]=-1;
	}
	
	node->num_keys=0;
	node->next= NULL;
	node->parent= NULL; 
}

node *search_node(node *root, int key){
	int i;
	node *cur_node;
	
	cur_node=root;
	
	while(cur_node->is_leaf==0){
		i=0;	
		while(i<MAXKEYNUM){
			if(key<cur_node->keys[i]){
				if(cur_node->pointers[i]==NULL){
					cur_node->pointers[i]=malloc(sizeof(node));
					init(cur_node->pointers[i], 1);
				}	
				cur_node= cur_node->pointers[i];
				break;
			}
			else if(cur_node->keys[i]==-1){
				if(cur_node->pointers[i]==NULL){
					cur_node->keys[i]=key;
					cur_node->pointers[i]=malloc(sizeof(node));
					init(cur_node->pointers[i], 1);
					cur_node->pointers[i]->parent=cur_node;
				}
				cur_node= cur_node->pointers[i];
				break;
			}
			else if(i==MAXKEYNUM){
				if(cur_node->pointers[i]==NULL){
					cur_node->pointers[i]=malloc(sizeof(node));
					init(cur_node->pointers[i], 1);
					cur_node->pointers[i]->parent=cur_node;
				}
				cur_node= cur_node->pointers[i+1];
				break;
			}
			else{
				i++;
			}
			
		}
	}
	return cur_node;
}


void insertion(node *root, int key){
	node *cur_node, *new_node, *new_eur;
	int i,j;
	
	cur_node= search_node(root, key);
	if(cur_node->num_keys==MAXKEYNUM){
		printf("Xreiazetai spasimo... the insertion failed\n");
		new_node= malloc(sizeof(node));
		init(new_node, 1);
		cur_node->next=new_node;
		
		for(i=0; i<=MAXKEYNUM/2; i++){
			new_node->keys[i]=cur_node->keys[i+MAXKEYNUM/2];	
		}
		new_node->num_keys=MAXKEYNUM/2+1;	/*An to MAXKEYNUM einai artios den xreiazetai to +1*/
		
		for(i=MAXKEYNUM/2; i<MAXKEYNUM; i++){
			cur_node->keys[i]=-1;
		}
		cur_node->num_keys=MAXKEYNUM/2;
		
		if(cur_node->parent==NULL){
			new_eur= malloc(sizeof(node));
			init(new_eur, 0);
			cur_node->parent= new_eur;
			new_node->parent= new_eur;
			new_eur->keys[0]=new_node->keys[0];
			new_eur->num_keys=1;
			new_eur->pointers[0]=cur_node;
			new_eur->pointers[1]=new_node;
			i=0;
		}
		else{
			if(cur_node->parent->num_keys<MAXKEYNUM){
				new_node->parent= cur_node->parent;
				i=0;
				while(new_node->parent->keys[i]<=new_node->keys[0] && i<new_node->parent->num_keys){
					i++;
				}
				if(i<new_node->parent->num_keys){
					for(j=new_node->parent->num_keys; j>i; j--){
						new_node->parent->keys[j]=new_node->parent->keys[j-1];
						new_node->parent->pointers[j+1]=new_node->parent->pointers[j];
					}
				}
				new_node->parent->keys[i]=new_node->keys[0];
				new_node->parent->pointers[i+1]=new_node;
				new_node->parent->num_keys++;
			}
			else if(cur_node->parent->num_keys==MAXKEYNUM && cur_node->parent->pointers[MAXKEYNUM]==NULL){
				
			}
		}
		if(key>=new_node->keys[0]){
			cur_node=new_node;
		}
			
	}
	i=0;
	while(cur_node->keys[i]<=key && i<cur_node->num_keys){
		i++;
	}
	if(i<cur_node->num_keys){
		for(j=cur_node->num_keys; j>i; j--){
			cur_node->keys[j]=cur_node->keys[j-1];
		}
	}
		cur_node->keys[i]=key;
		cur_node->num_keys++;
		printf("I inserted %d in position %d\n",cur_node->keys[i], i+1);	
}

int main(void){
	node *root;
	int i,j,z;
	
	root=malloc(sizeof(node));
	init(root, 1);
	insertion(root, 20);
	insertion(root, 1);
	insertion(root, 9);
	insertion(root, 3);
	insertion(root, 42);
	insertion(root, 14);
	insertion(root, 5);
	insertion(root, 29);
	
	root=root->parent;
	
	insertion(root, 31);	
	insertion(root, 45);
	insertion(root, 8);	
	insertion(root, 61);	
	insertion(root, 11);
	insertion(root, 15);
	insertion(root, 25);
	insertion(root, 27);
	insertion(root, 28);
	insertion(root, 2);
	insertion(root, 4);
	insertion(root, 6);
	insertion(root, 7);
	
	j=0;
	while(j<=MAXKEYNUM && root->pointers[j]!=NULL){
		i=0;
		while(i<MAXKEYNUM && root->pointers[j]->keys[i]!=-1){
			printf("%d\t",root->pointers[j]->keys[i]);
			i++;
		}
		j++;
		printf("\n\n");
	}
	insertion(root, 16);
	insertion(root, 17);
	insertion(root, 21);
	
	j=0;
	while(j<=MAXKEYNUM && root->pointers[j]!=NULL){
		i=0;
		while(i<MAXKEYNUM && root->pointers[j]->keys[i]!=-1){
			printf("%d\t",root->pointers[j]->keys[i]);
			i++;
		}
		j++;
		printf("\n\n");
	}
	
	insertion(root, 76);
	insertion(root, 56);
	insertion(root, 46);
	
	j=0;
	while(j<=MAXKEYNUM && root->pointers[j]!=NULL){
		i=0;
		while(i<MAXKEYNUM && root->pointers[j]->keys[i]!=-1){
			printf("%d\t",root->pointers[j]->keys[i]);
			i++;
		}
		j++;
		printf("\n\n");
	}
	
	insertion(root, 22);
	insertion(root, 23);
	insertion(root, 24);
	
	j=0;
	while(j<=MAXKEYNUM && root->pointers[j]!=NULL){
		i=0;
		while(i<MAXKEYNUM && root->pointers[j]->keys[i]!=-1){
			printf("%d\t",root->pointers[j]->keys[i]);
			i++;
		}
		j++;
		printf("\n\n");
	}
	
/*	 Print gia depth=3 (2 epipeda euretiriou + 1 dedomenwn)
	
	j=0;
	while(j<=MAXKEYNUM && root->pointers[j]!=NULL){
		i=0;
		while(i<MAXKEYNUM && root->pointers[j]->pointers[i]!=NULL){
			z=0;
			while(z<MAXKEYNUM && root->pointers[j]->pointers[i]->keys[z]){
				printf("%d\t",root->pointers[j]->pointers[i]->keys[z]);
				z++;
			}
			i++;
			printf("\n\n");
		}
		j++;
	}
*/	
	return 0;
}
