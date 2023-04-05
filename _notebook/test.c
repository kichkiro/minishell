/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:49:06 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/04 13:11:52 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int find_executable(char *command) {
    char	*path = getenv("PATH");
    char	*dir;
    char	*token;
    char	executable_path[1024];

    // Split the PATH variable into individual directories
    dir = strdup(path);
    token = strtok(dir, ":");
    
    // Look for the executable in each directory
    while (token != NULL) {
        sprintf(executable_path, "%s/%s", token, command);
        if (access(executable_path, X_OK) == 0) {
            // Found the executable
            printf("Found %s in %s\n", command, token);
            return (execv(executable_path, NULL));
        }
        token = strtok(NULL, ":");
    }

    // If we get here, the executable was not found
    printf("Could not find %s\n", command);

	printf("%s", path);

    return (-1);
}

int main() {
    char *command = "ls";
    find_executable(command);
    return 0;
}

