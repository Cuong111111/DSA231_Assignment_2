#include "main.h"
long long MAXSIZE;
template<typename E>
class heap{
    public:
    bool (*cmp)(E left,E right);
    E* Heap;
    int maxsize;
    int n;
    void siftdown(int pos){
        while(isLeaf(pos)==0){
            int lc = leftchild(pos);
            int rc = rightchild(pos);
            int min=lc;
            if((rc<n)&&cmp(Heap[rc],Heap[lc])) min = rc;
            if(cmp(Heap[pos],Heap[min]))return;
                E a = Heap[min];
                Heap[min]=Heap[pos];
                Heap[pos]=a;
            pos = min;

        }
    }
    heap(E* h, int num,int max,bool (*cmp)(E left,E right)){
        Heap = h;
        n = num;
        maxsize = max;
        this->cmp = cmp;
        buildHeap();
    }
    int size(){return n;}
    bool isLeaf(int pos){return (pos>= n/2)&& (pos<n);}
    int leftchild(int pos){return 2*pos+1;}
    int rightchild(int pos){return 2*pos+2;}
    int parent(int pos){return (pos-1)/2;}
    void buildHeap(){
        for(int i = n/2-1;i>=0;i--){
          
            siftdown(i);
            }
    }
    
    void insert(E& it){
        if(n>= maxsize) return;
        int curr = n++;
        Heap[curr]=it;
        while((curr!=0)&&(cmp(Heap[curr],Heap[parent(curr)]))){
            E a = Heap[curr];
            Heap[curr]= Heap[parent(curr)];
            Heap[parent(curr)] = a;
            curr = parent(curr);
        }
    }
    E removefirst(){
        if(n==0) return nullptr;
        E a = Heap[n-1];
        Heap[n-1]= Heap[0];
        Heap[0] = a;
        n--;
        if(n >  0){  
            siftdown(0);
        }
        return Heap[n];        
    }
    E remove(int pos){
        if(pos == n-1) n--;
        else{
            E a = Heap[n-1];
            Heap[n-1]= Heap[pos];
            Heap[pos] = a;
            n--;
            while((pos!=0)&&(cmp(Heap[pos],Heap[parent(pos)]))){
                E a = Heap[pos];
                Heap[pos]= Heap[parent(pos)];
                Heap[parent(pos)] = a;
                pos = parent(pos);
            }
            if(n!=0) siftdown(pos);
        }
        return Heap[n];
    }
};

class HuffNode{
    public:
    string way;
    char it;
    char old;
    int wgt;
    int thutu;
    int height;
    HuffNode *lc;
    HuffNode *rc;
    bool leaf;
    ~HuffNode(){}
    HuffNode(char & val, int freq){
        it = val;wgt=freq;
        height=1;
        lc = nullptr;
        rc = nullptr;
        leaf =1;
    }
    HuffNode( HuffNode *l, HuffNode *r){
        wgt = l->weight()+r->weight();
        it = '!';
        height=1;
        lc=l;
        rc=r;
        leaf =0;
    }
    char val(){return it;}
    int weight() {return wgt;};
    bool isLeaf(){return leaf;}
    
};
class HuffTree{
public:
HuffNode *Root;
HuffNode * root(){return Root;}
int weight(){return Root->weight();}
HuffTree(char&val,int freq){
    Root = new HuffNode(val,freq);
}
HuffTree(HuffTree*l,HuffTree*r){
    Root = new HuffNode(l->root(),r->root());
    Root->height = max(l->Root->height,r->Root->height)+1;
       bool check =0;
    for(int i=0;i<3;i++) {
        check=0;
        Root = preorderBalance(Root,check);
    }
    //correct(Root);
}
HuffTree(HuffNode *node){
    Root = node;
}
~HuffTree(){
};
HuffNode* preorderBalance(HuffNode*&node,bool & check){
    if(node == nullptr) return nullptr;
    //if(k==3) return node;
    //cout << node->height  <<'-';
    //if(node->lc!=nullptr)cout<< node->lc->height  <<'-';
    //if(node->rc!=nullptr)cout<< node->rc->height  <<'-';
    //cout<<k<<'\n';
    if(Balance(node)>1||Balance(node)<-1) {
        if(Balance(node)>1 && Balance(node->lc)>=0){
            node = rotateRight(node);
            check = 1;
            return node;
        }
        else if(Balance(node)>1 && Balance(node->lc)<=-1){
            node->lc=rotateLeft(node->lc);
            node = rotateRight(node); 
            check =1;
            return node;
        }
        else if(Balance(node)<-1 && Balance(node->rc)<=0){
            node = rotateLeft(node);
            check=1;
            return node;
        }
        else if(Balance(node)<-1 && Balance(node->rc)>=1){
            node->rc=rotateRight(node->rc);
            node = rotateLeft(node);
            check = 1;
            return node;
        }
    }
    if(check==0) node->lc = preorderBalance(node->lc,check);
    if(check==0) node->rc =preorderBalance(node->rc,check);
    if(node->leaf==0)  node->height=max(node->lc->height,node->rc->height)+1;
    return node;
}
HuffNode * rotateLeft(HuffNode * node){
    HuffNode * cur = node->rc;
    node->rc = cur->lc;
    cur->lc = node;
    node->height=max(node->lc->height,node->rc->height)+1;
    cur->height = max(cur->lc->height,cur->rc->height)+1;
    return cur;
}
HuffNode * rotateRight(HuffNode * node){
    HuffNode * cur = node->lc;
    node->lc = cur->rc;
    cur->rc = node;
    node->height=max(node->lc->height,node->rc->height)+1;
    cur->height = max(cur->lc->height,cur->rc->height)+1;
    return cur;
}
int Balance(HuffNode*node){
    if(node == nullptr) return 0;
    if(node->leaf==1) return 0;
    return node->lc->height - node->rc->height;
}

void PrintInOrder(HuffNode * node){
    if(node == nullptr) return;
    PrintInOrder(node->lc);
    if(node->leaf) cout << node->it <<'\n';
    else cout << node->wgt<<'\n';
    PrintInOrder(node->rc);
}
void printinorder(){
    PrintInOrder(Root);
}
void correct(HuffNode *node){
    if (node == nullptr) return;
    if(node->leaf==1) return;
    correct(node->lc);
    correct(node->rc);
    node->wgt=node->lc->wgt+node->rc->wgt;
}
};

bool Compare(HuffTree *left,HuffTree *right) {
    bool a=0;
    if(left->weight() < right->weight()) a=1;
    else if(left->weight() == right->weight() && right->Root->thutu > left->Root->thutu)a=1;
    return a;
}
void Swap(HuffTree *left,HuffTree*right){
    HuffNode* a = left->Root;
 //   cout<< left->weight()<<' '<<right->weight()<<'\n';
    left->Root=right->Root;
    right->Root=a;
}
void buildWay(HuffNode* node,string a){
    if(node== nullptr) return;
    buildWay(node->lc,a+'0');
    buildWay(node->rc,a+'1');
    if(node->isLeaf()) node->way=a;
}
HuffTree*buildHuff(HuffTree**TreeArray,int count,bool & error){
    heap<HuffTree*> *forest = new heap<HuffTree*>(TreeArray,count,count,Compare);
 //  for(int i =0;i<forest->n;i++)
    //cout<<TreeArray[i]->Root->it  <<TreeArray[i]->Root->wgt<<TreeArray[i]->Root->thutu<<" va ";
    long long k=count;
    HuffTree *temp1,*temp2,*temp3=nullptr;
    if(count == 1) temp3 = forest->Heap[0]; 
    while(forest->n>1){
        
        temp1 = forest->removefirst();
        temp2 = forest->removefirst();
        temp3 = new HuffTree(temp1,temp2);
        temp3->Root->thutu=k;k++;
        forest->insert(temp3);
       delete temp1;
       delete temp2;
       if(temp3->Root->it !='!') error = 1;
    }
    //temp3->correct(temp3->Root);
    buildWay(temp3->Root,"");
    temp3->Root->way="0";
    return temp3;
}


 class Node{
    public:
    int val;
    Node * next;
    Node *prev;
    Node(int b){
        val = b;
        next = nullptr;
        prev = nullptr;
        }
};

class doublelist{
public:
    Node* head;
    Node* tail;
    int size;
    doublelist(){
        size = 0;
        head = nullptr;
        tail = nullptr;
    }
    ~doublelist(){
        removeall();
    }
    void addback(int val){
        Node* a = new Node(val);
        if(tail==nullptr){
            head = a;
            tail = a;
        } else{
            tail->next = a;
            a->prev = tail;
            tail = a;
        }
        size++;
    }
    void addfront(int val){
        Node* a = new Node(val);
        if(head==nullptr){
            head = a;
            tail = a;
        } else{
            head->prev = a;
            a->next = head;
            head = a;
        }
        size++;
    }
    void removefront(){
        Node* remove = head;
        if(head == nullptr) return;
        head = head->next;
        if(head!=nullptr)head->prev = nullptr;
        size--;
        delete remove;
        if(size==0){
            head = nullptr;
            tail = nullptr;
        }
    }
    void removeback(){
        Node* remove = tail;
        if(tail == nullptr) return;
        tail = tail->prev;
        if(tail!=nullptr)tail->next= nullptr;
        size--;
        delete remove;
        if(size==0){
            head = nullptr;
            tail = nullptr;
        }
    }
    void removeall(){
        Node* cur = head;
        while(cur !=nullptr){
            Node * dltNode = cur;
            cur = cur->next;
            delete dltNode;
        }
        head = nullptr;
        tail = nullptr;
        size =0;
    }
};

class BSTTree{
public:
    class BSTNode{
    public:
    int value;
    BSTNode*left;
    BSTNode*right;
    BSTNode(int val){
        value=val;
        left = nullptr;
        right = nullptr;
    }
    ~BSTNode(){}
};
long long count;
BSTNode * root;
doublelist * orderlist;
BSTTree(){
    count=0;
    orderlist = new doublelist();
    root = nullptr;
}
~BSTTree(){
    deleteall(root);
    orderlist->removeall();
}
void deleteall(BSTNode*tree){
    if(tree == nullptr)return;
    deleteall(tree->left);
    deleteall(tree->right);
    delete tree;
}
void addorder(int val){
    orderlist->addback(val);
}
void addBST(int val){
    BSTNode * newnode = new BSTNode(val);
    count++;
    addorder(val);
    BSTNode* cur = root;
    BSTNode* parent = nullptr;
    if(root == nullptr) {root = newnode;return;}
    while(cur!=nullptr){
        parent=cur;
        if(val<cur->value)cur =cur->left;
        else cur = cur->right; 
    }
    if(val<parent->value)parent->left=newnode;
    else parent->right=newnode; 
}
BSTNode* deleteBSTNode(BSTNode * tree,int val){
    if(tree == nullptr) return tree;
    if(val<tree->value) tree->left=deleteBSTNode(tree->left,val);
    else if(val>tree->value) tree->right=deleteBSTNode(tree->right,val);
    else{
        if(tree->left==nullptr){
            BSTNode * dlttree = tree;
            tree = tree->right;
            delete dlttree;
            return tree;
        } else if(tree->right==nullptr){
            BSTNode * dlttree = tree;
            tree = tree->left;
            delete dlttree;
            return tree;
        }
        if(tree->left!=nullptr&&tree->right!=nullptr){
            BSTNode * dlttree=tree->right;
            while(dlttree->left!=nullptr)dlttree=dlttree->left;
            tree->value=dlttree->value;
            tree->right=deleteBSTNode(tree->right,tree->value);
        }
    }
    return tree;
}
void deleteBST(int val){
    root = deleteBSTNode(root,val); 
}
void deleteFIFO(){
if(orderlist->size==0) return;
 int a = 0;
 a=orderlist->head->val;
 orderlist->removefront();
 deleteBST(a);
}
int countchau(BSTNode* tree){
    if (tree == nullptr) return 0;
    return countchau(tree->left) + countchau(tree->right)+1;
}
void printInOrder(BSTNode*tree){
    if(tree == nullptr) return;
    printInOrder(tree->left);
    cout << tree->value<<'\n';
    printInOrder(tree->right);
}
void printIn(){
    printInOrder(root);
}
long long nCk(long long n,long long k){
   long long* arr = new long long [k+1];
    for(long long i =0;i<=k;i++){
        arr[i]=0;
    }
    arr[0]=1;
    for(long long i =1;i<=n;i++){
        for(long long j = min(i,k);j>0;j--){
            arr[j]=(arr[j]+arr[j-1])%MAXSIZE;
        }
    }
    long long a = arr[k]%MAXSIZE;
    delete[] arr;
    return a;
}
long long hoanvi(BSTNode*tree){
   if(tree==nullptr)return 1;
    long long left=countchau(tree->left);
    long long right = countchau(tree->right);
    long long sum = left + right;
    long long s= nCk(sum,left);
    return ((s * hoanvi(tree->left))%MAXSIZE * hoanvi(tree->right))%MAXSIZE;
}
};

class Gojo{
    public:
    BSTTree * Area;
    Gojo(){
    Area = new BSTTree[MAXSIZE+1];
    }
    ~Gojo(){
        delete[] Area;
    }
    void InsertArea(int val,int ID){
            Area[ID].addBST(val);
    }
    void kokusen(){
        for(int i =1;i<=MAXSIZE;i++){
            long long a = Area[i].hoanvi(Area[i].root)%MAXSIZE;
            //cout << i << '-' << a << '-'<<Area[i].count <<' ';
            if(a> Area[i].count) a = Area[i].count;
            for(int j =0;j<a;j++)Area[i].deleteFIFO();
        }
    }
};
class SukunaArea{
       public:
        long long pos;
        SukunaArea(){
            pos = -1;
        }
        ~SukunaArea(){}
    };
class SukunaNode{
    public:
    long long thutu;
    long long count;
    long long ID;
    doublelist *list;
    SukunaNode(){
        count = 0 ;
        ID = -1;
        list = new doublelist();
    }
    ~SukunaNode(){
        list->removeall();
    }
};  
bool CompareSukuna( SukunaNode left, SukunaNode right) {
    bool a=0;
    if(left.count < right.count) a=1;
    else if(left.count == right.count && right.thutu > left.thutu)a=1;
    return a;
}
class Sukuna{
    public:
    long long order;
    int n;
    int maxsize;
    SukunaArea *Area;
    SukunaNode * Heap;
    Sukuna(){
        n=0;order =0;
        maxsize= MAXSIZE;
        Heap = new SukunaNode[MAXSIZE];
        Area = new SukunaArea[MAXSIZE+1];
    }
    ~Sukuna(){
        delete[] Heap;
        delete[] Area;
    }
    bool isLeaf(int pos){return (pos>= n/2)&& (pos<n);}
    int leftchild(int pos){return 2*pos+1;}
    int rightchild(int pos){return 2*pos+2;}
    int parent(int pos){return (pos-1)/2;}
    void swap(long long pos1,long long pos2){
        Area[Heap[pos1].ID].pos = pos2;
        Area[Heap[pos2].ID].pos = pos1;
        long long a = Heap[pos1].count;
        Heap[pos1].count=Heap[pos2].count;
        Heap[pos2].count=a;
        long long b = Heap[pos1].ID;
        Heap[pos1].ID=Heap[pos2].ID;
        Heap[pos2].ID=b;
        doublelist *c= Heap[pos1].list;
        Heap[pos1].list=Heap[pos2].list;
        Heap[pos2].list=c;
        long long d = Heap[pos1].thutu;
        Heap[pos1].thutu=Heap[pos2].thutu;
        Heap[pos2].thutu=d;
    }
    void reheapdown(int pos){
        while(isLeaf(pos)==0){
            int lc = leftchild(pos);
            int rc = rightchild(pos);
            int min=lc;
            if(rc<n){ 
                if(Heap[rc].count<Heap[lc].count) min = rc;
                else if(Heap[rc].count == Heap[lc].count && Heap[rc].thutu < Heap[lc].thutu ) min = rc;
            }
            if((Heap[pos].count<Heap[min].count))return;
            else if(Heap[pos].count == Heap[min].count && Heap[pos].thutu < Heap[min].thutu ) return;
                swap(pos,min);
                pos = min;
        }
    }
    void reheapup(int pos){
         int curr = pos;
        while((curr!=0)&&((Heap[curr].count<Heap[parent(curr)].count)||(Heap[curr].count == Heap[parent(curr)].count && Heap[curr].thutu < Heap[parent(curr)].thutu))){
            swap(curr,parent(curr));
            curr = parent(curr);
        }
    }
    void insert(int it,int ID,int result){
        if(n>= maxsize) return;
        int curr = n;
        Area[ID].pos=curr;
        n++;
        Heap[curr].count=it;
        Heap[curr].ID=ID;
        Heap[curr].thutu = order;order++;
        Heap[curr].list->addback(result);
        reheapup(curr);
    }
    void increase(int pos, int result){
        Heap[pos].count++;
        Heap[pos].thutu = order;order++;
        Heap[pos].list->addback(result);
        reheapdown(pos);
    }
    void AddArea(int ID,int result){
        long long pos = Area[ID].pos;
        if(pos==-1) insert(1,ID,result) ;
        else increase(pos,result); 
    }
    void remove(long long pos){
        if(pos == n-1) {n--;}
        else{
            swap(pos,n-1);
            n--;
            reheapup(pos);
            if(n!=0) reheapdown(pos);
        }
         for(long long i =0;i<Heap[n].count;i++) {
            cout << Heap[n].list->head->val<<'-'<<Heap[n].ID <<'\n';
            Heap[n].list->removefront();
        }
        Heap[n].count=0;
        Heap[n].thutu=-1;
        Area[Heap[n].ID].pos =-1;
    }
    void decrease(long long pos, long long num){
        Heap[pos].count -= num ;
        Heap[pos].thutu=order;order++;
        for(long long i =0;i<num;i++) {
            cout << Heap[pos].list->head->val<<'-'<<Heap[pos].ID <<'\n';
            Heap[pos].list->removefront();
        }
    //    reheapup(pos);
    //    if(n!=0) reheapdown(pos);
    }
    void RemoveArea(int pos,int num){
    //  cout << pos<<' '<<num<<" "<<Heap[pos].count <<'\n';
        if(num>=Heap[pos].count) remove(pos); 
        else decrease(pos,num);
    }
    void printpreorder(int pos,int num){
        if(pos>=n) return;   
       int a =0;
        Node* current = Heap[pos].list->tail;
        while(current!=nullptr){
        cout <<Heap[pos].ID<<'-'<< current->val<<'\n';
        current = current->prev;
        a++;
        if(a==num) break;
        }
      //  cout << Heap[pos].ID << ' ' << Heap[pos].count<<'\n';
        printpreorder(leftchild(pos),num);
        printpreorder(rightchild(pos),num);
    }
    void printpre(int num){
        //for(int i=0;i<MAXSIZE;i++){
        //    if (Area[i].pos!=-1) cout <<i <<'-'<<Area[i].pos<<' ';
        //}
        if(num<=0) return;
        printpreorder(0,num);
    } 
    void keiteiken(int num){
        SukunaNode*list = new SukunaNode[n];
        for(int i =0;i<n;i++){
            list[i].ID=Heap[i].ID;
           list[i].count=Heap[i].count;
           list[i].thutu=Heap[i].thutu;
        }
        sort(list,list+n,CompareSukuna);
        //for(int i =0;i<n;i++){
        //    cout << list[i].ID<<'-'<<Area[list[i].ID].pos<<' ';
        //}
        //cout <<'\n';
        int k=num;
        if(num>n) k=n;
        //cout <<"k="<<k<<'\n';
        for(int i =0;i<k;i++){
         RemoveArea(Area[list[i].ID].pos,num);
       //  printpre(0);
        }
        delete[]list;
    }
};

struct letter{
    char kitu;
    char newkitu;
    int soluong;
    letter(){
        soluong=0;
    }
};

void swap(letter * let1,letter *let2){
    char a = let1->kitu; 
    let1->kitu= let2->kitu;
    let2->kitu = a;
    int b = let1->soluong;
    let1->soluong = let2->soluong;
    let2->soluong = b;
}
class Restaurant{
public:
Gojo * GojoRestaurant;
Sukuna * SukunaRestaurant;
HuffTree * HuffRoot;
HuffNode** Huffnode;
Restaurant(){
    GojoRestaurant= nullptr;
    SukunaRestaurant = nullptr;
    HuffRoot = nullptr;
    Huffnode = nullptr;
}
~Restaurant(){
    delete GojoRestaurant;
    delete SukunaRestaurant;
    delete HuffRoot;
    delete[] Huffnode;
}
void LAPSE(string name){
    long long len = name.length();
    letter * lett = new letter[1000]; 
    int tong=0;
    for(long long i=0;i<len;i++){
        bool a=0;
        for(int j=0;j<tong;j++){
            if(lett[j].kitu==name[i]){
                lett[j].soluong ++;
                a=1;
                break;
            }
        }
        if(a==0){
            lett[tong].kitu=name[i];
            lett[tong].soluong = 1;
            tong++;
        }
    }
    if(tong<3) {
        delete[]lett;
        return;
    }
    for(int j=0;j<tong;j++){
        int mahoa = lett[j].kitu + lett[j].soluong%26;
        if (lett[j].kitu>=97&&lett[j].kitu<=122){
            if(mahoa>=97&&mahoa<=122) lett[j].newkitu = mahoa;
            else lett[j].newkitu=mahoa-26; 
        }
        else if(lett[j].kitu>=65&&lett[j].kitu<=90){
             if(mahoa>=65&&mahoa<=90) lett[j].newkitu = mahoa;
            else lett[j].newkitu=mahoa-26; 
        }
	}
    letter * mahoa = new letter[1000];
    int newtong=0; 
    for(long long i=0;i<tong;i++){
        bool a=0;
        for(int j=0;j<newtong;j++){
            if(mahoa[j].kitu==lett[i].newkitu){
                mahoa[j].soluong +=lett[i].soluong;
                a=1;
                break;
            }
        }
        if(a==0){
            mahoa[newtong].kitu=lett[i].newkitu;
            mahoa[newtong].soluong = lett[i].soluong;
            newtong++;
        }
    }
    
    int current =0;
    bool flag =0;
    while(current<newtong&& flag ==0){
        int walker = newtong - 1;
        flag = 1;
        while(walker>current){
            if(mahoa[walker].soluong<mahoa[walker-1].soluong){
                flag =0;
                swap(mahoa[walker],mahoa[walker-1]);
            } else if(mahoa[walker].soluong== mahoa[walker-1].soluong){
                int s1 = mahoa[walker].kitu;
                int s2 =  mahoa[walker-1].kitu;
                if(s1 >90) s1 -=58;
                if(s2>90) s2 -=58;
                if (s1< s2){
                flag =0;
                swap(mahoa[walker],mahoa[walker-1]);
                }
            }
            walker--;
        }
        current ++;
    }
    //for(int i=0;i<newtong;i++)    cout << mahoa[i].kitu <<'-'<< mahoa[i].soluong<<' ';
    //cout <<'\n';
    HuffNode** node = new HuffNode*[newtong];
    HuffTree** tree = new HuffTree*[newtong];
    for(int i=0;i<newtong;i++){
        node[i]= new HuffNode(mahoa[i].kitu,mahoa[i].soluong);
        node[i]->thutu=i;
        tree[i] = new HuffTree(node[i]);
    }
    bool check = 0;
    HuffTree* root = buildHuff(tree,newtong,check);
    if(check == 1) {
        delete[] lett;
        delete[] mahoa;
        delete[] node;
        delete root;
        return;
    }
 //   buildWay(root->Root,"");
    if(HuffRoot!=nullptr) {
        delete HuffRoot;
        delete[] Huffnode;
        HuffRoot = nullptr;
    }
    HuffRoot = root;
    Huffnode = node;
   // cout << HuffRoot->Root->wgt <<'\n';
    //cout <<'\n';
    //  for(int i=0;i<newtong;i++){
    // cout << node[i]->it <<' '<< node[i]->way<<'\n';
    //}
    string so;
    for(int i = len-1;i>=0;i--){
        char a;
        for(int j=0;j<tong;j++){
            if(name[i]==lett[j].kitu) a = lett[j].newkitu;
        }
        for(int j=0;j<newtong;j++){
            if(a==node[j]->it) so = node[j]->way + so;
        }
        if((int)so.length()>=10) break;
    }
    string newso;
    int k =1,dem=0;
    int result =0;
    int solen=so.length();
    for(int i = solen-1;i>=0;i--){
        dem++;
        newso +=so[i];
        if(dem==10) break;
    }
    dem =0;
    solen = newso.length();
    for(int i= solen-1;i>=0;i--){
        dem++;
        result +=(newso[i]-'0')*k;
        k*=2;
        if(dem == 10) break;
    }

    int ID = result%MAXSIZE+1;
//    cout  << result<<' ' <<ID<<' ';
    if(result % 2==1){
        GojoRestaurant->InsertArea(result,ID);
     //   cout << "Gojo\n";
        }
    else {
        SukunaRestaurant->AddArea(ID,result);
        //cout << "Sukuna\n";
        }
    delete[] lett;
    delete[] mahoa;
}

};


void simulate(string filename)
{	
		Restaurant* res= new Restaurant();
	ifstream ss(filename);
	string str,maxsize,name,num;
	long long NUM;
	while(ss >> str)
	{ 
		if(str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize);
			res->GojoRestaurant = new Gojo();
			res->SukunaRestaurant = new Sukuna(); 
    	}
        else if(str == "LAPSE")
        {
          //  cout << "LAPSE" <<'\n';
            ss >> name;
			res->LAPSE(name);
    	}
    	else if(str == "KOKUSEN") 
    	{   
           // cout <<"KOKUSEN"<<'\n';
            res->GojoRestaurant->kokusen();
		}
    	else if(str == "KEITEIKEN")
    	{   
    		ss >> num;
			NUM = stoi(num);
           // cout <<"KEITEIKEN "<<NUM<<'\n';
            res->SukunaRestaurant->keiteiken(NUM);
		}
		else if(str == "HAND") 
		{  // cout <<"HAND"<<'\n';
            if(res->HuffRoot!=nullptr) res->HuffRoot->printinorder();
		}
    	else if(str == "LIMITLESS")
     	{   
			ss >> num;
			NUM = stoi(num);
            //cout << "LIMITLESS" <<' ' <<NUM <<'\n';

            if(NUM<=MAXSIZE &&NUM>=0)res->GojoRestaurant->Area[NUM].printIn();
    	}
    	else if(str == "CLEAVE")
    	{   
    		ss >> num;
			NUM = stoi(num);
           // cout << "CLEAVE" << " " << NUM<<'\n';
            res->SukunaRestaurant->printpre(NUM);
    	}
    }
    delete res;
	return;
}