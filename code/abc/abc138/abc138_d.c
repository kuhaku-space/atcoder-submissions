#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200001

void dfs(int node, int parent, int *tree[], int child_num[], int node_num[]){
  int i,child;

  for(i=0;i<child_num[node];i++){
    child=tree[node][i];
    if(child!=parent){
      node_num[child]+=node_num[node];
      dfs(child,node,tree,child_num,node_num);
    }
  }
}

void input_node(int a, int b, int *tree[], int tree_size[], int child_num[]){
  if(tree_size[a]==0){
    tree[a]=(int *)malloc(sizeof(int));
    tree_size[a]=1;
  }else if(child_num[a]==tree_size[a]){
    tree[a]=(int *)realloc(tree[a],sizeof(int)*tree_size[a]*2);
    tree_size[a]*=2;
  }
  tree[a][child_num[a]++]=b;
}

int main(void){
  int i,j;

  int n,q;
  scanf("%d%d",&n,&q);

  int *tree[MAX_N];
  int tree_size[MAX_N]={};
  int child_num[MAX_N]={};

  int a,b;
  for(i=0;i<n-1;i++){
    scanf("%d%d",&a,&b);
    input_node(a, b, tree, tree_size, child_num);
    input_node(b, a, tree, tree_size, child_num);
  }

  int p,x;
  int node_num[MAX_N]={};
  for(i=0;i<q;i++){
    scanf("%d%d",&p,&x);
    node_num[p]+=x;
  }

  dfs(1,0,tree,child_num,node_num);

  for(i=1;i<=n;i++){
    printf("%d ",node_num[i]);
  }
  printf("\n");

  return 0;
}
