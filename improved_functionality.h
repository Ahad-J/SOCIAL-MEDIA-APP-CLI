#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<vector>
#include <ctime>
#include <sstream>
#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
using namespace std;
using namespace sf;
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
    string timeline_post_file_path = "timeline.txt";
    string post_timeline_file_path = "post_timeline.txt";
    string getCurrentLocalTimeAsString(int i) {
        // Get the current time
        time_t now;
        struct tm current_time;
        time(&now);
        localtime_s(&current_time, &now);

        // Convert current time to string
        stringstream ss;
        ss << (current_time.tm_year + 1900) << '-'
            << (current_time.tm_mon + 1) << '-'
            << current_time.tm_mday-i;
        return ss.str();
    }
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
            if (_temp == search_word)
            {
                file >> _temp;
                if (!_temp.empty())
                {
                    storage.push_back(_temp);
                }
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
        if (!firxt.empty()&&!second.empty())
        {
            ofstream file(filepath, ios::app);
            Tokenizer(firxt);
            Tokenizer(second);
            file << firxt << ' ' << second << '\n';
            file.close();
            Detokenizer(firxt);
            Detokenizer(second);
        }
       
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
        cin.ignore();
        getline(cin, name);
        cout << "Your unique ID is \t" << ID << endl;
        cout << "Remember your ID you can use it to access the app\n";
        cout << "Set date in format DD-MM-YYYY\n";
        Date = getCurrentLocalTimeAsString(0);
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
        Date = getCurrentLocalTimeAsString(0);
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
    vector<string> likes;
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
        cin.ignore();
        getline(cin, context);
        ID = IDassigner("POST-", user_post_file_path);
        owner = ptr->ID;
        writetofile(user_post_file_path, owner, ID);
        writetofile(post_description_file_path, ID, context);
        writetofile(post_owner_file_path, ID, owner);
        writetofile(timeline_post_file_path,ptr->Date,ID);
        writetofile(post_timeline_file_path, ID, ptr->Date);


    }
    template<class b>
    Post(b*& ptr,string Pid)
    {
        context = NextGetter(Pid, post_description_file_path);
        context += "---reposted from ";
        string org_owner = NextGetter(Pid, post_owner_file_path);
        context += org_owner;
        ID = IDassigner("POST-", user_post_file_path);
        owner = ptr->ID;
        writetofile(user_post_file_path, owner, ID);
        writetofile(post_description_file_path, ID, context);
        writetofile(post_owner_file_path, ID, owner);
        writetofile(timeline_post_file_path, ptr->Date, ID);
        writetofile(post_timeline_file_path, ID, ptr->Date);


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

class Driver :public MajorUsedFunctions
{
public:
    void login(User*& main)
    {
        string temp;
        cout << "Enter your user ID\n";
        cin.ignore();
        getline(cin, temp);
        if (DuplicateCheck(user_name_file_path, temp))
        {
            main = new User(temp);
            cout << "Welcome user \t" << main->name << endl;

        }
        else
        {
            cout << "No such user exist\n";
            main = nullptr;
        }
    }
    void Signup(User*& main)
    {
        main = new User;
    }
    template<class c>
    void viewposts(c*& ptr)
    {
        for (auto i : ptr->post)
        {
            cout << i << '\t' << NextGetter(i, post_description_file_path) << endl;
        }
    }
    template<class d>
    void viewFriendlist(d*& ptr)
    {
        getwhatever(user_friend_file_path, ptr->friend_list, ptr->ID);
        for (int i = 0; i < (ptr->friend_list.size()); i++)
        {
            cout << ptr->friend_list[i] << '\t' << NextGetter(ptr->friend_list[i].erase(0, 2), user_name_file_path) << endl;
        }
    }
    template<class E>
    void createApost(E*& ptr)
    {
        Post a(ptr);

    }
    void createAcomment(User*& ptr, string pid)
    {
        if (OccurenceCounter(pid, post_comments_file_path) < 10 && !pid.empty())
        {
            string commentID = IDassigner("COMMENT-", post_comments_file_path);
            string context;
            cout << "Enter context of comment\n";
            cin.ignore();
            getline(cin, context);
            writetofile(user_comment_file_path, ptr->ID, commentID);
            writetofile(post_comments_file_path, pid, commentID);
            writetofile(comment_description_file_path, commentID, context);
            writetofile(comment_post_file_path, commentID, pid);
            writetofile(post_timeline_file_path, commentID, ptr->Date);
            writetofile(timeline_post_file_path, ptr->Date, commentID);
        }
        else
        {
            cout << "limit of comment over exceded\n";
        }
    }
    void likeApost(User*& ptr, string pid)
    {
        if (OccurenceCounter(pid, user_likedPosts_file_Path) < 10 && !pid.empty())
        {
            writetofile(user_likedPosts_file_Path, ptr->ID, pid);
            writetofile(post_likedusers_file_path, pid, ptr->ID);
            writetofile(timeline_post_file_path, "L-" + pid, ptr->Date);
            writetofile(post_timeline_file_path, ptr->Date, "L-" + pid);
        }
    }
    void Home(User*& ptr, vector<string>& friendPosts, vector<string>& pagePosts)
    {
        if (ptr == nullptr) {
            cout << "Error: User not logged in.\n";
            return;
        }

        // Get the friend list and liked posts of the user
        getwhatever(user_friend_file_path, ptr->friend_list, ptr->ID);
        getwhatever(user_likedPosts_file_Path, ptr->liked, ptr->ID);
        if (ptr->friend_list.empty())
        {
            cout << "NO FRIENDS ADDED IN LIST\n";
        }
        if (ptr->liked.empty())
        {
            cout << "NO LIKED POSTS EXIST\n";
        }
        // Get the current date and time
        string currentDate = getCurrentLocalTimeAsString(0);
        string hrdate = getCurrentLocalTimeAsString(1);

        // Temporary storage for pages liked by the user
        vector<string> tempPages;
        string t;

        // Collect pages liked by the user
        for (auto i : ptr->liked)
        {
            t = NextGetter(i, post_owner_file_path);
            if (t.substr(0, 5) == "PAGE-")
            {
                tempPages.push_back(t);
            }
        }

        // Display posts from friends shared in the last 24 hours
        for (auto friendID : ptr->friend_list)
        {
            if (!friendID.empty())
            {
                // Get posts for each friend
                getwhatever(user_post_file_path, friendPosts, friendID.erase(0, 2));

                // Display each friend's posts shared in the last 24 hours
                for (auto postID : friendPosts)
                {
                    if (!postID.empty())
                    {
                        string postDate = NextGetter(postID, post_timeline_file_path);
                        if (postDate == currentDate || postDate == hrdate)
                        {
                            string temp = NextGetter(postID, post_description_file_path);
                            cout << "Friend Post: " << postID << ' ' << temp << endl;
                        }
                    }
                    else if (friendPosts.empty())
                    {
                        cout << "NO FRIENDS POSTS IN LAST 24 hrs\n";
                        break;
                    }
                }
            }
        }

        // Display posts from liked pages shared in the last 24 hours
        for (auto pageID : tempPages)
        {
            if (!pageID.empty())
            {
                // Get posts for each liked page
                getwhatever(user_post_file_path, pagePosts, pageID);

                // Display each liked page's posts shared in the last 24 hours
                for (auto postID : pagePosts)
                {
                    if (!postID.empty())
                    {
                        string postDate = NextGetter(postID, post_timeline_file_path);
                        if (postDate == currentDate || postDate == hrdate)
                        {
                            string temp = NextGetter(postID, post_description_file_path);
                            cout << "Liked Page Post: " << postID << ' ' << temp << endl;
                        }
                    }
                    else if (pagePosts.empty())
                    {
                        cout << "NO PAGE POSTS IN LAST 24 hrs\n";
                        break;
                    }
                }
            }
        }
    }
    void Loginwindow()
    {
        sf::RenderWindow window(sf::VideoMode(800, 800), "INSTA-M", sf::Style::Close);
        sf::Event action;

        // Heading
        sf::Font f1;
        f1.loadFromFile("font1.otf");
        sf::Text T1;
        T1.setFont(f1);
        T1.setString("InstaM");
        T1.setCharacterSize(80);
        T1.setFillColor(sf::Color::White);
        T1.setOutlineColor(sf::Color::Black); // Set outline color
        T1.setOutlineThickness(5); // Set outline thickness
        sf::FloatRect textRect1 = T1.getLocalBounds();
        T1.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
        T1.setPosition(800 / 2, 100); // Centered at the top of the window

        // Login button
        sf::RectangleShape loginouter;
        sf::Text T2;
        T2.setFont(f1);
        T2.setString("LOGIN");
        T2.setCharacterSize(50);
        T2.setFillColor(sf::Color::Black);
        T2.setOutlineColor(sf::Color::White); // Set outline color
        T2.setOutlineThickness(2); // Set outline thickness
        sf::FloatRect textRect2 = T2.getLocalBounds();
        T2.setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
        T2.setPosition(800 / 2, 400); // Position login button text centered within the button

        loginouter.setSize(sf::Vector2f(200, 50));
        loginouter.setPosition(800 / 2 - 100, 350); // Adjusted position to center vertically
        loginouter.setOutlineThickness(20);
        loginouter.setFillColor(sf::Color::Red);
        loginouter.setOutlineColor(sf::Color::Blue);

        // Signup button
        sf::RectangleShape signupouter;
        sf::Text T3;
        T3.setFont(f1);
        T3.setString("SIGNUP");
        T3.setCharacterSize(50);
        T3.setFillColor(sf::Color::Black);
        T3.setOutlineColor(sf::Color::White); // Set outline color
        T3.setOutlineThickness(2); // Set outline thickness
        sf::FloatRect textRect3 = T3.getLocalBounds();
        T3.setOrigin(textRect3.left + textRect3.width / 2.0f, textRect3.top + textRect3.height / 2.0f);
        T3.setPosition(800 / 2, 550); // Position signup button text centered within the button

        signupouter.setSize(sf::Vector2f(200, 50));
        signupouter.setPosition(800 / 2 - 100, 500); // Adjusted position to center vertically
        signupouter.setOutlineThickness(20);
        signupouter.setFillColor(sf::Color::Green);
        signupouter.setOutlineColor(sf::Color::Blue);

        while (window.isOpen())
        {
            while (window.pollEvent(action))
            {
                if (action.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (action.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                    if (loginouter.getGlobalBounds().contains(mousePosF))
                    {
                        loginouter.setOutlineColor(sf::Color::Cyan);
                        loginouter.setOutlineThickness(25);
                        loginouter.setFillColor(sf::Color::Yellow);
                    }
                    else if (signupouter.getGlobalBounds().contains(mousePosF))
                    {
                        signupouter.setOutlineColor(sf::Color::Cyan);
                        signupouter.setOutlineThickness(25);
                        signupouter.setFillColor(sf::Color::Yellow);
                    }
                }
            }

            window.clear(sf::Color::White);
            window.draw(T1); // Draw heading
            window.draw(loginouter);
            window.draw(T2);
            window.draw(signupouter);
            window.draw(T3);
            window.display();
        }
    }
    void viewvector(vector<string>temp)
    {
        for (auto i : temp)
        {
            if (!i.empty())
            {
                cout << i << endl;
            }
        }
    }
    void getsuggestions(string file_path, vector<string> &storage, string sub, int start, int end)
    {
        ifstream file(file_path, ios::in);
        string _temp;
        while (file >> _temp)
        {
            if (_temp.substr(start, end) == sub)
            {
                if (!_temp.empty())
                {
                    storage.push_back(_temp);
                }
            }
        }
        file.close();
    }
    void driver_run()
    {
        User* main = nullptr;
        cout << "\t\tWELCOME TO CLI BASED SOCIAL MEDIA APP\n\t\tenter l for login\n\t\tenter s for signup\nenter p to login into a page";
        char choice = ' '; cin >> choice;
        if (choice == 'l' || choice == 'L')
        {
            login(main);
        }
        else if (choice == 's' || choice == 'S')
        {
            Signup(main);
        }
        else if (choice=='P'||choice=='p')
        {
            cout << "Enter your Page ID\n";
            string temp;
            getline(cin, temp);
            if (DuplicateCheck(page_owner_file_path,temp))
            {
                Page* main_ = new Page(temp);
                getwhatever(user_post_file_path, main_->post, main_->ID);
                viewposts(main_);
                cout << "WELCOME TO YOUR PROFILE WHAT WOULD U LIKE TO DO\n";
                cout << "Options\n";
                cout << "1->View posts (a)\n";
                cout << "2->Create posts (b)\n";
                cin >> choice;
                if (choice == 'a' && !main_->post.empty())
                {
                    cout << "Enter Index to view posts\n";
                    int index;
                    cin >> index;
                    if (index <= main_->post.size() && index != 0)
                    {
                        cout << main_->post[index - 1] << ' ' << NextGetter(main_->post[index - 1], post_description_file_path);
                        cout << "Options\n";
                        cout << "1->View comments (a)\n";
                        cout << "2->View likes (b)\n";
                        cout << "3->View publishing date (c)\n";
                        cin >> choice;
                        if (choice == 'a')
                        {
                            Post a(main_->post[index - 1]);
                            getwhatever(post_comments_file_path, a.comments, a.ID);
                            viewvector(a.comments);
                        }
                        else if (choice == 'b')
                        {
                            Post a(main_->post[index - 1]);
                            getwhatever(post_likedusers_file_path, a.likes, a.ID);
                            viewvector(a.likes);
                        }
                        else if (choice == 'c')
                        {
                            cout << NextGetter(main_->post[index - 1], post_timeline_file_path) << endl;
                        }

                    }
                    else if (index > main_->post.size())
                    {
                        cout << "Invalid index entered\n";
                    }

                }
                else if (choice == 'b')
                {
                    createApost(main_);
                }
                else if (main_->post.empty())
                {
                    cout << "No post to show\n";
                }


            }
            

        }
        if (main)
        {
            while (choice != '0')
            {

                cout << "\t\tMENU\n";
                cout << "1->Enter 1 for home\n";
                cout << "2->Enter 2 for profile\n";
                cout << "3->Enter 3 for friend list\n";
                cout << "4->Enter 4 for page list\n";
                cout << "5-Enter 5 to recieve friend suggestions\n";
                cout << "6->Press 0 to exit menu\n";
                cin >> choice;
                //system("CLS");
                if (choice == '1')
                {
                    vector<string> temp1;
                    vector<string> temp2;
                    system("CLS");
                    Home(main, temp1, temp2);
                    if (!temp1.empty() || !temp2.empty())
                    {
                        int index = 0;
                        cout << "Enter index to like / comment on post\n";
                        cin >> index;
                        if (index < temp1.size())
                        {
                            cout << "What would you like to do\n";
                            cout << "1->like (a)\n";
                            cout << "2->comment (b)\n";
                            cout << "3->Repost (c)\n";
                            cin >> choice;
                            if (choice == 'a')
                            {
                                likeApost(main, temp1[index - 1]);
                            }
                            else if (choice == 'b')
                            {
                                createAcomment(main, temp1[index - 1]);
                            }
                            else if (choice == 'c')
                            {
                                Post a(main, temp1[index - 1]);
                            }
                        }
                        else if (index > temp1.size() && index<temp1.size()+temp2.size())
                        {
                            cout << "What would you like to do\n";
                            cout << "1->like (a)\n";
                            cout << "2->comment (b)\n";
                            cout << "3->Repost (c)\n";
                            cin >> choice;
                            if (choice == 'a')
                            {
                                likeApost(main, temp2[index - temp1.size() - 1]);
                            }
                            else if (choice == 'b')
                            {
                                createAcomment(main, temp2[index - temp1.size() - 1]);
                            }
                            else if (choice == 'c')
                            {
                                Post a(main, temp2[index - temp1.size() - 1]);

                            }
                        }
                        else
                        {
                            cout << "Invalid index entered\n";
                        }
                    }

                }
                else if (choice == '2')
                {
                    getwhatever(user_post_file_path, main->post, main->ID);
                    viewposts(main);
                        cout << "WELCOME TO YOUR PROFILE WHAT WOULD U LIKE TO DO\n";
                        cout << "Options\n";
                        cout << "1->View posts (a)\n";
                        cout << "2->Create posts (b)\n";
                        cout << "2->Create a page (c)\n";
                        cin >> choice;
                        if (choice == 'a' && !main->post.empty())
                        {
                            cout << "Enter Index to view posts\n";
                            int index;
                            cin >> index;
                            if (index<=main->post.size() && index!=0)
                            {
                                cout << main->post[index - 1] << ' ' << NextGetter(main->post[index - 1], post_description_file_path);
                                cout << "Options\n";
                                cout << "1->View comments (a)\n";
                                cout << "2->View likes (b)\n";
                                cout << "3->View publishing date (c)\n";
                                cin >> choice;
                                if (choice == 'a')
                                {
                                    Post a(main->post[index - 1]);
                                    getwhatever(post_comments_file_path, a.comments, a.ID);
                                    viewvector(a.comments);
                                }
                                else if (choice == 'b')
                                {
                                    Post a(main->post[index - 1]);
                                    getwhatever(post_likedusers_file_path, a.likes, a.ID);
                                    viewvector(a.likes);
                                }
                                else if (choice == 'c')
                                {
                                    cout << NextGetter(main->post[index - 1], post_timeline_file_path) << endl;
                                }
                                
                            }
                            else if (index > main->post.size())
                            {
                                cout << "Invalid index entered\n";
                            }
                            
                        }
                        else if (choice == 'b')
                        {
                            createApost(main);
                        }
                        else if (main->post.empty())
                        {
                            cout << "No post to show\n";
                        }
                        else if (choice=='c')
                        {
                            Page* main_ = new Page(main);
                            getwhatever(user_post_file_path, main_->post, main_->ID);
                            viewposts(main_);
                            cout << "WELCOME TO YOUR PROFILE WHAT WOULD U LIKE TO DO\n";
                            cout << "Options\n";
                            cout << "1->View posts (a)\n";
                            cout << "2->Create posts (b)\n";
                            cin >> choice;
                            if (choice == 'a' && !main_->post.empty())
                            {
                                cout << "Enter Index to view posts\n";
                                int index;
                                cin >> index;
                                if (index <= main_->post.size() && index != 0)
                                {
                                    cout << main_->post[index - 1] << ' ' << NextGetter(main_->post[index - 1], post_description_file_path);
                                    cout << "Options\n";
                                    cout << "1->View comments (a)\n";
                                    cout << "2->View likes (b)\n";
                                    cout << "3->View publishing date (c)\n";
                                    cin >> choice;
                                    if (choice == 'a')
                                    {
                                        Post a(main_->post[index - 1]);
                                        getwhatever(post_comments_file_path, a.comments, a.ID);
                                        viewvector(a.comments);
                                    }
                                    else if (choice == 'b')
                                    {
                                        Post a(main_->post[index - 1]);
                                        getwhatever(post_likedusers_file_path, a.likes, a.ID);
                                        viewvector(a.likes);
                                    }
                                    else if (choice == 'c')
                                    {
                                        cout << NextGetter(main_->post[index - 1], post_timeline_file_path) << endl;
                                    }

                                }
                                else if (index > main_->post.size())
                                {
                                    cout << "Invalid index entered\n";
                                }

                            }
                            else if (choice == 'b')
                            {
                                createApost(main_);
                            }
                            else if (main_->post.empty())
                            {
                                cout << "No post to show\n";
                            }


                        }
                        
                            
                }
                else if (choice == '3')
                {
                    viewFriendlist(main);
                    if (!main->friend_list.empty())
                    {
                        int index;
                        cout << "Enter index to view friend profile\n";
                        cin >> index;
                        cout << "Name-:\t" << NextGetter(main->friend_list[index - 1], user_name_file_path)<<endl;
                        vector<string>temp;
                        getwhatever(user_post_file_path, temp, main->friend_list[index - 1]);
                        viewvector(temp);
                        cout << "Enter post to interact\n";
                        cin >> index;
                        cout << "What would you like to do\n";
                        cout << "1->like (a)\n";
                        cout << "2->comment (b)\n";
                        cout << "3->Repost (c)\n";
                        cin >> choice;
                        if (choice == 'a')
                        {
                            likeApost(main, temp[index - 1]);
                        }
                        else if (choice == 'b')
                        {
                            createAcomment(main, temp[index - 1]);
                        }
                        else if (choice == 'c')
                        {
                            Post a(main, temp[index - 1]);
                        }
                    }
                    else
                    {
                        cout << "NO FRIENDS JEE\n";
                    }
                }
                else if (choice == '4')
                {
                    vector<string>temp;
                    getsuggestions(page_owner_file_path, temp, "PAGE-", 0, 5);
                    viewvector(temp);
                    if (!temp.empty())
                    {
                        cout << "Enter page to interact\n";
                        int index;
                        cin >> index;
                        vector<string>temp_post;
                        getwhatever(user_post_file_path, temp_post, temp[index - 1]);
                        cout << "What would you like to do\n";
                        cout << "1->like (a)\n";
                        cout << "2->comment (b)\n";
                        cout << "3->Repost (c)\n";
                        cin >> choice;
                        if (choice == 'a')
                        {
                            likeApost(main, temp_post[index - 1]);
                        }
                        else if (choice == 'b')
                        {
                            createAcomment(main, temp_post[index - 1]);
                        }
                        else if (choice == 'c')
                        {
                            Post a(main, temp_post[index - 1]);
                        }
                    }
                    else
                    {
                        cout << "NO pages followed yet\n";
                    }

                }
                else if (choice == '0')
                {
                    break;
                }
                else if(choice=='5')
                {
                    vector<string> temp1;
                    getsuggestions(user_name_file_path,temp1,"USER-", 0, 5);
                    viewvector(temp1);
                    if (!temp1.empty())
                    {
                        int index = 0;
                        cout << "Enter index to add user as your friend\n";
                        cin >> index;
                        addfriend(main->ID, temp1[index - 1]);
                    }
                    
                }

            }
        }

    }
};