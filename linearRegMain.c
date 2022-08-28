////////////////////////////////////////////////////////////////////////////////////////////
/// Projekt:			Lineare Regression
/// Schule: 			BBS-ME Fachschule Elektrotechik
///	Klasse: 			FSEA20
/// Projektbetreuer: 	Hadifi, T. 
/// Projektgruppe:		Güney, A.
///						Schlüter, N.
///						Wall, D.
////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

///MessageBox_OK management functions 
#include "linearRegMB.h"
///#define(s) to increase readability of the code
#include "linearRegDef.h"
///Structures of variables
#include "linearRegVar.h"
///File handling, open, read, write
#include "linearRegFile.h"
///Calculation functions
#include "linearRegCalc.h"
///Menu and printToScreen functions
#include "linearRegMenu.h"



int main(int argc, char *argv[]){

	FILE *filePointer_main;
	char fileName_main[30];
	int fileSize_main;
	
	///Print basic information about the program
	printREADME();
	
	while(1){
		
		///switch through user selected menu cases 
		switch(getMenuSelection()) {
			
			case UPLOAD_NEW_FILE: 
				
				///Get file name, open file in read mode
				filePointer_main = openFile(fileName_main, READ);
				///Count rows in file to determin how many sample points there are
				fileSize_main = getFileLength(filePointer_main);
				///allocate memory for input values
				samplePointsIn = GET_MEMORY(samplePoints, fileSize_main);
				CHECK_MEMORY(samplePointsIn);
				///read file content to struct and close file afterwards
				readFile(fileSize_main, filePointer_main, samplePointsIn);
				fclose(filePointer_main);
				///set progression flag
				progressFlag.fileUploaded = TRUE;
				///Update user about progression
				MessageBox_OK("File upload complete.", "Information");
				
			break;
			
			case CALCULATE_REGRESSION_LINE: 
			
				if(progressFlag.fileUploaded == TRUE){
					///allocate memory for sum and regression values
					sumValues = GET_MEMORY(sums, 1);
					CHECK_MEMORY(sumValues);
					regressionValues = GET_MEMORY(regression, 1);
					CHECK_MEMORY(regressionValues);
					///Calculate sums, regression function, deviation
					calculateSums(fileSize_main, samplePointsIn, sumValues);
					calculateRegressionLine(fileSize_main, sumValues, regressionValues);
					calculateSumSimpleDeviation(fileSize_main, samplePointsIn, sumValues, regressionValues);
					///Analyze the correlation coefficient, store textual interpretaion
					analyzeCorrelationCoefficient(regressionValues);
					///set progression flag
					progressFlag.regressionLineCalculated = TRUE;
					///Update user about progression
					MessageBox_OK("Calculation complete.", "Information");
				}else
					MessageBox_OK("Please upload a file.", "MessageBox_OK");
			break;
			
			case PRINT_RESULTS: 
				
				if(progressFlag.regressionLineCalculated == TRUE)
					///Print calculation results to the screen
					printResults(fileSize_main, samplePointsIn, sumValues, regressionValues);
				else
					MessageBox_OK("Calculation not finished.", "Information");
			break;
			
			case RESULTS_TO_FILE: 
			
				if(progressFlag.regressionLineCalculated == TRUE){
					///Get file name and open in write mode
					filePointer_main = openFile(fileName_main, WRITE);
					///write to file
					writeResultsToFile(filePointer_main, sumValues, regressionValues);
					///write additional content
					if(MessageBox_YESNO("Print simple deviation value for each sample point?", "Message") == IDYES)
						writeSimpleDeviationToFile(fileSize_main, filePointer_main, samplePointsIn, regressionValues);
					///close file
					fclose(filePointer_main);
					///Update user about progression
					MessageBox_OK("File successfully created", "Information");
				}else
					MessageBox_OK("Please upload a file and/or finish calculation.", "MessageBox_OK");
			break;
			
			case CALCULATE_Y_WITH_REG_FUNC: 
			
				if(progressFlag.regressionLineCalculated == TRUE){
					///allocate memory for file parameters
					yCalculationParameters = GET_MEMORY(calculationParameters, 1);
					CHECK_MEMORY(yCalculationParameters);
					///get xMin and xMax from user and calculate the range between them
					getYcalculationParameter(yCalculationParameters);
					///allocate memory for XY table
					samplePointsOut = GET_MEMORY(samplePoints, yCalculationParameters[0].xRange);
					CHECK_MEMORY(samplePointsOut);
					///Calculate y with linear regression function 
					calculateYwithRegfunction(regressionValues, yCalculationParameters, samplePointsOut);
					///set progression flag
					progressFlag.yWithRegFuncCalculated = TRUE;
					///Update user about progression				
					MessageBox_OK("Calculation complete.", "Information");
				}	
				else
					MessageBox_OK("Please calculate regression function from input file first.", "MessageBox_OK");
			break;
					
			case XY_TABLE_TO_FILE: 
				
				if(progressFlag.yWithRegFuncCalculated == TRUE){
					///Get file name and open in write mode
					filePointer_main = openFile(fileName_main, WRITE);
					///write to file and close afterwards 
					writeXYtableToFile(yCalculationParameters[0].xRange, filePointer_main, samplePointsOut);
					fclose(filePointer_main);
					///Update user about progression
					MessageBox_OK("File successfully created", "Information");
				}else
					MessageBox_OK("Please upload a file and/or finish calculations.", "MessageBox_OK");
			break;
			
			case CLEAR_MEMORY: 
				///free memory and reset flag if it has been set
				if(progressFlag.fileUploaded == TRUE){
					free(samplePointsIn);
					progressFlag.fileUploaded = FALSE;
				}
				///free memory and reset flag if it has been set
				if(progressFlag.regressionLineCalculated == TRUE){
					free(sumValues);
					free(regressionValues);
					progressFlag.regressionLineCalculated = FALSE;
				}
				///free memory and reset flag if it has been set
				if(progressFlag.yWithRegFuncCalculated == TRUE){
					free(yCalculationParameters);
					free(samplePointsOut);
					progressFlag.yWithRegFuncCalculated = FALSE;
				}
				
				MessageBox_OK("Memory cleared.", "Information");
			break;
				
			default: 
			//flushing of invalide input taken care of in getMenuSelection() function
			break;
		}				
	}
	
	return 0;
}
