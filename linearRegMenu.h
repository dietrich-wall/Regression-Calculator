#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


////////////////////////////////////////////////////////////////////////////////////////////
/// Print time and date
////////////////////////////////////////////////////////////////////////////////////////////

void currentTimeDate(){
	
	time_t timeObj;
	char timeString[100];
	struct tm *timeData;
	
	time( &timeObj ); 
	timeData = localtime( &timeObj );

	printf("\n\t%s\n\n", asctime(timeData)); 

	}

////////////////////////////////////////////////////////////////////////////////////////////
/// Print basic information about the program
////////////////////////////////////////////////////////////////////////////////////////////

void printREADME(){
	
	printf("\n\t\tLinar Regression Calculator\n\n");
	
	printf("\nThis Program will calculate the regression line as well as\n");
	printf("\nthe correlation coefficient from any two-dimensional sample points.\n\n\n");
	
	printf("\nThe File holding the sample points must meet these requirements:\n\n");
	
	printf("\n\t1. .txt file  \n");
	printf("\n\t2. MS-DOS format   \n");
	printf("\n\t3.  x and y sample points in opposing columns  \n\n");
	
	printf("\nPleas consider clearing the memory (menu option '0') before closing the program  \n\n\n");
	system("pause");
	
}

////////////////////////////////////////////////////////////////////////////////////////////
/// Print the program menu 
////////////////////////////////////////////////////////////////////////////////////////////

void printMenuOptions(){
	
	system("cls");
	
	printf("\n\tLinar Regression Calculator\n");
	currentTimeDate();
	
	printf("\n1. Upload new file\n\n");
	
	printf("\n2. Calculate and analyze regession line\n");
	printf("\n3. Calculation results\n");
	printf("\n4. Store calculation results in a file\n\n");
	
	printf("\n6. Calculate 'y' values with the regession function\n");
	printf("\n7. Store new XY table in a file\n\n");
	
	
	printf("\n\n0. Clear memory\n\n");
	printf("\nSelect to proceed: ");
}

////////////////////////////////////////////////////////////////////////////////////////////
/// Get integer input from user to navigate the menu
////////////////////////////////////////////////////////////////////////////////////////////

int getMenuSelection(){
	
	int selection;
	//flush user input
	fflush(stdin);
	
	printMenuOptions();
	
	//Safeguard from non integer input
	if(scanf("%i", &selection) != 1)
        getMenuSelection();
    else
        return selection;
}

////////////////////////////////////////////////////////////////////////////////////////////
/// Print deviation of each 'y' sample points to the regression line
////////////////////////////////////////////////////////////////////////////////////////////

void printSimpleDeviation(int fielsize, struct samplePoints *samplePointsIn, struct sums *sumValues, struct regression *regressionValues){
	
	double simpleDeviation;
	int i;
	
	printf("\n\nThe deviation of each sample point compared to the regression line:\n");
	
	for(i = 0; i < fielsize; i++){
		simpleDeviation =  regressionValues[0].m * samplePointsIn[i].x + regressionValues[0].b - samplePointsIn[i].y;
		printf("Point(%.1lf|%.1lf), deviation = %lf\n", samplePointsIn[i].x, samplePointsIn[i].y, simpleDeviation);
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////
/// Print all calculation results 
////////////////////////////////////////////////////////////////////////////////////////////

void printResults(int fielsize, struct samplePoints *samplePointsIn, struct sums *sumValues, struct regression *regressionValues){
	
	system("cls");
	
	printf("The mean of the submitted 'x' sample points is: %.4lf\n", sumValues[0].sumXmean);
	printf("The mean of the submitted 'y' sample points is: %.4lf\n", sumValues[0].sumYmean);
	printf("\n");
	printf("Calculated slope 'm' is: %.4lf\n", regressionValues[0].m);
	printf("Calculated y-intercept 'b' is: %.4lf\n", regressionValues[0].b);
	printf("\n");
	printf("The regresion function is: y = %.4lf * x + %.4lf\n", regressionValues[0].m, regressionValues[0].b);
	printf("\n");
	printf("The correlation coefficientr 'r' is: %lf\n", regressionValues[0].r);
	printf("The interpretation reads: %s\n", regressionValues[0].rInterpretation);
	printf("\n");
	printf("The 'simple deviation' of the input values is: %lf\n", sumValues[0].simpleDeviation);
	printf("The 'standart deviation' of the input values is: %lf\n", sumValues[0].standartDeviation);
	printf("\n");
	
	if(MessageBox_YESNO("Store simple deviation value for each sample point?", "Additional print") == IDYES)
		printSimpleDeviation(fielsize, samplePointsIn, sumValues, regressionValues);
		
	system("pause");
}

