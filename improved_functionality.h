#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<vector>
using namespace std;
class MajorUsedFunctions
{
public:
    string user_name_file_path = "user.txt";
    string user_friend_file_path = "_friend.txt";
    string user_post_file_path = "_post.txt";
    string post_description_file_path = "_post_description.txt";
    string user_likedPosts_file_Path = "_liked_posts.txt";
    string user_comment_file_path = "_comment.txt";
    string comment_post_file_path = "_comment_post.txt";
    string comment_description_file_path = "_comment_description.txt";
    string page_title_file_path = "_page.txt";
    string page_description_file_path = "_page_desc.txt";
    string user_owner_page_file_path = "_page_owner.txt";
    string post_owner_file_path = "_owner_post.txt";
    string post_comments_file_path = "post_comments.txt";
    string post_likedusers_file_path = "_post_liked_count.txt";
    string page_owner_file_path = "_page_owner_PG_O.txt";
    string timeline_file_path = "timeline.txt";
    bool DuplicateCheck(const string& _file_path, const string& _search)
    {
        ifstream file(_file_path);
        string _temp;
        while (file >> _temp)
        {
            if (_temp == _search)
            {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    void Tokenizer(string& _n)
    {
        for (int i = 0; i < _n.length(); i++)
        {
            if (_n[i] == ' ')
            {
                _n[i] = '_';
            }
        }
    }
    void Detokenizer(string& _n)
    {
        for (int i = 0; i < _n.length(); i++)
        {
            if (_n[i] == '_')
            {
                _n[i] = ' ';
            }
        }
    }
    string IDassigner(const string& parent_id, const string& file_path)
    {
        srand(time(0));
        string temp_child_id;
        do
        {
            temp_child_id = parent_id;
            temp_child_id += to_string(1 + rand() % 9999);
        } while (DuplicateCheck(file_path, temp_child_id));
        return temp_child_id;
    }
    string NextGetter(const string& _search, const string& file_path)
    {
        ifstream file(file_path, ios::in);
        string _temp;
        while (file >> _temp)
        {
            if (_temp == _search)
            {
                file >> _temp;
                file.close();
                Detokenizer(_temp);
                return _temp;
            }
        }
        file.close();
        return "";
    }
    int OccurenceCounter(const string& _search, const string& file_path)
    {
        int counter = 0;
        ifstream file(file_path,ios::in);
        string _temp;
        while (file >> _temp)
        {
            if (_temp == _search)
            {
                ++counter;
            }
        }
        file.close();
        return counter;
    }
    void DeletePTR(vector<string>& _array)
    {
        _array.clear();
    }
    void getwhatever(string filepath, vector<string>& storage, string search_word)
    {
        ifstream file(filepath,ios::in);
        string _temp;
        while (file >> _temp)
        {
            if (storage.size() + 1 >= storage.capacity())
            {
                storage.resize(storage.size() + 1);
            }
            if (_temp == search_word)
            {
                file >> _temp;
                storage.push_back(_temp);
            }
        }
        file.close();
    }

    void addfriend(string ID, string ID2)
    {
        string temp = "F-";
        temp += ID;
        string _temp = "F-";
        _temp += ID2;
        ofstream file(user_friend_file_path,ios::app);
        file << ID << ' ' << _temp << '\n' << ID2 << ' '<<temp << '\n';
        file.close();
    }
    void writetofile(string filepath,string firxt,string second)
    {
        ofstream file(filepath, ios::app);
        Tokenizer(firxt);
        Tokenizer(second);
        file << firxt << ' ' << second << '\n';
        file.close();
        Detokenizer(firxt);
        Detokenizer(second);
    }
};
class User : public MajorUsedFunctions
{
public:
    string name = "default";
    string datatype = "USER-";
    string ID = "default";
    string Date = "00-00-0000";
    vector<string> friend_list;
    vector<string> page_list;
    vector<string> post;
    vector<string> liked;
    vector<string> commented_posts;
    User()
    {
        ID = IDassigner(datatype, user_name_file_path);
        cout << "Enter your name\n";
        getline(cin, name);
        cout << "Your unique ID is \t" << ID << endl;
        cout << "Remember your ID you can use it to access the app\n";
        cout << "Set date in format DD-MM-YYYY\n";
        getline(cin, Date);
        ofstream file(user_name_file_path, ios::app);
        Tokenizer(name);
        file << ID << ' ' << name << '\n';
        Detokenizer(name);
    }
    User(string _ID)
    {
        ID = _ID;
        name = NextGetter(_ID, user_name_file_path);
        Detokenizer(name);
        cout << "Set date in format DD-MM-YYYY\n";
        getline(cin, Date);
    }
    ~User()
    {
        cout << "Destructor called\n";
        DeletePTR(friend_list);
        DeletePTR(page_list);
        DeletePTR(post);
        DeletePTR(liked);
        DeletePTR(commented_posts);
    }
};
class Page :public MajorUsedFunctions
{
public:
    string _owner_id = "DEFAULT";
    string name = "default";
    string datatype = "PAGE-";
    string ID = "default";
    string title = "default";
    string context = "default";
    string Date = "00-00-0000";
    vector<string> friend_list;
    vector<string> post;
    Page(string n)
    {
        if (DuplicateCheck(page_title_file_path, n))
        {
            ID = n;
            _owner_id = NextGetter(ID, page_owner_file_path);
            name = NextGetter(_owner_id, user_name_file_path);
            title = NextGetter(ID, page_title_file_path);
            context = NextGetter(ID, page_description_file_path);
        }
        else
        {
            cout << "User not found\n";
        }

    }
    Page(User *ptr)
    {
        ID = IDassigner(datatype, user_owner_page_file_path);
        cout << "Enter your page title\n";
        getline(cin, title);
        cout << "Enter your description\n";
        getline(cin, context);
        _owner_id = ptr->ID;
        writetofile(user_owner_page_file_path,_owner_id,ID);
        writetofile(page_title_file_path, ID, title);
        writetofile(page_description_file_path, ID, context);
        
    }
    ~Page()
    {
        DeletePTR(post);
        DeletePTR(friend_list);
    }
};
class Post :public MajorUsedFunctions
{
public:
    string ID;
    string context;
    string owner;
    vector<string> comments;
    Post(string _ID)
    {
        if (DuplicateCheck(user_post_file_path, _ID))
        {
            ID = _ID;
            context = NextGetter(ID, post_description_file_path);
            owner = NextGetter(ID, post_owner_file_path);
            getwhatever(post_comments_file_path, comments, ID);
        }
    }
    template<class b>
    Post(b*&ptr)
    {
        cout << "Enter your post context\n";
        getline(cin, context);
        ID = IDassigner("POST-", user_post_file_path);
        owner = ptr->ID;
        writetofile(user_post_file_path, owner, ID);
        writetofile(post_description_file_path, ID, context);
        writetofile(post_owner_file_path, ID, owner);

    }
    ~Post()
    {
        DeletePTR(comments);
    }
    void addpost(Post* ptr)
    {
        writetofile(user_post_file_path, ptr->owner, ptr->ID);
        writetofile(post_description_file_path, ptr->ID, ptr->context);
        writetofile(post_owner_file_path, ptr->ID, ptr->owner);
    }
};

class Driver:public MajorUsedFunctions
{
public:
    void login(User*&main)
    {
        string temp;
        cout << "Enter your user ID\n";
        getline(cin, temp);
        if (DuplicateCheck(user_name_file_path, temp))
        {
            main = new User(temp);
            cout << "Welcome user \t" << main->name << endl;
            
        }
        else
        {
            cout << "No such user exist\n";
            main=nullptr;
        }
    }
    void Signup(User*main)
    {
        main = new User;
    }
    template<class c>
    void viewposts(c*&ptr)
    {
        getwhatever(user_post_file_path, ptr->post, ptr->ID);
        for  (auto i:ptr->post)
        {
            cout << i << '\t' << NextGetter(i, post_description_file_path) << endl;
        }
    }
    template<class d>
    void viewFriendlist(d*& ptr)
    {
        getwhatever(user_friend_file_path, ptr->friend_list, ptr->ID);
        for (int i=0;i< (ptr->friend_list.size());i++)
        {
            cout << ptr->friend_list[i] << '\t' << NextGetter(ptr->friend_list[i].erase(0,2), user_name_file_path) << endl;
        }
    }
    template<class E>
    void createApost(E*&ptr)
    {
        Post a(ptr);
    }
    void createAcomment(User*&ptr,string pid)
    {
        if (OccurenceCounter(pid,post_comments_file_path)<10)
        {
            string commentID = IDassigner("COMMENT-", post_comments_file_path);
            string context;
            cout << "Enter context of comment\n";
            getline(cin, context);
            writetofile(user_comment_file_path, ptr->ID, commentID);
            writetofile(post_comments_file_path, pid, commentID);
            writetofile(comment_description_file_path, commentID, context);
            writetofile(comment_post_file_path, commentID, pid);
        }
        else
        {
            cout << "limit of comment over exceded\n";
        }
    }
    void likeApost(User*& ptr, string pid)
    {
        if (OccurenceCounter(pid,user_likedPosts_file_Path)<10)
        {
            writetofile(user_likedPosts_file_Path, ptr->ID, pid);
            writetofile(post_likedusers_file_path, pid, ptr->ID);
        }
    }
    void Home(User*& ptr)
    {
        // Get the friend list and liked posts of the user
        getwhatever(user_friend_file_path, ptr->friend_list, ptr->ID);
        getwhatever(user_likedPosts_file_Path, ptr->liked, ptr->ID);

        // Temporary storage for pages liked by the user
        vector<string> tempPages;
        string t;

        // Collect pages liked by the user
        for (auto i : ptr->liked)
        {
            t = NextGetter(i, post_owner_file_path);
            if (t.substr(0,5) == "PAGE-")
            {
                tempPages.push_back(t);
            }
        }

        // Display posts from friends
        for (auto friendID : ptr->friend_list)
        {
            if (!friendID.empty())
            {
                // Get posts for each friend
                vector<string> friendPosts;
                getwhatever(user_post_file_path, friendPosts, friendID.erase(0, 2));

                // Display each friend's posts
                for (auto postID : friendPosts)
                {
                    if (!postID.empty())
                    {
                        string temp = NextGetter(postID, post_description_file_path);
                        cout << "Friend Post: " << postID << ' ' << temp << endl;
                    }
                }
            }
        }

        // Display posts from liked pages
        for (auto pageID : tempPages)
        {
            if (!pageID.empty())
            {
                // Get posts for each liked page
                vector<string> pagePosts;
                getwhatever(user_post_file_path, pagePosts, pageID);

                // Display each liked page's posts
                for (auto postID : pagePosts)
                {
                    if (!postID.empty())
                    {
                        string temp = NextGetter(postID, post_description_file_path);
                        cout << "Liked Page Post: " << postID << ' ' << temp << endl;
                    }
                }
            }
        }
    }
    void driver_run()
    {
        User* main = nullptr;
        login(main);
        Page* a = new Page(main);
        createApost(a);
        viewposts(a);
        delete main;
    }
};
