//standard header files
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//defining constants
#define MAX_TRANSACTIONS 1000
#define MAX_LENGTH 50
#define FALSE_STATUS 'F'
#define TRUE_STATUS 'T'
#define FILENAME "creditCardData.txt"
#define NUM_OF_CLUSTERS 3 
#define MAX_ITERATION 100
#define THRESHOLD 4

//defining constants for colours
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define DEFAULT "\x1b[0m"

struct Transaction {

    double amount;
    char location[MAX_LENGTH];
    char ip[MAX_LENGTH];

};

//function to read data and return no. of transactions
int readDataFromFile( struct Transaction *transactions ){

    FILE *file = fopen( FILENAME , "r" );

    if ( file == NULL ){

        printf( RED "Error in opening the file.......\n\n" DEFAULT );
        exit( EXIT_FAILURE );
        return 0;

    } else {

        int count = 0;
        while ( fscanf( file , "%lf %s %s", &transactions[count].amount , transactions[count].ip , 
        transactions[count].location ) == 3 && count < MAX_TRANSACTIONS ){

            count++ ;

        }

        return count;
        
    }

    fclose( file );

}

int calculateDistance( struct Transaction point1 , struct Transaction point2 ){

    return fabs( point1.amount - point2.amount );

}

void assignTransactionToCluster( struct Transaction *transactions , struct Transaction *centroids , 
int numOfTransactions , int transactionCluster[ numOfTransactions ] ){

    double minDistance = 0;
    double distance = 0;
    for ( int i = 0 ; i < numOfTransactions ; i++ ){

        minDistance = calculateDistance( transactions[i] , centroids[0] );
        int clusterIndex = 0;

        for ( int j = 1 ; j < NUM_OF_CLUSTERS ; j++ ){

            distance = calculateDistance( transactions[i] , centroids[j] );
            
            if( minDistance > distance ){

                minDistance = distance;
                clusterIndex = j;

            }

        }

        transactionCluster[i] = clusterIndex;

    }

}

void updateCentroids( struct Transaction *transactions , struct Transaction *centroids , 
int numOfTransactions , int transactionCluster[ numOfTransactions ] ){

    int clusterCounts[ NUM_OF_CLUSTERS ] = {0};
    for ( int i = 0; i < numOfTransactions; i++ ) {

        int clusterIndex = transactionCluster[i];
        centroids[clusterIndex].amount += transactions[i].amount;
        clusterCounts[clusterIndex]++;

    }

    for ( int i = 0; i < NUM_OF_CLUSTERS; i++ ) {

        if ( clusterCounts[i] > 0 ) {

            centroids[i].amount /= clusterCounts[i];

        }

    }

}

void calculateStatistics( struct Transaction *transactions , int numOfTransactions , 
double *mean , double *standardDeviation ){

    //Calculating mean.........
    *mean = 0.0;
    double transactionsSum = 0.0;

    for( int i = 0 ; i < numOfTransactions ; ++i ){

        transactionsSum += transactions[i].amount;

    }

    *mean = transactionsSum / numOfTransactions;

    //Calculating standard deviation.....
    double squaredDiff = 0.0;

    for( int i = 0 ; i < numOfTransactions ; ++i ){

        squaredDiff += pow( transactions[i].amount - *mean , 2 );

    }

    *standardDeviation = sqrt( squaredDiff / numOfTransactions );

}

int detectPotentialFraud( struct Transaction *transactions , struct Transaction *centroids , 
int numOfTransactions , double mean , double standardDeviation , int fraudIndex[ numOfTransactions ] , 
int *fraudCount ){

    //checking using k-means and statistics
    char status = TRUE_STATUS;  
    for( int i = 0 ; i < numOfTransactions ; i++ ){

        double minDistance = calculateDistance( transactions[i] , centroids[0] );
        for ( int j = 1; j < NUM_OF_CLUSTERS; j++ ) {

            double distance = calculateDistance( transactions[i] , centroids[j]);
            if (distance < minDistance) {                

                minDistance = distance;

            }

        }

        if( ( minDistance > THRESHOLD && transactions[i].amount > mean + 2 * standardDeviation ) || 
        ( transactions[i].ip[0] == '1' && transactions[i].ip[1] == '9' && transactions[i].ip[2] == '2' && transactions[i].ip[3] == '.' 
        && transactions[i].ip[4] == '1' && transactions[i].ip[5] == '6' && transactions[i].ip[6] == '8' ) ){

            //fraud detect
            fraudIndex[i] = 1;
            (*fraudCount)++;
            status = FALSE_STATUS;

        } else {

            //no fraud (no anomaly detected)
            fraudIndex[i] = 0;

        }

    }

    if ( status == 'F' ){

        return 1;

    } else {

        return 0;
        
    }

}

int checkTransactions( struct Transaction *transactions , int numOfTransactions ){

    char status = TRUE_STATUS;

    /*Checking number of transactions....*/
    if ( numOfTransactions <= 0 ){

        printf( RED "No valid transactions found.\n\n" DEFAULT );
        status = FALSE_STATUS;

    }

    for ( int i = 0 ; i < numOfTransactions ; i++ ){

        /*Checking amount of each transaction.....*/
        if( transactions[i].amount < 0.0 ){

            printf( RED "Invalid Transaction Amount Found!!\n\n" DEFAULT );
            status = FALSE_STATUS;

        /*Checking location where transaction took place....*/
        } else if ( transactions[i].location[0] == '\0' ){

            printf( RED "Invalid Location Detected....\n\n" DEFAULT );
            status = FALSE_STATUS;

        }

    }

    if( status == 'F'){

        //wrong data
        return 0;

    } else {

        return 1;

    }

}

int main(){

    //start the program

    struct Transaction transactions[MAX_TRANSACTIONS];

    printf( YELLOW "\nCredit Card Fraud Detector\n\n" DEFAULT );
    
    int numOfTransactions = readDataFromFile( transactions );
    int transactionStatus = checkTransactions( transactions , numOfTransactions );

    if ( transactionStatus ){

        //Iitialise centroids randomly or manually
        struct Transaction centroids[ NUM_OF_CLUSTERS ];
        for ( int i = 0 ; i < NUM_OF_CLUSTERS ; i++ ){

            centroids[i] = transactions[ rand() % numOfTransactions ];

        }

        //performing k means cluster algorithm
        for ( int i = 0 ; i < MAX_ITERATION ; i++ ){

            int transactionCluster[ numOfTransactions ];
            assignTransactionToCluster( transactions , centroids , numOfTransactions , transactionCluster );
            updateCentroids( transactions , centroids , numOfTransactions , transactionCluster );

        }

        //calculate statistics like mean and standard deviation
        double mean , standardDeviation;
        calculateStatistics( transactions , numOfTransactions , &mean , &standardDeviation );

        //function to detect potential fraud
        int fraudIndex[ numOfTransactions ];
        int fraudCount = 0;
        int isFraud = detectPotentialFraud( transactions , centroids , numOfTransactions , mean , 
        standardDeviation , fraudIndex , &fraudCount );

        //Output result
        printf( YELLOW "Red Transactions --> Potential Fraud\nGreen Transactions --> Non Fraud\n\n" DEFAULT );
        printf( BLUE "Number of Frauds Found : %d\n\n" DEFAULT , fraudCount );
        printf(YELLOW "No.\tAmount\t\tIP\t\tLocation\n" DEFAULT);
        if ( isFraud ){

            for( int i = 0 ; i < numOfTransactions ; i++ ){

                if( fraudIndex[i] == 1 ){

                    printf( RED "%d\t%lf\t%s\t%s\n" DEFAULT , i+1 , transactions[i].amount , transactions[i].ip , 
                    transactions[i].location );

                } else if ( fraudIndex[i] == 0 ){

                    printf( GREEN "%d\t%lf\t%s\t%s\n" DEFAULT , i+1 , transactions[i].amount , transactions[i].ip , 
                    transactions[i].location );

                }

            }

        } else {

            for( int i = 0 ; i < numOfTransactions ; i++ ){

                printf( GREEN "%d\t%lf\t%s\t%s\n" DEFAULT , i+1 , transactions[i].amount , transactions[i].ip , 
                transactions[i].location );

            }

        }

    } else {

        return 1; 

    }
    
    return 0;

    //end the program

}