#define buff_max 25
#define mod %
    struct item{
        // different member of the produced data
        // or consumed data   
    }
    // An array is needed for holding the items.
    // This is the shared place which will be 
    // access by both process  
    // item shared_buff [ buff_max ];
    // Two variables which will keep track of
    // the indexes of the items produced by producer
    // and consumer The free index points to
    // the next free index. The full index points to
    // the first full index.
    int free_index = 0;
    int full_index = 0;


item nextProduced;
    while(1){
        // check if there is no space
        // for production.
        // if so keep waiting.
        while((free_index+1) mod buff_max == full_index);
        shared_buff[free_index] = nextProduced;
        free_index = (free_index + 1) mod buff_max;
    }


