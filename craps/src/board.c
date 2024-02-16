#include "board.h"
#include "colors.h"

#include <stdio.h>

void printBoard() {
    printf("                                       +-----+-----+-----+-----+------+------+-------+--.           \n");
    printf("                                       |     |     |     |     |      |      |       |   `--.       \n");
    printf("                                       +-----+-----+-----+-----+------+------+       |%s(6)%sD  ||`----.\n", ANSI_RED, ANSI_RESET);
    printf("                                       |     |     |     |     |      |      | DON'T |%s(6)%sO  ||     |\n", ANSI_RED, ANSI_RESET);
    printf("                                       +-----+-----+-----+-----+------+------+ COME  |   N  ||     |\n");
    printf("                                       |     |     |     |     |      |      |  BAR  |   '  ||     |\n");
    printf("                                       |  %s4%s  |  %s5%s  | %sSix%s |  %s8%s  | %sNine%s |  %s10%s  |       |   T  ||  P  |\n", ANSI_YELLOW, ANSI_RESET, ANSI_YELLOW, ANSI_RESET, ANSI_YELLOW, ANSI_RESET, ANSI_YELLOW, ANSI_RESET, ANSI_YELLOW, ANSI_RESET, ANSI_YELLOW, ANSI_RESET);
    printf("                                       |     |     |     |     |      |      |       |      ||  A  |\n");
    printf("                                       +-----+-----+-----+-----+------+------+ %s(6)(6)%s|   P  ||  S  |\n", ANSI_RED, ANSI_RESET, ANSI_RED, ANSI_RESET);
    printf("                                       |     |     |     |     |      |      |       |   A  ||  S  |\n");
    printf("                                       +-----+-----+-----+-----+------+------+-------+   S  ||     |\n");
    printf("+--------------------------------+           |       %s.---   .-.    .. ..   .....%s     |   S  ||  L  |\n", ANSI_RED, ANSI_RESET);
    printf("| 5 for 1     %sSEVEN%s      5 for 1 |           |      %s|      |   |  |  |  |  |%s         |      ||  I  |\n", ANSI_RED, ANSI_RESET, ANSI_RED, ANSI_RESET);
    printf("|---------------+----------------| (C)-(E)-> |      %s|      |   |  |  |  |  +----%s     |   B  ||  N  |\n", ANSI_RED, ANSI_RESET);
    printf("|  %s(3) (3)%s      |       %s(5) (5)%s  |           |      %s|      |   |  |  |  |  |%s         |   A  ||  E  |\n", ANSI_YELLOW, ANSI_RESET, ANSI_YELLOW, ANSI_RESET, ANSI_RED, ANSI_RESET);
    printf("| 10 for 1      |        8 for 1 |           |       %s`---   `-`   `  `  `  `````%s     |   R  ||     |\n", ANSI_RED, ANSI_RESET);
    printf("|---------------+----------------| (C)-(E)-> +---------------------------------------+------+|     |\n");
    printf("|  %s(4) (4)%s      |       %s(2) (2)%s  |           | %sPAYS DOUBLE              PAYS DOUBLE%s .`       |     |\n", ANSI_YELLOW, ANSI_RESET, ANSI_YELLOW, ANSI_RESET, ANSI_YELLOW, ANSI_RESET);
    printf("| 10 for 1      |        8 for 1 |           |    %s(2)  3 - 4 - 9 - 10 - 11  (12)%s .--`        |     |\n", ANSI_YELLOW, ANSI_RESET);
    printf("+---------------+----------------+ (C)-(E)-> |                  %sFIELD%s         .--`    %s8%s      |     |\n", ANSI_YELLOW, ANSI_RESET, ANSI_RED, ANSI_RESET);
    printf("|               |                |           |                            .--`   %sB%s           |     |\n", ANSI_RED, ANSI_RESET);
    printf("|  %s(1) (1)%s  +-------+   %s(6) (6)%s  | (C)-(E)-> +---------------------------`          %sI%s        |     |\n", ANSI_RED, ANSI_RESET, ANSI_RED, ANSI_RESET, ANSI_RED, ANSI_RESET);
    printf("| 30 for 1  | %sHORN%s  |   30 for 1 |           |  DON'T PASS BAR  %s(6) (6)%s |      %s6      G%s  .--       |\n", ANSI_RED, ANSI_RESET, ANSI_RED, ANSI_RESET, ANSI_RED, ANSI_RESET);
    printf("+-----------+       +------------+ (C)-(E)-> +--------------------------+            .--`          |\n");
    printf("|           |  %sBET%s  |            |           +--------------------------+-----------`          .--`\n", ANSI_RED, ANSI_RESET);
    printf("|  %s(1) (2)%s  +---+---+   %s(6) (5)%s  |           +       PASS LINE                             .--`\n", ANSI_RED, ANSI_RESET, ANSI_RED, ANSI_RESET);
    printf("| 15 for 1      |       15 for 1 | (C)-(E)-> +--------------------------------------------`\n");
    printf("+---------------+----------------+                                                        \n");
    printf("| 8 for 1    %sANY CRAPS%s   8 for 1 | (C)-(E)->                                              \n", ANSI_RED, ANSI_RESET);
    printf("+--------------------------------+                                                        \n");
}