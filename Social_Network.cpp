#include<iostream>
#include<vector>
#include "Set.h"
#include <unordered_map>

using namespace std;

Set users_list = Set();
unordered_map<int, Set> friends_map; 

/*returns the id of the user created*/
int create_user()
{
    int s = users_list.get_size();
    if(s==0)
    {
        users_list.insert(0);
        friends_map[0] = Set();
        return 0;
    }
    int last_user = users_list.find_kth_smallest(s);
    int new_user = last_user+1;
    users_list.insert(new_user);
    friends_map[new_user] = Set();
    return new_user;
}

int add_friend(int user, int new_friend)
{
    if(!users_list.find_element(user) || !users_list.find_element(new_friend))
    {
        return 0;
    }
    if(friends_map.find(user)==friends_map.end() || friends_map.find(new_friend)==friends_map.end())
    {
        return 0;
    }
    Set user1_friends = friends_map[user];
    Set user2_friends = friends_map[new_friend];
    user1_friends.insert(new_friend);
    user2_friends.insert(user);
    friends_map[user] = user1_friends;
    friends_map[new_friend] = user2_friends;
    return 1;
}

/*INTERSECTION APPLICATION*/

vector<int> get_mutual_friends(int user1, int user2)
{
    if(!users_list.find_element(user1) || !users_list.find_element(user2))
    {
        vector<int> v;
        return v;
    }
    if(friends_map.find(user1)==friends_map.end() || friends_map.find(user2)==friends_map.end())
    {
        vector<int> v;
        return v;
    }
    Set uf1 = friends_map[user1];
    Set uf2 = friends_map[user2];
    Set mutual_friends = uf1.INTERSECTION(uf2);
    return mutual_friends.get_elements();
}

/*UNION APPLICATION*/

vector<int> get_friend_suggestions(int user)
{
    if(!users_list.find_element(user) || friends_map.find(user)==friends_map.end())
    {
        vector<int> v;
        return v;
    }
    Set uf = friends_map[user];
    vector<int> user_friends = uf.get_elements();
    Set suggested_friends = Set();
    for(int i=0; i<user_friends.size(); i++)
    {
        int fr = user_friends[i];
        Set second_friends = friends_map[user_friends[i]];
        suggested_friends = suggested_friends.UNION(second_friends);
    }
    Set temp_set = Set();
    temp_set.insert(user);
    suggested_friends = suggested_friends.DIFFERENCE(temp_set);
    suggested_friends = suggested_friends.DIFFERENCE(uf);
    return suggested_friends.get_elements();
}

vector<int> get_exclusive_friends(int user)
{
    if(!users_list.find_element(user) || friends_map.find(user)==friends_map.end())
    {
        vector<int> v;
        return v;
    }
    Set uf = friends_map[user];
    vector<int> user_friends = uf.get_elements();
    for(int i=0; i<user_friends.size(); i++)
    {
        Set x = friends_map[user_friends[i]];
        uf = uf.DIFFERENCE(x);
    }
    return uf.get_elements();
}

vector<int> get_users_list()
{
    return users_list.get_elements();
}

void print_users_list()
{
    vector<int> ul = get_users_list();
    cout<<endl;
    for(int i=0; i<ul.size(); i++)
    {
        cout<<ul[i]<<" ";
    }
    cout<<endl;
}

void print_network()
{
    for(unordered_map<int,Set>::iterator it = friends_map.begin(); it!=friends_map.end(); ++it)
    {
        int user = it->first;
        Set friends = it->second;
        cout<<endl;
        cout<<user<<" : ";
        vector<int> friend_list = friends.get_elements();
        for(int i=0; i<friend_list.size(); i++)
        {
            cout<<friend_list[i]<<" ";
        }
        cout<<endl;
    }
}


int main()
{

    int option = -1;
    cout<<"\n1. Create user\n2. Add friend\n3. View mutual friends\n4. Get friend suggestions\n5. View exclusive friends\n6. View entire network\n7. Exit\n";
    cin>>option;
    while(option!=7)
    {
        if(option==1)
        {
            int new_user = create_user();
            cout<<"\nNew user added"<<new_user<<"\n";
        }
        else if(option==2)
        {
            int user1, user2;
            cout<<"\nEnter user1: ";
            cin>>user1;
            cout<<"\nEnter user2: ";
            cin>>user2;
            int succ = add_friend(user1, user2);
            if(succ)
            {
                cout<<"\nFriends added successfully\n";
            }
            else
            {
                cout<<"\nSomething went wrong in adding friends\n";
            }
        }
        else if(option==3)
        {
            int user1, user2;
            cout<<"\nEnter the user1: ";
            cin>>user1;
            cout<<"\nEnter the user2: ";
            cin>>user2;
            vector<int> mf = get_mutual_friends(user1, user2);
            cout<<"\nMutual friends : ";
            for(int i=0; i<mf.size(); i++)
            {
                cout<<mf[i]<<" ";
            }
            cout<<endl;
        }
        else if(option==4)
        {
            int user;
            cout<<"\nEnter the user : ";
            cin>>user;
            vector<int> suggestions = get_friend_suggestions(user);
            cout<<endl<<endl;
            for(int i=0; i<suggestions.size(); i++)
            {
                cout<<suggestions[i]<<" ";
            }
            cout<<endl<<endl;
        }
        else if(option==5)
        {
            int user;
            cout<<"\nEnter the user : ";
            cin>>user;
            vector<int> ex_fr = get_exclusive_friends(user);
            cout<<endl<<endl;
            for(int i=0; i<ex_fr.size(); i++)
            {
                cout<<ex_fr[i]<<" ";
            }
            cout<<endl<<endl;
        }
        else if(option==6)
        {
            print_network();
        }
        cout<<"\n1. Create user\n2. Add friend\n3. View mutual friends\n4. Get friend suggestions\n5. View exclusive friends\n6. View entire network\n7. Exit\n";
        cin>>option;
    }

    return 0;
}