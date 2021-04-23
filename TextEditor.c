#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    FILE *fp, *temp_fp;
    char character, save_choice, exit_confirmation, open_choice, overwrite_choice;
    char Entered_filename[24];
    char file_extension[] = ".txt";

    const char *defaultfilename = "INPUT.txt";
    fp = fopen(defaultfilename, "w+");
    if (fp == NULL)
    {
        puts("Unable to open file editor");
        exit(1);
    }
    printf("\n\n##################################################################\n");
    printf("\t\tWelcome to Text editor:\n");
    printf("--------------------------------------------------------------------\n\n");
    printf("Note: To terminate the file press \"ctrl + z\" then press enter\n");
    printf("--------------------------------------------------------------------\n\n");

    while ((character = getchar()) != EOF)
    {
        fprintf(fp, "%c", character);
    }
    fclose(fp);

    // printf("\nWould you want to save the file?\nEnter any key to save\nOr Enter \"n\" to exit without saving. : ");
    printf("\n\nPress Enter to save.. [To Exit press any key] : ");
    fflush(stdin);

    if (getch() == 13)
    {
    save:
        printf("\nSaving the file... \nEnter the filename: ");
        fflush(stdin);
        scanf("%s", &Entered_filename);

        strcat(Entered_filename, file_extension);
        const char *new_filename = Entered_filename;
        temp_fp = fopen(new_filename, "r");
        overwrite_choice = (temp_fp != NULL) ? 'k' : 'z'; //here z is any arbitary character
        while (temp_fp != NULL)
        {
            if (overwrite_choice == 'k')
            {
                printf("\a\n\"%s\" already existed! \nDo you want to overwrite?(y/n) : ", Entered_filename);
                fflush(stdin);
                scanf("%c", &overwrite_choice);
            }
            else if (overwrite_choice == 'y' || overwrite_choice == 'Y')
            {
                fclose(temp_fp);
                temp_fp = fopen(new_filename, "w");
                break;
            }
            else if (overwrite_choice == 'n' || overwrite_choice == 'N')
            {

                printf("\n Enter another filename: ");
                scanf("%s", &Entered_filename);
                strcat(Entered_filename, file_extension);
                new_filename = Entered_filename;

                if (fopen(new_filename, "r") == NULL)
                {
                    fclose(temp_fp);
                    temp_fp = fopen(new_filename, "w+");
                    break;
                }
                else
                {
                    overwrite_choice = 'k';
                }
            }
            else
            {
                printf("\n\aInvalid selection! Try again.\nDo you want to overwrite?(y/n) : ");
                fflush(stdin);
                scanf("%c", &overwrite_choice);
            }
        }
        fclose(temp_fp);
        remove(new_filename);
        rename(defaultfilename, new_filename);
        fp = fopen(new_filename, "r");
        printf("\nFile: \"%s\" saved successfully!", new_filename);
        printf("\n\nDo you want to view the file [\"%s\"] ?(y/n) : ", new_filename);
        fflush(stdin);
        scanf("%c", &open_choice);
        if (open_choice == 'y' || open_choice == 'Y')
        {
            printf("\n################## FILE VIEWING MODE ##########################\n\n");
            printf(" Opening file>> [\"%s\"]\n", new_filename);
            printf("--------------------------------------------------------------------\n\n");

            //fp = fopen(new_filename, "r");
            if (fp == NULL)
            {
                printf("\n\aUnable to view the file this time...");
            }
            while ((character = getc(fp)) != EOF)
            {
                printf("%c", character);
            }
            printf("\n################### End of FILE VIEWING MODE ####################\n\n");
        }

        printf("\n Closing the editor...");
        printf("\n ..");
        printf("\n ...");
        printf("\n ....");
        printf("\n >> Editor successfully closed after saving the file [\"%s\"].\n", new_filename);
        fclose(fp);
        getch();
        exit(0);
    }
    else
    {
        printf("\n\aDo you really want to exit without saving the file? (y/n) : ");
        fflush(stdin);
        scanf("%c", &exit_confirmation);
        while (exit_confirmation != 'y' || exit_confirmation != 'Y' || exit_confirmation != 'n' || exit_confirmation != 'N')
        {

            if (exit_confirmation == 'y' || exit_confirmation == 'Y')
            {
                printf("\nFile does not save!");
                printf("\n >> Closing the editor...");
                printf("\n ..");
                printf("\n ...");
                printf("\n ....");
                printf("\n >> Editor successfully closed without saving the file.\n");

                getch();
                exit(0);
            }
            else if (exit_confirmation == 'n' || exit_confirmation == 'n')
            {
                goto save;
            }
            else
            {
                printf("\n\aInvalid Selection.. Try again. (y/n)? ");
                fflush(stdin);
                scanf("%c", &exit_confirmation);
            }
        }
    }
}
