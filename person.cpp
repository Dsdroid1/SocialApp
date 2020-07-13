#include<iostream>
#include<string>
#include<list>
#include<map>
#include<iterator>

using namespace std;

typedef enum {FAILURE,SUCCESS} status_code;
typedef enum {LEFT_UNBALANCE,BALANCED,RIGHT_UNBALANCED} Balance_factor;
//Note: LEFT_UNBALANCED woul mean Tree is skewed Left that ht(left_subtree)>ht(right_subtree).

class AVLTreeNode{
    public:
        int ID=-1;
        int visited=0;
        AVLTreeNode *left=NULL;
        AVLTreeNode *right=NULL;
        Balance_factor BF=BALANCED;

        //Functions
        AVLTreeNode* LeftRotate();
        AVLTreeNode* RightRotate();
};

class AVLTree{
    public:
        AVLTreeNode *root;
        status_code Insert(int ID);
        status_code Delete(int ID);
};





class Person{
    private:
        std::string Name;
        int Age;
        std::string School_Name;
        int Duration_at_school;
        std::string College_Name;
        int Duration_at_college;
        int UserID;
        std::string Password;
        list<std::string> Hobbies;

    public:
        //Some getters and setters
        void SetName(std::string Name){ this->Name=Name;}
        std::string GetName(){ return Name;}
        void SetAge(int Age){ this->Age=Age;}
        int GetAge(){ return Age;}
        void SetSchoolName(std::string School_Name){ this->School_Name=School_Name;}
        std::string GetSchoolName(){ return School_Name;}
        void SetCollegeName(std::string College_Name){ this->College_Name=College_Name;}
        std::string GetCollegeName(){ return College_Name;}
        void SetUserID(int ID){ this->UserID=ID;}
        int GetUserID(){ return UserID;}
        void SetPassword(std::string Password){ this->Password=Password;}
        std::string GetPassword(){ return Password;}
        
        void AddHobby(std::string Hobby_name){ Hobbies.push_back(Hobby_name);}
        status_code DeleteHobby(std::string Hobby_name)
        {
            list<std::string>::iterator iter=Hobbies.begin();
            status_code sc=FAILURE;
            while(iter!=Hobbies.end() && sc==FAILURE)
            {
                if(*iter==Hobby_name)
                {
                    sc=SUCCESS;
                    Hobbies.remove(Hobby_name);
                }
                iter++;
            }
            return sc;
        }

        Person(std::string Name,int Age,int UserID,std::string Password)
        {
            this->Name=Name;
            this->Password=Password;
            this->Age=Age;
            this->UserID=UserID;
        }
};

class GraphEdgeNode{
    private:
        GraphEdgeNode *next=NULL;
        int FriendID;
        GraphDataNode *jump=NULL;//To reach the corresponding DataNode

    public:
        void SetGraphDataNode(GraphDataNode *Data){ this->jump=Data;}
        void SetNextGraphEdgeNode(GraphEdgeNode *Edge){ this->next=Edge;} 
        void SetFriendID(int ID){ this->FriendID=ID;}
        int GetFriendID(){ return FriendID;}
        //To move through the linklist
        GraphEdgeNode* Advance()
        {
            if(this != NULL)
            {
                return this->next;
            }
        }
        GraphDataNode* GetDataNode()
        {
            if(this != NULL)
            {
                return this->jump;
            }
        }

};

class GraphDataNode{
    private:
        Person P;//All info regarding the Person
        GraphDataNode *down=NULL;//LinkList of DataNode of Person
        GraphEdgeNode *next=NULL;//Edgelist(linklist format) for this person

    public:
        Person GetUserInfo(){ return this->P;}
        void SetUserInfo(Person P){ this->P=P;}
        GraphEdgeNode* GetFriendList(){ return next;}
        GraphDataNode* GetNextUser(){ return down;}
        void SetFriendListPtr(GraphEdgeNode *list){ this->next=list;}
        void SetNextUser(GraphDataNode *down){ this->down=down;}
        status_code AddFriend(int UserID2,GraphDataNode *Users)
        {
            status_code sc=SUCCESS;
            int found=0;
            while(Users!=NULL && found==0)
            {
                if((Users->GetUserInfo).GetUserID==UserID2)
                {
                    found=1;
                }
                else
                {
                    Users=Users->GetNextUser();   
                }
            }
            //Now establish the links and make edgenodes...
            if(found==1)
            {
                GraphEdgeNode *User1,*User2;
                //This will follow insert at start,but check if already inserted
                User1=this->GetFriendList();
                User2=Users->GetFriendList();
                int exists=0;
                if(User1!=NULL)
                {
                    //Check if edge already exists
                    while(User1->Advance() != NULL && exists==0)
                    {
                        if(User1->GetFriendID()==UserID2)
                        {
                            exists=1;
                        }
                        else
                        {
                            User1=User1->Advance();   
                        }
                    }
                    if(exists==0)
                    {
                        User1=(GraphEdgeNode *)malloc(sizeof(GraphEdgeNode));
                        if(User1==NULL)
                        {
                            //Memory Error
                            sc=FAILURE;
                        }
                        else
                        {
                            User1->SetFriendID(UserID2);
                            User1->SetNextGraphEdgeNode(this->GetFriendList());
                            User1->SetGraphDataNode(Users);        
                            this->SetFriendListPtr(User1);
                        }
                    }
                }   
                else
                {
                    //Since this User doesnt have any friend,this edge can safely be added
                    //Now we can perform InsertAtStart
                    this->SetFriendListPtr((GraphEdgeNode *)malloc(sizeof(GraphEdgeNode)));
                    User1=this->GetFriendList();
                    if(User1==NULL)
                    {
                        //Memory Error
                        sc=FAILURE;
                    }
                    else
                    {
                        User1->SetNextGraphEdgeNode(NULL);
                        User1->SetFriendID(UserID2);
                        User1->SetGraphDataNode(Users);
                    }
                }
                if(exists==0)
                {
                    //Now add the reverse edge(undirected graph)
                    if(User2==NULL)
                    {
                        Users->SetFriendListPtr((GraphEdgeNode *)malloc(sizeof(GraphEdgeNode)));
                        User2=Users->GetFriendList();
                        if(User2==NULL)
                        {
                            sc=FAILURE;
                        }
                        else
                        {
                            User2->SetFriendID((this->GetUserInfo).GetUserID);
                            User2->SetGraphDataNode(this);
                            User2->SetNextGraphEdgeNode(NULL);
                        }
                    }
                    else
                    {
                        User2=(GraphEdgeNode *)malloc(sizeof(GraphEdgeNode));
                        if(User2!=NULL)
                        {
                            User2->SetNextGraphEdgeNode(Users->GetFriendList());
                            User2->SetFriendID((this->GetUserInfo).GetUserID);
                            User2->SetGraphDataNode(this);
                            Users->SetFriendListPtr(User2);
                        }
                        else
                        {
                            sc=FAILURE;
                        }
                    }
                }            
            }
            else
            {
                sc=FAILURE;
                //The second node does not exist.
            }
        }
        void DisplayAllConnections(Graph G)//Incomplete...
        {
            cout << "Friend(s):" << endl;
            GraphEdgeNode *FriendList=this->GetFriendList();
            GraphDataNode *Friend=NULL;
            while(FriendList != NULL)
            {
                cout << endl;
                Friend=FriendList->GetDataNode();
                cout << "Name of Friend:" <<(Friend->GetUserInfo).GetName() << endl;
                cout << "UserID of friend:" << (Friend->GetUserInfo).GetUserID() << endl;
                FriendList=FriendList->Advance();
            }
            cout << "Possible Connectons:" << endl;
            //Do a DFS....
            //Make a map
            map<int, int> visited;
                //Use a more reliable DS
                //Maybe use an AVL Tree(Self Implemented)
                //It will make search time O(logN) but reliable(No collision stuff)
            GraphDataNode *Users;
            Users=G.GetUserList();
            while(Users!=NULL)
            {
                visited.insert(pair<int, int>((Users->GetUserInfo()).GetUserID(),0));
                Users=Users->GetNextUser();
            }
            //But don't print the friends again... 
            //Require a modded DFS...
            //It can have an extra param such as isStartPoint to see if it should print or not...
            G.DFS(this,visited);
            
        }
};

class Graph{
    private:
        GraphDataNode *UserList=NULL;

    public:
        GraphDataNode* GetUserList(){ return UserList;}
        status_code AddUserAtEnd(Person P)
        {
            status_code sc=SUCCESS;
            GraphDataNode *Users=this->UserList;
            if(Users==NULL)
            {
                //No User Present as of now....
                UserList=(GraphDataNode *)malloc(sizeof(GraphDataNode));
                if(UserList!=NULL)
                {
                    UserList->SetNextUser(NULL);
                    UserList->SetFriendListPtr(NULL);
                    UserList->SetUserInfo(P);
                }
                else
                {
                    sc=FAILURE;
                }
            }
            else
            {
                while(Users->GetNextUser()!=NULL)
                {
                    Users=Users->GetNextUser();
                }
                Users->SetNextUser((GraphDataNode *)malloc(sizeof(GraphDataNode)));
                Users=Users->GetNextUser();
                if(Users!=NULL)
                {
                    Users->SetFriendListPtr(NULL);
                    Users->SetNextUser(NULL);
                    Users->SetUserInfo(P);
                }
                else
                {
                    sc=FAILURE;
                }
            }
            return sc;
        }

        status_code AddUserAtStart(Person P)
        {
            GraphDataNode *Users=UserList;
            status_code sc=SUCCESS;
            if(Users==NULL)
            {
                UserList=(GraphDataNode *)malloc(sizeof(GraphDataNode));
                if(UserList!=NULL)
                {
                    UserList->SetNextUser(NULL);
                    UserList->SetFriendListPtr(NULL);
                    UserList->SetUserInfo(P);
                }
                else
                {
                    sc=FAILURE;
                }
            }
            else
            {
                UserList=(GraphDataNode *)malloc(sizeof(GraphDataNode));
                if(UserList!=NULL)
                {
                    UserList->SetUserInfo(P);
                    UserList->SetFriendListPtr(NULL);
                    UserList->SetNextUser(Users);
                }
                else
                {
                    UserList=Users;
                    sc=FAILURE;
                }
            }
            return sc;
        }

        status_code AddEdge(int UserID1,int UserID2)
        {
            GraphDataNode *Users=UserList;
            //Find UserID1
            int found=0;
            status_code sc=SUCCESS;
            while(Users != NULL && found==0)
            {
                if((Users->GetUserInfo).GetUserID==UserID1)
                {
                    found=1;
                }
                else
                {
                    Users=Users->GetNextUser();
                }
            }
            if(found==1)
            {
                sc=Users->AddFriend(UserID2,UserList);
            }
            else
            {
                //One of the nodes does not exist
                sc=FAILURE;
            }
            return sc;
        }

        status_code DeleteID(int ID)
        {
            //First check if ID exists in the Graph
            GraphDataNode *Users=UserList,*prev=NULL;
            status_code sc=SUCCESS;
            int found=0;
            while(Users!=NULL && found==0)
            {
                if((Users->GetUserInfo).GetUserID==ID)
                {
                    found=1;
                }
                else
                {
                    prev=Users;
                    Users=Users->GetNextUser();   
                }
            }
            if(found==1)
            {
                //TO be DELETED
                //We wil try to delete the edges first
                GraphEdgeNode *Edgelist=Users->GetFriendList(),*toDelete=NULL;
                GraphEdgeNode *Friend_s_list=NULL,*friend_prev=NULL;
                GraphDataNode *Data=NULL;
                int friend_found=0;
                while(Edgelist != NULL && sc==SUCCESS)
                {
                    friend_found=0;
                    Data=Edgelist->GetDataNode();
                    Friend_s_list=Data->GetFriendList();
                    friend_prev=NULL;
                    while(Friend_s_list != NULL && friend_found==0)
                    {
                        if(Friend_s_list->GetFriendID == ID)
                        {
                            friend_found=1;
                        }
                        else
                        {
                            friend_prev=Friend_s_list;
                            Friend_s_list=Friend_s_list->Advance();
                        }
                    }
                    if(friend_found==1)
                    {
                        if(friend_prev==NULL)
                        {
                            //This was the first(latest node)
                            Data->SetFriendListPtr((Data->GetFriendList())->Advance());
                            free(Friend_s_list);
                        }
                        else
                        {
                            friend_prev->SetNextGraphEdgeNode(Friend_s_list->Advance());   
                            free(Friend_s_list);
                        }
                        //Now even delete from the ID node
                        toDelete=Edgelist;
                        Edgelist=Edgelist->Advance();
                        free(toDelete);
                    }
                    else
                    {
                        sc=FAILURE;
                    }
                    
                }
                if(sc==SUCCESS)
                {
                    //Now delete the ID node
                    if(prev==NULL)
                    {
                        UserList=Users->GetNextUser();
                    }
                    else
                    {
                        prev->SetNextUser(Users->GetNextUser());
                    }
                    free(Users);
                }
            }
            else
            {
                sc=FAILURE;//ID to be deleted does not exist
            }
            return sc;
        }
        
        //The Above functions are support some Basic Operations on the graph.
        //Next,Algorithms will be implemented.
        void Full_DFS()
        {
            GraphDataNode *Users=UserList;
            
            if(Users!=NULL)
            {
                
                //Also,initialize a HashMap to keep track of which IDs have been visisted
                map<int, int> visited;
                //Use a more reliable DS
                //Maybe use an AVL Tree(Self Implemented)
                //It will make search time O(logN) but reliable(No collision stuff)
                while(Users!=NULL)
                {
                    visited.insert(pair<int, int>((Users->GetUserInfo()).GetUserID(),0));
                    Users=Users->GetNextUser();
                }
                //0 signifies no node has been visited yet.
                Users=UserList;
                //Now start the algorithm for DFS
                while(Users != NULL)
                {
                    if(visited[(Users->GetUserInfo()).GetUserID()]==0)
                    {
                        DFS(Users,visited);
                    }
                    Users=Users->GetNextUser();
                }
            }
        }

        void DFS(GraphDataNode *curr,map<int,int> visited)
        {
            if(visited[(curr->GetUserInfo()).GetUserID]==0)
            {
                GraphEdgeNode *FriendList;
                visited[(curr->GetUserInfo()).GetUserID()]=1;
                cout << "Visited " << (curr->GetUserInfo()).GetUserID() << endl;
                FriendList=curr->GetFriendList();
                while(FriendList != NULL)
                {
                    if(visited[FriendList->GetFriendID()]==0)
                    {
                        DFS(FriendList->GetDataNode(),visited);
                    }
                    FriendList=FriendList->Advance();
                }
            }
        }
};