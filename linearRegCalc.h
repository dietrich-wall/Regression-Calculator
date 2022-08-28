#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////////////////
/// Calculate sums, mean and variance values needed for the regression calculation 
////////////////////////////////////////////////////////////////////////////////////////////

void calculateSums(int n, struct samplePoints *samplePointsIn, struct sums *sumValues){
	///Counter variable
	int i;
	
	///Calculate sums from sample points
	for(i = 0; i < n; i++){
		sumValues[0].sumX += samplePointsIn[i].x;
		sumValues[0].sumXpow2 += samplePointsIn[i].x * samplePointsIn[i].x;
		sumValues[0].sumY += samplePointsIn[i].y;
		sumValues[0].sumXY += samplePointsIn[i].x * samplePointsIn[i].y;
	}	
	
	///Calculate mean value of sample points
	sumValues[0].sumXmean = sumValues[0].sumX / n;
	sumValues[0].sumYmean = sumValues[0].sumY / n;
	
	///Calculate squared deviation between each sample point and its mean value
	for(i = 0; i < n; i++){
		sumValues[0].varianceX += (samplePointsIn[i].x - sumValues[0].sumXmean) * (samplePointsIn[i].x - sumValues[0].sumXmean);
		sumValues[0].varianceY += (samplePointsIn[i].y - sumValues[0].sumYmean) * (samplePointsIn[i].y - sumValues[0].sumYmean);
		sumValues[0].varianceXY += (samplePointsIn[i].x - sumValues[0].sumXmean) * (samplePointsIn[i].y - sumValues[0].sumYmean);
	}
	
	///Calculate standart deviation
	sumValues[0].standartDeviation = sqrt(sumValues[0].varianceY / n);
}

////////////////////////////////////////////////////////////////////////////////////////////
/// Calculate slope and intercept for the regression function
/// Calculate correlation coefficient 
////////////////////////////////////////////////////////////////////////////////////////////

double denominator(int n, struct sums *sumValues){
	///denominator used for both m and b calculation
	return (n * sumValues[0].sumXpow2 - sumValues[0].sumX * sumValues[0].sumX);
}

double calculateSlope(int n, struct sums *sumValues){
	///return slope of the regression line
    return (n * sumValues[0].sumXY - sumValues[0].sumX * sumValues[0].sumY) / denominator(n, sumValues);
}

double calculateIntercept(int n, struct sums *sumValues){
	///return y-intercept constant of the regression line
	///(sumValues[0].sumY - regressionValues[0].m * sumValues[0].sumX) / n;
    return (sumValues[0].sumXpow2 * sumValues[0].sumY - sumValues[0].sumX * sumValues[0].sumXY) / denominator(n, sumValues);
}

double calculateCorrelationCoefficient(int n, struct sums *sumValues){
	///return correlation coefficient
    return sumValues[0].varianceXY / sqrt(sumValues[0].varianceX * sumValues[0].varianceY);
}

void calculateRegressionLine(int n, struct sums *sumValues, struct regression *regressionValues){
	///m: slope of the regression line
	regressionValues[0].m = calculateSlope(n, sumValues);
	
	///b: y-intercept constant of the regression line
	regressionValues[0].b = calculateIntercept(n, sumValues);
	
	///r: Correlation coefficient
	regressionValues[0].r = calculateCorrelationCoefficient(n, sumValues);
}

////////////////////////////////////////////////////////////////////////////////////////////
/// Interpret the correlation coefficient and store a textual interpretaion
////////////////////////////////////////////////////////////////////////////////////////////

void analyzeCorrelationCoefficient(struct regression *regressionValues){
	
	//Increase readability
	double r = regressionValues[0].r;
	
	///Inverse the correlation coefficient if it is negative
	if(r < 0)
		r *= (-1);
	
	///Store interpretation of the correlation coefficient according to its size	
	if(r == 0)
		strcpy(regressionValues[0].rInterpretation, "No linear correlation");
	else if(r > 0 && r <= 0.25)
		strcpy(regressionValues[0].rInterpretation, "Low linear correlation");
	else if(r > 0.25 && r <= 0.75)
		strcpy(regressionValues[0].rInterpretation, "Moderate linear correlation");
	else if(r > 0.75 && r < 1)
		strcpy(regressionValues[0].rInterpretation, "High linear correlation");
	else if(r == 1)
		strcpy(regressionValues[0].rInterpretation, "Absolute linear correlation");
	else
		strcpy(regressionValues[0].rInterpretation, "Value corrupted");
}

////////////////////////////////////////////////////////////////////////////////////////////
/// Calculate simple deviation between sample points and regression line
////////////////////////////////////////////////////////////////////////////////////////////

void calculateSumSimpleDeviation(int sampleCount, struct samplePoints *samplePointsIn, struct sums *sumValues, struct regression *regressionValues){
	
	int i;
	double deviation;
	/// f(xi) =  m*xi + b = yi
	for(i = 0; i < sampleCount; i++)
		deviation = samplePointsIn[i].y - (regressionValues[0].m * samplePointsIn[i].x + regressionValues[0].b);
		sumValues[0].simpleDeviation += deviation;
} 

////////////////////////////////////////////////////////////////////////////////////////////
/// Calculate 'y' values with the regression function
////////////////////////////////////////////////////////////////////////////////////////////

void calculateYwithRegfunction(struct regression *regressionValues, struct calculationParameters *yCalculationParameters, struct samplePoints *samplePointsOut){
	
	int i = 0, x;
	
	for (x = yCalculationParameters[0].xMin; x <= yCalculationParameters[0].xMax; x++){
		samplePointsOut[i].x = x;
		samplePointsOut[i].y = regressionValues[0].m * x + regressionValues[0].b;
		i++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
/// Get min and max value from user to calculate 'y' with regression function
/// Calculate range between chosen min and max values 
////////////////////////////////////////////////////////////////////////////////////////////

void getYcalculationParameter(struct calculationParameters *yCalculationParameters){
	
	system("cls");
    ///get xMin value from user
    printf("\nEnter minimum x value: ");
	scanf("%i", &yCalculationParameters[0].xMin);
	///get xMax valuefrom user
	printf("\nEnter maximum x value: ");
	scanf("%i", &yCalculationParameters[0].xMax);
	
	//safeguard in case xMax smaller than xMin
	if(yCalculationParameters[0].xMax < yCalculationParameters[0].xMin){
		MessageBox_OK("xMin has to be smaller than xMax", "error");
		getYcalculationParameter(yCalculationParameters);
	}
		
	//Calculate range between chosen xMin and xMax values 
	//Add 1 to account for 0
	//evtl noch eine abfrage ob eine 0 vorhanden ist, funzt aber auch so
	yCalculationParameters[0].xRange =  yCalculationParameters[0].xMax + yCalculationParameters[0].xMin * (-1) + 1;
}


