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
    string user_file_path = "user.txt";
    string friend_file_path = "_friend.txt";
    string post_file_path = "_post.txt";
    string post_description_file_path = "_post_description.txt";
    string liked_Posts_file_Path = "_liked_posts.txt";
    string comment_file_path = "_comment.txt";
    string comment_post_file_path = "_comment_post.txt";
    string comment_description_file_path = "_comment_description.txt";
    string page_file_path = "_page.txt";
    string page_owner_file_path = "_page_owner.txt";
    string owner_post_file_path = "_owner_post.txt";
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
    string IDassigner(const string& parent_id,const string& file_path)
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
        ifstream file(file_path,ios::in);
        string _temp;
        while (file >> _temp)
        {
            if (_temp == _search)
            {
                file >> _temp;
                file.close();
                return _temp;
            }
        }
        file.close();
        return "";
    }
    int OccurenceCounter(const string& _search, const string& file_path)
    {
        int counter = 0;
        ifstream file(file_path);
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
    template<class a>
    void getfriends(const string& file_path, a*& ptr)
    {
        ptr->friend_list_counter = OccurenceCounter(ptr->ID, file_path);
        ptr->friend_list.resize(ptr->friend_list_counter);
        ifstream file(file_path);
        string _temp;
        int index = 0;
        while (file >> _temp)
        {
            if (_temp == ptr->ID)
            {
                file >> _temp;
                ptr->friend_list[index] = _temp;
                ++index;
            }
        }
    }
    template<class b>
    void viewfriends(b* ptr)
    {
        for (const auto& friendID : ptr->friend_list)
        {
            string temp = friendID.substr(2);
            cout << friendID << '\t' << NextGetter(temp, user_file_path) << endl;
        }
    }
    template<class c>
    void addfriend(c*& ptr, string FRNDID)
    {
        if (DuplicateCheck(user_file_path, FRNDID))
        {
            FRNDID = "F-" + FRNDID;
            ofstream file(friend_file_path, ios::app);
            if (!file.is_open())
            {
                cout << "File could not be opened\n";
                return;
            }
            file << ptr->ID << ' ' << FRNDID << '\n';
        }
        else
        {
            cout << "User not found\n";
        }
    }
    template<class c>
    void addpost(c*& ptr)
    {
        string context, ID;
        ID = IDassigner("POST-",post_description_file_path);
        cout << "Enter context\n";
        getline(cin, context);
            ofstream file(post_file_path, ios::app);
            if (!file.is_open())
            {
                cout << "File could not be opened\n";
                return;
            }
            file << ptr->ID << ' ' << ID << '\n';
            file.close();
            ofstream file2(post_description_file_path, ios::app);
            Tokenizer(context);
            file2 << ID << ' ' <<context<< '\n';
            ptr->post.push_back(ID);
    }
    void DeletePTR(vector<string**>& _array, int& _array_size)
    {
        for (int i = 0; i < _array_size; i++)
        {
            delete[] _array[i];
        }
        _array.clear();
        _array_size = 0;
    }
    template<class a>
    void getPost(const string& file_path,a*& ptr,string &_ID)
    {
        ptr->post_counter += OccurenceCounter(_ID, file_path);
        ptr->post.resize(ptr->post_counter+1);
        ifstream file(file_path,ios::in);
        string _temp;
        int index = 0;
        while (file >> _temp)
        {
            if (_temp == _ID)
            {
                file >> _temp;
                ptr->post[index] = _temp;
                ++index;
            }
        }
        file.close();
    }
    template<class b>
    void viewposts(b* ptr)
    {
        for (const auto& postID : ptr->post)
        {
            string temp = NextGetter(postID, post_description_file_path);
            Detokenizer(temp);
            cout << postID << '\t' << temp << endl;
        }
    }
    template<class a>
    void getcomment(const string& file_path, a*& ptr)
    {
        ptr->commented_posts_counter = OccurenceCounter(ptr->ID, file_path);
        ptr->commented_posts.resize(ptr->commented_posts_counter);
        ifstream file(file_path);
        string _temp;
        int index = 0;
        while (file >> _temp)
        {
            if (_temp == ptr->ID)
            {
                file >> _temp;
                ptr->commented_posts[index] = _temp;
                ++index;
            }
        }
    }
    template<class b>
    void viewcomment(b* ptr)
    {
        for (const auto& postID : ptr->commented_posts)
        {
            string temp = NextGetter(postID, comment_description_file_path);
            Detokenizer(temp);
            cout << postID << '\t' << temp << endl;
        }
    }
    template<class a>
    void getliked(const string& file_path, a*& ptr)
    {
        ptr->liked_counter = OccurenceCounter(ptr->ID, file_path);
        ptr->liked.resize(ptr->liked_counter+1);
        ifstream file(file_path,ios::in);
        string _temp;
        int index = 0;
        while (file >> _temp)
        {
            if (_temp == ptr->ID)
            {
                file >> _temp;
                ptr->liked[index] = _temp;
                ++index;
            }
        }
        file.close();
    }
    template<class b>
    void viewliked (b* ptr)
    {
        for (const auto& postID : ptr->liked)
        {
            string temp = NextGetter(postID,post_description_file_path);
            Detokenizer(temp);
            cout << postID << '\t' << temp << endl;
        }
    }
    template<class c>
    void addlikepost(c*& ptr,string postID)
    {
        ofstream file(liked_Posts_file_Path, ios::app);
        if (!file.is_open())
        {
            cout << "File could not be opened\n";
            return;
        }
        file << ptr->ID << ' ' << postID << '\n';
        file.close();
        ++ptr->liked_counter;
        ptr->liked.resize(ptr->liked_counter);
        ptr->liked.push_back(postID);

    }
    template<class c>
    void addcommentpost(c*& ptr, string postID)
    {
        string context;
        cout << "Enter your comment\n";
        getline(cin, context);
        string commentID;
        commentID=IDassigner("COMMENT-", comment_file_path);
        ofstream file(comment_file_path, ios::app);
        file << ptr->ID << ' ' << commentID << '\n';
        file.close();
        ofstream file2(comment_post_file_path, ios::app);
        file2 << commentID << ' ' << postID << '\n';
        file2.close();
        ofstream file3(comment_description_file_path, ios::app);
        file3 << commentID << ' ' << context << '\n';
        file3.close();
        ++ptr->commented_posts_counter;
        ptr->commented_posts.resize(ptr->commented_posts_counter);
        ptr->commented_posts.push_back(commentID);

    }
    void getwhatever(string filepath,vector<string> storage,string search_word)
    {
        ifstream file(filepath, ios::in);
        string _temp;
        while (file>>_temp)
        {
            if (_temp==search_word)
            {
                file >> _temp;
                storage.resize(storage.size() + 1);
                storage.push_back(_temp);
            }
        }
        file.close();
    }
};
class Page:public MajorUsedFunctions
{
public:
    string _owner_id="DEFAULT";
    string name = "default";
    string datatype = "PAGE-";
    string ID = "default";
    string title = "default";
    string context = "default";
    vector<string> friend_list;
    vector<string> post;
    int friend_list_counter = 0;
    int post_counter = 0;
    Page(string n)
    {
        if (DuplicateCheck(user_file_path,n))
        {
            _owner_id = n;
            ID = NextGetter(_owner_id,page_owner_file_path);
            name = NextGetter(_owner_id, user_file_path);
        }
        
    }
    Page()
    {
        cout << "Enter your user ID\n";
        do
        {
            cout << "Enter your user ID\n";
            getline(cin, _owner_id);
        } while (!DuplicateCheck(user_file_path,_owner_id)&&_owner_id!="0000");
        ID=IDassigner(datatype, user_file_path);
        cout << "Enter your page title\n";
        getline(cin, title);
        cout << "Enter your context\n";
        getline(cin, context);
        ofstream file(page_owner_file_path, ios::app);
        file <<_owner_id << ' ' << ID << '\n';
        file.close();
        ofstream file2(page_file_path, ios::app);
        Tokenizer(title);
        Tokenizer(context);
        file2 << ID << ' ' << title << ' ' << context << '\n';
        Detokenizer(title);
        Detokenizer(context);
        file2.close();
    }
    ~Page()
    {

    }
};
class User : public MajorUsedFunctions
{
public:
    string name = "default";
    string datatype = "USER-";
    string ID = "default";
    vector<string> friend_list;
    vector<string> page_list;
    vector<string> post;
    vector<string> liked;
    vector<string> commented_posts;

    int friend_list_counter = 0;
    int page_list_counter = 0;
    int post_counter = 0;
    int liked_counter = 0;
    int commented_posts_counter = 0;
    User()
    {
        ID=IDassigner(datatype, user_file_path);
        cout << "Enter your name\n";
        getline(cin, name);
        cout << "Your unique ID is \t" << ID << endl;
        cout << "Remember your ID you can use it to access the app\n";
        ofstream file(user_file_path, ios::app);
        Tokenizer(name);
        file << ID << ' ' << name << '\n';
        Detokenizer(name);
    }
    User(string _ID)
    {
        ID = _ID;
        name = NextGetter(_ID, user_file_path);
        Detokenizer(name);
    }
    ~User()
    {

    }
};
class Post:public MajorUsedFunctions
{
public:
    string ID;
    vector<string> comments;
    int comment_counter=0;
    Post(string _ID)
    {
        if (DuplicateCheck(post_file_path,_ID))
        {
            ID = _ID;
            getwhatever(comment_file_path, comments, ID);
        }
    }
    ~Post()
    {

    }
};
class Driver : public MajorUsedFunctions
{
public:
    User* Login()
    {
        User* temp = nullptr;
        cout << "Enter your ID\n";
        string _temp;
        getline(cin, _temp);
        if (DuplicateCheck(user_file_path, _temp))
        {
            cout << "User has been found\n";
            temp = new User(_temp);
            return temp;
        }
        else
        {
            cout << "No such user exists\n";
            return nullptr;
        }
    }
    User* Signup()
    {
        User* temp = new User;
        return temp;
    }
    void Home(User* ptr)
    {
        getliked(liked_Posts_file_Path, ptr);
        ptr->page_list_counter = 0;
        for (int i = 0; i < ptr->liked_counter; i++)
        {
            string pageID = NextGetter(ptr->liked[i], owner_post_file_path);
            if (!pageID.empty())
            {
                ptr->page_list.push_back(pageID);
                ptr->page_list_counter++;
            }
        }
        getfriends(user_file_path, ptr);
        for (int i = 0; i < ptr->friend_list_counter; i++)
        {
            getPost(post_file_path, ptr, ptr->friend_list[i]);
        }
        for (int i = 0; i < ptr->page_list_counter; i++)
        {
            getPost(post_file_path, ptr, ptr->page_list[i]);
        }
        displayposts(ptr->post);
    }

    void displayposts(vector<string> a)
    {
        for (const auto post:a)
        {
            cout << post << endl;
        }
    }
    void likeApost(vector<string> a,int index,User*main)
    {
        addlikepost(main,a[index]);
    }
    void driver()
    {
        User* ptr = nullptr;
        ptr = Login();
        addcommentpost(ptr, "POST-7020");
        Post a("POST-7020");
        for (auto comment:a.comments)
        {
            cout << comment << '\t' << NextGetter(comment, comment_post_file_path);
        }
    }
};
