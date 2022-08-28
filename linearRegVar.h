
////////////////////////////////////////////////////////////////////////////////////////////
/// Structures of variables used for storing...
////////////////////////////////////////////////////////////////////////////////////////////

///...the progress of the program
struct progressFlags{
	int fileUploaded;
	int XYtableStored, resultsStored;
	int regressionLineCalculated, yWithRegFuncCalculated;
}progressFlag;

///...the values of the input file (samplePointsIn)
///...the values for the output file (samplePointsOut)
struct samplePoints{
	double x, y;
}*samplePointsIn, *samplePointsOut;

///...the parameters for calculating 'y' with the regression function
struct calculationParameters{
	int xMin, xMax;
	///Range between xMin and xMax
	///Used to determin the size of the samplePointsOut struct
	int xRange;
}*yCalculationParameters;

///...the sums, mean and variance values needed for the regression calculation 
struct sums{
	double sumX;
	double sumXpow2;
	double sumY;
	double sumXY;
	double sumXmean;
	double sumYmean;
	double varianceX;
	double varianceY;
	double varianceXY;
	double simpleDeviation;
	double standartDeviation;
}*sumValues;

///...the calculated regression values
struct regression{
	double m, b, r;
	//String for storing the interpretation of the correlation coefficient
	char rInterpretation[30];
}*regressionValues;

