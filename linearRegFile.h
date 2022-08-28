#include <stdio.h>
#include <stdlib.h>



////////////////////////////////////////////////////////////////////////////////////////////
/// Get filename from user
////////////////////////////////////////////////////////////////////////////////////////////
void getFileName(char *fileName){

	system("cls");

    ///Get filename from user
    printf("\nEnter file Name: ");
    scanf("%s", fileName);

    ///Append .txt if the user didn't do so
    if (strstr(fileName, ".txt") == 0)
        strcat(fileName, ".txt");
}

////////////////////////////////////////////////////////////////////////////////////////////
/// Open file in chosen mode. 
/// Ask user to reenter filename if pointer returns NULL
////////////////////////////////////////////////////////////////////////////////////////////

FILE *openFile(char *fileName, char *mode){
	
	//Ugly goto label to account for non existent filename
	REENTER_FILENAME:
	getFileName(fileName);
	
    FILE *filepointer;
	
	///Open file and check if done successfully
    filepointer = fopen(fileName, mode);
    if(filepointer == NULL){
    	MessageBox_OK("File not in directory.\nPlease reenter the file name.", "Error");
        goto REENTER_FILENAME;
	}
    return filepointer;
}

////////////////////////////////////////////////////////////////////////////////////////////
/// Count rows in file do determin it's size
////////////////////////////////////////////////////////////////////////////////////////////

int getFileLength(FILE *filePointer){
 
    char row[50];
    int count = 0;
    
	///Count rows in file until end of file
    do{
        fgets(row, 50, filePointer); 
        count++;
    }while(!feof(filePointer));

    rewind(filePointer);
    
    return count;
}

////////////////////////////////////////////////////////////////////////////////////////////
/// Read file content to struct
////////////////////////////////////////////////////////////////////////////////////////////

void readFile(int fileSize, FILE *filePointer, struct samplePoints *samplePointsIn){
	///Counter variable
	int i;
	
	///Scan file and write data to struct
	for(i = 0; i < fileSize; i++)
		fscanf(filePointer, "%lf %lf", &samplePointsIn[i].x, &samplePointsIn[i].y);
}

////////////////////////////////////////////////////////////////////////////////////////////
/// Write struct content to file
////////////////////////////////////////////////////////////////////////////////////////////

void writeXYtableToFile(int fileSize, FILE *filePointer, struct samplePoints *samplePointsOut){
	///Counter variable
	int i;
	///write data to file
	for (i = 0; i < fileSize; i++)
		fprintf(filePointer, "%.0lf\t%.2lf\n", samplePointsOut[i].x ,samplePointsOut[i].y);
}

////////////////////////////////////////////////////////////////////////////////////////////
/// Write simple deviation between sample points and regression line to file
////////////////////////////////////////////////////////////////////////////////////////////

void writeSimpleDeviationToFile(int fileSize, FILE *filePointer, struct samplePoints *samplePointsIn, struct regression *regressionValues){

	double deviation;
	int i;
	
	fprintf(filePointer, "\n\nThe deviation of each sample point compared to the regression line:\n\n");
	
	for(i = 0; i < fileSize; i++){
		deviation = samplePointsIn[i].y - (regressionValues[0].m * samplePointsIn[i].x + regressionValues[0].b);
		fprintf(filePointer, "Point(%.1lf|%.1lf), deviation = %lf\n", samplePointsIn[i].x, samplePointsIn[i].y, deviation);
	}
	
}


////////////////////////////////////////////////////////////////////////////////////////////
/// write calculation results to file
////////////////////////////////////////////////////////////////////////////////////////////

void writeResultsToFile(FILE *filePointer, struct sums *sumValues, struct regression *regressionValues){
	
	fprintf(filePointer, "This file contains the caclulation results\n\n");
	fprintf(filePointer, "The mean of the submitted 'x' sample points is: %.4lf\n", sumValues[0].sumXmean);
	fprintf(filePointer, "The mean of the submitted 'y' sample points is: %.4lf\n\n", sumValues[0].sumYmean);
	fprintf(filePointer, "Calculated slope 'm' is: %.4lf\n", regressionValues[0].m);
	fprintf(filePointer, "Calculated y-intercept 'b' is: %.4lf\n\n", regressionValues[0].b);
	fprintf(filePointer, "The regresion function is: y = %.4lf * x + %.4lf\n\n",regressionValues[0].m, regressionValues[0].b);
	fprintf(filePointer, "The correlation coefficient 'r' is: %lf\n",regressionValues[0].r);
	fprintf(filePointer, "The interpretation reads: %s\n\n", regressionValues[0].rInterpretation);
	fprintf(filePointer, "The simple deviation of the input values is: %lf\n", sumValues[0].simpleDeviation);
	fprintf(filePointer, "The standart deviation of the input values is: %lf\n", sumValues[0].standartDeviation);
}



