// PA4: Strongly connected components
// CMPS 101 
// Winter 2019 
// Stone, Matthew 
// 1673656 
//------------------------- 
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Digraph.h"
#include <string.h>
int main(int argc, char * argv[])
{
    // FILE IO
    //// READER
    FILE * reader = fopen(argv[1], "r");
    FILE * writer = fopen(argv[2], "w");
    if (reader == 0)
    {
        fprintf(writer,"file not found");
        exit(1);
    }
    else
    {
        int store1 = 0;
        int store2 = 0;
        int size = 0;
        char command[2000];
        // sets a size from input and creates a graph.
        fgets(command, 2000, reader);
        // token from the FILEIO given to us.
        char * token = strtok(command, ", \n\r");
        // atoi function given to me in 2/8/19 lab.
        size = atoi(token);
        // checks if size is valid, iterates first line
        if (size > 0)
        {
            Digraph NGraph = newDigraph(size);
            // function from FILEIO
            token = strtok(NULL, ", \n\r");
            while (token != NULL)
            {
                store1 = atoi(token);
                token = strtok(NULL, ", \n\r");
                store2 = atoi(token);
                token = strtok(NULL, ", \n\r");
                addEdge( NGraph, store1, store2);
            }
            // below is a selection if else statement that we learned in Abishek's office hours on last friday before due day.
            while (fgets(command,2000,reader) != NULL)
            {
                token = strtok(command, ", \n\r");
                if ( strcmp(token, "PrintDigraph") == 0 )
                {
                    fprintf(writer,"PrintDigraph");
                    token = strtok(NULL, ", \n\r");
                    if (token == NULL)
                    {
                        fprintf(writer,"\n");
                        printDigraph(writer,NGraph);
                    }
                    else
                    {
                        while (token != NULL)
                        {
                            fprintf(writer," %s",token);
                            token = strtok(NULL, ", \n\r");
                        }
                        fprintf(writer,"\nERROR\n");
                    }
                }
                else if ( strcmp(token, "GetSize") == 0 )
                {
                    fprintf(writer,"GetSize");
                    token = strtok(NULL, ", \n\r");
                    if (token == NULL)
                    {
                        fprintf(writer,"\n");
                        fprintf( writer, "%d\n", getSize(NGraph) );
                    }
                    else
                    {
                        while (token != NULL)
                        {
                            fprintf(writer," %s",token);
                            token = strtok(NULL, ", \n\r");
                        }
                        fprintf(writer,"\nERROR\n");
                    }
                }
                else if ( strcmp(token, "GetOrder") == 0 )
                {
                    fprintf(writer,"GetOrder");
                    token = strtok(NULL, ", \n\r");
                    if ( token == NULL )
                    {
                        fprintf(writer,"\n");
                        fprintf( writer, "%d\n", getOrder(NGraph) );
                    }
                    else
                    {
                        while (token != NULL)
                        {
                            fprintf(writer," %s",token);
                            token = strtok(NULL, ", \n\r");
                        }
                        fprintf(writer,"\nERROR\n");
                    }
                }
                else if ( strcmp(token, "GetOutDegree") == 0 )
                {
                    fprintf(writer,"GetOutDegree");
                    token = strtok(NULL, ", \n\r");
                    // if token is NULL, print error.
                    if ( token != NULL )
                    {
                        // if not NULL, convert to argument
                        store1 = atoi(token);
                        fprintf(writer," %d",store1);
                        token = strtok(NULL, ", \n\r");
                        // check for further arguments, if detected output ERROR
                        if ( token != NULL)
                        {
                            while (token != NULL)
                            {
                                fprintf(writer," %s",token);
                                token = strtok(NULL, ", \n\r");
                            }
                            fprintf(writer,"\nERROR\n");
                        }
                        else
                        {
                            // check if argument is valid.
                            if ( store1 <= getOrder(NGraph) && store1 > 0 )
                            {
                                fprintf(writer,"\n%d\n", getOutDegree(NGraph, store1));
                            }
                            else
                            {
                                fprintf(writer,"\nERROR\n");
                            }    
                        }
                    }
                    else
                    {
                        fprintf(writer,"\nERROR\n");
                    }
                }
                else if ( strcmp(token, "DeleteEdge") == 0 )
                {
                    fprintf(writer,"DeleteEdge");
                    token = strtok(NULL, ", \n\r");
                    // checks first argument
                    if ( token != NULL )
                    {
                        store1 = atoi(token);
                        fprintf(writer," %d",store1);
                        token = strtok(NULL, ", \n\r");
                        if ( token != NULL )
                        {
                            store2 = atoi(token);
                            fprintf(writer," %d",store2);
                            token = strtok(NULL, ", \n\r");
                            if (token == NULL)
                            {
                                fprintf(writer,"\n");
                                if ( store1 <= getOrder(NGraph) && store1 > 0 && store2 <= getOrder(NGraph) && store2 > 0 )
                                {
                                    fprintf(writer,"%d\n",deleteEdge(NGraph, store1, store2));
                                }
                                else
                                {
                                    fprintf(writer,"ERROR\n");
                                }
                            }
                            else
                            {
                                while (token != NULL)
                                {
                                    fprintf(writer," %s",token);
                                    token = strtok(NULL, ", \n\r");
                                }
                                fprintf(writer,"\nERROR\n");
                            }
                        }
                        else
                        {
                            fprintf(writer,"\nERROR\n");
                        }
                    }
                    else
                    {
                        fprintf(writer,"\nERROR\n");
                    }
                }
                else if ( strcmp(token, "AddEdge") == 0 )
                {
                    fprintf(writer,"AddEdge");
                    token = strtok(NULL, ", \n\r");
                    if ( token != NULL )
                    {
                        store1 = atoi(token);
                        fprintf(writer," %d",store1);
                        token = strtok(NULL, ", \n\r");
                        if ( token != NULL )
                        {
                            store2 = atoi(token);
                            fprintf(writer," %d",store2);
                            token = strtok(NULL, ", \n\r");
                            if ( token == NULL)
                            {
                                fprintf(writer,"\n");
                                if ( store1 <= getOrder(NGraph) && store1 > 0 && store2 <= getOrder(NGraph) && store2 > 0 )
                                {
                                    fprintf(writer,"%d\n",addEdge(NGraph, store1, store2));
                                }
                                else
                                {
                                    fprintf(writer,"ERROR\n");
                                }
                            }
                            else
                            {
                                while (token != NULL)
                                {
                                    fprintf(writer," %s",token);
                                    token = strtok(NULL, ", \n\r");
                                }
                                fprintf(writer,"\nERROR\n");
                            }
                        }
                        else
                        {
                            fprintf(writer,"\nERROR\n");
                        }
                    }
                    else
                    {
                        fprintf(writer,"\nERROR\n");
                    }
                }
                else if ( strcmp(token, "InSameSCC") == 0 )
                {
                    fprintf(writer,"InSameSCC ");
                    token = strtok(NULL, ", \n\r");
                    if ( token != NULL )
                    {
                        store1 = atoi(token);
                        fprintf(writer,"%d",store1);
                        token = strtok(NULL, ", \n\r");
                        if ( token != NULL )
                        {
                            store2 = atoi(token);
                            fprintf(writer," %d",store2);
                            token = strtok(NULL, ", \n\r");
                            if ( token != NULL )
                            {
                                while (token != NULL)
                                {
                                    fprintf(writer," %s",token);
                                    token = strtok(NULL, ", \n\r");
                                }
                                fprintf(writer,"\nERROR\n");
                            }
                            else
                            {
                                fprintf(writer,"\n");
                                int result = inSameSCC(NGraph,store1,store2);
                                if ( result == 1 )
                                {
                                    fprintf(writer,"YES\n");
                                }
                                else if ( result < 0)
                                {
                                    fprintf(writer,"ERROR\n");
                                }
                                else
                                {
                                    fprintf(writer,"NO\n");
                                }
                            }
                        }
                        else
                        {
                            fprintf(writer,"\nERROR\n");
                        }
                    }
                    else
                    {
                        fprintf(writer,"\nERROR\n");
                    }
                }
                else if ( strcmp(token, "GetNumSCCVertices") == 0 )
                {
                    fprintf(writer,"GetNumSCCVertices");
                    token = strtok(NULL, ", \n\r");
                    if ( token != NULL )
                    {
                        store1 = atoi(token);
                        fprintf(writer," %d ",store1);
                        token = strtok(NULL, ", \n\r");
                        if (token == NULL)
                        {
                            int result = getNumSCCVertices(NGraph,store1);
                            if (result == -1)
                            {
                                fprintf(writer,"\nERROR\n");
                            }
                            else
                            {
                                fprintf(writer,"\n%d\n",result);
                            }
                        }
                        else
                        {
                            while (token != NULL)
                            {
                                fprintf(writer,"%s",token);
                               token = strtok(NULL, ", \n\r");
                            }
                            fprintf(writer,"\nERROR\n");
                        }
                    }
                    else
                    {
                        fprintf(writer,"\nERROR\n");
                    }
                }
                else if ( strcmp(token, "GetCountSCC") == 0 )
                {
                    fprintf(writer,"GetCountSCC");
                    token = strtok(NULL, ", \n\r");
                    if ( token != NULL )
                    {
                        while (token != NULL)
                        {
                            fprintf(writer," %s",token);
                            token = strtok(NULL, ", \n\r");
                        }
                        fprintf(writer,"\nERROR\n");
                    }
                    else
                    {
                        fprintf(writer,"\n%d\n",getCountSCC(NGraph));
                    }
                }
                else
                {
                    while (token != NULL)
                    {
                        fprintf(writer,"%s ",token);
                        token = strtok(NULL, ", \n\r");
                    }
                    fprintf(writer,"\nERROR\n");
                }
            }
            freeDigraph(&NGraph);
        }
        else
        {
            // print line, then error, then rest of file.
            fprintf(writer,"%s",token);
            while (token != NULL)
            {
                token = strtok(NULL, ", \n\r");
                fprintf(writer," %s",token);
            }
            fprintf(writer,"\nERROR\n");
        }
    }
    // reads in commands from input file.
    fclose(reader);
    fclose(writer);
    return 0;
}

