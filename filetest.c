#include <stdio.h>
#include <string.h>

int encrypt(char input[50], char password[6])
{
    FILE *in, *out;
    char output[100];
    sprintf(output, "encrypted_%s", input);
    in = fopen(input, "rb");
    out = fopen(output, "wb");
    int curr;

    while ((curr = getc(in)) != EOF)
    {
        for (int i = 0; i < 4; i++)
        {
            curr = curr ^ password[i];
        }
        fputc(curr, out);
    }
    fclose(in);
    fclose(out);
    return 0;
}

int decrypt(char input[50], char password[6])
{
    FILE *in, *out;
    char output[100];
    sprintf(output, "decrypted_%s", input);
    in = fopen(input, "rb");
    out = fopen(output, "wb");
    if (!in)
    {
        printf("File not Found!!\n");
        return 0;
    }
    int curr;

    while ((curr = getc(in)) != EOF)
    {
        for (int i = 0; i < 4; i++)
        {
            curr = curr ^ password[i];
        }
        fputc(curr, out);
    }
    fclose(in);
    fclose(out);
    return 0;
}

int renameFile(char input[50], char output[50]){
    if(rename(input,output)==0){
       printf("\n File renamed successfully!!\n");
    }else{
       perror("\nXX File rename Failed XX\n");
     
    }
    return 0;
}

int compress(char input[50])
{
    char output[50];
    sprintf(output, "compressed_%s", input);

    FILE *in = fopen(input, "rb");
    if (!in)
        return -1;

    FILE *out = fopen(output, "wb");
    if (!out)
    {
        fclose(in);
        return -1;
    }

    int prev = getc(in);
    if (prev == EOF)
    {
        fclose(in);
        fclose(out);
        return 0;
    }

    int curr, count = 1;

    while ((curr = getc(in)) != EOF)
    {
        if (curr == prev)
        {
            count++;
        }
        else
        {
            fputc((unsigned char)count, out);
            fputc((unsigned char)prev, out);
            prev = curr;
            count = 1;
        }
    }

    fputc((unsigned char)count, out);
    fputc((unsigned char)prev, out);

    fclose(in);
    fclose(out);
    return 0;
}
int decompress(char input[50])
{
    char output[50];
    sprintf(output, "decompressed_%s", input);

    FILE *in = fopen(input, "rb");
    if (!in)
        return -1;

    FILE *out = fopen(output, "wb");
    if (!out)
    {
        fclose(in);
        return -1;
    }

    int count, letter;

    while ((count = getc(in)) != EOF)
    {

        letter = getc(in);
        if (letter == EOF)
        {
            break;
        }

        for (int i = 0; i < count; i++)
        {
            fputc((unsigned char)letter, out);
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}

int main()
{
    char input[100],output[100] ,password[6];
    int choice;
    while (1)
    {

        printf("choose what you want to do : \n 1. Encryption\n 2. Decryption\n 3. compress\n 4. Decompress\n 5.Rename\n 6. Exit\nEnter choice : ");
        scanf("%d", &choice);
        getchar();
        if (choice == 6)
        {
            break;
        }
        printf("Enter the name of your file : ");
        fgets(input, sizeof(input), stdin);
        for (int i = 0; input[i] != '\0'; i++)
        {
            if (input[i] == '\n')
            {
                input[i] = '\0';
                break;
            }
        }
        if (choice == 1 || choice == 2)
        {
            printf("Enter 4 digit password : ");
            fgets(password, sizeof(password), stdin);
            for (int i = 0; password[i] != '\0'; i++)
            {
                if (password[i] == '\n')
                {
                    password[i] = '\0';
                    break;
                }
            }
        }
        if (choice == 1)
        {
            char output[100];
            printf("\n encrypting...\n");
            encrypt(input, password);
            sprintf(output, "encrypted_%s", input);
            printf("New encrypted file added by the name %s", output);
        }
        else if (choice == 2)
        {
            char output[100];
            printf("\n decrypting...\n");
            decrypt(input, password);
            sprintf(output, "decrypted_%s", input);
            printf("New decrypted file added by the name %s\n", output);
        }
        else if (choice == 3)
        {
            char output[100];
            printf("\n compressing...\n");
            compress(input);
            sprintf(output, "compressed_%s", input);
            printf("New compressed file added by the name %s", output);
        }
        else if (choice == 4)
        {
            char output[100];
            printf("\n decompressing...\n");
            decompress(input);
            sprintf(output, "decompressed_%s", input);
            printf("New decompressed file added by the name %s", output);
        }else if (choice == 5){
            printf("Enter the name of your output file : ");
            fgets(output, sizeof(output), stdin);
            for (int i = 0; output[i] != '\0'; i++)
            {
                if (output[i] == '\n')
                {
                    output[i] = '\0';
                    break;
                }
            }
            renameFile(input,output);            
        }
    }

    return 0;
}
