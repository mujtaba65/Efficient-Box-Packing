#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define box 6
#define length 5
#define width 4
/*
Prototypes of functions basically declares them so that i can implement my functions lower than main.
printInvoice basically prints the receipt with number of units for each type and boxes used along with the total and tax.
placementOfPackages is pretty straight forward packages the units in the respective place placing them from large to small.
randomNumber allocates a random number to each random number totalling upto 24.
printBox well it prints the 3d Array with the inner 2D array showing a box and the outer most being the box.
*/
void printInvoice(int s, int m, int l, int b);
int placementOfPackages(int *small, int *medium, int *large, char arr[*][length][width]);
void randomNumber(int *small, int *medium, int *large);
void printBox(char arr[*][length][width]);
/*
main is the heart of this code where mainly most variables are declared and nothing significant happens here, it calls the functions and most of the work happening in functions :D.
*/
int main(){
	int large = 0;
	int medium = 0;
	int small = 0;
	char arr[box][length][width] = {0};
	randomNumber(& small, & medium, & large);
	int totalLarge = large;
	int totalMedium = medium;
	int totalSmall = small;
	int boxes = placementOfPackages(& small, & medium, & large, arr);
        printInvoice(totalSmall, totalMedium, totalLarge, boxes);
        printBox(arr);
	return 0;
}
/*
It prints out the invoice taking the arguments sent from the main function,
PARAMETERS: small packages, medium packages, large packages and boxes. 
Return: None
*/
void printInvoice(int s, int m, int l, int b){
	float priceOfSmall = 5.99 * s;
	float priceOfMedium = 10.99 * m;
	float priceOfLarge = 19.99 * l;
	float total = priceOfSmall + priceOfMedium + priceOfLarge;
	float priceOfBoxes = 1.49 * b;
	printf("Small   (%02d Units)   $%6.2f \n", s, priceOfSmall);
	printf("Medium  (%02d Units)   $%6.2f \n", m, priceOfMedium);
	printf("Large   (%02d Units)   $%6.2f \n", l, priceOfLarge); 
	printf("=============================\n");
	printf("TOTAL                $%6.2f \n", total);
	printf("Shipping  (%d BOXES)  $%6.2f \n", b, priceOfBoxes);
	printf("HST  (13%%)           $%6.2f \n",(float) 0.13 * total);
	printf("=============================\n");
	printf("Amount Charged        $%6.2f   \n",(float) total + 0.13 * total + priceOfBoxes);
	return;
		
}
/*
It helps with allocating the variables declared in the main function for the respective packages,
it uses pointers so that it can refer the memory address of the respective variables, so setting those values = 0
in the main function was essentially pointless as they are either way being overwritten in this function.
PARAMETERS:  small packages, medium packages, large packages 
Return: None
*/
void randomNumber(int *small, int *medium, int *large){
	srand(time(NULL));
	*large = rand() % 24;
	int math = 24 - *large;
	*medium = rand() % math;
	*small = math - *medium;
	return;	
}
/*
this function is just for printing the items in the 3D array.
It uses 3 for loops to iterate over the array pretty similar to the function below this 
but this just makes use of couple of print statements.
PARAMETER: arr = the 3D array declared in the main function
Return: None
*/
void printBox(char arr[box][length][width]){
	for (int i = 0; i < box; i++){
       		for (int x = 0; x < length; x++){
       			for (int j = 0; j < width; j++){
       				if(arr[i][0][0] == 'L' || arr[i][0][0] == 'M' || arr[i][0][0] == 'S' ){
       					printf("%c", arr[i][x][j]);
       				}			
                	}
		        if(arr[i][0][0] == 'L' || arr[i][0][0] == 'M' || arr[i][0][0] == 'S' )
	       			printf("\n");	
                }
     		if(arr[i][0][0] == 'L' || arr[i][0][0] == 'M' || arr[i][0][0] == 'S' ){
       			printf("\n");
       		}
        }
        return;
}
/*
Well basically the name sums it up, but to clarify about the if loop 
the if loop checks the current index and the neighboring indexes depending on the 
type of packages its checking for, this function mainly tries to fit in a large package
then medium then small, going down the order.It also makes use of pointers so that it can overwrite 
values in the memory address, this is mainly important for the array. 
This function also fulls the empty bracket in main function for boxes as it returns number of boxes.
PARAMETERS: small, medium, large, arr
Return: b (number of boxes)
*/

int placementOfPackages(int *small, int *medium, int *large, char arr[box][length][width]){
	int b = 0;
	for(int i = 0; i < box; i++){
		for(int x = 0; x < length; x++){
			for(int j = 0; j < width; j++){	
				if(x < (length - 1) &&  j < (width -1)){
					if(*large != 0){
						if(arr[i][x][j] == 0 && arr[i][x+1][j] == 0 && arr[i][x][j+1] == 0 && arr[i][x+1][j+1] == 0 ){           
							arr[i][x][j] = 'L';
							arr[i][x+1][j] = 'L';
							arr[i][x][j+1] = 'L';
							arr[i][x+1][j+1] = 'L';
							*large -= 1;			
						}
					}
				}
				if(x < (length - 1) || j < (width -1)){
		    			if(*medium != 0){		    			
		    				if (arr[i][x][j] == 0 && arr[i][x][j+1] == 0){
		        	    			arr[i][x][j] = 'M';
		       					arr[i][x][j+1] = 'M';		       				
		        				*medium -= 1;
		        			}else if (arr[i][x][j] == 0 && arr[i][x+1][j] == 0){
		        	    			arr[i][x][j] = 'M';
		       					arr[i][x+1][j] = 'M';		       				
		        				*medium -= 1;
		        			}
		   			}
				}						
				if(arr[i][x][j] == 0){				
					if(*small != 0){
						arr[i][x][j] = 'S';					
						*small -= 1;
					}
				}
			}						
		}
     		if(arr[i][0][0] == 'L' || arr[i][0][0] == 'M' || arr[i][0][0] == 'S' ){
       			b++;	
       		}
	}
	return b;
}

