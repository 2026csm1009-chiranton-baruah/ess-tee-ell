int marsExploration(char *s)
{
    int errors = 0;

    for (int i = 0; s[i]; i++)
    {
        if (i % 3 == 0 && s[i] != 'S')
            errors++;

        if (i % 3 == 1 && s[i] != 'O')
            errors++;

        if (i % 3 == 2 && s[i] != 'S')
            errors++;
    }

    return errors;
}

int main()
{
    char s[100005];

    scanf("%s", s);

    printf("%d\n", marsExploration(s));

    return 0;
}

/*
INPUT: SOSSPSSQSSOR
Output: 3
*/
