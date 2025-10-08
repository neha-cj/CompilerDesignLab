%{
#include "y.tab.h"
%}

%%

"("  {return LP; }
")"  {return RP; }
[ \t\n]  ;
.  {return 0; }
 

%%
