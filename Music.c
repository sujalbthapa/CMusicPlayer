//header files and libraries
#include <stdio.h>
#include <windows.h>
#include <MMsystem.h>
#include <conio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#include "globvar.h"

//defining
#define refresh_timer 1000
#define true 1
#define clrscr() system("cls")


//extern variables
int ch1, count;
char song[300][300];
char mciCommand[256];


//functions
int audio_list(int);
int display_dir();
int exit_case();
int mid_song_choice(int);
int mid_song_choice_2(int);
int mid_song_val(int, int);
int pause_play();
int playin_count(int);
int stop_sound();


//to get the song choice
int main()
{
    system("color B0");

    do{
        puts("---------------------------------------------------------------------------------------------------------------------");
        puts("\t\t\t\t\t\tMusic Playlist");
        puts("---------------------------------------------------------------------------------------------------------------------");
        count = display_dir();

        puts("---------------------------------------------------------------------------------------------------------------------");
        puts("---------------------------------------------------------------------------------------------------------------------");
        printf("\t\t\t\t\t\tChoose -->  ");
        scanf("%d", &ch1);


        audio_list(ch1);
        clrscr();

    }while(ch1 != count  );

    return 0;

}

//to display the files with wav extension in the directory
int display_dir()
{
    int i = 1;
    char *ptr1, *ptr2;

    DIR *d;
    struct dirent *dir;
    d = opendir(".");

    if (d)
    {
      while ((dir = readdir(d)) != NULL)
      {

        ptr1=strtok(dir->d_name,".");
        ptr2=strtok(NULL,".");
        if(ptr2!=NULL)
        {
            if(strcmp(ptr2,"wav")==0)
            {
                strcpy(song[i],ptr1);
                printf("%d)%s \n", i, ptr1);
                i++;
            }
        }

      }
        printf("%d)Exit \n", i);
        closedir(d);
     }

    return i;

}

//to play the selected song and check for exit
int audio_list(int ch1)
{

    if (ch1 < count)
    {
        clrscr();
        strcat(song[ch1],".wav");

        stop_sound();

        sprintf(mciCommand, "open %s alias CurrSong", song[ch1]);
        mciSendString(mciCommand, NULL, 0, NULL);


        sprintf(mciCommand, "play CurrSong");
        mciSendString(mciCommand, NULL, 0, NULL);

        strtok(song[ch1],".");

        clrscr();

        mid_song_choice(ch1);

        Sleep(refresh_timer);

    }
    else if(ch1 == count)
    {
        exit_case();
        return 0;

    }
    else
    {
        puts("Invalid...");
        Sleep(refresh_timer);
        stop_sound();
    }

    return 0;
}

//top display the song list
int playin_count(int ch1)
{

        if(ch1==count-1)
        {
            puts("---------------------------------------------------------------------------------------------------------------------");
            puts("---------------------------------------------------------------------------------------------------------------------");
            printf("Previous...... %s \n", song[ch1-1]);
            printf("Now Playing... %s \n", song[ch1]);
            puts("---------------------------------------------------------------------------------------------------------------------");

        }
        else if(ch1 == 1)
        {
            puts("---------------------------------------------------------------------------------------------------------------------");
            puts("---------------------------------------------------------------------------------------------------------------------");
            printf("Now Playing... %s \n", song[ch1]);
            printf("Next.......... %s \n", song[ch1+1]);
            puts("---------------------------------------------------------------------------------------------------------------------");
        }
        else
        {
            puts("---------------------------------------------------------------------------------------------------------------------");
            puts("---------------------------------------------------------------------------------------------------------------------");
            printf("Previous...... %s \n", song[ch1-1]);
            printf("Now Playing... %s \n", song[ch1]);
            printf("Next.......... %s \n", song[ch1+1]);
            puts("---------------------------------------------------------------------------------------------------------------------");
        }

    return 0;
}

//to exit the code
int exit_case()
{
    stop_sound();
    clrscr();
    Sleep(500);
    printf("Exiting....");
    Sleep(500);
    exit(0);

    return 0;


}

//for choices during the song is playing
int mid_song_choice(int c1)
{
    playin_count(c1);
    int c12 = c1;
    int n2;
    puts("---------------------------------------------------------------------------------------------------------------------");
    puts("Enter your choice : ");
    puts("\n1)Pause\n2)Next\n3)Previous\n4)Show Playlist\n5)Exit");
    puts("---------------------------------------------------------------------------------------------------------------------");

    puts("---------------------------------------------------------------------------------------------------------------------");
    printf("\t\t\t\t\t\tChoose --> ");
    scanf("%d",&n2);

    mid_song_val(n2, c12);

    return 0;

}

//for choices during the song is paused
int mid_song_choice_2(int c1)
{
    clrscr();
    playin_count(ch1);
    int c12 = c1;
    int n2;

    puts("---------------------------------------------------------------------------------------------------------------------");
    puts("Enter your choice : ");
    puts("\n1)Play\n2)Next\n3)Previous\n4)Show Playlist\n5)Exit\n");
    puts("---------------------------------------------------------------------------------------------------------------------");

    puts("---------------------------------------------------------------------------------------------------------------------");
    printf("\t\t\t\t\t\tChoose -->  ");
    scanf("%d",&n2);

    if(n2==1)
    {
    pause_play();
    }
    else
    {
    mid_song_val(n2, c12);
    }
    clrscr();
    mid_song_choice(c12);
    return 0;

}


//mid song choice solution
int mid_song_val(int n2, int c12)
{
    switch(n2)
    {

    case 1: mciSendString("pause CurrSong", NULL, 0, NULL);

            mid_song_choice_2(c12);
            Sleep(10000);
            break;

    case 2: stop_sound();
            audio_list(c12+1);
            break;

    case 3: stop_sound();
            audio_list(c12-1);
            break;

    case 4: clrscr();
            main();
            break;

    case 5: exit_case();
            break;

    default:puts("Invalid");
            stop_sound();
    }

    return 0;
}

//top stop the sound and close the MCI
int stop_sound()
{

    mciSendString("pause CurrSong", NULL, 0, NULL);

    mciSendString("stop CurrSong", NULL, 0, NULL);

    mciSendString("close CurrSong", NULL, 0, NULL);

    return 0;
}

//to resume the paused sound
int pause_play()
{
    sprintf(mciCommand, "resume CurrSong");
    mciSendString(mciCommand, NULL, 0, NULL);

    return 0;
}
