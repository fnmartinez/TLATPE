#include <ctype.h>
#include "../../include/Automata.h"
#include "../../include/Derivations.h"
#include "../../include/Derivation.h"
#include "../../include/utils.h"
#include "../../include/Converter.h"
#include <unistd.h>
/*#include <graphviz/gvc.h>
#include <graphviz/libgvplugin_core.la>*/

int containsNode(char name);
int containsSymbol(char name);
void addSymbol(char name);
void addNode(char name, char label, char isFinal);
void addDer(char f, char l, char s);
void printNodes();
void printDers();
void printSymbols();
