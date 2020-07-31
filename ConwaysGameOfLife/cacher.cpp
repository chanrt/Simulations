void cacheMiddle()
{
    int num_neigh;

    for(int row = 1; row < num_rows - 1; row++)
    {
        for(int col = 1; col < num_cols - 1; col++)
        {
            num_neigh = 0;
            if(matrix[row-1][col] == ALIVE) num_neigh++;
            if(matrix[row][col-1] == ALIVE) num_neigh++;
            if(matrix[row-1][col-1] == ALIVE) num_neigh++;
            if(matrix[row+1][col] == ALIVE) num_neigh++;
            if(matrix[row][col+1] == ALIVE) num_neigh++;
            if(matrix[row+1][col+1] == ALIVE) num_neigh++;
            if(matrix[row+1][col-1] == ALIVE) num_neigh++;
            if(matrix[row-1][col+1] == ALIVE) num_neigh++;

            cache[row][col] = num_neigh;
        }
    }
}

void cacheEdge()
{
    int num_neigh;

    for(int col = 1; col < num_cols - 1; col++)
    {
        num_neigh = 0;
        if(matrix[0][col-1] == ALIVE) num_neigh++;
        if(matrix[0][col+1] == ALIVE) num_neigh++;
        if(matrix[1][col-1] == ALIVE) num_neigh++;
        if(matrix[1][col] == ALIVE) num_neigh++;
        if(matrix[1][col+1] == ALIVE) num_neigh++;

        if(extended_neigh)
        {
            if(matrix[num_rows-1][col-1] == ALIVE) num_neigh++;
            if(matrix[num_rows-1][col] == ALIVE) num_neigh++;
            if(matrix[num_rows-1][col+1] == ALIVE) num_neigh++;
        }

        cache[0][col] = num_neigh;
    }

    for(int col = 1; col < num_cols - 1; col++)
    {
        num_neigh = 0;
        if(matrix[num_rows-1][col-1] == ALIVE) num_neigh++;
        if(matrix[num_rows-1][col+1] == ALIVE) num_neigh++;
        if(matrix[num_rows-2][col-1] == ALIVE) num_neigh++;
        if(matrix[num_rows-2][col] == ALIVE) num_neigh++;
        if(matrix[num_rows-2][col+1] == ALIVE) num_neigh++;
        
        if(extended_neigh)
        {
            if(matrix[0][col-1] == ALIVE) num_neigh++;
            if(matrix[0][col] == ALIVE) num_neigh++;
            if(matrix[0][col+1] == ALIVE) num_neigh++;
        }

        cache[num_rows-1][col] = num_neigh;
    }

    for(int row = 1; row < num_rows - 1; row++)
    {
        num_neigh = 0;
        if(matrix[row-1][0] == ALIVE) num_neigh++;
        if(matrix[row+1][0] == ALIVE) num_neigh++;
        if(matrix[row-1][1] == ALIVE) num_neigh++;
        if(matrix[row][1] == ALIVE) num_neigh++;
        if(matrix[row+1][1] == ALIVE) num_neigh++;
        
        if(extended_neigh)
        {
            if(matrix[row-1][num_cols-1] == ALIVE) num_neigh++;
            if(matrix[row][num_cols-1] == ALIVE) num_neigh++;
            if(matrix[row+1][num_cols-1] == ALIVE) num_neigh++;
        }

        cache[row][0] = num_neigh;
    }

    for(int row = 1; row < num_rows - 1; row++)
    {
        num_neigh = 0;
        if(matrix[row-1][num_cols-1] == ALIVE) num_neigh++;
        if(matrix[row+1][num_cols-1] == ALIVE) num_neigh++;
        if(matrix[row-1][num_cols-2] == ALIVE) num_neigh++;
        if(matrix[row][num_cols-2] == ALIVE) num_neigh++;
        if(matrix[row+1][num_cols-2] == ALIVE) num_neigh++;
        
        if(extended_neigh)
        {
            if(matrix[row-1][0] == ALIVE) num_neigh++;
            if(matrix[row][0] == ALIVE) num_neigh++;
            if(matrix[row+1][0] == ALIVE) num_neigh++;
        }

        cache[row][num_cols-1] = num_neigh;
    }
}

void cacheCorner()
{
    int num_neigh = 0;
    if(matrix[1][0] == ALIVE) num_neigh++;
    if(matrix[0][1] == ALIVE) num_neigh++;
    if(matrix[1][1] == ALIVE) num_neigh++;

    if(extended_neigh)
    {
        if(matrix[num_rows-1][0] == ALIVE) num_neigh++;
        if(matrix[num_rows-1][1] == ALIVE) num_neigh++;
        if(matrix[num_rows-1][num_cols-1] == ALIVE) num_neigh++;
        if(matrix[0][num_cols-1] == ALIVE) num_neigh++;
        if(matrix[1][num_cols-1] == ALIVE) num_neigh++;
    }

    cache[0][0] = num_neigh;

    num_neigh = 0;
    if(matrix[num_rows-2][num_cols-1] == ALIVE) num_neigh++;
    if(matrix[num_rows-1][num_cols-2] == ALIVE) num_neigh++;
    if(matrix[num_rows-2][num_cols-2] == ALIVE) num_neigh++;
    
    if(extended_neigh)
    {
        if(matrix[0][num_cols-1] == ALIVE) num_neigh++;
        if(matrix[0][num_cols-2] == ALIVE) num_neigh++;
        if(matrix[0][0] == ALIVE) num_neigh++;
        if(matrix[num_rows-1][0] == ALIVE) num_neigh++;
        if(matrix[num_rows-2][0] == ALIVE) num_neigh++;
    }

    cache[num_rows-1][num_cols-1] = num_neigh;

    num_neigh = 0;
    if(matrix[num_rows-2][0] == ALIVE) num_neigh++;
    if(matrix[num_rows-1][1] == ALIVE) num_neigh++;
    if(matrix[num_rows-2][1] == ALIVE) num_neigh++;
    
    if(extended_neigh)
    {
        if(matrix[0][num_cols-1] == ALIVE) num_neigh++;
        if(matrix[num_rows-1][num_cols-1] == ALIVE) num_neigh++;
        if(matrix[num_rows-2][num_cols-1] == ALIVE) num_neigh++;
        if(matrix[0][0] == ALIVE) num_neigh++;
        if(matrix[0][1] == ALIVE) num_neigh++;
    }

    cache[num_rows-1][0] = num_neigh;

    num_neigh = 0;
    if(matrix[1][num_cols-1] == ALIVE) num_neigh++;
    if(matrix[0][num_cols-2] == ALIVE) num_neigh++;
    if(matrix[1][num_cols-2] == ALIVE) num_neigh++;
    
    if(extended_neigh)
    {
        if(matrix[num_rows-1][0] == ALIVE) num_neigh++;
        if(matrix[0][0] == ALIVE) num_neigh++;
        if(matrix[1][0] == ALIVE) num_neigh++;
        if(matrix[num_rows-1][num_cols-1] == ALIVE) num_neigh++;
        if(matrix[num_rows-1][num_cols-2] == ALIVE) num_neigh++;
    }

    cache[0][num_cols-1] = num_neigh;
}