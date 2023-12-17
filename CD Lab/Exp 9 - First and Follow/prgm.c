#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int m = 0, i = 0, j = 0, n;
char a[10][10], f[10];

void first(char c);
void follow(char c);
void followfirst(char c);

int main() {
  char ch, c;
  printf("Enter #productions : ");
  scanf("%d", & n);
  printf("Enter productions :\n");
  scanf("%c", & ch);

  for (i = 0; i < n; i++)
    scanf("%s%c", a[i], & ch); //ch for newline

  int z;
  do {
    printf("Enter character whose first and follow is to be found : ");
    scanf(" %c%c", & c, & ch);
    first(c);
    printf("First(%c) : {", c);
    for (i = 0; i < m; i++)
      printf("%c ", f[i]);
    printf("}\n");

    m = 0;
    strcpy(f, " ");
    follow(c);
    printf("Follow(%c) : {", c);
    for (i = 0; i < m; i++)
      printf("%c ", f[i]);
    printf("}\n");
    
    strcpy(f, " ");
    m = 0;

    printf("Continue (0/1)? : ");
    scanf("%d%c", & z, & ch);
  } while (z == 1);
  return 0;
}

void first(char c) {
  int k;
  if (!isupper(c))
    f[m++] = c;
  for (k = 0; k < n; k++) {
    if (a[k][0] == c) {
      if (a[k][2] == '#') {
        f[m++] = '#';
      } else if (islower(a[k][2])) {
        f[m++] = a[k][2];
      } else {
        first(a[k][2]);
      }
    }
  }
}

void follow(char c) {
  if (a[0][0] == c)
    f[m++] = '$';
  for (i = 0; i < n; i++) {
    for (j = 2; j < strlen(a[i]); j++) {
      if (a[i][j] == c) {
        if (a[i][j + 1] != '\0') //either terminal or non-terminal
          followfirst(a[i][j + 1]);
        if (a[i][j + 1] == '\0' && a[i][0] != c) //2nd cond : to avoid infinite loop for prod A->A
          follow(a[i][0]);
      }
    }
  }

}

void followfirst(char c) {
  char temp[10];
  if (!isupper(c))
    temp[j++] = c;
  for (i = 0; i < n; i++) {
    if (a[i][0] == c) {
      if (a[i][2] == '#') {
        // Do nothing
      } else if (islower(a[i][2])) {
        temp[j++] = a[i][2];
      } else {
        followfirst(a[i][2]);
      }
    }
  }
  for (i = 0; i < j; i++) {
    if (temp[i] != '#') {
      f[m++] = temp[i];
    }
  }
}
