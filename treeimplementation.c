#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>



struct score {
	double score;
	int total_review;
	struct score* leftChild;
	struct score* rightChild;
	struct review* reviewChild;
};
//creating the review struct
struct review {
	int id;
	char text[100];
	struct review* leftChild;
	struct review* rightChild;
};
struct score *firstPtr;


//insertion functions
struct score* NewNode(double data, int id,char *c);
struct score* inserted(struct score* node, double data,int id,char *c);
struct review* NewReviewNode(int data,char *c);
struct review* insertedReview(struct review* node, int data,char *c);
void insertNewScore();
//searching functions
struct score* search(struct score * tree, double val);
void searchAllReviews(struct score *first ,int id);
struct review* searchReview(struct review* reviews,int id);
//printing functions
void print_preorder(struct score * tree);
 void print_preorders(struct review* review);
void print_inorder(struct score * tree);
void print_inorders(struct review* review);
void print_postorder(struct score * tree);
void print_postorders(struct review * review);
//deleting functions
struct score* deleteNode(struct score* root, double key);
struct review* deleteReviewNode(struct review* root);
struct score* findingMinimumNode(struct score* node);
void deletingScope();
//average functions
void findAverage(struct score* np);
//specific word functions
void isThereSpecificWord();
void print_Word(struct score * tree,char *c);
void print_Words(struct review * review,char *c);
//other functions
double menu();
void choiceDec();
void display();
//variables
double total=0,count=0,a=0,thiss=0;
int reviewCount=0,functionfour=0;
//MAIN
int main(){
	//variables
	char order[10];
	char path[50];
	char review_string[100];

	char* score="";
	char* id="";
	
    int ids=0;
	double scores=0;

	FILE *fp1,*fp2;
	//opening the order
	if((fp1=fopen("InputForProject2\\Order.txt","r"))==NULL){
		printf("Cannot open file.\n");
		exit(1);
	}
	//getting the orders
	while(!feof(fp1)){
		fscanf(fp1,"%s",order);
		//creating the path
	     strcpy(path,"InputForProject2\\");
	     strcat(path,order);
	     strcat(path,".txt");
	    //opening the path
	     if((fp2=fopen(path,"r"))==NULL){
	     	printf("Cannot open file.\n");
	     	exit(1);
	     }//reading the text
	     while(!feof(fp2)){
	     	fread(review_string,100,1,fp2);
	     }
	     //getting the id and score
	     score=strtok(order,"_");
	     id=strtok(NULL," ");
	     scores=atof(score);
	     ids=atoi(id);
	     
	    //insert
	     firstPtr=inserted(firstPtr,scores,ids,review_string);
	     
	}
	//menu part
	choiceDec();
	return 0;
}


 //new node
 struct score* NewNode(double data, int id,char *c) { 
 //memory allocation for a new node
  struct score* node = (struct score*)malloc(sizeof(struct score));  
  //adding data   
  node->score = data; 
  node->total_review=1;
  node->leftChild = NULL; 
  node->rightChild = NULL;
  //memory allocation for review node
  struct review* node2 = (struct review*)malloc(sizeof(struct review)); 
  //if there is a inserting new review .
  if(id==-152369){
  	node2=NULL;
  }
  else{
  node2->id = id; 
  node2->leftChild = NULL; 
  node2->rightChild = NULL;
  strcpy(node2->text,c);
  }
  
  node->reviewChild = node2;
//returning node
  return(node); 
} 
//review node
struct review* NewReviewNode(int data,char *c) { 
//mallocation
  struct review* node = (struct review*)malloc(sizeof(struct review));     
  node->id = data; 
  node->leftChild = NULL; 
  node->rightChild = NULL;
  strcpy(node->text,c);
  return(node); 
} 
 //insert method
 struct score* inserted(struct score* node, double data,int id,char *c) { 
 
  // 1. If the tree is empty,single node 
  if (node == NULL) { 
    return(NewNode(data,id,c)); 
  } 
  else { 
    // 2. else go down the tree
    if (data < node->score) 
	node->leftChild = inserted(node->leftChild, data, id,c); 
    else if(data > node->score)
	node->rightChild = inserted(node->rightChild, data, id,c);
	else{
		node->total_review++;
		node->reviewChild = insertedReview(node->reviewChild, id,c);
	}

    return(node);
  } 
} 
//insert review method
struct review* insertedReview(struct review* node, int data,char* c) { 
  // if null add a new node
  if (node == NULL) { 
    return(NewReviewNode(data,c)); 
  } 
  else { 
    //else go down the tree
    if (data < node->id) 
	node->leftChild = insertedReview(node->leftChild, data,c); 
    else if(data > node->id)
	node->rightChild = insertedReview(node->rightChild, data,c);

    return(node); 
  } 
}
 
 

 //search
struct score* search(struct score * tree, double val) {
	//if tree null, there is no node , so return null. nothing found
 if(!(tree)) {
   return NULL;
  }
  //if the node found
 if(val == (tree)->score) {
   return tree;
  }
  //go left 
  else if(val < (tree)->score) {
    search(((tree)->leftChild), val);
  } 
  //go right
  else if(val > (tree)->score){
    search(((tree)->rightChild), val);
  }
 }
 //
 //review search
 struct review* searchReview(struct review* reviews,int id){
 	//if the review is null return
 	if((reviews)==NULL) {
   return NULL;
  }
  //if the id which we want to find is equal to nodes id
 if(id == (reviews)->id) {

   return reviews;
  } else if(id < (reviews)->id) {

    searchReview(((reviews)->leftChild), id);
  } else if(id > (reviews)->id){

    searchReview(((reviews)->rightChild), id);
}
 }
void searchAllReviews(struct score *first ,int id){
 //	printf("%d  ",first->reviewChild->id);
     if(first){  
 		if(searchReview(first->reviewChild,id)!=NULL){
 			printf("there is an id with this id, be carefull !!!\n");
 			reviewCount++;
 		return ;
 		}
		 else{
 			searchAllReviews(first->leftChild,id);
 			
 	        searchAllReviews(first->rightChild,id);
 	    }
 	}
 	
 }

 
 



 void print_preorder(struct score * tree) {
 	
 if (tree) {
 printf("\n  %.1lf",tree->score);
 print_preorders(tree->reviewChild);
 print_preorder(tree->leftChild);
 print_preorder(tree->rightChild);
 }
 }
 void print_preorders(struct review* review){

if (review) {
	 printf("  %d   " ,review->id);
 print_preorders(review->leftChild);


 print_preorders(review->rightChild);
 }	
}
 
 
 void print_inorder(struct score * tree) {
 if (tree) {
 print_inorder(tree->leftChild);
 printf("\n  %.1lf     --- ",tree->score);
 print_inorders(tree->reviewChild);
 print_inorder(tree->rightChild);
 }
}

void print_inorders(struct review* review){

if (review) {
 print_inorders(review->leftChild);
 printf("  %d   " ,review->id);

 print_inorders(review->rightChild);
 }	
}
 
 
 void print_postorder(struct score * tree) {
 if (tree) {
 print_postorder(tree->leftChild);
 print_postorder(tree->rightChild);
 printf("\n  %.1lf    ",tree->score);
 print_postorders(tree->reviewChild);
 }
 }
 
 void print_postorders(struct review* review){

if (review) {
 print_postorders(review->leftChild);


 print_postorders(review->rightChild);
  printf("  %d   " ,review->id);
 }	
}
 
 //inserting New Score
 void insertNewScore(){
 	double value=0;
 	char gg[10]="";
 	char pp[10];
 	//getting the score number
 	printf("\n  ---  INSERTION A NEW SCORE TO MASTER-BST  ---  \nEnter the score number you want to add <score scope [0,5]> : ");
 	gets(gg);
 	value=atof(gg);
 	
 	
  //check the score which user entered, if it doesnt exist 
  if((value==0||value==1||value==2||value==3||value==4||value==5||value==0.5||value==1.5||value==2.5||value==3.5||value==4.5)){
 	if(search(firstPtr,value)==NULL){
      int a=0;
      //insert the score 
 		inserted(firstPtr,value,-152369,"");
 		//print the insertion information and get the new choice for processes
 		printf("The Score %lf added to the MASTER-BST\n\n1 - Display the new MASTER-BST\n2 - Go to Main MENU \n",value);
 		gets(pp);
 		a=atoi(pp);
 		if(a==1){
 		display();
 	    }
 	}
 	//if the score which user entered exists
 	else{
 		//print warning
 		printf("\nWARNING\nThere is an existing score with the score number %.1f\n\n",value);
 	}
 }
 else{
 	printf("\nYou have entered a score without the scope [0,5]\n");
 }
 }
 void insertNewReview(){
 	
 	struct score *temp=firstPtr;
 	int new_id=0;
 	double score_=0;
 	char ll[100];
 	char tt[100];
 	char zz[100];
 	printf("\nenter the review id you want to add : ");
 	gets(ll);
 	new_id=atoi(ll);
 	//call the funtion searchAllReviews to search if there is an existing review with the new id
   searchAllReviews(temp,new_id);
   //the global variable -if reviewCount == 0 , there is no review with this new id 
   if(reviewCount<1){
   	char review_c[100];
   	//get the review for insertion
   printf("The review id %d is suitable to add\nPlease enter the review (You can use only 100 charachters) :",new_id);
   gets(review_c);
   //geting the score number to add the review
   printf("\nenter the score number which you want to add the review to : ");
   gets(tt);
   score_=atof(tt);
   //finding the score node which the user wants to add the new review
   struct score* temp2=search(firstPtr,score_);
   //if temp2 is not null there is a score node to add
   if(temp2!=NULL){
   	//if the temp2 doesnt have a reviewChild so the total_review variable must be 1, because we are going to insert the first review
   if(temp2->reviewChild==NULL){
   		temp2->total_review=1;
   	}
   	//else we just need decrase the total_review of the temp2 one
   	else{
   		temp2->total_review++;
   	}
   	//call the function to inserting the review
   	temp2->reviewChild=insertedReview(temp2->reviewChild,new_id,review_c);
    //printing the insertion information
   	printf("\nThe Review with id %d has inserted to the Score with number %f \n\n",new_id,temp2->score);
   	//defaulting the variables for new process
   	reviewCount=0;
   	double displays=0;
   	printf("1 - Display the new MASTER-BST\n2 - Go to Main MENU : ");
   	gets(zz);
   	displays=atof(zz);
   	if(displays==1){
   	    display();
   	}
}
//if there is no node which the user want to add th review
else{
	double a=0;
	char kk[100];
	printf("\nThere is no score with score number %2.lf\n\n1 - Add a new review\n\n2 - Add the SCORE %2.lf and review %d please enter : ",score_,score_,new_id);
	gets(kk);
	a=atof(kk);
	//go to insertNewReview function
	if(a==1){
		insertNewReview();
	}
	//create the score node and add the review
	else if(a==2){
		if((score_==0||score_==1||score_==2||score_==3||score_==4||score_==5||score_==0.5||score_==1.5||score_==2.5||score_==3.5||score_==4.5)){
		
		inserted(firstPtr,score_,new_id,review_c);
		printf("\n\nThe SCORE with score number %2.lf added to the tree\n\n",score_);
	}
	else{
		printf("\nThe Score number %lf is not in the [0,5] scope, be carefull\n",score_);
	}
	}
}
}
//else the review which the user want to add exists
else{
	//default the variables
	reviewCount=0;
	double a=0;
	char tt[10];
	printf("\n\n1 - Add a new Review\n2 - Go to Main MENU : ");
	gets(tt);
	a=atof(tt);
	printf("\n\n");
	//call the insertNewReview function
	if(a==1){
		insertNewReview();
	}
}
 	
 }
struct score* deleteNode(struct score* root, double key)
{
	//if the node is null return because there is no node the delete
    if (root == NULL) 
	return root;
 //if the key which we want to delete is not bigger than the node's score go to the letChilf of the node
    else if (key < root->score)
    //go to the leftChild
        root->leftChild = deleteNode(root->leftChild, key);
        //if the key which we want to delete is bigger than the node's score go to the rightChilf of the node
    else if (key > root->score)
    //go to the rightChild
        root->rightChild = deleteNode(root->rightChild, key);
   //if the key is equal to the node's score, yeeaahh i have found you finally part.
    else
    {
    	//if the node which we want to delete doesnt have any child
        if(root->leftChild==NULL&& root->rightChild==NULL){
        	//just free the root
        	//root->reviewChild=deleteReviewNode(root->reviewChild);
        	root->reviewChild=NULL;
        	free(root);
        	//return null
        	return NULL;
        }
        //if the node which we want to delete has only the rightChild
        else if (root->leftChild == NULL)
        {
        	//get the right child of the node
            struct score *temp = root->rightChild;
            root->reviewChild=NULL;
            //root->reviewChild=deleteReviewNode(root->reviewChild);
            //free the node
            free(root);
           //and return the rightChild of the node 
            return temp;
        }
        //if the node which we want to delete has only the leftChild
        else if (root->rightChild == NULL)
        {
        	//get the leftChild of the node
            struct score *temp = root->leftChild;
            root->reviewChild=NULL;
            //root->reviewChild=deleteReviewNode(root->reviewChild);
            //free the node
            free(root);
           //and return the leftChild of the node
            return temp;
        }
        //if the node which we want to delete has two children, the problem begins :)
        else{
        	//we have to choose a new node to put to the place of the node which will be deleted
        	//so this new node must be the leftest child of the right subtree of the node which will bi deleted
        	//call the findingMinimumNode funtion to find the leftest node of the right subtree
        	//and get it to the temp
        struct score* temp = findingMinimumNode(root->rightChild);
        //the new score must be the minimum nodes score
        root->score = temp->score;
        root->reviewChild=temp->reviewChild;
        //and delete the right
        //root->rightChild->reviewChild=deleteReviewNode(root->rightChild->reviewChild);
        
        root->rightChild = deleteNode(root->rightChild, temp->score);
        }
        
    }
    return root;
}

struct review* deleteReviewNode(struct review* root)
{
	if(root){
		deleteReviewNode(root->rightChild);
		deleteReviewNode(root->leftChild);
		free(root);
		return NULL;
	}
}


 double menu(){	
 
    char c[50];
//variable to put the choice of user
    double choice=0;
 	
 		//printing the menu
 		printf("\n1. Add a new score node into the master-BST .  \n2. Add also some reviews into a specific review-score category.") ;
		 printf("\n3. Show the average score of all of the reviews. \n4. List the id s of reviews which have a particular word.");
		 printf(" \n5. Remove the reviews between in a specific score-scope. \n6. Display the tree. \n7. Exit : ");
		 //getting the choice
		 gets(c);	
		 //casting the choice double
		 choice=atof(c);
		 //if choice is not valid 
		 if(choice>7||choice<1){
		 	printf("\n\nNOT VALID INPUT\n\n");
		 	//returning the original caller funtion -1234567 for not valid input
		 	return -1234567;
		 }
		 //if choice is valid returning the choice
		 return choice;
		 
 }
void choiceDec(){
	//
	double choice=0;
	//calling the menu to find the users choice
	choice=menu();
	//printf("%lf",choice);
	
	if(choice==-1234567){
		choiceDec();
	}
	else if(choice==1){
		//calling the funtion for inserting new score
		insertNewScore();
		//calling the menu after the process
		choiceDec();
	}
    else if(choice==2){
    	//calling the function for inserting new review
    	insertNewReview();
    	//calling the menu after the process
    	choiceDec();
    }
    else if(choice==3){
    	printf("\n\n");
    	//declaring the variables as default for new process
    	total=count=a=thiss=0;
    	//calling the function to find average
    	findAverage(firstPtr);
    	//printing the average
		printf("The AVERAGE SCORE OF THE MASTER-BST is %lf",total/thiss);
		printf("\n\n");
		//calling the menu after the process
		choiceDec();
    }
    else if(choice==4){
    	//calling the function to check the specific word-review
    	isThereSpecificWord();
    	//calling the menu after the process
        choiceDec();
    }
    else if(choice==5){
    	//calling the function to delete scope
    	deletingScope();
    	choiceDec();
    }
    else if(choice==6){
    	//calling the function to display the master-BST
    	display();
    	choiceDec();
    }
    else if(choice==7){
    	exit(0);
    }

}
//average
void findAverage(struct score* np){
	//if the node is not null
if(np){
	//check the left child of the node
	findAverage(np->leftChild);
	//if the reviewChild of the node is not null count must be the totalreview of the node
	if(np->reviewChild!=NULL){
		//getting the node's total_review
		count=np->total_review;
	}
	else{
		//if the reviewChild of the node is null there wont be a review so the count must be 0
		count=0;
	}
	//getting the score of the node
	a=np->score;
	//adding the total
	total+=(count*a);
	//counting only the reviews
	thiss+=count;
	//checking the right child of the node;
	findAverage(np->rightChild);
}
}

//deleting
void deletingScope(){
    char c[50];
    char cends[50];
	double starts=0,ends=0;
	
	printf("\n--- Deleting the reviews in specific scope ---\nEnter the starting score number : ");
	//scanning the starting score number to delete
	gets(c);
	//casting the scorenumber which is string to the double variable
	starts=atof(c);

	printf("\nEnter the ending score number : ");
		//scanning the ending score number to delete
	gets(cends);
	//casting the ending score number which is string to the integer variable
	ends=atof(cends);
	
	
	if(starts>ends){
		double temp=ends;
		ends=starts;
		starts=temp;
	}
			//if the starting score number is little than the ending score ,
	while(starts<=ends){
		//call the deleteNode function to delete the score which has score number 
		
		firstPtr=deleteNode(firstPtr,starts);
		//go to next score number
		starts=starts+0.5;
	}
	
    
	

}
//
struct score* findingMinimumNode(struct score* node){
	//the min node must be placed in the left child of the left subtree, so we have to check the leftest leaf of the leftest child
	while(node->leftChild != NULL) {
	
	node = node->leftChild;
}
//when the min found, return it to the original caller deleteNode function
	return node;
}

//displaying the master-BST
void display(){
	int a=0;
	char ccd[10];
	printf("1 - Preorder\n2 - Inorder\n3 - Postorder : ");
	gets(ccd);
	a=atoi(ccd);
	    printf("\n\n\nSCORES    ---             REVIEWS");
	    //calling print_inorder function to print all elements of BST
	    if(a==1){
	    	print_preorder(firstPtr);
	    }else if(a==2){
	    	print_inorder(firstPtr);
	    }
	    else if(a==3){
	    	print_postorder(firstPtr);
	    }
	    else{
	    	printf("Wrong Choice");
	    }
		
		printf("\n\n\n");
}
//
void isThereSpecificWord(){
	char cs[100];
    printf("\nEnter the word to search : ");
    //getting the word which the user want to searh for reviews
    gets(cs);
    //calling print_Word function to search the word
    print_Word(firstPtr,cs);
    //checking the result
    if(functionfour==0){
    	//if there is no review which doesnt have the word print ---none---
    	printf("---none---");
    }
    functionfour=0;
}
//
void print_Word(struct score * tree,char *c) {
	//if tree isnt null ,
 if (tree) {
 	//call the same function to check the leftChild of the tree
 print_Word(tree->leftChild,c);
 //call the print_Words function to check the reviewChild of the tree
 print_Words(tree->reviewChild,c);
 //call the same function to check the rightChild of the tree
 print_Word(tree->rightChild,c);
 }
}
//
void print_Words(struct review* review,char *c){
	//if review isnt null ,
if (review) {
	//call the same function to check the left child of the review
 print_Words(review->leftChild,c);
//call the same function to check the right child of the review
 print_Words(review->rightChild,c);
 //if the review includes the word which entered by the user so,
  if(strstr(review->text,c)!=NULL){
  	//print the id of the review which includes the particular word
 printf("\nREVIEW %d\n" ,review->id);
 //and add 1 to the integer variable functionfour to understand the counting of reviews which have particular word
 functionfour++;
 }
 }	
}

 
