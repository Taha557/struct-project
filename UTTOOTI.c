#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 255 

typedef struct post{
    char* username;
    int post_id;
    int like;
    char* post_text;
    struct post *next;
} tpost;

typedef struct user{
    char* username;
    char* password;
    tpost *firstPost;
    struct user *next;
} tuser;
int signup (tuser **head){
    //user input
    char string1[MAX], string2[MAX];
    scanf("%s %s", string1, string2);
    char *userName = malloc(sizeof(char) * strlen(string1));
    char *passWord = malloc(sizeof(char) * strlen(string2));
    strcpy(userName, string1);
    strcpy(passWord, string2);
    //function
    tuser* newUser = malloc(sizeof(tuser));
    newUser -> username = userName;
    newUser -> password = passWord;
    newUser -> firstPost = NULL;
    newUser -> next = NULL;
    tuser *temp = (*head);
    while(temp != NULL){
        if (strcmp(temp -> username, userName) == 0){
            printf("This username is already taken!\n");
            return 0;
        }
        temp = temp -> next;
    }

    if (*head == NULL){
        *head = newUser;
        return 1;
    }
    else{
        tuser* lastUser = *head;
        while (lastUser -> next != NULL){
            lastUser = lastUser -> next;
        }
        lastUser -> next = newUser;
        return 1;
        }
    }


void printList(tuser *logged_in_user){
    if (logged_in_user != NULL){
        tpost *temp = (logged_in_user -> firstPost);
        printf("Username = %s\npassword = %s\n***********\n", logged_in_user -> username, logged_in_user -> password);
        while (temp != NULL){
            printf("post:%s\npost_id = %d\nlike = %d\n***********\n", temp -> post_text, temp -> post_id, temp -> like);
            temp = temp -> next;
            }
        }
    else{
        printf("You are not logged in!!!\n");
    }
}
int login(tuser **logged_in_user, tuser *head){
    //user input
    char string1[MAX], string2[MAX];
    scanf("%s %s", string1, string2);
    char *userName = malloc(sizeof(char) * strlen(string1));
    char *passWord = malloc(sizeof(char) * strlen(string2));
    strcpy(userName, string1);
    strcpy(passWord, string2);
    //function
    if ((*logged_in_user) == NULL){
        (*logged_in_user) = head;
        while ((*logged_in_user) != NULL){
            if ((strcmp((*logged_in_user) -> username, userName) && strcmp((*logged_in_user) -> username, userName)) == 0){
                ((*logged_in_user) -> username) = userName;
                ((*logged_in_user) -> password) = passWord;
                ((*logged_in_user) -> firstPost) = NULL;
                return 1;
            }
            (*logged_in_user) = ((*logged_in_user) -> next);
        }
        (*logged_in_user) = NULL;
        printf("Invalid creditentials!!!\n");
        return 0;
        }
    else{
        printf("You are currently logged in!!!!\n");
        return 0;
    }
}


int user_post(tuser **logged_in_user){
    if (logged_in_user == NULL){
        printf("You are not logged in!!!\n");
        return 0;
    }
    else{
        //user input
        char string1[MAX];
        gets(string1);
        fflush(stdin);
        char *post = malloc(sizeof(char) * (strlen(string1)));
        strcpy(post, string1);
        //function
        tpost* newPost = malloc(sizeof(tpost));
        newPost -> username = ((*logged_in_user) -> username);
        newPost -> post_text = post;
        newPost -> post_id = 1;
        newPost -> like = 0;
        newPost -> next = NULL;
        if (((*logged_in_user) -> firstPost) == NULL){
            ((*logged_in_user) -> firstPost) = newPost;
            return 1;
        }
        else{
            tpost *lastPost = ((*logged_in_user) -> firstPost);
            int i = 2;
            while ((lastPost -> next) != NULL){
                lastPost = lastPost -> next;
                i++;
            }
            lastPost -> next = newPost;
            (lastPost -> next) -> post_id = i;
            return 1;
        }
    }
}

int like_post(tuser *head){
    //user input
    int post_ID;
    char userName[MAX];
    scanf("%s %d", userName, &post_ID);
    fflush(stdin);
    //function
    tuser *temp = head;
    while (temp != NULL){
        if (strcmp(temp -> username, userName) == 0){
            tpost *tempPost;
            tempPost = (temp -> firstPost);
            while (tempPost != NULL){
                if (post_ID == (tempPost -> post_id)){
                    (tempPost -> like) ++;
                    return 1;
                }
                tempPost = tempPost -> next;
                if (tempPost == NULL){
                    printf("Invalid selection!!\n");
                    return 0;
                }
            }
        }
        temp = temp -> next;
    }
    if (temp == NULL){
        printf("This username does not exist!!!\n");
        return 0;
    }
}

int delete(tuser **logged_in_user){
    if ((*logged_in_user) == NULL){
        printf("you are not logged in!!!\n");
        return 0;
    }
    int id;
    fflush(stdin);
    scanf("%d", &id);
    tpost *temp = ((*logged_in_user)-> firstPost);
    tpost *prev;
    if ((temp != NULL) && (temp -> post_id == id)){
        ((*logged_in_user)-> firstPost) = (temp -> next);
        free(temp);
        return 1;
    }
    
    while ((temp != NULL) && (temp -> post_id != id)){
        prev = temp;
        temp = temp -> next;
    }
    
    if (temp == NULL){
        printf("Post not found!\n");
        return 0;
    }
    prev -> next = temp -> next;
    free(temp);
    return 1;
}

int logout(tuser **logged_in_user){
    if ((*logged_in_user) == NULL){
        printf("You are not logged in!!!\n");
        return 0;
    }
    else {
        (*logged_in_user) = NULL;
        printf("successfully done!!\n");
        return 1;
    }
}

int find_user(tuser *head){
    char userName[MAX];
    scanf("%s", userName);
    fflush(stdin);
    //function
    tuser *temp = head;
    while (temp != NULL){
        if (strcmp(temp -> username, userName) == 0){
            printf("%s\nposts:\n", userName);
            tpost *tempPost = (temp -> firstPost);
            while(tempPost != NULL){
                printf("post : %s\nlikes = %d\npost id = %d\n**********\n",tempPost -> post_text, tempPost -> like, tempPost -> post_id);
                tempPost = tempPost -> next;
            }
            return 1;
        }
        temp = temp -> next;
    }
    printf("this username does not exist!!!\n");
    return 0;
}



int main(){
    char command[10];
    tuser *head = NULL;
    tuser *logged_in_user = NULL;
    while (1){
        scanf("%s", command);
        fflush(stdin);
        if ((strcmp(command, "signup") && strcmp(command, "login") && strcmp(command, "logout") && strcmp(command, "info") && strcmp(command, "post") && strcmp(command, "like") && strcmp(command, "find_user") && strcmp(command, "delete")) != 0){
            printf("Invalid selection!!!\n");
        }
        else{
        if (strcmp(command, "signup") == 0){
            signup(&head);
            fflush(stdin);
        }
        else
        if (strcmp(command, "login") == 0){
            login(&logged_in_user, head);
            fflush(stdin);
        }
        else
        if (strcmp(command, "logout") == 0){
            logout(&logged_in_user);
            fflush(stdin);
        } 
        else
        if (strcmp(command, "info") == 0){
            printList(logged_in_user);
            fflush(stdin);
        }
        else
        if (strcmp(command, "post") == 0){
            user_post(&logged_in_user);
            fflush(stdin);
        }
        else
        if (strcmp(command, "like") == 0){
            like_post(head);
            fflush(stdin);
        }
        else
        if (strcmp(command, "find_user") == 0){
            find_user(head);
            fflush(stdin);
        }
        else
        if (strcmp(command, "delete") == 0){
            delete(&logged_in_user);
            fflush(stdin);
        }
        }
    }
    return 0;
}