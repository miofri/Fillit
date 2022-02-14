
#include "fillit.h"

/*
**  Round up number to get a square
*/

static int  round_up_sqrt(int i)
{
    int size;

    size = 2;
    if (i == 1)
    {
        return (1);
    }
    while (size * size < i)
    {
        size++;
    }
    return (size);
}

/*
** Install blocks to the map
*/

static int  install_blocks(t_map *map, t_coord *coor, size_t i)
{
    size_t  map_x;
    size_t  map_y;
    size_t  k;
    size_t  m;
    size_t  n;

    k = 0;
    map_x = i % map->size;
    map_y = i / map->size;
    while (k < 4)
    {
        m = map_x + coor[k].x;
        n = map_y + coor[k].y;
        if (map->new_map[m + n * map->size] != '.' || m >= map->size
            || n >= map->size)
        {
            return (0);
        }
        k++;
    }
    while (k > 0)
    {
        m = map_x + coor[--k].x;
        n = map_y + coor[k].y;
        map->new_map[m + n * map->size] = coor[0].letter;
    }
    return (1);
}

/*
** Check for the smallest square without overlap
** Use recursion to check is there any block will fit the place
** If solution didn't found, free map to avoid memory leak
*/

static void searching_solution(t_map *map, t_blocks *blocks, size_t nb_blocks, size_t *found)
{
    size_t  i;
    size_t  map_size;

    if (nb_blocks == blocks->nb_blocks)
    {
        *found = 1;
    }
    if (*found == 1)
    {
        return ;
    }
    i = 0;
    map_size = map->size * map->size;
    while (i < map_size && !(*found))
    {
        if (install_blocks(map, blocks->blocks[nb_blocks], i))
        {
            searching_solution(map, blocks, nb_blocks + 1, found);
        }
        if (*found == 0)
        {
            free_map(map, blocks->blocks[nb_blocks], i);
        }
        i++;
    }
}

/*
** Set block's shape to struct, create map and place blocks
** Go thru all the possibilities to get the smallest square
** When the smallest square found, print out map
** Free block that has been initialized then free map to
** avoid memory leak
*/

int final_solution(char *s)
{
    t_map       *map;
    t_blocks    *blocks;
    size_t      found;
    size_t      map_size;

    found = 0;
    blocks = init_blocks(s);
    if (!blocks)
    {
        return (0);
    }
    map_size = round_up_sqrt(blocks->nb_blocks) * 2;
    if (map_size < 4)
    {
        map_size = 4;
    }
    while (!found)
    {
        map = create_map(map_size);
        if (!map)
        {
            return (0);
        }
        searching_solution(map, blocks, 0, &found);
        if(!found)
        {
            free(map);
            map_size++;
        }
    }
    print_map(map->new_map, map_size);
    free_block(blocks);
    free(map);
    return (1);
}

