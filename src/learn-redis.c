#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include "adlist.h"
#include "testhelp.h"

#define TC_VERSION_MAJOR 2
#define TC_VERSION_MINOR 6

#define __xstr(s) __str(s)
#define __str(s) #s

#define ZMALLOC_LIB ("tcmalloc-" __xstr(TC_VERSION_MAJOR) "." __xstr(TC_VERSION_MINOR))
#define TMALLOC_LIB ("tcmalloc-" __str(TC_VERSION_MAJOR) "." __str(TC_VERSION_MINOR))


/* the macro usage inside zmalloc.h */
void testMacro(){
	printf("%s\n", ZMALLOC_LIB);
	printf("%s\n", TMALLOC_LIB);
}


/* adlist.h */
int testAdlist(){
	list *list = listCreate();
	int a=5, b=6, c=71, d=33, index=0;
	list = listAddNodeHead(list, &a);
	list = listAddNodeHead(list, &b);
	list = listAddNodeHead(list, &c);
	list = listAddNodeHead(list, &d);
	listIter *iter;
	listNode *node;
	iter = listGetIterator(list, AL_START_HEAD);
	while ((node = listNext(iter)) != NULL){
		/* print the list value */
		printf("index %d -->  node %d\n", index++, *(int *)listNodeValue(node));
	}
	
	int *p = &c;
	node = listSearchKey(list, p);
	printf("listSearchKey %d\n", *(int *)listNodeValue(node));

	node = listIndex(list, 0L);
	printf("listSearchKey %d\n", *(int *)listNodeValue(node));

	listRelease(list);
	//assert(list != NULL);
	test_cond("if list == NULL after listRelease", list == NULL );
	test_report();
}



int main(void){
	printf("Learning Redis this way!\n");

	printf("Macro Test\n");
	testMacro();

	printf("adlist Test\n");
	testAdlist();
	return 0;
}
