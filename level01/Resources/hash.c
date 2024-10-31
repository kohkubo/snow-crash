#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
const char *target_hash = "42hDRfypTqqnw";
// The salt is converted into a two-character string and is stored in the /etc/passwd file along with the encrypted “password.”
// ソルトは 2 文字の文字列に変換され、暗号化された「パスワード」とともに /etc/passwd ファイルに保存されます。
const char *salt = "42";

void dictionary_attack() {
    FILE *file = fopen("rockyou.txt", "r");
    if (file == NULL) {
        printf("Failed to open dictionary file.\n");
        return;
    }

    char password[100];
    while (fgets(password, sizeof(password), file)) {

        password[strcspn(password, "\n")] = 0;
        //printf("%s\n", password);
        char *hashed_password = crypt(password, salt);
        //printf("%s\n", hashed_password);
        if (strcmp(hashed_password, target_hash) == 0) {
            printf("Password found: %s\n", password);
            fclose(file);
            return;
        }
    }

    printf("Password not found in dictionary.\n");
    fclose(file);
}

int main() {
    dictionary_attack();

    return 0;
}
