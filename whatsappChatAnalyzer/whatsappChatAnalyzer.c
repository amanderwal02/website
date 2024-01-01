#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "chat.txt"
#define FILENAME1 "wholeChat.txt"
#define FILENAME2 "onlyMessage.txt"
#define FILENAME3 "dateChat.txt"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define DEFAULT "\x1b[0m"

void welcome(){

    printf( RED "\nWHATSAPP CHAT ANALYZER\n\n" DEFAULT );

}

void choiceRule(){

    printf("Available Choices : ");
    printf( GREEN "1 --> Print Whole Chat\n" );
    printf("                    2 --> Find Chatter's Name \n");
    printf("                    3 --> Count Particular Word \n");
    printf("                    4 --> Print Messages of Particular Date\n");
    printf("                    5 --> Print Messages by Particular User\n");
    printf("                    6 --> Count Messages by Particular User\n");
    printf("                    7 --> Exit the Program\n\n" DEFAULT );

}

void wholeChatTxt(){

    FILE *fp = fopen( FILENAME1 , "w" );

    if ( fp == NULL ){

        printf( RED "   ❌ ERROR : FILE NOT CREATING\n\n" DEFAULT );
        exit(EXIT_FAILURE);

    } else {

        char word[100];
        char ch;

        FILE *file = fopen ( FILENAME , "r" );

        if ( file == NULL ){

            printf( RED "   ❌ ERROR : FILE NOT FOUND\n\n");
            exit(EXIT_FAILURE);

        } else {

            while ( (fscanf( file , "%*s %*s %*s" , word )) == 0 ){

                while( (ch = fgetc(file)) != '\n' ){

                    fprintf( fp , "%c" , ch );

                }

                fputc( '\n' , fp );

            }

        }

        fclose( file );

    }

    fclose( fp );

}

void printWholeChat(){

    wholeChatTxt();

    FILE *file = fopen( FILENAME1 , "r" );

    if ( file == NULL ){

        printf( RED "   ❌ ERROR : FILE NOT FOUND\n\n" DEFAULT );
        exit(EXIT_FAILURE);

    } else {

        char word[100];
        char ch;

        printf("    ");

        while( (ch = fgetc(file)) != EOF ){

            putchar(ch);

        }

        printf("\n");

    }

    printf("\n");
    fclose( file );

}

void findChatters( int x , int y , char name[x][y] ){

    FILE *fp = fopen( FILENAME1 , "r" );

    if ( fp == NULL ){

        printf( RED "   ❌ ERROR : FILE NOT FOUND\n\n" DEFAULT );
        exit(EXIT_FAILURE);

    } else {

        char ch , ch2;
    
        for( int i = 0 ; i < x ; i++ ){

            while( (ch = fgetc(fp)) != '\n' ){

            }

            if (i == 1){

                ch2 = fgetc(fp);
                int p = fscanf( fp , "%[^:]" , name[i] ) == 1;

                while( strcmp( name[i-1] , name[i] ) == 0 ){

                    while( (ch = fgetc(fp)) != '\n' ){

                    }

                    ch2 = fgetc(fp);
                    p = fscanf( fp , "%[^:]" , name[i] ) == 1;
                    
                }

            } else {

                ch2 = fgetc(fp);
                int p = fscanf( fp , "%[^:]" , name[i] ) == 1;
                
            }

        } 

    }

    fclose(fp);

}

void onlyMessage(){

    FILE *file = fopen( FILENAME1 , "r" );

    if ( file == NULL ){

        printf( RED "   ❌ ERROR : FILE NOT FOUND\n\n" DEFAULT );
        exit(EXIT_FAILURE);

    } else {

        char word[100];
        char ch;

        FILE *fp = fopen( FILENAME2 , "w" );

            if ( fp == NULL ){

                printf( RED "   ❌ ERROR : FILE NOT CREATING\n\n" DEFAULT );
                exit(EXIT_FAILURE);

            } else {

                while( fscanf( file , "%*[^:]" , word ) == 0 ){

                    ch = fgetc(file);

                    while( (ch = fgetc(file)) != '\n' ){

                        fputc( ch , fp );

                    }

                    fputc('\n' , fp);

                }

            }

        fclose(fp);

    }

    fclose(file);

}

void overallWordCount(){

    char word[100];
    int n = 0;

    printf("        Enter the word (in small letters) : ");
    scanf("%s" , word );

    FILE *fp = fopen( FILENAME2 , "r" );

    if ( fp == NULL ){

        printf( RED "\n       ❌ ERROR : FILE NOT FOUND\n\n" DEFAULT );
        exit(EXIT_FAILURE);

    } else {

        char ch;
        char word2[100];

        while( (fscanf( fp , "%s" , word2 )) == 1 ){

            for( int i = 0 ; word2[i] != '\0' ; i++ ){

                if ( word2[i] >= 65 && word2[i] <= 90 ){

                    word2[i] += 32;

                }

            }
            
            if ( strcmp( word , word2 ) == 0 ){

                n++;

            }

        }
        
    }

    fclose( fp );

    printf("\n        No. of words '%s' used in chats : %d\n\n" , word , n );

}

void perUserWordCount( int x , int y , char name[x][y] ){
    
    FILE *fp = fopen( FILENAME1 , "r" );

    char word3[100];

    printf("        Enter the word (in small letters) : ");
    scanf("%s" , word3 );

    if( fp == NULL ){

        printf( RED "\n       ❌ ERROR : FILE NOT FOUND\n\n" DEFAULT );
        exit(EXIT_FAILURE);

    } else {
        
        int n1 = 0 , n2 = 0;
        char word[100];
        char word2[100];
        char ch , ch2 , ch3;

        while( (ch = fgetc(fp)) != '\n' ){

        }

        for( int i = 0 ; (ch = fgetc(fp)) != EOF ; i++){
            
            int p = fscanf( fp , "%[^:]" , word ) == 1;
            
            if( strcmp(word , name[0]) == 0 ){

                ch2 = fgetc(fp);

                while ( fscanf( fp , "%s" , word2 ) == 1 ){
                    
                    for( int i = 0 ; word2[i] != '\0' ; i++ ){

                        if ( word2[i] >= 65 && word2[i] <= 90 ){

                            word2[i] += 32;

                        }

                    }
                    
                    if ( strcmp( word3 , word2 ) == 0 ){

                        n1++;

                    }

                    ch3 = fgetc(fp);
                    if( ch3 == '\n' ){

                        break;

                    }
                
                }

            } else if( strcmp( word , name[1] ) == 0 ){

                ch2 = fgetc(fp);
                while ( fscanf( fp , "%s" , word2 ) == 1 ){
                    
                    for( int i = 0 ; word2[i] != '\0' ; i++ ){

                        if ( word2[i] >= 65 && word2[i] <= 90 ){

                            word2[i] += 32;

                        }

                    }
                    
                    if ( strcmp( word3 , word2 ) == 0 ){

                        n2++;

                    }

                    ch3 = fgetc(fp);
                    if( ch3 == '\n' ){

                        break;

                    }
                
                }


            }
        
        }

        printf("\n        No. of word '%s' used by '%s' : %d\n\n" , word3 , name[0] , n1 );
        printf("\n        No. of word '%s' used by '%s' : %d\n\n" , word3 , name[1] , n2 );
        
    }

}

void wordCount( int x , int y , char name[x][y] ){
    
    onlyMessage();
    printf("    Available Options : ");
    printf( GREEN "1 --> Overall Word Count\n");
    printf("                        2 --> Particular User Word Count\n");
    printf("                        3 --> Exit the Word Count Option\n\n" DEFAULT );

    int choice;

    OPTION : {

        printf("    🔸 Enter the option : ");
        scanf("%d" , &choice );

    }

    switch( choice ){

        case 1 : {

            printf( YELLOW "\n    🔹 CHOICE : OVERALL WORD COUNT\n\n" DEFAULT );
            overallWordCount();
            goto OPTION;

        }

        case 2 : {

            printf( YELLOW "\n    🔹 CHOICE : PARTICULAR USER WORD COUNT\n\n" DEFAULT );
            perUserWordCount( x , y , name );
            goto OPTION;

        }

        case 3 : {

            printf( YELLOW "\n    🔹 Exiting.........\n\n" DEFAULT );
            break;

        }

        default : {

            printf( RED "\n    ❌ ERROR : GIVE CORRECT INPUT\n\n" DEFAULT );
            goto OPTION;

        }

    }

}

void dateChatOnly(){

    FILE *file = fopen( FILENAME , "r" );

    if (file == NULL){

        printf( RED "\n       ❌ ERROR : FILE NOT FOUND\n\n" DEFAULT );
        exit(EXIT_FAILURE);

    } else {

        char word[100];
        char ch;

        FILE *fp = fopen( FILENAME3 , "w" );

        if( fp == NULL ){

            printf( RED "\n       ❌ ERROR : FILE NOT CREATING\n\n" DEFAULT );
            exit(EXIT_FAILURE);

        } else {

            while( fscanf( file , "%[^,]" , word ) == 1 ){

                fprintf( fp , "%s" , word );
                while( fscanf( file , "%*s %*s %*s" , word ) == 0 ){

                    while( (ch = fgetc(file)) != '\n' ){
                        
                        fputc( ch , fp );

                    }

                    fputc( '\n' , fp );

                    if( ch == '\n'){

                        break;

                    }

                }

            }

        }

        fclose(fp);

    }

    fclose(file);

}

void dateChat(){

    dateChatOnly();
    char date[100];
    printf("    Enter the date (in this format : dd/mm/yy) : ");
    scanf("%s", date);

    FILE *fp = fopen( FILENAME3 , "r" );

    if( fp == NULL ){

        printf( RED "\n       ❌ ERROR : FILE NOT FOUND\n\n" DEFAULT );
        exit(EXIT_FAILURE);

    } else {

        char word[100];
        char ch;
        printf("\n");
        while( fscanf( fp , "%s" , word ) == 1 ){
            
            printf("    ");
            if( strcmp( word , date ) == 0 ){
                
                ch = fgetc(fp);
                while( (ch = fgetc(fp)) != '\n' ){

                    putchar(ch);

                }

                printf("\n");

            }

        }

        printf("\n");

    }

    fclose(fp);

}

void perUserChat( char name[] ){

    //printf("hiiii %s\n", name);
    FILE *fp = fopen( FILENAME1 , "r" );

    if ( fp == NULL ){

        printf( RED "       ❌ ERROR : FILE NOT FOUND\n\n" DEFAULT );
        exit(EXIT_FAILURE);

    } else {

        char word[100];
        char ch;
        //printf("hiiii %s\n", name);
        while( (ch = fgetc(fp)) != '\n' ){

        }

        int i = 1;
        while( (ch = fgetc(fp)) != EOF ){
    
            int p = fscanf( fp , "%[^:]" , word ) == 1;
            
            if( strcmp( word , name ) == 0 ){

                ch = fgetc(fp);
                printf("        %d)",i);
                while( (ch = fgetc(fp)) != '\n' ){

                    putchar(ch);

                }

                printf("\n");
                i++;

            } else {

                while( (ch = fgetc(fp)) != '\n' ){

                }

            }

        }

    }

    printf("\n");
    fclose(fp);

}

void perUser( int x , int y , char name[x][y] ){

    int n;

    OPTION : {

        printf("    Available Options : ");
        printf( GREEN "1 --> Messages of %s\n", name[0] );
        printf("                        2 --> Messages of %s\n", name[1] );
        printf("                        3 --> Exit the Per User Message Option\n\n" DEFAULT );

        printf("    Enter the option : ");
        scanf("%d", &n);
        printf("\n");

    }

    switch( n ){

        case 1 : {
            
            printf( YELLOW "    🔹 CHOICE : MESSAGES OF %s\n\n" , name[0] );
            printf( DEFAULT);
            perUserChat( name[0] );
            goto OPTION;

        }

        case 2 : {

            printf( YELLOW "    🔹 CHOICE : MESSAGES OF %s\n\n" , name[1] );
            printf(DEFAULT);
            perUserChat( name[1] );
            goto OPTION;

        }

        case 3 : {

            printf( YELLOW "    🔹 Exiting..........\n\n" DEFAULT );
            break;

        }

        default : {

            printf( YELLOW "    🔹 INVALID INPUT !!\n\n" DEFAULT );
            goto OPTION;

        }

    }

}

void perUserCount( int x , int y , char name[x][y] ){

    FILE *fp = fopen( FILENAME1 , "r" );

    int i = 0;
    int w = 0;

    if ( fp == NULL ){

        printf( RED "       ❌ ERROR : FILE NOT FOUND\n\n" DEFAULT );
        exit(EXIT_FAILURE);

    } else {

        char word[100];
        char ch;
        
        while( (ch = fgetc(fp)) != '\n' ){

        }

        while( (ch = fgetc(fp)) != EOF ){
    
            int p = fscanf( fp , "%[^:]" , word ) == 1;
            
            if( strcmp( word , name[0] ) == 0 ){

                ch = fgetc(fp);
                
                while( (ch = fgetc(fp)) != '\n' ){

                }

                i++;

            } else if( strcmp( word , name[1] ) == 0 ){

                ch = fgetc(fp);
                
                while( (ch = fgetc(fp)) != '\n' ){

                }

                w++;

            }

        }

    }

    printf("        No. of messages of %s : %d\n", name[0] , i );
    printf("        No. of messages of %s : %d\n\n", name[1] , w );
    fclose(fp);

}

int main(){
    
    welcome();

    int choice;
    CHOICE :
    {
        choiceRule();
        printf("🟡 Enter the choice : ");
        scanf("%d" , &choice );
    }

    int n;
    char name[2][50];

    switch( choice ){

        case 1 : {

            printf( YELLOW "\n🟢 CHOICE : PRINT WHOLE CHAT\n\n" DEFAULT );
            printWholeChat();
            goto CHOICE;

        }

        case 2 : {

            printf( YELLOW "\n🟢 CHOICE : PRINT CHATTERS NAME\n\n" DEFAULT );
            findChatters( 2 , 50 , name );
            printf( BLUE "\n    Chatter's are : " DEFAULT );
            printf( GREEN "1)%s\n" , name[0] );
            printf("                    2)%s\n\n" DEFAULT , name[1] );
            goto CHOICE;

        }

        case 3 : {

            printf( YELLOW "\n🟢 CHOICE : COUNT PARTICULAR WORD\n\n" DEFAULT );
            findChatters( 2 , 50 , name );
            wordCount( 2 , 50 , name );
            goto CHOICE;

        }

        case 4 : {

            printf( YELLOW "\n🟢 CHOICE : PRINT MESSAGES BY DATE\n\n" DEFAULT );
            dateChat();
            goto CHOICE;

        }

        case 5 : {

            printf( YELLOW "\n🟢 CHOICE : PRINT MESSAGES BY PARTICULAR USER\n\n" DEFAULT );
            findChatters( 2 , 50 , name );
            perUser( 2 , 50 , name );
            goto CHOICE;

        }

        case 6 : {

            printf( YELLOW "\n🟢 CHOICE : COUNT MESSAGES BY PARTICULAR USER\n\n" DEFAULT );
            findChatters( 2 , 50 , name );
            perUserCount( 2 , 50 , name );
            goto CHOICE;

        }

        case 7 : {

            printf( YELLOW "\n🟢 Exiting the program...........\n\n" DEFAULT );
            break;

        }

        default : {

            printf( YELLOW "\n🟢 INVALID INPUT !!\n\n" DEFAULT );
            goto CHOICE;

        }

    }

    return 0;

}