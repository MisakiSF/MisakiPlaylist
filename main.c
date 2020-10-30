#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//nom du fichier
#define fileName "Musics.txt"
//**********
#define formatLectureEcriture "%d\t%s\t%s\t%s\t%s\n"

typedef struct Music
{
    int id;
    char *Title;
    char *Type;
    char *BandName;
    char *Description;
} Music;

typedef struct MusicElement
{
    Music *Music;
    struct MusicElement *next;
} MusicElement;

/*******************************************************/
Music *createMusic(int, char *,char *,char *,char *);
MusicElement *createMusicElement(Music *);
void addMusicToList(MusicElement **, Music *);
void afficherDetailMusic(Music *);
MusicElement *supprimerElement(MusicElement **, int);
Music *chercherMusic(MusicElement *, int);
void modifierMusic(Music *, int, char *, char *,char *,char *);
void afficherAll(MusicElement *);
void exporte(MusicElement *musics);
void import(MusicElement **musics);

/******************************************************/



char *allouerEspace()
{
    char *String;
    String = (char *)malloc(sizeof(char) * 100);
    scanf("%s", String);
    return String;
}




void menuMusic(MusicElement **L)
{
    MusicElement *ptr;
    int choix, i, id, nvId, c;
    char *nvTitle;
    char *nvType;
    char *nvBandName;
    char *nvDescription;

    printf("\n\n###################### **Manage Your Playist**###################### \n\n");
    printf("*.*.*.*.*.*.*.*.*.*.Made with love by El moudni Safae*.*.*.*.*.*.*.*.\n");


    do
    {
        printf("\n\n.-.-.-.-.-.-.-.- Menu .-.-.-.-.-.-.-.-\n");
        printf(" \n\t1. ADD MUSIC \n");
        printf(" \t2. DISPLAY PLAYLIST \n");
        printf(" \t3. DELETE MUSIC \n");
        printf(" \t4. EDITE MUSIC \n");
        printf(" \t5. FIND MUSIC \n");
        printf(" \t6. EXPORT DATA TO A FILE \n");
        printf(" \t7. IMPORT DATA FROM A FILE \n");
        printf(" \t8. EXIT \n");
        printf(".-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n\n\n");
        printf(" \t Dear User write on a number from the list below please : ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
        {
            system("cls");
            printf("\n################## ADD ##################\n");
            int id;
            char *Title;
            char *Type;
            char *BandName;
            char *Description;
            printf(" Id: ");
            scanf("%d", &id);

            printf(" Title: ");
            Title=allouerEspace();

            printf(" Type: ");
            Type=allouerEspace();

            printf("BandName :");
            BandName=allouerEspace();

            printf("Description : ");
            Description=allouerEspace();



            addMusicToList(L, createMusic(id, Title, Type,BandName,Description));
            break;
        }


        case 2:
        {
            system("cls");
            afficherAll(*L);
            break;
        }
        case 3:
        {
            system("cls");
            printf("\n################## DELETE ##################\n");
            printf(" write the id of the music you want to delete : ");
            scanf("%d", &c);
            supprimerElement(L, c);
            break;
        }
        case 4:
        {
            system("cls");
            printf("\n################## EDITE ##################\n");
            printf(" write the id of the music you want to edite: ");
            scanf("%d", &id);


            printf("nvTitle: ");
            nvTitle = allouerEspace();


            printf("nvType: ");
            nvType=allouerEspace();

            printf("nvBandName: ");
            nvBandName=allouerEspace();

            printf("nvDescription: ");
            nvDescription=allouerEspace();

            ptr = *L;
            while (ptr != NULL)
            {
                if (ptr->Music->id== id)
                    break;
                ptr = ptr->next;
            }
            modifierMusic(ptr->Music, id, nvTitle, nvType,nvBandName,nvDescription);
            break;
        }
        case 5:
        {
            system("cls");
            printf("\n################## FIND ##################\n");
            printf(" write the ID of the music you want to fine!! : ");
            scanf("%d", &c);
            Music *p;
            if ((p = chercherMusic(*L, c)) != NULL)
            {
                printf("Hai!it exists.. sugooy!!:\ncode: %d\nTitle: %s\nType: %s\nBandName: %s\nDescription: %s\n", p->id, p->Title, p->Type,p->BandName,p->Description);
            }
            else
                printf(" no no :( ");
            printf("\n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-n");
            break;
        }

        case 6:
            system("cls");
            exporte(*L);
            break;

        case 7:
             system("cls");
            import(L);
            break;

        case 8:
        {
           system("cls");
            printf(" ##### END #####n");
            break;
        }
        default:
            printf(" choice dsn't match!!!\n");
            break;
        }
    }
    while (choix != 8);

    printf("\n be Calm and Zen Your data is saved even if you forget to export it :P \n");
    exporte(*L);
}



//Creation de Music
Music *createMusic(int id, char *Title, char *Type,char *BandName,char *Description)
{
    Music *newMusic;
    newMusic =(Music *)malloc(sizeof(Music));

    newMusic->id = id;
    newMusic->Title = Title;
    newMusic->Type = Type;
    newMusic->BandName = BandName;
    newMusic->Description = Description;

    return newMusic;
}

//create new element
MusicElement *createMusicElement(Music *Music)
{
    MusicElement *newElement;
    newElement = (MusicElement *)malloc(sizeof(MusicElement));
    newElement->Music = Music;
    newElement->next = NULL;
    return newElement;
}

//Add an element to the list

void addMusicToList(MusicElement **listMusic, Music *Music)
{
    MusicElement *newElement;
//creation de l'elementprintf
    newElement = createMusicElement(Music);
//if empty
    if (*listMusic == NULL)
    {
        *listMusic = newElement;
        return;
    }

    MusicElement *last;
    last = *listMusic;
    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = newElement;

}

//afficher detail d'un Music
void afficherDetailMusic(Music *Music)
{   printf("===========================\n");
    printf("Id:          %d \n", Music->id);
    printf("Title:       %s \n", Music->Title);
    printf("Type:        %s \n", Music->Type);
    printf("BandName:    %s \n", Music->BandName);
    printf("Description: %s \n", Music->Description);
    printf("===========================\n");
}

//delete element
MusicElement *supprimerElement(MusicElement **listMusic, int id)
{
    MusicElement *ptr;
    ptr = *listMusic;

    if ((*listMusic)->Music->id == id)
    {
        (*listMusic) = (*listMusic)->next;
        printf("Delete Done!! \n");
        free(ptr);
        ptr = NULL;

    }
    else
    {
        MusicElement *tmp;
        while (ptr != NULL)
        {
            tmp = ptr;
            ptr = ptr->next;
            if (ptr->Music->id == id)
            {
                tmp->next = ptr->next;
                free(ptr);
                break;
            }
        }
        if (ptr != NULL)
            printf("Delete Done!! \n");
        else
        {
            printf("ID dsn't exist :(  \n");
        }
    }
}

//recherche d'un element
Music *chercherMusic(MusicElement *listMusic, int id)
{
    MusicElement *ptr;
    ptr = listMusic;
    while (listMusic != NULL)
    {
        if (ptr->Music->id == id)
        {
            return ptr->Music;
        }
        listMusic = listMusic->next;
    }
    return NULL;

    printf("Empty List!!");
}

//Modification de Music
void modifierMusic(Music *Music, int nvId, char *nvTitle, char *nvType,char *nvBandName,char *nvDescription)
{
    strcpy(Music->Title, nvTitle);

    strcpy(Music->Type, nvType);

    strcpy(Music->BandName, nvBandName);

    strcpy(Music->Description, nvDescription);
    printf("\n Edite Done!!!");
}

//display all elementList
void afficherAll(MusicElement *listMusic)
{
    MusicElement *ptr;
    ptr = listMusic;
    for (ptr = listMusic; ptr != NULL; ptr = ptr->next)
    {
        afficherDetailMusic(ptr->Music);
    }
}

//Enregister les donnees
void enregister(MusicElement*listMusic,FILE*pf_out)
{

    // pf_out // write

    MusicElement*ptr;
    ptr=listMusic;
    while(ptr!=NULL)
    {
        fprintf(pf_out,"%d\t%s\t%s\t%s\t%s\n",ptr->Music->id,ptr->Music->Title,ptr->Music->Type,ptr->Music->BandName,ptr->Music->Description);
        ptr=ptr->next;
    }
}
/**************main******************/
int main(int argc, char const *argv[])
{
    MusicElement *Musics = NULL;
    menuMusic(&Musics);
    return 0;
}
/**************EndOfmain******************/
void exporte(MusicElement *Musics)
{
    FILE *file = fopen(fileName, "w");

    if (!file)
    {
        printf("file is nulll!!!\n");
        return;
    }

    while (Musics)
    {
        fprintf(file, formatLectureEcriture, (Musics->Music->id), (Musics->Music->Title), (Musics->Music->Type),(Musics->Music->BandName),(Musics->Music->Description));
        Musics = Musics->next;
    }
    fclose(file);
}

void import(MusicElement **Musics)
{
    FILE *file = fopen(fileName, "r");
    if (!file)
    {
        printf("file is null!!!\n");
        return;
    }

    MusicElement *row = NULL;
    *Musics = NULL;
    MusicElement *tmp = NULL;

    int id;
    char *Title=(char*) malloc(100*sizeof(char));
    char *Type=(char*) malloc(100*sizeof(char));
    char *BandName=(char*) malloc(100*sizeof(char));
    char *Description=(char*) malloc(100*sizeof(char));

    while (fscanf(file, formatLectureEcriture, &id, Title, Type,BandName,Description) != EOF)
    {
            row = createMusicElement(createMusic(id,Title,Type,BandName,Description));

        if (*Musics == NULL)
        {
        // first element
            *Musics=row;
            tmp = *Musics;
        }
        else
        {
            tmp->next = row ;
            tmp = tmp->next;
            // insert in Last
        }

        // renouvelement de memoire

        Title=(char*) malloc(100*sizeof(char));
        Type=(char*) malloc(100*sizeof(char));
        BandName=(char*) malloc(100*sizeof(char));
        Description=(char*) malloc(100*sizeof(char));
    }
}
