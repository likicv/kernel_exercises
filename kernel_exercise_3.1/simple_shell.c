/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    char cmd[64];
    char *argv[10];
    pid_t pid;
    int status;

    printf("simple shell-> ");

    while (fgets(cmd, sizeof(cmd), stdin) != NULL) {

        /* strip newline */
        if (cmd[strlen(cmd) - 1] == '\n')
            cmd[strlen(cmd) - 1] = 0;

        /* handle 'exit' command */
        if (strcmp(cmd, "exit") == 0)
            break;

        /* tokenise input into argv[] */
        int i = 0;
        argv[i] = strtok(cmd, " ");
        while (argv[i] != NULL && i < 9)
            argv[++i] = strtok(NULL, " ");
        argv[i] = NULL;

        pid = fork();

        if (pid == 0) { /* child  process */
            execvp(argv[0], argv);
            perror(argv[0]);  /* show error if exec fails */
            exit(127);
        }

        /* parent waits */
        waitpid(pid, &status, 0);

        printf("simple shell-> ");
    }

    exit(0);
}


