/***************************************************************************
 *   breakme.c                                Version 20160612.152232      *
 *                                                                         *
 *   Generate password hints to break it                                   *
 *   Copyright (C) 2016         by Ruben Carlo Benante                     *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License.               *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *   To contact the author, please write to:                               *
 *   Ruben Carlo Benante                                                   *
 *   Email: rcb@beco.cc                                                    *
 *   Webpage: http://www.beco.cc                                           *
 *   Phone: +55 (81) 3184-7555                                             *
 ***************************************************************************/

/* ---------------------------------------------------------------------- */
/**
 * @file breakme.c
 * @ingroup GroupUnique
 * @brief Generate password hints to break it
 * @details This program really do a nice job as a template, and template only!
 * @version 20160612.152232
 * @date 2016-06-12
 * @author Ruben Carlo Benante <<rcb@beco.cc>>
 * @par Webpage
 * <<a href="http://www.beco.cc">www.beco.cc</a>>
 * @copyright (c) 2016 GNU GPL v2
 * @note This program is free software: you can redistribute it
 * and/or modify it under the terms of the
 * GNU General Public License as published by
 * the Free Software Foundation version 2 of the License.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.
 * If not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA. 02111-1307, USA.
 * Or read it online at <<http://www.gnu.org/licenses/>>.
 *
 *
 * @todo Now that you have the template, hands on! Programme!
 * @warning Be carefull not to lose your mind in small things.
 * @bug This file right now does nothing usefull
 *
 */

/*
 * Instrucoes para compilar:
 *   $gcc breakme.c -o breakme.x -Wall
 *        -Wextra -ansi -pedantic-errors -g -O0 -DDEBUG=1 -DVERSION="0.1.160612.142044"
 *   ou preferencialmente inclua um makefile e use:
 *   $make
 */

/* ---------------------------------------------------------------------- */
/* includes */

#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Miscellaneous functions (rand, malloc, srand)*/
#include <getopt.h> /* get options from system argc/argv */
#include <time.h> /* Time and date functions */
#include <assert.h> /* Verify assumptions with assert */
#include <string.h> /* Strings functions definitions */

/* #include <math.h> */ /* Mathematics functions */
/* #include <dlfcn.h> */ /* Dynamic library */
/* #include <malloc.h> */ /* Dynamic memory allocation */
/* #include <unistd.h> */ /* UNIX standard function */
/* #include <limits.h> */ /* Various C limits */
/* #include <ctype.h> */ /* Character functions */
/* #include <errno.h> */ /* Error number codes errno */
/* #include <signal.h> */ /* Signal processing */
/* #include <stdarg.h> */ /* Functions with variable arguments */
/* #include <pthread.h> */ /* Parallel programming with threads */
/* #include <fcntl.h> */ /* File control definitions */
/* #include <termios.h> */ /* Terminal I/O definitions POSIX */
/* #include <sys/stat.h> */ /* File status and information */
/* #include <float.h> */ /* Float constants to help portability */
/* #include <setjmp.h> */ /* Bypass standard function calls and return */
/* #include <stddef.h> */ /* Various types and MACROS */
/* #include <SWI-Prolog.h> */ /* Prolog integration with C */
/* #include <ncurses.h> */ /* Screen handling and optimisation functions */
/* #include <allegro.h> */ /* A game library for graphics, sounds, etc. */
/* #include <libintl.h> */ /* Internationalization / translation */
/* #include <locale.h> */ /* MACROS LC_ for location specific settings */
/* #include "libeco.h" */ /* I/O, Math, Sound, Color, Portable Linux/Windows */
/* #include "breakme.h" */ /* To be created for this template if needed */

/* ---------------------------------------------------------------------- */
/* definitions */

#ifndef VERSION /* gcc -DVERSION="0.1.160612.142628" */
#define VERSION "20160612.152232" /**< Version Number (string) */
#endif

/* Debug */
#ifndef DEBUG /* gcc -DDEBUG=1 */
#define DEBUG 0 /**< Activate/deactivate debug mode */
#endif

/** @brief Debug message if DEBUG on */
#define IFDEBUG(M) if(DEBUG) fprintf(stderr, "[DEBUG file:%s line:%d]: " M "\n", __FILE__, __LINE__); else {;}

/* limits */
#define SBUFF 256 /**< String buffer */

/* ---------------------------------------------------------------------- */
/* globals */

static int verb=0; /**< verbose level, global within the file */

char groups[6][6]={{0}}; /* 6 password groups: 0-5, 6-b, c-h, i-n, o-t and u-z (NOT A STRING! Not null terminated!) */

const char alf[36]="0123456789abcdefghijklmnopqrstuvwxyz";

/* ---------------------------------------------------------------------- */
/* prototypes */

void help(void); /* print some help */
void copyr(void); /* print version and copyright information */
void breakme_init(void); /* global initialization function */
char *passgen(int s); /* password generator */
void tipgen(char *p, int g, int t); /* tip generator */
void tipgen_groups(char *p); /* tip generator by groups */
int thisgroup(char c); /* return the group number for a char */
char lettergroup(char *p, int gpl, int lp, int gi, int li); /* return a letter from group gi, position li */

/* ---------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief This is the main event of the evening
 * @details Ladies and Gentleman... It's tiiiime!
 * Fightiiiiing at the blue corner,
 * he, who has compiled more C code than any other adversary in the history,
 * he, who has developed UNIX and Linux, and is an inspiration to maaany languages
 * and compilers, the GNU C Compiler, GCC!
 * Fightiiiiing at the red corner, the challenger, in his first fight, lacking of any
 * valid experience but angrily, blindly, and no doubtfully, will try to
 * compile this program without errors. He, the student, the apprentice,
 * the developer, beco!!
 *
 * @param[in] argc Argument counter
 * @param[in] argv Argument strings (argument values)
 *
 * @retval 0 If succeed (EXIT_SUCCESS).
 * @retval 1 Or another error code if failed.
 *
 * @par Example
 * @code
 *    $./breakme -h
 * @endcode
 *
 * @warning   Be carefull with...
 * @bug There is a bug with...
 * @todo Need to do...
 * @note You can read more about it at <<a href="http://www.beco.cc">www.beco.cc</a>>
 * @author Ruben Carlo Benante
 * @version 20160612.152232
 * @date 2016-06-12
 *
 */
int main(int argc, char *argv[])
{
    int opt; /* return from getopt() */
    int lines=6; /* number of lines to generate */
    int tips=6; /* number of letters in each group */
    int grps=6; /* groups per password letter */
    char *p=NULL; /* the password to crack */
    int i;

    IFDEBUG("Starting optarg loop...");

    /* getopt() configured options:
     *        -h      help
     *        -V      version
     *        -v      verbose
     *        -s X    password size (default 6 chars)
     *        -t X    tip size (default 6 chars per group)
     *        -d X    lines of data generated
     *        -g X    groups per password letter
     */
    opterr = 0;
    while((opt = getopt(argc, argv, "vhVd:t:g:")) != EOF)
        switch(opt)
        {
        case 'h':
            help();
            break;
        case 'V':
            copyr();
            break;
        case 'v':
            verb++;
            break;
        case 'd':
            lines=strtoul(optarg, NULL, 10);
            break;
        case 't':
            tips=strtoul(optarg, NULL, 10);
            break;
        case 'g':
            grps=strtoul(optarg, NULL, 10);
            break;
        case '?':
        default:
            printf("Type\n\t$man %s\nor\n\t$%s -h\nfor help.\n\n", argv[0], argv[0]);
            return EXIT_FAILURE;
        }

    if(verb)
        printf("Verbose level set at: %d\n", verb);

    breakme_init(); /* initialization function */

    p=passgen(6); /* generate password with a seed */

    for(i=0; i<lines; i++)
        tipgen(p, grps, tips);

    return EXIT_SUCCESS;
}

/* ---------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Generates a password to be craked
 * @details Details to be written in
 *
 * @return The password 
 *
 * @note You can read more about it at <<a href="http://www.beco.cc">www.beco.cc</a>>
 * @author Ruben Carlo Benante
 * @date 2016-06-12
 *
 */
void tipgen(char *p, int gpl, int lp)
{
    int cl; /* current letter */
    /* int gpl = 3; / * groups per password letter */
    /* int lp = 2; / * letters per group */
    int gi, li; /* generate group gi, letter li */
    int pi, pa; /* password index */

    int gp; /* total groups */
    int t; /* password size */

    t = strlen(p);
    gp = t * gpl; /* total of groups */

    /* char lettergroup(char *p, int gpl, int lp, int gi, int li)*/

    /* laco de debug: imprime tudo */
    pa=0;
    pi=0;
    for(gi = 0; gi < gp; gi++)
    {
        pi=gi/gpl;
        if(pi!=pa)
        {
            printf(", ");
            pa=pi;
        }
        /* printf("G%02d: ", gi); */
        for(li = 0; li < lp; li++)
        {
            cl=lettergroup(p, gpl, lp, gi, li);
            printf("%c", cl);
        }
        printf(" ");
    }
    printf("\n");
    pi=rand()%gpl+1;


        if(gi==pi)
            printf("%c", p[0]);
}

/* ---------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Generates a password to be craked
 * @details Details to be written in
 *
 * @return The password 
 *
 * @note You can read more about it at <<a href="http://www.beco.cc">www.beco.cc</a>>
 * @author Ruben Carlo Benante
 * @date 2016-06-12
 *
 */
/* void tipgen(char *p)*/
void tipgen_groups(char *p)
{
    int i, gj, gr, gc, lr;
    int gja[6]={0}; /* password groups already drawn */
    int gqt=6; /* how many groups left */
    int pg; /* the group of the current password letter */
    int cl; /* current letter */

    for(cl=0; cl<6; cl++) /* password letter */
    {
        /* printf("Letter %d tips: ", cl); */
        pg=thisgroup(p[cl]);
        gqt=6;
        for(i=0; i<6; i++) /* zeroes again */
            gja[i]=0;
        for(i=0; i<6; i++) /* tip size */
        {
            gr=rand()%gqt+1; /* a group position (first to last) */
            gc=0;
            gj=0; /* the next group to give a letter */
            while(1)
            {
                if(!gja[gj])
                {
                    gc++;
                    if(gc==gr)
                        break;
                }
                gj++;
            }
            gqt--;
            gja[gj]=1;
            /* printf(" g%d:", gj); */
            if(gj==pg) /* the current letter group */
            {
                printf("%c", p[cl]);
                continue;
            }
            lr=rand()%6; /* a letter from this group */
            printf("%c", groups[gj][lr]);
        }
        printf(" ");
    }
    printf("\n");
}

/* return the group number for a char */
int thisgroup(char x)
{
    int l, c;

    for(l=0; l<6; l++)
        for(c=0; c<6; c++)
            if(x==groups[l][c])
                return l;
    return -1;
}

/* given
 *  - p: password
 *  - gpl: number of groups per letter
 *  - lp: number of letters per group
 *  - gi: group
 *  - li: letter
 * return the letter li of group gi
 */
char lettergroup(char *p, int gpl, int lp, int gi, int li)
{
    int gp; /* number of groups */
    int i, g, l, c;
    int magic_seed;
    int t; /* password size */

    t=strlen(p);
    gp=t*gpl;

    magic_seed=gpl+lp+gi+li+t+gp;

    assert(gpl>0 && gpl<7);
    assert(t>0);
    assert(gp>=t);
    assert(lp>=2);
    assert(gi>=0 && gi<gp);
    assert(li>=0 && li<lp);

    for(i=0; i<t; i++)
        magic_seed += p[i];

    srand(magic_seed);

    for(g=0; g<=gi; g++)
    {
        i=g/gpl;
        for(l=0; l<=li; l++)
        {
            c = rand()%36;
            if(alf[c] == p[i])
                c=(++c==37?0:c);
        }
    }
    return alf[c];
} 

    


/* ---------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Generates a password to be craked
 * @details Details to be written in
 *
 * @return The password 
 *
 * @note You can read more about it at <<a href="http://www.beco.cc">www.beco.cc</a>>
 * @author Ruben Carlo Benante
 * @date 2016-06-12
 *
 */
char *passgen(int s)
{
    static char p[7]={0}; /* default to 6: remember to change */
    int y, x, i; /* password index */

    srand(s); /* the seed for a fixed "random" password */

    for(i=0; i<6; i++)
    {
        y=rand()%6; /* from all group positions */
        x=rand()%6; /* from all group positions */
        p[i]=groups[y][x];
    }

    if(DEBUG) fprintf(stderr, "[DEBUG file:%s line:%d]: Generated password: %s \n", __FILE__, __LINE__, p);

    if(!DEBUG) 
        srand(time(NULL)); /* now some really "pseudo-true" randomness */
    
    return p;
}

/* ---------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Prints help information and exit
 * @details Prints help information (usually called by opt -h)
 * @return Void
 * @author Ruben Carlo Benante
 * @version 20160612.152232
 * @date 2016-06-12
 *
 */
void help(void)
{
    IFDEBUG("help()");
    printf("%s - %s\n", "breakme", "Generate password hints to break it");
    printf("\nUsage: %s [-h|-v]\n", "breakme");
    printf("\nOptions:\n");
    printf("\t-h,  --help\n\t\tShow this help.\n");
    printf("\t-V,  --version\n\t\tShow version and copyright information.\n");
    printf("\t-v,  --verbose\n\t\tSet verbose level (cumulative).\n");
    /* add more options here */
    printf("\nExit status:\n\t0 if ok.\n\t1 some error occurred.\n");
    printf("\nTodo:\n\tLong options not implemented yet.\n");
    printf("\nAuthor:\n\tWritten by %s <%s>\n\n", "Ruben Carlo Benante", "rcb@beco.cc");
    exit(EXIT_FAILURE);
}

/* ---------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Prints version and copyright information and exit
 * @details Prints version and copyright information (usually called by opt -V)
 * @return Void
 * @author Ruben Carlo Benante
 * @version 20160612.152232
 * @date 2016-06-12
 *
 */
void copyr(void)
{
    IFDEBUG("copyr()");
    printf("%s - Version %s\n", "breakme", VERSION);
    printf("\nCopyright (C) %d %s <%s>, GNU GPL version 2 <http://gnu.org/licenses/gpl.html>. This  is  free  software: you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law. USE IT AS IT IS. The author takes no responsability to any damage this software may inflige in your data.\n\n", 2016, "Ruben Carlo Benante", "rcb@beco.cc");
    if(verb>3) printf("copyr(): Verbose: %d\n", verb); /* -vvvv */
    exit(EXIT_FAILURE);
}

/* ---------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief This function initializes some operations before start
 * @details Details to be written in
 * multiple lines
 *
 * @return Void
 *
 * @note You can read more about it at <<a href="http://www.beco.cc">www.beco.cc</a>>
 * @author Ruben Carlo Benante
 * @date 2016-06-12
 *
 */
void breakme_init(void)
{
    IFDEBUG("breakme_init()");

    int l, c;
    char r='0';

    /* initialization */

    for(l=0; l<6; l++)
        for(c=0; c<6; c++)
        {
            groups[l][c]=r;
            if(r == '9')
                r='a';
            else
                r++;
        }

    return;
}

/* ---------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : C config for Vim modeline */
/* Template by Dr. Beco <rcb at beco dot cc> Version 20160612.142044      */



