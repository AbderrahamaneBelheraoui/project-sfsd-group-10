#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct {
    char Module[20];
    float note;
    int coefficent;
} Studentnote;

typedef struct {
    int ID;
    char name[20];
    char familyname[20];
    int birthdate;
    char group[2];
    Studentnote notes[4];
    float avrege;
    int Delete;
} Student;

int Menu();
int Menu2();
int Menu3();
void Pickstudent(char *line, Student *student);
void Pickstudent2(char *line, Student *student);
void Printclass(FILE *file);
void Printffile(FILE *file);
void Searchstudent(FILE *file);
int  Checkstudent(FILE *file,int ID);
void Logicdelete(FILE *file,char *filename,int ID);
void physic1delete(FILE *file,char *filename,int ID);
void addfirst(FILE *file,char *filename,Student student);
void physicdeleteall(FILE *file,char *filename);
void Addstudent(FILE *file,char *filename);
void Modefiestudent(FILE *file,char *filename);


int main()
{
    int i=0,ID;
    char filename[20];
    printf("\033[1;32m\033[40m");
    printf("Enter your file name: ");
    scanf("%s", filename);

    do {

        FILE *file = NULL;
        file = fopen(filename, "r+");

        if (file == NULL)
        {
            printf("Error opening file.\n");
            return 1;
        }

        switch (Menu()) {
        case 1:
            Addstudent(file,filename);
            break;
        case 2:
            Searchstudent(file);
            break;
        case 3:
            Modefiestudent(file,filename);
            break;
        case 4:
            printf("\nEnter the ID of the student to delete logically:");
            scanf("%d",&ID);
            Logicdelete(file,filename,ID);
             printf("\nStudent logically deleted.");
            break;
        case 5:
            Printclass(file);
            break;
        case 6:
            physicdeleteall(file,filename);
            break;
        case 7:
            Printffile(file);
            break;
        case 8:
            printf("Exiting...\n");
            i = 1;
            break;
        }

        fclose(file);
    } while (i == 0);

    return 0;
}

int Menu() {

    int choice=0;
    while (choice<1 || choice>8)
    {
        printf("\nMENU: \n");
        printf("1 : Add student.\n");
        printf("2 : Search for student.\n");
        printf("3 : Modifie student information.\n");
        printf("4 : Delete a student logically.\n");
        printf("5 : Print a class from the highest avrage.\n");
        printf("6 : Delete non active students phisiclly.\n");
        printf("7 : Print all students with informations in the file.\n");
        printf("8 : Done editing.\n");
        printf("Your Choice: ");
        scanf("%d", &choice);
        printf("\033[H\033[J");  // terminal command "clear screen"
    }
    return choice;
}

int Menu2(){

    int choice=0;
    while (choice<1 || choice>6)
    {
        printf("\nMENU 2:\n");
        printf("1 : modefie name.\n");
        printf("2 : modefie family name.\n");
        printf("3 : modifie birth date.\n");
        printf("4 : modefie class.\n");
        printf("5 : modefie note.\n");
        printf("6 : Exit.\n");
        printf("Your Choice: ");
        scanf("%d", &choice);
    }
    return choice;
}

int Menu3(){

    int choice=0;
    while (choice<1 || choice>5)
    {
        printf("\nMENU 3: \n");
        printf("1 : SFSD note.\n");
        printf("2 : POO note.\n");
        printf("3 : ANALYSIS note.\n");
        printf("4 : ALGEBRA note.\n");
        printf("5 : Exit.\n");
        printf("Your Choice: ");
        scanf("%d", &choice);
    }
    return choice;
}

void Pickstudent(char *line, Student *student) {

    float notes[4];
    int i,coefficients[4];
    char *space,fullname[20],modules[4][20]={"SFSD","POO","ANALYSIS","ALGEBRA"};

    sscanf(line,"%d;%39[^;];%d;%2[^;];%f,%d;%f,%d;%f,%d;%f,%d;%f;%d",
           &student->ID,
           fullname,
           &student->birthdate,
           student->group,
            &notes[0], &coefficients[0],
            &notes[1], &coefficients[1],
            &notes[2], &coefficients[2],
            &notes[3], &coefficients[3],
           &student->avrege,
           &student->Delete);

           space=strchr(fullname,' ');
           *space='\0';
           strcpy(student->familyname,fullname);
           strcpy(student->name,space+1);


    for(i=0;i<4;i++)
    {
        strcpy(student->notes[i].Module, modules[i]);
        student->notes[i].note = notes[i];
        student->notes[i].coefficent = coefficients[i];
    }
}

void Pickstudent2(char *line, Student *student) {
    int i;
    char *piece,*space,tempName[40];
    char modules[4][20]={"SFSD","POO","ANALYSIS","ALGEBRA"};

    piece = strtok(line,";");
    student->ID = atoi(piece);

    piece = strtok(NULL,";");
    strcpy(tempName,piece);

    space = strchr(tempName,' ');
    *space = '\0';
    strcpy(student->familyname,tempName);
    strcpy(student->name,space+1);

    piece = strtok(NULL, ";");
    student->birthdate = atoi(piece);

    piece = strtok(NULL, ";");
    strcpy(student->group, piece);

    for(i=0;i<4;i++)
    {
        strcpy(student->notes[i].Module, modules[i]);

        piece = strtok(NULL,",");
        student->notes[i].note = atof(piece);

        piece = strtok(NULL,";");
        student->notes[i].coefficent = atoi(piece);
    }

    piece = strtok(NULL,";");
    student->avrege = atof(piece);

    piece = strtok(NULL,";");
    student->Delete = atoi(piece);
}

void Printffile(FILE *file) {
    int i=1,j;
    char line[MAX];


    fseek(file,0,SEEK_SET);
    printf("ALL STUDENTS INFORMATION:\n");

    while(fgets(line,MAX,file) != NULL)
    {
        Student student;
        Pickstudent(line, &student);
        if (student.Delete == 0)
        {
            printf("\nSTUDENT %d:\n",i);
            printf("ID: %d\n",student.ID);
            printf("Name: %s\n",student.name);
            printf("Family Name: %s\n",student.familyname);
            printf("Birthdate: %d\n",student.birthdate);
            printf("Group: %s\n", student.group);
            printf("Average: %.2f\n",student.avrege);
            printf("Notes:\n");

            for(j=0;j<4;j++)
            {
                printf("\tModule %d: %s\n",j + 1,student.notes[j].Module);
                printf("\tNote: %.2f\n",student.notes[j].note);
                printf("\tCoefficient: %d\n",student.notes[j].coefficent);
            }
            i++;
        }
    }
}

void Searchstudent(FILE *file) {
    int j,ID;
    char line[MAX];
    Student student;
    fseek(file,0,SEEK_SET);

    printf("Enter the student ID number: ");
    scanf("%d",&ID);

    while(fgets(line,MAX,file) != NULL)
    {
        Pickstudent(line,&student);
        if( student.ID == ID )
        {
            if( student.Delete == 1 )
            {
                printf("\nStudent is logiclly deleted !.");
                printf("\nDo you want show student informations:");
                do { printf("\n1: Yes.\n2: No.\nchoice: "); scanf("%d",&j); } while(j<1 || j>2);
                if(j==2){ return; }
            }

            printf("\nTHE STUDENT WITH THE ID (%d) INFORMATION:\n",ID);
            printf("ID: %d\n",student.ID);
            printf("Name: %s\n",student.name);
            printf("Familly Name: %s\n",student.familyname);
            printf("Birthdate: %d\n",student.birthdate);
            printf("Group: %s\n",student.group);
            printf("Average: %.2f\n",student.avrege);
            printf("Notes:\n");

            for(j=0;j<4;j++)
            {
                printf("\tModule %d: %s\n",j + 1,student.notes[j].Module);
                printf("\tNote: %.2f\n",student.notes[j].note);
                printf("\tCoefficient: %d\n",student.notes[j].coefficent);
            }
            return;
        }
    }
    printf("\nStudent doesn't exist.\n");
}

int  Checkstudent(FILE *file,int ID) {
    int exist = 0;
    char line[MAX];
    Student student;
    fseek(file,0,SEEK_SET);

    while (fgets(line,MAX,file) != NULL)
    {
        Pickstudent(line, &student);
        if (ID == student.ID && student.Delete == 0)
        {
            return 1;
        }
    }

    return 0;
}

void Logicdelete(FILE *file,char *filename,int ID){
    int i;
    char line[MAX];
    Student student;

    FILE *file2 = fopen("temp.txt","w+");

    if(file2 == NULL)
    {
        printf("Error opening the temporary file.\n");
        return ;
    }

    fseek(file,0,SEEK_SET);

    while (fgets(line,MAX,file) != NULL)
    {
        Pickstudent(line,&student);

        if(student.ID == ID && student.Delete == 0)
        {
            student.Delete = 1;
        }

        fprintf(file2,"%d;%s %s",student.ID,student.name,student.familyname);
        fprintf(file2, ";%d;%s", student.birthdate, student.group);

        for(i=0;i<4;i++)
        {
            fprintf(file2,";%.2f,%d", student.notes[i].note, student.notes[i].coefficent);
        }
        fprintf(file2,";%.2f;%d\n",student.avrege,student.Delete);
    }

    fclose(file);
    fclose(file2);
    remove(filename);
    rename("temp.txt",filename);
    file = fopen(filename,"r+");

}

void physic1delete(FILE *file,char *filename,int ID){
    int i;
    char line[MAX];
    Student student;

    FILE *file2 = fopen("temp.txt","w+");

    if(file2 == NULL)
    {
        printf("Error opening the temporary file.\n");
        return ;
    }

    fseek(file,0,SEEK_SET);

    while (fgets(line,MAX,file) != NULL)
    {
        Pickstudent(line,&student);
        if(student.ID != ID && student.Delete != 1)
        {
            fprintf(file2,"%d;%s %s",student.ID,student.name,student.familyname);
            fprintf(file2, ";%d;%s", student.birthdate, student.group);

            for(i=0;i<4;i++)
            {
            fprintf(file2,";%.2f,%d", student.notes[i].note, student.notes[i].coefficent);
            }
            fprintf(file2,";%.2f;%d\n",student.avrege,student.Delete);
        }
    }

    fclose(file);
    fclose(file2);

    remove(filename);
    rename("temp.txt",filename);
    file = fopen(filename,"r+");
}

void physicdeleteall(FILE *file,char *filename){
    int i;
    char line[MAX];
    Student student;

    FILE *file2 = fopen("temp.txt","w+");

    if(file2 == NULL)
    {
        printf("Error opening the temporary file.\n");
        return ;
    }

    fseek(file,0,SEEK_SET);

    while (fgets(line,MAX,file) != NULL)
    {
        Pickstudent(line,&student);
        if(student.Delete == 0)
        {
            fprintf(file2,"%d;%s %s",student.ID,student.name,student.familyname);
            fprintf(file2, ";%d;%s", student.birthdate, student.group);

            for(i=0;i<4;i++)
            {
            fprintf(file2,";%.2f,%d", student.notes[i].note, student.notes[i].coefficent);
            }
            fprintf(file2,";%.2f;%d\n",student.avrege,student.Delete);
        }
    }

    fclose(file);
    fclose(file2);

    remove(filename);
    rename("temp.txt",filename);

    printf("Students non actif has been deleted.\n");
}

void addfirst(FILE *file,char *filename,Student student){
    int i;
    char line[MAX];

    FILE *file2 = fopen("temp.txt","w+");

    if(file2 == NULL)
    {
        printf("Error opening the temporary file.\n");
        return;
    }

    fseek(file,0,SEEK_SET);
    fprintf(file2,"%d;%s %s",student.ID,student.name,student.familyname);
    fprintf(file2, ";%d;%s",student.birthdate, student.group);
    for(i=0;i<4;i++)
    {
        fprintf(file2,";%.2f,%d", student.notes[i].note, student.notes[i].coefficent);
    }
    fprintf(file2,";%.2f;%d\n",student.avrege,student.Delete);

    while (fgets(line,MAX,file) != NULL)
    {
        fputs(line,file2);
    }

    fclose(file);
    fclose(file2);
    remove(filename);
    rename("temp.txt",filename);
    file = fopen(filename,"r+");
}

void Addstudent(FILE *file,char *filename) {
    int i,keep=0;
    Student student;

    printf("Enter student information (ID): \n");

    printf("ID: ");
    scanf("%d",&student.ID);

    if(Checkstudent(file,student.ID)==1)
    {
        printf("Student with ID %d already exists.\n",student.ID);

        do {
            printf("\n0 : keep the old student, enter 0.");
            printf("\n1 : delete the old student logically and add the new one.");
            printf("\n2 : delete the old student physically and add the new one.");
            scanf("%d",&keep);
        } while (keep < 0 && keep > 2);

        if(keep > 0)
        {
            if(keep == 1)
            {
                Logicdelete(file,filename,student.ID);
                printf("Old student marked as deleted logically.\n");
            }
            else
            {
                physic1delete(file,filename,student.ID);
                printf("Old student marked as deleted physically.\n");
            }

        }
        else
        {
            printf("Keeping the old student.\n");
            return;
        }
    }

    printf("Name: ");
    scanf("%s", student.name);
    printf("Family Name: ");
    scanf("%s", student.familyname);

    do {
        printf("Birthdate (1990-2020): ");
        scanf("%d",&student.birthdate);
    } while (student.birthdate < 1990 || student.birthdate > 2020);

    printf("Group: ");
    scanf("%s", student.group);

    char modules[4][20]={"SFSD", "POO", "ANALYSIS", "ALGEBRE"};
    int count=0,coefficients[4]={4, 3, 2, 5};
    float avrg=0;

    for(i=0;i<4;i++)
    {
        strcpy(student.notes[i].Module, modules[i]);
        student.notes[i].coefficent = coefficients[i];

        do {
            printf("Note for module %s (between 0 and 20): ", student.notes[i].Module);
            scanf("%f",&student.notes[i].note);
        } while (student.notes[i].note < 0 || student.notes[i].note > 20);

        count = count + coefficients[i];
        avrg = avrg + student.notes[i].note * coefficients[i];
    }

    student.avrege = avrg / count;
    student.Delete = 0;

    addfirst(file,filename,student);
    printf("Student added successfully.\n");
}

void Printclass(FILE *file){

    int ID[20],i=0,j,k,itemp;
    char line[MAX],group[3];
    float avrg[20],ftemp;

    printf("\nEnter the class name: ");
    scanf("%s",group);

    Student student;
    fseek(file,0,SEEK_SET);

    while (fgets(line,MAX,file) != NULL)
    {
        Pickstudent(line,&student);
        if(strcmp(student.group,group) == 0 && student.Delete == 0)
        {
            ID[i] = student.ID;
            avrg[i] = student.avrege;
            i++;
        }
    }
    if(i==0){ printf("\n No student in the file is from the class: %s.\n",group); }
    else
    {
        for(j=0;j<i;j++)
        {
            for(k=j+1;k<i+1;k++)
            {
                if( avrg[j]<avrg[k] )
                {
                    ftemp = avrg[j];   itemp = ID[j];
                    avrg[j] = avrg[k]; ID[j] = ID[k];
                    avrg[k] = ftemp;   ID[k] = itemp;

                }
            }
        }

        printf("\nThe class %s students classment:\n",group);
        for(j=0;j<i;j++)
        {
            fseek(file,0,SEEK_SET);
            while (fgets(line,MAX,file) != NULL)
            {
                Pickstudent(line,&student);
                if(student.Delete == 0 && student.ID == ID[j])
                {
                    printf("Student %d : %s ,%s ,ID : %d.\n",j+1,student.name,student.familyname,student.ID);
                    break;
                }
            }
        }
    }


}

void Modefiestudent(FILE *file,char *filename){
    char line[MAX];
    float avrg=0;
    Student student;
    int i=0,ID, Restore=0, count=0;


    printf("\nEnter student ID: ");
    scanf("%d", &ID);

    if( Checkstudent(file,ID)==1 ){ Restore=1; }

    fseek(file, 0, SEEK_SET);
    while(fgets(line, MAX, file) != NULL)
    {
        Pickstudent(line, &student);
        if(student.ID == ID)
        {
            if(student.Delete == 1 && Restore == 0 )
            {
                printf("\nThis student is logically deleted.");
                printf("\n0 : Cancel modification");
                printf("\n1 : Restore student and modefie.");
                printf("\nYour choice:"); scanf("%d", &Restore);
                if(Restore == 0) { return; }
            }
            if(student.Delete == 0 || Restore != 0)
            {
                physic1delete(file,filename,ID);
                student.Delete = 0;
                do{
                switch(Menu2())
                {
                    case 1:
                        printf("\nThe new student name: "); scanf("%s",student.name);
                        break;
                    case 2:
                        printf("\nThe new student family name: "); scanf("%s",student.familyname);
                        break;
                    case 3:
                        do{ printf("\nThe new student birth date"); scanf("%d",&student.birthdate); }
                        while(student.birthdate>2020 || student.birthdate<1990);
                        break;
                    case 4:
                        printf("\nThe new student class: "); scanf("%s",student.group);
                        break;
                    case 5:
                        switch(Menu3())
                        {
                            case 1:
                                 do{ printf("\nThe new student SFSD note: "); scanf("%f",&student.notes[0].note); }
                                 while(student.notes[0].note<0 || student.notes[0].note>20);
                                break;
                            case 2:
                                do{ printf("\nThe new student POO note: "); scanf("%f",&student.notes[1].note); }
                                while(student.notes[1].note<0 || student.notes[1].note>20);
                                break;
                            case 3:
                                do{ printf("\nThe news tudent ANALYSIS note: "); scanf("%f",&student.notes[2].note); }
                                while(student.notes[2].note<0 || student.notes[2].note>20);
                                break;
                            case 4:
                                do{ printf("\nThe new student ALGEBRA note: "); scanf("%f",&student.notes[3].note); }
                                while(student.notes[3].note<0 || student.notes[3].note>20);
                                break;
                        }
                        break;
                    case 6:
                        printf("Exiting..."); i=1;
                        break;
                }
                }while(i==0);

                for(i=0;i<4;i++)
                {
                    count = count + student.notes[i].coefficent;
                    avrg = avrg + student.notes[i].note * student.notes[i].coefficent;
                }
                student.avrege = avrg / count;

                addfirst(file,filename,student);
                printf("\nThe student %s %s (%d) has been modefied.\n",student.name,student.familyname,student.ID);
                return;
            }
        }
    }
    printf("This student (ID : %d) doesnt exist.",student.ID);
}
