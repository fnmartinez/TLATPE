%{
char * grammar_name;
char previous;
int i;
%}
%x TO_VN VN TO_VT VT TO_D DISTINGUISHED TO_PR PRODUCTION PROD_TRNSTN TO_FIN FIN ERROR
space [ \t\n]
non_terminal [A-Z]
terminal [a-z]
number [0-9]
grammar_name [gG]{number}
lamda \\
valid_left_side {non_terminal}
valid_right_side ({non_terminal}{terminal})|({terminal}{non_terminal})|{lamda}|{terminal}|{non_terminal}
%%
<INITIAL>{space}*{grammar_name}{space}*={space}*\(	{for(i=0; i<yyleng && (yytext[i]==' ' || yytext[i]=='\n' || yytext[i]=='\t'); i++);
								yytext[0]=yytext[i];
								yytext[1]=yytext[i+1];
								yytext[2]='\0';
								printf("Grammar name: %s\n", yytext);
								BEGIN(TO_VN);}
<TO_VN>{space}*\{				printf("Non terminals: \n");BEGIN(VN);
<VN>{space}*{non_terminal}{space}*[,\}]			{printf("%s%c\n", yytext,(yytext[yyleng-1]==','?'\n':' '));
								if(yytext[yyleng-1]==',')
									BEGIN(VN);
								else if(yytext[yyleng-1]=='}')
									BEGIN(TO_VT);
								else
									BEGIN(ERROR);}
<TO_VT>{space}*,{space}*\{			printf("Terminals: \n");BEGIN(VT);
<VT>{space}*{terminal}{space}*[,\}]			{printf("%s%c\n", yytext, (yytext[yyleng-1]==','?'\n':' '));
								if(yytext[yyleng-1]==',')
									BEGIN(VT);
								else if(yytext[yyleng-1]=='}')
									BEGIN(TO_D);
								else
									BEGIN(ERROR);}
<TO_D>{space}*,					printf("Distinguished Element: \n"); BEGIN(DISTINGUISHED);
<DISTINGUISHED>{space}*{non_terminal}		{for(i=0; i<yyleng && (yytext[i]==' ' || yytext[i]=='\n' || yytext[i]=='\t'); i++);
								yytext[0]=yytext[i];
								yytext[1]='\0';
								printf("%s\n",yytext);
								BEGIN(TO_PR);}
<TO_PR>{space}*,{space}*\{			printf("Productions:\n");BEGIN(PRODUCTION);
<PRODUCTION>{space}*({valid_left_side}){space}*\-{space}*\>{space}*({valid_right_side}){space}*[,\|\}]	{printf("%s\n",yytext);
													if(yytext[yyleng-1]==',')
														BEGIN(PRODUCTION);
													else if(yytext[yyleng-1]=='}')
														BEGIN(TO_FIN);
													else if(yytext[yyleng-1]=='|')
													{
														for(i=0; i<yyleng && (yytext[i]==' ' || yytext[i]=='\n' || yytext[i]=='\t'); i++);
														previous=yytext[i];
														BEGIN(PROD_TRNSTN);
													}
													else
														BEGIN(ERROR);}
<PROD_TRNSTN>{space}*({valid_right_side}){space}*[,\|\}]	{printf("%c->%s\n", previous, yytext);
								if(yytext[yyleng-1]==',')
									BEGIN(PRODUCTION);
								else if(yytext[yyleng-1]=='}')
									BEGIN(TO_FIN);
								else if(yytext[yyleng-1]=='|')
								{
									BEGIN(PROD_TRNSTN);
								}
								else
									BEGIN(ERROR);
								}
<TO_FIN>{space}*\)	printf("End of Grammar\n");BEGIN(FIN);
<FIN>{space}*	printf("EOF!\n");
<ERROR>.{space}*	printf("ERROR!");
