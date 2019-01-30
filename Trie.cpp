class Trie{
	public:
		void init(){
			memset(node,0,sizeof(node));
			tot=0;
		}
		void insert(char *s){
			int x=0,t;
			for(int i=0;i<strlen(s);i++){
				node[x].sum++;
				t=trans(s[i]);
				if(node[x].son[t]){
					x=node[x].son[t];
				}else{
					node[x].son[t]=++tot;
					x=tot;
				}
			}
			node[x].sum++;
			node[x].endwithit++;
		}
		int search(char *s){
			int x=0,t;
			for(int i=0;i<strlen(s);i++){
				t=trans(s[i]);
				if(node[x].son[t]){
					x=node[x].son[t];
				}else{
					return 0;
				}
			}
			return node[x].endwithit;
		}
		int ask(char *s){
			int x=0;
			for(int i=0;i<strlen(s);i++){
				int t=trans(s[i]);
				if(node[x].son[t]){
					x=node[x].son[t];
				}else{
					return 0;
				}
			}
			return node[x].sum;
		}
	private:
		struct node{
			int son[26];
			int sum;
			int endwithit;
		}node[maxn];
		int tot;
		int trans(char x){
			return x-'a';
		}
};
