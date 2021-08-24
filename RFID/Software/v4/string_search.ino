bool string_search(char* text,char* c_to_search,int len_text ,int len_search)
{
    int pos_search = 0;
    int pos_text = 0;
    
    for (pos_text = 0; pos_text < len_text - len_search;++pos_text)
    {
        if(text[pos_text] == c_to_search[pos_search])
        {
            ++pos_search;
            if(pos_search == len_search)
            {
                // match
                
                return(true);
            }
        }
        else
        {
           pos_text -=pos_search;
           pos_search = 0;
        }
    } 
    return(false);
}

